#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	Player Missile Options #3
 *	Sling/Crossbow/Bow/Dart/Oil/Holy Water
 *
 */

int _PASCAL cmbt_missile_sling(PLAYER *adv)
{
	combat_write(11,"Using a sling",FALSE);

	return(cmbt_generic_missile(adv,CMBT_SLING,cmbt_missile_draw_sling_shot));
}

int _PASCAL cmbt_missile_crossbow(PLAYER *adv)
{
	combat_write(11,"Using a crossbow",FALSE);

	if (!adv->quarrels)
	{
		cmbt_hath_no_item("quarrels");
		return(FALSE);
	}

	return(cmbt_generic_missile(adv,CMBT_CROSSBOW,NULL));
}

int _PASCAL cmbt_missile_bow(PLAYER *adv)
{
	combat_write(11,"Using a longbow",FALSE);

	if (!adv->arrows)
	{
		cmbt_hath_no_item("arrows");
		return(FALSE);
	}

	return(cmbt_generic_missile(adv,CMBT_BOW,NULL));
}

int _PASCAL cmbt_missile_dart_oil_water(PLAYER *adv)
{
	char *t2="DFWQ";
	char temp[40];
	static char *t[]={"Throw a Dart",
					  "Throw Flaming Oil",
					  "Throw Holy Water",
					  "Quit"};

	static int boundary[]={104,40,256,46,
						   104,48,256,54,
						   104,56,256,62,
						   104,64,256,70,
						   -1,-1,-1,-1};
	GWINDOW win;
	int res,sel;

	if (!adv->darts &&
		!adv->oil	&&
		!player_is_carrying_potion(adv,POT_HOLYWATER))
	{
		sprintf(temp,"%s hath naught to throw!",adv->name);
		cmbt_bad_msg(temp,TRUE);

		return(FALSE);
	}

	win.x1=13;
	win.y1=5;
	win.x2=34;
	win.y2=11;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+3,
					   win.y1+1,
					   7,
					   11);

	if (adv->darts)
		tick(win.x1*8+2,win.y1*8,ON);

	if (adv->oil)
		tick(win.x1*8+2,win.y1*8+8,ON);

	if (player_is_carrying_potion(adv,POT_HOLYWATER))
		tick(win.x1*8+2,win.y1*8+16,ON);

	sel=mouse_in_range(boundary,t2,"");

	kill_gwindow(&win);

	switch(sel)
	{
		case 0 : res=cmbt_missile_dart(adv);  break;
		case 1 : res=cmbt_missile_oil(adv);   break;
		case 2 : res=cmbt_missile_water(adv); break;
		default: res=FALSE;                   break;
	}

	return(res);
}

int _PASCAL cmbt_missile_dart(PLAYER *adv)
{
	if (!adv->darts)
	{
		cmbt_hath_no_item("darts");
		return(FALSE);
	}

	combat_write(11,"Throwing a dart",FALSE);

	return(cmbt_generic_missile(adv,CMBT_DART,NULL));
}

int _PASCAL cmbt_missile_oil(PLAYER *adv)
{
	if (!adv->oil)
	{
		cmbt_hath_no_item("oil flasks");
		return(FALSE);
	}

	if (!player_is_carrying(adv,TINDER_BOX))
	{
		cmbt_hath_no_item("tinder-box");
		return(FALSE);
	}

	combat_write(11,"Throwing flaming oil",FALSE);

	return(cmbt_generic_oil_water(adv,CMBT_OIL));
}

int _PASCAL cmbt_missile_water(PLAYER *adv)
{
	if (!player_is_carrying_potion(adv,POT_HOLYWATER))
	{
		cmbt_hath_no_item("holy water");
		return(FALSE);
	}

	combat_write(11,"Throwing holy water",FALSE);

	return(cmbt_generic_oil_water(adv,CMBT_HOLYWATER));
}

void _PASCAL _NEAR cmbt_hath_no_item(char *item)
{
	char temp[50];

	sprintf(temp,"Thou hath no %s",item);
	cmbt_bad_msg(temp,TRUE);
}
