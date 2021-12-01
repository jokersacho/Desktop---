#include <QApplication>
#include "autohidewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	autoHideWidget w;
    w.show(); 
    return a.exec();
}
