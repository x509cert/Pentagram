#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include "sprite.h"
#include "butil.h"

/*
 *
 *	Combat Arena Utilities
 *
 */

void _PASCAL cmbt_area_nullify_square(int x,int y)
{
	cmbt_area[x][y].nocc=IS_EMPTY;
	cmbt_blank_square(x,y);
}

static void _PASCAL _NEAR cmbt_blank_square(int x,int y)
{
	int x_off=CMBT_X(x);
	int y_off=CMBT_Y(y);

	if (IN_DUNGEON)
	{
		_setcolor(0);
		_rectangle(_GFILLINTERIOR,x_off,y_off,x_off+CMBT_SIZE_X-2,y_off+CMBT_SIZE_Y-2);
	}
	else
	{
		draw_cmbt_grass(x,y);
	}
}

void _PASCAL cmbt_hit_a_square(int x,int y)
{
	cmbt_grab_image(x,y);

	draw_hit(x,y);
	hit_sound();

	delay(100);

	cmbt_replace_image(x,y);

	delay(30);
}

void _PASCAL cmbt_buzz_a_square(int x,int y,int short_long)
{
	int i;

	cmbt_grab_image(x,y);

	for (i=0; i<(short_long==BUZZ_LONG?4:2); i++)
	{
		draw_choose(x,y,14);
		delay(100);

		if (!NO_SOUND)
			utspkr(100);

		cmbt_replace_image(x,y);

		utspkr(0);
		delay(80);
	}
}

void _PASCAL pos_one_monster(MONSTER *mnst,int x,int y)
{
	mnst->x=x;
	mnst->y=y;

	cmbt_area[x][y].occ.monster = mnst;
	cmbt_area[x][y].nocc        = IS_MONSTER;

	cmbt_draw_monster(x,y);
}

static void _PASCAL _NEAR cmbt_draw_monster(int x,int y)
{
	if (!IN_DUNGEON)
	{
		_putimage(CMBT_X(x),CMBT_Y(y),(char _FAR *)monster_mask_image,_GAND);
		_putimage(CMBT_X(x),CMBT_Y(y),(char _FAR *)monster_image,_GOR);
	}
	else
		_putimage(CMBT_X(x),CMBT_Y(y),(char _FAR *)monster_image,_GPSET);
}

void _PASCAL pos_party_member(PLAYER *adv,int x,int y)
{
	adv->x=x;
	adv->y=y;

	cmbt_area[x][y].occ.player = adv;
	cmbt_area[x][y].nocc       = IS_PLAYER;

	if (IN_DUNGEON)
		draw_adv_image(adv->nclass,CMBT_X(x),CMBT_Y(y));
	else
		draw_adv_cmbt_image(adv->nclass,CMBT_X(x),CMBT_Y(y));
}

int _PASCAL get_player_from_cmbt_square(int x,int y)
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			if ((unsigned)x==TPP[i].x &&
				(unsigned)y==TPP[i].y)
				return(i);

	return(ERR);
}

int _PASCAL get_monster_from_cmbt_square(int x,int y)
{
	int i;

	for (i=0; i<MAX_MONSTERS; i++)
		if (monster_is_alive(&the_monsters[i]))
			if ((unsigned)x==the_monsters[i].x &&
				(unsigned)y==the_monsters[i].y)
				return(i);
	return(ERR);
}

void _PASCAL cmbt_dissolve_square(int x,int y)
{
	int xoff=CMBT_X(x);
	int yoff=CMBT_Y(y);
	int i;
	int xr,yr;
	int in_dng=IN_DUNGEON;

	for (i=0; i<900; i++)
	{
		xr=rand()%(CMBT_SIZE_X-1);
		yr=rand()%(CMBT_SIZE_Y-1);

		if (xr<=0)
			xr=(rand()%CMBT_SIZE_X/2)+1;

		if (yr<=0)
			yr=(rand()%CMBT_SIZE_Y/2)+1;

		FFPLOT(xoff+xr,yoff+yr,(char)(in_dng?0:cmbtgrass_image[yr][xr]));

		delay(1);
	}
}

void _PASCAL cmbt_display_slaughter(int x,int y)
{
	cmbt_draw_rip(x,y);
	combat_death_sound();

	cmbt_half_pause();

	cmbt_dissolve_square(x,y);
	flash(CMBT_X(x)+6,CMBT_Y(y)+6);

	cmbt_area_nullify_square(x,y);
}

int _PASCAL cmbt_area_contents(int x,int y)
{
	if (x<0 || x>=CMBT_AREA_X || y<0 || y>=CMBT_AREA_Y)
		return(IS_WALL);

	return(cmbt_area[x][y].nocc);
}

void _PASCAL cmbt_between_points(int x1,int y1,   /* Bresenhams algorithm */
								 int x2,int y2,
								 int *stopx,int *stopy,
								 void (_FAR *draw_func)(int xd,int yd))
{
	int i,delta;
	int halfdelta;
	int deltax,deltay;
	int errnumx=0, errnumy=0;
	int ix,iy;
	int tone=800;
	int plot;

	*stopx=x1;
	*stopy=y1;

	if ((deltax=x2-x1)>0)
	{
		ix=1;
	}
	else
	if (deltax<0)
	{
		deltax=-deltax;
		ix=-1;
	}
	else
	{
		ix=0;
	}

	if ((deltay=y2-y1)>0)
	{
		iy=1;
	}
	else
	if (deltay<0)
	{
		deltay=-deltay;
		iy=-1;
	}
	else
	{
		iy=0;
	}

	delta=deltax>deltay?deltax:deltay;

	halfdelta=delta/2;

	if (!NO_SOUND)
		utspkr(tone);

	for (i=1; i<=delta; i++)
	{
		errnumx+=deltax;
		errnumy+=deltay;

		plot=FALSE;

		if (errnumx>halfdelta)
		{
			errnumx-=delta;
			x1+=ix;
			plot=TRUE;
		}

		if (errnumy>halfdelta)
		{
			errnumy-=delta;
			y1+=iy;
			plot=TRUE;
		}

		if (plot)
		{
			cmbt_grab_image(x1,y1);

			draw_func(x1,y1);

			*stopx=x1;
			*stopy=y1;

			if (!NO_SOUND)
			{
				tone-=80;
				utspkr(tone);
			}

			delay(40);

			cmbt_replace_image(x1,y1);

			if (cmbt_area_contents(x1,y1)==IS_WALL)
			{
				utspkr(0);
				return;
			}
		}
	}

	utspkr(0);
}

void _PASCAL cmbt_grab_image(int x,int y)
{
	int xoff=CMBT_X(x);
	int yoff=CMBT_Y(y);

	GETBLOCK(xoff,yoff,xoff+CMBT_SIZE_X,yoff+CMBT_SIZE_Y,underneath_image);
}

void _PASCAL cmbt_replace_image(int x,int y)
{
	PUTBLOCK(CMBT_X(x),CMBT_Y(y),underneath_image);
}

void _PASCAL cmbt_draw_rip(int x,int y)
{
	_putimage(CMBT_X(x),CMBT_Y(y),cmbt_rip_buffer,_GPSET);
}
