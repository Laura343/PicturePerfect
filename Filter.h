#ifndef FILTER_H
#define FILTER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QToolButton>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMenu>
#include <QAction>
#include <QRectF>
#include <QDebug>
#include <QPixmap>
#include <QColor>
#include "CustomGraphicsScene.h"

class FilterWidget: public QWidget
{
    Q_OBJECT
public:
    FilterWidget(QWidget *parent = nullptr);
//private:

    bool is_button_active = false;
    bool is_brush_active=false;
    //layouts
    QVBoxLayout *vlay1;
    QHBoxLayout *main_hlay;
    QVBoxLayout *vlay2;
    QHBoxLayout *hlay;
    QVBoxLayout *main_vlay;

    //filters
    QToolButton* filter1;
    QToolButton* filter2;
    QToolButton* filter3;
    QToolButton* filter4;

    //tools
    QToolButton* zoomIn;
    QToolButton* zoomOut;
    QToolButton* rotate_left;
    QToolButton* rotate_right;
    QToolButton* paint;
    QToolButton* erase;
    QToolButton* color;
    QToolButton* size_plus;
    QToolButton* size_minus;
    QToolButton* wheel;
    QToolButton* save;

    //go back button
    QToolButton* fromFilterback_button;

    //zoom in/out, rotates
    CustomGraphicsScene *scene;
    QGraphicsView *view;

    //image
    QLabel* image;
    QPixmap originalPic;
    QPixmap pixmap;
    QPixmap prev;
    void setImage(QString);
    void setCamImage(const QPixmap* pixmap);
    QPixmap rotateLeftPixmap90Degrees(const QPixmap& original);
    QPixmap rotateRightPixmap90Degrees(const QPixmap& original);
    QColor currentColor = Qt::black; // Initial pen color is black
    int penSize = 2;
    bool firstTime=true;
public slots:
    void changeColor();
    void clearDrawing();
    void setPenSizeBig();
    void setPenSizeSmall();
    void slotZoomin();
    void slotZoomout();
    void slotRotateLeft();
    void slotRotateRight();
    void saveImages();
    //void cropMyImage();
};


#endif // FILTER_H
