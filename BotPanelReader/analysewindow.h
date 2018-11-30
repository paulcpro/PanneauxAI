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

private:
    Ui::analyseWindow *ui;
};

#endif // ANALYSEWINDOW_H
