#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/* Wizard Spells battle magic*/

int _PASCAL cast_DRAGONFLAME1(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,1,TY_FIRE,WK_ICE,6,1,adv->level,TRUE));
}

int _PASCAL cast_HAMMERHAND(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[80];

	if (effective_strength(adv)<10)
	{
		sprintf(temp,"%s art too weak to use Hammerhand!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	if (cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			res=TRUE;

			sprintf(temp,"%s%s hands glow red!",adv->name,end_s(adv->name));
			print_spell_description(temp);

			twinkle(CMBT_X(adv->x),CMBT_Y(adv->y));

			adv->in_effect.hammerhand=COMBAT_DURATION;
		}
	}

	return(res);
}

int _PASCAL cast_ARC_LIGHTNING1(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,1,TY_ELECTRICITY,WK_NONE,6,1,adv->level,TRUE));
}

int _PASCAL cast_GRAVMUR_RAGE(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,1,TY_MIND,WK_NONE,4,1,adv->level));
}

int _PASCAL cast_FROZEN_WIND1(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,1,TY_ICE,WK_FIRE,6,1,adv->level,TRUE));
}

int _PASCAL cast_FIRE_MIST(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,1,TY_FIRE,WK_ICE,3,1,adv->level));
}

int _PASCAL cast_MIGHTY_APPEARANCE(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[80];

	if (cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			adv->in_effect.mighty_appearance+=adv->level;

			sprintf(temp,"%s%s effective strength increases to %d!",
						adv->name,
						end_s(adv->name),
						effective_strength(adv));

			print_spell_description(temp);

			twinkle(CMBT_X(adv->x),CMBT_Y(adv->y));

			res=TRUE;
		}
	}

	return(res);
}

/************************************************************************/

int _PASCAL cast_DRAGONFLAME2(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,2,TY_FIRE,WK_ICE,6,2,adv->level,TRUE));
}

int _PASCAL cast_LETHARGY(PLAYER *adv,SPELL_NAME *spell_name)
{
	MONSTER *mnst;
	int x,y;
	int endx,endy;

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,2))
		return(FALSE);

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
	{
		add_lost_spell_pts(adv,2);
		return(FALSE);
	}

	cmbt_between_points(adv->x,adv->y,x,y,&endx,&endy,cmbt_missile_draw_magenta);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_spell_missed(endx,endy);
		return(TRUE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	if (percent()>effective_monster_saving_throw(mnst,adv,NORMAL_SPELL_SAVE))
	{
		mnst->is_lethargic+=adv->level;
		cmbt_hit_a_square(mnst->x,mnst->y);

		print_spell_description("Thy foe succumbs to ye spell!");

		twinkle(CMBT_X(mnst->x),CMBT_Y(mnst->y));
	}
	else
	{
		spell_sound();
		spell_does_naught();
	}

	return(TRUE);
}

int _PASCAL cast_SWIFTNESS(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[80];
	PLAYER *on;
	int whom;

	if (cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,2))
		{
			whom=adv_select_adventurer("Cast","Swiftness on?",TRUE);

			if (whom!=ERR)
			{
				on=&TPP[whom];

				on->in_effect.swiftness+=adv->level;

				sprintf(temp,"%s%s effective speed increases to %d!",
							on->name,
							end_s(on->name),
							effective_speed(on));

				print_spell_description(temp);

				twinkle(CMBT_X(on->x),CMBT_Y(on->y));

				res=TRUE;
			}
			else
				add_lost_spell_pts(adv,2);
		}
	}

	return(res);
}

int _PASCAL cast_ARC_LIGHTNING2(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,2,TY_ELECTRICITY,WK_NONE,6,2,adv->level,TRUE));
}

int _PASCAL cast_BLINDING_FLASH(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,2,TY_ENERGY,WK_NONE,5,2,adv->level));
}

int _PASCAL cast_FROZEN_WIND2(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,2,TY_ICE,WK_FIRE,6,2,adv->level,TRUE));
}

/************************************************************************/

int _PASCAL cast_DRAGONFLAME3(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,3,TY_FIRE,WK_ICE,8,3,adv->level,TRUE));
}

int _PASCAL cast_ARC_LIGHTNING3(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,3,TY_ELECTRICITY,WK_NONE,8,3,adv->level,TRUE));
}

int _PASCAL cast_DEATH_CURSE(PLAYER *adv,SPELL_NAME *spell_name)
{
	MONSTER *mnst;
	int x,y,endx,endy;
	int killed=FALSE;
	int hit=FALSE;
	int damage=0;
	char *msg;
	char temp[60];
	int dice_base;
	int saved;

	if (adv->ethics!=CHAOTIC)
	{
		GX("Only chaotic wizards may cast Death Curse!",BAD);
		return(FALSE);
	}

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

	spell_sound();

	cmbt_between_points(adv->x,adv->y,
						x,y,
						&endx,&endy,
						cmbt_missile_draw_white);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_spell_missed(endx,endy);

		return(TRUE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	saved=(percent()>=effective_monster_saving_throw(mnst,adv,NORMAL_SPELL_SAVE))?FALSE:TRUE;

	dice_base=8;

	if (is_undead_or_demon(mnst))		/* Undead & Demons GAIN HP! */
	{
		cmbt_hit_a_square(mnst->x,mnst->y);

		mnst->current_hp+=get_dice_roll(adv->level,2,mnst->hd);
		cmbt_bad_msg("Thy foe appears stronger!",TRUE);

		morale_increase(mnst,2);

		half_pause();

		return(TRUE);
	}

	if (mnst->hd<4)
	{
		hit=killed=TRUE;
		msg="Thy foe art instantly vapourised!";
	}
	else
	if (mnst->hd<=adv->level)
	{
		hit=TRUE;

		if (saved)
		{
			damage=get_dice_roll(dice_base,adv->level,0);

			if (damage>=mnst->current_hp)
			{
				killed=TRUE;
				msg="Thy foe art turned to a bubbling pulp!";
			}
		}
		else
		{
			killed=TRUE;
			msg="All that remains of thy foe art ash!";
		}
	}
	else
	{
		if (saved)
			hit=killed=FALSE;
		else
		{
			damage=get_dice_roll(dice_base,adv->level/2,0);

			if (damage>=mnst->current_hp)
			{
				killed=TRUE;
				msg="Thy foe crumbles to dust - dead!";
			}
		}
	}

	if (hit)
	{
		cmbt_hit_a_square(mnst->x,mnst->y);

		if (killed)
		{
			combat_write(15,msg,TRUE);
			half_pause();
			cmbt_monster_is_slain(adv,mnst);
		}
		else
		{
			sprintf(temp,"%s inflicts %d damage.",adv->name,damage);
			combat_write(14,temp,TRUE);

			good_sound();

			monster_reduce_hp(mnst,damage);
		}
	}
	else
	{
		spell_does_naught();
	}

	return(TRUE);
}

int _PASCAL cast_BIND_DEMON(PLAYER *adv,SPELL_NAME *spell_name)
{
	int saved;
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

	spell_sound();

	cmbt_between_points(adv->x,adv->y,
						x,y,
						&endx,&endy,
						cmbt_missile_draw_blue);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_spell_missed(endx,endy);

		return(TRUE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	saved=((percent()>=effective_monster_saving_throw(mnst,adv,NORMAL_SPELL_SAVE))?FALSE:TRUE);

	if (mnst->bane_rune_type & TYP_DEMONIC)
	{
		twinkle(CMBT_X(mnst->x),CMBT_Y(mnst->y));

		if (mnst->hd>adv->level)
		{
			if (saved)
			{
				mnst->hd++;
				mnst->current_hp=mnst->hd*8;
				mnst->attack_damage[0]+=6;
				mnst->current_morale=MORALE_MAX;

				combat_write(4,"Ye Demon art dangerously enraged!",TRUE);
				solemn_sound();
			}
			else
			{
				mnst->spell_bound=adv->level;

				combat_write(14,"Ye demon art frozen still!",TRUE);
				good_sound();
			}
		}
		else
		{
			num_monsters--;
			num_monsters_killed++;
			cmbt_xp_gained+=mnst->xp;
			add_to_professionalism(adv,2);
			adv->kills++;

			mnst->current_hp=0;

			combat_write(15,"Thy foe returns to ye hells!",TRUE);
			good_sound();

			cmbt_dissolve_square(mnst->x,mnst->y);
			flash(CMBT_X(x)+5,CMBT_Y(y)+6);

			cmbt_area_nullify_square(mnst->x,mnst->y);
		}
	}
	else
	{
		spell_does_naught();
	}

	return(TRUE);
}

int _PASCAL cast_FROZEN_WIND3(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,3,TY_ICE,WK_FIRE,8,3,adv->level,TRUE));
}
