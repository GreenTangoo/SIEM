#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <QObject>
#include <QLabel>
#include <QPainter>
#include <QGraphicsObject>

#include "../correlation_module/graph.h"
#include "../correlation_module/sub_graph.h"
#include "../prediction_module/predictor.hpp"
#include "../aggregator/time_class/parse_time.hpp"

class graph_node : public QGraphicsObject
{
    Q_OBJECT
private:
    QLabel *info_label;
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    explicit graph_node();
    ~graph_node();
    void setInfoArea(QLabel *label);
public slots:
    void showIinfo();
};

#endif // GRAPH_NODE_H
