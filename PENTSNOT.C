#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL dungeon_encounter_snotling()
{
	int i;
	int chosen=ERR;

	for (i=P_NUM; i>0; i--)
	{
		if (player_is_alive(&TPP[i]))
		{
			chosen=i;
			break;
		}
	}

	if (chosen==ERR)		 /* No adventurer found */
		return;

	dungeon_snotling_sneak_up(&TPP[i]);
}

void _PASCAL _NEAR dungeon_snotling_sneak_up(PLAYER *adv)
{
	unsigned long amount_nicked;
	static char temp[150];
	static char *what[]={"Unseen by",
						 "Unknown to"};

	amount_nicked=dungeon_snotling_get_money(adv);

	sprintf(temp,"%s %s, a small, dark creature, armed with a keen blade, sneaks up on %s.",
				 what[rand()%2],
				 adv->name,
				 adv->him_her);

	SCROLL(1,0,temp);

	snotling_sound();

	pause(2);

	if (amount_nicked==0L ||
		percent()<=effective_chance_spot_snotling(adv))
	{
		sprintf(temp,"Luckily, %s notices ye creature. As it runs into ye inky blackness, it swears to itself!",
					  adv->name);

		SCROLL(1,14,temp);
		good_sound();

		return;
	}

	pause(2);

	adv->cash-=amount_nicked;

	sprintf(temp,"With incredible ease, ye creature lifts %luGC from %s%s purse!",
				amount_nicked,
				adv->name,
				end_s(adv->name));

	SCROLL(1,0,temp);

	snotling_sound();

	pause(2);

	dungeon_snotling_has_money(adv);
}

void _PASCAL _NEAR dungeon_snotling_has_money(PLAYER *adv)
{
	GWINDOW win;
	char temp[50];
	static char *line2="victim of Dungeon Snotlings!";
	static int boundary[]={137,78,172,90,
						   -1,-1,-1,-1};

	SCROLL(1,0,"Ye creature runs off into ye dungeon darkness"
			   " - giggling to itself!");

	solemn_sound();

	pause(2);

	win.x1=4;
	win.y1=5;
	win.x2=37;
	win.y2=13;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	sprintf(temp,"%s art another hapless",adv->name);

	_settextcolor(6);
	_settextposition(win.y1+3,20-strlen_half(temp));
	_outtext(temp);

	_settextposition(win.y1+4,20-strlen_half(line2));
	_outtext(line2);

	click_box(137,78,B_OK);

	draw_evil_eyes(148,win.y1*8+2);

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

unsigned long _PASCAL _NEAR dungeon_snotling_get_money(PLAYER *adv)
{
	unsigned long amount_nicked=adv->cash/23L;

	if (amount_nicked<=2L)
		amount_nicked=0L;

	return(amount_nicked);
}

void _PASCAL _NEAR draw_evil_eyes(int x,int y)
{
	int i,j;
	int d=33;

	draw_evil_eyes_part(x,y,0);

	delay(100);

	for (j=0; j<2; j++)
	{
		for (i=0; i<6; i++)
		{
			draw_evil_eyes_part(x,y,i);
			delay(d);
		}

		_setcolor(0);
		_moveto(x,y+5);
		_lineto(x+15,y+5);

		delay(300);

		for (i=5; i>=0; i--)
		{
			draw_evil_eyes_part(x,y,i);
			delay(d);
		}

		delay(180);
	}
}

void _PASCAL _NEAR draw_evil_eyes_part(int x,int y,int top)
{
	int i,j;

	_setcolor(0);
	_moveto(x,y+top-1);
	_lineto(x+15,y+top-1);

	for (i=top; i<6; i++)
		for (j=0; j<15; j++)
			FFPLOT(x+j,y+i,evil_eyes[i][j]);
}
