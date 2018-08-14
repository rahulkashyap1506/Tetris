#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<alloc.h>

int level=1,lines=0,score=0;
int board[20][10],board1[20][10];
void *buf;

struct tetrimino
      {int i[4];
       int j[4];
       int col;
      }ttr[7];

struct ctetrimino
      {tetrimino ttr;
       int i;
       int j;}cttr,tempttr;

/***** FUNCTION PROTOTYPES *****/

void background();
void status();
void print();
void cttrprint();
void working();
void next(int n);
void rotate(tetrimino &ttr);

/***** MAIN BODY *****/

void main()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\turboc3\\bgi");
 cleardevice();

 int size=imagesize(0,0,23,23);
 buf=(void *)malloc(size);
 getimage(0,0,22,22,buf);

 int i,j,k;

 for(i=0;i<20;i++)
    for(j=0;j<10;j++)
       {board[i][j]=0;
	board1[i][j]=0;}

 // I
 ttr[0].i[0]=0;	ttr[0].j[0]=0;
 ttr[0].i[1]=1; ttr[0].j[1]=0;
 ttr[0].i[2]=2; ttr[0].j[2]=0;
 ttr[0].i[3]=3; ttr[0].j[3]=0;
 ttr[0].col=3;

 // O
 ttr[1].i[0]=0; ttr[1].j[0]=0;
 ttr[1].i[1]=0; ttr[1].j[1]=1;
 ttr[1].i[2]=1; ttr[1].j[2]=0;
 ttr[1].i[3]=1; ttr[1].j[3]=1;
 ttr[1].col=14;

 // T
 ttr[2].i[0]=0; ttr[2].j[0]=0;
 ttr[2].i[1]=0; ttr[2].j[1]=1;
 ttr[2].i[2]=0; ttr[2].j[2]=2;
 ttr[2].i[3]=1; ttr[2].j[3]=1;
 ttr[2].col=5;

 // S
 ttr[3].i[0]=0; ttr[3].j[0]=1;
 ttr[3].i[1]=0; ttr[3].j[1]=2;
 ttr[3].i[2]=1; ttr[3].j[2]=0;
 ttr[3].i[3]=1; ttr[3].j[3]=1;
 ttr[3].col=2;

 // Z
 ttr[4].i[0]=0; ttr[4].j[0]=0;
 ttr[4].i[1]=0; ttr[4].j[1]=1;
 ttr[4].i[2]=1; ttr[4].j[2]=1;
 ttr[4].i[3]=1; ttr[4].j[3]=2;
 ttr[4].col=4;

 // J
 ttr[5].i[0]=0; ttr[5].j[0]=1;
 ttr[5].i[1]=1; ttr[5].j[1]=1;
 ttr[5].i[2]=2; ttr[5].j[2]=1;
 ttr[5].i[3]=2; ttr[5].j[3]=0;
 ttr[5].col=9;

 // L
 ttr[6].i[0]=0; ttr[6].j[0]=0;
 ttr[6].i[1]=1; ttr[6].j[1]=0;
 ttr[6].i[2]=2; ttr[6].j[2]=0;
 ttr[6].i[3]=2; ttr[6].j[3]=1;
 ttr[6].col=6;

 background();
 status();
 working();

 getch();
 closegraph();
}


/***** BACKGROUND *****/

void background()
{int x,y,i,j;
 cleardevice();

 rectangle(0,0,getmaxx(),getmaxy());

 x=220;
 y=10;
 setlinestyle(3,2,3);
 rectangle(x-2,y-2,x+230+1,y+460+1);	//Main Box
 setlinestyle(0,0,1);
 rectangle(x-2,y-2,x+230+1,y+460+1);

 x=490;
 y=140;
 for(i=0;i<4;i++)
    for(j=0;j<4;j++)
       rectangle(x+i*23,y+j*23,x+(i+1)*23-1,y+(j+1)*23-1);  //Next Tetriminos
 settextstyle(8,0,4);
 outtextxy(502,228,"Next");

 settextstyle(0,0,4);
 outtextxy(15,100,"TETRIS");

 settextstyle(8,0,3);

 outtextxy(20,180,"Level");
 x=15;
 y=215;
 rectangle(x,y,x+150,y+25);     //Level

 outtextxy(20,250,"Lines");
 x=15;
 y=285;
 rectangle(x,y,x+150,y+25);	//Lines

 outtextxy(20,320,"Score");
 x=15;
 y=355;
 rectangle(x,y,x+150,y+25); 	//Score

 gotoxy(65,24);
 cout<<"P - Pause";

 gotoxy(65,25);
 cout<<"Q - Quit";
}

/***** STATUS *****/

void status()
{char lvl[10]="00",lns[10]="000",scr[10]="00000";
 int x,y,m,n;

 settextstyle(8,0,3);
 setfillstyle(1,0);

 m=15;
 n=215;
 int a[]={m,n,m+150,n,m+150,n+25,m,n+25,m,n};
 fillpoly(5,a);
 x=level;
 y=1;
 while(x)
      {lvl[y]=48+x%10;
       x/=10;
       y--;}
 outtextxy(75,210,lvl);

 m=15;
 n=285;
 int b[]={m,n,m+150,n,m+150,n+25,m,n+25,m,n};
 fillpoly(5,b);
 x=lines;
 y=2;
 while(x)
      {lns[y]=48+x%10;
       x/=10;
       y--;}
 outtextxy(65,280,lns);

 m=15;
 n=355;
 int c[]={m,n,m+150,n,m+150,n+25,m,n+25,m,n};
 fillpoly(5,c);
 x=score;
 y=4;
 while(x)
      {scr[y]=48+x%10;
       x/=10;
       y--;}
 outtextxy(50,350,scr);
}

/***** PRINT *****/

void print()
{int x,y,i,j;

 x=220;
 y=10;

 for(i=0;i<20;i++)
    for(j=0;j<10;j++)
       if(board1[i][j]==0)
	 putimage(x+j*23,y+i*23,buf,0);

 for(i=0;i<20;i++)
    for(j=0;j<10;j++)
       if(board[i][j]!=0)
	  {setcolor(15);
	   rectangle(x+j*23,y+i*23,x+(j+1)*23-1,y+(i+1)*23-1);
	   setfillstyle(1,board[i][j]);
	   floodfill(x+j*23+10,y+i*23+10,15);}

}

/***** TETRIMINO PRINT *****/

void cttrprint()
{int x,y,a;

 x=220;
 y=10;
 for(a=0;a<4;a++)
    {rectangle(x + cttr.j*23 + cttr.ttr.j[a]*23,
	       y + cttr.i*23 + cttr.ttr.i[a]*23,
	       x + cttr.j*23 + (cttr.ttr.j[a]+1)*23-1,
	       y + cttr.i*23 + (cttr.ttr.i[a]+1)*23-1);
     setfillstyle(1,cttr.ttr.col);
     floodfill(x + cttr.j*23 + cttr.ttr.j[a]*23 + 10,
	       y + cttr.i*23 + cttr.ttr.i[a]*23 + 10,
	       15);}

}

/***** WORKING *****/

void working()
{int i,j,nttr,check,time=20,t1,t2,t3,end,finish;
 char ch;

 randomize();

 nttr=random(7);

 do{finish=0;
    status();

    cttr.ttr=ttr[nttr];
    cttr.i=0;
    cttr.j=4;

    check=0;
    for(t1=0;t1<4;t1++)
       if(board1[cttr.ttr.i[t1]+cttr.i]
		[cttr.ttr.j[t1]+cttr.j]==0)
	  check++;
    if(check!=4)
      {finish=1;
       break;}

    nttr=random(7);
    next(nttr);

    print();
    cttrprint();

    do{end=0;
       check=0;
       do{if(kbhit())
	    {ch=getch();
	     if(ch==72)
	       {tempttr=cttr;
		rotate(tempttr.ttr);
		t2=0;
		for(t1=0;t1<4;t1++)
		   if(board1[tempttr.ttr.i[t1]+tempttr.i]
			    [tempttr.ttr.j[t1]+tempttr.j]==0&&
		      tempttr.i+tempttr.ttr.i[t1]<20&&
		      tempttr.j+tempttr.ttr.j[t1]<10)
		      t2++;
		if(t2==4)
		  {rotate(cttr.ttr);
		   print();
		   cttrprint();}
	       }
	     else if(ch==75||ch==77)
	       {tempttr=cttr;
		if(ch==75)
		  tempttr.j--;
		if(ch==77)
		  tempttr.j++;
		t2=0;
		for(t1=0;t1<4;t1++)
		   if(board1[tempttr.ttr.i[t1]+tempttr.i]
			    [tempttr.ttr.j[t1]+tempttr.j]==0&&
		      tempttr.i+tempttr.ttr.i[t1]<20&&
		      tempttr.j+tempttr.ttr.j[t1]<10&&
		      tempttr.j+tempttr.ttr.j[t1]>=0)
		      t2++;
		if(t2==4)
		  {if(ch==75)
		     cttr.j--;
		   if(ch==77)
		     cttr.j++;
		   print();
		   cttrprint();}
	       }
	     else if(ch==80)
	       break;
	     else
	       {if(ch=='p')
		  getch();
		if(ch=='q')
		  exit(ch - 'q');}
	    }
	  delay(time);
	  check++;
	  if(check==25)
	    break;
	 }while(check<25);

       t2=0;
       t3=0;
       for(t1=0;t1<4;t1++)
	  {if(cttr.ttr.i[t1]>t2)
	     t2=cttr.ttr.i[t1];
	   if(cttr.ttr.j[t1]>t3)
	     t3=cttr.ttr.j[t1];}

       check=0;
       for(j=0;j<10;j++)
	  if(board1[cttr.i+t2+1][j]==0&&cttr.i+t2+1<20)
	    check++;

       if(check==10)
	 {cttr.i++;
	  print();
	  cttrprint();}
       else
	 {tempttr=cttr;
	  tempttr.i++;
	  check=0;
	  for(t1=0;t1<4;t1++)
	     if(board1[tempttr.ttr.i[t1]+tempttr.i]
		      [tempttr.ttr.j[t1]+tempttr.j]==0&&cttr.i+t2+1<20)
	       check++;
	  if(check==4)
	    {cttr.i++;
	     print();
	     cttrprint();}
	  else
	    {for(t1=0;t1<4;t1++)
		{board1[cttr.ttr.i[t1]+cttr.i]
		       [cttr.ttr.j[t1]+cttr.j]=1;
		 board[cttr.ttr.i[t1]+cttr.i]
		      [cttr.ttr.j[t1]+cttr.j]=cttr.ttr.col;
		 end=1;}
	     score+=10;

	     t1=0;
	     for(i=0;i<20;i++)
		{check=0;
		 for(j=0;j<10;j++)
		    if(board1[i][j]==1)
		      check++;
		 if(check==10)
		   {t1++;
		    score+=100;
		    lines+=1;
		    for(t2=i;t2>0;t2--)
		       for(t3=0;t3<10;t3++)
			  {board[t2][t3]=board[t2-1][t3];
			   board1[t2][t3]=board1[t2-1][t3];}
		    for(j=0;j<10;j++)
		       {board[0][j]=0;
			board1[0][j]=0;}
		   }
		}
	     if(t1==4)
	       score+=400;
	    }
	 }
      }while(end==0);
    print();
    cttrprint();

    level=score/1000+1;
    if(level>10)
      level=10;
    time=21-level*2;
   }while(finish==0);

 if(finish==1)
   {cleardevice();
    background();
    status();}

}

/***** NEXT *****/

void next(int n)
{int x,y,i,j,a;

 x=490;
 y=140;

 setfillstyle(1,0);
 for(i=0;i<4;i++)
    for(j=0;j<4;j++)
       floodfill(x+j*23+5,y+i*23+5,15);

 setfillstyle(1,ttr[n].col);

 for(a=0;a<4;a++)
    floodfill(x+ttr[n].j[a]*23+1,y+ttr[n].i[a]*23+1,15);

}

/**** ROTATE *****/

void rotate(tetrimino &ttr)
{int a[4][4],i,j,temp[4][4],check,x;

 for(i=0;i<4;i++)
    for(j=0;j<4;j++)
       a[i][j]=0;

 for(i=0;i<4;i++)
    for(j=0;j<4;j++)
       for(x=0;x<4;x++)
	  if(ttr.i[x]==i&&ttr.j[x]==j)
	    a[i][j]=1;

 for(i=0;i<4;i++)
    for(j=0;j<4;j++)
       temp[i][j]=a[3-j][i];

 for(i=0;i<4;i++)
    for(j=0;j<4;j++)
       a[i][j]=temp[i][j];

 do{check=0;
    for(j=0;j<4;j++)
       if(a[0][j]==0)
	 check++;
    if(check==4)
      {for(i=0;i<3;i++)
	  for(j=0;j<4;j++)
	     a[i][j]=a[i+1][j];
       for(j=0;j<4;j++)
	  a[3][j]=0;}
    }while(check==4);

 do{check=0;
    for(i=0;i<4;i++)
       if(a[i][0]==0)
	 check++;
    if(check==4)
      {for(j=0;j<3;j++)
	  for(i=0;i<4;i++)
	     a[i][j]=a[i][j+1];
       for(i=0;i<4;i++)
	  a[i][3]=0;}
    }while(check==4);

 check=0;

 for(i=0;i<4;i++)
    for(j=0;j<4;j++)
       if(a[i][j]!=0)
	 {ttr.i[check]=i;
	  ttr.j[check]=j;
	  check++;}

}