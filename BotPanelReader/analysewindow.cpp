#include "analysewindow.h"
#include "ui_analysewindow.h"
#include <histogrammewindow.h>
#include "mainwindow.h"
#include <QFileDialog>

analyseWindow::analyseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyseWindow)
{
    ui->setupUi(this);

    setFixedSize(800,450);


}

analyseWindow::~analyseWindow()
{
    delete ui;
}

void analyseWindow::on_pushButton_3_clicked()
{
    histogrammeWindow *f = new histogrammeWindow();
    f->show();
}

void analyseWindow::on_pushButton_2_clicked()
{
    close();
}

void analyseWindow::on_pushButton_4_clicked()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
}
