#include "analysewindow.h"
#include "ui_analysewindow.h"
#include <histogrammewindow.h>
#include "mainwindow.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <opencv2\opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QMessageBox>

using namespace cv;

analyseWindow::analyseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyseWindow)
{
    ui->setupUi(this);

    setFixedSize(800,450);
    show();

    //Récupère l'image de la fenêtre mainwindow (image original)
    MainWindow *f = new MainWindow();
    QString image = f->getCheminImage();
    int x = this->ui->lImage->width();
    int y = this->ui->lImage->height();
    //Affichage dans le label Image original
    QPixmap *pixmap_img = new QPixmap(image);
    this->ui->lImage->setPixmap(pixmap_img->scaled(x,y));

    //Application du filtre rouge par défaut

    Mat3b image = imread("C:/Users/win/Desktop/PanneauxAI/limitation-vitesse.jpg"); //Récupération de l'image

    Mat3b hsv; //Teinte (couleur) / Saturation (plus ou moins vif) / value (type de teinte)
    cvtColor(image, hsv, COLOR_BGR2HSV); //Teint l'image de base en la convertissant de RGB à HSV voir: https://docs.opencv.org/4.0.0/d8/d01/group__imgproc__color__conversions.html#ga397ae87e1288a81d2363b61574eb8cab
    //fonction cvtColor: 1er/Image 2e/Récupère un objet Mat3b pour y mettre le filtre 3e/Choix de du filtre à appliquer



    imshow("ImageBasic", image);
    imshow("Teinte", hsv);
    Mat1b mask1, mask2;

    //Application d'un premier mask pour ce type de couleur RGB;
    inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
    //On comprend un panel entre deux scalaires
    //1er/ image teinté 2e/ scalair rgb valeur basses, 3e/ scalair rgb valeur haute  4e/ Sort un objet


    //Puis du second voir: https://docs.opencv.org/4.0.0/d2/de8/group__core__array.html#ga48af0ab51e36436c5d04340e036ce981
    inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);


    imshow("Mask1", mask1);
    imshow("Mask2", mask2);
    Mat1b mask = mask1 | mask2; //Application de plusieurs filtre en même temps

    imshow("Mask", mask);
    waitKey();

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
    if(fichier == "") {
        QMessageBox::critical(this, "Erreur", "Votre fichier n'a pas pu être enregistré.");
    } else {
        QMessageBox::information(this, "Informations", "Votre fichier a été enregistré avec succès !");
    }
}
