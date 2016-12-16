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
    QTableView * table;
    PageWidget * page;

protected:
    void resizeEvent(QResizeEvent * event);
};

#endif // TABLEVIEW_H
