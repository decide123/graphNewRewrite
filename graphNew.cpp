#include "TXLib.h"

const double Step = 0.02;
const double xMAX =  10;
const double xMIN = -10;
const COLORREF netBGcolor = RGB (6,   4, 102);
const COLORREF netLNcolor = RGB (138, 6, 255);

struct Button
    {
    double (*mathFunc) (double x);
    double xPosB;
    double yPosB;
    double sizeX;
    double sizeY;
    };

void drawGraph (double (*mathFunc) (double x));
double linear (double x);
void drawCartesian (double x, double y);
void drawPolar     (double rho, double phi);

void graphTypeChoice (std::vector <Button> *buttons);
bool mouseDetection (std::vector  <Button> *buttons, int i);
void buttonPlacement (std::vector <Button> *buttons);
void drawButtons (std::vector <Button> *buttons);
void drawNet (COLORREF netBGcolor, COLORREF netLNcolor);



int main()
    {
    txCreateWindow (1920, 900);

    Button buttonsOld[1] = {{linear, 0, 0, 100, 20}};

    std::vector <Button> buttons;

    for (int i = 0; i < sizeof (buttonsOld)/sizeof (Button); i++)
        {
        buttons.push_back (buttonsOld[i]);
        }

        drawNet     (netBGcolor, netLNcolor);

    while(!GetAsyncKeyState (VK_ESCAPE))
        {
        drawButtons (&buttons);
        graphTypeChoice (&buttons);
        }

    return 0;
    }

void drawGraph (double (*mathFunc) (double x))
    {
    double x = xMIN;

    txMessageBox ("123");

    while (x < xMAX)
        {
        drawPolar (x, mathFunc (x));
        x += Step;
        }

    txMessageBox ("1234");
    txSleep (100);
    }

double linear (double x)
    {
    double y = x;

    return y;
    }

void drawCartesian (double x, double y)
    {
    x =  50*x + txGetExtentX()/2;
    y = -50*y + txGetExtentY()/2;

    txCircle (x, y, 1);
    }

void drawPolar     (double rho, double phi)
    {
    double x =  50*rho*cos (phi) + txGetExtentX()/2;;
    double y = -50*rho*sin (phi) + txGetExtentY()/2;

    txCircle (x, y, 1);
    printf ("drawing\n");
    }

void graphTypeChoice (std::vector <Button> *buttons) //сделать членом класса
    {
    int sizeOfbuttons = buttons -> size();

    for (int i = 0; i < sizeOfbuttons; i++)
        {
        if (mouseDetection (buttons, i))
            {
            drawGraph (buttons -> at(i).mathFunc);
            }
        }
    }

bool mouseDetection (std::vector <Button> *buttons, int i)
    {
    txRectangle

    if (txMouseX() > buttons -> at(i).xPosB  && txMouseX() < buttons -> at(i).xPosB + buttons -> at(i).sizeX
     && txMouseY() > buttons -> at(i).yPosB  && txMouseY() > buttons -> at(i).yPosB + buttons -> at(i).sizeY
     && GetAsyncKeyState (MK_LBUTTON))
        {
        printf ("button pressed\n");
        return true;
        }

    else   return false;
    }

void drawNet (COLORREF netBGcolor, COLORREF netLNcolor)
    {
    txSetColor     (netLNcolor);
    txSetFillColor (netBGcolor);

    txRectangle (50*(txGetExtentX()/1920), 50*(txGetExtentY()/1080), txGetExtentX() - 50*(txGetExtentX()/1920), txGetExtentY() - 50*(txGetExtentY()/1920));

    int xLine = 50*(txGetExtentX()/1920);
    while (xLine < txGetExtentX() - 50*(txGetExtentX()/1920))
        {
        txLine (xLine, 50*(txGetExtentY()/1920), xLine, txGetExtentY() - 50*(txGetExtentY()/1080));
        xLine += 50*(txGetExtentX()/1920);
        }

    int yLine = 50*(txGetExtentY()/1080);
    while (yLine < txGetExtentY() - 50*(txGetExtentY()/1080))
        {
        txLine (50*(txGetExtentX()/1920), yLine, txGetExtentX() - 50*(txGetExtentX()/1920), yLine);
        yLine += 50*(txGetExtentX()/1920);
        }

    }

void drawButtons (std::vector <Button> *buttons)
    {
    int sizeOfbuttons = buttons -> size();

    buttonPlacement (buttons);

    for (int i = 0; i < sizeOfbuttons; i++)
        {
        txSetFillColor (RGB (0,   0,   0  ));
        txSetColor     (RGB (255, 255, 255));

        txRectangle (buttons -> at(i).xPosB,                          buttons -> at(i).yPosB,
                     buttons -> at(i).xPosB + buttons -> at(i).sizeX, buttons -> at(i).yPosB + buttons -> at(i).sizeY);
        }
    }




void buttonPlacement (std::vector <Button> *buttons)
    {
    double xPos = 10;
    double yPos = 10;
    int sizeOfbuttons = buttons -> size();

    for (int i = 0; i < sizeOfbuttons; i++)
        {
        if (buttons -> at(i).xPosB == 0)
            {
            buttons -> at(i).xPosB = xPos;
            buttons -> at(i).yPosB = yPos;

            xPos = xPos + 1.5*buttons -> at(i).sizeX;

            if (xPos + 1.5*buttons -> at(i).sizeX > txGetExtentX())
                {
                yPos = yPos + 1.5*buttons -> at(i).sizeY;
                xPos = 10;
                }
            }
        }
    }
