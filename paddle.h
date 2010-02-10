#ifndef PADDLE_H
#define PADDLE_H

#include <QImage>
#include <QRect>

class Paddle
{

  public:
    Paddle();
    ~Paddle();

  public:
    void resetState();
    void moveLeft(int);
    void moveRight(int);
    QRect getRect();
    QImage & getImage();

  private:
    QImage image;
    QRect rect;

};

#endif

