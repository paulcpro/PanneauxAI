/********************************************************************************
** Form generated from reading UI file 'analysewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSEWINDOW_H
#define UI_ANALYSEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_analyseWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *lImage;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QLabel *label_5;
    QLabel *lImage_3;
    QLabel *lImage_5;
    QLabel *label_7;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;

    void setupUi(QDialog *analyseWindow)
    {
        if (analyseWindow->objectName().isEmpty())
            analyseWindow->setObjectName(QStringLiteral("analyseWindow"));
        analyseWindow->resize(627, 555);
        label = new QLabel(analyseWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 141, 31));
        label_2 = new QLabel(analyseWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(340, 20, 131, 41));
        lImage = new QLabel(analyseWindow);
        lImage->setObjectName(QStringLiteral("lImage"));
        lImage->setGeometry(QRect(20, 60, 291, 181));
        label_4 = new QLabel(analyseWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(340, 60, 271, 171));
        pushButton_2 = new QPushButton(analyseWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 490, 111, 41));
        pushButton_4 = new QPushButton(analyseWindow);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(110, 490, 111, 41));
        label_5 = new QLabel(analyseWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 240, 131, 31));
        lImage_3 = new QLabel(analyseWindow);
        lImage_3->setObjectName(QStringLiteral("lImage_3"));
        lImage_3->setGeometry(QRect(30, 270, 261, 201));
        lImage_5 = new QLabel(analyseWindow);
        lImage_5->setObjectName(QStringLiteral("lImage_5"));
        lImage_5->setGeometry(QRect(320, 270, 281, 211));
        label_7 = new QLabel(analyseWindow);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(320, 240, 151, 31));
        checkBox = new QCheckBox(analyseWindow);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(470, 30, 101, 21));
        checkBox_2 = new QCheckBox(analyseWindow);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(170, 240, 91, 31));
        checkBox_3 = new QCheckBox(analyseWindow);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(480, 240, 101, 31));
        checkBox_4 = new QCheckBox(analyseWindow);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setGeometry(QRect(100, 30, 111, 17));

        retranslateUi(analyseWindow);

        QMetaObject::connectSlotsByName(analyseWindow);
    } // setupUi

    void retranslateUi(QDialog *analyseWindow)
    {
        analyseWindow->setWindowTitle(QApplication::translate("analyseWindow", "BotPanelReader - Analyse", Q_NULLPTR));
        label->setText(QApplication::translate("analyseWindow", "Image original :", Q_NULLPTR));
        label_2->setText(QApplication::translate("analyseWindow", "Image filtr\303\251 : Filtre rouge", Q_NULLPTR));
        lImage->setText(QApplication::translate("analyseWindow", "Image Original", Q_NULLPTR));
        label_4->setText(QApplication::translate("analyseWindow", "Image Filtr\303\251 Rouge", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("analyseWindow", "Fermer", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("analyseWindow", "Enregistrer", Q_NULLPTR));
        label_5->setText(QApplication::translate("analyseWindow", "Image original : Filtre noir", Q_NULLPTR));
        lImage_3->setText(QApplication::translate("analyseWindow", "Image Filtr\303\251 Noir", Q_NULLPTR));
        lImage_5->setText(QApplication::translate("analyseWindow", "Image Filtr\303\251 R\303\251sultat", Q_NULLPTR));
        label_7->setText(QApplication::translate("analyseWindow", "Image original : Filtre R\303\251sultat", Q_NULLPTR));
        checkBox->setText(QApplication::translate("analyseWindow", "Enregistrer", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("analyseWindow", "Enregistrer", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("analyseWindow", "Enregistrer", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("analyseWindow", "Tout S\303\251lectionner", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class analyseWindow: public Ui_analyseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSEWINDOW_H
