#ifndef LEARNINGWINDOW_H
#define LEARNINGWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>


namespace Ui{
class learningwindow;
}

class learningwindow : public QMainWindow
{

    Q_OBJECT

public:
    explicit learningwindow(QWidget *parent=0);
    ~learningwindow();

private:
    Ui::learningwindow *ui;
};

#endif // LEARNINGWINDOW_H

