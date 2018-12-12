#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getCheminImage();
    void setCheminImage(QString);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void affichageImage();

    void on_pushButton_3_clicked();

    void affichageDossier();


private:
    Ui::MainWindow *ui;
    static QString cheminImage;
};

#endif // MAINWINDOW_H
