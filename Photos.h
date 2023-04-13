#ifndef PHOTOS_H
#define PHOTOS_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QVector>
#include <QString>

class PhotosWidget : public QWidget
{
    Q_OBJECT

public:
    PhotosWidget(QWidget *parent = nullptr);

//private:
    QToolButton *fromPhotosBack_button;

    QVBoxLayout* lay;
    QGridLayout *grid_lay;
    QVector<QToolButton*> button_array;
    QVector<QString> path_array={"Images/image1.jpg",
                                        "Images/image2.jpg",
                                        "Images/image3.jpg",
                                        "Images/image4.jpg",
                                        "Icons/square-plus.png"};
};



#endif // PHOTOS_H


