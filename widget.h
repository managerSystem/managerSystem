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
#include <QMessageBox>

enum Ope_aim {
    RepairRecord, RepairHistory, ReceiveRecord,
    ReceiveHistory, LateRecord, LeaveRecord, LeaveHistory, UserInfor, DormInfor
};

const QString name[9] = {
    "维修", "维修记录", "信件", "收信记录", "晚归", "离校", "离校记录", "学生", "宿舍"
};

const QString infor[9][6] = {
    {"财产号","宿舍楼号","宿舍号","报修日期","备注"},
    {},
    {"信件编号","收件人","到达时间","宿舍楼号","宿舍号"},
    {},
    {"学号","晚归日期","晚归原因"},
    {"学号","离校时间","预计归校时间","离校原因"},
    {},
    {"学号","姓名","宿舍楼号","宿舍号"},
    {"宿舍楼号","宿舍号","宿舍电话"}
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void createDialog();
    void createShowWidget();
    ~Widget();

protected:
    void paintEvent(QPaintEvent * event);
    bool eventFilter( QObject * watched, QEvent * event );

protected slots:
    void login_success(QString _username, QString _password, Identify _id);
    void logout_success();
    void showChanged(int index);
    void initShow(int index = -1);
    void inputFromFile();
    bool addRepair3(QList<QString> infor);
    bool repairComplete2();
    bool addMail3(QList<QString> infor);
    bool getMail2();
    bool addLate3(QList<QString> infor);
    bool addLeave3(QList<QString> infor);
    bool backSchool2();
    bool deleteInfor2();
    bool addPerson3(QList<QString> infor);
    bool addDorm3(QList<QString> infor);
    void showSearch();
    void reset();
    void changeReg();
    void changePassword();

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
    QPushButton * addDorm;
    QPushButton * chooseFile;        //从文件导入学生信息
    QPushButton * chooseFile2;       //从文件导入宿舍信息
    QPushButton * addReapir;         //增加维修
    QPushButton * repairComplete;    //维修完成
    QPushButton * addMail;           //增加信件
    QPushButton * getMail;           //领取信件
    QPushButton * addLate;           //添加晚归记录
    QPushButton * addLeave;          //添加离校记录
    QPushButton * backSchool;        //返校
    QPushButton * deleteInfor;       //删除信息

    Dialog * addPerson2;            //输入添加的用户的信息
    Dialog * addDorm2;               //输入添加的宿舍的信息
    Dialog * addReapir2;             //输入维修信息
    Dialog * addMail2;               //输入信件信息
    Dialog * addLate2;               //输入晚归信息
    Dialog * addLeave2;              //输入离校信息

    QString username;
    QString password;
    Identify id;
    int sushelou;
    int sushe;

    Ope_aim ope_aim;
    QSqlQuery query;
    QMessageBox alert;               //输入错误时弹窗警告
};

#endif // WIDGET_H
