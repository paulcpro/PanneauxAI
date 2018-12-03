#include "mainwindow.h"
#include <analysewindow.h>
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include "QFileDialog"
#include "QMessageBox"
#include <QPixmap>

QString MainWindow::cheminImage = "";


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

    //Affichage photo
    //QPixmap *pixmap_img = new QPixmap("C:/Users/win/Desktop/PanneauxAI/70.jpg");
    //this->ui->lImage->setPixmap(pixmap_img->scaled(200,200));
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


//Bouton Analyser
void MainWindow::on_pushButton_clicked()
{



    if(getCheminImage() == "") {
        QMessageBox::critical(this, "Erreur", "Sélectionner une image");
    } else {
        //Faire un get de l'image ouverte avec le bouton ouvrir////////////
        QString image = getCheminImage();

        QMessageBox::information(this,"chemin","chemin : " + image);
        analyseWindow *f = new analyseWindow();
        f->show();
    }

}


//Bouton Ouvrir
void MainWindow::on_pushButton_2_clicked()
{
    //Dans la comboBox on pourrait afficher toutes les images d'un dossier.
    //Ouverture d'une image
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    setCheminImage(fichier);
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);

    QString image = getCheminImage();
    int x = this->ui->lImage->width();
    int y = this->ui->lImage->height();
    QPixmap *pixmap_img = new QPixmap(image);
    this->ui->lImage->setPixmap(pixmap_img->scaled(x,y));

}
