#ifndef STREAMWINDOW_H
#define STREAMWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class streamWindow;
}

class streamWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit streamWindow(QWidget *parent = 0);
    ~streamWindow();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_pressed();

protected:
void closeEvent(QCloseEvent *event);

private:
    Ui::streamWindow *ui;

    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;
};

#endif // STREAMWINDOW_H
