#include <QApplication>
#include <iostream>
#include "breakout.h"
using namespace std;
/*!
@brief main of all

the des of main goes here

@param nIndex 0: Update, 1:Install, 2:Erase
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Breakout brout;
    brout.resize(420,450);
    brout.show();
    return app.exec();
}

