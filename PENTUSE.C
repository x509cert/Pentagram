#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

#ifndef DEV
#pragma optimize("za",on)
#endif

int _PASCAL actually_use_item(PLAYER *adv)
{
	GWINDOW win;
	int i,j;
	int num_items;
	char temp[80];
	char *item_desc;
	int fin;
	static USE_SWAP items[MAX_CARRY];
	int select;
	static int boundary[]={32,  56,226, 62,
						   32,  64,226, 70,
						   32,  72,226, 78,
						   32,  80,226, 86,
						   32,  88,226, 94,
						   32,  96,226,102,
						   32, 104,226,110,
						   32, 112,226,118,
						   32, 120,226,126,
						   32, 128,226,134,
						   32, 136,226,142,
						   32, 144,226,150,
						   109,162,144,174,
							-1,-1,-1,-1};
	win.x1=4;
	win.y1=6;
	win.x2=30;
	win.y2=win.y1+6+MAX_CARRY;
	win.back=0;
	win.border=3;

	for (i=0,num_items=ERR; i<MAX_CARRY; i++)
	{
		j=adv->items_carried[i].item;

		if (j==HOODED_LANTERN   ||
			j==SEXTANT			||
			j==RING_OF_FIRE     ||
			j==RING_OF_ICICLES  ||
			j==THUNDER_WAND     ||
			j==ICE_WAND         ||
			j==FIRE_WAND        ||
			j==HEALING_STAVE    ||
			j==SUSTENANCE_WAND  ||
			j==DEVOURING_ROD    ||
			j==CURIOUS_BOX      ||
			j==GRIMOIRE         ||
			j==LUTE)
		{
			num_items++;

			items[num_items].bit=adv->items_carried[i];

			switch(adv->items_carried[i].item)
			{
				case HOODED_LANTERN   : item_desc=STR_HOODED_LANTERN;  break;
				case SEXTANT          : item_desc=STR_SEXTANT;         break;
				case RING_OF_FIRE     : item_desc=STR_RING_OF_FIRE;    break;
				case RING_OF_ICICLES  : item_desc=STR_RING_OF_ICICLES; break;
				case THUNDER_WAND     : item_desc=STR_THUNDER_WAND;    break;
				case ICE_WAND         : item_desc=STR_ICE_WAND;        break;
				case FIRE_WAND        : item_desc=STR_FIRE_WAND;       break;
				case HEALING_STAVE    : item_desc=STR_HEALING_STAVE;   break;
				case SUSTENANCE_WAND  : item_desc=STR_SUSTENANCE_WAND; break;
				case DEVOURING_ROD    : item_desc=STR_DEVOURING_ROD;   break;
				case CURIOUS_BOX      : item_desc=STR_CURIOUS_BOX;     break;
				case LUTE             : item_desc=STR_LUTE;            break;
				case GRIMOIRE         : item_desc=STR_GRIMOIRE;        break;
				default               : break;
			}

			strcpy(items[num_items].desc,item_desc);
		}
	}

	if (num_items==ERR)
	{
		sprintf(temp,"%s hath naught to use!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	make_gwindow(&win);

	click_box(109,162,B_QUIT);

	_settextposition(win.y1+1,win.x1+4);
	_settextcolor(14);
	_outtext("Select Item to Use");

	for (i=0; i<=num_items; i++)
	{
		_settextcolor(13);
		sprintf(temp,"%cù",i+'A');
		_settextposition(win.y1+2+i,win.x1+1);
		_outtext(temp);

		_settextcolor(5);
		_settextposition(win.y1+2+i,win.x1+3);
		_outtext(items[i].desc);
	}

	fin=FALSE;

	while (!fin)
	{
		select=mouse_in_range(boundary,"ABCDEFGHIJKLQ","");

		if ((select>num_items) && (select!=12))
			continue;

		fin=TRUE;
	}

	kill_gwindow(&win);

	fin=FALSE;

	if (select!=12)
	{
		switch(items[select].bit.item)
		{
			case HOODED_LANTERN 		:	fin=use_hooded_lantern(adv);  break;
			case SEXTANT				:	fin=use_sextant(adv);		  break;
			case RING_OF_FIRE			:	fin=use_ring_of_fire(adv);	  break;
			case RING_OF_ICICLES		:	fin=use_ring_of_icicles(adv); break;
			case THUNDER_WAND			:	fin=use_thunder_wand(adv);	  break;
			case ICE_WAND				:	fin=use_ice_wand(adv);		  break;
			case FIRE_WAND				:	fin=use_fire_wand(adv); 	  break;
			case HEALING_STAVE			:	fin=use_healing_stave(adv);   break;
			case SUSTENANCE_WAND		:	fin=use_sustenance_wand(adv); break;
			case DEVOURING_ROD          :   fin=use_rod_of_devouring(adv);break;
			case CURIOUS_BOX            :   fin=use_curious_box(adv);     break;
			case LUTE                   :   fin=use_lute(adv);            break;
			case GRIMOIRE               :   fin=use_grimoire(adv);        break;
			default                     :   break;
		}
	}

	return(fin);
}

#ifndef DEV
#pragma optimize("",on)
#endif

int _PASCAL _NEAR use_hooded_lantern(PLAYER *adv)
{
	char temp[120];

	if (bard_is_singing(adv,"light a lantern"))
		return(FALSE);

	if (IN_COMBAT)
	{
		strcpy(temp,"Thou art supposedly fighting!");
		cmbt_bad_msg(temp,TRUE);

		return(FALSE);
	}

	if (adv->in_effect.lantern_lit)
	{
		sprintf(temp,"%s art carrying an illuminated lantern!",adv->name);

		SCROLL(1,0,temp);

		bad_sound();

		return(FALSE);
	}

	if (player_is_carrying(adv,TINDER_BOX)     &&
		player_is_carrying(adv,HOODED_LANTERN) &&
		adv->oil!=0)
	{
		adv->oil--;
		adv->in_effect.lantern_lit+=(70+((rand()-rand())%15));

		sprintf(temp,"As %s ignites %s hooded lantern, it flares up, invoking a soft, warm yellow light.",
					  adv->name,
					  adv->his_her);

		SCROLL(1,14,temp);

		use_item_sound();

		return(TRUE);
	}
	else
	{
		sprintf(temp,"To light a hooded lantern, %s needs a hooded lantern, oil and a tinder-box!",adv->name);

		SCROLL(1,0,temp);

		bad_sound();
	}

	return(FALSE);
}

int _PASCAL _NEAR use_sextant(PLAYER *adv)
{
	char temp[120];
	char ew[20];
	char ns[20];

	if (effective_intelligence(adv)<13)
	{
		sprintf(temp,"The mechanics of a sextant are beyond %s!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	if (bard_is_singing(adv,"use a sextant"))
		return(FALSE);

	if (IN_COMBAT)
	{
		cmbt_bad_msg("Why wouldst thou use a sextant in melee? Dolt!",TRUE);
		return(FALSE);
	}

	if (pent_data.x<=89)
		sprintf(ew,"%d~W",89-pent_data.x);
	else
		sprintf(ew,"%d~E",pent_data.x-89);

	if (pent_data.y<=86)
		sprintf(ns,"%d~N",86-pent_data.y);
	else
		sprintf(ns,"%d~S",pent_data.y-86);

	sprintf(temp,"using %s sextant, %s determines thy party to be at "
				 "%s and %s %s.",
				 adv->his_her,
				 adv->name,
				 ns,ew,
				 get_province(pent_data.x,pent_data.y));

	SCROLL(1,14,temp);

	use_item_sound();

	return(TRUE);
}

int _PASCAL _NEAR use_grimoire(PLAYER *adv)
{
	GWINDOW win;
	int page=0;
	char temp[80];
	int fin=FALSE;
	int change=FALSE;
	int x;
	int max_pages=6;
	int clear;
	static int boundary[]={65, 142,100,154,
						   125,142,160,154,
						   185,142,220,154,
						   -1,-1,-1,-1};

	if (bard_is_singing(adv,"read ye grimoire"))
		return(FALSE);

	if (IN_COMBAT)
	{
		cmbt_bad_msg("'tis no time to read, fool!",TRUE);
		return(FALSE);
	}

	sprintf(temp,"With great care %s opens ye grimoire!",adv->name);
	SCROLL(1,14,temp);
	general_low_sound();
	half_pause();

	win.x1=5;
	win.y1=2;
	win.x2=33;
	win.y2=21;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	click_box(65, 142,B_PREV);
	click_box(125,142,B_NEXT);
	click_box(185,142,B_QUIT);

	generic_pic_draw(95,19,"PAGE0");

	while (!fin)
	{
		change=TRUE;
		clear=FALSE;

		switch(mouse_in_range(boundary,"PNQ",""))
		{
			case 0 : if (--page<0)
					 {
						page=0;
						change=FALSE;
					 }

					 if (page==0)
						clear=TRUE;

					 break;

			case 1 : if (++page>max_pages)
					 {
						page=max_pages;
						change=FALSE;
					 }

					 if (page==1)
						clear=TRUE;

					 break;

			case 2 : fin=TRUE;
					 change=FALSE;
					 break;
		}

		if (change)
		{
			sprintf(temp,"page%d",page);

			x=page?50:95;

			if (clear)
			{
				_setcolor(0);
				_rectangle(_GFILLINTERIOR,
						   win.x1*8+4,win.y1*8+3,win.x2*8-16,win.y2*8-27);
			}

			generic_pic_draw(x,19,temp);
		}
	}

	kill_gwindow(&win);

	sprintf(temp,"%s closes ye grimoire and puts it away.",adv->name);
	SCROLL(1,14,temp);

	general_low_sound();

	return(TRUE);
}
