#include "tableview.h"
#include <QMessageBox>
#include <QEvent>
#include <QDebug>

TableView::TableView(QWidget *parent) : QWidget(parent), table(new QTableView(this)), page(new PageWidget(3, this))
{
    connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showInfor(QModelIndex)));
}

TableView::TableView(TableView *tableview) : table(tableview->table), page(tableview->page)
{
}

QList<QString> TableView::getOneRow(int row)
{
    QList<QString> list;
    for(int i=0; i<table->model()->columnCount(); i++)
        list << table->model()->data(table->model()->index(row, i)).toString();
    return list;
}

void TableView::resizeEvent(QResizeEvent *event)
{
    table->setGeometry(0, 0, width(), height()-20);
    page->setGeometry(0, height()-20, width(), 20);

    QWidget::resizeEvent(event);
}

void TableView::showInfor(QModelIndex index)
{
    QMessageBox::warning(0, "信息", this->table->model()->data(index).toString());
}

