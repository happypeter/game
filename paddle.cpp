#include "paddle.h"


Paddle::Paddle()
{
  image.load("paddle.png");

  rect = image.rect();
  resetState();
}

Paddle::~Paddle()
{
 printf("paddle deleted\n");
}

void Paddle::moveLeft(int left)
{
  if (rect.left() >= 2)
    rect.moveTo(left, rect.top());
}

void Paddle::moveRight(int right)
{
  if (rect.right() <= 298)
    rect.moveTo(right, rect.top());
}

void Paddle::resetState()
{
  rect.moveTo(200, 380);
}

QRect Paddle::getRect()
{
  return rect;
}

QImage & Paddle::getImage()
{
  return image;
}

