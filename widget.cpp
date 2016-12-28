#include "widget.h"

#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent), choose(new QComboBox(this)), context(new QLineEdit(this)), start(new QPushButton(this)),
    showName(new QPushButton(this)), logout(new QPushButton(this)),
    login(new Login()), widget(new QTabWidget(this)), checkbox(new QCheckBox("根据当前结果查询", this)),
    resetButton(new QPushButton("重置搜索结果", this)), addPerson(new QPushButton("添加用户", this)),
    delPerson(new QPushButton("删除用户", this)), chooseFile(new QPushButton("文件导入", this))
{
    setMaximumSize(780,500);
    setMinimumSize(780,500);

    widget->setGeometry(30, 160, 620, 300);
    resetButton->setGeometry(680, 200, 80, 30);
    addPerson->setGeometry(680, 250, 80, 30);
    addPerson->hide();
    delPerson->setGeometry(680, 300, 80, 30);
    delPerson->hide();
    chooseFile->setGeometry(680, 450, 80, 30);
    chooseFile->hide();

    id = Empty;
    ope_aim = RepairRecord;

    choose->setGeometry(60, 120, 100, 30);
    context->setGeometry(200, 120, 300, 30);
    start->setGeometry(520, 120, 100, 30);
    start->setText("查询");
    showName->setGeometry(660, 20, 40, 30);
    logout->setGeometry(710, 20, 40, 30);
    logout->setText("注销");
    checkbox->setGeometry(400, 470, 200, 30);

    login->show();
    connect(login, SIGNAL(login_success(QString,QString,Identify)), this, SLOT(login_success(QString,QString,Identify)));
    connect(logout, SIGNAL(clicked(bool)), this, SLOT(logout_success()));
    connect(widget, SIGNAL(currentChanged(int)), this, SLOT(showChanged(int)));
    connect(chooseFile, SIGNAL(clicked(bool)), this, SLOT(inputFromFile()));

}

void Widget::createShowWidget()
{
    for(int i=0; i<7; i++)
    {
        showResults[i] = new TableView(this);
        widget->addTab(showResults[i], name[i]);
        initShow(i);
    }
}

void Widget::login_success(QString _username, QString _password, Identify _id)
{
    login->hide();
    show();
    showName->setText(username);
    createShowWidget();
    if(_id == Root)
    {
        showResults[7] = new TableView(this);
        widget->addTab(showResults[7], name[7]);
        initShow(7);
        showResults[8] = new TableView(this);
        widget->addTab(showResults[8], name[8]);
        initShow(8);
    }
    username = _username;
    password = _password;
    id = _id;
    initShow(0);
}

void Widget::logout_success()
{
    id = Empty;
    widget->clear();
    chooseFile->hide();
    for(int i=0; i<7; i++)
        delete showResults[i];
    if(id == Root)
    {
        delete showResults[7];
        delete showResults[8];
    }
    close();
    login->show();
}

void Widget::showChanged(int index)
{
    ope_aim = (Ope_aim)index;
    if(id == User)
        choose->hide();
    else
    {
        choose->clear();
        if(ope_aim == UserInfor || ope_aim == DormInfor)
            chooseFile->show();
        else
            chooseFile->hide();
        choose->addItem("宿舍");
        choose->addItem("学号");
        switch(ope_aim)
        {
            case ReceiveRecord:
                choose->addItem("信件号");
            break;
            case ReceiveHistory:
                choose->addItem("信件号");
            break;
            default:
                break;
        }
    }
    initShow();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont font;
    font.setCapitalization(QFont::SmallCaps);//设置大小写
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);//设置间距
    font.setPixelSize(30);
    painter.setFont(font);//添加字体
    painter.drawText(QRectF(150, 40, 400, 40), Qt::AlignCenter, QString("欢迎使用宿舍管理系统"));
    QWidget::paintEvent(event);
}

void Widget::initShow(int index)
{
    if(id == Empty)
        return;
    if(index == -1)
        index = ope_aim;
    if(index == UserInfor)
        model[index].setQuery(QString("select 学号,姓名,宿舍楼号,宿舍号 from %1").arg(name[index]));
    else
        model[index].setQuery(QString("select * from %1").arg(name[index]));
    showResults[index]->table->horizontalHeader()->setStretchLastSection(true);
    showResults[index]->table->setModel(&model[index]);
    for(int i=0; i<model[index].columnCount(); i++)
        showResults[index]->table->setColumnWidth(i, 600/model[index].columnCount());
    showResults[index]->table->verticalHeader()->setHidden(true);
}

void Widget::inputFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择导入文件", "", "Text file(*.txt)");
    if(!fileName.isEmpty())
    {
        QByteArray ba = fileName.toLatin1();
        char *mm = ba.data();
        freopen(mm, "r", stdin);
        vector<string>shows;
        if(ope_aim == DormInfor)
        {
            shows.push_back("宿舍楼号");
            shows.push_back("宿舍号");
            shows.push_back("宿舍电话");
        }
        else
        {
            shows.push_back("学号");
            shows.push_back("密码");
            shows.push_back("姓名");
            shows.push_back("性别");
            shows.push_back("院系名");
            shows.push_back("宿舍楼号");
            shows.push_back("宿舍号");
        }
        QList<QString> list;
        string temp;
        int count = 1;
        while(cin >> temp)
        {
            list.append(QString::fromStdString(temp));
            for(int i=1; i<(int)shows.size(); i++)
            {
                if(!(cin>>temp))
                {
                    initShow();
                    QMessageBox::warning(this, "导入文件失败", QString("在第%1条数据处出错").arg(count));
                    return;
                }
                list.append(QString::fromStdString(temp));
            }
            for(int i=0; i<(int)shows.size(); i++)
            {
                if(shows[i] == "性别")
                {
                    if(list.at(i) != "男" && list.at(i) != "女")
                    {
                        initShow();
                        QMessageBox::warning(this, "导入文件失败", QString("在第%1条数据处出错").arg(count));
                        return;
                    }
                }
            }
            if(ope_aim == DormInfor)
                model[ope_aim].setQuery(QString("insert into 宿舍 values(%1,%2,%3)").arg(list.at(0)).arg(list.at(1)).arg(list.at(2)));
            else model[ope_aim].setQuery(QString("insert into 学生 values(%1,'%2','%3','%4','%5',%6,%7)").arg(list.at(0)).arg(list.at(1)).arg(list.at(2)).arg(list.at(3)).arg(list.at(4)).arg(list.at(5)).arg(list.at(6)));
            list.clear();
            count++;
        }
        freopen("/dev/console", "r", stdin);
        QMessageBox::warning(this,"添加成功","成功从文件导入数据");
        model[ope_aim].submit();
        initShow();
    }
}

Widget::~Widget()
{
}
