#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <opencv2\opencv.hpp>
#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->ui->setupUi(this);
    this->ui->graphicsView->setScene(new QGraphicsScene(this));
    this->ui->graphicsView->scene()->addItem(&pixmap);
}

/*
Dialog::~Dialog()
{
    delete ui;
}
*/

void Dialog::closeEvent(QCloseEvent *event)
{
    /*
if(video.isOpened())
{

QMessageBox::warning(this, "Warning", "Stop the video before closing the application!");

event->ignore();
}
else
{
event->accept();
}
*/

}
