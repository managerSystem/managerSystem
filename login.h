#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSqlQuery>

enum Identify {
    Empty, User, Root
};

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget * parent = 0);
    ~Login();

protected:
    void mousePressEvent(QMouseEvent * event);

signals:
    void login_success(QString username, QString password, Identify id = User);

protected slots:
    void check();

private:
    QLabel * showname;
    QLabel * showpass;
    QLineEdit * username;
    QLineEdit * password;
    QPushButton * log;

    QSqlQuery query;
};

#endif // LOGIN_H
