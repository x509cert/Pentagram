#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *  Player Missile Options #4
 *	Use wand/ring in combat
 *
 */

int _PASCAL actually_use_wand(PLAYER *adv,int wand)
{
	char temp[40];
	char *t="Using %s %s..";

	switch(wand)
	{
		case THUNDER_WAND : sprintf(temp,t,adv->his_her,STR_THUNDER_WAND); break;
		case ICE_WAND     : sprintf(temp,t,adv->his_her,STR_ICE_WAND);     break;
		case FIRE_WAND    : sprintf(temp,t,adv->his_her,STR_FIRE_WAND);    break;
		case DEVOURING_ROD: sprintf(temp,t,adv->his_her,STR_DEVOURING_ROD);break;
	}

	combat_write(11,temp,FALSE);

	if (actually_use_wand_get_mode()==WAND_MODE_SCATTER)
		return(actually_use_wand_scatter(adv,wand));
	else
		return(actually_use_wand_solitary(adv,wand));
}

int _PASCAL actually_use_wand_scatter(PLAYER *adv,int wand)
{
	int attack_failed;
	int endy,endx;
	int i;
	int base_damage=1,damage;
	MONSTER *mnst;
	int pc;
	void (_FAR *draw)(int xp,int yp);

	for (i=0; i<MAX_MONSTERS; i++)
	{
		mnst=&the_monsters[i];

		attack_failed=FALSE;

		if (monster_is_alive(mnst) && !mnst->flown)
		{
			switch(wand)
			{
				case THUNDER_WAND  : if (monster_imm_to_electricity(mnst))
										attack_failed=TRUE;
									 else
										base_damage=8;

									 draw=cmbt_missile_draw_blue;

									 break;

				case ICE_WAND      : if (monster_imm_to_ice(mnst))
										attack_failed=TRUE;
									 else
										base_damage=6;

									 draw=cmbt_missile_draw_white;

									 break;

				case FIRE_WAND     : if (monster_imm_to_fire(mnst))
										attack_failed=TRUE;
									 else
										base_damage=6;

									 draw=cmbt_missile_draw_red;

									 break;

				case DEVOURING_ROD : base_damage=10;

									 draw=cmbt_missile_draw_magenta;

									 break;
			}

			cmbt_between_points(adv->x,adv->y,
								mnst->x,mnst->y,
								&endx,&endy,
								draw);

			if (cmbt_area_contents(endx,endy)==IS_WALL)
			{
				cmbt_hit_a_square(endx,endy);
				combat_write(4,"Missed!",TRUE);
			}
			else
			{
				damage=get_dice_roll(base_damage,1,1);

				pc=percent();

				if (pc<effective_monster_saving_throw(mnst,NULL,WAND_MODE_SCATTER))
					attack_failed=TRUE;

				if (attack_failed || !damage)
				{
					wand_attack_failed();
				}
				else
				{
					wand_attack_succeeded(adv,mnst,damage);
				}

				if (are_all_monsters_dead_or_flown())
					break;
			}
		}
	}

	return(TRUE);
}

int _PASCAL actually_use_wand_solitary(PLAYER *adv,int wand)
{
	int x,y;
	int endy,endx;
	int fin;
	MONSTER *mnst;
	int attack_failed=FALSE;
	int base_damage=1,damage;
	void (_FAR *draw)(int xp,int yp);

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
		fin=FALSE;
	else
	{
		fin=TRUE;

		mnst=cmbt_area[x][y].occ.monster;

		switch(wand)
		{
			case THUNDER_WAND  : if (monster_imm_to_electricity(mnst))
									attack_failed=TRUE;
								 else
									base_damage=30;

								 draw=cmbt_missile_draw_blue;

								 break;

			case ICE_WAND      : if (monster_imm_to_ice(mnst))
									attack_failed=TRUE;
								 else
									base_damage=20;

								 draw=cmbt_missile_draw_white;

								 break;

			case FIRE_WAND     : if (monster_imm_to_fire(mnst))
									attack_failed=TRUE;
								 else
									base_damage=20;

								 draw=cmbt_missile_draw_red;

								 break;

			case DEVOURING_ROD : base_damage=50;

								 draw=cmbt_missile_draw_magenta;

								 break;
		}

		cmbt_between_points(adv->x,adv->y,
							x,y,
							&endx,&endy,
							draw);

		if (cmbt_area_contents(endx,endy)==IS_WALL)
		{
			cmbt_hit_a_square(endx,endy);
			combat_write(4,"Missed!",TRUE);

			return(TRUE);
		}

		if (percent()<effective_monster_saving_throw(mnst,NULL,WAND_MODE_SOLITARY))
			attack_failed=TRUE;

		damage=get_dice_roll(base_damage,1,adv->level);

		if (attack_failed || !damage)
		{
			wand_attack_failed();
		}
		else
		{
			wand_attack_succeeded(adv,mnst,damage);
		}
	}

	return(fin);
}

void _PASCAL wand_attack_succeeded(PLAYER *adv,MONSTER *mnst,int damage)
{
	char temp[80];

	cmbt_hit_a_square(mnst->x,mnst->y);

	sprintf(temp,"Thine attack inflicts %d damage.",damage);

	combat_write(14,temp,TRUE);

	monster_reduce_hp(mnst,damage);

	if (monster_is_dead(mnst))
		cmbt_monster_is_slain(adv,mnst);
	else
		cmbt_pause(1);
}

void _PASCAL wand_attack_failed()
{
	cmbt_bad_msg("Thine attack appears to do no harm!",TRUE);
}

int _PASCAL actually_use_wand_get_mode()
{
	GWINDOW win;
	int res;
	char *t2="ST";
	static char *t[]={"Scattered targets",
					  "Solitary target"};
	static int boundary[]={160,64,296,70,
						   160,72,296,78,
							-1,-1,-1,-1};

	win.x1=20;
	win.y1=8;
	win.x2=39;
	win.y2=12;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   7,
					   11);

	short_prompt_sound();

	switch(mouse_in_range(boundary,t2,""))
	{
		case 0 : res=WAND_MODE_SCATTER;  break;
		case 1 : res=WAND_MODE_SOLITARY; break;
	}

	kill_gwindow(&win);

	return(res);
}

int _PASCAL actually_use_ring(PLAYER *adv,int ring)
{
	int x,y;
	int endy,endx;
	int fin;
	MONSTER *mnst;
	int attack_failed=FALSE;
	int base_damage=1,damage;
	char temp[40];
	char *t="Using %s %s..";
	void (_FAR *draw)(int xp,int yp);

	if (!player_is_wearing(adv,ring))
	{
		cmbt_bad_msg("Ye must wear a ring to use it!",TRUE);
		return(FALSE);
	}

	switch(ring)
	{
		case RING_OF_FIRE	 : sprintf(temp,t,adv->his_her,STR_RING_OF_FIRE);
							   draw=cmbt_missile_draw_red;
							   break;

		case RING_OF_ICICLES : sprintf(temp,t,adv->his_her,STR_RING_OF_ICICLES);
							   draw=cmbt_missile_draw_white;
							   break;
	}

	combat_write(11,temp,FALSE);

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
		fin=FALSE;
	else
	{
		fin=TRUE;

		mnst=cmbt_area[x][y].occ.monster;

		switch(ring)
		{
			case RING_OF_ICICLES:if (monster_imm_to_ice(mnst))
									attack_failed=TRUE;
								 else
									base_damage=12;

								 break;

			case RING_OF_FIRE   :if (monster_imm_to_fire(mnst))
									attack_failed=TRUE;
								 else
									base_damage=12;

								 break;
		}

		cmbt_between_points(adv->x,adv->y,
							x,y,
							&endx,&endy,
							draw);

		if (cmbt_area_contents(endx,endy)==IS_WALL)
		{
			cmbt_hit_a_square(endx,endy);
			combat_write(4,"Missed!",TRUE);

			return(TRUE);
		}

		if (percent()<effective_monster_saving_throw(mnst,NULL,WAND_MODE_SOLITARY))
			attack_failed=TRUE;

		damage=get_dice_roll(base_damage,1,adv->level);

		if (attack_failed || !damage)
		{
			wand_attack_failed();
		}
		else
		{
			wand_attack_succeeded(adv,mnst,damage);
		}
	}

	return(fin);
}
