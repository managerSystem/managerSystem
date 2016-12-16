#include "widget.h"

#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>

Widget::Widget(QWidget *parent) :
    QWidget(parent), choose(new QComboBox(this)), context(new QLineEdit(this)), start(new QPushButton(this)),
    showName(new QPushButton(this)), logout(new QPushButton(this)),
    login(new Login()), widget(new QTabWidget(this)), checkbox(new QCheckBox("根据当前结果查询", this)),
    resetButton(new QPushButton("重置搜索结果", this)), addPerson(new QPushButton("添加用户", this)),
    delPerson(new QPushButton("删除用户", this))
{
    setMaximumSize(780,500);
    setMinimumSize(780,500);

    widget->setGeometry(30, 160, 620, 300);
    resetButton->setGeometry(680, 200, 80, 30);
    addPerson->setGeometry(680, 250, 80, 30);
    addPerson->hide();
    delPerson->setGeometry(680, 300, 80, 30);
    delPerson->hide();

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
    for(int i=0; i<8; i++)
        showResults[i] = NULL;
}

void Widget::createShowWidget()
{
    widget->clear();
    for(int i=0; i<7; i++)
    {
        if(showResults[i] != NULL)
            delete showResults[i];
        showResults[i] = new TableView(this);
        widget->addTab(showResults[i], name[i]);
        initShow(i);
    }
    if(id == Root)
    {
        if(showResults[7] != NULL)
            delete showResults[7];
        showResults[7] = new TableView(this);
        widget->addTab(showResults[7], name[7]);
        initShow(7);
    }
}

void Widget::login_success(QString _username, QString _password, Identify _id)
{
    username = _username;
    password = _password;
    id = _id;
    login->hide();
    show();
    showName->setText(username);
    createShowWidget();
}

void Widget::logout_success()
{
    close();
    login->show();
}

void Widget::showChanged(int index)
{
    if(id == User)
        choose->hide();
    else
    {
        choose->clear();
        ope_aim = (Ope_aim)index;
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
    if(index == -1)
        index = ope_aim;
    if(index == UserInfor)
        model[index].setQuery(QString("select 学号,姓名,宿舍楼号,宿舍号 from %1 limit 0,20").arg(name[index]));
    else
        model[index].setQuery(QString("select * from %1").arg(name[index]));
    showResults[index]->table->horizontalHeader()->setStretchLastSection(true);
    showResults[index]->table->setModel(&model[index]);
    for(int i=0; i<model[index].columnCount(); i++)
        showResults[index]->table->setColumnWidth(i, 600/model[index].columnCount());
    showResults[index]->table->verticalHeader()->setHidden(true);
}

Widget::~Widget()
{
}
