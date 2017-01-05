#include "login.h"

#include <QMessageBox>
#include <QDate>
#include <QDebug>

Login::Login(QWidget * parent) : QWidget(parent), showname(new QLabel(this)), showpass(new QLabel(this)),
    username(new QLineEdit("admin",this)), password(new QLineEdit("admin",this)), log(new QPushButton(this))
{
    setWindowModality(Qt::ApplicationModal);

    setMaximumSize(400, 200);
    setMinimumSize(400, 200);

    showname->setGeometry(60, 40, 60, 30);
    showname->setText("帐号");

    username->setGeometry(150, 40, 180, 30);

    showpass->setGeometry(60, 90, 60, 30);
    showpass->setText("密码");

    password->setGeometry(150, 90, 180, 30);

    log->setGeometry(140, 150, 120, 30);
    log->setText("登录");
    connect(log, SIGNAL(clicked(bool)), this, SLOT(check()));
}

void Login::mousePressEvent(QMouseEvent *event)
{
    if(username->text() == "admin"){
    username->setText("140200321");
    password->setText("123456");}
    else
    {
        username->setText("admin");
        password->setText("admin");
    }
    QWidget::mousePressEvent(event);
}

void Login::check()
{
    query.prepare("select * from 学生 where 学号=? and 密码=?");
    query.addBindValue(username->text());
    query.addBindValue(password->text());
    query.exec();
    if(query.next())
        emit login_success(username->text(), password->text(), User);
    else
    {
        query.prepare("select * from 管理员 where 帐号=? and 密码=?");
        query.addBindValue(username->text());
        query.addBindValue(password->text());
        query.exec();
        if(query.next())
            emit login_success(username->text(), password->text(), Root);
        else
            QMessageBox::warning(this, "登录失败", "请检查帐号密码");
    }
}

Login::~Login()
{

}
