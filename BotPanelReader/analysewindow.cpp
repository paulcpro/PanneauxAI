#include "analysewindow.h"
#include "ui_analysewindow.h"
#include "histogrammewindow.h"
#include "mainwindow.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <opencv2\opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include <vector>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <opencv2/ml.hpp>


using namespace cv;
using namespace ml;
using namespace std;

QImage Mat2QImage(const cv::Mat3b &src) {
        QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
        for (int y = 0; y < src.rows; ++y) {
                const cv::Vec3b *srcrow = src[y];
                QRgb *destrow = (QRgb*)dest.scanLine(y);
                for (int x = 0; x < src.cols; ++x) {
                        destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
                }
        }
        return dest;
}

analyseWindow::analyseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyseWindow)
{
    ui->setupUi(this);

    setFixedSize(800,600);
    show();


    /************* Menu Bar **************/
    QMainWindow *fB = new QMainWindow();
    QMenu *fichier = fB->menuBar()->addMenu("&Fichier");
            QAction *ouvrirImage = new QAction("Ouvrir");
            //Configuration du bouton ouvrir////////////////// Obstacle: 3e argument
            //On doit faire un slot qui ouvre dans la fenêtre actuel l'image
            //connect(ouvrirImage, SIGNAL(triggered()), this, SLOT(affichageImage()));
    fichier->addAction(ouvrirImage);

    QMenu *enregistrement = new QMenu("&Enregistrer", fB->menuBar());
   // QMenu *enregistrement = menuBar()->addMenu("&Enregistrer");
        QAction *enregistrerRouge = new QAction("Filtre Rouge");
        //connect Enregistrer Filtre Rouge
        QAction *enregistrerNoir = new QAction("Filtre Noir");
        //connect Enregistrer Filtre Noir
        QAction *enregistrerResultat = new QAction("Filtre Résultat");
        //connect Enregistrer Filtre Résultat
        QAction *enregistrerTout = new QAction("Tout");
        //connect Enregistrer Tout
    enregistrement->addAction(enregistrerRouge);
    enregistrement->addAction(enregistrerNoir);
    enregistrement->addAction(enregistrerResultat);
    enregistrement->addAction(enregistrerTout);

        QMenu *fichierRecents = new QMenu("Fichier récents");
            QAction *recentAction = new QAction("Fichier1.txt");
        fichierRecents->addAction(recentAction);
   fichier->addMenu(fichierRecents);

    QMenu *options = fB->menuBar()->addMenu("&Options");
        QAction *filtreAuto = new QAction("AutoFiltre");
        filtreAuto->setCheckable(true);
        filtreAuto->isChecked();
    options->addAction(filtreAuto);

    QMenu *aide = fB->menuBar()->addMenu("&Aide");
        QAction *aideAction = new QAction("Aide");
        //Configuration du bouton Aide///////////////////////// Obstacle: 3e argument
        //Faire un slot qui va ouvrir un readme.txt se trouvant dans le dossier du logiciel pour l'utilisation du logiciel
        //connect(aideAction, SIGNAL(triggered()), this, SLOT(affichageDossier()));
    aide->addAction(aideAction);

    QMenu *quitter = fB->menuBar()->addMenu("&Quitter");
        QAction *quitterAction = new QAction("Quitter");
        //connect(quitterAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    quitter->addAction(quitterAction);


    /*       Création du filtre rouge     */
    //Récupère l'image de la fenêtre mainwindow (image original)
    MainWindow *f = new MainWindow();
    QString imageR = f->getCheminImage();
    int x = this->ui->lImage->width();
    int y = this->ui->lImage->height();
    //Affichage dans le label Image original
    QPixmap *pixmap_img = new QPixmap(imageR);
    this->ui->lImage->setPixmap(pixmap_img->scaled(x,y));


    //Application du filtre rouge par défaut->
    std::string imageRC = imageR.toLocal8Bit().constData();
    Mat3b image = imread(imageRC); //Récupération de l'image
    Mat3b imageBlack = imread(imageRC);

    Mat3b hsv; //Teinte (couleur) / Saturation (plus ou moins vif) / value (type de teinte)
    cvtColor(image, hsv, COLOR_BGR2HSV); //Teint l'image de base en la convertissant de RGB à HSV voir: https://docs.opencv.org/4.0.0/d8/d01/group__imgproc__color__conversions.html#ga397ae87e1288a81d2363b61574eb8cab
    //fonction cvtColor: 1er/Image 2e/Récupère un objet Mat3b pour y mettre le filtre 3e/Choix de du filtre à appliquer

    Mat1b mask1, mask2;

    //imshow("ImageBasic", image);
    //imshow("Teinte", hsv);


    //Application d'un premier m
    //ask pour ce type de couleur RGB;
    inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
    //On comprend un panel entre deux scalaires
    //1er/ image teinté 2e/ scalair rgb valeur basses, 3e/ scalair rgb valeur haute  4e/ Sort un objet

    //Puis du second voir: https://docs.opencv.org/4.0.0/d2/de8/group__core__array.html#ga48af0ab51e36436c5d04340e036ce981
    inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);



    //imshow("Mask1", mask1);
    //imshow("Mask2", mask2);

    Mat1b mask = mask1 | mask2; //Application de plusieurs filtre en même temps

    //Sauvegarde du filtre rouge
    imwrite( "C:/Users/danym/Documents/Cours_CFI_MONTIGNY/Projet_Panneau/PanneauxAI-master_18122018/PanneauxAI-master/PanneauxAI/filtreRouge.jpg", mask);

    /***********************************/




    /*********** FIN DU FILTRE ROUGE ***********/

    /*      Création du filtre cercle       */

    //Lecture de l'image filtré en rouge et noir
   QString imageRouge = ("C:/Users/danym/Documents/Cours_CFI_MONTIGNY/Projet_Panneau/PanneauxAI-master_18122018/PanneauxAI-master/PanneauxAI/filtreRouge.jpg");
   std::string imageRougeC = imageRouge.toLocal8Bit().constData();

       Mat src = imread(imageRougeC);
       // Check if image is loaded fine
       Mat gray;

       //Converti en noir et blanc l'image
       cvtColor(src, gray, COLOR_BGR2GRAY);

       //Traite l'image en noir et blanc et resort l'image traitée
       medianBlur(gray, gray, 5);

       vector<Vec3f> circles;
       //Traite notre image pour y resortir un cercle
       HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                    gray.rows/5,  // Changer la valeur pour détecter des cercles à une distance différente
                    100, 30, 1, 250 // Changement des deux derniers parametres pour faire varier la détection
               // (min_radius & max_radius) to detect larger circles
       );

       for( size_t i = 0; i < circles.size(); i++ )
       {
           Vec3i c = circles[i];

           Point center = Point(c[0], c[1]);

           // Affiche le point du cercle
           circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);

           // Sert à tracer le cercle
           int radius = c[2];
           circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);


           Mat src2 = imread(imageRC);
           Mat clone(src2, Rect(center.x-radius, center.y-radius, radius*2, radius*2));


                      QFile file("image.png");     //clone
                                 file.open(QIODevice::WriteOnly);
                                 QImage img = Mat2QImage(clone);
                                 img.save(&file, "PNG");   //enregistrement de l'image
                                 file.close();

                      imshow("clone", clone);

       }
       //imshow("Detection de cercle", src);

       //Sauvegarde du filtre détection de cercle
       imwrite("C:/Users/danym/Documents/Cours_CFI_MONTIGNY/Projet_Panneau/PanneauxAI-master_18122018/PanneauxAI-master/PanneauxAI/filtreCercle.jpg", src);


       ////Test lecture chiffre////







    /********* FIN DU FILTRE CERCLE *********/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //       Création du filtre noir */
 //      Mat3b teinte;
//       QString imagecoupe = ("C:/Users/danym/Documents/Cours_CFI_MONTIGNY/Projet_Panneau/BotPanelReader_18122018_1142/Build-BotPanelReader-Desktop_Qt_5_9_0_MinGW_32bit-Debug/image.png");
//       std::string imageCoupe = imagecoupe.toLocal8Bit().constData();
//       Mat src3 = imread(imageCoupe);
       //test COLOR_BGR2GRAY -> bug
       //test COLOR_RGB2GRAY -> bug
       //test COLOR_BGRA2RGBA -> bug
       //test COLOR_GRAY2BGR -> bug
       //test COLOR_BGR2HLS -> Teint en vert; laisse rouge; noir en violet

//       cvtColor(src3, teinte, COLOR_BGR2HSV );

//       Mat1b maskTest1;
       //Mat1b maskTest2;


       //imshow("Teinte Black", teinte);
       //0,0,0 ; 255,255,255 => met tout en blanc
       //0,0,0 ; 100,100,100 => BON RESULTAT
       //0,0,0 ; 100,255,255 => color le rouge en noir
//       inRange(teinte, Scalar(0, 0, 0), Scalar(80, 80, 80), maskTest1);
       //0,0,0 ; 50,50,50 => Retrouve bien le 70 mais pas entierement
       //0,0,0 ; 75,75,75 => Retrouve bien le cercle rouge

       //imshow("Teinte Black", teinte);
       //0,0,0 ; 255,255,255 => met tout en blanc
       //0,0,0 ; 100,100,100 => BON RESULTAT
       //0,0,0 ; 100,255,255 => color le rouge en noir
       //inRange(teinte, Scalar(0, 0, 0), Scalar(50, 50, 50), maskTest2);

//       imshow("Mask Test1", maskTest1);

       /* Résultat avec filtre rouge et noir */
       /*
       Mat1b maskFinal = maskTest1 | mask;

       imshow("Mask Final", maskFinal);

       imwrite("C:/Resources/PanneauxAI/filtreFinal.jpg", maskFinal);
       */

       //imshow("Mask Test2", maskTest2);

       //Mat1b maskBlack = maskTest1 | maskTest2;

       //imshow("Mask Black", maskBlack);


       //Sauvegarde du filtre noir
//      imwrite("C:/Users/danym/Documents/Cours_CFI_MONTIGNY/Projet_Panneau/PanneauxAI-master_18122018/PanneauxAI-master/PanneauxAI/filtreNoir.jpg", maskTest1);
       /*****************************/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       //Utilisation du filtre cercle sur le filtre rouge

    //Affichage de l'image une fois fitlré rouge dans le label
    int x4 = this->ui->label_4->width();
    int y4 = this->ui->label_4->height();
    //Affichage dans le label Image filtré
    QPixmap *pixmap_img4 = new QPixmap("C:/Users/danym/Documents/Cours_CFI_MONTIGNY/Projet_Panneau/PanneauxAI-master_18122018/PanneauxAI-master/PanneauxAI/filtreRouge.jpg");
    this->ui->label_4->setPixmap(pixmap_img4->scaled(x4,y4));

    //Affichage de l'image une fois filtré noir dans le label
    int x2 = this->ui->lImage_3->width();
    int y2 = this->ui->lImage_3->height();
    QPixmap *pixmap_img3 = new QPixmap("C:/Users/danym/Documents/Cours_CFI_MONTIGNY/Projet_Panneau/PanneauxAI-master_18122018/PanneauxAI-master/PanneauxAI/filtreNoir.jpg");
    this->ui->lImage_3->setPixmap(pixmap_img3->scaled(x2,y2));

    //Affichage de l'image une fois filtré noir dans le label
    int x5 = this->ui->lImage_5->width();
    int y5 = this->ui->lImage_5->height();
    QPixmap *pixmap_img5 = new QPixmap("C:/Users/danym/Documents/Cours_CFI_MONTIGNY/Projet_Panneau/PanneauxAI-master_18122018/PanneauxAI-master/PanneauxAI/filtreCercle.jpg");
    this->ui->lImage_5->setPixmap(pixmap_img5->scaled(x5,y5));

    //imshow("Mask", mask);
    waitKey();


    /********** FIN UTILISATION OPENCV **************/

}






analyseWindow::~analyseWindow()
{
    delete ui;
}

void analyseWindow::on_pushButton_2_clicked()
{
    close();
}

//bugged
void analyseWindow::on_pushButton_3_clicked() {
close();
}

//Sert à enregistrer les images des labels en fonction des checkbox checké
void analyseWindow::on_pushButton_4_clicked() {
    //Filtre rouge
    if(this->ui->checkBox_4->isChecked()) {
//std::string imageRougeC = imageRouge.toLocal8Bit().constData(); POUR QSTRING TO STRING
        //std::string str = "example";
        //QString qs = QString::fromLocal8Bit(str.c_str());
        //Convertir cet image du string au qstring



        QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer filtre rouge", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
        QFile file(fichier);

        if(fichier == "") {
            QMessageBox::critical(this, "Erreur", "Votre fichier n'a pas pu être enregistré.");
        } else {
            QMessageBox::information(this, "Informations", "Votre fichier a été enregistré avec succès !");
        }
    }

    //Filtre noir
    if(this->ui->checkBox_2->isChecked()) {
        QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer filtre noir", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
       // QFile file(fichier);

        if(fichier == "") {
            QMessageBox::critical(this, "Erreur", "Votre fichier n'a pas pu être enregistré.");
        } else {
            QMessageBox::information(this, "Informations", "Votre fichier a été enregistré avec succès !");
        }
    }

    //Résultat
    if(this->ui->checkBox_3->isChecked()) {
        QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer filtre final", "nouvelleImageEnregistrement", "Images (*.png *.gif *.jpg *.jpeg)");
        QFile file(fichier);

        if(fichier == "") {
            QMessageBox::critical(this, "Erreur", "Votre fichier n'a pas pu être enregistré.");
        } else {
            QMessageBox::information(this, "Informations", "Votre fichier a été enregistré avec succès !");
        }
    }
}

//bugged
void analyseWindow::on_checkBox_4_stateChanged(int a){ a=1;}

void analyseWindow::on_checkBox_4_clicked()
{
    if(!this->ui->checkBox_2->isChecked()) {
    this->ui->checkBox_2->setChecked(true);
    }

    if(!this->ui->checkBox_3->isChecked()) {
    this->ui->checkBox_3->setChecked(true);
    }

    if(!this->ui->checkBox->isChecked()) {
    this->ui->checkBox->setChecked(true);
    }
}
