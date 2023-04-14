#include "Filter.h"
#include <QPixmap>
#include <QFileDialog>
#include "imageToQImage.h"
#include "functionFilter.h"
#include <QCursor>
#include <QBitMap>
#include <QColorDialog>
FilterWidget::FilterWidget(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    view->installEventFilter(this);
    setMouseTracking(true);
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


    //added hanun paint
    QHBoxLayout* knopki=new QHBoxLayout;
    knopki->addWidget(b1);
    knopki->addWidget(b2);
    knopki->addWidget(b3);
    knopki->addWidget(b4);
    knopki->addWidget(b5);
    knopki->addWidget(b6);
    main_vlay->addLayout(knopki);
    setLayout(main_vlay);
    //


    connect(zoomIn,&QToolButton::clicked,this,&FilterWidget::slotZoomin);
    connect(zoomOut,&QToolButton::clicked,this,&FilterWidget::slotZoomout);
    connect(rotate_right,&QToolButton::clicked,this,&FilterWidget::slotRotateRight);
    connect(rotate_left,&QToolButton::clicked,this,&FilterWidget::slotRotateleft);
    connect(save,&QToolButton::clicked,this,&FilterWidget::saveImages);
    //doesn't work
    //connect(crop,&QToolButton::clicked,this,&FilterWidget::cropMyImage);


    connect(filter1,&QToolButton::clicked,this,[this](){
        scene->clear();
        pixmap=originalPic;
        scene->addPixmap(originalPic);
        });
    connect(filter2,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        makeGray(img);
        QImage qimg = ImageToQImage(img);
        pixmap=QPixmap::fromImage(qimg);
        scene->addPixmap(pixmap);
        });
    connect(filter3,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        Zerno(img);
        QImage qimg = ImageToQImage(img);
        pixmap=QPixmap::fromImage(qimg);
        scene->addPixmap(pixmap);
        });
    connect(filter4,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        redBlue(img);
        QImage qimg = ImageToQImage(img);
        pixmap=QPixmap::fromImage(qimg);
        scene->addPixmap(pixmap);
        });


    //pixmapItem = new MyPixmapItem(pixmap);
    //scene->addItem(pixmapItem);
   

    connect(b4,SIGNAL(clicked()),this,SLOT(changeColor()));
    connect(b5,SIGNAL(clicked()),this,SLOT(setPenSizeBig()));
    connect(b6,SIGNAL(clicked()),this,SLOT(setPenSizeSmall()));
} 

// bool FilterWidget::eventFilter(QObject *obj, QEvent *event)
// {
//     if (obj == view /*&& event->type() == QEvent::GraphicsSceneMouseEvent*/)
//     {
//         QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);

//         // Check the mouse event type
//         if (mouseEvent->type() == QEvent::GraphicsSceneMousePress)
//         {
//             // Handle mouse press event
//             if (mouseEvent->button() == Qt::LeftButton)
//             {
//                 isDrawing = true;
//                 lastPoint = view->mapToScene(mouseEvent->pos().toPoint());
//             }
//         }
//         else if (mouseEvent->type() == QEvent::GraphicsSceneMouseMove)
//         {
//             // Handle mouse move event
//             if (isDrawing)
//             {
//                 // Draw line from last point to current point
//                 QPainter painter(&pixmap);
//                 painter.setPen(QPen(currentColor, penSize));
//                 painter.drawLine(lastPoint, view->mapToScene(mouseEvent->pos().toPoint()));
//                 lastPoint = view->mapToScene(mouseEvent->pos().toPoint());
//                 update();
//             }
//         }
//         else if (mouseEvent->type() == QEvent::GraphicsSceneMouseRelease)
//         {
//             // Handle mouse release event
//             if (mouseEvent->button() == Qt::LeftButton)
//             {
//                 isDrawing = false;
//             }
//         }

//         // Return true to indicate that the event has been handled
//         return true;
//     }

//     // Call the base eventFilter() for default event handling
//     return QWidget::eventFilter(obj, event);
// }



void FilterWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void FilterWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = true;
        lastPoint = event->pos();
    }
}

void FilterWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing)
    {
        // Draw line from last point to current point
        QPainter painter(&pixmap);
        painter.setPen(QPen(currentColor, penSize));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void FilterWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = false;
    }
}


    // void FilterWidget::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //      if (event->button() == Qt::LeftButton || event->buttons() & Qt::TouchPointPressed) {
    //         lastPoint = event->pos(); // Save the starting point of the mouse click or touch
    //     }
    // }

    // void FilterWidget::mouseMoveEvent(QGraphicsSceneMouseEvent  *event) {
    //     if (event->buttons() & Qt::LeftButton || event->buttons() & Qt::TouchPointPressed) {
    //         QPainter painter(&pixmap);
    //         painter.setPen(QPen(currentColor, penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //         painter.drawLine(lastPoint, event->pos()); // Draw a line from lastPoint to current mouse position or touch point
    //         lastPoint = event->pos(); // Update lastPoint to current mouse position or touch point
    //         update(); // Update the widget to trigger repaint
    //     }
    // }

    // void FilterWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent  *event) {
    //     if (event->button() == Qt::LeftButton || event->buttons() & Qt::TouchPointReleased) {
    //         lastPoint = QPoint(); // Reset lastPoint when mouse or touch is released
    //     }
    // }


    // void FilterWidget::resizeEvent(QResizeEvent *event) {
    //    QPixmap newPixmap(event->size());
    //     newPixmap.fill(Qt::white); // Fill the pixmap with white color
    //     QPainter painter(&newPixmap);
    //     painter.drawPixmap(0, 0, pixmap); // Draw the old pixmap onto the new pixmap
    //     pixmap = newPixmap;
    // }

    //   void FilterWidget::drawLineTo(const QPointF &endPoint)
    // {
    //     // Draw a line on the pixmap from lastPos to endPoint
    //     QPainter painter(&pixmap);
    //     painter.setRenderHint(QPainter::Antialiasing, true);
    //     painter.setPen(QPen(Qt::red, 3));
    //     painter.drawLine(lastPos, endPoint);
    //     pixmapItem->setPixmap(pixmap);
    //     lastPos = endPoint.toPoint();
    // }


void FilterWidget::changeColor() {
        QColorDialog colorDialog(this);
        QColor newColor = colorDialog.getColor(currentColor);
        if (newColor.isValid()) {
            currentColor = newColor; // Update currentColor with the chosen color
        }
    }

    void FilterWidget::clearDrawing() {
        scene->clear();
        scene->addPixmap(pixmap);
    }

    void FilterWidget::setPenSizeBig() {
        penSize++; // Update penSize with the chosen pen size
    }

    void FilterWidget::setPenSizeSmall() {
        penSize--; // Update penSize with the chosen pen size
    }


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
    
    QPixmap rotated(pixmap.size());
    rotated.fill(Qt::transparent);

    QPainter painter(&rotated);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(pixmap.width() / 2, pixmap.height() / 2);
    painter.rotate(90);
    painter.translate(-pixmap.width() / 2, -pixmap.height() / 2);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();
    pixmap=rotated;
    scene->clear();
    scene->addPixmap(pixmap);
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
    pixmap= QPixmap(path);
    originalPic = pixmap.scaled(QSize(400, 400), Qt::KeepAspectRatio);
    pixmap=originalPic;
    scene = new QGraphicsScene;
    scene->addPixmap(pixmap);
    view = new QGraphicsView(scene);
    //view->setFixedSize(600,600);
    vlay1->addWidget(view);
}


void FilterWidget::setCamImage(const QPixmap* p)
{
    scene = new QGraphicsScene;
    pixmap=(*p).scaled(QSize(400, 400), Qt::KeepAspectRatio);
    scene->addPixmap(pixmap);
    view = new QGraphicsView(scene);
    vlay1->addWidget(view);
} 






