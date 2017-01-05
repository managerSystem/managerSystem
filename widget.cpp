#include "widget.h"

#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QHeaderView>
#include <QFileDialog>
#include <QEvent>
#include <QInputDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent), choose(new QComboBox(this)), context(new QLineEdit(this)), start(new QPushButton(this)),
    showName(new QPushButton(this)), logout(new QPushButton(this)),
    login(new Login()), widget(new QTabWidget(this)), checkbox(new QCheckBox("根据当前结果查询", this)),
    resetButton(new QPushButton("重置搜索结果", this)), addPerson(new QPushButton("添加用户", this)),
    addDorm(new QPushButton("添加宿舍", this)), chooseFile(new QPushButton("文件导入", this)),
    addReapir(new QPushButton("报修", this)), repairComplete(new QPushButton("维修完成", this)),
    addMail(new QPushButton("添加信件", this)), getMail(new QPushButton("信件已取", this)),
    addLate(new QPushButton("添加", this)), addLeave(new QPushButton("添加", this)),
    backSchool(new QPushButton("返校", this)), deleteInfor(new QPushButton("删除", this))
{
    setMaximumSize(780,500);
    setMinimumSize(780,500);

    createDialog();
    widget->setGeometry(30, 160, 620, 300);
    resetButton->setGeometry(680, 200, 80, 30);
    addPerson->setGeometry(680, 250, 80, 30);
    addPerson->hide();
    addDorm->setGeometry(680, 250, 80, 30);
    addDorm->hide();
    chooseFile->setGeometry(680, 450, 80, 30);
    chooseFile->hide();
    addReapir->setGeometry(680, 250, 80, 30);
    addReapir->hide();
    repairComplete->setGeometry(680, 250, 80, 30);
    repairComplete->hide();
    addMail->setGeometry(680, 250, 80, 30);
    addMail->hide();
    getMail->setGeometry(680, 300, 80, 30);
    getMail->hide();
    addLate->setGeometry(680, 250, 80, 30);
    addLate->hide();
    addLeave->setGeometry(680, 250, 80, 30);
    addLeave->hide();
    backSchool->setGeometry(680, 300, 80, 30);
    backSchool->hide();
    deleteInfor->setGeometry(680, 400, 80, 30);
    deleteInfor->hide();

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
    connect(addReapir, SIGNAL(clicked(bool)), addReapir2, SLOT(exec()));
    connect(addReapir2, SIGNAL(submit(QList<QString>)), this, SLOT(addRepair3(QList<QString>)));
    connect(repairComplete, SIGNAL(clicked(bool)), this, SLOT(repairComplete2()));
    connect(addMail, SIGNAL(clicked(bool)), addMail2, SLOT(exec()));
    connect(addMail2, SIGNAL(submit(QList<QString>)), this, SLOT(addMail3(QList<QString>)));
    connect(getMail, SIGNAL(clicked(bool)), this, SLOT(getMail2()));
    connect(addLate, SIGNAL(clicked(bool)), addLate2, SLOT(exec()));
    connect(addLate2, SIGNAL(submit(QList<QString>)), this, SLOT(addLate3(QList<QString>)));
    connect(addLeave, SIGNAL(clicked(bool)), addLeave2, SLOT(exec()));
    connect(addLeave2, SIGNAL(submit(QList<QString>)), this, SLOT(addLeave3(QList<QString>)));
    connect(backSchool, SIGNAL(clicked(bool)), this, SLOT(backSchool2()));
    connect(deleteInfor, SIGNAL(clicked(bool)), this, SLOT(deleteInfor2()));
    connect(addPerson, SIGNAL(clicked(bool)), addPerson2, SLOT(exec()));
    connect(addPerson2, SIGNAL(submit(QList<QString>)), this, SLOT(addPerson3(QList<QString>)));
    connect(addDorm, SIGNAL(clicked(bool)), addDorm2, SLOT(exec()));
    connect(addDorm2, SIGNAL(submit(QList<QString>)), this, SLOT(addDorm3(QList<QString>)));

    connect(choose, SIGNAL(currentIndexChanged(int)), this, SLOT(changeReg()));
    connect(start, SIGNAL(clicked(bool)), this, SLOT(showSearch()));
    connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(reset()));
    connect(showName, SIGNAL(clicked(bool)), this, SLOT(changePassword()));
    installEventFilter(this);
}

void Widget::changeReg()
{
    int index=choose->currentIndex();
    int op=ope_aim;
    QRegExp regExp(".*");
    if((index==1&&op==2)||(index==1&&op==3))
        context->setValidator(new QRegExpValidator(regExp, this));
    else
    {
        QRegExp regEx("(^([0-9])+(#[0-9]{7})?$)|(([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3})-(((0[13578]|1[02])-(0[1-9]|[12][0-9]|3[01]))|((0[469]|11)-(0[1-9]|[12][0-9]|30))|(02-(0[1-9]|[1][0-9]|2[0-8]))))");//([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3})-(((0[13578]|1[02])-(0[1-9]|[12][0-9]|3[01]))|((0[469]|11)-(0[1-9]|[12][0-9]|30))|(02-(0[1-9]|[1][0-9]|2[0-8])))
        context->setValidator(new QRegExpValidator(regEx, this));
    }
}

void Widget::reset()
{
    initShow(ope_aim);
}

void Widget::showSearch()
{
    int index=ope_aim;
    switch(ope_aim)
    {
        //int index=ope_aim;
        case RepairRecord://宿舍 报修日期
            if(choose->currentIndex()==0)
            {
                int flag=(context->text()).indexOf('#');

                QStringList dorm=(context->text()).split("#");
                if(flag > 0 && flag < context->text().length()-1)
                {
                    model[index].setQuery(QString("select 财产.财产名,维修.宿舍楼号,维修.宿舍号,维修.报修日期,维修.备注 from 维修,财产 where 维修.财产号=财产.财产号 and 维修.宿舍楼号=%1 and 维修.宿舍号=%2;")
                    .arg(dorm[0])
                    .arg(dorm[1]));
                }
                else
                {
                    alert.setText("请以 楼号#宿舍号 格式输入！");
                    alert.exec();
                    context->clear();
                }
            }
            else if(choose->currentIndex()==1)
            {
                int flag=(context->text()).indexOf('-');
                if(flag==4)
                    model[index].setQuery(QString("select 财产.财产名,维修.宿舍楼号,维修.宿舍号,维修.报修日期,维修.备注 from 维修,财产 where 维修.财产号=财产.财产号 and 维修.报修日期 like '%1%'")
                    .arg(context->text()));
                else
                {
                    alert.setText("请以 xxxx-xx-xx 格式输入！");
                    alert.exec();
                    context->clear();
                }
            }
            break;
        case RepairHistory://宿舍 报修日期
            if(choose->currentIndex()==0)
            {
                QString tmp=context->text();
                int flag=tmp.indexOf('#');
                if(flag <= 0 || flag >= tmp.length()-1 || !tmp.contains('#'))
                {
                    alert.setText("请以 楼号#宿舍号 格式输入！");
                    alert.exec();
                    context->clear();
                    break;
                }
                QStringList dorm=(context->text()).split("#");
                model[index].setQuery(QString("select 财产.财产名,维修记录.宿舍楼号,维修记录.宿舍号,维修记录.报修日期,维修记录.维修日期,维修记录.备注 from 维修记录,财产 where 维修记录.财产号=财产.财产号 and 维修记录.宿舍楼号=%1 and 维修记录.宿舍号=%2;")
                    .arg(dorm[0])
                .arg(dorm[1]));
            }
            else if(choose->currentIndex()==1)
            {
                int flag=(context->text()).indexOf('-');
                if(flag==4)
                    model[index].setQuery(QString("select 财产.财产名,维修记录.宿舍楼号,维修记录.宿舍号,维修记录.报修日期,维修记录.维修日期,维修记录.备注 from 维修记录,财产 where 维修记录.财产号=财产.财产号 and 维修记录.报修日期 like '%1%'")
                    .arg(context->text()));
                else
                {
                    alert.setText("请以 xxxx-xx-xx 格式输入！");
                    alert.exec();
                    context->clear();
                }
            }
            break;
        case ReceiveRecord://信件编号 收件人 到达时间 宿舍
            if(choose->currentIndex()==0)
            {
                if(!context->text().toInt())
                {
                    alert.setText("请输入非零整数");
                    alert.exec();
                    break;
                }
                model[index].setQuery(QString("select * from 信件 where 信件编号=%1")
                 .arg(context->text()));
            }
            else if(choose->currentIndex()==1)
            {
                if(context->text().contains("'") || context->text().contains("\""))
                {
                    alert.setText("对于sql注入，我只能做到这一步了，哈哈");
                    alert.exec();
                    break;
                }
                qDebug()<<context->text()<<endl;
                model[index].setQuery(QString("select * from 信件 where 收件人='%1';")
                .arg(context->text()));
            }
            else if(choose->currentIndex()==2)
            {
                int flag=(context->text()).indexOf('-');
                if(flag==4)
                    model[index].setQuery(QString("select * from 信件 where 信件.到达时间 like '%1%'")
                    .arg(context->text()));
                else
                {
                    alert.setText("请以 xxxx-xx-xx 格式输入！");
                    alert.exec();
                    context->clear();
                }
            }
            else if(choose->currentIndex()==3)
            {
                QString tmp=context->text();
                int flag=tmp.indexOf('#');
                if(flag <= 0 || flag >= tmp.length()-1 || !tmp.contains('#'))
                {
                    alert.setText("请以 楼号#宿舍号 格式输入！");
                    alert.exec();
                    context->clear();
                    break;
                }
                QStringList dorm=(context->text()).split("#");
                model[index].setQuery(QString("select * from 信件 where 宿舍楼号=%1 and 宿舍号=%2;")
                .arg(dorm[0])
                .arg(dorm[1]));
            }
            break;
        case ReceiveHistory://信件编号 收件人 到达时间 收取时间 宿舍
            if(choose->currentIndex()==0)
            {
                if(!context->text().toInt())
                {
                    alert.setText("请输入非零整数");
                    alert.exec();
                    break;
                }
                model[index].setQuery(QString("select * from 收信记录 where 信件编号=%1;")
                .arg(context->text()));
            }
            else if(choose->currentIndex()==1)
            {
                if(context->text().contains("'") || context->text().contains("\""))
                {
                    alert.setText("对于sql注入，我只能做到这一步了，哈哈");
                    alert.exec();
                    break;
                }
                qDebug()<<context->text()<<endl;
                model[index].setQuery(QString("select * from 收信记录 where 收件人='%1';")
                    .arg(context->text()));
            }
            else if(choose->currentIndex()==2)
            {
                int flag=(context->text()).indexOf('-');
                if(flag==4)
                    model[index].setQuery(QString("select * from 收信记录 where 收信记录.到达时间 like '%1%'")
                    .arg(context->text()));
                else
                {
                    alert.setText("请以 xxxx-xx-xx 格式输入！");
                    alert.exec();
                    context->clear();
                }
            }
            else if(choose->currentIndex()==3)
            {
                int flag=(context->text()).indexOf('-');
                if(flag==4)
                    model[index].setQuery(QString("select * from 收信记录 where 信件.收取时间 like '%1%'")
                    .arg(context->text()));
                else
                {
                    alert.setText("请以 xxxx-xx-xx 格式输入！");
                    alert.exec();
                    context->clear();
                }
            }
            else if(choose->currentIndex()==4)
            {
                QString tmp=context->text();
                int flag=tmp.indexOf('#');
                if(flag <= 0 || flag >= tmp.length()-1 || !tmp.contains('#'))
                {
                    alert.setText("请以 楼号#宿舍号 格式输入！");
                    alert.exec();
                    context->clear();
                    break;
                }
                QStringList dorm=(context->text()).split("#");
                model[index].setQuery(QString("select * from 收信记录 where 宿舍楼号=%1 and 宿舍号=%2;")
                .arg(dorm[0])
                .arg(dorm[1]));
            }
            break;
    }
    if(ope_aim==4&&choose->currentIndex()==1)       //学号查询晚归
    {
        QString s_username=context->text();
        model[ope_aim].setQuery(QString("select * from %1 where 学号= '%2'").arg(name[ope_aim]).arg(s_username));
    }
    else if(ope_aim==4&&choose->currentIndex()==0)
    {
        QString tmp=context->text();
        int flag=tmp.indexOf('#');
        if(flag > 0 && flag < tmp.length()-1)
        {
            QStringList dorm=tmp.split('#');
            qDebug()<<dorm[0]<<" "<<dorm[1]<<endl;
            model[ope_aim].setQuery(QString("select * from %1,学生 where 宿舍楼号= %2 and 宿舍号= %3 and %1.学号=学生.学号").arg(name[ope_aim]).arg(dorm[0]).arg(dorm[1]));
        }
        else
        {

            alert.setText("请以 楼号#宿舍号 格式输入！");
            alert.exec();
            context->clear();
        }
    }
    else if(ope_aim==4&&choose->currentIndex()==2)
    {
        int flag=(context->text()).indexOf('-');
        if(flag==4)
            model[index].setQuery(QString("select * from 晚归 where 晚归.晚归日期 like '%1%'")
            .arg(context->text()));
        else
        {
            alert.setText("请以 xxxx-xx-xx 格式输入！");
            alert.exec();
            context->clear();
        }
    }

    else if(ope_aim==5&&choose->currentIndex()==1)    //学号查询离校
    {
        QString s_username=context->text();
        model[ope_aim].setQuery(QString("select * from %1 where 学号= '%2'").arg(name[ope_aim]).arg(s_username));
    }
    else if(ope_aim==5&&choose->currentIndex()==0)
    {
        QString tmp=context->text();
        int flag=tmp.indexOf('#');
        if(flag > 0 && flag < tmp.length()-1)
        {
            QStringList dorm=tmp.split('#');
            qDebug()<<dorm[0]<<" "<<dorm[1]<<endl;
            model[ope_aim].setQuery(QString("select * from %1,学生 where 宿舍楼号= %2 and 宿舍号= %3 and %1.学号=学生.学号").arg(name[ope_aim]).arg(dorm[0]).arg(dorm[1]));
        }
        else
        {

            alert.setText("请以 楼号#宿舍号 格式输入！");
            alert.exec();
            context->clear();
        }
    }
    else if(ope_aim==5&&choose->currentIndex()==2)
    {
        int flag=(context->text()).indexOf('-');
        if(flag==4)
            model[index].setQuery(QString("select * from 离校 where 离校.离校时间 like '%1%'")
            .arg(context->text()));
        else
        {
            alert.setText("请以 xxxx-xx-xx 格式输入！");
            alert.exec();
            context->clear();
        }
    }
    else if(ope_aim==6&&choose->currentIndex()==1)    //学号查询离校记录
    {
        QString s_username=context->text();
        model[ope_aim].setQuery(QString("select * from %1 where 学号= '%2'").arg(name[ope_aim]).arg(s_username));
    }
    else if(ope_aim==6&&choose->currentIndex()==0)
    {
        QString tmp=context->text();
        int flag=tmp.indexOf('#');
        if(flag > 0 && flag < tmp.length()-1)
        {
            QStringList dorm=tmp.split('#');
            qDebug()<<dorm[0]<<" "<<dorm[1]<<endl;
            model[ope_aim].setQuery(QString("select * from %1,学生 where 宿舍楼号= %2 and 宿舍号= %3 and %1.学号=学生.学号").arg(name[ope_aim]).arg(dorm[0]).arg(dorm[1]));
        }
        else
        {

            alert.setText("请以 楼号#宿舍号 格式输入！");
            alert.exec();
            context->clear();
        }
    }
    else if(ope_aim==6&&choose->currentIndex()==2)
    {
        int flag=(context->text()).indexOf('-');
        if(flag==4)
            model[index].setQuery(QString("select * from 离校记录 where 离校记录.离校时间 like '%1%'")
            .arg(context->text()));
        else
        {
            alert.setText("请以 xxxx-xx-xx 格式输入！");
            alert.exec();
            context->clear();
        }
    }
    else if(ope_aim==6&&choose->currentIndex()==3)
    {
        int flag=(context->text()).indexOf('-');
        if(flag==4)
            model[index].setQuery(QString("select * from 离校记录 where 离校记录.归校时间 like '%1%'")
            .arg(context->text()));
        else
        {
            alert.setText("请以 xxxx-xx-xx 格式输入！");
            alert.exec();
            context->clear();
        }
    }
    else if(ope_aim==7&&choose->currentIndex()==1)  //学号搜索学生
    {
        //int index=ope_aim;
        QString s_username=context->text();
        //qDebug() <<s_username<<endl;
        model[ope_aim].setQuery(QString("select 学号,姓名,宿舍楼号,宿舍号 from %1 where 学号= '%2'").arg(name[ope_aim]).arg(s_username));
    }
    else if(ope_aim==7&&choose->currentIndex()==0) //宿舍号搜索学生
    {

        qDebug()<<context->text()<<endl;
        QString tmp=context->text();
        int flag=tmp.indexOf('#');
        if(flag > 0 && flag < tmp.length()-1)
        {
            QStringList dorm=tmp.split('#');
            qDebug()<<dorm[0]<<" "<<dorm[1]<<endl;
            model[ope_aim].setQuery(QString("select 学号,姓名,宿舍楼号,宿舍号 from %1 where 宿舍楼号= %2 and 宿舍号= %3").arg(name[ope_aim]).arg(dorm[0]).arg(dorm[1]));
        }
        else
        {

            alert.setText("请以 楼号#宿舍号 格式输入！");
            alert.exec();
            context->clear();
        }
    }
    else if(ope_aim==8&&choose->currentIndex()==1)  //学号搜索学生
    {
        //int index=ope_aim;
        QString lou=context->text();
        //qDebug() <<s_username<<endl;
        model[ope_aim].setQuery(QString("select * from %1 where 宿舍楼号= '%2'").arg(name[ope_aim]).arg(lou));
    }
    else if(ope_aim==8&&choose->currentIndex()==0)
    {

        qDebug()<<context->text()<<endl;
        QString tmp=context->text();
        int flag=tmp.indexOf('#');
        if(flag > 0 && flag < tmp.length()-1)
        {
            QStringList dorm=tmp.split('#');
            qDebug()<<dorm[0]<<" "<<dorm[1]<<endl;
            model[ope_aim].setQuery(QString("select * from %1 where 宿舍楼号= %2 and 宿舍号= %3").arg(name[ope_aim]).arg(dorm[0]).arg(dorm[1]));
        }
        else
        {

            alert.setText("请以 楼号#宿舍号 格式输入！");
            alert.exec();
            context->clear();
        }
    }
}

void Widget::createDialog()
{
    int inputNum = 8;
    vector<string> shows;
    shows.push_back("学号");
    shows.push_back("密码");
    shows.push_back("姓名");
    shows.push_back("性别");
    shows.push_back("专业");
    shows.push_back("宿舍楼号");
    shows.push_back("宿舍号");
    addPerson2 = new Dialog(inputNum,shows);
    shows.clear();
    shows.push_back("宿舍楼号");
    shows.push_back("宿舍号");
    shows.push_back("宿舍电话");
    addDorm2 = new Dialog(inputNum,shows);
    shows.clear();
    inputNum = 0;
    shows.push_back("财产名");
    query.exec("select 财产名 from 财产");
    while(query.next())
    {
        inputNum++;
        shows.push_back(query.value(0).toString().toStdString());
    }
    shows.push_back("备注");
    addReapir2 = new Dialog(inputNum, shows);
    shows.clear();
    shows.push_back("收件人");
    shows.push_back("宿舍楼号");
    shows.push_back("宿舍号");
    addMail2 = new Dialog(inputNum, shows);
    shows.clear();
    shows.push_back("学号");
    shows.push_back("晚归原因");
    addLate2 = new Dialog(inputNum, shows);
    shows.clear();
    shows.push_back("学号");
    shows.push_back("离校时间");
    shows.push_back("预计归校时间");
    shows.push_back("离校原因");
    addLeave2 = new Dialog(inputNum, shows);
}

void Widget::createShowWidget()
{
    for(int i=0; i<7; i++)
    {
        showResults[i] = new TableView(this);
        installEventFilter(showResults[i]);
        widget->addTab(showResults[i], name[i]);
    }
}

void Widget::login_success(QString _username, QString _password, Identify _id)
{
    login->hide();
    show();
    showName->setText(_username);
    createShowWidget();
    if(_id == Root)
    {
        showResults[7] = new TableView(this);
        installEventFilter(showResults[7]);
        widget->addTab(showResults[7], name[7]);
        showResults[8] = new TableView(this);
        installEventFilter(showResults[8]);
        widget->addTab(showResults[8], name[8]);
    }
    else
    {
        query.prepare("select 宿舍楼号,宿舍号 from 学生 where 学号=?");
        query.addBindValue(_username);
        query.exec();
        query.next();
        sushelou = query.value(0).toInt();
        sushe = query.value(1).toInt();
    }
    username = _username;
    password = _password;
    id = _id;
    widget->setCurrentIndex(0);
    showChanged(0);
    for(int i=0; i<7; i++)
        initShow(i);
    if(id == Root)
    {
        initShow(7);
        initShow(8);
    }
}

void Widget::logout_success()
{
    id = Empty;
    widget->clear();
    chooseFile->hide();
    addReapir->hide();
    repairComplete->hide();
    addMail->hide();
    getMail->hide();
    addLate->hide();
    addLeave->hide();
    backSchool->hide();
    deleteInfor->hide();
    addPerson2->hide();
    addDorm2->hide();
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
    {
        if(ope_aim == RepairRecord)
        {
            addReapir->show();
            deleteInfor->show();
        }
        else
        {
            addReapir->hide();
            deleteInfor->hide();
        }
    }
    else if(id == Root)
    {
        if(ope_aim == RepairRecord)
        {
            repairComplete->show();
            addMail->hide();
            getMail->hide();
            addLate->hide();
            addLeave->hide();
            backSchool->hide();
            deleteInfor->hide();
        }
        else if(ope_aim == ReceiveRecord)
        {
            repairComplete->hide();
            addMail->show();
            getMail->show();
            addLate->hide();
            addLeave->hide();
            backSchool->hide();
            deleteInfor->show();
        }
        else if(ope_aim == LateRecord)
        {
            repairComplete->hide();
            addMail->hide();
            getMail->hide();
            addLate->show();
            addLeave->hide();
            backSchool->hide();
            deleteInfor->show();
        }
        else if(ope_aim == LeaveRecord)
        {
            repairComplete->hide();
            addMail->hide();
            getMail->hide();
            addLate->hide();
            addLeave->show();
            backSchool->show();
            deleteInfor->show();
        }
        else
        {
            repairComplete->hide();
            addMail->hide();
            getMail->hide();
            addLate->hide();
            addLeave->hide();
            backSchool->hide();
            deleteInfor->hide();
        }
        if(ope_aim == UserInfor || ope_aim == DormInfor)
        {
            chooseFile->show();
            deleteInfor->show();
            if(ope_aim == UserInfor)
                addPerson->show();
            else
                addDorm->show();
        }
        else
        {
            chooseFile->hide();
            addPerson->hide();
            addDorm->hide();
        }
    }
    if(id == User)
    {
        choose->hide();
        start->hide();
        context->hide();
    }
    else
    {
        choose->show();
        choose->clear();
        start->show();
        context->show();
        ope_aim = (Ope_aim)index;
        switch(ope_aim)
        {
            case RepairRecord:
                choose->addItem("宿舍");
                choose->addItem("报修日期");
                break;
            case RepairHistory:
                choose->addItem("宿舍");
                choose->addItem("报修日期");
                break;
            case ReceiveRecord:
                choose->addItem("信件编号");
                choose->addItem("收件人");
                choose->addItem("到达时间");
                choose->addItem("宿舍");
                break;
            case ReceiveHistory:
                choose->addItem("信件编号");
                choose->addItem("收件人");
                choose->addItem("到达时间");
                choose->addItem("收取时间");
                choose->addItem("宿舍");
                break;
            case LateRecord:
                choose->addItem("宿舍");
                choose->addItem("学号");
                choose->addItem("晚归日期");
                break;
            case LeaveRecord:
                choose->addItem("宿舍");
                choose->addItem("学号");
                choose->addItem("离校时间");
                break;
            case LeaveHistory:
                choose->addItem("宿舍");
                choose->addItem("学号");
                choose->addItem("离校时间");
                choose->addItem("归校时间");

                break;
            case UserInfor:
                choose->addItem("宿舍");
                choose->addItem("学号");
                break;
            case DormInfor:
                choose->addItem("宿舍");
                choose->addItem("楼号");
                break;
            default:
                break;
        }
    }
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

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}

void Widget::initShow(int index)
{
    QString add[3] = {QString(""), QString(" and 宿舍楼号=%1 and 宿舍号=%2").arg(sushelou).arg(sushe), QString("")};
    QString fulladd[3] = {QString(""), QString(" where 宿舍楼号=%1 and 宿舍号=%2").arg(sushelou).arg(sushe), QString("")};
    QString personadd[3] = {QString(""), QString(" where 学号=%1").arg(username), QString("")};
    if(id == Empty)
        return;
    if(index == -1)
        index = ope_aim;
    if(index == UserInfor)
        model[index].setQuery(QString("select 学号,姓名,宿舍楼号,宿舍号 from %1").arg(name[index]));
    else if(index == RepairRecord)
        model[index].setQuery(QString("select 财产名,宿舍楼号,宿舍号,报修日期,备注 from 财产,维修 where 财产.财产号=维修.财产号")+add[id]);
    else if(index == RepairHistory)
        model[index].setQuery(QString("select 财产名,宿舍楼号,宿舍号,报修日期,维修日期,备注 from 财产,维修记录 where 财产.财产号=维修记录.财产号")+add[id]);
    else if(index == LateRecord || index == LeaveRecord || index == LeaveHistory)
        model[index].setQuery(QString("select * from %1").arg(name[index])+personadd[id]);
    else
        model[index].setQuery(QString("select * from %1").arg(name[index])+fulladd[id]);
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

bool Widget::addRepair3(QList<QString> infor)
{
    query.prepare("select 财产号 from 财产 where 财产名=?");
    query.addBindValue(infor.at(0));
    query.exec();
    query.next();
    int id1 = query.value(0).toInt();
    query.exec(QString("select * from 维修 where 财产号=%1 and 宿舍楼号=%2 and 宿舍号=%3").arg(id1).arg(sushelou).arg(sushe));
    if(query.next())
    {
        QMessageBox::warning(this, "申报失败", "已有该维修记录");
        return false;
    }
    query.prepare("insert into 维修 values(?, ?, ?, ?, ?)");
    query.addBindValue(id1);
    query.addBindValue(sushelou);
    query.addBindValue(sushe);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(infor.at(1));
    query.exec();
    initShow();
    QMessageBox::warning(this, "申报成功", "请耐心等待");
    return true;
}

bool Widget::repairComplete2()
{
    int row = showResults[ope_aim]->table->currentIndex().row();
    if(row == -1)
    {
        QMessageBox::warning(this, "操作失败", "请选中行");
        return false;
    }
    QList<QString> list = showResults[ope_aim]->getOneRow(row);
    query.prepare("select 财产号 from 财产 where 财产名=?");
    query.addBindValue(list.at(0));
    query.exec();
    query.next();
    int id1 = query.value(0).toInt();
    query.exec(QString("delete from 维修 where 财产号=%1 and 宿舍楼号=%2 and 宿舍号=%3")
               .arg(id1).arg(list.at(1)).arg(list.at(2)));
    query.exec(QString("insert into 维修记录 values(%1, %2, %3, '%4', '%5', '%6')")
               .arg(id1).arg(list.at(1)).arg(list.at(2)).arg(list.at(3))
               .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(list.at(4)));
    initShow();
    initShow(RepairHistory);
    QMessageBox::warning(this, "操作成功", "维修已记录");
    return true;
}

bool Widget::addMail3(QList<QString> infor)
{
    query.prepare("select 宿舍楼号,宿舍号 from 学生 where 姓名=?");
    query.addBindValue(infor.at(0));
    query.exec();
    bool ok = false;
    while(query.next())
    {
        sushelou = query.value(0).toInt();
        sushe = query.value(1).toInt();
        if(infor.at(1).toInt() == sushelou && infor.at(2).toInt() == sushe)
        {
            ok = true;
            break;
        }
    }
    if(!ok)
    {
        QMessageBox::warning(this, "操作失败", "收件人信息有误，请检查");
        return false;
    }
    query.prepare("insert into 信件(收件人,到达时间,宿舍楼号,宿舍号) values(?, ?, ?, ?)");
    query.addBindValue(infor.at(0));
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(sushelou);
    query.addBindValue(sushe);
    query.exec();
    initShow();
    QMessageBox::warning(this, "操作成功", "成功添加信件");
    return true;
}

bool Widget::getMail2()
{
    int row = showResults[ope_aim]->table->currentIndex().row();
    if(row == -1)
    {
        QMessageBox::warning(this, "操作失败", "请选中行");
        return false;
    }
    QList<QString> list = showResults[ope_aim]->getOneRow(row);
    query.exec(QString("delete from 信件 where 信件编号=%1").arg(list.at(0)));
    query.prepare("insert into 收信记录 values(?, ?, ?, ?, ?, ?)");
    query.addBindValue(list.at(0));
    query.addBindValue(list.at(1));
    QString arriveTime = list.at(2);
    arriveTime[10] = ' ';
    query.addBindValue(arriveTime);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(list.at(3));
    query.addBindValue(list.at(4));
    query.exec();
    initShow();
    initShow(ReceiveHistory);
    QMessageBox::warning(this, "操作成功", "发放信件成功");
    return true;
}

bool Widget::addLate3(QList<QString> infor)
{
    query.prepare("select * from 学生 where 学号=?");
    query.addBindValue(infor.at(0));
    query.exec();
    if(!query.next())
    {
        QMessageBox::warning(this, "操作失败", "该学号不存在,请检查");
        return false;
    }
    query.prepare("insert into 晚归 values(?, ?, ?)");
    query.addBindValue(infor.at(0));
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(infor.at(1));
    query.exec();
    initShow();
    QMessageBox::warning(this, "操作成功", "成功添加晚归记录");
    return true;
}

bool Widget::addLeave3(QList<QString> infor)
{
    query.prepare("select * from 学生 where 学号=?");
    query.addBindValue(infor.at(0));
    query.exec();
    if(!query.next())
    {
        QMessageBox::warning(this, "操作失败", "该学号不存在,请检查");
        return false;
    }
    query.prepare("insert into 离校 values(?, ?, ?, ?)");
    query.addBindValue(infor.at(0));
    query.addBindValue(infor.at(1));
    query.addBindValue(infor.at(2));
    query.addBindValue(infor.at(3));
    query.exec();
    initShow();
    QMessageBox::warning(this, "操作成功", "成功添加离校记录");
    return true;
}

bool Widget::backSchool2()
{
    int row = showResults[ope_aim]->table->currentIndex().row();
    if(row == -1)
    {
        QMessageBox::warning(this, "操作失败", "请选中行");
        return false;
    }
    QList<QString> list = showResults[ope_aim]->getOneRow(row);
    query.prepare("delete from 离校 where 学号=? and 离校时间=?");
    query.addBindValue(list.at(0));
    query.addBindValue(list.at(1));
    query.exec();
    query.prepare("insert into 离校记录 values(?, ?, ?, ?, ?)");
    query.addBindValue(list.at(0));
    QString leaveTime = list.at(1);
    leaveTime[10] = ' ';
    query.addBindValue(leaveTime);
    QString backTime = list.at(2);
    backTime[10] = ' ';
    query.addBindValue(backTime);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:ss:mm"));
    query.addBindValue(list.at(3));
    query.exec();
    initShow();
    initShow(LeaveHistory);
    QMessageBox::warning(this, "操作成功", "成功确认返校");
    return true;
}

bool Widget::deleteInfor2()
{
    int row = showResults[ope_aim]->table->currentIndex().row();
    if(row == -1)
    {
        QMessageBox::warning(this, "操作失败", "请选中行");
        return false;
    }
    QList<QString> list = showResults[ope_aim]->getOneRow(row);
    QString aim = QString("delete from %1 where ").arg(name[ope_aim]);
    for(int i=0; i<(int)list.size(); i++)
    {
        aim += QString("%1=?").arg(infor[ope_aim][i]);
        if(i != (int)list.size()-1)
            aim += QString(" and ");
    }
    int id1;
    for(int i=0; i<(int)list.size(); i++)
    {
        if(infor[ope_aim][i].contains("财产号"))
        {
            query.prepare("select 财产号 from 财产 where 财产名=?");
            query.addBindValue(list.at(i));
            query.exec();
            query.next();
            id1 = query.value(0).toInt();
        }
    }
    query.prepare(aim);
    for(int i=0; i<(int)list.size(); i++)
    {
        QString need = list.at(i);
        if(infor[ope_aim][i].contains("时间") || infor[ope_aim][i].contains("日期"))
            need[10] = ' ';
        else if(infor[ope_aim][i].contains("财产号"))
            need = QString::number(id1);
        query.addBindValue(need);
    }
    query.exec();
    initShow();
    QMessageBox::warning(this, "删除成功", "成功删除该数据");
    return true;
}

bool Widget::addPerson3(QList<QString> infor)
{
    if(infor.at(0).toInt() <= 0)
    {
        QMessageBox::warning(this, "操作失败", "学号不合法");
        return false;
    }
    sushelou = infor.at(5).toInt();
    sushe = infor.at(6).toInt();
    query.exec(QString("select * from 宿舍 where 宿舍楼号=%1 and 宿舍号=%2").arg(sushelou).arg(sushe));
    if(!query.next())
    {
        QMessageBox::warning(this, "操作失败", "宿舍号不存在");
        return false;
    }
    query.prepare("select * from 学生 where 学号=?");
    query.addBindValue(infor.at(0));
    query.exec();
    if(query.next())
    {
        QMessageBox::warning(this, "操作失败", "该学号已存在");
        return false;
    }
    query.prepare("insert into 学生 values(?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(infor.at(0));
    query.addBindValue(infor.at(1));
    query.addBindValue(infor.at(2));
    query.addBindValue(infor.at(3));
    query.addBindValue(infor.at(4));
    query.addBindValue(infor.at(5));
    query.addBindValue(infor.at(6));
    query.exec();
    initShow();
    QMessageBox::warning(this, "操作成功", "成功添加学生");
    return true;
}

bool Widget::addDorm3(QList<QString> infor)
{
    if(infor.at(2).toInt() <= 0 || infor.at(0).toInt() <= 0 || infor.at(1).toInt() <= 0)
    {
        QMessageBox::warning(this, "操作失败", "宿舍信息不合法");
        return false;
    }
    sushelou = infor.at(0).toInt();
    sushe = infor.at(1).toInt();
    query.exec(QString("select * from 宿舍 where 宿舍楼号=%1 and 宿舍号=%2").arg(sushelou).arg(sushe));
    if(query.next())
    {
        QMessageBox::warning(this, "操作失败", "宿舍号已存在");
        return false;
    }
    query.prepare("insert into 宿舍 values(?, ?, ?)");
    query.addBindValue(infor.at(0));
    query.addBindValue(infor.at(1));
    query.addBindValue(infor.at(2));
    query.exec();
    initShow();
    QMessageBox::warning(this, "操作成功", "成功添加宿舍");
    return true;
}

void Widget::changePassword()
{
    if(id == Root)
        return;
    QString newPassword = QInputDialog::getText(this, "请输入新的密码", "新密码");
    if(!newPassword.isEmpty())
    {
        query.prepare("update 学生 set 密码=? where 学号=?");
        query.addBindValue(newPassword);
        query.addBindValue(username);
        query.exec();
        alert.setText("成功修改密码");
        alert.exec();
    }
}

Widget::~Widget()
{
}
