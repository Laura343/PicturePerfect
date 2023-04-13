#pragma once

#include <QWidget>
#include <QToolButton>

class CustomTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTitleBar(QWidget* parent = nullptr);

private:
    QToolButton* closeButton_;
    QToolButton* minimizeButton_;
    QToolButton* maximizeButton_;
};