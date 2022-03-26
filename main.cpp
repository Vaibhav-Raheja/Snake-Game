#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<string>
using namespace std;
    void restart();
    void snake();
    void game();
    int x,y,appleX=rand()%770,appleY=rand()%570,score=0,hx=400,hy=300,speed=5,curX,curY,length; //x,y=tail start pos hx,hy=head pos
    char s[50];
    bool gameover=false;
    string dir="left";
    string prvdir="up";
    bool appleeaten=false;
    void startgame()
    {
       initwindow(800,600,"");
       outtextxy(300,300,"Press Space to Start Game");
       if(GetAsyncKeyState(VK_SPACE))
       {
           snake();
           game();
       }
       getch();
       closegraph();
    }
    void snake()
    {
         while(gameover==false)
    {
        cleardevice();
        //borders
        bar(0,0,30,600);
        bar(0,0,800,30);
        bar(770,0,800,600);
        bar(0,570,800,600);
        circle(appleX,appleY,7.5);
        //score and apple eaten
        if(hx<=appleX+7.5&&hx>=appleX-7.5&&hy<=appleY+7.5&&hy>=appleY-7.5||(hx+20<=appleX+7.5&&hx+20>=appleX-7.5&&hy+20<=appleY+7.5&&hy+20>=appleY-7.5)||curX==appleX||curY==appleY)
        {
            length++;
            appleX=50+rand()%((770+1)-50);
            appleY=50+rand()%((570+1)-50);
            circle(appleX,appleY,7.5);
            for(int i=0;i<1;i++)
            {
              score=score+10;
            }
        }
        //snake spawn....
        bar(hx,hy,hx+20,hy+20);
        //snake movement
        if(GetAsyncKeyState(VK_LEFT))
        {
            prvdir=dir;
            dir="left";
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            prvdir=dir;
            dir="right";
        }
        else if (GetAsyncKeyState(VK_UP))
        {
            prvdir=dir;
            dir="up";
        }
        else if(GetAsyncKeyState(VK_DOWN))
        {
            prvdir=dir;
            dir="down";
        }
        if(dir=="left")
        {
            hx-=speed;
            curX=hx;
            bar(curX-speed,curY,curX+(50*length)-speed,curY+20);
        }
        else if(dir=="right")
        {
            hx+=speed;
            curX=hx;
            bar(curX-speed,curY,curX+(50*length)+speed,curY+20);
        }
        else if(dir=="up")
        {
            hy-=speed;
            curY=hy;
            bar(curX,curY-speed,curX,curY+(50*length)-speed);
        }
        else if(dir=="down")
        {
            hy+=speed;
            curY=hy;
            bar(curX,curY-speed,curX,curY-(50*length)+speed);
        }
        setcolor(YELLOW);
        sprintf(s,"Score %d",score);
        outtextxy(30,30,s);
        if(hx==750||hy==550||hx==0||hy==0)
        {
            gameover=true;
        }
        delay(50);
    }
    }
    void game()
    {
    int main=initwindow(800,600,"",-3,-3);
    snake();
    getch();
    closegraph();
    }
int main()
{
    start:
    startgame();
    game();
    int choice;
    CHoice:
    cout<<"******************Game Over******************"<<endl;
    cout<<"\t          Score:"<<score<<endl;
    cout<<"\t          1: Restart"<<endl;
    cout<<"\t          2: Endgame"<<endl;
    cout<<"\t          Enter Choice: ";
    cin>>choice;
    if(choice==1)
        {
            gameover=false;
            appleeaten=false;
            goto start;
        }
        else if(choice==2)
        {
          exit(EXIT_SUCCESS);
        }
        else
        {
            cout<<"Wrong Number Entered \n";
            goto CHoice;
        }
    return 0;
}
