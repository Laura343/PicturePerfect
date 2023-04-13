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

    //go back button
    QToolButton* fromFilterback_button = new QToolButton;

    //zoom in/out, rotates
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView(scene);

    //image
    QLabel* image = new QLabel;
    QPixmap picture;
    void setImage(QString);
    void setCamImage(const QPixmap* pixmap);
public slots:
    void slotZoomin();
    void slotZoomout();
    void slotRotateleft();
    void slotRotateRight();
    void saveImages();
    //void cropMyImage();
};


#endif // FILTER_H
