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
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>
#include <QAction>
#include <QRectF>
#include <QDebug>
#include <QPixmap>
#include <QPointF>
#include <QColor>
#include <QLine>
#include <QGraphicsSceneMouseEvent>
#include <QResizeEvent>
#include <QEvent>
#include <QObject>
#include "CustomGraphicsScene.h"
//#include "MyPixmapItem.h"

class FilterWidget: public QWidget
{
    Q_OBJECT
public:
    FilterWidget(QWidget *parent = nullptr);
//private:
    //layouts
    QVBoxLayout *vlay1 = new QVBoxLayout;
    QHBoxLayout *main_hlay=new QHBoxLayout;
    QVBoxLayout *vlay2=new QVBoxLayout;
    QHBoxLayout *hlay=new QHBoxLayout;//tools
    QVBoxLayout *main_vlay = new QVBoxLayout;

    //filters
    QToolButton* filter1 = new QToolButton;
    QToolButton* filter2 = new QToolButton;
    QToolButton* filter3 = new QToolButton;
    QToolButton* filter4 = new QToolButton;

    //tools
    QToolButton* zoomIn = new QToolButton;
    QToolButton* zoomOut = new QToolButton;
    QToolButton* crop = new QToolButton;
    QToolButton* rotate_left = new QToolButton;
    QToolButton* rotate_right = new QToolButton;
    QToolButton* paint = new QToolButton;
    QToolButton* save = new QToolButton;



    QPushButton* b1=new QPushButton("clear all");
    QPushButton* b2=new QPushButton("pen");
    QPushButton* b3=new QPushButton("erasor");
    QPushButton* b4=new QPushButton("color change");
    QPushButton* b5=new QPushButton("size bigger");
    QPushButton* b6=new QPushButton("size smaller");


    //go back button
    QToolButton* fromFilterback_button = new QToolButton;

    //zoom in/out, rotates
    //QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView(scene);

    CustomGraphicsScene *scene=new CustomGraphicsScene;


    //image
    QLabel* image = new QLabel;
    QPixmap originalPic;
    QPixmap pixmap;
    //MyPixmapItem* pixmapItem;
    void setImage(QString);
    void setCamImage(const QPixmap* pixmap);


//paint stuff
    QColor currentColor = Qt::black; // Initial pen color is black
    int penSize = 2;
    QPointF lastPoint;
    bool isDrawing;
   
    //  void paintEvent(QPaintEvent *event);

    // void mousePressEvent(QMouseEvent *event);

    // void mouseMoveEvent(QMouseEvent *event);

    // void mouseReleaseEvent(QMouseEvent *event);
    // void drawLineTo(const QPointF &endPoint);
    //void focusInEvent(QFocusEvent *event);
    //void focusOutEvent(QFocusEvent *event);

    //bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void changeColor();
    void clearDrawing();
    void setPenSizeBig();
    void setPenSizeSmall();
//

    void slotZoomin();
    void slotZoomout();
    void slotRotateleft();
    void slotRotateRight();
    void saveImages();
};


#endif // FILTER_H
