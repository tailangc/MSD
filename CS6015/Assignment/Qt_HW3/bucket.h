#ifndef BUCKET_H
#define BUCKET_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <QGraphicsScene>



class bucket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    bucket(QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // BUCKET_H
