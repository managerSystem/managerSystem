#include "dialog.h"

#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(int inputNum,vector<string> shows) :inputNum(inputNum), shows(shows)
{
    setMaximumSize(300, shows.size()*50+30);
    setMinimumSize(300, shows.size()*50+30);

    labels = new QLabel*[(int)shows.size()];
    lineedits = new QLineEdit*[(int)shows.size()];
    ok = false;
    for(int i=0; i<(int)shows.size(); i++)
    {
        labels[i] = new QLabel(QString::fromStdString(shows[i]),this);
        labels[i]->setGeometry(10,10+(i-(ok>0)*inputNum)*50,60,30);
        if(shows[i] == "性别")
        {
            sex = new QComboBox(this);
            sex->addItem("男");
            sex->addItem("女");
            sex->setGeometry(90, 10+(i-(ok>0)*inputNum)*50, 200, 30);
            continue;
        }
        else if(shows[i] == "生日")
        {
            birth = new QDateEdit(this);
            birth->setGeometry(90, 10+(i-(ok>0)*inputNum)*50, 200, 30);
            birth->setCalendarPopup(true);
            continue;
        }
        else if(shows[i] == "图书id" || shows[i] == "财产名")
        {
            bookId = new QComboBox(this);
            bookId->setGeometry(90, 10+i*50, 200, 30);
            for(int j=i+1;j<=i+inputNum;j++)
                bookId->addItem(QString::fromStdString(shows[j]));
            setMaximumSize(300, (shows.size()-inputNum)*50+30);
            setMinimumSize(300, (shows.size()-inputNum)*50+30);
            ok = i+1;
            i+=inputNum;
            continue;
        }
        lineedits[i] = new QLineEdit(this);
        lineedits[i]->setGeometry(90, 10+(i-(ok>0)*inputNum)*50, 200, 30);
    }

    confirm = new QPushButton("确定", this);
    confirm->setGeometry(25, (shows.size()-(ok>0)*inputNum)*50, 100, 20);
    cancel = new QPushButton("取消", this);
    cancel->setGeometry(175, (shows.size()-(ok>0)*inputNum)*50, 100, 20);

    connect(confirm,SIGNAL(clicked(bool)),this,SLOT(confirmSubmit()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void Dialog::confirmSubmit()
{
    QList<QString>list;
    int num = shows.size();
    if(ok)
        num-=inputNum;
    for(int i=0; i<num; i++)
    {
        if(shows[i+((i>=ok)&&ok)*inputNum] == "性别")
            list << sex->currentText();
        else if(shows[i+((i>=ok)&&ok)*inputNum] == "生日")
            list << birth->dateTime().toString("yyyy-MM-dd");
        else if(shows[i+((i>=ok)&&ok)*inputNum] == "离校时间" || shows[i+((i>=ok)&&ok)*inputNum] == "预计归校")
        {
            string aim = lineedits[i+((i>=ok)&&ok)*inputNum]->text().toStdString();
            bool ok3 = true;
            if(aim.length() != 19)
                ok3 = false;
            for(int j=0; j<19; j++)
            {
                if(j==4 || j==7)
                {
                    if(aim[j] != '-')
                        ok3 = false;
                }
                else if(j==13 || j==16)
                {
                    if(aim[j] != ':')
                        ok3 = false;
                }
                else if(j==10)
                {
                    if(aim[j] != ' ')
                        ok3 = false;
                }
                else if(aim[j]>'9' || aim[j]<'0')
                    ok3 = false;
                if(!ok3)
                    break;
            }
            if(ok3)
            {
                int y=(aim[0]-'0')*1000+(aim[1]-'0')*100+(aim[2]-'0')*10+aim[3]-'0';
                int M=(aim[5]-'0')*10+aim[6]-'0';
                int d=(aim[8]-'0')*10+aim[9]-'0';
                int h=(aim[11]-'0')*10+aim[12]-'0';
                int m=(aim[14]-'0')*10+aim[15]-'0';
                int s=(aim[17]-'0')*10+aim[18]-'0';
                if(!QDateTime(QDate(y,M,d),QTime(h,m,s)).isValid() || QDateTime(QDate(y,M,d), QTime(h,m,s)) < QDateTime::currentDateTime())
                    ok3 = false;
            }
            if(!ok3)
            {
                QMessageBox::warning(0, "操作失败", "DateTime类数据必须是'yyyy-MM-dd hh:mm:ss'的格式且必须合法");
                return;
            }
            else
                list << lineedits[i+((i>=ok)&&ok)*inputNum]->text();
        }
        else if(shows[i+((i>=ok)&&ok)*inputNum] == "图书id" || shows[i+((i>=ok)&&ok)*inputNum] == "财产名")
            list << bookId->currentText();
        else
            list << lineedits[i+((i>=ok)&&ok)*inputNum]->text();
        bool ok2 = true;
        for(int j=0; j<list.at(i).length(); j++)
            if(list.at(i)[j]!=' ')
                ok2 = false;
        if(ok2)
        {
            QMessageBox::warning(this,"操作失败",QString("%1不能为空且不能全为空格").arg(QString::fromStdString(shows[i+((i>=ok)&&ok)*inputNum])));
            return;
        }
    }
    emit submit(list);
    close();
}
