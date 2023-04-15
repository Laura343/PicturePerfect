#include "mainwindow.h"

MainWindow::MainWindow()
{
    resize(500,600);
    setWindowTitle("Picture Perfect");
    setWindowIcon(QIcon(":Icons/window_icon.jpg"));

    menuBar = new QMenuBar(this);
    mode_menu = new QMenu("Mode",this);
    light = new QAction("Light",this);
    dark = new QAction("Dark",this);
    help_menu = new QMenu("Help",this);
    about_us = new QAction("About us",this);
    mode_menu->addAction(light);
    mode_menu->addAction(dark);
    help_menu->addAction(about_us);
    menuBar->addMenu(mode_menu);
    menuBar->addMenu(help_menu);
    setMenuBar(menuBar);

    cameraWidget = new CameraWidget;
    photosWidget = new PhotosWidget;
    filterWidget = new FilterWidget;

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(cameraWidget); //0 index
    stackedWidget->addWidget(photosWidget);  //1 index
    stackedWidget->addWidget(filterWidget);  //2 index
    setCentralWidget(stackedWidget);

    connect(light, &QAction::triggered, this, &MainWindow::toggleLightMode);
    connect(dark, &QAction::triggered, this, &MainWindow::toggleDarkMode);

    connect(cameraWidget->goToPhotos_button,&QToolButton::clicked,this,[this](){stackedWidget->setCurrentIndex(1);});

    connect(filterWidget->fromFilterback_button,&QToolButton::clicked,this,[this](){stackedWidget->setCurrentIndex(0);});
    connect(photosWidget->fromPhotosBack_button,&QToolButton::clicked,this,[this](){stackedWidget->setCurrentIndex(0);});

    connect(photosWidget->button_array[0],&QToolButton::clicked,this,[this](){
        delete filterWidget->view;
        delete filterWidget->scene;
        filterWidget->setImage(photosWidget->path_array[0]);
        stackedWidget->setCurrentIndex(2);});
    connect(photosWidget->button_array[1],&QToolButton::clicked,this,[this](){
        delete filterWidget->view;
        delete filterWidget->scene;
        filterWidget->setImage(photosWidget->path_array[1]);
        stackedWidget->setCurrentIndex(2);});
    connect(photosWidget->button_array[2],&QToolButton::clicked,this,[this](){
        delete filterWidget->view;
        delete filterWidget->scene;
        filterWidget->setImage(photosWidget->path_array[2]);
        stackedWidget->setCurrentIndex(2);});
    connect(photosWidget->button_array[3],&QToolButton::clicked,this,[this](){
        delete filterWidget->view;
        delete filterWidget->scene;
        filterWidget->setImage(photosWidget->path_array[3]);
        stackedWidget->setCurrentIndex(2);});
    connect(cameraWidget->goToFilter_button,&QToolButton::clicked,this,[this](){
        delete filterWidget->view;
        delete filterWidget->scene;
        Image im = cameraWidget->cam.captureOriginalImage();
        filterWidget->originalPic=QPixmap::fromImage(ImageToQImage(im)).scaled(QSize(400, 400), Qt::KeepAspectRatio);;
        filterWidget->setCamImage(cameraWidget->m_label->pixmap());
        stackedWidget->setCurrentIndex(2);}); 

    connect(photosWidget->button_array[4],&QToolButton::clicked,this,&MainWindow::addPhoto);
    
    connect(about_us,&QAction::triggered,this,&MainWindow::aboutUsMessageBox);
}

void MainWindow::aboutUsMessageBox(){
    QMessageBox::about(this, tr("About our application"),
            tr("This is a simple Qt application"));
}

void MainWindow::addPhoto()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", "", "JPEG files (*.jpg);;All files (*.*)");
    if(filePath=="")
    {
        return;
    }
    QToolButton* button = new QToolButton(this);
    button->setIcon(QIcon(filePath));
    button->setIconSize(QSize(200, 200));
    button->setAutoRaise(true);
    button->setStyleSheet("QToolButton { border: none; }");
    photosWidget->button_array.append(button);

    QToolButton* tmp=new QToolButton;
    tmp=photosWidget->button_array[photosWidget->button_array.size()-2];
    photosWidget->button_array[photosWidget->button_array.size()-2]=photosWidget->button_array[photosWidget->button_array.size()-1];
    photosWidget->button_array[photosWidget->button_array.size()-1]=tmp;

    photosWidget->lay->removeItem(photosWidget->grid_lay);
    if (photosWidget->grid_lay)
    {
        delete photosWidget->grid_lay;
    }

    photosWidget->grid_lay= new QGridLayout();
    for(int i=0;i<photosWidget->button_array.size();i++)
    {
        photosWidget->grid_lay->addWidget(photosWidget->button_array[i],i/3,i%3);
    }
    photosWidget->lay->addLayout(photosWidget->grid_lay);
    setLayout(photosWidget->grid_lay);

    connect(photosWidget->button_array[photosWidget->button_array.size()-2],&QToolButton::clicked,this,[this,filePath](){
        delete filterWidget->view;
        delete filterWidget->scene;
        filterWidget->setImage(filePath);
        stackedWidget->setCurrentIndex(2);});
}

//light mode
void MainWindow::toggleLightMode()
{
    // Set light mode stylesheets
    setStyleSheet("QWidget { background-color: white; color: black; }");
    stackedWidget->setStyleSheet("QWidget { background-color: white; color: black; }");
}

//dark mode 
void MainWindow::toggleDarkMode()
{
    // Set dark mode stylesheets
    setStyleSheet("QWidget { background-color: grey; color: black; }");
    stackedWidget->setStyleSheet("QWidget { background-color: grey; color: black; }");
}



MainWindow::~MainWindow()
{

}





