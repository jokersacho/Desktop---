#ifndef AUTOHIDEWIDGET_H
#define AUTOHIDEWIDGET_H
#pragma once
#include <QWidget>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QPainter>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QToolButton>
#include <QDir>
#include <QDebug>
#include "buttonclicked.h"
#include "path.h"

namespace Ui {
class autoHideWidget;
}

class autoHideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit autoHideWidget(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *evevt);
    void enterEvent(QEvent *event);                 //鼠标进入事件
    void leaveEvent(QEvent *event);                 //鼠标离开事件
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseRleaseEvent(QMouseEvent *event);
    void hideWidget();
    void dragEnterEvent(QDragEnterEvent *event);    //拖动快捷方式进程序
    void dropEvent(QDropEvent*event);               //鼠标松开
    ~autoHideWidget();
private slots:
    void inputPath(QString  &path,QString fileName);
    void reLoad();
    void on_btnClose_clicked();

private:
    Ui::autoHideWidget *ui;
    bool is_hiding;
    QPoint m_startPosition, m_framePosition;
    bool m_dragging;
    QPixmap m_back;
	buttonClicked *button;
    int count=0;
    path m_path;
	QUrl t;
    QFileIconProvider icon_provider;
};

#endif // AUTOHIDEWIDGET_H
