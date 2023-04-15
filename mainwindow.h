#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QStyle>
#include <QStyleOptionTitleBar>
#include <QPalette>
#include <QPixmap>
#include <QMessageBox>
#include <QCoreApplication>
#include "Camera.h"
#include "Filter.h"
#include "Photos.h"
#include "frameCapture.h"
#include "imageToQImage.h"

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
    QMenuBar* menuBar;
    QMenu *mode_menu;
    QMenu *help_menu;
    QAction *light;
    QAction *dark;
    QAction *about_us;
public slots:
    void toggleLightMode();
    void toggleDarkMode();
    void aboutUsMessageBox();
};


#endif // MAINWINDOW_H



