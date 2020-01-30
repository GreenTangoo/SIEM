#include "graph_node.h"

graph_node::graph_node()
{

}

graph_node::~graph_node()
{

}

void graph_node::setInfoArea(QLabel *label)
{
    info_label = label;
}

QRectF graph_node::boundingRect() const
{
    return QRectF(-12,-15,24,30);
}

void graph_node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Draw rectangle
    QPolygon polygon;
    polygon << QPoint(this->x(), this->y() - 12) << QPoint(this->x() + 15, this->y())
            << QPoint(this->x(), this->y() + 12) << QPoint(this->x() - 15, this->y());
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void graph_node::showIinfo()
{

}
