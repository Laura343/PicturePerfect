#include "Filter.h"
#include <QPixmap>
#include <QFileDialog>
#include "imageToQImage.h"
#include "functionFilter.h"
FilterWidget::FilterWidget(QWidget *parent)
    : QWidget(parent)
{

    fromFilterback_button->setIcon(QIcon(":Icons/home.png"));
    fromFilterback_button->setIconSize(QSize(30, 30));
    fromFilterback_button->setAutoRaise(true);
    fromFilterback_button->setStyleSheet("QToolButton { border: none; }");

    zoomIn->setIcon(QIcon(":Icons/zoomIn.png"));
    zoomIn->setIconSize(QSize(30, 30));
    zoomIn->setAutoRaise(true);
    zoomIn->setStyleSheet("QToolButton { border: none; }");

    zoomOut->setIcon(QIcon(":Icons/zoomOut.jpg"));
    zoomOut->setIconSize(QSize(30, 30));
    zoomOut->setAutoRaise(true);
    zoomOut->setStyleSheet("QToolButton { border: none; }");

    rotate_left->setIcon(QIcon(":Icons/rotateLeft.png"));
    rotate_left->setIconSize(QSize(30, 30));
    rotate_left->setAutoRaise(true);
    rotate_left->setStyleSheet("QToolButton { border: none; }");

    rotate_right->setIcon(QIcon(":Icons/rotateRight.png"));
    rotate_right->setIconSize(QSize(30, 30));
    rotate_right->setAutoRaise(true);
    rotate_right->setStyleSheet("QToolButton { border: none; }");

    crop->setIcon(QIcon(":Icons/crop.jpg"));
    crop->setIconSize(QSize(30, 30));
    crop->setAutoRaise(true);
    crop->setStyleSheet("QToolButton { border: none; }");

    paint->setIcon(QIcon(":Icons/paint.jpg"));
    paint->setIconSize(QSize(30, 30));
    paint->setAutoRaise(true);
    paint->setStyleSheet("QToolButton { border: none; }");

    save->setIcon(QIcon(":Icons/disk.png"));
    save->setIconSize(QSize(30, 30));
    save->setAutoRaise(true);
    save->setStyleSheet("QToolButton { border: none; }");

    filter1->setIcon(QIcon(":Icons/original.jpg"));
    filter1->setIconSize(QSize(80, 80));
    filter1->setAutoRaise(true);
    filter1->setStyleSheet("QToolButton { border: none; }");

    filter2->setIcon(QIcon(":Icons/black_and_white.jpg"));
    filter2->setIconSize(QSize(80, 80));
    filter2->setAutoRaise(true);
    filter2->setStyleSheet("QToolButton { border: none; }");

    filter3->setIcon(QIcon(":Icons/sand.jpg"));
    filter3->setIconSize(QSize(80, 80));
    filter3->setAutoRaise(true);
    filter3->setStyleSheet("QToolButton { border: none; }");

    filter4->setIcon(QIcon(":Icons/red-blue.jpg"));
    filter4->setIconSize(QSize(80, 80));
    filter4->setAutoRaise(true);
    filter4->setStyleSheet("QToolButton { border: none; }");

    hlay->addWidget(filter1);
    hlay->addWidget(filter2);
    hlay->addWidget(filter3);
    hlay->addWidget(filter4);

    vlay1->addWidget(view);

    vlay2->addWidget(fromFilterback_button,1);
    vlay2->addWidget(zoomIn,2);
    vlay2->addWidget(zoomOut,3);
    vlay2->addWidget(rotate_left,4);
    vlay2->addWidget(rotate_right,5);
    vlay2->addWidget(crop,6);
    vlay2->addWidget(paint,7);
    vlay2->addWidget(save,8);

    main_hlay->addLayout(vlay1);
    main_hlay->addLayout(vlay2);
    main_vlay->addLayout(main_hlay);
    main_vlay->addLayout(hlay);
    setLayout(main_vlay);

    connect(zoomIn,&QToolButton::clicked,this,&FilterWidget::slotZoomin);
    connect(zoomOut,&QToolButton::clicked,this,&FilterWidget::slotZoomout);
    connect(rotate_right,&QToolButton::clicked,this,&FilterWidget::slotRotateRight);
    connect(rotate_left,&QToolButton::clicked,this,&FilterWidget::slotRotateleft);
    connect(save,&QToolButton::clicked,this,&FilterWidget::saveImages);
    //doesn't work
    //connect(crop,&QToolButton::clicked,this,&FilterWidget::cropMyImage);


    connect(filter1,&QToolButton::clicked,this,[this](){
        scene->addPixmap(picture);
        });
    connect(filter2,&QToolButton::clicked,this,[this](){
        Image img=QImageToImage(picture.toImage());
        makeGray(img);
        QImage qimg = ImageToQImage(img);
        scene->addPixmap(QPixmap::fromImage(qimg));
        });
    connect(filter3,&QToolButton::clicked,this,[this](){
        Image img=QImageToImage(picture.toImage());
        Zerno(img);
        QImage qimg = ImageToQImage(img);
        scene->addPixmap(QPixmap::fromImage(qimg));
        });
    connect(filter4,&QToolButton::clicked,this,[this](){
        Image img=QImageToImage(picture.toImage());
        redBlue(img);
        QImage qimg = ImageToQImage(img);
        scene->addPixmap(QPixmap::fromImage(qimg));
        });
}


//doesn't work
// void FilterWidget::cropMyImage(){
//     //QRectF visibleArea = view->mapToScene(view->viewport()->rect()).boundingRect();

//     // Get the current image from the scene
//     QPixmap currentImage = QPixmap::grabWidget(view);
//     QPixmap resized = currentImage.scaled(QSize(200, 200), Qt::KeepAspectRatio);
//     scene->addPixmap(resized);
//     view->setScene(scene);
//     // QRect cropRect(50, 50, 100, 100);
//     // currentImage = currentImage.copy(cropRect);
// }


//save 
void FilterWidget::saveImages(){
    // Get the path where the images will be saved
    QString path = QFileDialog::getExistingDirectory(this, tr("Save Images"));

    // Counter variable to generate unique names for each image
    static int counter = 0;

    // Loop through the QGraphicsScene and get each QPixmap
    foreach (QGraphicsItem* item, scene->items()) {
        if (item->type() == QGraphicsPixmapItem::Type) {
            QGraphicsPixmapItem* pixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            QPixmap pixmap = pixmapItem->pixmap();

            // Use the QPixmap::save() function to save each image to the file system with a unique name
            QString fileName = QString("%1/image_%2.png").arg(path).arg(counter++);
            pixmap.save(fileName);
        }
    }
}

void FilterWidget::slotZoomin()
{
    view->scale(1.1,1.1);
}

void FilterWidget::slotZoomout()
{
    view->scale(1/1.1,1/1.1);
}

void FilterWidget::slotRotateleft()
{
    view->rotate(-90);
}

void FilterWidget::slotRotateRight()
{
    view->rotate(90);
}

//old version
// void FilterWidget::setImage(QString path)
// {
//     QPixmap pixmap(path);
//     QPixmap resized = pixmap.scaled(QSize(400, 400), Qt::KeepAspectRatio);
//     scene = new QGraphicsScene;
//     scene->addPixmap(resized);
//     view = new QGraphicsView(scene);
//     //view->setFixedSize(600,600);
//     vlay1->addWidget(view);
// }


void FilterWidget::setImage(QString path)
{
    QPixmap pixmap(path);
    picture = pixmap.scaled(QSize(400, 400), Qt::KeepAspectRatio);
    scene = new QGraphicsScene;
    scene->addPixmap(picture);
    view = new QGraphicsView(scene);
    //view->setFixedSize(600,600);
    vlay1->addWidget(view);
}


//old version
// void FilterWidget::setCamImage(const QPixmap* pixmap)
// {
//     QPixmap resized = (*pixmap).scaled(QSize(400, 400), Qt::KeepAspectRatio);
//     scene = new QGraphicsScene;
//     scene->addPixmap(resized);
//     view = new QGraphicsView(scene);
//     vlay1->addWidget(view);
// }


void FilterWidget::setCamImage(const QPixmap* pixmap)
{
    scene = new QGraphicsScene;
    scene->addPixmap((*pixmap).scaled(QSize(400, 400), Qt::KeepAspectRatio));
    view = new QGraphicsView(scene);
    vlay1->addWidget(view);
} 






