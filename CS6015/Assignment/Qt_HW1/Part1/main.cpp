#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create an instance of mainWidget
    mainWidget widget;
    widget.show();

    return a.exec();
}
