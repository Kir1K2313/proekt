
#include "TXLib.h"

struct button
{
   int x;
   int y;
   const char* text;
};

void drawButton(button btn)
{
//x = 100;y = 30;
      txSetColor(TX_BLACK);
      txSetFillColor(TX_GRAY);
      Win32::RoundRect(txDC(), btn.x+5, btn.y+5, btn.x+115, btn.y+45, 30, 30);
      txSetColor(TX_BLACK);
      txSetFillColor(TX_WHITE);
      Win32::RoundRect(txDC(), btn.x, btn.y , btn.x+110, btn.y+40, 30, 30);
      txSetColor(TX_BLACK);
      txSelectFont("Times New Roman", 28);
      txDrawText(btn.x,btn.y,btn.x+110,btn.y+40, btn.text);
}

int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC korpus = txLoadImage("Pictures/������1.bmp");
    HDC korpus2 = txLoadImage("Pictures/������2.bmp");
    HDC korpus3 = txLoadImage("Pictures/������3.bmp");

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
      txBegin();
      txSetColor(TX_WHITE);
      txSetFillColor(TX_GRAY);
      txClear();


      button btn[10];
      btn[0]={100, 30, "������"};//������ ������
      btn[1]={270, 30, "�����"};//������ �����
      btn[2]={440, 30, "C����"};//������ �����
      btn[3]={630, 30, "��������"};//������ ��������

      for(int nk=0; nk<4; nk++)
      {
         drawButton(btn[nk]);
      }
      /*
      drawButton(btn[0]);
      drawButton(btn[1]);
      drawButton(btn[2]);
      drawButton(btn[3]);
      */
      //txTransparentBlt(txDC(), 300, 250, 459,394, korpus, 0, 0, TX_WHITE);
     // txTransparentBlt(txDC(), 50, 100, 459,394, korpus2, 0, 0, TX_WHITE);
      //txTransparentBlt(txDC(), 50, 100, 509,394, korpus3, 0, 0, TX_WHITE);


      if(txMouseButtons() == 1 &&
        txMouseX() >= btn[0].x &&
        txMouseX() <= btn[0].x+110 &&
        txMouseY() >= btn[0].y &&
        txMouseY() <= btn[0].y+40)
      {
        txTransparentBlt(txDC(), 300, 250, 459,394, korpus, 0, 0, TX_WHITE);
      }

      txSleep(50);
      txEnd();

     }

    txDeleteDC(korpus);
    txDeleteDC(korpus2);
    txDeleteDC(korpus3);

    return 0;
}

