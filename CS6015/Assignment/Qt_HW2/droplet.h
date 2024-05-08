#ifndef DROPLET_H
#define DROPLET_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
//#include "bucket.h"

class bucket;
class droplet:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    droplet(QGraphicsItem *parent = nullptr);
public slots:
    void move();
};

#endif // DROPLET_H
