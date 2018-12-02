#include "mainwindow.h"
#include <analysewindow.h>
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include "QFileDialog"
#include "QMessageBox"

#include <opencv2\opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(800,450);

    /************* Menu Bar **************/
    QMenu *fichier = menuBar()->addMenu("&Fichier");
        QMenu *fichierRecents = new QMenu("Fichier récents");
            QAction *recentAction = new QAction("Fichier1.txt");
        fichierRecents->addAction(recentAction);
   fichier->addMenu(fichierRecents);

    QMenu *options = menuBar()->addMenu("&Options");
        QAction *filtreAuto = new QAction("AutoFiltre");
        filtreAuto->setCheckable(true);
        filtreAuto->isChecked();
    options->addAction(filtreAuto);

    QMenu *aide = menuBar()->addMenu("&Aide");
        QAction *aideAction = new QAction("Aide");
    aide->addAction(aideAction);

    QMenu *quitter = menuBar()->addMenu("&Quitter");
        QAction *quitterAction = new QAction("Quitter");
        connect(quitterAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    quitter->addAction(quitterAction);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    analyseWindow *f = new analyseWindow();
    f->show();


    //Faire un get de l'image ouverte avec le bouton ouvrir////////////
    //QString image = getCheminImage();
    Mat3b bgr = imread("C:/Users/win/Desktop/PanneauxAI/stop-sign-model.png");

    Mat3b hsv;
    cvtColor(bgr, hsv, COLOR_BGR2HSV);

    Mat1b mask1, mask2;
    inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
    inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);

    Mat1b mask = mask1 | mask2;

    imshow("Mask", mask);
    waitKey();
}

void MainWindow::on_pushButton_2_clicked()
{
    //Dans la comboBox on pourrait afficher toutes les images d'un dossier.
    //Ouverture d'une image
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
}
