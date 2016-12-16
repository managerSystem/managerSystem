#include "tableview.h"

TableView::TableView(QWidget *parent) : QWidget(parent), table(new QTableView(this)), page(new PageWidget(3, this))
{
}

TableView::TableView(TableView *tableview) : table(tableview->table), page(tableview->page)
{
}

void TableView::resizeEvent(QResizeEvent *event)
{
    table->setGeometry(0, 0, width(), height()-20);
    page->setGeometry(0, height()-20, width(), 20);

    QWidget::resizeEvent(event);
}

