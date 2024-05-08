#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include <QVBoxLayout>

#include "bucket.h"
#include "droplet.h"



class game1scene : public QGraphicsScene
{
    Q_OBJECT

public:
    QLabel *pointsLabel;
    QLabel *missedLabel;

    game1scene(QObject *parent = nullptr);
    void checkMissedDroplets();
    void winningGame();
    void loosingGame();
    int gameLevel(std::string level);
    void updateLabels();

    static int windowWidth;
    static int windowHeight;
    static int drops_collected;
    static int game_score;
    static int missed_droplets;
    static QMediaPlayer* soundEffect1;
    static QMediaPlayer* soundEffect2;
    static QMediaPlayer* missingEffect;

signals:
    void loosingSignal(int value);
    void winningSignal(int value);


};

#endif // GAME1SCENE_H
