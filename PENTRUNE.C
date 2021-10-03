#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL bane_rune_acquire()	 /* When a bane rune is acquired HP-=10% */
{
	int type;
	int num;

	if (the_party.all_dead)
		return;

	num=bane_rune_select_adv();

	if (num!=ERR)
	{
		bane_rune_announce();

		if (bane_rune_yes_no())
		{
			type=bane_rune_type();

			adv.bane_rune=type;

			TPP[num]=adv;
		}

		GX("Ye shadowy figure disappears beyond ye blackness...",GOOD);
	}
}

int _PASCAL bane_rune_type()
{
	GWINDOW win;
	int offset;
	int i;
	int x,y;
	int type;
	char *title="Which Bane Rune doth ye select?";
	static int types[]={
							TYP_UNDEAD,
							TYP_FIRE,
							TYP_WATER,
							TYP_EARTH,
							TYP_AERIAL,
							TYP_DEMONIC,
							TYP_NOCTURNAL,
							TYP_ICE
						};

	static int boundary[]={11, 68,34, 90,
						   48, 68,64, 90,
						   85, 68,103,90,
						   120,68,138,90,
						   151,68,174,90,
						   186,68,212,90,
						   217,68,251,90,
						   260,68,275,90,
							-1,-1,-1,-1};

	win.x1=1;
	win.y1=7;
	win.x2=38;
	win.y2=13;
	win.back=0;
	win.border=5;

	make_gwindow(&win);

	x=win.x1*8+8;
	y=win.y1*8+12;

	offset=(win.x2-win.x1)*8;
	offset-=16;
	offset/=SIZE(types);

	_settextcolor(12);
	_settextposition(win.y1+1,1+(((win.x2-win.x1)/2)-strlen_half(title)));
	_outtext(title);

	for (i=0; i<SIZE(types); i++)
	{
		bane_rune_draw(types[i],x,y,TRUE);

		x+=offset;
	}

	switch(mouse_in_range(boundary,"UFWEADNI",""))
	{
		case 0 : type=TYP_UNDEAD;   break;
		case 1 : type=TYP_FIRE;     break;
		case 2 : type=TYP_WATER;    break;
		case 3 : type=TYP_EARTH;    break;
		case 4 : type=TYP_AERIAL;   break;
		case 5 : type=TYP_DEMONIC;  break;
		case 6 : type=TYP_NOCTURNAL;break;
		case 7 : type=TYP_ICE;      break;
	}

	kill_gwindow(&win);

	return(type);
}

int _PASCAL bane_rune_yes_no()
{
	GWINDOW win;
	int result;
	char temp[40];
	int hp_lose;
	char *t1="To acquire a Bane Rune, %s";
	char *t2="must make a considerable sacrifice.";
	char *t3="%s must forgo %d HP permanently!";
	char *t4="Doth %s proceed?";

	static int boundary[]={108,75,143,87,
						   168,75,203,87,
							-1,-1,-1,-1};

	hp_lose=adv.hp/10;
	hp_lose++;

	win.x1=1;
	win.y1=4;
	win.x2=39;
	win.y2=13;
	win.back=0;
	win.border=6;

	make_gwindow(&win);

	_settextcolor(14);

	sprintf(temp,t1,adv.name);
	_settextposition(win.y1+1,20-strlen_half(temp));
	_outtext(temp);

	_settextposition(win.y1+2,20-strlen_half(t2));
	_outtext(t2);

	sprintf(temp,t3,(adv.sex==SX_MALE?"He":"She"),hp_lose);
	_settextposition(win.y1+3,20-strlen_half(temp));
	_outtext(temp);

	sprintf(temp,t4,adv.name);
	_settextposition(win.y1+5,20-strlen_half(temp));
	_outtext(temp);


	click_box(108,75,B_YES);
	click_box(168,75,B_NO);

	switch(mouse_in_range(boundary,"YN","YQ"))
	{
		case 0 :    result=TRUE;  break;
		default:    result=FALSE; break;
	}

	kill_gwindow(&win);

	return(result);
}

int _PASCAL bane_rune_select_adv()
{
	int i;
	int num;
	int result=ERR;

	for (i=0; i<20; i++)
	{
		num=rand()%(P_NUM+1);

		adv=TPP[num];

		if (adv.bane_rune==TYP_NO_RUNES && player_is_alive(&adv))
		{
			result=num;
			break;
		}
	}

	return(result);
}

void _PASCAL bane_rune_announce()
{
	static char *mess1[]={"A shadowy figure, clad in a ragged",
						  "green cloak, approaches thy",
						  "party. In a deep, but timeworn",
						  "voice he murmurs, \"I may aid thy",
						  "cause by bestowing upon one member",
						  "ye most coveted device of ancient",
						  "times - A Bane Rune.\""};

	char temp[80];
	static char *mess2[]={"Ye figure raises it's arm and",
						  "points a long, sinewy finger at -"};
	int i;
	GWINDOW win;
	static int boundary1[]={135,106,170,118,
							-1,-1,-1,-1};

	static int boundary2[]={135,81,170,93,
							-1,-1,-1,-1};

	win.x1=2;
	win.y1=5;
	win.x2=38;
	win.y2=win.y1+3+SIZE(mess1)+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(5);

	for (i=0; i<SIZE(mess1); i++)
	{
		_settextposition(win.y1+1+i,20-strlen_half(mess1[i]));
		_outtext(mess1[i]);
	}

	click_box(135,106,B_OK);

	general_low_sound();

	pause(1);

	mouse_in_range(boundary1,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	win.y2=win.y1+5+SIZE(mess2)+2;

	make_gwindow(&win);

	_settextcolor(5);

	for (i=0; i<SIZE(mess2); i++)
	{
		_settextposition(win.y1+1+i,20-strlen_half(mess2[i]));
		_outtext(mess2[i]);
	}

	sprintf(temp,"%s ye %s",adv.name,adv.class);
	_settextcolor(13);
	_settextposition(win.y1+2+i,20-strlen_half(temp));
	_outtext(temp);

	click_box(135,81,B_OK);

	mouse_in_range(boundary2,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}
