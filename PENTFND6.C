#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 * Monster Cast spell/Breath Weapon
 *
 */

int _PASCAL make_monster_cast_spell(MONSTER *mnst,int attack)
{
	PLAYER *adv;
	int player;
	int att=mnst->attack_type[attack];
	char temp[60];

	if (att!=MON_BREATH)
	{
		player=monster_get_spell_victim(mnst);

		if (player==ERR)
			return(FALSE);

		adv=&TPP[player];
	}

	switch(att)
	{
		case MON_FIRE		:
		case MON_ICE		:
		case MON_ELECTRICITY:
		case MON_MAGIC      :  sprintf(temp,"%s casts %s at %s!",
									mnst->name,
									mnst->magic_attack_string,
									adv->name);

							   break;

		case MON_SPIT_FIRE	:  sprintf(temp,"%s spits a ball of fire at %s!",
									mnst->name,
									adv->name);

							   break;

		case MON_ROCK       :  sprintf(temp,"%s hurls a rock at %s!",
									mnst->name,
									adv->name);

							   break;

		case MON_ARROW		:  sprintf(temp,"%s unleashes an arrow at %s!",
									mnst->name,
									adv->name);

							   break;

		case MON_BREATH     :  sprintf(temp,"%s breaths fire on thy party!",
									mnst->name);

							   break;

		case MON_GAZE       :  sprintf(temp,"%s gazes at %s!",
									mnst->name,
									adv->name);

							   break;

		default 			:  break;
	}

	combat_write(4,temp,FALSE);
	bad_sound();
	cmbt_pause(1);

	switch(att)
	{
		case MON_SPIT_FIRE	:
		case MON_FIRE       : monster_cast_fire(mnst,adv,attack);        break;
		case MON_ICE        : monster_cast_ice(mnst,adv,attack);         break;
		case MON_ELECTRICITY: monster_cast_electricity(mnst,adv,attack); break;
		case MON_MAGIC      : monster_cast_power_spell(mnst,adv,attack); break;
		case MON_BREATH     : monster_use_breath(mnst,attack);           break;
		case MON_ROCK		: monster_throw_rock(mnst,adv,attack);		 break;
		case MON_ARROW		: monster_fire_arrow(mnst,adv,attack);		 break;
		case MON_GAZE		: monster_use_gaze(mnst,adv,attack);		 break;
		default             : DEBUG(); break;
	}

	return(TRUE);
}

void _PASCAL _NEAR monster_cast_fire(MONSTER *mnst,PLAYER *adv,int attack)
{
	int save=((percent()<=effective_magic_save(adv,MON_FIRE))?TRUE:FALSE);
	monster_generic_cast_spell(mnst,adv,MON_FIRE,attack,save,cmbt_missile_draw_red);
}

void _PASCAL _NEAR monster_cast_ice(MONSTER *mnst,PLAYER *adv,int attack)
{
	int save=((percent()<=effective_magic_save(adv,MON_ICE))?TRUE:FALSE);
	monster_generic_cast_spell(mnst,adv,MON_ICE,attack,save,cmbt_missile_draw_blue);
}

void _PASCAL _NEAR monster_cast_electricity(MONSTER *mnst,PLAYER *adv,int attack)
{
	int save=((percent()<=effective_magic_save(adv,MON_ELECTRICITY))?TRUE:FALSE);
	monster_generic_cast_spell(mnst,adv,MON_ELECTRICITY,attack,save,cmbt_missile_draw_white);
}

void _PASCAL _NEAR monster_cast_power_spell(MONSTER *mnst,PLAYER *adv,int attack)
{
	int save=((percent()<=effective_magic_save(adv,MON_MAGIC))?TRUE:FALSE);
	monster_generic_cast_spell(mnst,adv,MON_MAGIC,attack,save,cmbt_missile_draw_magenta);
}

void _PASCAL _NEAR monster_fire_arrow(MONSTER *mnst,PLAYER *adv,int attack)
{
	int save=((percent()<=effective_magic_save(adv,MON_ARROW))?TRUE:FALSE);
	void (_FAR *draw)(int xp,int yp);

	switch(cmbt_missile_which_arrow(mnst->x,mnst->y,adv->x,adv->y))
	{
		case DIR_NORTH : draw=cmbt_missile_draw_north_arrow; break;
		case DIR_SOUTH : draw=cmbt_missile_draw_south_arrow; break;
		case DIR_EAST  : draw=cmbt_missile_draw_east_arrow;  break;
		case DIR_WEST  : draw=cmbt_missile_draw_west_arrow;  break;
	}

	monster_generic_cast_spell(mnst,adv,MON_ARROW,attack,save,draw);
}

void _PASCAL _NEAR monster_throw_rock(MONSTER *mnst,PLAYER *adv,int attack)
{
	int save=((percent()<=effective_magic_save(adv,MON_ROCK))?TRUE:FALSE);
	monster_generic_cast_spell(mnst,adv,MON_ROCK,attack,save,cmbt_missile_draw_rock);
}

void _PASCAL _NEAR monster_use_gaze(MONSTER *mnst,PLAYER *adv,int attack)
{
	int save=((percent()<=effective_magic_save(adv,MON_MAGIC))?TRUE:FALSE);
	monster_generic_cast_spell(mnst,adv,MON_GAZE,attack,save,cmbt_missile_draw_magenta);
}

void _PASCAL _NEAR monster_generic_cast_spell(MONSTER *mnst,
											  PLAYER *adv,
											  int type,
											  int attack,
											  int save,
											  void (_FAR *draw)(int xd,int yd))
{
	int ex,ey;
	int damage=get_dice_roll(mnst->attack_damage[attack],1,(mnst->hd/3)*2);

	cmbt_between_points(mnst->x,mnst->y,adv->x,adv->y,&ex,&ey,draw);

	if (cmbt_area_contents(ex,ey)==IS_WALL)
		monster_spell_hits_wall(ex,ey);
	else
	if (save || damage==0)
		monster_spell_fails(type);
	else
		monster_spell_succeeds(adv,damage);
}

void _PASCAL _NEAR monster_use_breath(MONSTER *mnst,int attack)
{
	int i;
	PLAYER *adv;
	char temp[80];
	int saved;

	for (i=0; i<=P_NUM; i++)
	{
		adv=&TPP[i];

		if (player_is_alive(adv) && percent()>effective_luck(adv))
		{
			sprintf(temp,"%s breaths at %s!",mnst->name,adv->name);
			cmbt_bad_msg(temp,TRUE);

			saved=(percent()>effective_dragon_breath_save(adv)?FALSE:TRUE);

			monster_generic_cast_spell(mnst,adv,MON_FIRE,attack,saved,cmbt_missile_draw_red);
		}
	}
}

void _PASCAL _NEAR monster_spell_hits_wall(int x,int y)
{
	cmbt_hit_a_square(x,y);
	combat_write(14,"Missed!",TRUE);
}

void _PASCAL _NEAR monster_spell_fails(int type)
{
	char *t;

	switch(type)
	{
		case MON_ROCK : t="but ye rock misses!";   break;
		default       : t="but causes no damage!"; break;
	}

	combat_write(14,t,TRUE);
	good_sound();
}

void _PASCAL _NEAR monster_spell_succeeds(PLAYER *adv,int damage)
{
	char temp[60];

	cmbt_hit_a_square(adv->x,adv->y);

	reduce_hp(adv,damage,NO_DISPLAY);

	sprintf(temp,"Inflicting %d damage on %s!",damage,adv->him_her);

	combat_write(12,temp,TRUE);

	cmbt_pause(1);

	if (player_is_dead(adv))
		cmbt_player_is_slain(adv);
	else
	if (player_is_weak(adv))
		cmbt_player_is_weak(adv);
}

int _PASCAL _NEAR monster_get_spell_victim(MONSTER *mnst)
{
	int i;
	int num_in_line=0;
	static struct {
					  int adv;
					  int dist;

				  } line[MAX_PARTY],closest;

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (straight_line_monster_to_player(mnst,&TPP[i]))
			{
				line[num_in_line].adv=i;
				line[num_in_line].dist=distance_between_points(mnst->x,
															   mnst->y,
															   TPP[i].x,
															   TPP[i].y);

				num_in_line++;
			}
		}
	}

	if (num_in_line==0)
		return(ERR);
	else
	if (num_in_line==1)
		return(line[0].adv);
	else
	{
		closest.adv =ERR;
		closest.dist=99;

		for (i=0; i<num_in_line; i++)
			if (line[i].dist<=closest.dist)
				closest=line[i];

		return(closest.adv);
	}
}
int _PASCAL _NEAR straight_line_monster_to_player(MONSTER *mnst, PLAYER *adv)
{
	int x1=mnst->x, y1=mnst->y, x2=adv->x, y2=adv->y;
	int i,delta;
	int halfdelta;
	int deltax,deltay;
	int errnumx=0, errnumy=0;
	int ix,iy;
	int plot;

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

		if (plot && cmbt_area_contents(x1,y1)==IS_WALL)
			return(FALSE);
	}

	return(TRUE);
}
