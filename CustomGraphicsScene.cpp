// CustomGraphicsScene.cpp

#include "CustomGraphicsScene.h"
#include <QPainter>
#include <QGraphicsPixmapItem>

CustomGraphicsScene::CustomGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{
}

void CustomGraphicsScene::setPixmap(const QPixmap& pixmap)
{
    m_pixmap = pixmap;
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        // Record the last position of the mouse
        m_lastPos = event->scenePos();
    }

    // Call the base class implementation to allow for further processing
    QGraphicsScene::mousePressEvent(event);
}

void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        // Draw on the pixmap using a QPainter
        QPainter painter(&m_pixmap);
        painter.setPen(Qt::black);
        painter.drawLine(m_lastPos, event->scenePos());
        m_lastPos = event->scenePos();

        // Update the QGraphicsPixmapItem to reflect the changes
        QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(items().first());
        if (pixmapItem) {
            pixmapItem->setPixmap(m_pixmap);
        }

        // Update the view to redraw the scene
        update();
    }

    // Call the base class implementation to allow for further processing
    QGraphicsScene::mouseMoveEvent(event);
}

void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        // Record the last position of the mouse
        m_lastPos = event->scenePos();
    }

    // Call the base class implementation to allow for further processing
    QGraphicsScene::mouseReleaseEvent(event);
}
