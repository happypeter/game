#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include <QWidget>
#include <QKeyEvent>

class Breakout : public QWidget
{
  Q_OBJECT

  public:
    Breakout(QWidget *parent = 0);
    ~Breakout();

  protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();

  private:
    int x;
    int timerId;
    Ball *ball;
    Paddle *paddle;
    Brick * bricks[30];
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;

};

#endif

