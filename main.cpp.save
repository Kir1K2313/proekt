#include "TXLib.h"
#include <fstream>
using namespace std;

struct Form
{
  string text_question;
  int right_answer;
  string text_answer1;
  string text_answer2;
  string text_answer3;
  HDC pic_fon;
};

bool click_answer(int x)
{
  return(txMouseButtons() == 1 &&
         txMouseX() >= x &&
         txMouseY() >= 350 &&
         txMouseX() <= x+200 &&
         txMouseY() <= 450);
}

void draw_answer(int x, string text, int font)
{
  txSetColor(TX_WHITE);
  txSetFillColor(TX_BLACK);
  txSelectFont("Arial", font);
  Win32::RoundRect(txDC(), x, 350, x+200, 450, 20, 20 );
  txDrawText (x, 350, x+200, 450, text.c_str());
}

string getPart(string str, int *pos2)
{
    int pos1 = *pos2 + 1;
    *pos2 = str.find(",", pos1);
    string Part = str.substr(pos1,*pos2 - pos1);
    return Part;
}

int main()
{
    txCreateWindow (800, 600);
    txTextCursor (false);

    HDC fon = txLoadImage("картинки/фон.bmp");
    int n_question = 1;
    int result = 0;
    Form form;
    Form form_list[50];
    string str;
    int n = 0;
    ifstream file("13131.txt");
    int font = 35;
    string PAGE = "Start";

    while(file.good())
    {
        getline(file, str);
        int pos2 = -1;

        form_list[n].text_question = getPart(str,&pos2);
        form_list[n].right_answer = atoi(getPart(str,&pos2).c_str());
        form_list[n].text_answer1 = getPart(str,&pos2);
        form_list[n].text_answer2 = getPart(str,&pos2);
        form_list[n].text_answer3 = getPart(str,&pos2);
        form_list[n].pic_fon =  txLoadImage(getPart(str,&pos2).c_str());
        n++;
    }
    file.close();

    while(n_question<=n)
    {
        if(PAGE=="Start")
        {
             txBegin();
             txSetColor(TX_WHITE,5);
             txSetFillColor(TX_BLACK);
             txRectangle(txDC(), 0,0,800,600);
             txSelectFont("Arial", 55);
             txDrawText(50,50,750,150, "Тест по геншин импакту");
             txSelectFont("Arial", 45);
             txDrawText(50,200,750,350, "Проверь свои знании");
             txSelectFont("Arial", 35);
             txRectangle(300,450,500,500);
             txDrawText(300,450,500,500,"Начать");

             if( txMouseX() >= 300 && txMouseY()>= 450 &&
                 txMouseX() <= 500 && txMouseY()<= 500 &&
                 txMouseButtons() == 1)
                {
                  PAGE="Тест";
                }
            txEnd();
            txSleep(10);
        }

        if(PAGE == "Тест")
        {
            txBegin();
            txSetFillColor(TX_BLACK);
            txClear();

            form = form_list[n_question - 1];

            txSetColor(TX_BLACK);
            txSetFillColor(TX_WHITE);
            font = 35;
            txSelectFont("Arial", font);
            txBitBlt (txDC(), 0, 0, 800,600, form.pic_fon);
            txDrawText(50, 50 ,750, 250, form.text_question.c_str());

            if(n_question == 8)
            {
               font = 25;
            }
            draw_answer(50, form.text_answer1, font);
            draw_answer(300, form.text_answer2, font);
            draw_answer(550, form.text_answer3, font);

            txSetColor(TX_BLACK);
            font = 35;
            txSelectFont("Arial", font);
            char str[10];
            sprintf(str, "Вопрос %d/%d", n_question, n);
            txDrawText(50, 0 ,750, 50, str );

            if (click_answer(50))
            {
              while(txMouseButtons() == 1) txSleep(10);
              txSleep(500);
              n_question++;
              if(form.right_answer == 1)
              {
                result++;
              }
            }
            if (click_answer(300))
            {
              while(txMouseButtons() == 1) txSleep(10);
              txSleep(500);
              n_question++;
              if(form.right_answer == 2)
              {
                result++;
              }
            }

             if (click_answer(550))
            {
              while(txMouseButtons() == 1) txSleep(10);
              txSleep(500);
              n_question++;
              if(form.right_answer == 3)
              {
                result++;
              }
            }

            txEnd;
            txSleep(50);
        }
    }
    txSetColor(TX_WHITE);
    txSetFillColor(TX_BLACK);
    txClear();
    txBitBlt(txDC(), 0,0,800,600,fon);
    txDrawText(50, 50 ,750, 200, "Ваш результат:");
    char stroka[10];
    sprintf(stroka, "%d", result);
    txDrawText(50, 150 ,750, 250, stroka);

    if (result==10)
    {
        txDrawText(250, 300, 550, 400, "Знаток" );
        txDrawText(50,350,750,600, "Вы отлично разбираетесь в данной вселенной");
    }
    else if(result <=10 && result>=6 )
    {
        txDrawText(250,300, 550, 400, "Cредний" );
        txDrawText(50,350,750,750, "Вы достаточно хорошо разбираетесь в данной вселенной");
    }
    else if(result<=5)
    {
        txDrawText(250, 300, 550, 400, "Новичок" );
        txSelectFont("Arial", 30);
        txDrawText(50,410,750,600, "Вы к сожалению не очень хорошо разбираетесь в данной вселенной");
    }
    for(int i=0; i<=n; i++)
    {
    txDeleteDC(form_list[i].pic_fon);
    }

    return 0;
}
