#pragma once
#ifndef BUTTONCLICKED_H
#define BUTTONCLICKED_H


#include <QToolButton>
#include <QMouseEvent>
#include <windows.h>

class buttonClicked : public QToolButton //重写qtoolbutton类；
{
    Q_OBJECT

public:
    buttonClicked(QWidget *parent=nullptr);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    QWidget *parent;
};

#endif // BUTTONCLICKED_H
