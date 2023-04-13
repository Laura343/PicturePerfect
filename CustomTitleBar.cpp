//CustomTitleBar.cpp
#include "CustomTitleBar.h"
#include <QHBoxLayout>

CustomTitleBar::CustomTitleBar(QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    closeButton_ = new QToolButton(this);
    closeButton_->setObjectName("closeButton");
    closeButton_->setFixedSize(20, 20);
    closeButton_->setIcon(QIcon(":/icons/close.png"));

    minimizeButton_ = new QToolButton(this);
    minimizeButton_->setObjectName("minimizeButton");
    minimizeButton_->setFixedSize(20, 20);
    minimizeButton_->setIcon(QIcon(":/icons/minimize.png"));

    maximizeButton_ = new QToolButton(this);
    maximizeButton_->setObjectName("maximizeButton");
    maximizeButton_->setFixedSize(20, 20);
    maximizeButton_->setIcon(QIcon(":/icons/maximize.png"));

    layout->addWidget(closeButton_);
    layout->addWidget(minimizeButton_);
    layout->addWidget(maximizeButton_);

    setLayout(layout);
    setMinimumHeight(30);
    setMaximumHeight(30);
}