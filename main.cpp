#include "TXLib.h"
#include <iostream>
#include <fstream>
#include "dirent.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct Button
{
   int x;
   int y;
   const char* text;
   string category;
};

//??????? ??????
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
  string adress;
  HDC image;
  int w;
  int h;
  int w_scr;
  int h_scr;
  string category;
  bool visible;
};

void drawPicture(Pictures pct)
{
   if(pct.visible)
   {
        Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.w_scr, pct.h_scr, pct.image, 0, 0, pct.w, pct.h, TX_WHITE);
   }
}

int get_w(string adress)
{
   FILE *f1 = fopen(adress.c_str(), "rb");
   unsigned char headerinfo[54];
   fread(headerinfo, sizeof(unsigned char),54,f1);

   int w = *(int*)&headerinfo[18];
   return w;
}

int get_h(string adress)
{
   FILE *f1 = fopen(adress.c_str(), "rb");
   unsigned char headerinfo[54];
   fread(headerinfo, sizeof(unsigned char),54,f1);

   int h = *(int*)&headerinfo[22];
   return h;
}

int readFromDir(string adress, Pictures menuPicture[], int COUNT_PICTURES)
{
     DIR *dir;
     struct dirent *ent;
     int lastY = 100;
     if ((dir = opendir (adress.c_str())) != NULL)
        {
            while ((ent = readdir (dir))  != NULL)
            {
                if((string)ent->d_name != "." && (string)ent->d_name != "..")
                {
                    menuPicture[COUNT_PICTURES].y = lastY;
                    menuPicture[COUNT_PICTURES].adress = adress + (string)ent->d_name;
                    COUNT_PICTURES ++;
                    lastY += 100;
                }
            }
            closedir (dir);

        }
      return COUNT_PICTURES;
}


string runFileDialog(bool isSave)
{
   string fileName = "";
   OPENFILENAME ofn;
   TCHAR szFile[260] = {0};

   ZeroMemory(&ofn, sizeof(ofn));
   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = txWindow();
   ofn.lpstrFile = szFile;
   ofn.nMaxFile = sizeof(szFile);
   ofn.lpstrFilter = ("Text\0*.TXT\0");
   ofn.nFilterIndex = 1;
   ofn.lpstrFileTitle = NULL;
   ofn.nMaxFileTitle = 0;
   ofn.lpstrInitialDir = NULL;
   ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

   if (isSave)
   {
      if (GetSaveFileName(&ofn) == TRUE)
      {
         fileName = ofn.lpstrFile;

         if (fileName.find(".txt") > 1000)
         {
           fileName =  fileName + ".txt";
         }
      }
   }
   else
   {
      if (GetOpenFileName(&ofn) == TRUE)
      {
         fileName = ofn.lpstrFile;
      }
   }

   return fileName;
}

const int COUNT_BTN = 7;
const int BTN_SAVE  = COUNT_BTN - 2;
const int BTN_LOAD  = COUNT_BTN - 1;
int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    int COUNT_BTN = 7;
    int COUNT_PICTURES = 0;
    int select = -1;
    bool mouse_free = false;
    int nCentralPictures = 0;
    string PAGE = "????";

    char str[100];


     //?????? ??????
      Button btn[COUNT_BTN];
      btn[0]={60, 30, "??????", "??????"};//?????? ??????
      btn[1]={230, 30, "??????", "??????"};//?????? ??????
      btn[2]={400, 30, "???????", "???????"};//?????? ???????
      btn[3]={570, 30, "????????", "????????"};//?????? ????????
      btn[4]={740, 30, "???????", "???????"};
      btn[5]={1010, 30, "?????????", ""};
      btn[6]={1010, 80, "?????????", ""};


      //?????? ????????
      Pictures menuPicture[100];

      //?????? ???????? ? ??????
      Pictures centralPicture[100];

      COUNT_PICTURES = readFromDir("Pictures/??????/",menuPicture,COUNT_PICTURES);
      COUNT_PICTURES = readFromDir("Pictures/????????/",menuPicture,COUNT_PICTURES);
      COUNT_PICTURES = readFromDir("Pictures/??????/",menuPicture,COUNT_PICTURES);
      COUNT_PICTURES = readFromDir("Pictures/???????/",menuPicture,COUNT_PICTURES);
      COUNT_PICTURES = readFromDir("Pictures/???????/",menuPicture,COUNT_PICTURES);



    for(int npic=0; npic < COUNT_PICTURES; npic++)
    {
        menuPicture[npic].x = 50;

        menuPicture[npic].image = txLoadImage(menuPicture[npic].adress.c_str());

        menuPicture[npic].w = get_w(menuPicture[npic].adress);
        menuPicture[npic].h = get_h(menuPicture[npic].adress);

        menuPicture[npic].w_scr = menuPicture[npic].w;
        menuPicture[npic].h_scr = menuPicture[npic].h;


        int pos1 = menuPicture[npic].adress.find("/");
        int pos2 = menuPicture[npic].adress.find("/", pos1+1);
        menuPicture[npic].category = menuPicture[npic].adress.substr(pos1+1, pos2-pos1-1);

        menuPicture[npic].visible = false;

    }

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
      txSetColor(TX_WHITE);
      txSetFillColor(TX_GRAY);
      txClear();

      if(PAGE =="????")
        {
            txSetFillColor (TX_GRAY);
            txRectangle(0,0,1200,800);
            txSetFillColor (TX_GRAY);
            txRectangle(500,100,700,150);
            txDrawText(500,100,700,150,"??????");

            if(txMouseX() >= 500 && txMouseY()>= 100 &&
               txMouseX() <= 700 && txMouseY()<= 150 &&
               txMouseButtons() == 1)
            {
               PAGE="????????";
            }

               txRectangle(500,200,700,250);
               txDrawText(500,200,700,250,"?????");

            if(txMouseX() >= 500 && txMouseY()>= 200 &&
               txMouseX() <= 700 && txMouseY()<= 250 &&
               txMouseButtons() == 1)
            {
               return 0;
            }

        }
    if(PAGE == "????????")
    {
      txBegin();

      //????????? ??????
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

        //????????? ???????? ? ?????? ?? ????????? ????-????????
        for(int npic=0; npic < COUNT_PICTURES; npic++)
        {
            if( txMouseButtons() == 1 &&
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
                centralPicture[nCentralPictures] = {900,
                                                    100,
                                                    menuPicture[npic].adress,
                                                    menuPicture[npic].image,
                                                    menuPicture[npic].w,
                                                    menuPicture[npic].h,
                                                    menuPicture[npic].w,
                                                    menuPicture[npic].h,
                                                    menuPicture[npic].category,
                                                    menuPicture[npic].visible};

                nCentralPictures++;
            }
        }

     //????????? ????-???????? ?? ????????? ??????
    for(int nk=0; nk < COUNT_BTN-2; nk++)
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

      //????? ??????????? ??????

        for(int npic=0; npic < nCentralPictures; npic++)
        {
         if(txMouseButtons() == 1 &&
            centralPicture[npic].visible &&
            txMouseX() >= centralPicture[npic].x &&
            txMouseX() <= centralPicture[npic].x + centralPicture[npic].w &&
            txMouseY() >= centralPicture[npic].y &&
            txMouseY() <= centralPicture[npic].y + centralPicture[npic].h)
            {
                select = npic;
                mouse_free = false;
            }
        }



      //???????????? ????????? ??????????? ???????? ????????
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

      //???????????? ????????? ??????????? ???????? ??????
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


     // ???????? ????????
     if(select>=0 && GetAsyncKeyState(VK_DELETE))
     {
         centralPicture[select] = centralPicture[nCentralPictures - 1];
         nCentralPictures--;
         select=-1;
         mouse_free = true;

     }

     if(click(btn[5]))
    {
        string fileName = runFileDialog(true);
        if (fileName != "")
        {
           ofstream fout;

           fout.open(fileName);

           for (int npic = 0; npic < nCentralPictures; npic++)
           {
                if(centralPicture[npic].visible)
                {
                    fout << centralPicture[npic].x << endl;
                    fout << centralPicture[npic].y << endl;
                    fout << centralPicture[npic].adress << endl;
                }
           }
           fout.close();
           txMessageBox("?????????","???????", MB_ICONINFORMATION);

         }
    }

    if (click(btn[6]))
    {
        string fileName = runFileDialog(true);
        if(fileName != "")
        {
            for(int npic = 0; npic < COUNT_PICTURES; npic++)
            {
                centralPicture[npic].visible = false ;
            }

            char buff[50];
            ifstream fin(fileName);
            while (fin.good())
            {
                fin.getline(buff, 50);
                int x = atoi(buff);
                fin.getline(buff, 50);
                int y = atoi(buff);
                fin.getline(buff, 50);
                string adress = (buff);

                for(int npic = 0; npic < COUNT_PICTURES; npic++)
                {
                    if(menuPicture[npic].adress == adress)
                    {

                    centralPicture[nCentralPictures] = {x,
                                                        y,
                                                        menuPicture[npic].adress,
                                                        menuPicture[npic].image,
                                                        menuPicture[npic].w,
                                                        menuPicture[npic].h,
                                                        menuPicture[npic].w,
                                                        menuPicture[npic].h,
                                                        menuPicture[npic].category,
                                                        true};
                    nCentralPictures++;
                    }
                }
            }
            fin.close();
        }
    }

      txSleep(300);
      txEnd();


 }
}

     for(int npic=0; npic < COUNT_PICTURES; npic++)
     {
        txDeleteDC(menuPicture[npic].image);
     }


    return 0;
}

