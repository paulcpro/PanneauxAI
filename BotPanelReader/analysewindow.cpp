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


using namespace cv;
using namespace std;

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

    /***********************************/

    /* Création du filtre noir */
    Mat3b teinte;

    //test COLOR_BGR2GRAY -> bug
    //test COLOR_RGB2GRAY -> bug
    //test COLOR_BGRA2RGBA -> bug
    //test COLOR_GRAY2BGR -> bug
    //test COLOR_BGR2HLS -> Teint en vert; laisse rouge; noir en violet

    cvtColor(imageBlack, teinte, COLOR_BGR2HSV );

    Mat1b maskTest1, maskTest2;


    //imshow("Teinte Black", teinte);
    //0,0,0 ; 255,255,255 => met tout en blanc
    //0,0,0 ; 100,100,100 => BON RESULTAT
    //0,0,0 ; 100,255,255 => color le rouge en noir
    inRange(teinte, Scalar(0, 0, 0), Scalar(75, 75, 75), maskTest1);
    //0,0,0 ; 50,50,50 => Retrouve bien le 70 mais pas entierement
    //0,0,0 ; 75,75,75 => Retrouve bien le cercle rouge

    //imshow("Teinte Black", teinte);
    //0,0,0 ; 255,255,255 => met tout en blanc
    //0,0,0 ; 100,100,100 => BON RESULTAT
    //0,0,0 ; 100,255,255 => color le rouge en noir
    //inRange(teinte, Scalar(0, 0, 0), Scalar(50, 50, 50), maskTest2);

    imshow("Mask Test1", maskTest1);

    Mat1b maskFinal = maskTest1 | mask;

    imshow("Mask Final", maskFinal);

    imwrite("C:/Resources/PanneauxAI/filtreFinal.jpg", maskFinal);

    //imshow("Mask Test2", maskTest2);

    //Mat1b maskBlack = maskTest1 | maskTest2;

    //imshow("Mask Black", maskBlack);

    /*****************************/


    /*********** FIN DU FILTRE ROUGE ***********/

    /*      Création du filtre cercle       */
       Mat src = imread(imageRC);
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
       }
       imshow("Detection de cercle", src);
    /********* FIN DU FILTRE CERCLE *********/


    //Set un dossier par défaut; Ajout sélection par user
    QString defaultResources;

    imwrite( "C:/Resources/PanneauxAI/filtre.jpg", mask );


    //Affichage de l'image une fois fitlré dans le label
    int x4 = this->ui->label_4->width();
    int y4 = this->ui->label_4->height();
    //Affichage dans le label Image filtré
    QPixmap *pixmap_img4 = new QPixmap("C:/Resources/PanneauxAI/filtre.jpg");
    this->ui->label_4->setPixmap(pixmap_img4->scaled(x4,y4));



    imshow("Mask", mask);
    waitKey();

}

analyseWindow::~analyseWindow()
{
    delete ui;
}

void analyseWindow::on_pushButton_2_clicked()
{
    close();
}

//Ce bouton n'existe plus mais obligé de mettre la methode correspondante sinon bug
void analyseWindow::on_pushButton_3_clicked() {
close();
}

//Vérfier en fonction des checkbox ce qu'on devra enregistrer//////////////////////////////////////
void analyseWindow::on_pushButton_4_clicked()
{
    //Check tout
    if(this->ui->checkBox_4->isChecked()) {
    connect(this->ui->checkBox_4, SIGNAL(toggled(bool)), this->ui->checkBox_3, SLOT(setChecked(true)));
    connect(this->ui->checkBox_4, SIGNAL(toggled(bool)), this->ui->checkBox_2, SLOT(setChecked(true)));
    connect(this->ui->checkBox_4, SIGNAL(toggled(bool)), this->ui->checkBox, SLOT(setChecked(true)));
    }

    //Filtre rouge
    if(this->ui->checkBox_4->isChecked()) {
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
        QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer filtre final", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
       // QFile file(fichier);

        if(fichier == "") {
            QMessageBox::critical(this, "Erreur", "Votre fichier n'a pas pu être enregistré.");
        } else {
            QMessageBox::information(this, "Informations", "Votre fichier a été enregistré avec succès !");
        }
    }
}
