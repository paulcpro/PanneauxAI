#include "analysewindow.h"
#include "ui_analysewindow.h"

analyseWindow::analyseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyseWindow)
{
    ui->setupUi(this);

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
        QAction *quitterAction = new QAction("Aide");
    quitter->addAction(quitterAction);
}

analyseWindow::~analyseWindow()
{
    delete ui;
}
