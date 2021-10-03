#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <butil.h>
#include "mmalloc.h"
#include "sprite.h"

#define mapimagepixY 13
#define mapsize 	 WINDOW_MAP_SIZE

static char _FAR     *adv_map_buffer;

void _PASCAL place_map()
{
	unsigned long size;

	size=_imagesize(0,0,153,mapimagepixY*mapsize);

	adv_map_buffer=(char _FAR *)Mmalloc((size_t)size);

	if (adv_map_buffer==(char _FAR *)NULL)
		panic_RAM("MAP");

	_getimage(0,
			  0,
			  153,
			  mapimagepixY*mapsize,
			  (char _FAR *)adv_map_buffer);

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,0,0,153,mapimagepixY*mapsize);

	_setcolor(8);
	_rectangle(_GFILLINTERIOR,6,6,153,mapimagepixY*mapsize);
}

void _PASCAL kill_map()
{
	_putimage(0,0,(char _FAR *)adv_map_buffer,_GPSET);

	Mfree((void *)adv_map_buffer);
}

void _PASCAL draw_first_map()
{
	int i,j;

	for (i=-4; i<5; i++)
		for (j=-4; j<5; j++)
			draw_map_square(i,j,map_bit(pent_data.x+j,pent_data.y+i));

	position_party_on_map();
}

void _PASCAL draw_map(int direction)
{
	int old_feature=pent_data.current_feature;
	int x,y;
	int bump=FALSE;

	pent_data.current_feature=map_bit(pent_data.x,pent_data.y);

	if (pent_data.current_feature==HIGH_MOUNTAINS &&
		check_party_globals_in_effect(IN_EFFECT_SPELL_OF_PASSAGE)==ERR)
	{
		if (!NO_SOUND)
			utspkr(100);

		shake_screen();
		utspkr(0);

		SCROLL(1,0,"Impassable!");

		switch(direction)
		{
			case DIR_NORTH  :   pent_data.y++; break;
			case DIR_SOUTH  :   pent_data.y--; break;
			case DIR_EAST   :   pent_data.x--; break;
			case DIR_WEST	:	pent_data.x++; break;
			default 		:	break;
		}

		pent_data.current_feature=map_bit(pent_data.x,pent_data.y);

		bump=TRUE;
	}

	if (is_night_time())
	{
		draw_night_map();
		return;
	}

	if (night_flagged)
	{
		draw_first_map();
		night_flagged=FALSE;
		return;
	}

	switch(direction)
	{
		case DIR_NORTH  :   y=pent_data.y+1; x=pent_data.x;   break;
		case DIR_SOUTH  :   y=pent_data.y-1; x=pent_data.x;   break;
		case DIR_EAST   :   y=pent_data.y;   x=pent_data.x-1; break;
		case DIR_WEST   :   y=pent_data.y;   x=pent_data.x+1; break;
		default         :   y=pent_data.y;   x=pent_data.x;   break;
	}

	if (!bump && direction!=JUST_TELEPORTED)
	{
		switch(old_feature)
		{
			case GRASS          :   PUTBLOCK(72,56,map_icon_grass);
									break;

			case HILLS          :   PUTBLOCK(72,56,map_icon_hills);
									break;

			case MOUNTAINS      :   PUTBLOCK(72,56,map_icon_mts);
									break;

			case HIGH_MOUNTAINS :   PUTBLOCK(72,56,map_icon_highmts);
									break;

			case WATER          :   PUTBLOCK(72,56, rand()%4?map_icon_water
															:map_icon_water2);
									break;

			case FOREST         :   PUTBLOCK(72,56,map_icon_forest);
									break;

			case MARSH          :   PUTBLOCK(72,56,map_icon_marsh);
									break;

			case SEA            :   PUTBLOCK(72,56,rand()%4?map_icon_sea
														   :map_icon_sea2);
									break;

			case CITY           :   PUTBLOCK(72,56,map_icon_town);
									break;

			case PATH           :   switch(determine_road_shape(x,y))
									{
										case 1 : PUTBLOCK(72,56,map_icon_road01); break;
										case 2 : PUTBLOCK(72,56,map_icon_road02); break;
										case 3 : PUTBLOCK(72,56,map_icon_road03); break;
										case 4 : PUTBLOCK(72,56,map_icon_road04); break;
										case 5 : PUTBLOCK(72,56,map_icon_road05); break;
										case 6 : PUTBLOCK(72,56,map_icon_road06); break;
										case 7 : PUTBLOCK(72,56,map_icon_road07); break;
										case 8 : PUTBLOCK(72,56,map_icon_road08); break;
										case 9 : PUTBLOCK(72,56,map_icon_road09); break;
										case 10: PUTBLOCK(72,56,map_icon_road10); break;
										case 11: PUTBLOCK(72,56,map_icon_road11); break;
									}

									break;

			case TOWN           :   PUTBLOCK(72,56,map_icon_village);
									break;

			case RUIN           :   PUTBLOCK(72,56,map_icon_ruin);
									break;

			case DUNGEON        :   PUTBLOCK(72,56,map_icon_dungeon);
									break;

			case CELTIC_CROSS   :   PUTBLOCK(72,56,map_icon_cross);
									break;

			case SIGNPOST       :   PUTBLOCK(72,56,map_icon_signpost);
									break;

			case BRIDGE_UD      :   PUTBLOCK(72,56,map_icon_br_ud);
									break;

			case BRIDGE_LR      :   PUTBLOCK(72,56,map_icon_br_lr);
									break;

			default             :   PUTBLOCK(72,56,map_icon_grass);
									break;
		}

		switch(direction)
		{
			case DIR_NORTH  :   scroll_north();
								position_party_on_map();
								fill_northern_map();
								break;

			case DIR_SOUTH  :   scroll_south();
								position_party_on_map();
								fill_southern_map();
								break;

			case DIR_EAST   :   scroll_east();
								position_party_on_map();
								fill_eastern_map();
								break;

			case DIR_WEST   :   scroll_west();
								position_party_on_map();
								fill_western_map();
								break;

			default         :   position_party_on_map();
								break;
		}
	}
	else
	{
		draw_map_square(0,0,pent_data.current_feature);
		position_party_on_map();
	}

	if (pent_data.current_feature==BRIDGE)
	{
		if (map_bit(pent_data.x-1,pent_data.y)==WATER &&
			map_bit(pent_data.x+1,pent_data.y)==WATER)
			pent_data.current_feature=BRIDGE_UD;
		else
			pent_data.current_feature=BRIDGE_LR;
	}

	if (!the_party.all_dead)
		if (pent_data.current_feature==SEA || pent_data.current_feature==WATER)
			all_party_damaged_swim();
}

void _PASCAL draw_night_map()
{
	int i,j;

	if (!night_flagged)
	{
		_setcolor(0);
		_rectangle(_GFILLINTERIOR,8,8,151,43);
		_rectangle(_GFILLINTERIOR,8,68,151,115);
		_rectangle(_GFILLINTERIOR,8,44,55,78);
		_rectangle(_GFILLINTERIOR,104,44,151,78);
	}

	night_flagged=TRUE;

	for (i=-1; i<2; i++)
		for (j=-1; j<2; j++)
			draw_map_square(i,j,map_bit(pent_data.x+j,pent_data.y+i));

	if (pent_data.current_feature==BRIDGE)
	{
		if (map_bit(pent_data.x-1,pent_data.y)==WATER &&
			map_bit(pent_data.x+1,pent_data.y)==WATER)
			pent_data.current_feature=BRIDGE_UD;
		else
			pent_data.current_feature=BRIDGE_LR;
	}

	position_party_on_map();

	if (!the_party.all_dead)
		if (pent_data.current_feature==SEA || pent_data.current_feature==WATER)
			all_party_damaged_swim();
}

#ifndef DEV
#pragma optimize("za",on)
#pragma optimize("b2",on)
#endif

void _PASCAL _NEAR fill_northern_map()
{
	int j;
	int i=-4;

	for (j=-4; j<5; j++)
		draw_map_square(i,j,map_bit(pent_data.x+j,pent_data.y+i));
}

void _PASCAL _NEAR fill_southern_map()
{
	int j;
	int i=4;

	for (j=-4; j<5; j++)
		draw_map_square(i,j,map_bit(pent_data.x+j,pent_data.y+i));
}

void _PASCAL _NEAR fill_eastern_map()
{
	int j=4;
	int i;

	for (i=-4; i<5; i++)
		draw_map_square(i,j,map_bit(pent_data.x+j,pent_data.y+i));
}

void _PASCAL _NEAR fill_western_map()
{
	int j=-4;
	int i;

	for (i=-4; i<5; i++)
		draw_map_square(i,j,map_bit(pent_data.x+j,pent_data.y+i));
}

void _PASCAL _NEAR draw_map_square(int i,int j,int im)
{
	switch(im)
	{
		case GRASS          :   PUTBLOCK(j*16+72,i*12+56,map_icon_grass);
								break;

		case HILLS          :   PUTBLOCK(j*16+72,i*12+56,map_icon_hills);
								break;

		case MOUNTAINS      :   PUTBLOCK(j*16+72,i*12+56,map_icon_mts);
								break;

		case HIGH_MOUNTAINS :   PUTBLOCK(j*16+72,i*12+56,map_icon_highmts);
								break;

		case WATER          :   PUTBLOCK(j*16+72,i*12+56,
										  rand()%4?map_icon_water
												  :map_icon_water2);
								break;

		case FOREST         :   PUTBLOCK(j*16+72,i*12+56,map_icon_forest);
								break;

		case MARSH          :   PUTBLOCK(j*16+72,i*12+56,map_icon_marsh);
								break;

		case SEA            :   PUTBLOCK(j*16+72,i*12+56,
										  rand()%4?map_icon_sea
												  :map_icon_sea2);
								break;

		case CITY           :   PUTBLOCK(j*16+72,i*12+56,map_icon_town);
								break;

		case PATH           :   switch(determine_road_shape(j+pent_data.x,i+pent_data.y))
								{
									case 1 : PUTBLOCK(j*16+72,i*12+56,map_icon_road01); break;
									case 2 : PUTBLOCK(j*16+72,i*12+56,map_icon_road02); break;
									case 3 : PUTBLOCK(j*16+72,i*12+56,map_icon_road03); break;
									case 4 : PUTBLOCK(j*16+72,i*12+56,map_icon_road04); break;
									case 5 : PUTBLOCK(j*16+72,i*12+56,map_icon_road05); break;
									case 6 : PUTBLOCK(j*16+72,i*12+56,map_icon_road06); break;
									case 7 : PUTBLOCK(j*16+72,i*12+56,map_icon_road07); break;
									case 8 : PUTBLOCK(j*16+72,i*12+56,map_icon_road08); break;
									case 9 : PUTBLOCK(j*16+72,i*12+56,map_icon_road09); break;
									case 10: PUTBLOCK(j*16+72,i*12+56,map_icon_road10); break;
									case 11: PUTBLOCK(j*16+72,i*12+56,map_icon_road11); break;
								}

								break;

		case TOWN           :   PUTBLOCK(j*16+72,i*12+56,map_icon_village);
								break;

		case RUIN           :   PUTBLOCK(j*16+72,i*12+56,map_icon_ruin);
								break;

		case DUNGEON        :   PUTBLOCK(j*16+72,i*12+56,map_icon_dungeon);
								break;

		case CELTIC_CROSS   :   PUTBLOCK(j*16+72,i*12+56,map_icon_cross);
								break;

		case SIGNPOST       :   PUTBLOCK(j*16+72,i*12+56,map_icon_signpost);
								break;

		case BRIDGE         :   if (map_bit(pent_data.x+j-1,pent_data.y+i)==WATER &&
									map_bit(pent_data.x+j+1,pent_data.y+i)==WATER)
									PUTBLOCK(j*16+72,i*12+56,map_icon_br_ud);
								else
									PUTBLOCK(j*16+72,i*12+56,map_icon_br_lr);

								break;

		default             :   PUTBLOCK(j*16+72,i*12+56,map_icon_grass);
								break;
	}
}

int _PASCAL _NEAR determine_road_shape(int i,int j)
{
	int u,d,r,l;

	l=map_bit(i-1,j)==PATH;
	r=map_bit(i+1,j)==PATH;
	u=map_bit(i,j-1)==PATH;
	d=map_bit(i,j+1)==PATH;

	if (u&d&l&r)
		return(1);

	if (u&l&r)
		return(2);

	if (l&r&d)
		return(3);

	if (u&d&r)
		return(4);

	if (u&d&l)
		return(5);

	if (u&r)
		return(6);

	if (d&l)
		return(7);

	if (d&r)
		return(8);

	if (u&l)
		return(9);

	if (l|r)
		return(10);

	if (u|d)
		return(11);

	return(11);
}

void _PASCAL _NEAR position_party_on_map()
{
	if (pent_data.current_feature==FOREST)
	{
		_putimage(72,
				  56,
				  (char _FAR *)map_icon_party2,
				  _GPSET);
	}
	else
	{
		_putimage(72,
				  56,
				  (char _FAR *)map_icon_party_mask,
				  _GAND);

		_putimage(72,
				  56,
				  (char _FAR *)map_icon_party,
				  _GOR);
	}
}

#ifndef DEV
#pragma optimize("",on)
#endif
