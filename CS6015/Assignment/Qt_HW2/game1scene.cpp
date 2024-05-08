#include "game1scene.h"
#include "cloud.h"
#include "droplet.h"

game1scene::game1scene(QObject *parent):QGraphicsScene(parent) {

    QPixmap background(":/new/prefix1/images/background.jpg");
    background = background.scaled(910, 512, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setBackgroundBrush(background);

    setSceneRect(0,0,910, 512);

    //add the bucket
    bucket *bucketItem = new bucket();
    bucketItem->setPos((910 - bucketItem->pixmap().width()) / 2, 512 - bucketItem->pixmap().height()); // Position at bottom center
    bucketItem->setFlag(QGraphicsItem::ItemIsFocusable);
    bucketItem->setFocus();
    addItem(bucketItem);

    QList<cloud*> clouds;

    //add 3 cloud on different pos
    for (int i = 0; i < 3; ++i) {
        cloud* cloudItem = new cloud();
        int x_position = 100 + i * 250 - 50 ;
        cloudItem->setPos(x_position, 7);
        addItem(cloudItem);
        clouds.append(cloudItem);
    }


    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this, clouds]() {
        if (!clouds.isEmpty()) {
            int cloudIndex = rand() % clouds.size();  // 随机选择一朵云
            cloud* selectedCloud = clouds.at(cloudIndex);
            int dropletX = selectedCloud->x() + rand() % selectedCloud->pixmap().width();
            droplet* droplets = new droplet();
            droplets->setPos(dropletX, selectedCloud->y() + selectedCloud->pixmap().height());
            addItem(droplets);
        }

    });

     timer->start(300);

}
