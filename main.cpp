
#include "TXLib.h"

void drawButton(int x, int y, const char* text)
{
//x = 100;y = 30;
      txSetColor(TX_BLACK);
      txSetFillColor(TX_GRAY);
      Win32::RoundRect(txDC(), x+5, y+5, x+115, y+45, 30, 30);
      txSetColor(TX_BLACK);
      txSetFillColor(TX_WHITE);
      Win32::RoundRect(txDC(), x, y , x+110, y+40, 30, 30);
      txSetColor(TX_BLACK);
      txSelectFont("Times New Roman", 28);
      txDrawText(x,y,x+110,y+40, text);
}
int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC korpus = txLoadImage("Pictures/корпус1.bmp");
    HDC korpus2 = txLoadImage("Pictures/корпус2.bmp");
    HDC korpus3 = txLoadImage("Pictures/корпус3.bmp");

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
      txBegin();
      txSetColor(TX_WHITE);
      txSetFillColor(TX_GRAY);
      txClear();

      drawButton(100, 30, "Корпус"); //кнопка корпус
      drawButton(270, 30, "Колёса"); //кнопка колёса
      drawButton(440, 30, "Cтёкла"); //кнопка стёкла
      drawButton(630, 30, "Наклейки");// кнопка наклейки

      txTransparentBlt(txDC(), 300, 250, 459,394, korpus, 0, 0, TX_WHITE);
      txTransparentBlt(txDC(), 50, 100, 259,194, korpus2, 0, 0, TX_WHITE);
      txTransparentBlt(txDC(), 50, 100, 309,194, korpus3, 0, 0, TX_WHITE);

      txSleep(50);
      txEnd();

     }

    txDeleteDC(korpus);
    txDeleteDC(korpus2);
    txDeleteDC(korpus3);

    return 0;
}

