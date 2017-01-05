#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "pagewidget.h"

#include <QWidget>
#include <QTableView>

class TableView : public QWidget
{
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = 0);
    TableView(TableView * tableview);
    QList<QString> getOneRow(int row);
    QTableView * table;
    PageWidget * page;

protected:
    void resizeEvent(QResizeEvent * event);

protected slots:
    void showInfor(QModelIndex index);
};

#endif // TABLEVIEW_H
