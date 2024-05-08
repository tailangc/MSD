#ifndef DROPLET_H
#define DROPLET_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include "bucket.h"

class droplet:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    droplet(QGraphicsItem *parent = nullptr);
    int drop_speed = 1;
public slots:
    void move();
};

#endif // DROPLET_H
