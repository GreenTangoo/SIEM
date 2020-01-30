#include "mainapplicationwindow.h"
#include "ui_mainapplicationwindow.h"

MainApplicationWindow::MainApplicationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApplicationWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    /*node = new graph_node();
    node->setPos(100, 100);
    scene->addItem(node);*/

}

MainApplicationWindow::~MainApplicationWindow()
{
    delete ui;
}

