
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
    int COUNT_PICTURES = 23;
    int select = -1;
    bool mouse_free = false;
    int nCentralPictures = 0;

    char str[100];


     //������ ������
      Button btn[COUNT_BTN];
      btn[0]={60, 30, "������", "������"};//������ ������
      btn[1]={230, 30, "�����", "�����"};//������ �����
      btn[2]={400, 30, "�������", "�������"};//������ �������
      btn[3]={570, 30, "��������", "��������"};//������ ��������
      btn[4]={740, 30, "�������", "�������"};
      //������ ��������
      Pictures menuPicture[COUNT_PICTURES];
      menuPicture[0] = {50,100, txLoadImage("Pictures/������1.bmp"), 500, 154, 300, 100, false, "������"};
      menuPicture[1] = {50,170, txLoadImage("Pictures/������2.bmp"), 200, 180, 280, 220, false, "������"};
      menuPicture[2] = {50,300, txLoadImage("Pictures/������3.bmp"), 230, 150, 280, 150, false, "������"};
      menuPicture[3] = {50,400, txLoadImage("Pictures/������4.bmp"), 431, 117, 280, 80, false, "������"};
      menuPicture[4] = {50,445, txLoadImage("Pictures/������5.bmp"), 500, 500, 330, 230, false, "������"};

      menuPicture[5] = {50,100, txLoadImage("Pictures/��������1.bmp"),27, 38, 100, 70, false, "��������"};
      menuPicture[6] = {50,200, txLoadImage("Pictures/��������2.bmp"),41, 50, 100, 70, false, "��������"};
      menuPicture[7] = {50,300, txLoadImage("Pictures/��������3.bmp"),100, 70, 100, 70, false, "��������"};
      menuPicture[8] = {50,400, txLoadImage("Pictures/��������4.bmp"),225, 225, 100, 70, false, "��������"};
      menuPicture[9] = {50,500, txLoadImage("Pictures/��������5.bmp"),225, 225, 100, 70, false, "��������"};

      menuPicture[10] = {50,100, txLoadImage("Pictures/������1.bmp"),85, 68, 100, 80, false, "�����"};
      menuPicture[11] = {50,200, txLoadImage("Pictures/������2.bmp"),150, 100, 100, 80, false, "�����"};
      menuPicture[12] = {50,300, txLoadImage("Pictures/������3.bmp"),165, 170, 100, 80, false, "�����"};
      menuPicture[13] = {50,400, txLoadImage("Pictures/������4.bmp"),400, 392, 100, 80, false, "�����"};
      menuPicture[14] = {50,500, txLoadImage("Pictures/������5.bmp"),260, 260, 100, 80, false, "�����"};

      menuPicture[15] = {50,100, txLoadImage("Pictures/�������1.bmp"),348, 348, 100, 70, false, "�������"};
      menuPicture[16] = {50,200, txLoadImage("Pictures/�������2.bmp"),225, 225, 100, 70, false, "�������"};
      menuPicture[17] = {50,300, txLoadImage("Pictures/�������3.bmp"),360, 360, 100, 70, false, "�������"};
      menuPicture[18] = {50,400, txLoadImage("Pictures/�������4.bmp"),225, 225, 100, 70, false, "�������"};
      menuPicture[19] = {50,500, txLoadImage("Pictures/�������5.bmp"),800, 800, 100, 70, false, "�������"};

      menuPicture[20] = {50,100, txLoadImage("Pictures/�������1.bmp"),100, 110, 100, 70, false, "�������"};
      menuPicture[21] = {50,200, txLoadImage("Pictures/�������2.bmp"),193,  87, 100, 70, false, "�������"};
      menuPicture[22] = {50,300, txLoadImage("Pictures/�������3.bmp"),273, 107, 100, 70, false, "�������"};
      //������ �������� � ������
      Pictures centralPicture[1000];

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
      for(int npic=0; npic < nCentralPictures; npic++)
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
                while(txMouseButtons() == 1)
                {
                    txSleep(20);
                }
                  centralPicture[nCentralPictures] = {250,
                                                      200,
                                                      menuPicture[npic].image,
                                                      menuPicture[npic].w,
                                                      menuPicture[npic].h,
                                                      menuPicture[npic].w_scr,
                                                      menuPicture[npic].h_scr,
                                                      menuPicture[npic].visible,
                                                      menuPicture[npic].category};
                  nCentralPictures++;
            }
        }

     //��������� ����-�������� �� ��������� ������
      for(int nk=0; nk < COUNT_BTN; nk++)
      {
        if(click(btn[nk]))
         {
            while(txMouseButtons() == 1)
            {
                txSleep(20);
            }
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



      //����� ����������� ������

        for(int npic=0; npic < COUNT_PICTURES; npic++)
        {
         if(txMouseButtons() == 1 &&
            centralPicture[npic].visible &&
            txMouseX() >= centralPicture[npic].x &&
            txMouseX() <= centralPicture[npic].x + centralPicture[npic].w_scr &&
            txMouseY() >= centralPicture[npic].y &&
            txMouseY() <= centralPicture[npic].y + centralPicture[npic].h_scr)
            {
                select = npic;
                mouse_free = false;
            }
        }

    sprintf(str, "vibor = %d   kol = %d", select, nCentralPictures);
    txTextOut(0, 0, str);

      //������������ ��������� ����������� �������� ��������
      if(select >= 0)
      {
         if(GetAsyncKeyState(VK_RIGHT)) centralPicture[select].x += 3;
         if(GetAsyncKeyState(VK_LEFT))  centralPicture[select].x -= 3;
         if(GetAsyncKeyState(VK_UP))    centralPicture[select].y -= 3;
         if(GetAsyncKeyState(VK_DOWN))  centralPicture[select].y += 3;

         if(GetAsyncKeyState(VK_OEM_PLUS))
         {
            centralPicture[select].w_scr = centralPicture[select].w_scr * 1.02;
            centralPicture[select].h_scr = centralPicture[select].h_scr * 1.02;
         }

         if(GetAsyncKeyState(VK_OEM_MINUS))
         {
            centralPicture[select].w_scr = centralPicture[select].w_scr * 0.98;
            centralPicture[select].h_scr = centralPicture[select].h_scr * 0.98;
         }
      }

      //������������ ��������� ����������� �������� ������
      if(select >= 0)
      {
          if(txMouseButtons() == 1 && !mouse_free)
          {
            centralPicture[select].x  = txMouseX() - centralPicture[select].w_scr/2;
            centralPicture[select].y  = txMouseY() - centralPicture[select].h_scr/2;
          }
          else
          {
                if(txMouseButtons() != 1)
                {
                  mouse_free = true;
                }
          }
      }
     // �������� ��������
     if(select>=0 && GetAsyncKeyState(VK_DELETE))
     {
         centralPicture[select] = centralPicture[nCentralPictures - 1];
         nCentralPictures--;
         select=-1;
         mouse_free = true;

     }

      txSleep(50);
      txEnd();

     }

     for(int npic=0; npic < COUNT_PICTURES; npic++)
     {
        txDeleteDC(menuPicture[npic].image);
     }


    return 0;
}

