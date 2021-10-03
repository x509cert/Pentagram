#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <ctype.h>
#include <butil.h>
#include "mmalloc.h"

#define GAME_OVER   9999
#define GAME_STX    40
#define GAME_STY    30
#define GAME_BOXSZX 14
#define GAME_BOXSZY 12
#define MARB_PLAYER 1
#define MARB_DEMON	2

static char marble_pic[][13]={
				  {0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0},
				  {0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0,0x0},
				  {0x0,0x1,0x1,0x1,0x2,0x2,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
				  {0x0,0x1,0x1,0x2,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
				  {0x1,0x1,0x2,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
				  {0x1,0x1,0x2,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
				  {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
				  {0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
				  {0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
				  {0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0,0x0},
				  {0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0},
             };

static int          board[8][8],weightings[8][8],coords[64][2];
static int          over,xx=0,yy=0,go=0;
static int          player_won;
static char _FAR	*undermarble_image;

void _PASCAL hall_play_demon_marbles()
{
	GWINDOW win;
	char temp[60];
	unsigned long bet;

	player_won=FALSE;

	win.x1=3;
	win.y1=2;
	win.x2=30;
	win.y2=19;
	win.back=0;
	win.border=4;

	undermarble_image=(char _FAR *)Mmalloc(200);

	if (undermarble_image==NULL)
		panic_RAM("Marbles");

	bet=hall_get_bet();

	if (bet!=0L)
	{
		sprintf(temp,"%s places a bet of %lu GC.",adv.name,bet);
		SCROLL(1,0,temp);

		make_gwindow(&win);

		xx=0;
		yy=0;

		marbles_startscreen();
		go=rand()%2;

		over=FALSE;

		if (go)
		{
			go=FALSE;

			while (!over)
			{
				marbles_playerselect();
				marbles_evaluate();

				if (!over)
				{
					marbles_computerselect();
					marbles_evaluate();
				}
			}

			marbles_won(over);

		}
		else
		{
			go=TRUE;
			marbles_evaluate();

			while (!over)
			{
				marbles_computerselect();
				marbles_evaluate();

				if (!over)
				{
					marbles_playerselect();
					marbles_evaluate();
				}
			}

			marbles_won(over);
		}

		kill_gwindow(&win);
	}

	if (player_won)
	{
		sprintf(temp,"%s hath just won %lu GC!",adv.name,bet*25L);
		GX(temp,GOOD);

		adv.cash+=bet*25L;
	}

	Mfree(undermarble_image);
}	

void _PASCAL _NEAR marbles_startscreen()
{
	generic_pic_draw(GAME_STX-14,GAME_STY-10,"GAME");
	memset(&board[0][0],0,sizeof(board));

	_setcolor(8);
	_rectangle(_GFILLINTERIOR,GAME_STX,GAME_STY,GAME_STX+110,GAME_STY+95);

	print_up_down(186,26);
	print_left_right(186,41);

	click_box(180,63,B_OK);
	click_box(180,85,B_QUIT);

	draw_marble(192,105,MARB_PLAYER,FALSE);
	print_text("YOU",186,107,NORMAL_HEIGHT,14);

	draw_marble(192,120,MARB_DEMON,FALSE);
	print_text("DEMON",178,122,NORMAL_HEIGHT,14);
}

void _PASCAL _NEAR marbles_updatescreen(int x,int y)
{
	int xx,yy;

	xx=x*GAME_BOXSZX+GAME_STX;
	yy=y*GAME_BOXSZY+GAME_STY;

	draw_marble(xx,yy,board[x][y],TRUE);
}

static void _PASCAL _NEAR marbles_cursor(int x,int y,int onoff)
{
	int xx,yy;

	xx=x*GAME_BOXSZX+GAME_STX;
	yy=y*GAME_BOXSZY+GAME_STY;

	if (onoff==ON)
	{
		_getimage(xx,yy,xx+GAME_BOXSZX,yy+GAME_BOXSZY,undermarble_image);

		_setcolor(15);
		_moveto(xx+4,yy+5);
		_lineto(xx+8,yy+5);

		_moveto(xx+6,yy+3);
		_lineto(xx+6,yy+7);
	}
	else
	{
		_putimage(xx,yy,undermarble_image,_GPSET);
	}
}

void _PASCAL _NEAR marbles_playerselect()
{
	int c=0,fin=FALSE;
	static int boundary[]={198,26,208,35,
						   186,26,196,35,
						   198,41,208,52,
						   185,41,196,52,
						   180,63,215,75,
						   180,85,215,97,
							-1,-1,-1,-1};

	marbles_cursor(xx,yy,ON);

	while (!fin)
	{
		c=mouse_in_range(boundary,"\xC8""\xD0""\xCD""\xCBªª","ªªªª Q");

		marbles_cursor(xx,yy,OFF);

		if (c<4)
		{
			switch(c)
			{
				case 0 : yy--; break;
				case 1 : yy++; break;
				case 2 : xx++; break;
				case 3 : xx--; break;
			}

			if (xx<0) xx=7;
			if (xx>7) xx=0;
			if (yy<0) yy=7;
			if (yy>7) yy=0;

			marbles_cursor(xx,yy,ON);
		}
		else
		if (c==4)                       /* Space pressed */
		{
			if (board[xx][yy] == 0)
			{
				board[xx][yy]=MARB_PLAYER;
				marbles_cursor(xx,yy,OFF);
				marbles_updatescreen(xx,yy);
				fin=TRUE;
			}
			else
			{
				bad_sound2();
				marbles_cursor(xx,yy,ON);
			}
		}
		else
		{
			fin=gget_yn("Art thou yielding so soon?");

			if (fin)
			{
				over=MARB_DEMON;
			}
			else
				marbles_cursor(xx,yy,ON);
		}
	}
}

void _PASCAL _NEAR marbles_evaluate()
{
	int j,k,l,p,c;

	memset(&weightings[0][0],0,sizeof(weightings));

	for (j=0;j<8;j++)
	{
		for (k=0;k<5;k++)
		{
			p=0; c=0;

			for (l=0;l<4;l++)
			{
				switch (board[j][k+l])
				{
					case 1: p++; break;
					case 2: c++; break;
				}
			}

			p=marbles_new(p,MARB_PLAYER);
			c=marbles_new(c,MARB_DEMON);

			if (p == GAME_OVER)
				over=MARB_PLAYER;

			if (c == GAME_OVER)
				over=MARB_DEMON;

			if (p == 0 && c>0)
				for (l=0;l<4;l++)
					weightings[j][k+l]+=c;

			if (c == 0 && p>0)
				for (l=0;l<4;l++)
					weightings[j][k+l]+=p;
		}
	}

	for (k=0;k<8;k++)
	{
		for (j=0;j<5;j++)
		{
			p=0; c=0;

			for (l=0;l<4;l++)
			{
				switch (board[j+l][k])
				{
					case 1: p++; break;
					case 2: c++; break;
				}
			}

			p=marbles_new(p,MARB_PLAYER);
			c=marbles_new(c,MARB_DEMON);

			if (p == GAME_OVER)
				over=MARB_PLAYER;

			if (c == GAME_OVER)
				over=MARB_DEMON;

			if (p == 0 && c>0)
				for (l=0;l<4;l++)
					weightings[j+l][k]+=c;

			if (c == 0 && p>0)
				for (l=0;l<4;l++)
					weightings[j+l][k]+=p;
		}
	}

	for (j=0;j<5;j++)
	{
		for (k=0;k<5;k++)
		{
			p=0; c=0;

			for (l=0;l<4;l++)
			{
				switch(board[j+l][k+l])
				{
					case 1: p++; break;
					case 2: c++; break;
				}
			}

			p=marbles_new(p,MARB_PLAYER);
			c=marbles_new(c,MARB_DEMON);

			if (p == GAME_OVER)
				over=MARB_PLAYER;

			if (c == GAME_OVER)
				over=MARB_DEMON;

			if (p == 0 && c>0)
				for (l=0;l<4;l++)
					weightings[j+l][k+l]+=c;

			if (c == 0 && p>0)
				for (l=0;l<4;l++)
					weightings[j+l][k+l]+=p;
		}
	}

	for (j=3;j<8;j++)
	{
		for (k=0;k<5;k++)
		{
			p=0; c=0;

			for (l=0;l<4;l++)
			{
				switch(board[j-l][k+l])
				{
					case 1: p++; break;
					case 2: c++; break;
				}
			}

			p=marbles_new(p,MARB_PLAYER);
			c=marbles_new(c,MARB_DEMON);

			if (p == GAME_OVER)
				over=MARB_PLAYER;

			if (c == GAME_OVER)
				over=MARB_DEMON;

			if (p == 0 && c>0)
				for (l=0;l<4;l++)
					weightings[j-l][k+l]+=c;

			if (c == 0 && p>0)
				for (l=0;l<4;l++)
					weightings[j-l][k+l]+=p;
		}
	}
}

void _PASCAL _NEAR marbles_computerselect()
{
	int t,top,x,y,j,k,l;

	top=0;

	for (j=0;j<8;j++)
		for (k=0;k<8;k++)
			if (board[j][k] == 0)
				if ((l=weightings[j][k]) > top)
					top=l;

	l=0;

	for (j=0;j<8;j++)
	{
		for (k=0;k<8;k++)
		{
			if (weightings[j][k]==top && board[j][k]==0)
			{
				coords[l][0]=j;
				coords[l][1]=k;
				l++;
			}
		}
	}

	t=rand()%l;

	x=coords[t][0];
	y=coords[t][1];

	board[x][y]=MARB_DEMON;
	marbles_updatescreen(x,y);
}

int _PASCAL _NEAR marbles_new(int num,int player)
{
	switch(num)
	{
		case 0 : return(0);
		case 1 : return(player*2);
		case 2 : return(player*10);
		case 3 : return(player*75);
		case 4 : return(GAME_OVER);
	}

	return(0);
}

void _PASCAL _NEAR marbles_won(int player)
{
	static char *won[]={ "\"A curse on thee! Thou hast won!\"",
						 "\"Thou art lucky and hath beaten me!\"",
						 "\"Luck doth ride with thee! Thou hast won!\""};
	static char *lose[]={"\"I win! I am indeed ye Lord of Demon Marbles!\"",
						 "\"Come play once more..if thou wish to be beaten again!\"",
						 "\"I win..again..and again..and again!\""};

	half_pause();

	if (player==MARB_PLAYER)
	{
		GX(won[rand()%SIZE(won)],GOOD);
		player_won=TRUE;
	}
	else
	{
		GX(lose[rand()%SIZE(lose)],SOLEMN);
	}
}

void _PASCAL _NEAR draw_marble(int x,int y,int player,int del)
{
	int col1,col2;
	int i,j,k,c;

	if (player==MARB_PLAYER)
	{
		col1=4;
		col2=12;

		for (i=0;i<11;i++)
		{
			for (j=0;j<13;j++)
			{
				if (c=marble_pic[i][j])
					FFPLOT(j+x,i+y,(char)(c==1?col1:col2));
			}
		}

		if (!NO_SOUND)
		{
			utspkr(1000);
			delay(50);
			utspkr(0);
		}
	}
	else
	{
		col1=9;
		col2=11;

		if (del)
		{
			delay(50+rand()%600);

			for (i=0; i<600; i++)
			{
				j=rand()%11;
				k=rand()%13;

				if (c=marble_pic[j][k])
					FFPLOT(k+x,j+y,(char)(c==1?col1:col2));

				delay(2);
			}
		}

		for (i=0; i<11; i++)
			for (j=0; j<13; j++)
				if (c=marble_pic[i][j])
					FFPLOT(j+x,i+y,(char)(c==1?col1:col2));

		if (!NO_SOUND)
		{
			utspkr(500);
			delay(50);
			utspkr(0);
		}
	}
}

void _PASCAL hall_get_rules()
{
	int rule_no;
	GWINDOW win;
	int fin=FALSE;
	static int boundary[]={ 70,150,105,162,
						   123,150,158,162,
						   176,150,211,162,
							-1,-1,-1,-1};

	win.x1=7;
	win.y1=5;
	win.x2=30;
	win.y2=22;
	win.back=0;
	win.border=13;

	make_gwindow(&win);

	click_box( 70,150,B_PREV);
	click_box(123,150,B_NEXT);
	click_box(176,150,B_FINISH);

	rule_no=0;

	while (!fin)
	{
		hall_get_rules_cls();

		switch(rule_no)
		{
			case 0 : hall_get_rules_high_low(win.x1,win.y1);    break;
			case 1 : hall_get_rules_wizard_dice(win.x1,win.y1); break;
			case 2 : hall_get_rules_blackjack(win.x1,win.y1);   break;
			case 3 : hall_get_rules_marbles(win.x1,win.y1);     break;
		}

		switch(mouse_in_range(boundary,"PNF","PFQ"))
		{
			case 0 : rule_no--; break;
			case 1 : rule_no++; break;
			default: fin=TRUE;  break;
		}

		if (rule_no<0)
			rule_no=0;

		if (rule_no>3)
			rule_no=3;
	}

	kill_gwindow(&win);
}

void _PASCAL _NEAR hall_get_rules_cls()
{
	_setcolor(0);
	_rectangle(_GFILLINTERIOR,51,35,228,144);
}

void _PASCAL _NEAR hall_get_rules_marbles(int x,int y)
{
	char *title="Rules (Demon Marbles)";
	int i;
	static char *text[]={"This  game  of  skill",
						 "gets  its  name  from",
						 "the belief that a dem",
						 "-ons soul  is trapped",
						 "in the playing board.",
						 "The object  is to get",
						 "4 balls in a straight",
						 "line whilst  prevent-",
						 "ing the  demon  doing",
						 "the   same.  Use  the",
						 "Cursor keys, spacebar",
						 "and escape keys."};

	_settextcolor(14);
	_settextposition(y+1,x+1);
	_outtext(title);

	_settextcolor(5);

	for (i=0; i<SIZE(text); i++)
	{
		_settextposition(y+i+2,x+1);
		_outtext(text[i]);
	}
}

void _PASCAL _NEAR hall_get_rules_high_low(int x,int y)
{
	char *title="Rules (High Low)";
	int i;
	static char *text[]={"Five  Cards  are laid",
						 "out  face  down.  The",
						 "first card  is turned",
						 "up and you  must det-",
						 "ermine  if  the  next",
						 "card is  Higher/Lower",
						 "or   Red/Black .  The",
						 "game  is  won if  you",
						 "guess  all the cards.",
						 "",
						 "Aces are high."};

	_settextcolor(14);
	_settextposition(y+1,x+1);
	_outtext(title);

	_settextcolor(5);

	for (i=0; i<SIZE(text); i++)
	{
		_settextposition(y+i+2,x+1);
		_outtext(text[i]);
	}
}

void _PASCAL _NEAR hall_get_rules_wizard_dice(int x,int y)
{
	char *title="Rules (Wizard Dice)";
	int i;
	static char *text[]={"A wager is placed on",
						 "the  outcome of  two",
						 "dice.  The  dice are",
						 "then thrown  and the",
						 "results noted.",
						 "",
						 "7 always loses.",
						 "",
						 "2,3 4,10,11  and  12",
						 "pay 3-1.",
						 "",
						 "5,6,8 and 9 pay 2-1."};

	_settextcolor(14);
	_settextposition(y+1,x+1);
	_outtext(title);

	_settextcolor(5);

	for (i=0; i<SIZE(text); i++)
	{
		_settextposition(y+i+2,x+1);
		_outtext(text[i]);
	}
}

void _PASCAL _NEAR hall_get_rules_blackjack(int x,int y)
{
	char *title="Rules (5 Card Jack)";
	int i;
	static char *text[]={"5 cards  are dealt to",
						 "the player and house.",
						 "The   house's   first",
						 "card is turned as are",
						 "the   player's  first",
						 "two. The objective is",
						 "for the player to get",
						 "as  close  to  21  by",
						 "taking  more   cards,",
						 "and getting  a higher",
						 "score than the house.",
						 "Aces count as 11"
						 };

	_settextcolor(14);
	_settextposition(y+1,x+1);
	_outtext(title);

	_settextcolor(5);

	for (i=0; i<SIZE(text); i++)
	{
		_settextposition(y+i+2,x+1);
		_outtext(text[i]);
	}
}
