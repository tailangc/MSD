#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>

#include "game1scene.h"


int  main(int argc, char **argv)
{
    QApplication app (argc, argv);

    game1scene *scene = new game1scene();

    QGraphicsView* view_obj = new QGraphicsView(scene);

    view_obj->setFixedSize(910,512);

    view_obj->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view_obj->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view_obj->show();

    return app.exec();
}
