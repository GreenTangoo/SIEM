#ifndef MAINAPPLICATIONWINDOW_H
#define MAINAPPLICATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainApplicationWindow;
}

class MainApplicationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainApplicationWindow(QWidget *parent = nullptr);
    ~MainApplicationWindow();

private:
    Ui::MainApplicationWindow *ui;
};

#endif // MAINAPPLICATIONWINDOW_H
