#include "mainwindow.h"
#include "analysewindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include "QFileDialog"
#include "QMessageBox"
#include <QPixmap>
#include <QDesktopServices>

QString MainWindow::cheminImage = "";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(800,450);

    /************* Menu Bar **************/
    QMenu *fichier = menuBar()->addMenu("&Fichier");
            QAction *ouvrirImage = new QAction("Ouvrir");
            //On doit faire un slot qui ouvre dans la fenêtre actuel l'image
            connect(ouvrirImage, SIGNAL(triggered()), this, SLOT(affichageImage()));
    fichier->addAction(ouvrirImage);

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
        //Faire un slot qui va ouvrir un readme.txt se trouvant dans le dossier du logiciel pour l'utilisation du logiciel
        connect(aideAction, SIGNAL(triggered()), this, SLOT(affichageDossier()));
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


/**********GET AND SET***********/
QString MainWindow::getCheminImage() {
return MainWindow::cheminImage;
}


void MainWindow::setCheminImage(QString x) {
    MainWindow::cheminImage = x;
}

//Bouton MenuBar:: Aide
void MainWindow::affichageDossier() {
    //Sert à ouvrir un fichier grâce à un chemin indiquant le fichier à ouvrir
    QDesktopServices::openUrl(QUrl("C:/BotPanelReader/readme.txt",QUrl::TolerantMode));
}

//Bouton Analyser
void MainWindow::on_pushButton_clicked()
{
   //Fait tout le traitement d'images sans afficher les filtres
    //Il affiche le kilomètrage du panneaux
}


//Bouton MenuBar::Ouvrir
void MainWindow::affichageImage() {
    //Ouverture d'une image
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    setCheminImage(fichier);

    QString image = getCheminImage();
    int x = this->ui->lImage->width();
    int y = this->ui->lImage->height();
    QPixmap *pixmap_img = new QPixmap(image);
    this->ui->lImage->setPixmap(pixmap_img->scaled(x,y));
}

//Bouton Ouvrir
void MainWindow::on_pushButton_2_clicked()
{
    //Ouverture d'une image
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    setCheminImage(fichier);

    QString image = getCheminImage();
    int x = this->ui->lImage->width();
    int y = this->ui->lImage->height();
    QPixmap *pixmap_img = new QPixmap(image);
    this->ui->lImage->setPixmap(pixmap_img->scaled(x,y));
}

//Bouton détail
void MainWindow::on_pushButton_3_clicked()
{
    //Mettre tout ce qui est dans la fenêtre analyse
    if(getCheminImage() == "") {
        QMessageBox::critical(this, "Erreur", "Sélectionner une image");
    } else {
        QString image = getCheminImage();
        analyseWindow *f = new analyseWindow();
        f->show();
    }
}

