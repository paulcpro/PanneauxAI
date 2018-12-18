/********************************************************************************
** Form generated from reading UI file 'streamwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAMWINDOW_H
#define UI_STREAMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_streamWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *streamWindow)
    {
        if (streamWindow->objectName().isEmpty())
            streamWindow->setObjectName(QStringLiteral("streamWindow"));
        streamWindow->resize(800, 600);
        centralwidget = new QWidget(streamWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(130, 130, 501, 351));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 100, 61, 21));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(160, 100, 113, 20));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(650, 140, 71, 31));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(650, 190, 71, 31));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(650, 450, 71, 31));
        streamWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(streamWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        streamWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(streamWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        streamWindow->setStatusBar(statusbar);

        retranslateUi(streamWindow);

        QMetaObject::connectSlotsByName(streamWindow);
    } // setupUi

    void retranslateUi(QMainWindow *streamWindow)
    {
        streamWindow->setWindowTitle(QApplication::translate("streamWindow", "BotPanelReader - Stream Window", Q_NULLPTR));
        label->setText(QApplication::translate("streamWindow", "Port :", Q_NULLPTR));
        pushButton->setText(QApplication::translate("streamWindow", "Stream", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("streamWindow", "Capturer", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("streamWindow", "Fermer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class streamWindow: public Ui_streamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAMWINDOW_H
