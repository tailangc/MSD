#include "bucket.h"

bucket::bucket(QGraphicsItem *parent):QGraphicsPixmapItem(parent){

    setPixmap(QPixmap(":/new/prefix1/images/bucket.png").scaled(150,150));
    // setFlag(QGraphicsItem::ItemIsFocusable);
    // setFocus();
}


void bucket::keyPressEvent(QKeyEvent *event){
    int stepSize = 10;

    if(event->key()== Qt::Key_Left){
        setPos(x()- stepSize,y());
    }else if ( event->key() == Qt::Key_Right){
        if(x() + pixmap().width() + stepSize <= scene()->width())
        setPos(x()+ stepSize,y());
    }
}
