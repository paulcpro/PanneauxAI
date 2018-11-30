#ifndef HISTOGRAMMEWINDOW_H
#define HISTOGRAMMEWINDOW_H

#include <QDialog>

namespace Ui {
class histogrammeWindow;
}

class histogrammeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit histogrammeWindow(QWidget *parent = 0);
    ~histogrammeWindow();

private:
    Ui::histogrammeWindow *ui;
};

#endif // HISTOGRAMMEWINDOW_H
