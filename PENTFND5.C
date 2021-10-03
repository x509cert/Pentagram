#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 * Monster Flee
 *
 */

void _PASCAL make_monster_flee(MONSTER *mnst)
{
	char temp[40];
	int num;

	if (mnst->can_plane_travel)
	{
		make_monster_fade(mnst);
		return;
	}

	if (mnst->flee_x==FLEE_COORDS_NOT_SET &&
		mnst->flee_y==FLEE_COORDS_NOT_SET)
		set_monster_flee_coords(mnst);

	if (monster_at_combat_edge(mnst))
	{
		sprintf(temp,"%s escapes ye battle!",mnst->name);
		combat_write(4,temp,TRUE);

		flee_sound();

		num=get_monster_from_cmbt_square(mnst->x,mnst->y);

		cmbt_area_nullify_square(mnst->x,mnst->y);

		the_monsters[num].flown=TRUE;
		the_monsters[num].current_hp=0;

		cmbt_xp_gained+=(mnst->xp/2);

		num_monsters--;

		morale_all_decrease(percent()>75?2:1);

		cmbt_pause(1);

		return;
	}

	actually_make_monster_move(mnst);
}

int _PASCAL monster_at_combat_edge(MONSTER *mnst)
{
	if (mnst->x==0             ||
		mnst->y==0             ||
		mnst->x>=CMBT_AREA_X-1 ||
		mnst->y>=CMBT_AREA_Y-1)
		return(TRUE);
	else
		return(FALSE);
}

void _PASCAL set_monster_flee_coords(MONSTER *mnst)
{
	int dn,ds,de,dw;
	int i,can_exit=FALSE;
	static struct _flee_c {
							 int dist;
							 int dir;

						  } flee_dirs[4];

	dn=mnst->y;
	ds=abs(CMBT_AREA_Y-mnst->y);

	dw=mnst->x;
	de=abs(CMBT_AREA_X-mnst->x);

	flee_dirs[0].dist=dn;
	flee_dirs[0].dir =DIR_NORTH;

	flee_dirs[1].dist=ds;
	flee_dirs[1].dir =DIR_SOUTH;

	flee_dirs[2].dist=de;
	flee_dirs[2].dir =DIR_EAST;

	flee_dirs[3].dist=dw;
	flee_dirs[3].dir =DIR_WEST;

	qsort((void *)&flee_dirs[0],
		  SIZE(flee_dirs),
		  sizeof(flee_dirs[0]),
		  flee_closest_wall);

	for (i=0; i<SIZE(flee_dirs); i++)
	{
		switch(flee_dirs[i].dir)
		{
			case DIR_NORTH  : can_exit=set_monster_flee_coordsN(mnst); break;
			case DIR_EAST   : can_exit=set_monster_flee_coordsE(mnst); break;
			case DIR_WEST   : can_exit=set_monster_flee_coordsW(mnst); break;
			case DIR_SOUTH  : can_exit=set_monster_flee_coordsS(mnst); break;
		}

		if (can_exit)
			break;
	}
}

int _PASCAL set_monster_flee_coordsN(MONSTER *mnst)
{
	int i;

	if (cmbt_area_contents(mnst->x,0)==IS_EMPTY)
	{
		mnst->flee_x=mnst->x;
		mnst->flee_y=0;

		return(TRUE);
	}

	for (i=0; i<CMBT_AREA_X; i++)
	{
		if (cmbt_area_contents(i,0)==IS_EMPTY)
		{
			mnst->flee_x=i+1;
			mnst->flee_y=0;

			return(TRUE);
		}
	}

	return(FALSE);
}

int _PASCAL set_monster_flee_coordsS(MONSTER *mnst)
{
	int i;
	int px,py;

	get_party_combat_location(&px,&py);

	if (mnst->y<(unsigned)py)
		return(FALSE);

	if (cmbt_area_contents(mnst->x,CMBT_AREA_Y-1)==IS_EMPTY)
	{
		mnst->flee_x=mnst->x;
		mnst->flee_y=CMBT_AREA_Y-1;

		return(TRUE);
	}

	for (i=0; i<CMBT_AREA_X; i++)
	{
		if (cmbt_area_contents(i,CMBT_AREA_Y-1)==IS_EMPTY)
		{
			mnst->flee_x=i+1;
			mnst->flee_y=CMBT_AREA_Y-1;

			return(TRUE);
		}
	}

	return(FALSE);
}

int _PASCAL set_monster_flee_coordsE(MONSTER *mnst)
{
	int i;

	if (cmbt_area_contents(CMBT_AREA_X-1,mnst->y)==IS_EMPTY)
	{
		mnst->flee_x=CMBT_AREA_X-1;
		mnst->flee_y=mnst->y;

		return(TRUE);
	}

	for (i=0; i<CMBT_AREA_Y; i++)
	{
		if (cmbt_area_contents(CMBT_AREA_X-1,i)==IS_EMPTY)
		{
			mnst->flee_x=CMBT_AREA_X-1;
			mnst->flee_y=i+1;

			return(TRUE);
		}
	}

	return(FALSE);
}

int _PASCAL set_monster_flee_coordsW(MONSTER *mnst)
{
	int i;

	if (cmbt_area_contents(0,mnst->y)==IS_EMPTY)
	{
		mnst->flee_x=0;
		mnst->flee_y=mnst->y;

		return(TRUE);
	}

	for (i=0; i<CMBT_AREA_Y; i++)
	{
		if (cmbt_area_contents(0,i)==IS_EMPTY)
		{
			mnst->flee_x=0;
			mnst->flee_y=i+1;

			return(TRUE);
		}
	}

	return(FALSE);
}

int _CDECL flee_closest_wall(int *n1,int *n2)
{
	return(sgn(*n1-*n2));
}

void _PASCAL make_monster_fade(MONSTER *mnst)
{
	int num;

	combat_write(14,"Thy foe begins to fade....",TRUE);
	good_sound();

	num=get_monster_from_cmbt_square(mnst->x,mnst->y);

	the_monsters[num].flown=TRUE;
	the_monsters[num].current_hp=0;

	cmbt_xp_gained+=(mnst->xp/2);

	num_monsters--;

	morale_all_decrease(percent()>75?2:1);

	cmbt_dissolve_square(mnst->x,mnst->y);
	flash(CMBT_X(mnst->x)+5,CMBT_Y(mnst->y)+6);

	cmbt_area_nullify_square(mnst->x,mnst->y);

	combat_write(15,"GONE!",TRUE);

	flee_sound();
}
