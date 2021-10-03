#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <butil.h>

/* Druid Spells battle magic */

int _PASCAL cast_TRUEFLIGHT(PLAYER *adv,SPELL_NAME *spell_name)
{
	char temp[60];
	int res=FALSE;

	if (cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			adv->in_effect.trueflight+=4;

			sprintf(temp,"A pearly haze encircles %s!",adv->name);
			print_spell_description(temp);

			twinkle(CMBT_X(adv->x),CMBT_Y(adv->y));

			res=TRUE;
		}
	}

	return(res);
}

int _PASCAL cast_FLAME_SHEET(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,1,TY_FIRE,WK_ICE,6,1,adv->level,FALSE));
}

int _PASCAL cast_RAZOR_LEAVES1(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,1,TY_ENERGY,WK_NONE,3,1,adv->level));
}

/************************************************************************/

int _PASCAL cast_RAZOR_LEAVES2(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,2,TY_ENERGY,WK_NONE,3,2,adv->level));
}

int _PASCAL cast_TANGLE_THORNS(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[80];

	if (cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,2))
		{
			adv->in_effect.tangle_thorns+=(adv->level+1);

			sprintf(temp,"A misty hedge of piercing thorns engulfs %s",adv->name);
			print_spell_description(temp);

			twinkle(CMBT_X(adv->x),CMBT_Y(adv->y));

			res=TRUE;
		}
	}

	return(res);
}

int _PASCAL cast_ICE_HAMMER(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,2,TY_ENERGY,WK_NONE,5,2,adv->level,FALSE));
}

/************************************************************************/

int _PASCAL cast_ASCERTAIN_POWER(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	int i,xr,yr;
	int max_hp, hpp;
	GWINDOW win;
	int sq=6;
	static int col[]={15,11,9,1};
	static char *opt[]={"HIGH","AVERAGE","LOW","WEAK"};
	static int boundary[]={210,130,245,142,
						   -1,-1,-1,-1};

	if (cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,3))
		{
			res=TRUE;

			win.x1=20;
			win.y1=7;
			win.x2=37;
			win.y2=20;
			win.back=0;
			win.border=14;

			xr=win.x1*8+10;
			yr=win.y1*8+13;

			spell_sound();

			make_gwindow(&win);

			_settextposition(win.y1+1,win.x1+1);
			_settextcolor(5);
			_outtext(STR_ASCERTAIN_POWER);

			write_little("STRENGTH",235,73,5,FAST);

			for (i=0; i<4; i++)
			{
				_setcolor(col[i]);
				_rectangle(_GFILLINTERIOR,235,83+(i*10),235+sq,83+sq+(i*10));

				write_little(opt[i],248,83+(i*10)+2,13,FAST);
			}

			_setcolor(4);
			_rectangle(_GBORDER,
					   xr,
					   yr,
					   xr+(sq*CMBT_AREA_X),
					   yr+(sq*CMBT_AREA_Y));

			click_box(210,130,B_OK);

			max_hp=the_monsters[0].hd*8;

			for (i=0; i<MAX_MONSTERS; i++)
			{
				if (monster_is_alive(&the_monsters[i]))
				{
					if (!NO_SOUND)
						utspkr(100);

					hpp=((the_monsters[i].current_hp*100)/max_hp);

					_setcolor(col[3]);

					if (hpp>=75)
						_setcolor(col[0]);
					else
					if (hpp>=50)
						_setcolor(col[1]);
					else
					if (hpp>=25)
						_setcolor(col[2]);

					_rectangle(_GFILLINTERIOR,
							   xr+(sq*the_monsters[i].x+1),
							   yr+(sq*the_monsters[i].y+1),
							   xr+(sq*the_monsters[i].x+sq-1),
							   yr+(sq*the_monsters[i].y+sq-1));

					if (!NO_SOUND)
					{
						delay(20);
						utspkr(0);
					}
				}
			}

			(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

			kill_gwindow(&win);
		}
	}

	return(res);
}

int _PASCAL cast_BANISH_ELEMENTAL(PLAYER *adv,SPELL_NAME *spell_name)
{
	MONSTER *mnst;
	int x,y,endx,endy;

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,3))
		return(FALSE);

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
	{
		add_lost_spell_pts(adv,3);
		return(FALSE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	spell_sound();

	cmbt_between_points(adv->x,adv->y,x,y,&endx,&endy,cmbt_missile_draw_magenta);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_spell_missed(endx,endy);
	}
	else
	if (percent()>effective_monster_saving_throw(mnst,adv,NORMAL_SPELL_SAVE)
		&& is_an_elemental(mnst))
	{
		cmbt_hit_a_square(mnst->x,mnst->y);
		make_monster_fade(mnst);
	}
	else
	{
		spell_does_naught();
	}

	return(TRUE);
}

int _PASCAL cast_RAZOR_LEAVES3(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,3,TY_ENERGY,WK_NONE,4,3,adv->level));
}

int _PASCAL cast_CALL_HAILSTORM(PLAYER *adv,SPELL_NAME *spell_name)
{
	if (effective_temperature()>=0)
	{
		GX("'tis too warm to cast Call Hailstorm!",BAD);
		return(FALSE);
	}

	if (IN_DUNGEON || IN_RUIN)
	{
		GX("Call Hailstorm works only in ye wild!",BAD);
		return(FALSE);
	}

	return(generic_scatter_battle_magic(adv,spell_name,3,TY_ENERGY,WK_NONE,6,1,adv->level*2));
}

int _PASCAL cast_MAELSTROM(PLAYER *adv,SPELL_NAME *spell_name)
{
	int i;
	MONSTER *mnst;
	int x,y,endx,endy;
	char temp[40];
	int save;
	static char *col[]={"red","orange","green","blue","white"};
	static int ncol[]={12,6,10,9,15};

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,3))
		return(FALSE);

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
	{
		add_lost_spell_pts(adv,3);
		return(FALSE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	spell_sound();

	save=effective_monster_saving_throw(mnst,adv,NORMAL_SPELL_SAVE);

	cmbt_between_points(adv->x,adv->y,x,y,&endx,&endy,cmbt_missile_draw_magenta);

	if (((percent()*3)/2)>save)
	{
		if (cmbt_area_contents(endx,endy)==IS_WALL)
		{
			cmbt_spell_missed(endx,endy);
			return(TRUE);
		}

		adv->hp-=2;

		adv->current_hp=min(adv->current_hp,adv->hp);

		for (i=0; i<5; i++)
		{
			sprintf(temp,"%s light",col[i]);
			combat_write(ncol[i],temp,FALSE);

			inflict_spell_damage(adv,mnst,WK_NONE,TRUE,4,4,adv->level,NULL,mnst->x,mnst->y);

			if (monster_is_dead(mnst))
				break;

			half_pause();
		}
	}
	else
	{
		spell_does_naught();
	}

	return(TRUE);
}

int _PASCAL cast_EARTHQUAKE(PLAYER *adv,SPELL_NAME *spell_name)
{
	int i;
	MONSTER *mnst;
	int dice_base;
	int save_poss;

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,3))
		return(FALSE);

	if (IN_DUNGEON)
	{
		GX("An earthquake art an ill idea in a dungeon!",BAD);
		return(FALSE);
	}

	spell_sound();

	if (!NO_SOUND)
		utspkr(20);

	for (i=0; i<5; i++)
		shake_screen();

	utspkr(0);

	for (i=0; i<MAX_MONSTERS; i++)
	{
		mnst=&the_monsters[i];
		dice_base=12;

		if (mnst->current_hp>0 && !mnst->flown)
		{
			(void)get_spell_colour_and_dice(TY_QUAKE,&dice_base,mnst,&save_poss);

			inflict_spell_damage(adv,mnst,WK_QUAKE,save_poss,dice_base,1,
								 adv->level/2,NULL,mnst->x,mnst->y);
		}
	}

	return(TRUE);
}
