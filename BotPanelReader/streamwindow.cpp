#include "streamwindow.h"
#include "ui_streamwindow.h"

streamWindow::streamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::streamWindow)
{
    QLabel *label = new QLabel(this);
    QPixmap pixmapImg("C:/2.jpg");
    label->setPixmap(pixmapImg);
    label->resize(pixmapImg.size());

    ui->setupUi(this);

    setWindowIcon(QIcon("C:/Cours/Projet BotPanelReader/icon.png"));
    setFixedSize(800 , 450);

    //Bouton fermer
    this->ui->pushButton_3->setGeometry(550, 387 , 150, 40);

    //Bouton Stream
    this->ui->pushButton->setGeometry(550, 70, 150, 40);

    //Label port
    this->ui->label->setGeometry(30, 40, 50, 30);

    //Entrée du port
    this->ui->lineEdit->setGeometry(65, 47, 75, 15);

    //Graphic View
    this->ui->graphicsView->setGeometry(30, 70, 500, 379);

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

    //Si la vidéo commence à stream
    if(video.isOpened()) {
        ui->pushButton->setText("Start");

        //Ferme la capture de la vidéo
        video.release();
        return;
    }

    if(isCamera) {
        //Vérifie si le port entré contient la cam
        if(!video.open(cameraIndex)) {
            QMessageBox::critical(this,
                                  "Camera Error",
                                  "Make sure you entered a correct camera index,"
                                  "<br>or that the camera is not being accessed by another program!");
            return;
        }
    } else {
        //Vérifie si la vidéo peut etre lu
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

    //tant que la vidéo stream
    while(video.isOpened()) {
        //On affiche chaque image
        video >> frame;
        if(!frame.empty()) {
            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);

            //Faire un QMessageBox pour afficher les infos des frames


            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
        }
        qApp->processEvents();
    }

    ui->pushButton->setText("Start");
}
