#include "dialog.h"

#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(int inputNum,vector<string> shows) :inputNum(inputNum), shows(shows)
{
    setMaximumSize(300, inputNum*50+30);
    setMinimumSize(300, inputNum*50+30);

    labels = new QLabel*[inputNum];
    lineedits = new QLineEdit*[inputNum];
    for(int i=0; i<inputNum; i++)
    {
        labels[i] = new QLabel(QString::fromStdString(shows[i]),this);
        labels[i]->setGeometry(10,10+i*50,60,30);
        if(shows[i] == "性别")
        {
            sex = new QComboBox(this);
            sex->addItem("男");
            sex->addItem("女");
            sex->setGeometry(90, 10+i*50, 200, 30);
            continue;
        }
        else if(shows[i] == "生日")
        {
            birth = new QDateEdit(this);
            birth->setGeometry(90, 10+i*50, 200, 30);
            birth->setCalendarPopup(true);
            continue;
        }
        lineedits[i] = new QLineEdit(this);
        lineedits[i]->setGeometry(90,10+i*50,200,30);
    }

    confirm = new QPushButton("确定", this);
    confirm->setGeometry(25, inputNum*50, 100, 20);
    cancel = new QPushButton("取消", this);
    cancel->setGeometry(175, inputNum*50, 100, 20);

    connect(confirm,SIGNAL(clicked(bool)),this,SLOT(confirmSubmit()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void Dialog::confirmSubmit()
{
    QList<QString>list;
    for(int i=0; i<inputNum; i++)
    {
        if(shows[i] == "性别")
            list << sex->currentText();
        else if(shows[i] == "生日")
            list << birth->dateTime().toString("yyyy-MM-dd");
        else
            list << lineedits[i]->text();
        if(list.at(i).isEmpty() || list.at(i).contains(" "))
        {
            QMessageBox::warning(this,"操作失败",QString("%1不能为空且不能含空格").arg(QString::fromStdString(shows[i])));
            return;
        }
    }
    emit submit(list);
    close();
}
