#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

/*
 *
 *	Player Missile Options #1
 *
 */

int _PASCAL cmbt_missile(PLAYER *adv)
{
	int fin=TRUE;
	char temp[80];
	char weap[30];

	if (bard_is_singing(adv,"throw a missile"))
		return(FALSE);

	strcpy(weap,get_weapon_name(adv->weapon_used.item));

	switch(adv->weapon_used.item)
	{
		case SLING		 : fin=cmbt_missile_sling(adv);    break;
		case CROSSBOW	 : fin=cmbt_missile_crossbow(adv); break;
		case BOW		 : fin=cmbt_missile_bow(adv);	   break;

		case DAGGER 	 :
		case AXE		 :
		case SHORT_SWORD :
		case LONG_SWORD  :
		case RAPIER 	 :
		case CLAYMORE	 :
		case MACE		 :
		case FLAIL		 :
		case HALBERD	 : fin=FALSE;
						   sprintf(temp,"Thou cannot use %s %s as a missile!",
								isvowel((int)*weap)?"an":"a",
								weap);

						   cmbt_bad_msg(temp,TRUE);

						   break;

		default 		 : fin=cmbt_missile_dart_oil_water(adv); break;
	}

	return(fin);
}

int _PASCAL cmbt_generic_missile(PLAYER *adv,
								 int attack_mode,
								 void (_FAR *draw_func)(int xd,int yd))
{
	int startx,starty,newx,newy,endy,endx;
	int hit_foe=TRUE;
	int per;
	int num;
	int chance;

	startx=newx=adv->x;
	starty=newy=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&newx,&newy,TRUE,FALSE,FALSE);

	if (newx==startx && newy==starty)
		return(FALSE);

	if (cmbt_move_player_allowed(newx,newy,startx,starty,1))
	{
		cmbt_cannot_use_in_close_melee(attack_mode);

		return(FALSE);
	}

	switch(attack_mode)
	{
		case CMBT_CROSSBOW	: adv->quarrels--;
							  break;

		case CMBT_BOW		: adv->arrows--;
							  break;

		case CMBT_DART		: adv->darts--;
							  break;

		default 			: break;
	}

	chance=percent()+modify_missile_for_distance(startx,starty,newx,newy);
	chance-=modify_missile_for_magic(adv,attack_mode);

	if (chance>effective_missile(adv))
	{
		hit_foe=FALSE;
		cmbt_get_missed_missile_pos(&newx,&newy);
	}

	if (draw_func==NULL)
	{
		switch(cmbt_missile_which_arrow(adv->x,adv->y,newx,newy))
		{
			case DIR_NORTH : draw_func=cmbt_missile_draw_north_arrow; break;
			case DIR_SOUTH : draw_func=cmbt_missile_draw_south_arrow; break;
			case DIR_EAST  : draw_func=cmbt_missile_draw_east_arrow;  break;
			case DIR_WEST  : draw_func=cmbt_missile_draw_west_arrow;  break;
			default 	   : DEBUG(); break;
		}
	}

	cmbt_between_points(adv->x,adv->y,newx,newy,&endx,&endy,draw_func);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_missile_hit_wall_msg(endx,endy);
		return(TRUE);
	}
	else
	if (cmbt_area_contents(endx,endy)==IS_PLAYER)
	{
		per=get_player_from_cmbt_square(endx,endy);

		if (per!=ERR)
			cmbt_missile_hit_adv(adv,&TPP[per],attack_mode);

		return(TRUE);
	}

	if (!hit_foe)
	{
		cmbt_missile_missed_msg();
		return(TRUE);
	}

	num=get_monster_from_cmbt_square(endx,endy);

	if (the_monsters[num].magic_weapon_to_hit &&
		(adv->weapon_used.type==NO_PLUS || adv->weapon_used.type==CURSED))
		wand_attack_failed();
	else
		cmbt_player_phys_hits(adv,&the_monsters[num],attack_mode);

	return(TRUE);
}

int _PASCAL cmbt_generic_oil_water(PLAYER *adv,int attack_mode)
{
	int startx,starty,newx,newy,endy,endx;
	int hit_foe=TRUE;
	int num;
	int chance;
	char temp[80];

	startx=newx=adv->x;
	starty=newy=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&newx,&newy,TRUE,FALSE,TRUE);

	if (newx==startx && newy==starty)
		return(FALSE);

	if (cmbt_move_player_allowed(newx,newy,startx,starty,1))
	{
		cmbt_cannot_use_in_close_melee(attack_mode);

		return(FALSE);
	}

	switch(attack_mode)
	{
		case CMBT_OIL		: adv->oil--;
							  break;

		case CMBT_HOLYWATER : potion_remove_from_player(adv,POT_HOLYWATER);
							  break;

		default 			: break;
	}

	chance=percent()+modify_missile_for_distance(startx,starty,newx,newy);

	if (chance>effective_missile(adv))
	{
		hit_foe=FALSE;
		cmbt_get_missed_missile_pos(&newx,&newy);
	}

	cmbt_between_points(adv->x,adv->y,
						newx,newy,
						&endx,&endy,
						cmbt_missile_draw_flask);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_missile_hit_wall_msg(endx,endy);
		cmbt_oil_water_splash(adv,endx,endy,attack_mode);

		return(TRUE);
	}

	if (!hit_foe)
	{
		cmbt_missile_missed_msg();

		if (get_dice_roll(25,1,0)<=effective_luck(adv))
		{
			sprintf(temp,"Ye flask lies unbroken in ye %s!",
						 (IN_DUNGEON||IN_RUIN)?"gloom":"tussock");

			combat_write(14,temp,TRUE);
			good_sound();

			if (attack_mode==CMBT_OIL)
				adv->oil_left++;
			else
				adv->holywater_left++;
		}
		else
		{
			if (attack_mode!=CMBT_OIL)
				cmbt_bad_msg("Thy flask ruptures, spilling its contents!",FALSE);
			else
				cmbt_bad_msg("Thy flask ruptures and ye flames art doused!",FALSE);
		}

		cmbt_pause(2);

		return(TRUE);
	}

	num=get_monster_from_cmbt_square(endx,endy);

	if (num!=ERR)
		cmbt_player_phys_hits(adv,&the_monsters[num],attack_mode);
	else
	{
		cmbt_hit_a_square(endx,endy);
		combat_write(14,"Thy flask shatters on ye ground!",TRUE);
		good_sound();
		cmbt_pause(1);
	}

	cmbt_oil_water_splash(adv,endx,endy,attack_mode);

	return(TRUE);
}

void _PASCAL cmbt_oil_water_splash(PLAYER *adv,int x,int y,int attack_mode)
{
	int i;
	int splashed;
	static int dir[]={-1,-1,
					  -1, 0,
					  -1, 1,
					   0,-1,
					   0, 1,
					   1,-1,
					   1, 0,
					   1, 1};
	MONSTER *mnst;
	PLAYER *adv2;

	for (i=0; i<SIZE(dir); i+=2)
	{
		if (cmbt_area_contents(x+dir[i],y+dir[i+1])==IS_MONSTER)
		{
			mnst=cmbt_area[x+dir[i]][y+dir[i+1]].occ.monster;
			splashed=FALSE;

			switch(attack_mode)
			{
				case CMBT_OIL		:	if (!monster_imm_to_fire(mnst))
											if (percent()>effective_monster_dodge_splash(mnst))
												splashed=TRUE;

										break;

				case CMBT_HOLYWATER :	if (is_undead_or_demon(mnst))
											if (percent()>effective_monster_dodge_splash(mnst))
												splashed=TRUE;

										break;
			}

			if (splashed)
				cmbt_monster_is_splashed(adv,mnst);
		}
		else
		if (cmbt_area_contents(x+dir[i],y+dir[i+1])==IS_PLAYER)
		{
			adv2=cmbt_area[x+dir[i]][y+dir[i+1]].occ.player;
			splashed=FALSE;

			if (attack_mode==CMBT_OIL)
				if (get_dice_roll(50,1,0)>effective_dragon_breath_save(adv))
					splashed=TRUE;

			if (splashed)
				cmbt_player_is_splashed(adv2);
		}
	}
}

void _PASCAL cmbt_missile_hit_adv(PLAYER *from,PLAYER *adv,int attack_mode)
{
	char *desc;
	int dam=0;
	int save=((percent()<=effective_magic_save(adv,MON_ARROW))?TRUE:FALSE);
	char temp[80];

	switch(attack_mode)
	{
		case CMBT_CROSSBOW	: desc="quarrel";	 dam=8; break;
		case CMBT_BOW		: desc="arrow"; 	 dam=6; break;
		case CMBT_DART		: desc="dart";		 dam=2; break;
		case CMBT_SLING 	: desc="sling shot"; dam=4; break;
		default 			: break;
	}

	if (dam==0)
		return;

	if (save)
	{
		sprintf(temp,"%s dodges %s%s %s!",
				  adv->name,
				  from->name,
				  end_s(from->name),
				  desc);

		combat_write(14,temp,TRUE);
		good_sound();
		cmbt_pause(1);
	}
	else
	{
		cmbt_player_is_missiled(from,adv,desc,dam);
	}
}

static int _PASCAL _NEAR modify_missile_for_distance(int x1,int y1,int x2,int y2)
{
	int dx=abs(x1-x2);
	int dy=abs(y1-y2);
	int v=max(dx,dy);
	int res=0;

	if (v>2)
		res=(v/2)*6;   /* 6% per 2 squares */

	return(res);
}

static int _PASCAL _NEAR modify_missile_for_magic(PLAYER *adv,int attack)
{
	int plus,add;

	switch(attack)
	{
		case CMBT_CROSSBOW	: add=12; plus=adv->weapon_used.type; break;
		case CMBT_BOW		: add=7;  plus=adv->weapon_used.type; break;
		default 			: add=0;  plus=NO_PLUS;
	}

	return((plus*7)+add);	  /* 7% per plus to hit */
}

static void _PASCAL _NEAR cmbt_missile_hit_wall_msg(int x,int y)
{
	char temp[40];
	char *hit="rock";

	if (IN_DUNGEON)
		hit="wall";
	else
	if (pent_data.current_feature==FOREST)
		hit="tree";

	sprintf(temp,"Thy shot hit a %s!",hit);

	cmbt_hit_a_square(x,y);
	cmbt_bad_msg(temp,TRUE);
}

static void _PASCAL _NEAR cmbt_missile_missed_msg()
{
	cmbt_bad_msg(percent()>50?"Thy shot misses it's mark!"
							 :"Thine aim goes much astray!",TRUE);
}

static void _PASCAL _NEAR cmbt_get_missed_missile_pos(int *x,int *y)
{
	int newx=*x;
	int newy=*y;

	newx+=plus_or_minus_one();
	newy+=plus_or_minus_one();

	newx=min(CMBT_AREA_X-1,newx);
	newx=max(0, 		   newx);
	newy=min(CMBT_AREA_Y-1,newy);
	newy=max(0, 		   newy);

	*x=newx;
	*y=newy;
}

void _PASCAL cmbt_cannot_use_in_close_melee(int weapon)
{
	char temp[60];
	char *wname;

	switch(weapon)
	{
		case CMBT_BOW	   :  wname="use a bow";	  break;
		case CMBT_CROSSBOW :  wname="use a crossbow"; break;
		case CMBT_DART	   :  wname="throw darts";	  break;
		case CMBT_SLING    :  wname="use a sling";	  break;
		case CMBT_OIL	   :
		case CMBT_HOLYWATER:  wname="throw flasks";   break;
	}

	sprintf(temp,"Thou cannot %s in close melee!",wname);

	cmbt_bad_msg(temp,TRUE);
}

int _PASCAL cmbt_missile_which_arrow(int px,int py,int mx,int my)
{
	int dir;
	int ns,ew;

	ns=my-py;
	ew=mx-px;

	if (abs(ns)>abs(ew))
	{
		if (sgn(ns)==1)
			dir=DIR_SOUTH;
		else
			dir=DIR_NORTH;
	}
	else
	{
		if (sgn(ew)==1)
			dir=DIR_EAST;
		else
			dir=DIR_WEST;
	}

	return(dir);
}
