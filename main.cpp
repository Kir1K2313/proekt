
#include "TXLib.h"
struct Button
{
   int x;
   int y;
   const char* text;
   string category;
};

//������� ������
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
  bool visible;
  string category;

};

void drawPicture(Pictures pct)
{
   if(pct.visible)
   {
        Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.w_scr, pct.h_scr, pct.image, 0, 0, pct.w, pct.h, TX_WHITE);
   }
}


int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    int COUNT_BTN = 5;
    int COUNT_PICTURES = 15;

     //������ ������
      Button btn[COUNT_BTN];
      btn[0]={60, 30, "������", "������"};//������ ������
      btn[1]={230, 30, "�����", "�����"};//������ �����
      btn[2]={400, 30, "�������", "�������"};//������ �������
      btn[3]={570, 30, "��������", "��������"};//������ ��������
      btn[4]={740, 30, "�������", "�������"};

      Pictures menuPicture[COUNT_PICTURES];
      menuPicture[0] = {50,100, txLoadImage("Pictures/������1.bmp"), 500, 154, 200, 80, false, "������"};
      menuPicture[1] = {50,170, txLoadImage("Pictures/������2.bmp"), 200, 180, 200, 180, false, "������"};
      menuPicture[2] = {50,300, txLoadImage("Pictures/������3.bmp"), 230, 150, 230, 150, false, "������"};

      menuPicture[3] = {50,100, txLoadImage("Pictures/��������1.bmp"),27, 38, 100, 70, false, "��������"};
      menuPicture[4] = {50,200, txLoadImage("Pictures/��������2.bmp"),41, 50, 100, 70, false, "��������"};
      menuPicture[5] = {50,300, txLoadImage("Pictures/��������3.bmp"),100, 70, 100, 70, false, "��������"};

      menuPicture[6] = {50,100, txLoadImage("Pictures/������1.bmp"),85, 68, 100, 80, false, "�����"};
      menuPicture[7] = {50,200, txLoadImage("Pictures/������2.bmp"),150, 100, 100, 80, false, "�����"};
      menuPicture[8] = {50,300, txLoadImage("Pictures/������3.bmp"),165, 170, 100, 80, false, "�����"};

      menuPicture[9] = {50,100, txLoadImage("Pictures/�������1.bmp"),348, 348, 100, 70, false, "�������"};
      menuPicture[10] = {50,200, txLoadImage("Pictures/�������2.bmp"),225, 225, 100, 70, false, "�������"};
      menuPicture[11] = {50,300, txLoadImage("Pictures/�������3.bmp"),360, 360, 100, 70, false, "�������"};

      menuPicture[12] = {50,100, txLoadImage("Pictures/�������1.bmp"),100, 110, 100, 70, false, "�������"};
      menuPicture[13] = {50,200, txLoadImage("Pictures/�������2.bmp"),193,  87, 100, 70, false, "�������"};
      menuPicture[14] = {50,300, txLoadImage("Pictures/�������3.bmp"),273, 107, 100, 70, false, "�������"};

      Pictures centralPicture[COUNT_PICTURES];
      centralPicture[0] = {350,200, txLoadImage("Pictures/������1.bmp"), 500, 154, 370, 150, false, "������"};
      centralPicture[1] = {350,200, txLoadImage("Pictures/������2.bmp"), 200, 180, 300, 180, false, "������"};
      centralPicture[2] = {350,200, txLoadImage("Pictures/������3.bmp"), 230, 150, 300, 180, false, "������"};

      centralPicture[3] = {250,200, txLoadImage("Pictures/��������1.bmp"),27, 38, 27, 38, false, "��������"};
      centralPicture[4] = {250,200, txLoadImage("Pictures/��������2.bmp"),41, 50, 100, 70, false, "��������"};
      centralPicture[5] = {250,200, txLoadImage("Pictures/��������3.bmp"),100, 70, 100, 70, false, "��������"};

      centralPicture[6] = {250,200, txLoadImage("Pictures/������1.bmp"),85, 68, 100, 80, false, "�����"};
      centralPicture[7] = {250,200, txLoadImage("Pictures/������2.bmp"),150, 100, 100, 80, false, "�����"};
      centralPicture[8] = {250,200, txLoadImage("Pictures/������3.bmp"),165, 170, 100, 80, false, "�����"};

      centralPicture[9] = {250,200, txLoadImage("Pictures/�������1.bmp"),348, 348, 100, 70, false, "�������"};
      centralPicture[10] = {250,200, txLoadImage("Pictures/�������2.bmp"),225, 225, 100, 70, false, "�������"};
      centralPicture[11] = {250,200, txLoadImage("Pictures/�������3.bmp"),360, 360, 100, 70, false, "�������"};

      centralPicture[12] = {250,200, txLoadImage("Pictures/�������1.bmp"),100, 110, 100, 70, false, "�������"};
      centralPicture[13] = {250,200, txLoadImage("Pictures/�������2.bmp"),193, 87, 100, 70, false, "�������"};
      centralPicture[14] = {250,200, txLoadImage("Pictures/�������3.bmp"),273, 107, 100, 70, false, "�������"};
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
      txBegin();
      txSetColor(TX_WHITE);
      txSetFillColor(TX_GRAY);
      txClear();
      //��������� ������
      for(int nk=0; nk<COUNT_BTN; nk++)
      {
         drawButton(btn[nk]);
      }

      for(int npic=0; npic < COUNT_PICTURES; npic++)
      {
         drawPicture(menuPicture[npic]);
      }
      for(int npic=0; npic < COUNT_PICTURES; npic++)
      {
         drawPicture(centralPicture[npic]);
      }
     //��������� �������� � ������ �� ��������� ����-��������
        for(int npic=0; npic < COUNT_PICTURES; npic++)
        {
            if(txMouseButtons() == 1 &&
            menuPicture[npic].visible &&
            txMouseX() >= menuPicture[npic].x &&
            txMouseX() <= menuPicture[npic].x + menuPicture[npic].w_scr &&
            txMouseY() >= menuPicture[npic].y &&
            txMouseY() <= menuPicture[npic].y + menuPicture[npic].h_scr)
            {
                for(int n1=0; n1 < COUNT_PICTURES; n1++)
                {
                    if(centralPicture[n1].category ==  centralPicture[npic].category)
                    {
                        centralPicture[n1].visible = false;
                    }
                }
                centralPicture[npic].visible = !centralPicture[npic].visible;
                txSleep(100);
            }

        }

     //��������� ����-�������� �� ��������� ������
      for(int nk=0; nk < COUNT_BTN; nk++)
      {
        if(click(btn[nk]))
         {
            for(int npic=0; npic < COUNT_PICTURES; npic++)
            {
               menuPicture[npic].visible = false;
               if(menuPicture[npic].category == btn[nk].category)
               {
                 menuPicture[npic].visible = true;
               }
            }
         }
      }




      txSleep(50);
      txEnd();

     }

     for(int npic=0; npic < COUNT_PICTURES; npic++)
     {
        txDeleteDC(menuPicture[npic].image);
     }

     for(int npic=0; npic < COUNT_PICTURES; npic++)
     {
        txDeleteDC(centralPicture[npic].image);
     }

    return 0;
}

