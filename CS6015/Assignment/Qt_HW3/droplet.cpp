#include "droplet.h"
#include "game1scene.h"
// #include <QRandomGenerator>


droplet::droplet(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {

    setPixmap(QPixmap(":/new/prefix1/images/water.gif").scaled(30,30));
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this ,&droplet::move);
    timer->start(50);
}



void droplet::move(){
    if (game1scene::drops_collected >= 20) {
        drop_speed = 16;
    } else if (game1scene::drops_collected >= 15) {
        drop_speed = 8;
    } else if (game1scene::drops_collected >= 10) {
        drop_speed = 4;
    } else if (game1scene::drops_collected >= 5) {
        drop_speed = 2;
    }

    setPos(x(),y() + drop_speed);

    QList<QGraphicsItem*> colliding_item = collidingItems();
    for(QGraphicsItem* item : colliding_item){
        bucket* bucketItem = dynamic_cast<bucket*>(item);
        if(bucketItem){
            int randomIndex = rand() % 2;
            if(randomIndex == 0){
                game1scene::soundEffect1 -> play();
            }
            else{
                game1scene::soundEffect2 -> play();
            }
            scene()->removeItem(this);
            // game1scene::soundEffect1 -> play();
            game1scene::drops_collected ++;
            game1scene::game_score += 5;
            deleteLater();
        }
    }
    // if(y()> game1scene::windowHeight){
    //     scene()->removeItem(this);
    //     delete this;
    // }

}
