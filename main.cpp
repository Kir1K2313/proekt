
#include "TXLib.h"
struct Button
{
   int x;
   int y;
   const char* text;
};

//функция кнопки
void drawButton(Button btn)
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

bool click(Button btn)
{
 return (txMouseButtons() == 1 &&
        txMouseX() >= btn.x &&
        txMouseX() <= btn.x+110 &&
        txMouseY() >= btn.y &&
        txMouseY() <= btn.y+40);
}
struct Pictures
{
  int x;
  int y;
  HDC image;
  int w;
  int h;
  int w_scr;
  int h_scr;

};

void drawPicture(Pictures pct)
{
   Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.w_scr, pct.h_scr, pct.image, 0, 0, pct.w, pct.h, TX_WHITE);
}


int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

     //Массив кнопок
      Button btn[10];
      btn[0]={100, 30, "Корпус"};//кнопка корпус
      btn[1]={270, 30, "Колёса"};//кнопка колёса
      btn[2]={440, 30, "Cтёкла"};//кнопка стёкла
      btn[3]={630, 30, "Наклейки"};//кнопка наклейки

      Pictures menuPicture[12];
      menuPicture[0] = {50,100, txLoadImage("Pictures/корпус1.bmp"), 500, 154, 200, 100};
      menuPicture[1] = {50,200, txLoadImage("Pictures/корпус2.bmp"), 200, 180, 200, 150};
      menuPicture[2] = {50,300, txLoadImage("Pictures/корпус3.bmp"), 230, 150, 230, 150};

      menuPicture[3] = {50,100, txLoadImage("Pictures/наклейка1.bmp"),30, 39, 100, 70};
      menuPicture[4] = {50,200, txLoadImage("Pictures/наклейка2.bmp"),40, 50, 100, 70};
      menuPicture[5] = {50,300, txLoadImage("Pictures/наклейка3.bmp"),100, 70, 100, 70};

      menuPicture[6] = {50,100, txLoadImage("Pictures/колесо1.bmp"),85, 68, 100, 50};
      menuPicture[7] = {50,200, txLoadImage("Pictures/колесо2.bmp"),150, 100, 100, 50};
      menuPicture[8] = {50,300, txLoadImage("Pictures/колесо3.bmp"),150, 125, 100, 50};

    bool korpusvisible = false;
    bool nakleikavisible = false;
    bool kolesovisible = false;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
      txBegin();
      txSetColor(TX_WHITE);
      txSetFillColor(TX_GRAY);
      txClear();
      //Рисование кнопок
      for(int nk=0; nk<4; nk++)
      {
         drawButton(btn[nk]);
      }



      //Клик на кнопку корпус
      if(click(btn[0]))
      {
       korpusvisible = true;
       nakleikavisible = false;
       kolesovisible = false;
      }
      if(click(btn[1]))
      {
       korpusvisible = false;
       nakleikavisible = false;
       kolesovisible = true;
      }
      if(click(btn[3]))
      {
       korpusvisible = false;
       nakleikavisible = true;
       kolesovisible = false;
      }

      if(korpusvisible)
      {
         for(int npic=0; npic<= 2; npic++)
         {
          drawPicture(menuPicture[npic]);
         }
      }
      if(nakleikavisible)
      {
         for(int npic=3; npic<=5; npic++)
         {
          drawPicture(menuPicture[npic]);
         }
      }
      if(kolesovisible)
      {
         for(int npic=6; npic<=8; npic++)
         {
          drawPicture(menuPicture[npic]);
         }
      }

      txSleep(50);
      txEnd();

     }

    return 0;
}

