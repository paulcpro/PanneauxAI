#include "histogrammewindow.h"
#include "ui_histogrammewindow.h"

histogrammeWindow::histogrammeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::histogrammeWindow)
{
    ui->setupUi(this);
}

histogrammeWindow::~histogrammeWindow()
{
    delete ui;
}
