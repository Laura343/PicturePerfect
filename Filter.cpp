#include "Filter.h"
#include <QPixmap>
#include <QFileDialog>
#include <QDateTime>
#include "imageToQImage.h"
#include "functionFilter.h"
FilterWidget::FilterWidget(QWidget *parent)
    : QWidget(parent)
{
    //layouts
    vlay1 = new QVBoxLayout;
    main_hlay=new QHBoxLayout;
    vlay2=new QVBoxLayout;
    hlay=new QHBoxLayout;//tools
    main_vlay = new QVBoxLayout;

    //filters
    filter1 = new QToolButton;
    filter2 = new QToolButton;
    filter3 = new QToolButton;
    filter4 = new QToolButton;

    //tools
    zoomIn = new QToolButton;
    zoomOut = new QToolButton;
    rotate_left = new QToolButton;
    rotate_right = new QToolButton;
    paint = new QToolButton;
    erase = new QToolButton;
    color = new QToolButton;
    size_plus = new QToolButton;
    size_minus = new QToolButton;
    wheel = new QToolButton;
    save = new QToolButton;

    //go back button
    fromFilterback_button = new QToolButton;

    //zoom in/out, rotate Left/Right
    scene = new CustomGraphicsScene;
    view = new QGraphicsView(scene);

    //image
    image = new QLabel;

    fromFilterback_button->setIcon(QIcon(":Icons/home.png"));
    fromFilterback_button->setIconSize(QSize(30, 30));
    fromFilterback_button->setAutoRaise(true);
    fromFilterback_button->setToolTip("Home Page");
    fromFilterback_button->setStyleSheet("QToolButton { border: none; }");

    zoomIn->setIcon(QIcon(":Icons/zoomIn.png"));
    zoomIn->setIconSize(QSize(30, 30));
    zoomIn->setAutoRaise(true);
    zoomIn->setToolTip("Zoom In");
    zoomIn->setStyleSheet("QToolButton { border: none; }");

    zoomOut->setIcon(QIcon(":Icons/zoomOut.jpg"));
    zoomOut->setIconSize(QSize(30, 30));
    zoomOut->setAutoRaise(true);
    zoomOut->setToolTip("Zoom Out");
    zoomOut->setStyleSheet("QToolButton { border: none; }");

    rotate_left->setIcon(QIcon(":Icons/rotateLeft.png"));
    rotate_left->setIconSize(QSize(30, 30));
    rotate_left->setAutoRaise(true);
    rotate_left->setToolTip("Rotate Left");
    rotate_left->setStyleSheet("QToolButton { border: none; }");

    rotate_right->setIcon(QIcon(":Icons/rotateRight.png"));
    rotate_right->setIconSize(QSize(30, 30));
    rotate_right->setAutoRaise(true);
    rotate_right->setToolTip("Rotate Right");
    rotate_right->setStyleSheet("QToolButton { border: none; }");

    paint->setIcon(QIcon(":Icons/color-palette.png"));
    paint->setIconSize(QSize(30, 30));
    paint->setAutoRaise(true);
    paint->setToolTip("Paint");
    paint->setStyleSheet("QToolButton { border: none; }");

    erase->setIcon(QIcon(":Icons/rubber.png"));
    erase->setIconSize(QSize(30, 30));
    erase->setAutoRaise(true);
    erase->setToolTip("Rubber");
    erase->setStyleSheet("QToolButton { border: none; }");

    color->setIcon(QIcon(":Icons/paint.jpg"));
    color->setIconSize(QSize(30, 30));
    color->setAutoRaise(true);
    color->setToolTip("Colors");
    color->setStyleSheet("QToolButton { border: none; }");

    size_plus->setIcon(QIcon(":Icons/plus.png"));
    size_plus->setIconSize(QSize(30, 30));
    size_plus->setAutoRaise(true);
    size_plus->setToolTip("Increase The Size Of Brush");
    size_plus->setStyleSheet("QToolButton { border: none; }");

    size_minus->setIcon(QIcon(":Icons/minus.png"));
    size_minus->setIconSize(QSize(30, 30));
    size_minus->setAutoRaise(true);
    size_minus->setToolTip("Decrease The Size Of Brush");
    size_minus->setStyleSheet("QToolButton { border: none; }");

    wheel->setIcon(QIcon(":Icons/wheel.png"));
    wheel->setIconSize(QSize(30, 30));
    wheel->setAutoRaise(true);
    wheel->setToolTip("Choose Colors");
    wheel->setStyleSheet("QToolButton { border: none; }");

    save->setIcon(QIcon(":Icons/disk.png"));
    save->setIconSize(QSize(30, 30));
    save->setAutoRaise(true);
    save->setToolTip("Save");
    save->setStyleSheet("QToolButton { border: none; }");

    filter1->setIcon(QIcon(":Icons/original.jpg"));
    filter1->setIconSize(QSize(80, 80));
    filter1->setAutoRaise(true);
    filter1->setToolTip("No Filter");
    filter1->setStyleSheet("QToolButton { border: none; }");

    filter2->setIcon(QIcon(":Icons/black_and_white.jpg"));
    filter2->setIconSize(QSize(80, 80));
    filter2->setAutoRaise(true);
    filter2->setToolTip("Black And White");
    filter2->setStyleSheet("QToolButton { border: none; }");

    filter3->setIcon(QIcon(":Icons/sand.jpg"));
    filter3->setIconSize(QSize(80, 80));
    filter3->setAutoRaise(true);
    filter3->setToolTip("Sand");
    filter3->setStyleSheet("QToolButton { border: none; }");

    filter4->setIcon(QIcon(":Icons/red-blue.jpg"));
    filter4->setIconSize(QSize(80, 80));
    filter4->setAutoRaise(true);
    filter4->setToolTip("Red And Blue");
    filter4->setStyleSheet("QToolButton { border: none; }");

    hlay->addWidget(filter1);
    hlay->addWidget(filter2);
    hlay->addWidget(filter3);
    hlay->addWidget(filter4);

    vlay1->addWidget(view);

    vlay2->addWidget(fromFilterback_button,1);
    vlay2->addWidget(save,2);
    vlay2->addWidget(zoomIn,3);
    vlay2->addWidget(zoomOut,4);
    vlay2->addWidget(rotate_left,5);
    vlay2->addWidget(rotate_right,6);
    vlay2->addWidget(paint,7);

    main_hlay->addLayout(vlay1);
    main_hlay->addLayout(vlay2);
    main_vlay->addLayout(main_hlay);
    main_vlay->addLayout(hlay);
    setLayout(main_vlay);

    connect(zoomIn,&QToolButton::clicked,this,&FilterWidget::slotZoomin);
    connect(zoomOut,&QToolButton::clicked,this,&FilterWidget::slotZoomout);
    connect(rotate_right,&QToolButton::clicked,this,&FilterWidget::slotRotateRight);
    connect(rotate_left,&QToolButton::clicked,this,&FilterWidget::slotRotateLeft);
    connect(save,&QToolButton::clicked,this,&FilterWidget::saveImages);

    connect(filter1,&QToolButton::clicked,this,[this](){
        scene->clear();
        pixmap = originalPic;
        scene->addPixmap(originalPic);
        });
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
    connect(paint,&QToolButton::clicked,this,[this](){
        if(is_button_active == false){
            if(firstTime)
            {
                 prev=pixmap;
                 firstTime=false;
            }       
            erase = new QToolButton;
            color = new QToolButton;
            size_plus = new QToolButton;
            size_minus = new QToolButton;
            wheel = new QToolButton;
            erase->setIcon(QIcon(":Icons/rubber.png"));
            erase->setIconSize(QSize(30, 30));
            erase->setAutoRaise(true);
            erase->setToolTip("Rubber");
            erase->setStyleSheet("QToolButton { border: none; }");

            color->setIcon(QIcon(":Icons/paint.jpg"));
            color->setIconSize(QSize(30, 30));
            color->setAutoRaise(true);
            color->setToolTip("Brush");
            color->setStyleSheet("QToolButton { border: none; }");

            size_plus->setIcon(QIcon(":Icons/plus.png"));
            size_plus->setIconSize(QSize(30, 30));
            size_plus->setAutoRaise(true);
            size_plus->setToolTip("Increase the size");
            size_plus->setStyleSheet("QToolButton { border: none; }");

            size_minus->setIcon(QIcon(":Icons/minus.png"));
            size_minus->setIconSize(QSize(30, 30));
            size_minus->setAutoRaise(true);
            size_minus->setToolTip("Decrease the size");
            size_minus->setStyleSheet("QToolButton { border: none; }");

            wheel->setIcon(QIcon(":Icons/wheel.png"));
            wheel->setIconSize(QSize(30, 30));
            wheel->setAutoRaise(true);
            wheel->setToolTip("Choose Colors");
            wheel->setStyleSheet("QToolButton { border: none; }");

            vlay2->addWidget(color,8);
            vlay2->addWidget(erase,9);
            vlay2->addWidget(wheel,10);
            vlay2->addWidget(size_plus,11);
            vlay2->addWidget(size_minus,12);
            is_button_active = true;
            connect(color,&QToolButton::clicked,this,[this](){
                if(is_brush_active)
                {
                    scene->is_active = false;
                    is_brush_active=false;
                }
                else
                {
                    scene->is_active = true;
                    is_brush_active=true;
                }
            });
            connect(wheel,SIGNAL(clicked()),this,SLOT(changeColor()));
            connect(size_plus,SIGNAL(clicked()),this,SLOT(setPenSizeBig()));
            connect(size_minus,SIGNAL(clicked()),this,SLOT(setPenSizeSmall()));
            connect(erase,SIGNAL(clicked()),this,SLOT(clearDrawing()));
        }
        else{
            delete erase;
            delete color;
            delete wheel;
            delete size_plus;
            delete size_minus;
            is_button_active = false;
            scene->is_active = false;
            is_brush_active=false;
        }
    });

}

//save 
void FilterWidget::saveImages(){
    // Get the path where the images will be saved
    QString path = QFileDialog::getExistingDirectory(this, tr("Save Images"));
    // Loop through the QGraphicsScene and get each QPixmap
    foreach (QGraphicsItem* item, scene->items()) {
        if (item->type() == QGraphicsPixmapItem::Type) {
            QGraphicsPixmapItem* pixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            QPixmap pixmap = pixmapItem->pixmap();

            // Use the QPixmap::save() function to save each image to the file system with a unique name
            QString fileName = QString("%1/image_%2.png").arg(path).arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmsszzz").replace(":", "_"));
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

void FilterWidget::slotRotateLeft()
{
    QTransform transform;
    transform.rotate(-90); // Rotate by 90 degrees
    pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
    scene->clear();
    scene->addPixmap(pixmap);
}

void FilterWidget::slotRotateRight()
{
    QTransform transform;
    transform.rotate(90); // Rotate by 90 degrees
    pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
    scene->clear();
    scene->addPixmap(pixmap);
}

void FilterWidget::setImage(QString path)
{
    pixmap= QPixmap(path);
    originalPic = pixmap.scaled(QSize(400, 400), Qt::KeepAspectRatio);
    pixmap=originalPic;
    scene = new CustomGraphicsScene;
    scene->addPixmap(pixmap);
    view = new QGraphicsView(scene);
    vlay1->addWidget(view);
    scene->setPixmap(pixmap,currentColor,penSize);
}

void FilterWidget::setCamImage(const QPixmap* p)
{
    scene = new CustomGraphicsScene;
    pixmap=(*p).scaled(QSize(400, 400), Qt::KeepAspectRatio);
    scene->addPixmap(pixmap);
    view = new QGraphicsView(scene);
    vlay1->addWidget(view);
    scene->setPixmap(pixmap,currentColor,penSize);
}

void FilterWidget::changeColor() {
        QColorDialog colorDialog(this);
        QColor newColor = colorDialog.getColor(currentColor);
        if (newColor.isValid()) {
            currentColor = newColor; // Update currentColor with the chosen color
        }
    }

void FilterWidget::clearDrawing() {
        scene->clear();
        pixmap=prev;
        scene->addPixmap(prev);
    }

void FilterWidget::setPenSizeBig() {
        penSize++; // Update penSize with the chosen pen size
    }

void FilterWidget::setPenSizeSmall() {
        penSize--; // Update penSize with the chosen pen size
    }




