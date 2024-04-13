#include <QApplication>
#include "mainwidget.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    mainWidget window;
    window.setWindowTitle("Calculator");
    window.show();

    return app.exec();
}
