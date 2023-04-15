#include "CustomGraphicsScene.h"
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QPen>
CustomGraphicsScene::CustomGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{
}
void CustomGraphicsScene::setPixmap(QPixmap& pixmap,QColor& col,int& size,bool& is_Active)
{
    m_pixmap = &pixmap;
    m_currentColor = &col;
    m_penSize = &size;
    is_active = &is_Active;
}
void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(is_active){
        if (event->button() == Qt::LeftButton) {
            // Record the last position of the mouse
            m_lastPos = event->scenePos();
        }
        // Call the base class implementation to allow for further processing
        QGraphicsScene::mousePressEvent(event);
    }
}
void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(is_active){
        if (event->buttons() & Qt::LeftButton) {
            // Draw on the pixmap using a QPainter
            QPainter painter(m_pixmap);
            painter.setPen(QPen(*m_currentColor, *m_penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(m_lastPos, event->scenePos());
            m_lastPos = event->scenePos();
            clear();
            addPixmap(*m_pixmap);
        }
        // Call the base class implementation to allow for further processing
        QGraphicsScene::mouseMoveEvent(event);
    }
}
void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(is_active){
        if (event->button() == Qt::LeftButton) {
            // Record the last position of the mouse
            m_lastPos = event->scenePos();
        }
        // Call the base class implementation to allow for further processing
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

