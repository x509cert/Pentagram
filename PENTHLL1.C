#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <butil.h>
#include <bkeybrd.h>
#include "mmalloc.h"

static char _FAR *card_front_im;
static char _FAR *card_back_im;

static CARDS cards[]={
				CS_HEARTS,      CV_TWO,
				CS_HEARTS,      CV_THREE,
				CS_HEARTS,      CV_FOUR,
				CS_HEARTS,      CV_FIVE,
				CS_HEARTS,      CV_SIX,
				CS_HEARTS,      CV_SEVEN,
				CS_HEARTS,      CV_EIGHT,
				CS_HEARTS,      CV_NINE,
				CS_HEARTS,      CV_TEN,
				CS_HEARTS,      CV_JACK,
				CS_HEARTS,      CV_QUEEN,
				CS_HEARTS,      CV_KING,
				CS_HEARTS,      CV_ACE,

				CS_SPADES,      CV_TWO,
				CS_SPADES,      CV_THREE,
				CS_SPADES,      CV_FOUR,
				CS_SPADES,      CV_FIVE,
				CS_SPADES,      CV_SIX,
				CS_SPADES,      CV_SEVEN,
				CS_SPADES,      CV_EIGHT,
				CS_SPADES,      CV_NINE,
				CS_SPADES,      CV_TEN,
				CS_SPADES,      CV_JACK,
				CS_SPADES,      CV_QUEEN,
				CS_SPADES,      CV_KING,
				CS_SPADES,      CV_ACE,

				CS_CLUBS,       CV_TWO,
				CS_CLUBS,       CV_THREE,
				CS_CLUBS,       CV_FOUR,
				CS_CLUBS,       CV_FIVE,
				CS_CLUBS,       CV_SIX,
				CS_CLUBS,       CV_SEVEN,
				CS_CLUBS,       CV_EIGHT,
				CS_CLUBS,       CV_NINE,
				CS_CLUBS,       CV_TEN,
				CS_CLUBS,       CV_JACK,
				CS_CLUBS,       CV_QUEEN,
				CS_CLUBS,       CV_KING,
				CS_CLUBS,       CV_ACE,

				CS_DIAMONDS,    CV_TWO,
				CS_DIAMONDS,    CV_THREE,
				CS_DIAMONDS,    CV_FOUR,
				CS_DIAMONDS,    CV_FIVE,
				CS_DIAMONDS,    CV_SIX,
				CS_DIAMONDS,    CV_SEVEN,
				CS_DIAMONDS,    CV_EIGHT,
				CS_DIAMONDS,    CV_NINE,
				CS_DIAMONDS,    CV_TEN,
				CS_DIAMONDS,    CV_JACK,
				CS_DIAMONDS,    CV_QUEEN,
				CS_DIAMONDS,    CV_KING,
				CS_DIAMONDS,    CV_ACE,
			  };

void _PASCAL hall()
{
	GWINDOW win;
	static char person[180];
	static    char *t[]={"High-Low",
						 "Five Card Jack",
						 "Wizard Dice",
						 "Demon Marbles",
						 "House Rules",
						 "Leave ye Hall"};
	int i;
	char *letters="HFWDRL";
	int fin=FALSE;
	static int boundary[]={96,48,208,54,
						   96,56,208,62,
						   96,64,208,70,
						   96,72,208,78,
						   96,80,208,86,
						   96,88,208,94,
						   -1,-1,-1,-1};

	print_large_title("AT YE GAMING HALL");

	if (who_is_going("Who enters ye Hall?")==ERR)
		return;

	if (player_is_dead(&adv))
	{
		sprintf(person,"%s art dead!",adv.name);
		GX(person,BAD);
		return;
	}

	if (player_is_drunk(&adv))
	{
		player_is_drunk_so_leave(&adv,"Hall");
		return;
	}

	load_card_images();

	while (!fin)
	{
		win.x1=12;
		win.y1=6;
		win.x2=28;
		win.y2=14;
		win.back=0;
		win.border=4;

		make_gwindow(&win);

		print_menu_options(t,
						   SIZE(t),
						   letters,
						   win.x1+1,
						   win.y1+1,
						   5,
						   13);

		cls_scroll();

		sprintf(person,"%s hath %lu GC left.",adv.name,adv.cash);
		SCROLL(2,0,person);

		SCROLL(1,14,"Please select thy game.....");

		i=mouse_in_range(boundary,"HFWDRQ",letters);

		kill_gwindow(&win);

		switch(i)
		{
			case 0  :   hall_play_high_low();      break;
			case 1  :   hall_play_black_jack();    break;
			case 2  :   hall_play_wizard_dice();   break;
			case 3  :   hall_play_demon_marbles(); break;
			case 4  :   hall_get_rules();          break;
			default :   fin=TRUE;                  break;
		}

		cls();
	}

	if ((adv.cash>100) && (adv.level<5) && (adv.nrace!=HALF_OGRE) &&
	   (((unsigned)(rand()%32)>(adv.luck+adv.agility))))
		hall_get_attacked();

	kill_card_images();

	save_adventurer(&adv);
}

void _PASCAL load_card_images()
{
#define IM_SIZE  380

	char temp[40];
	FILE *fptr;

	card_back_im =(char _FAR *)Mmalloc(IM_SIZE);
	card_front_im=(char _FAR *)Mmalloc(IM_SIZE);

	sprintf(temp,"%sCARDFRNT.PIC",PIC_DIRECTORY);

	if ((fptr=fopen(temp,"rb"))==NULL)
		panic_FILE(temp);

	fread((void *)card_front_im,IM_SIZE,1,fptr);

	fclose(fptr);

	sprintf(temp,"%sCARDBACK.PIC",PIC_DIRECTORY);

	if ((fptr=fopen(temp,"rb"))==NULL)
		panic_FILE(temp);

	fread((void *)card_back_im,IM_SIZE,1,fptr);

	fclose(fptr);

#undef IM_SIZE
}

void _PASCAL kill_card_images()
{
	Mfree((void *)card_back_im);
	Mfree((void *)card_front_im);
}

void _PASCAL hall_play_high_low()
{
	int NUM_CARDS=5;
	int select;
	int i;
	char temp[80];
	long bet;
	char *title="High Low";
	int wrong=FALSE;

	_settextcolor(1);
	_settextposition(4,20-strlen_half(title));
	_outtext(title);

	bet=hall_get_bet();

	if (bet!=0L)
	{
		sprintf(temp,"%s places a bet of %lu GC.",adv.name,bet);
		SCROLL(1,0,temp);

		hall_shuffle_cards();

		for (i=0; i<NUM_CARDS; i++)
		{
			utspkr(0);

			hall_draw_card_back(i*40+65,50);

			if (!NO_SOUND)
			{
				utspkr((i+1)*100);
				delay(50);
			}
		}

		utspkr(0);

		hall_draw_card_front(65,50,cards[0].value,cards[0].suit);

		for (i=1; i<NUM_CARDS; i++)
		{
			hall_pointing_hand(i*40+72,85);

			select=hall_high_low_select();

			hall_kill_pointing_hand(i*40+72,85);

			hall_draw_card_front(i*40+65,50,cards[i].value,cards[i].suit);

			switch(select)
			{
				case B_HIGHER     :   if (cards[i].value<=cards[i-1].value)
										wrong=TRUE;

									  break;

				case B_LOWER      :   if (cards[i].value>=cards[i-1].value)
										wrong=TRUE;

									  break;

				case B_CARD_RED   :   if (cards[i].suit==CS_SPADES ||
										cards[i].suit==CS_CLUBS)
											wrong=TRUE;

									  break;

				case B_CARD_BLACK :   if (cards[i].suit==CS_DIAMONDS ||
										cards[i].suit==CS_HEARTS)
											wrong=TRUE;

									  break;
			}

			if (wrong)
			{
				oops(13);

				break;
			}
			else
			{
				good_sound();
			}
		}

		if (!wrong)
		{
			sprintf(temp,"%s hath just won %lu GC!",adv.name,bet*3L);
			GX(temp,GOOD);

			adv.cash+=bet*3L;
		}
	}
}

void _PASCAL hall_shuffle_cards()
{
	int i;
	int from,to;
	CARDS temp;
	GWINDOW win;

	win.x1=12;
	win.y1=7;
	win.x2=30;
	win.y2=10;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+1);
	_outtext("Shuffling Cards!");

	for (i=0; i<400; i++)
	{
		from=rand()%SIZE(cards);
		to=rand()%SIZE(cards);

		if (from==to)
			continue;

		temp=cards[to];
		cards[to]=cards[from];
		cards[from]=temp;
	}

	delay(300);

	kill_gwindow(&win);
}

int _PASCAL hall_high_low_select()
{
	GWINDOW win;
	int option;
	static int boundary[]={193,150,228,162,
						   193,130,228,142,
						   238,130,273,142,
						   238,150,273,162,
							-1,-1,-1,-1};
	win.x1=21;
	win.y1=14;
	win.x2=39;
	win.y2=23;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+1);
	_outtext("Be ye next card");

	click_box(193,150,B_CARD_RED);
	click_box(193,130,B_CARD_BLACK);
	click_box(238,150,B_LOWER);
	click_box(238,130,B_HIGHER);

	switch(mouse_in_range(boundary,"RBHL",""))
	{
		case 0 : option=B_CARD_RED;    break;
		case 1 : option=B_CARD_BLACK;  break;
		case 2 : option=B_HIGHER;      break;
		case 3 : option=B_LOWER;       break;
	}

	kill_gwindow(&win);

	return(option);
}

void _PASCAL hall_pointing_hand(int x,int y)
{
	char _FAR *image;
	long size;
	int dummy;
	int khit=FALSE;
	int i;

	generic_pic_draw(x,y,"HALLHAND");

	size=(long)_imagesize(x,y-1,x+13,y+12);

	image=(char _FAR *)Mmalloc((size_t)size);

	_getimage(x,y-1,x+13,y+12,image);

	for (i=0; i<13; i++)
	{
		_putimage(x,y,image,_GPSET);
		delay(50);

		_putimage(x,y+1,image,_GPSET);
		delay(50);

		if (kbhit())
		{
			khit=TRUE;
			break;
		}

		if (mouse_button_l())
			break;
	}

	if (khit)
		kbgetkey(&dummy);

	Mfree((void *)image);
}

void _PASCAL hall_kill_pointing_hand(int x,int y)
{
	_setcolor(0);
	_rectangle(_GFILLINTERIOR,x,y,x+13,y+13);
}

void _PASCAL hall_draw_card_back(int x,int y)
{
	_putimage(x,y,card_back_im,_GPSET);
}

void _PASCAL hall_draw_card_front(int x,int y,int value,int suit)
{

#define XV 3
#define YV 3
#define XS 15
#define YS 19

	int i,j;
	char *val;
	int col=((suit==CS_HEARTS || suit==CS_DIAMONDS)?4:0);

	_putimage(x,y,card_front_im,_GPSET);

	switch(value)
	{
		case CV_TWO   : val="2"; break;
		case CV_THREE : val="3"; break;
		case CV_FOUR  : val="4"; break;
		case CV_FIVE  : val="5"; break;
		case CV_SIX   : val="6"; break;
		case CV_SEVEN : val="7"; break;
		case CV_EIGHT : val="8"; break;
		case CV_NINE  : val="9"; break;
		case CV_TEN   : val="T"; break;
		case CV_JACK  : val="J"; break;
		case CV_QUEEN : val="Q"; break;
		case CV_KING  : val="K"; break;
		case CV_ACE   : val="A"; break;
	}

	print_text(val,x+XV,y+YV,DOUBLE_HEIGHT,col);

	switch(suit)
	{
		case CS_HEARTS   :  for (i=0; i<7; i++)
								for (j=0; j<7; j++)
									if (cards_hearts[i][j])
										FFPLOT(j+x+XS,i+y+YS,(char)cards_hearts[i][j]);

							break;

		case CS_DIAMONDS :  for (i=0; i<7; i++)
								for (j=0; j<7; j++)
									if (cards_diamonds[i][j])
										FFPLOT(j+x+XS,i+y+YS,(char)cards_diamonds[i][j]);

							break;

		case CS_CLUBS    :  for (i=0; i<7; i++)
								for (j=0; j<7; j++)
									if (cards_clubs[i][j])
										FFPLOT(j+x+XS,i+y+YS,(char)cards_clubs[i][j]);

							break;

		case CS_SPADES   :  for (i=0; i<7; i++)
								for (j=0; j<7; j++)
									if (cards_spades[i][j])
										FFPLOT(j+x+XS,i+y+YS,(char)cards_spades[i][j]);

							break;
	}

#undef XV
#undef YV
#undef XS
#undef YS
}

long _PASCAL hall_get_bet()
{
	char temp[80];
	GWINDOW win;
	unsigned long num;
	char *pic="[   ]";
	int fin=FALSE;

	win.x1=3;
	win.y1=7;
	win.x2=36;
	win.y2=13;
	win.back=0;
	win.border=4;

	while (!fin)
	{
		make_gwindow(&win);

		_settextcolor(7);

		strcpy(temp,"How much dost thou bet?");

		_settextposition(win.y1+1,20-strlen_half(temp));
		_outtext(temp);

		strcpy(temp,"A bet of 0 GC quits ye game.");

		_settextposition(win.y1+2,20-strlen_half(temp));
		_outtext(temp);

		_settextposition(win.y1+4,18);
		_outtext(pic);

		strcpy(temp,gquery(19,win.y1+4,2,2,'N',""));

		kill_gwindow(&win);

		if (strlen(temp))
			num=atol(temp);
		else
			num=0L;

		if (num==0L)
		{
			fin=TRUE;
		}
		else
		{
			if (num>adv.cash)
			{
				if (adv.cash==0L)
					sprintf(temp,"%s hath no money!",adv.name);
				else
					sprintf(temp,"%s hath but %lu GC!",adv.name,adv.cash);

				GX(temp,BAD);

				fin=FALSE;
			}
			else
			{
				adv.cash-=num;
				fin=TRUE;
			}
		}
	}

	return(strlen(temp)?num:0L);
}

void _PASCAL hall_play_wizard_dice()
{
	int i;
	char temp[80];
	long bet;
	char *title="Wizard Dice";
	char *hope1="Hoping for 2,3,4,10,11 or 12";
	char *hope2="Hoping for 5,6,8 or 9";
	int won=FALSE;
	int dice1,dice2;
	int bet_type;
	int total;

	_settextcolor(1);
	_settextposition(4,20-strlen_half(title));
	_outtext(title);

	bet=hall_get_bet();

	if (bet!=0L)
	{
		sprintf(temp,"%s places a bet of %lu GC.",adv.name,bet);
		SCROLL(1,0,temp);

		bet_type=hall_dice_select_bet();

		_settextcolor(9);
		strcpy(temp,bet_type?hope2:hope1);
		_settextposition(5,20-strlen_half(temp));
		_outtext(temp);


		hall_place_dice();

		for (i=0; i<30; i++)
			dice1=hall_shake_dice(0);

		pause(1);

		for (i=0; i<30; i++)
			dice2=hall_shake_dice(1);

		total=dice1+dice2;

		won=FALSE;

		sprintf(temp,"Wizard Dice total art %d",total);
		_settextcolor(5);
		_settextposition(13,20-strlen_half(temp));
		_outtext(temp);

		switch(bet_type)
		{
			case 0 : if (total==2  || total==3  || total==4 ||
						 total==10 || total==11 || total==12)
							won=TRUE;

					 break;

			case 1 : if (total==5 || total==6 || total==8 || total==9)
						won=TRUE;

					 break;
		}

		if (won)
		{
			delay(500);

			if (bet_type==0)
				adv.cash+=bet*3L;
			else
				adv.cash+=bet*2L;

			sprintf(temp,"%s hath just won %lu GC!",adv.name,
												   bet_type?bet*2L:bet*3L);
			GX(temp,GOOD);
		}
		else
			oops(15);

		strcpy(temp,"                             ");
		_settextposition(13,20-strlen_half(temp));
		_outtext(temp);

		_settextposition(5,20-strlen_half(temp));
		_outtext(temp);

	}
}

int _PASCAL hall_dice_select_bet()
{
	GWINDOW win;
	int back;
	char temp[40];
	char *t1="2,3,4,10,11 or 12";
	char *t2="5,6,8 or 9";
	static int boundary[]={87, 80,221,86,
						   112,88,189,94,
							-1,-1,-1,-1};

	win.x1=5;
	win.y1=7;
	win.x2=35;
	win.y2=14;
	win.back=0;
	win.border=11;

	make_gwindow(&win);

	_settextcolor(9);

	strcpy(temp,"What outcome does");
	_settextposition(win.y1+1,20-strlen_half(temp));
	_outtext(temp);

	sprintf(temp,"%s wish to back?",adv.name);
	_settextposition(win.y1+2,20-strlen_half(temp));
	_outtext(temp);

	_settextcolor(5);
	_settextposition(win.y1+4,20-strlen_half(t1));
	_outtext(t1);
	_settextcolor(13);
	_settextposition(win.y1+4,20-strlen_half(t1));
	_outtext("2");

	_settextcolor(5);
	_settextposition(win.y1+5,20-strlen_half(t2));
	_outtext(t2);
	_settextcolor(13);
	_settextposition(win.y1+5,20-strlen_half(t2));
	_outtext("5");

	back=mouse_in_range(boundary,"25","");

	kill_gwindow(&win);

	return(back);
}

void _PASCAL hall_place_dice()
{
	_setcolor(DICE_COLOUR);
	_rectangle(_GFILLINTERIOR,105,50,145,80);
	_rectangle(_GFILLINTERIOR,175,50,215,80);

	_setcolor(DICE_COLOUR+8);
	_rectangle(_GBORDER,105,50,145,80);
	_rectangle(_GBORDER,175,50,215,80);

	FFPLOT(105,50,(char)0);
	FFPLOT(105,80,(char)0);
	FFPLOT(145,50,(char)0);
	FFPLOT(145,80,(char)0);

	FFPLOT(175,50,(char)0);
	FFPLOT(175,80,(char)0);
	FFPLOT(215,50,(char)0);
	FFPLOT(215,80,(char)0);
}

int _PASCAL hall_shake_dice(int num)
{
	int value;
	int i,j;
	int x,y;
	int offset;
	int xdist=10;
	static char *faces[]={"   ",
						  " O ",
						  "   ",

						  "O  ",
						  "   ",
						  "  O",

						  "O  ",
						  " O ",
						  "  O",

						  "O O",
						  "   ",
						  "O O",

						  "O O",
						  " O ",
						  "O O",

						  "O O",
						  "O O",
						  "O O"};
	x=num?183:113;
	y=53;

	value=rand()%6;
	value++;

	offset=(value-1)*3;

	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			if (faces[i+offset][j]=='O')
			{
				_setcolor(15);
				_rectangle(_GFILLINTERIOR,x+j*xdist,
										  y+i*xdist,
										  x+j*xdist+4,
										  y+i*xdist+4);

				FFPLOT(x+j*xdist,  y+i*xdist,  (char)DICE_COLOUR);
				FFPLOT(x+j*xdist+4,y+i*xdist,  (char)DICE_COLOUR);
				FFPLOT(x+j*xdist,  y+i*xdist+4,(char)DICE_COLOUR);
				FFPLOT(x+j*xdist+4,y+i*xdist+4,(char)DICE_COLOUR);
			}
			else
			{
				_setcolor(DICE_COLOUR);
				_rectangle(_GFILLINTERIOR,x+j*xdist,
										  y+i*xdist,
										  x+j*xdist+4,
										  y+i*xdist+4);
			}
		}
	}

	if (!NO_SOUND)
	{
		utspkr(300+value*75);
		delay(30);
		utspkr(0);
	}

	return(value);
}

void _PASCAL hall_get_attacked()
{
	unsigned long i;
	char temp[90];

	i=(long)rand()%80;
	i+=5;

	if (adv.cash>200)
		i+=50;

	if (adv.cash>500)
		i+=100;

	if (adv.cash>1000)
		i+=400;

	if (adv.cash>2000)
		i+=1200;

	cls_scroll();
	sprintf(temp,"JUST AS %s LEAVES YE GAMING HALL YE WORLD GOES BLACK.",adv.name);
	scroll_wrap_write(0,temp);
	bad_sound();

	pause(2);

	SCROLL(2,14,"AS YE SLOWLY COME TO THY SENSES AND "
				"PICK THYSELF UP OFF YE GROUND, YE NOTICE "
				"THY PURSE FEELS A LITTLE LIGHTER"
				"..AND YE HAVE A SPLITTING HEADACHE!");

	pause(4);

	SCROLL(2,0,"YE HURRIDLY OPEN THY PURSE AND COUNT THY MONEY...");

	sprintf(temp,"....AND NOTICE THAT YE NOW ONLY HAVE %lu GC LEFT FROM %lu.",
				  adv.cash-i,
				  adv.cash);

	SCROLL(1,0,temp);

	adv.cash-=i;
	pause(2);

	sprintf(temp,"%s HATH BEEN MUGGED!",adv.name);
	SCROLL(2,14,temp);

	bad_sound2();
	pause(4);
}

void _PASCAL oops(int y)
{
	GWINDOW win;

	win.x1=13;
	win.y1=y;
	win.x2=30;
	win.y2=y+3;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	_settextcolor(6);
	_settextposition(win.y1+1,win.x1+1);
	_outtext("...ooOOOOPPSSS!");

	solemn_sound();

	pause(2);

	kill_gwindow(&win);
}

void _PASCAL hall_play_black_jack()
{
	int NUM_CARDS=5;
	int i;
	char temp[80];
	long bet;
	char *title="Five Card Jack";
	int player_won,   dealer_won;
	int player_lost,  dealer_lost;
	int player_total, dealer_total;
	int dealer_y=40;
	int player_y=80;
	int card_number;
	int player_fin;
	int dealer_fin;

	_settextcolor(1);
	_settextposition(4,20-strlen_half(title));
	_outtext(title);

	player_won=dealer_won=player_lost=dealer_lost=player_fin=dealer_fin=FALSE;

	player_total=dealer_total=0;

	bet=hall_get_bet();

	if (bet!=0L)
	{
		sprintf(temp,"%s places a bet of %lu GC.",adv.name,bet);
		SCROLL(1,0,temp);

		hall_shuffle_cards();

		for (i=0; i<NUM_CARDS; i++)
		{
			utspkr(0);

			hall_draw_card_back(i*40+65,dealer_y);
			hall_draw_card_back(i*40+65,player_y);

			if (!NO_SOUND)
			{
				utspkr((i+1)*100);
				delay(50);
			}
		}

		utspkr(0);

		_settextcolor(12);
		_settextposition(7,2);
		_outtext("Dealer");

		_settextposition(12,2);
		_outtext("Player");

		hall_draw_card_front(65, player_y,cards[0].value,cards[0].suit);
		hall_draw_card_front(105,player_y,cards[1].value,cards[1].suit);

		hall_draw_card_front(65,dealer_y,cards[5].value,cards[5].suit);

		player_total =hall_card_add(cards[0].value);

		card_number=1;

		while (!player_fin)
		{
			if (!NO_SOUND)
			{
				utspkr((card_number+1)*100);
				delay(50);
				utspkr(0);
			}

			hall_draw_card_front(card_number*40+65,
								 player_y,
								 cards[card_number].value,
								 cards[card_number].suit);

			player_total+=hall_card_add(cards[card_number].value);

			_settextposition(12,34);
			_settextcolor(12);
			sprintf(temp,"%2d",player_total);
			_outtext(temp);

			if (player_total==21)
			{
				player_fin=TRUE;
				player_won=TRUE;
				player_lost=FALSE;
			}
			else
			if (player_total>21)
			{
				player_fin=TRUE;
				player_lost=TRUE;
				player_won=FALSE;
			}
			else
			{
				switch(hall_another_card())
				{
					case BJ_STICK   : player_fin=TRUE;
									  player_lost=FALSE;
									  break;

					default         : break;
				}

				card_number++;

				if (card_number>=NUM_CARDS)
				{
					player_fin=TRUE;
				}
			}
		}
	}

	/* Dealer Section */

	if (bet!=0L)
	{
		card_number=0;
		dealer_total=0;
		dealer_fin=FALSE;

		if (!player_lost)
		{
			while (!dealer_fin)
			{
				if (!NO_SOUND)
				{
					utspkr((card_number+1)*100);
					delay(50);
					utspkr(0);
				}

				hall_draw_card_front(card_number*40+65,
									 dealer_y,
									 cards[card_number+5].value,
									 cards[card_number+5].suit);

				dealer_total+=hall_card_add(cards[card_number+5].value);

				_settextposition(7,34);
				_settextcolor(12);
				sprintf(temp,"%2d",dealer_total);
				_outtext(temp);

				if (dealer_total>21)
				{
					dealer_fin=TRUE;
					dealer_lost=TRUE;
					dealer_won=FALSE;
					player_lost=FALSE;
					player_won=TRUE;
				}
				else
				if (dealer_total==21 || dealer_total>=player_total)
				{
					dealer_fin=TRUE;
					dealer_won=TRUE;
					dealer_lost=FALSE;
					player_lost=TRUE;
					player_won=FALSE;
				}
				else
				{
					card_number++;

					if (card_number>=NUM_CARDS)
					{
						dealer_fin=TRUE;

						if (dealer_total>=player_total && dealer_total<=21)
						{
							dealer_won=TRUE;
							dealer_lost=FALSE;
							player_lost=TRUE;
							player_won=FALSE;
						}
					}
				}

				delay(500);
			}

			if (player_won && dealer_won)
			{
				sprintf(temp,"Both ye dealer and %s have won, %s gets %s money back!",
							  adv.name,
							  adv.name,
							  adv.his_her);

				GX(temp,GOOD);

				adv.cash+=bet;
			}
			else
			if (player_lost && dealer_lost)
			{
				sprintf(temp,"Both ye dealer and %s have lost!",adv.name);
				GX(temp,BAD);
			}
			else
			if (dealer_won)
			{
				sprintf(temp,"%s scored %d, ye dealer scored %d. Dealer wins!",
							 adv.name,player_total, dealer_total);

				GX(temp,SOLEMN);
			}
			else
			if (player_won)
			{
				sprintf(temp,"%s hath won %lu GC!",adv.name,bet*3L);
				GX(temp,GOOD);

				adv.cash+=bet*3L;
			}
		}
		else
		{
			sprintf(temp,"%s busted, ye Dealer wins!",adv.name);
			GX(temp,SOLEMN);
		}
	}

	_settextposition(7,2);
	_outtext("  ");
}

int _PASCAL hall_card_add(int value)
{
	int result;

	switch(value)
	{
		case CV_TWO   : result= 2; break;
		case CV_THREE : result= 3; break;
		case CV_FOUR  : result= 4; break;
		case CV_FIVE  : result= 5; break;
		case CV_SIX   : result= 6; break;
		case CV_SEVEN : result= 7; break;
		case CV_EIGHT : result= 8; break;
		case CV_NINE  : result= 9; break;
		case CV_TEN   :
		case CV_JACK  :
		case CV_QUEEN :
		case CV_KING  : result=10; break;
		case CV_ACE   : result=11; break;
	}

	return(result);
}

int _PASCAL hall_another_card()
{
	GWINDOW win;
	char *title="Another Card?";
	static int boundary[]={108,138,143,150,
						   160,138,195,150,
							-1,-1,-1,-1};

	int result;

	win.x1=12;
	win.y1=15;
	win.x2=28;
	win.y2=win.y1+6;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(14);
	_settextposition(win.y1+1,20-strlen_half(title));
	_outtext(title);

	click_box(108,138,B_YES);
	click_box(160,138,B_NO);

	result=mouse_in_range(boundary,"YN","");

	kill_gwindow(&win);

	return(result?BJ_STICK:BJ_ANOTHER);
}
