#ifndef MAINAPPLICATIONWINDOW_H
#define MAINAPPLICATIONWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QtCore>
#include <QtGui>

#include "sub_graph_gui.h"


namespace Ui
{
    class MainApplicationWindow : public QMainWindow
    {
        Q_OBJECT
    private:
        Ui::MainApplicationWindow *ui;
        QGraphicsScene *scene;
        topology::graph *graph_obj;
        std::vector<sub_graph_gui> sub_graphs;
    public:
        explicit MainApplicationWindow(QWidget *parent = nullptr);
        ~MainApplicationWindow();
        void start_siem();
    };
}

#endif // MAINAPPLICATIONWINDOW_H
