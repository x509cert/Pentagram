#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

#ifndef DEV
#pragma optimize("za",on)
#pragma optimize("b2",on)
#endif

void _PASCAL dungeon_view_from_party(int l,int x,int y)
{
	int i;

	if (check_party_globals_in_effect(IN_EFFECT_LIGHT)==ERR)
	{
		if (see_through(l,x-1,y))
			dungeon_redraw_feature(l,x-1,y,dungeon.map[l][x-1][y].feature);

		if (see_through(l,x+1,y))
			dungeon_redraw_feature(l,x+1,y,dungeon.map[l][x+1][y].feature);

		if (see_through(l,x,y-1))
			dungeon_redraw_feature(l,x,y-1,dungeon.map[l][x][y-1].feature);

		if (see_through(l,x,y+1))
			dungeon_redraw_feature(l,x,y+1,dungeon.map[l][x][y+1].feature);

		dungeon.map[l][x][y].mapped=1;
	}
	else
	{
		for (i=1; i<=3; i++)                        /* To the left */
			if (see_through(l,x-i,y))
				dungeon_redraw_feature(l,x-i,y,dungeon.map[l][x-i][y].feature);
			else
				break;


		for (i=1; i<=3; i++)                        /* To the right */
			if (see_through(l,x+i,y))
				dungeon_redraw_feature(l,x+i,y,dungeon.map[l][x+i][y].feature);
			else
				break;


		for (i=1; i<=3; i++)                        /* To the top */
			if (see_through(l,x,y-i))
				dungeon_redraw_feature(l,x,y-i,dungeon.map[l][x][y-i].feature);
			else
				break;


		for (i=1; i<=3; i++)                        /* To the bottom */
			if (see_through(l,x,y+i))
				dungeon_redraw_feature(l,x,y+i,dungeon.map[l][x][y+i].feature);
			else
				break;


		if (see_through(l,x+1,y))                   /* X+1, Y Clear */
		{
			if (see_through(l,x+2,y-1))
				dungeon_redraw_feature(l,x+2,y-1,dungeon.map[l][x+2][y-1].feature);

			if (see_through(l,x+2,y+1))
				dungeon_redraw_feature(l,x+2,y+1,dungeon.map[l][x+2][y+1].feature);
		}



		if (see_through(l,x-1,y))                   /* X-1,Y Clear */
		{
			if (see_through(l,x-2,y-1))
				dungeon_redraw_feature(l,x-2,y-1,dungeon.map[l][x-2][y-1].feature);

			if (see_through(l,x-2,y+1))
				dungeon_redraw_feature(l,x-2,y+1,dungeon.map[l][x-2][y+1].feature);
		}


		if (see_through(l,x,y+1))                  /* X,Y+1 Clear */
		{
			if (see_through(l,x+1,y+2))
				dungeon_redraw_feature(l,x+1,y+2,dungeon.map[l][x+1][y+2].feature);

			if (see_through(l,x-1,y+2))
				dungeon_redraw_feature(l,x-1,y+2,dungeon.map[l][x-1][y+2].feature);
		}


		if (see_through(l,x,y-1))                   /* X,Y-1 Clear */
		{
			if (see_through(l,x+1,y-2))
				dungeon_redraw_feature(l,x+1,y-2,dungeon.map[l][x+1][y-2].feature);

			if (see_through(l,x-1,y-2))
				dungeon_redraw_feature(l,x-1,y-2,dungeon.map[l][x-1][y-2].feature);
		}


		if (see_through(l,x-1,y-1))
			dungeon_redraw_feature(l,x-1,y-1,dungeon.map[l][x-1][y-1].feature);


		if (see_through(l,x-1,y+1))
			dungeon_redraw_feature(l,x-1,y+1,dungeon.map[l][x-1][y+1].feature);


		if (see_through(l,x+1,y-1))
			dungeon_redraw_feature(l,x+1,y-1,dungeon.map[l][x+1][y-1].feature);


		if (see_through(l,x+1,y+1))
			dungeon_redraw_feature(l,x+1,y+1,dungeon.map[l][x+1][y+1].feature);
	}
}

int _PASCAL _NEAR see_through(int l,int x,int y)
{
	int see=TRUE;
	int mapped=dungeon.map[l][x][y].mapped;

	if (x<0 || y<0 || x>MAX_DUNGEON_X || y>MAX_DUNGEON_Y)
	{
		see=FALSE;
	}
	else
	{
		switch(dungeon.map[l][x][y].feature)
		{
			case DNG_DOOR          :
			case DNG_HEAVY_DOOR    :
			case DNG_LOCKED_DOOR   :
			case DNG_SECRET_DOOR   :
			case DNG_WALL          : see=FALSE; break;
			default                : see=TRUE;  break;
		}

		if (!see    &&
			!mapped &&
			dungeon.map[l][x][y].feature!=DNG_WALL)         /* If you can't see through it and it's */
		{                                                   /* not mapped, draw it anyway!!         */
			dungeon_redraw_feature(l,x,y,dungeon.map[l][x][y].feature);
		}

		dungeon.map[l][x][y].mapped=1;
	}

	return(see);
}

#ifndef DEV
#pragma optimize("",on)
#endif
