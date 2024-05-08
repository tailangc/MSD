#include "game1scene.h"
#include "cloud.h"
#include "droplet.h"
#include <iostream>
#include <QLabel>
#include <QGraphicsProxyWidget>


int game1scene::drops_collected = 0;
int game1scene::game_score = 0;
int game1scene::missed_droplets = 0;
int game1scene::windowHeight = 512;
int game1scene::windowWidth = 910;
QMediaPlayer* game1scene::soundEffect1 = new QMediaPlayer();
QMediaPlayer* game1scene::soundEffect2 = new QMediaPlayer();
QMediaPlayer* game1scene::missingEffect = new QMediaPlayer();

game1scene::game1scene(QObject *parent):QGraphicsScene(parent) {

    QTimer* scoreUpdateTimer = new QTimer(this);
    connect(scoreUpdateTimer, &QTimer::timeout, this, &game1scene::updateLabels);


    pointsLabel = new QLabel();
    missedLabel = new QLabel();
    pointsLabel->setFont(QFont("Arial", 16));
    missedLabel->setFont(QFont("Arial", 16));

    // Set initial text for the labels
    updateLabels();

    // Add labels to the scene
    QGraphicsProxyWidget *dropsCollectedProxy = addWidget(pointsLabel);
    dropsCollectedProxy->setPos(70, 80);

    QGraphicsProxyWidget *missedDropletsProxy = addWidget(missedLabel);
    missedDropletsProxy->setPos(70, 100);

    scoreUpdateTimer->start(100);

    // soundEffect1 = new QMediaPlayer(this);
    QAudioOutput* audioOutput1 = new QAudioOutput;
    QAudioOutput* audioOutput2 = new QAudioOutput;
    QAudioOutput* missingOutput = new QAudioOutput;
    soundEffect1->setAudioOutput(audioOutput1);
    soundEffect2->setAudioOutput(audioOutput2);
    missingEffect->setAudioOutput(missingOutput);
    soundEffect1->setSource(QUrl("qrc:/new/prefix1/RaningMen.m4a"));
    soundEffect2->setSource(QUrl("qrc:/new/prefix2/HALLELUJAHH.m4a"));
    missingEffect->setSource(QUrl("qrc:/new/prefix3/MissingEffect.m4a"));
    audioOutput1->setVolume(50);
    audioOutput2->setVolume(50);
    missingOutput->setVolume(50);



    QPixmap background(":/new/prefix1/images/background.jpg");
    background = background.scaled(windowWidth, windowHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setBackgroundBrush(background);


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

    QTimer* missedDropletTimer = new QTimer(this);
    connect(missedDropletTimer, &QTimer::timeout, this, &game1scene::checkMissedDroplets);
    missedDropletTimer->start(300);


    //generating droplets
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




     QTimer* gameTimer = new QTimer(this);
     connect(gameTimer, &QTimer::timeout, [this]() {

         // std::cout << "Current missed droplets: " << missed_droplets << "\n";
         if (game_score >= 150) {
             winningGame();
         }

         if (missed_droplets >= 5) {
             loosingGame();
         }
     });

     gameTimer->start(100);



}

void game1scene::checkMissedDroplets(){
    // std::cout << "check function being called" << "\n";
    foreach(QGraphicsItem *item, items()) {
        droplet* dropletItem = dynamic_cast<droplet*>(item);
        if (dropletItem) {

            // Check missing by reaching out of bound
            if (dropletItem->y() > windowHeight) {
                missingEffect->play();
                missed_droplets++;
                // scene()->removeItem(this);
                // delete this;
            }
        }
    }
}


void game1scene::winningGame(){
    int value = 1;
    emit winningSignal(value);
    std::cout << "Congradulations! you win the game!" << "\n";
        //TODO: winning game widget
}

void game1scene::loosingGame(){
    int value = 0;
    emit loosingSignal(value);
        std::cout << "You lose the game" << "\n";
        //TODO: loosing game widget

}

int game1scene::gameLevel(std::string level){
    if (level == "easy"){
        return 100;
    }
    else if (level == "medium"){
        return 200;
    }
    else {
        return 300;
    }
}



void game1scene::updateLabels()
{
    pointsLabel->setText("Points: " + QString::number(game_score));
    missedLabel->setText("Missed Droplets: " + QString::number(missed_droplets));
}
