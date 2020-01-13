#include "mainapplicationwindow.h"
#include "ui_mainapplicationwindow.h"

MainApplicationWindow::MainApplicationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApplicationWindow)
{
    ui->setupUi(this);
}

MainApplicationWindow::~MainApplicationWindow()
{
    delete ui;
}
