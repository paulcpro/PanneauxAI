#include "histogrammewindow.h"
#include "ui_histogrammewindow.h"

histogrammeWindow::histogrammeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::histogrammeWindow)
{
    ui->setupUi(this);

    setFixedSize(800,450);


}

histogrammeWindow::~histogrammeWindow()
{
    delete ui;
}

void histogrammeWindow::on_pushButton_clicked()
{
    close();
}
