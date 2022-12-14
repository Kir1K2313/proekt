#include <iostream>

using namespace std;

int click(btn(BTN_5)))
{
  string fileName = "1.txt"
  if(fileName != "")
  {
     for(int npic = 0; npic < COUNT_PICTURE; npic++)
     {
       centralpicture[npic].visible = false;
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
      for(int npic = 0; npic < COUNT_PICTURE; npic++)
      {
          if(centralpicture[npic].adress = adress)
          {
              centralpicture[npic].x = x;
              centralpicture[npic].y = y;
              centralpicture[npic].visible = true;
          }
      }
     }
     fin.close();
  }
}
