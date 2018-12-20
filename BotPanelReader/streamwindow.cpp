#include "streamwindow.h"
#include "ui_streamwindow.h"

streamWindow::streamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::streamWindow)
{
    ui->setupUi(this);
    setFixedSize(800,600);
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
    if(video.isOpened()) {
    QMessageBox::warning(this, "Warning", "Stop the video before closing the application!");
    event->ignore();
    } else {
    event->accept();
    }
}


void streamWindow::on_pushButton_pressed()
{
    using namespace cv;
    bool isCamera;
    int cameraIndex = ui->lineEdit->text().toInt(&isCamera);

    if(video.isOpened()) {
        ui->pushButton->setText("Start");
        video.release();
        return;
    }

    if(isCamera) {
        if(!video.open(cameraIndex)) {
            QMessageBox::critical(this,
                                  "Camera Error",
                                  "Make sure you entered a correct camera index,"
                                  "<br>or that the camera is not being accessed by another program!");
            return;
        }
    } else {
        if(!video.open(ui->lineEdit->text().trimmed().toStdString())) {
            QMessageBox::critical(this,
                                  "Video Error",
                                  "Make sure you entered a correct and supported video file path,"
                                  "<br>or a correct RTSP feed URL!");
            return;
        }
    }

    ui->pushButton->setText("Stop");

    Mat frame;
    while(video.isOpened()) {
        video >> frame;
        if(!frame.empty()) {
            copyMakeBorder(frame,
                           frame,
                           frame.rows/2,
                           frame.rows/2,
                           frame.cols/2,
                           frame.cols/2,
                           BORDER_REFLECT);

            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
        }
        qApp->processEvents();
    }

    ui->pushButton->setText("Start");
}
