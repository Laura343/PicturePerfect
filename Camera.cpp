#include "Camera.h"
#include "ImageToQImage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPixmap>

CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent)
{
    cam.startCamera();
    timerId = startTimer(30); // start timer to capture frames
    // create a label to display camera stream
    m_label = new QLabel(this);
    m_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_label->setAlignment(Qt::AlignCenter);
        
    // create a layout to position the label and button
    QHBoxLayout *camLay = new QHBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout(this);
    camLay->addWidget(m_label);

    original = new QToolButton;
    black_and_white = new QToolButton;
    sand = new QToolButton;
    red_blue = new QToolButton;

    original->setIcon(QIcon(":Icons/original.jpg"));
    original->setIconSize(QSize(80, 80));
    original->setAutoRaise(true);
    original->setStyleSheet("QToolButton { border: none; }");

    black_and_white->setIcon(QIcon(":Icons/black_and_white.jpg"));
    black_and_white->setIconSize(QSize(80, 80));
    black_and_white->setAutoRaise(true);
    black_and_white->setStyleSheet("QToolButton { border: none; }");

    sand->setIcon(QIcon(":Icons/sand.jpg"));
    sand->setIconSize(QSize(80, 80));
    sand->setAutoRaise(true);
    sand->setStyleSheet("QToolButton { border: none; }");

    red_blue->setIcon(QIcon(":Icons/red-blue.jpg"));
    red_blue->setIconSize(QSize(80, 80));
    red_blue->setAutoRaise(true);
    red_blue->setStyleSheet("QToolButton { border: none; }");

    QHBoxLayout *filtersLay=new QHBoxLayout(this);

    filtersLay->addWidget(original);
    filtersLay->addWidget(black_and_white);
    filtersLay->addWidget(sand);
    filtersLay->addWidget(red_blue);
    layout->addLayout(camLay);
    layout->addLayout(filtersLay);

    goToPhotos_button = new QToolButton;
    goToFilter_button = new QToolButton;

    goToPhotos_button->setIcon(QIcon(":Icons/add_picT.jpg"));
    goToPhotos_button->setIconSize(QSize(30, 30));
    goToPhotos_button->setAutoRaise(true);
    goToPhotos_button->setStyleSheet("QToolButton { border: none; }");

    goToFilter_button->setIcon(QIcon(":Icons/camera_t.png"));
    goToFilter_button->setIconSize(QSize(30, 30));
    goToFilter_button->setAutoRaise(true);
    goToFilter_button->setStyleSheet("QToolButton { border: none; }");
    
    //QHBoxLayout* lay=new QHBoxLayout;
    filtersLay->addWidget(goToFilter_button);
    filtersLay->addWidget(goToPhotos_button);

    connect(original,&QToolButton::clicked,this,[this](){filterNumber=0;});
    connect(sand,&QToolButton::clicked,this,[this](){filterNumber=1;});
    connect(black_and_white,&QToolButton::clicked,this,[this](){filterNumber=2;});
    connect(red_blue,&QToolButton::clicked,this,[this](){filterNumber=3;});

    setLayout(layout);

}

CameraWidget::~CameraWidget() 
{
    cam.endCamera(); // release the camera
}


void CameraWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        QImage image = ImageToQImage(cam.captureImage(filterNumber));
        m_label->setPixmap(QPixmap::fromImage(image));
    }
}



