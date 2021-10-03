#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <butil.h>

/* Illusionist Spells battle magic */

int _PASCAL cast_HORRIFY(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_HORRIFY_or_JONAS_SPOOK(adv,spell_name,1));
}

int _PASCAL cast_PHANTASM1(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,1,TY_MIND,WK_NONE,4,1,adv->level));
}

int _PASCAL cast_STAR_FLARE(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,1,TY_ENERGY,WK_NONE,8,1,adv->level,FALSE));
}

int _PASCAL cast_AXELS_BLUR(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_generic_AXEL(adv,spell_name,1));
}

int _PASCAL cast_ALLYS_DANCING_DAGGER(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_generic_ALLYS_spell(adv,spell_name,1));
}

/************************************************************************/

int _PASCAL cast_JONAS_SPOOK(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_HORRIFY_or_JONAS_SPOOK(adv,spell_name,2));
}

int _PASCAL cast_KORINAS_LEAP(PLAYER *adv,SPELL_NAME *spell_name)
{
	int x,y;
	PLAYER *on;
	int whom;
	int res=FALSE;
	char temp[60];

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,2))
		return(FALSE);

	whom=adv_select_adventurer("Cast Korina's","Leap on?",TRUE);

	if (whom!=ERR)
	{
		res=TRUE;

		on=&TPP[whom];
		x=on->x;
		y=on->y;

		sprintf(temp,"Whither dost %s leap?",on->name);
		combat_write(14,temp,TRUE);

		general_low_sound();

		cmbt_select_sq_around_player(9,&x,&y,FALSE,FALSE,TRUE);

		if ((unsigned)x==on->x && (unsigned)y==on->y)
		{
			add_lost_spell_pts(adv,2);
			return(FALSE);
		}

		spell_sound();

		twinkle(CMBT_X(on->x),CMBT_Y(on->y));

		korinas_leap_sound();

		cmbt_area_nullify_square(on->x,on->y);

		on->x=x;
		on->y=y;

		cmbt_area_nullify_square(x,y);
		pos_party_member(on,x,y);

		korinas_leap_sound();
	}
	else
		add_lost_spell_pts(adv,2);

	return(res);
}

int _PASCAL cast_PHANTASM2(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,2,TY_MIND,WK_NONE,4,2,adv->level));
}

int _PASCAL cast_MOON_FLARE(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,2,TY_ENERGY,WK_NONE,8,2,adv->level,FALSE));
}

int _PASCAL cast_AXELS_SHIMMER(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_generic_AXEL(adv,spell_name,2));
}

int _PASCAL cast_ALLYS_DANCING_MACE(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_generic_ALLYS_spell(adv,spell_name,2));
}

/************************************************************************/

int _PASCAL cast_AXELS_SHADOW(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_generic_AXEL(adv,spell_name,3));
}

int _PASCAL cast_SUN_FLARE(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,3,TY_ENERGY,WK_NONE,8,3,adv->level,FALSE));
}

int _PASCAL cast_SUSPEND_TIME(PLAYER *adv,SPELL_NAME *spell_name)
{
	int x,y,endx,endy;
	MONSTER *mnst;

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

	mnst=cmbt_area[x][y].occ.monster;

	cmbt_between_points(adv->x,adv->y,x,y,&endx,&endy,cmbt_missile_draw_magenta);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_spell_missed(endx,endy);
		return(TRUE);
	}

	if (percent()>effective_monster_saving_throw(mnst,adv,NORMAL_SPELL_SAVE))
	{
		spell_does_naught();
	}
	else
	{
		combat_write(15,"Time stagnates for thy foe!",TRUE);
		good_sound();

		twinkle(CMBT_X(mnst->x),CMBT_Y(mnst->y));

		mnst->time_suspended+=(adv->level+1);
	}

	return(TRUE);
}

int _PASCAL cast_PHANTASM3(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_scatter_battle_magic(adv,spell_name,3,TY_MIND,WK_NONE,6,3,adv->level));
}

int _PASCAL cast_ALLYS_DANCING_SABRE(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_generic_ALLYS_spell(adv,spell_name,3));
}

int _PASCAL _NEAR cast_generic_ALLYS_spell(PLAYER *adv,SPELL_NAME *spell_name,int pts)
{
	int x,y,endx,endy;
	MONSTER *mnst;
	int lv=adv->level+1;

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,pts))
		return(FALSE);

	if (adv->in_effect.allys_dancing_dagger +
		adv->in_effect.allys_dancing_mace   +
		adv->in_effect.allys_dancing_sabre)
	{
		cmbt_bad_msg("Ye hath already an Ally's spell active!",TRUE);

		add_lost_spell_pts(adv,pts);

		return(FALSE);
	}

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
	{
		add_lost_spell_pts(adv,pts);
		return(FALSE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	print_spell_description("A ghostly shape drifts towards thy foe!");

	cmbt_between_points(adv->x,adv->y,mnst->x,mnst->y,&endx,&endy,cmbt_missile_draw_sling_shot);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_spell_missed(endx,endy);
		return(TRUE);
	}

	adv->in_effect.allys_opponent=mnst;

	switch(spell_name->name)
	{
		case ALLYS_DANCING_DAGGER : adv->in_effect.allys_dancing_dagger+=lv;
									break;

		case ALLYS_DANCING_MACE   : adv->in_effect.allys_dancing_mace+=lv;
									break;

		case ALLYS_DANCING_SABRE  : adv->in_effect.allys_dancing_sabre+=lv;
									break;
	}

	ALLYS_spell_actually_hit(adv);

	return(TRUE);
}

void _PASCAL ALLYS_spell_actually_hit(PLAYER *adv)
{
	MONSTER *mnst;
	int damage=0;
	int base=0,add=adv->level;
	int hit_chance=ERR;
	char *weapon,temp[80];

	mnst=adv->in_effect.allys_opponent;

	if (mnst==NULL || monster_is_dead(mnst))
	{
		nullify_allys_spells(adv);
		return;
	}

	if (adv->in_effect.allys_dancing_dagger)
	{
		weapon="Dagger";
		hit_chance=60;
		base=3;
	}
	else
	if (adv->in_effect.allys_dancing_mace)
	{
		weapon="Mace";
		hit_chance=70;
		base=6;
	}
	else
	if (adv->in_effect.allys_dancing_sabre)
	{
		weapon="Sabre";
		hit_chance=80;
		base=8;
	}

	if (hit_chance==ERR)
		return;

	hit_chance+=(adv->level*2);
	hit_chance+=(mnst->ac*3);

	if (adv->bane_rune!=TYP_NO_RUNES)
	{
		if (adv->bane_rune==mnst->monster_type)
		{
			hit_chance+=10;
			add+=(rand()%5);
		}
	}

	sprintf(temp,"%s%s Allys Dancing %s attacks..",
		   adv->name,
		   end_s(adv->name),
		   weapon);

	combat_write(11,temp,FALSE);
	general_low_sound();
	half_pause();

	damage=get_dice_roll(base,1,add);

	if (damage<=0)
		hit_chance=ERR;

	if (percent()<=hit_chance)
	{
		sprintf(temp,"inflicting %d damage.",damage);

		cmbt_hit_a_square(mnst->x,mnst->y);

		combat_write(14,temp,TRUE);

		monster_reduce_hp(mnst,damage);

		if (monster_is_dead(mnst))
		{
			cmbt_monster_is_slain(adv,mnst);
			nullify_allys_spells(adv);
		}
	}
	else
	{
		cmbt_bad_msg("But inflicts no damage!",TRUE);
	}
}

int _PASCAL _NEAR cast_HORRIFY_or_JONAS_SPOOK(PLAYER *adv,SPELL_NAME *spell_name,int pts)
{
	int x,y,endx,endy;
	MONSTER *mnst;
	int save;

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,pts))
		return(FALSE);

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
	{
		add_lost_spell_pts(adv,pts);
		return(FALSE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	save=effective_monster_saving_throw(mnst,adv,NORMAL_SPELL_SAVE);

	if (spell_name->name==JONAS_SPOOK)
		save/=2;

	spell_sound();

	cmbt_between_points(adv->x,adv->y,x,y,&endx,&endy,cmbt_missile_draw_white);

	if (cmbt_area_contents(endx,endy)==IS_WALL)
	{
		cmbt_spell_missed(endx,endy);
		return(TRUE);
	}

	if (percent()<=save || monster_imm_to_mind_spells(mnst))
	{
		spell_does_naught();
	}
	else
	{
		mnst->current_morale=0;
		mnst->morale_affected=TRUE;
		mnst->fleeing=TRUE;

		combat_write(14,"An aura of panic envelops thy foe!",TRUE);

		good_sound();

		twinkle(CMBT_X(mnst->x),CMBT_Y(mnst->y));
	}

	return(TRUE);
}

int _PASCAL _NEAR cast_generic_AXEL(PLAYER *adv,SPELL_NAME *spell_name,int pts)
{
	char temp[80];
	char *msg,*desc;
	int dur;
	int lv=adv->level;
	int whom;
	int res=FALSE;

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,pts))
		return(FALSE);

	switch(spell_name->name)
	{
		case AXELS_BLUR     : msg="Blur";    dur=lv+1;   desc="ruby";   break;
		case AXELS_SHIMMER  : msg="Shimmer"; dur=lv+1;   desc="violet"; break;
		case AXELS_SHADOW   : msg="Shadow";  dur=lv*2+1; desc="indigo"; break;
	}

	sprintf(temp,"%s on?",msg);

	whom=adv_select_adventurer("Cast Axel's",temp,TRUE);

	if (whom!=ERR)
	{
		res=TRUE;

		switch(spell_name->name)
		{
			case AXELS_BLUR     : TPP[whom].in_effect.axels_blur+=dur;    break;
			case AXELS_SHIMMER  : TPP[whom].in_effect.axels_shimmer+=dur; break;
			case AXELS_SHADOW   : TPP[whom].in_effect.axels_shadow+=dur;  break;
		}

		sprintf(temp,"A %s sheen covers %s!",desc,TPP[whom].name);
		print_spell_description(temp);

		twinkle(CMBT_X(TPP[whom].x),CMBT_Y(TPP[whom].y));
	}
	else
		add_lost_spell_pts(adv,pts);

	return(res);
}
