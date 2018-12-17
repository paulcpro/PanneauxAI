#ifndef DIALOG_H
#define DIALOG_H
#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <opencv2\opencv.hpp>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

protected:
void closeEvent(QCloseEvent *event);

private:
    Ui::Dialog *ui;
    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;
};

#endif // DIALOG_H
