#include "widget.h"
#include "connect_database.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!connect_mysql())
    {
        QMessageBox::warning(0, "打开数据库失败", "请尝试重启以及检查数据库连接");
        exit(0);
    }
    Widget w;

    return a.exec();
}
