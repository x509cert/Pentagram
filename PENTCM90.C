#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <string.h>
#include "butil.h"
#ifdef DEV
#endif

/*
 *
 *	Combat write routine
 *
 */

#define SCROLL_WIDTH	14

void _PASCAL combat_write(int col,char *text,int drawline)
{
	char temp[100];
	int number_of_quotes,k,l,j;
	unsigned i;

	if (!strlen(text))
	{
		combat_write_mod_line(col,text,drawline);
		return;
	}

	Fscroll_combat(9);

	memset((void *)temp,0,sizeof(temp));

	for (i=0,number_of_quotes=0; i<strlen(text); i++)
		if (text[i]=='"')
			text[i]=(char)((++number_of_quotes&1)?'{':'}');

	for (i=0,j=0,k=0; i<strlen(text); i++)
	{
		temp[k++]=text[i];

		if (text[i]=='\n')
			j=0;

		if (++j>=SCROLL_WIDTH)
		{
			j=0;

			if (!isspace((int)temp[k]))
			{
				for (l=k; l>=0; l--, j++)
				{
					if (isspace((int)temp[l]))
					{
						temp[l]='\n';
						break;
					}
				}
			}
			else
				temp[k++]='\n';
		}
	}

	combat_write_mod_line(col,temp,drawline);
}

void _PASCAL combat_write_mod_line(int col,char *text,int drawline)
{
	int i,j;
	char t[2];

	if (strlen(text))
	{
		for (i=0,j=0; i<(int)strlen(text); i++)
		{
			if (text[i]!='\n')
			{
				t[0]=text[i];
				t[1]='\0';

				print_text(t,208+j*8,192-11,NORMAL_HEIGHT,col);
				j++;
			}
			else
			{
				Fscroll_combat(9);
				j=0;
			}
		}
	}

	if (drawline)
	{
		Fscroll_combat(9);
		draw_full_chain();
		Fscroll_combat(2);
	}
}

void _PASCAL draw_full_chain()
{
	draw_chain(209,192-9);
	draw_chain(245,192-9);
	draw_chain(272,192-9);
}

void _PASCAL select_a_foe_msg()
{
	int i;

	combat_write(6,"Select thy foe..",FALSE);

	if (NO_SOUND)
		return;

	for (i=0; i<2; i++)
	{
		utspkr(700);
		delay(50);
		utspkr(0);
		delay(30);
	}
}

void _PASCAL cmbt_bad_msg(char *msg,int paws)
{
	combat_write(4,msg,TRUE);

	bad_sound();

	if (paws)
		cmbt_pause(1);
}

void _PASCAL cmbt_print_spell_name(SPELL_NAME *spell_name)
{
	combat_write(5,spell_name->descrip,FALSE);
}

#ifdef DEV

void _PASCAL cmbt_DEBUG()
{
	GWINDOW win;
	char temp[80],mon[40];
	int i,j;
	int x,y;
	int col;

	if (!IN_COMBAT)
	{
		combat(WANDERING_MONSTER);
		return;
	}

	win.x1=25;
	win.y1=1;
	win.x2=40;
	win.y2=25;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	x=win.x1*8+2;
	y=win.y1;

	write_little("COMBAT DEBUG WINDOW",x,y*8,14,FAST);
	y++;

	for (i=0; i<MAX_MONSTERS+MAX_PARTY; i++)
	{
		switch(battle_order[i].nocc)
		{
			case IS_PLAYER   :  sprintf(temp,"%-14s %3d %2d %2u,%-2u",
									battle_order[i].occ.player->name,
									battle_order[i].occ.player->current_hp,
									battle_order[i].occ.player->level,
									battle_order[i].occ.player->x,
									battle_order[i].occ.player->y);

								col=1;

								break;

			case IS_MONSTER  :  strcpy(mon,battle_order[i].occ.monster->name);
								mon[13]='\0';

								sprintf(temp,"%-14s %3d %2d %2u,%-2u",
									mon,
									battle_order[i].occ.monster->current_hp,
									battle_order[i].occ.monster->hd,
									battle_order[i].occ.monster->x,
									battle_order[i].occ.monster->y);

								col=4;

								break;

			default          :  strcpy(temp,"--Empty--");
								col=7;
								break;

		}

		write_little(temp,x,y*8,col,FAST);
		y++;
	}

	y++;

	sprintf(temp,"Num Monsters %d",num_monsters);
	write_little(temp,x,y*8,7,FAST);
	y++;

	y=y*8+4;
	x+=30;

	_setcolor(5);
	_rectangle(_GBORDER,x-2,y-2,x+2+(CMBT_AREA_X*4),y+2+(CMBT_AREA_Y*4));

	for (i=0; i<CMBT_AREA_X; i++)
	{
		for (j=0; j<CMBT_AREA_Y; j++)
		{
			switch(cmbt_area[i][j].nocc)
			{
				case IS_PLAYER	: col=1; break;
				case IS_MONSTER : col=4; break;
				case IS_WALL	: col=7; break;
				default 		: col=0; break;
			}

			_setcolor(col);
			_rectangle(_GFILLINTERIOR,x+(i*4),y+(j*4),x+2+(i*4),y+2+(j*4));
		}
	}

	getch();

	kill_gwindow(&win);
}

#endif
