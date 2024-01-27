#pragma warning(disable:4996)
#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
//rangi kardan:
typedef enum
{
    BLACK = 0, BLUE = 1, GREEN = 2,
    AQUA = 3, RED = 4, PURPLE = 5,
    YELLOW = 6, WHITE = 7, GRAY = 8,
    LIGHT_BLUE = 9, LIGHT_GREEN = 10,
    LIGHT_AQUA = 11, LIGHT_RED = 12,
    LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15
} ConsoleColors;
typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;
short setTextColor(const ConsoleColors foreground)
{
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}
//
struct userinformaition
{
    string name;
    int wins;
    int failures;
};
//
struct gameboard
{
    int satr;
    int sotoon;
    int minnumber;
};
struct home
{
    char aval;
    char dovom;
} ;
int main()
{

     int un=0;
     userinformaition gamers[1000];


     FILE *fptr;
     fptr=fopen("D:\\mineroo.txt","rb");
      while(fptr==NULL)
             fptr=fopen("D:\\mineroo.txt","rb");
     for(int i=0;i<1000;++i)
            fread(&gamers[i],sizeof(userinformaition),1,fptr);

     fclose(fptr);

     Beep(2000,200);
     Beep(1500,200);
     Beep(1000,200);
     Beep(500,200);
     setTextColor(LIGHT_BLUE);
     cout<<"<<Mine ";setTextColor(RED);cout<<"Sweeper>>"<<endl;
     lable1:
     setTextColor(GREEN);
     cout<<endl<<"Menu:"<<endl<<endl;
     setTextColor(LIGHT_BLUE);
     cout<<"1-start new game"<<endl<<"2-watch Scoreboard"<<endl;
     setTextColor(RED);
     cout<<"3-exit game"<<endl;
     int choice,bomb=0;
     bool payan=true;
     setTextColor(YELLOW);
     cout<<"Enter your choice";
     cin>>choice;
     system("cls");
     if(choice==1)
     {
        setTextColor(GRAY);
        cout<<"Enter your name";
        for(un;un<1000;++un)
        {cin>>gamers[un].name;
        for(int f=0;f<=un;++f)
        if(gamers[un].name==gamers[f].name)
        un=f;
        break;}
        //un==usernumber;
        setTextColor(YELLOW);
        cout<<"level of game:"<<endl;
        setTextColor(WHITE);
        cout<<"1-easy"<<endl;
        setTextColor(BLUE);
        cout<<"2-medium"<<endl;
        setTextColor(RED);
        cout<<"3-hard"<<endl;
        cin>>choice;
//easy:


        if(choice==1)
        {
           gameboard g1;
           g1.satr=9;g1.sotoon=9;g1.minnumber=10;
           home gameboard1[g1.satr][g1.sotoon];
           srand(time(0));
           for(int i=1;i<=10;++i)
               gameboard1[rand()%9+1][rand()%9+1].aval='@';
           //@==bomb;
           for(int i=1;i<=g1.satr;++i)
               for(int j=1;j<=g1.sotoon;++j)
               {   bomb=0;
                   if(gameboard1[i][j].aval!='@')
                   {
                      for(int m=i-1;m<=i+1;++m)
                        for(int n=j-1;n<=j+1;++n)
                        if(gameboard1[m][n].aval=='@')
                        bomb++;
                      gameboard1[i][j].aval=bomb;bomb=0;
                   }
               }
           for(int i=1;i<=g1.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g1.sotoon;++j)
                    if(gameboard1[i][j].aval=='@')
                    cout<<gameboard1[i][j].aval<<" ";
               else
                    cout<<(int)gameboard1[i][j].aval<<" ";
               }
           for(int i=1;i<=g1.satr;++i)
               for(int j=1;j<=g1.sotoon;++j)
                   gameboard1[i][j].dovom='*';

           for(int i=1;i<=g1.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g1.sotoon;++j)
                    cout<<"|"<<gameboard1[i][j].dovom<<"|"<<" ";}
          while(payan)

          {   lable2:
              setTextColor(AQUA);
              cout<<endl<<"orders:"<<endl;
              setTextColor(LIGHT_PURPLE);
              cout<<"1-display a house"<<endl<<"2-flagging a house"<<endl<<"3-remove the flag of a house"<<endl<<"4-Exit the game"<<endl;
              cin>>choice;
              setTextColor(AQUA);
              if(choice==1)
              {   int satrdisplay,sotoondisplay;
                  cin>>satrdisplay>>sotoondisplay;
                          if(gameboard1[satrdisplay][sotoondisplay].dovom=='^')
                          {cout<<"Are you sure or not?"<<endl;
                           cout<<"1-yes"<<endl;
                           cout<<"2-no"<<endl;
                           cin>>choice;
                           if(choice==1)
                           {
                          if(gameboard1[satrdisplay][sotoondisplay].aval=='@')
                          {cout<<"Game Over";Beep(500,1000);payan=false;gamers[un].failures++;un++;
                          for(int i=1;i<=g1.satr;++i)
                          {cout<<endl;
                                   for(int j=1;j<=g1.sotoon;++j)
                                       if(gameboard1[i][j].aval=='@')
                                       cout<<"|"<<gameboard1[i][j].aval<<"|"<<" ";
                                       else
                                       cout<<"|"<<(int)gameboard1[i][j].aval<<"|"<<" ";
                                   }
                          goto lable1;break;}
                          else if(gameboard1[satrdisplay][sotoondisplay].aval>0)
                          {gameboard1[satrdisplay][sotoondisplay].dovom=(int)gameboard1[satrdisplay][sotoondisplay].aval;}
                          else if(gameboard1[satrdisplay][sotoondisplay].aval==0)
                          {for(int i=satrdisplay-1;i<=satrdisplay+1;++i)
                               for(int j=sotoondisplay-1;j<=sotoondisplay+1;++j)
                               if(gameboard1[i][j].aval!='@'){
                                if(gameboard1[i][j].aval>0)
                                {gameboard1[i][j].dovom=gameboard1[i][j].aval;}
                                else if(gameboard1[i][j].aval==0)
                                {for(int m=i-1;m<=i+1;++m)
                                    for(int n=j-1;n<=j+1;++n)
                                     {if(m>0&&n>0)
                                      if(gameboard1[m][n].aval!='@')
                                      gameboard1[m][n].dovom=gameboard1[m][n].aval;}}

                               }


}}if(choice==2)
     goto lable2;

                          }
                    else
                        if(gameboard1[satrdisplay][sotoondisplay].aval=='@')
                          {cout<<"Game Over";Beep(500,1000);payan=false;gamers[un].failures++;un++;
                          for(int i=1;i<=g1.satr;++i)
                          {cout<<endl;
                                   for(int j=1;j<=g1.sotoon;++j)
                                       if(gameboard1[i][j].aval=='@')
                                       cout<<"|"<<gameboard1[i][j].aval<<"|"<<" ";
                                       else
                                       cout<<"|"<<(int)gameboard1[i][j].aval<<"|"<<" ";
                                   }goto lable1;break;}
                          else if(gameboard1[satrdisplay][sotoondisplay].aval>0)
                          {gameboard1[satrdisplay][sotoondisplay].dovom=(int)gameboard1[satrdisplay][sotoondisplay].aval;}
                          else if(gameboard1[satrdisplay][sotoondisplay].aval==0)
                          {for(int i=satrdisplay-1;i<=satrdisplay+1;++i)
                               for(int j=sotoondisplay-1;j<=sotoondisplay+1;++j)
                               if(gameboard1[i][j].aval!='@'){
                               if(gameboard1[i][j].aval>0)
                                {gameboard1[i][j].dovom=gameboard1[i][j].aval;}
                                else if(gameboard1[i][j].aval==0)
                                {for(int m=i-1;m<=i+1;++m)
                                    for(int n=j-1;n<=j+1;++n)
                                     {if(m>0&&n>0)
                                      if(gameboard1[m][n].aval!='@')
                                      gameboard1[m][n].dovom=gameboard1[m][n].aval;}}


                          }
                          }}

if(choice==2)
{   int satrdisplay,sotoondisplay;
    cin>>satrdisplay>>sotoondisplay;
    gameboard1[satrdisplay][sotoondisplay].dovom='^';
}
if(choice==3)
{
    int satrdisplay,sotoondisplay;
    cin>>satrdisplay>>sotoondisplay;
    gameboard1[satrdisplay][sotoondisplay].dovom='*';

}
if(choice==4)
{
    goto lable1;
}
for(int i=1;i<=g1.satr;++i)
    {cout<<endl;
    for(int j=1;j<=g1.sotoon;++j)
    if(gameboard1[i][j].dovom=='*'||gameboard1[i][j].dovom=='^')
    cout<<"|"<<gameboard1[i][j].dovom<<"|"<<" ";
    else
        cout<<"|"<<(int)gameboard1[i][j].dovom<<"|"<<" ";
    }
int khonsa=0;
    for(int i=1;i<=g1.satr;++i)
        {for(int j=1;j<=g1.sotoon;++j)
        {
            if(gameboard1[i][j].dovom=='*')
            {khonsa++;}
        }}
if(khonsa==10)
{   cout<<endl<<"Victory";Beep(1500,1000);Beep(500,1000);Beep(2500,1000);
    gamers[un].wins++;un++;
    for(int i=1;i<=g1.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g1.sotoon;++j)
                    if(gameboard1[i][j].aval=='@')
                    cout<<"|"<<gameboard1[i][j].aval<<"|"<<" ";
               else
                    cout<<"|"<<(int)gameboard1[i][j].aval<<"|"<<" ";
               }goto lable1;break;
}


        }}
//medium:


else if(choice==2)
{
           gameboard g2;
           g2.satr=16;g2.sotoon=16;g2.minnumber=40;
           home gameboard2 [g2.satr][g2.sotoon];
           srand(time(0));
           for(int i=1;i<=g2.minnumber;++i)
               gameboard2[rand()%16+1][rand()%16+1].aval='@';
           //@==bomb;
           for(int i=1;i<=g2.satr;++i)
               for(int j=1;j<=g2.sotoon;++j)
               {   bomb=0;
                   if(gameboard2[i][j].aval!='@')
                   {
                      for(int m=i-1;m<=i+1;++m)
                        for(int n=j-1;n<=j+1;++n)
                        if(gameboard2[m][n].aval=='@')
                        bomb++;
                      gameboard2[i][j].aval=bomb;bomb=0;
                   }
               }
           for(int i=1;i<=g2.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g2.sotoon;++j)
                    if(gameboard2[i][j].aval=='@')
                    cout<<gameboard2[i][j].aval<<" ";
               else
                    cout<<(int)gameboard2[i][j].aval<<" ";
               }
           for(int i=1;i<=g2.satr;++i)
               for(int j=1;j<=g2.sotoon;++j)
                   gameboard2[i][j].dovom='*';

           for(int i=1;i<=g2.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g2.sotoon;++j)
                    cout<<"|"<<gameboard2[i][j].dovom<<"|"<<" ";}
          while(payan)

          {   lable3:
              setTextColor(AQUA);
              cout<<endl<<"orders:"<<endl;
              setTextColor(LIGHT_PURPLE);
              cout<<"1-display a house"<<endl<<"2-flagging a house"<<endl<<"3-remove the flag of a house"<<endl<<"4-Exit the game"<<endl;
              cin>>choice;
              setTextColor(AQUA);
              if(choice==1)
              {   int satrdisplay,sotoondisplay;
                  cin>>satrdisplay>>sotoondisplay;
                          if(gameboard2[satrdisplay][sotoondisplay].dovom=='^')
                          {cout<<"Are you sure or not?"<<endl;
                           cout<<"1-yes"<<endl;
                           cout<<"2-no"<<endl;
                           cin>>choice;
                           if(choice==1)
                           {
                          if(gameboard2[satrdisplay][sotoondisplay].aval=='@')
                          {cout<<"Game Over";Beep(500,1000);payan=false;gamers[un].failures++;un++;
                          for(int i=1;i<=g2.satr;++i)
                          {cout<<endl;
                                   for(int j=1;j<=g2.sotoon;++j)
                                       if(gameboard2[i][j].aval=='@')
                                       cout<<"|"<<gameboard2[i][j].aval<<"|"<<" ";
                                       else
                                       cout<<"|"<<(int)gameboard2[i][j].aval<<"|"<<" ";
                                   }
                          goto lable1;break;}
                          else if(gameboard2[satrdisplay][sotoondisplay].aval>0)
                          {gameboard2[satrdisplay][sotoondisplay].dovom=(int)gameboard2[satrdisplay][sotoondisplay].aval;}
                          else if(gameboard2[satrdisplay][sotoondisplay].aval==0)
                          {for(int i=satrdisplay-1;i<=satrdisplay+1;++i)
                               for(int j=sotoondisplay-1;j<=sotoondisplay+1;++j)
                               if(gameboard2[i][j].aval!='@'){
                                if(gameboard2[i][j].aval>0)
                                {gameboard2[i][j].dovom=gameboard2[i][j].aval;}
                                else if(gameboard2[i][j].aval==0)
                                {for(int m=i-1;m<=i+1;++m)
                                    for(int n=j-1;n<=j+1;++n)
                                     {if(m>0&&n>0)
                                      if(gameboard2[m][n].aval!='@')
                                      gameboard2[m][n].dovom=gameboard2[m][n].aval;}}

                               }


}}if(choice==2)
     goto lable3;

                          }
                    else
                        if(gameboard2[satrdisplay][sotoondisplay].aval=='@')
                          {cout<<"Game Over";Beep(500,1000);payan=false;gamers[un].failures++;un++;
                          for(int i=1;i<=g2.satr;++i)
                          {cout<<endl;
                                   for(int j=1;j<=g2.sotoon;++j)
                                       if(gameboard2[i][j].aval=='@')
                                       cout<<"|"<<gameboard2[i][j].aval<<"|"<<" ";
                                       else
                                       cout<<"|"<<(int)gameboard2[i][j].aval<<"|"<<" ";
                                   }goto lable1;break;}
                          else if(gameboard2[satrdisplay][sotoondisplay].aval>0)
                          {gameboard2[satrdisplay][sotoondisplay].dovom=(int)gameboard2[satrdisplay][sotoondisplay].aval;}
                          else if(gameboard2[satrdisplay][sotoondisplay].aval==0)
                          {for(int i=satrdisplay-1;i<=satrdisplay+1;++i)
                               for(int j=sotoondisplay-1;j<=sotoondisplay+1;++j)
                               if(gameboard2[i][j].aval!='@'){
                               if(gameboard2[i][j].aval>0)
                                {gameboard2[i][j].dovom=gameboard2[i][j].aval;}
                                else if(gameboard2[i][j].aval==0)
                                {for(int m=i-1;m<=i+1;++m)
                                    for(int n=j-1;n<=j+1;++n)
                                     {if(m>0&&n>0)
                                      if(gameboard2[m][n].aval!='@')
                                      gameboard2[m][n].dovom=gameboard2[m][n].aval;}}

                               }
                          }
                          }

if(choice==2)
{   int satrdisplay,sotoondisplay;
    cin>>satrdisplay>>sotoondisplay;
    gameboard2[satrdisplay][sotoondisplay].dovom='^';
}
if(choice==3)
{
    int satrdisplay,sotoondisplay;
    cin>>satrdisplay>>sotoondisplay;
    gameboard2[satrdisplay][sotoondisplay].dovom='*';

}
if(choice==4)
{
    goto lable1;
}
for(int i=1;i<=g2.satr;++i)
    {cout<<endl;
    for(int j=1;j<=g2.sotoon;++j)
    if(gameboard2[i][j].dovom=='*'||gameboard2[i][j].dovom=='^')
    cout<<"|"<<gameboard2[i][j].dovom<<"|"<<" ";
    else
        cout<<"|"<<(int)gameboard2[i][j].dovom<<"|"<<" ";
    }
int khonsa=0;
    for(int i=1;i<=g2.satr;++i)
        {for(int j=1;j<=g2.sotoon;++j)
        {
            if(gameboard2[i][j].dovom=='*')
            {khonsa++;}
        }}
if(khonsa==10)
{   cout<<endl<<"Victory";Beep(1500,1000);Beep(500,1000);Beep(2500,1000);gamers[un].wins++;un++;
    for(int i=1;i<=g2.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g2.sotoon;++j)
                    if(gameboard2[i][j].aval=='@')
                    cout<<"|"<<gameboard2[i][j].aval<<"|"<<" ";
               else
                    cout<<"|"<<(int)gameboard2[i][j].aval<<"|"<<" ";
               }goto lable1;break;
}
               }

        }
//hard:


else if(choice==3)
{
    gameboard g3;
           g3.satr=16;g3.sotoon=30;g3.minnumber=99;
           home gameboard3 [g3.satr][g3.sotoon];
           srand(time(0));
           for(int i=1;i<=99;++i)
               gameboard3[rand()%16+1][rand()%30+1].aval='@';
           //@==bomb;
           for(int i=1;i<=g3.satr;++i)
               for(int j=1;j<=g3.sotoon;++j)
               {   bomb=0;
                   if(gameboard3[i][j].aval!='@')
                   {
                      for(int m=i-1;m<=i+1;++m)
                        for(int n=j-1;n<=j+1;++n)
                        if(gameboard3[m][n].aval=='@')
                        bomb++;
                      gameboard3[i][j].aval=bomb;bomb=0;
                   }
               }
           for(int i=1;i<=g3.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g3.sotoon;++j)
                    if(gameboard3[i][j].aval=='@')
                    cout<<gameboard3[i][j].aval<<" ";
               else
                    cout<<(int)gameboard3[i][j].aval<<" ";
               }
           for(int i=1;i<=g3.satr;++i)
               for(int j=1;j<=g3.sotoon;++j)
                   gameboard3[i][j].dovom='*';

           for(int i=1;i<=g3.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g3.sotoon;++j)
                    cout<<"|"<<gameboard3[i][j].dovom<<"|"<<" ";}
          while(payan)

          {   lable4:
              setTextColor(AQUA);
              cout<<endl<<"orders:"<<endl;
              setTextColor(LIGHT_PURPLE);
              cout<<"1-display a house"<<endl<<"2-flagging a house"<<endl<<"3-remove the flag of a house"<<endl<<"4-Exit the game"<<endl;
              cin>>choice;
              setTextColor(AQUA);
              if(choice==1)
              {   int satrdisplay,sotoondisplay;
                  cin>>satrdisplay>>sotoondisplay;
                          if(gameboard3[satrdisplay][sotoondisplay].dovom=='^')
                          {cout<<"Are you sure or not?"<<endl;
                           cout<<"1-yes"<<endl;
                           cout<<"2-no"<<endl;
                           cin>>choice;
                           if(choice==1)
                           {
                          if(gameboard3[satrdisplay][sotoondisplay].aval=='@')
                          {cout<<"Game Over";Beep(500,1000);payan=false;gamers[un].failures++;un++;
                          for(int i=1;i<=g3.satr;++i)
                          {cout<<endl;
                                   for(int j=1;j<=g3.sotoon;++j)
                                       if(gameboard3[i][j].aval=='@')
                                       cout<<"|"<<gameboard3[i][j].aval<<"|"<<" ";
                                       else
                                       cout<<"|"<<(int)gameboard3[i][j].aval<<"|"<<" ";
                                   }
                          goto lable1;break;}
                          else if(gameboard3[satrdisplay][sotoondisplay].aval>0)
                          {gameboard3[satrdisplay][sotoondisplay].dovom=(int)gameboard3[satrdisplay][sotoondisplay].aval;}
                          else if(gameboard3[satrdisplay][sotoondisplay].aval==0)
                          {for(int i=satrdisplay-1;i<=satrdisplay+1;++i)
                               for(int j=sotoondisplay-1;j<=sotoondisplay+1;++j)
                               if(gameboard3[i][j].aval!='@'){
                                if(gameboard3[i][j].aval>0)
                                {gameboard3[i][j].dovom=gameboard3[i][j].aval;}
                                else if(gameboard3[i][j].aval==0)
                                {for(int m=i-1;m<=i+1;++m)
                                    for(int n=j-1;n<=j+1;++n)
                                     {if(m>0&&n>0)
                                      if(gameboard3[m][n].aval!='@')
                                      gameboard3[m][n].dovom=gameboard3[m][n].aval;}}

                               }


}}if(choice==2)
     goto lable4;

                          }
                    else
                        if(gameboard3[satrdisplay][sotoondisplay].aval=='@')
                          {cout<<"Game Over";Beep(500,1000);payan=false;gamers[un].failures++;un++;
                          for(int i=1;i<=g3.satr;++i)
                          {cout<<endl;
                                   for(int j=1;j<=g3.sotoon;++j)
                                       if(gameboard3[i][j].aval=='@')
                                       cout<<"|"<<gameboard3[i][j].aval<<"|"<<" ";
                                       else
                                       cout<<"|"<<(int)gameboard3[i][j].aval<<"|"<<" ";
                                   }goto lable1;break;}
                          else if(gameboard3[satrdisplay][sotoondisplay].aval>0)
                          {gameboard3[satrdisplay][sotoondisplay].dovom=(int)gameboard3[satrdisplay][sotoondisplay].aval;}
                          else if(gameboard3[satrdisplay][sotoondisplay].aval==0)
                          {for(int i=satrdisplay-1;i<=satrdisplay+1;++i)
                               for(int j=sotoondisplay-1;j<=sotoondisplay+1;++j)
                               if(gameboard3[i][j].aval!='@'){
                               if(gameboard3[i][j].aval>0)
                                {gameboard3[i][j].dovom=gameboard3[i][j].aval;}
                                else if(gameboard3[i][j].aval==0)
                                {for(int m=i-1;m<=i+1;++m)
                                    for(int n=j-1;n<=j+1;++n)
                                     {if(m>0&&n>0)
                                      if(gameboard3[m][n].aval!='@')
                                      gameboard3[m][n].dovom=gameboard3[m][n].aval;}}


                          }
                          }}

if(choice==2)
{   int satrdisplay,sotoondisplay;
    cin>>satrdisplay>>sotoondisplay;
    gameboard3[satrdisplay][sotoondisplay].dovom='^';
}
if(choice==3)
{
    int satrdisplay,sotoondisplay;
    cin>>satrdisplay>>sotoondisplay;
    gameboard3[satrdisplay][sotoondisplay].dovom='*';

}
if(choice==4)
{
    goto lable1;
}
for(int i=1;i<=g3.satr;++i)
    {cout<<endl;
    for(int j=1;j<=g3.sotoon;++j)
    if(gameboard3[i][j].dovom=='*'||gameboard3[i][j].dovom=='^')
    cout<<"|"<<gameboard3[i][j].dovom<<"|"<<" ";
    else
        cout<<"|"<<(int)gameboard3[i][j].dovom<<"|"<<" ";
    }
int khonsa=0;
    for(int i=1;i<=g3.satr;++i)
        {for(int j=1;j<=g3.sotoon;++j)
        {
            if(gameboard3[i][j].dovom=='*')
            {khonsa++;}
        }}
if(khonsa==10)
{   cout<<endl<<"Victory";Beep(1500,1000);Beep(500,1000);Beep(2500,1000);gamers[un].wins++;un++;
    for(int i=1;i<=g3.satr;++i)
               {cout<<endl;
               for(int j=1;j<=g3.sotoon;++j)
                    if(gameboard3[i][j].aval=='@')
                    cout<<"|"<<gameboard3[i][j].aval<<"|"<<" ";
               else
                    cout<<"|"<<(int)gameboard3[i][j].aval<<"|"<<" ";
               }goto lable1;break;
}


        }




}






     }
for(int o=0;o<un;++o)
cout<<gamers[o].name<<gamers[o].failures<<gamers[o].wins;
fptr=fopen("D:\\mineroo.txt","a");
for(int i=0;i<3;++i)
            fwrite(&gamers[i],sizeof(userinformaition),1,fptr);
     fclose(fptr);









    setTextColor(WHITE);
    return 0;
}
