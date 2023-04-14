#ifndef MYPIXMAPITEM_H
#define MYPIXMAPITEM_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

// Custom QGraphicsPixmapItem subclass
class MyPixmapItem : public QGraphicsPixmapItem
{
public:
    MyPixmapItem(const QPixmap &pixmap);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QPointF lastPos; // Store last position for drawing

    void drawLineTo(const QPointF &endPoint);
};
#endif