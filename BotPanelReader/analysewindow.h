#ifndef ANALYSEWINDOW_H
#define ANALYSEWINDOW_H

#include <QDialog>

namespace Ui {
class analyseWindow;
}

class analyseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit analyseWindow(QWidget *parent = 0);
    ~analyseWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_4_clicked();

private:
    Ui::analyseWindow *ui;
};

#endif // ANALYSEWINDOW_H
