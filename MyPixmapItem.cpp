#include "MyPixmapItem.h"

    MyPixmapItem::MyPixmapItem(const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap) {}

    void MyPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) 
    {
        // Handle mouse press event here
        lastPos = event->pos(); // Store last position for drawing
        QGraphicsPixmapItem::mousePressEvent(event);
    }

    void MyPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) 
    {
        // Handle mouse move event here
        drawLineTo(event->pos()); // Draw line to current position
        lastPos = event->pos();   // Update last position
        QGraphicsPixmapItem::mouseMoveEvent(event);
    }

    void MyPixmapItem::drawLineTo(const QPointF &endPoint)
    {
        // Draw a line on the pixmap from lastPos to endPoint
        QPixmap pixmap = this->pixmap();
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::red, 3));
        painter.drawLine(lastPos, endPoint);
        setPixmap(pixmap);
    }


