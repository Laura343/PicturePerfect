#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include "Camera.h"
#include "Filter.h"
#include "Photos.h"
#include "CustomTitleBar.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void addPhoto();

private:
    QStackedWidget *stackedWidget;
    CameraWidget *cameraWidget;
    PhotosWidget *photosWidget;
    FilterWidget *filterWidget;
    CustomTitleBar *titleBar;
    QMenu *menu;
    QMenu *mode;
    QAction *light;
    QAction *dark;
public slots:
    void toggleLightMode();
    void toggleDarkMode();
};


#endif // MAINWINDOW_H



