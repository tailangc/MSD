#ifndef CLOUD_H
#define CLOUD_H


#include <QGraphicsPixmapItem>

class cloud:public QGraphicsPixmapItem
{
public:
    cloud(QGraphicsItem *parent = nullptr): QGraphicsPixmapItem(parent){
        setPixmap(QPixmap(":/new/prefix1/images/cloud.png").scaled(400,100));//云大小
    }
};

#endif // CLOUD_H
