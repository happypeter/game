#include "breakout.h"
#include <QPainter>
#include <QApplication>

Breakout::Breakout(QWidget *parent)
    : QWidget(parent)
{

  x = 0;
  gameOver = FALSE;
  gameWon = FALSE;
  paused = FALSE;
  gameStarted = FALSE;
  ball = new Ball();
  paddle = new Paddle();


  int k = 0;
  for (int i=0; i<5; i++) {
    for (int j=0; j<6; j++) {
      bricks[k] = new Brick(j*60+30, i*20+50);
      k++; 
    }
  }
}

Breakout::~Breakout() {
 delete ball;
 delete paddle;
 for (int i=0; i<30; i++) {
   delete bricks[i];
 }
}

void Breakout::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  if (gameOver) {
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width("Game Over");

    painter.setFont(font);
    int h = height();
    int w = width();

    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, "Game Over");
  }
  else if(gameWon) {
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width("Victory");

    painter.setFont(font);
    int h = height();
    int w = width();

    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, "Victory");
  }
  else {
    painter.drawImage(ball->getRect(), 
        ball->getImage());
    painter.drawImage(paddle->getRect(), 
        paddle->getImage());

    for (int i=0; i<30; i++) {
        if (!bricks[i]->isDestroyed()) 
          painter.drawImage(bricks[i]->getRect(), 
              bricks[i]->getImage());
    }
  }
}

void Breakout::timerEvent(QTimerEvent *event)
{
  ball->autoMove();
  checkCollision();
  repaint();
}



void Breakout::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
       {  
         int x = paddle->getRect().x();
        for (int i=1; i<=20; i++)
          paddle->moveLeft(x--);
        break;
       }
    case Qt::Key_Right:
        { 
          int x = paddle->getRect().x();
          for (int i=1; i<=20; i++)
            paddle->moveRight(x++);
        }
        break;
    case Qt::Key_P:
        { 
          pauseGame();
        }
        break;
    case Qt::Key_Space:
        {
          startGame();
        }
        break;
    case Qt::Key_Escape:
        {
          qApp->exit();
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Breakout::startGame()
{ 
  if (!gameStarted) {
    ball->resetState();
    paddle->resetState();

    for (int i=0; i<30; i++) {
      bricks[i]->setDestroyed(FALSE);
    }
    gameOver = FALSE; 
    gameWon = FALSE; 
    gameStarted = TRUE;
    timerId = startTimer(8);//the speed of the ball
  }
}

void Breakout::pauseGame()
{
  if (paused) {
    timerId = startTimer(10);
    paused = FALSE;
  } else {
    paused = TRUE;
    killTimer(timerId); 
   }
}

void Breakout::stopGame()
{
  killTimer(timerId);    
  gameOver = TRUE;      
  gameStarted = FALSE;
}

void Breakout::victory()
{
  killTimer(timerId);
  gameWon = TRUE;  
  gameStarted = FALSE;
}

void Breakout::checkCollision()
{

  if (ball->getRect().bottom() > 400)
    stopGame(); 

  for (int i=0, j=0; i<30; i++) {
    if (bricks[i]->isDestroyed()) {
      j++;
    }
    if (j==30) 
      victory();
  }

  if ((ball->getRect()).intersects(paddle->getRect())) {

    int paddleLPos = paddle->getRect().left();  
    int ballLPos = ball->getRect().left();   

    int first = paddleLPos + 8;
    int second = paddleLPos + 16;
    int third = paddleLPos + 24;
    int fourth = paddleLPos + 32;

    if (ballLPos < first) {
      ball->setXDir(-1);
      ball->setYDir(-1);
    }

    if (ballLPos >= first && ballLPos < second) {
      ball->setXDir(-1);
      ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos >= second && ballLPos < third) {
       ball->setXDir(0);
       ball->setYDir(-1);
    }

    if (ballLPos >= third && ballLPos < fourth) {
       ball->setXDir(1);
       ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos > fourth) {
      ball->setXDir(1);
      ball->setYDir(-1);
    }


  }


  for (int i=0; i<30; i++) {
    if ((ball->getRect()).intersects(bricks[i]->getRect())) {

      int ballLeft = ball->getRect().left();  
      int ballHeight = ball->getRect().height(); 
      int ballWidth = ball->getRect().width();
      int ballTop = ball->getRect().top();  

      QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
      QPoint pointLeft(ballLeft - 1, ballTop);  
      QPoint pointTop(ballLeft, ballTop -1);
      QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);  

      if (!bricks[i]->isDestroyed()) {
        if(bricks[i]->getRect().contains(pointRight)) {
           ball->setXDir(-1);
        } 

        else if(bricks[i]->getRect().contains(pointLeft)) {
           ball->setXDir(1);
        } 

        if(bricks[i]->getRect().contains(pointTop)) {
           ball->setYDir(1);
        } 

        else if(bricks[i]->getRect().contains(pointBottom)) {
           ball->setYDir(-1);
        } 

        bricks[i]->setDestroyed(TRUE);
      }
    }
  }

}

