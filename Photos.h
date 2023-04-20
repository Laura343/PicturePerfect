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
public:
    QToolButton *fromPhotosBack_button;
    QVBoxLayout* lay;
    QGridLayout *grid_lay;
    QVector<QToolButton*> button_array;
    QVector<QString> path_array={":Images/selena.jpg",
                                        ":Images/ariana_grande.jpeg",
                                        ":Images/image2.jpg",
                                        ":Images/smiles.png",
                                        ":Icons/image.png"};
};



#endif // PHOTOS_H


