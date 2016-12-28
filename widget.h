#ifndef WIDGET_H
#define WIDGET_H

#include "login.h"
#include "tableview.h"
#include "dialog.h"

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTabWidget>
#include <QCheckBox>
#include <QSqlQueryModel>
#include <QSqlQuery>

enum Ope_aim {
    RepairRecord, RepairHistory, ReceiveRecord,
    ReceiveHistory, LateRecord, LeaveRecord, LeaveHistory, UserInfor, DormInfor
};

const QString name[9] = {
    "维修", "维修记录", "信件", "收信记录", "晚归", "离校", "离校记录", "学生", "宿舍"
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void createShowWidget();
    ~Widget();

protected:
    void paintEvent(QPaintEvent * event);

protected slots:
    void login_success(QString _username, QString _password, Identify _id);
    void logout_success();
    void showChanged(int index);
    void initShow(int index = -1);
    void inputFromFile();

private:
    QComboBox * choose;        //选择查询目标
    QLineEdit * context;       //查询内容
    QPushButton * start;       //开始查询
    QPushButton * showName;    //显示帐号名称
    QPushButton * logout;         //注销
    Login * login;                  //登陆界面

    TableView * showResults[9];    //显示查询图书结果,借阅记录,用户列表
    QSqlQueryModel model[9];
    QTabWidget * widget;         //显示管理员界面

    QCheckBox * checkbox;            //是否从当前结果继续查询
    QPushButton * resetButton;       //重置按钮
    QPushButton * addPerson;         //增加用户
    QPushButton * delPerson;         //删除用户
    QPushButton * chooseFile;        //从文件导入学生信息
    QPushButton * chooseFile2;       //从文件导入宿舍信息
    QPushButton * addReapir;         //增加

    Dialog * addUser;                //输入添加的用户的信息

    QString username;
    QString password;
    Identify id;

    Ope_aim ope_aim;
    QSqlQuery query;
};

#endif // WIDGET_H
