#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QPointF>
#include <QObject>

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CustomGraphicsScene(QObject* parent = nullptr);

    // Set the pixmap that you want to draw on
    void setPixmap(const QPixmap& pixmap);

protected:
    // Reimplement mousePressEvent to handle mouse press events
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    // Reimplement mouseMoveEvent to handle mouse move events
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    // Reimplement mouseReleaseEvent to handle mouse release events
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QPixmap m_pixmap; // The pixmap to draw on
    QPointF m_lastPos; // The last position of the mouse
};
#endif

