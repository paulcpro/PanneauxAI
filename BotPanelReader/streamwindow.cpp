#include "streamwindow.h"
#include "ui_streamwindow.h"


streamWindow::streamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::streamWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);
}

streamWindow::~streamWindow()
{
    delete ui;
}

void streamWindow::on_pushButton_3_clicked()
{
    close();
}

void streamWindow::closeEvent(QCloseEvent *event)
{
    if(video.isOpened())
    {
    QMessageBox::warning(this, "Warning", "Stop the video before closing the application!");
    event->ignore();
    } else {
    event->accept();
    }
}
