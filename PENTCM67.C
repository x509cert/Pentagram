#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include "bkeybrd.h"
#include "bkeys.h"

/*
 *
 *	During combat, select a square about a player
 *
 *	1 square for moving, and short range melee
 *	2 squares for medium range melee with halberd
 *	9 squares for long range melee with oil and spells
 *
 */

void _PASCAL cmbt_select_sq_around_player(int dist,
										  int *x,int *y,
										  int monst,int player,int empty)
{
	int startx, starty;
	int newx,newy;
	int ax,ay;
	int fin=FALSE;
	int scan,key;
	int legal=TRUE;
	int input=FALSE;
	int mx,my;
	int old_mx,old_my;
	char dummy;
	int MV_UP, MV_DOWN, MV_BOSS, MV_HELP, MV_LEFT, MV_RIGHT, MV_ENTER;

	ax=startx=newx=*x;
	ay=starty=newy=*y;

	if (mouse_installed)
	{
		mouse_set_combat_move_mickey();

		old_mx=mouse_x;
		old_my=mouse_y;

		mouse_x=160;
		mouse_y=100;

		mouse_gotoxy(mouse_x,mouse_y);
	}

	while (!fin)
	{
		ax=*x;
		ay=*y;

		if (legal)
		{
			cmbt_grab_image(ax,ay);
			draw_x_hair(ax,ay,14);
		}

		if (mouse_installed)
			mouse_readxy(&mouse_x,&mouse_y);

		input=MV_HELP=MV_BOSS=MV_LEFT=MV_RIGHT=MV_UP=MV_DOWN=MV_ENTER=FALSE;

		while (!input)
		{
			if (kbready(&dummy,&scan))
			{
				key=kbgetkey(&scan);

				switch(scan)
				{
					case KB_S_A_B     : if (key==0) MV_BOSS=TRUE; break;
					case KB_S_N_F1    : MV_HELP=TRUE;             break;
					case KB_S_N_UP    : MV_UP=TRUE;               break;
					case KB_S_N_DOWN  : MV_DOWN=TRUE;             break;
					case KB_S_N_LEFT  : MV_LEFT=TRUE;             break;
					case KB_S_N_RIGHT : MV_RIGHT=TRUE;            break;
					case KB_S_N_ENTER : MV_ENTER=TRUE;            break;
				}
			}
			else
			{
				if (mouse_installed)
				{
					mouse_readxy(&mx,&my);

					if (mx!=mouse_x || my!=mouse_y)
					{
						if (my<mouse_y)
							MV_UP=TRUE;

						if (my>mouse_y)
							MV_DOWN=TRUE;

						if (mx<mouse_x)
							MV_LEFT=TRUE;

						if (mx>mouse_x)
							MV_RIGHT=TRUE;

						mouse_x=mx;
						mouse_y=my;
					}
					else
					{
						if (mouse_button_l())
							MV_ENTER=TRUE;

						if (mouse_button_r())
							MV_HELP=TRUE;
					}
				}
			}

			if (MV_BOSS  || MV_HELP || MV_LEFT ||
				MV_RIGHT || MV_UP	|| MV_DOWN || MV_ENTER)
				input=TRUE;
		}

		legal=FALSE;

		if (MV_BOSS)
		{
			oops_here_comes_the_boss();
		}
		else
		if (MV_HELP)
		{
			if (situation_status==OFF)
			{
				mouse_sound();

				if (mouse_installed)
					mouse_mickey_restore();

				situation_details();

				if (mouse_installed)
					mouse_set_combat_move_mickey();
			}
		}

		if (MV_UP)
		{
			if (cmbt_move_player_in_bounds(ax,ay-1) &&
				cmbt_move_player_allowed(startx,starty,ax,ay-1,dist))
			{
				legal=TRUE;
				newx=ax;
				newy=ay-1;
			}
		}

		if (MV_DOWN)
		{
			if (cmbt_move_player_in_bounds(ax,ay+1) &&
				cmbt_move_player_allowed(startx,starty,ax,ay+1,dist))
			{
				legal=TRUE;
				newx=ax;
				newy=ay+1;
			}
		}

		if (MV_RIGHT)
		{
			if (cmbt_move_player_in_bounds(ax+1,ay) &&
				cmbt_move_player_allowed(startx,starty,ax+1,ay,dist))
			{
				legal=TRUE;
				newx=ax+1;
				newy=ay;
			}
		}

		if (MV_LEFT)
		{
			if (cmbt_move_player_in_bounds(ax-1,ay) &&
				cmbt_move_player_allowed(startx,starty,ax-1,ay,dist))
			{
				legal=TRUE;
				newx=ax-1;
				newy=ay;
			}
		}

		if (MV_ENTER && !legal)
		{
			if (startx!=ax || starty!=ay)
			{
			   switch(cmbt_area_contents(ax,ay))
			   {
				   case IS_EMPTY   : if (empty)  legal=TRUE; break;
				   case IS_MONSTER : if (monst)  legal=TRUE; break;
				   case IS_PLAYER  : if (player) legal=TRUE; break;
				   default		   : legal=FALSE;			 break;
			   }

			   fin=legal;

			   if (legal)
				   move_player_sound();
			}
			else
			if (startx==ax && starty==ay)
			{
				legal=fin=TRUE;
			}

			if (!legal)
			{
				fin=FALSE;
				bad_sound();
			}
		}

		if (legal)
		{
			cmbt_replace_image(ax,ay);

			*x=newx;
			*y=newy;

			click_sound();
		}
	}

	if (mouse_installed)
	{
		mouse_x=old_mx;
		mouse_y=old_my;
		mouse_mickey_restore();
		mouse_gotoxy(mouse_x,mouse_y);
	}
}

int _PASCAL cmbt_move_player_allowed(int sx,int sy,int ex,int ey,int dist)
{
	return((abs(sx-ex)<=dist && abs(sy-ey)<=dist)?TRUE:FALSE);
}

int _PASCAL _NEAR cmbt_move_player_in_bounds(int x,int y)
{
	return((x>=0 && y>=0 && x<CMBT_AREA_X && y<CMBT_AREA_Y)?TRUE:FALSE);
}
