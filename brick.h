#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>

class Brick
{

  public:
    Brick(int, int);
    ~Brick();

  public:
    void resetState();
    bool isDestroyed();
    void setDestroyed(bool);
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();

  private:
    QImage image;
    QRect rect;
    int position;
    bool destroyed;

};

#endif

