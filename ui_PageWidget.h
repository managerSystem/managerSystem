/********************************************************************************
** Form generated from reading UI file 'PageWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEWIDGET_H
#define UI_PAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *previousPageLabel;
    QWidget *leftPagesWidget;
    QLabel *leftSeparateLabel;
    QWidget *centerPagesWidget;
    QLabel *rightSeparateLabel;
    QWidget *rightPagesWidget;
    QLabel *nextPageLabel;
    QLabel *label;
    QLineEdit *pageLineEdit;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PageWidget)
    {
        if (PageWidget->objectName().isEmpty())
            PageWidget->setObjectName(QStringLiteral("PageWidget"));
        PageWidget->resize(309, 23);
        PageWidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(PageWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        previousPageLabel = new QLabel(PageWidget);
        previousPageLabel->setObjectName(QStringLiteral("previousPageLabel"));

        horizontalLayout->addWidget(previousPageLabel);

        leftPagesWidget = new QWidget(PageWidget);
        leftPagesWidget->setObjectName(QStringLiteral("leftPagesWidget"));

        horizontalLayout->addWidget(leftPagesWidget);

        leftSeparateLabel = new QLabel(PageWidget);
        leftSeparateLabel->setObjectName(QStringLiteral("leftSeparateLabel"));

        horizontalLayout->addWidget(leftSeparateLabel);

        centerPagesWidget = new QWidget(PageWidget);
        centerPagesWidget->setObjectName(QStringLiteral("centerPagesWidget"));

        horizontalLayout->addWidget(centerPagesWidget);

        rightSeparateLabel = new QLabel(PageWidget);
        rightSeparateLabel->setObjectName(QStringLiteral("rightSeparateLabel"));

        horizontalLayout->addWidget(rightSeparateLabel);

        rightPagesWidget = new QWidget(PageWidget);
        rightPagesWidget->setObjectName(QStringLiteral("rightPagesWidget"));

        horizontalLayout->addWidget(rightPagesWidget);

        nextPageLabel = new QLabel(PageWidget);
        nextPageLabel->setObjectName(QStringLiteral("nextPageLabel"));

        horizontalLayout->addWidget(nextPageLabel);

        label = new QLabel(PageWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        pageLineEdit = new QLineEdit(PageWidget);
        pageLineEdit->setObjectName(QStringLiteral("pageLineEdit"));
        pageLineEdit->setMinimumSize(QSize(50, 0));
        pageLineEdit->setMaximumSize(QSize(50, 16777215));
        pageLineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(pageLineEdit);

        label_2 = new QLabel(PageWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(45, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(PageWidget);

        QMetaObject::connectSlotsByName(PageWidget);
    } // setupUi

    void retranslateUi(QWidget *PageWidget)
    {
        PageWidget->setWindowTitle(QApplication::translate("PageWidget", "Form", 0));
#ifndef QT_NO_TOOLTIP
        previousPageLabel->setToolTip(QApplication::translate("PageWidget", "\344\270\212\344\270\200\351\241\265", 0));
#endif // QT_NO_TOOLTIP
        previousPageLabel->setText(QApplication::translate("PageWidget", "<<", 0));
#ifndef QT_NO_TOOLTIP
        leftSeparateLabel->setToolTip(QApplication::translate("PageWidget", "\344\270\213\344\270\200\351\241\265", 0));
#endif // QT_NO_TOOLTIP
        leftSeparateLabel->setText(QApplication::translate("PageWidget", "..", 0));
#ifndef QT_NO_TOOLTIP
        rightSeparateLabel->setToolTip(QApplication::translate("PageWidget", "\344\270\213\344\270\200\351\241\265", 0));
#endif // QT_NO_TOOLTIP
        rightSeparateLabel->setText(QApplication::translate("PageWidget", "..", 0));
#ifndef QT_NO_TOOLTIP
        nextPageLabel->setToolTip(QApplication::translate("PageWidget", "\344\270\213\344\270\200\351\241\265", 0));
#endif // QT_NO_TOOLTIP
        nextPageLabel->setText(QApplication::translate("PageWidget", ">>", 0));
        label->setText(QApplication::translate("PageWidget", "\347\254\254", 0));
        label_2->setText(QApplication::translate("PageWidget", "\351\241\265", 0));
    } // retranslateUi

};

namespace Ui {
    class PageWidget: public Ui_PageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEWIDGET_H
