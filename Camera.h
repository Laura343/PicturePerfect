#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include "frameCapture.h"

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget();
    QLabel *m_label;
    Camera cam;
    QToolButton* original;
    QToolButton* sand;
    QToolButton* black_and_white;
    QToolButton* red_blue;
    int filterNumber=0;
    int timerId;
    void timerEvent(QTimerEvent* event);
public:
    QToolButton *goToPhotos_button;
    QToolButton *goToFilter_button;
};
#endif // CAMERA_H

