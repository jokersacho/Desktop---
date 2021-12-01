#include "buttonclicked.h"

buttonClicked::buttonClicked(QWidget *parent)
    : QToolButton(parent)
{
    parent = parent;
}

void buttonClicked::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QString path = this->text();
        ShellExecute(NULL, L"open", path.toStdWString().c_str(), NULL, NULL, SW_SHOWNORMAL);//获取该按钮内文本属性即路径，并且在桌面上根据路径打开文件；
    }
}


