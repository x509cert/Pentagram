#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

/*
 *
 *	Player/Monster damage routines
 *
 */

void _PASCAL cmbt_monster_is_slain(PLAYER *adv,MONSTER *mnst)
{
	static char *opts[]={"Nice Move!",
						 "Excellent!",
						 "Well Done!",
						 "Ouch!!",
						 "Wooooww!",
						 "Kkaappooww!",
						 "Impressive!"};

	add_to_professionalism(adv,1);
	adv->kills++;

	num_monsters--;
	num_monsters_killed++;

	cmbt_xp_gained+=mnst->xp;

	mnst->current_hp=0;

	morale_all_decrease(percent()>75?2:1);

	monster_perform_death_throes(mnst);
	combat_write(15,opts[rand()%SIZE(opts)],TRUE);
	good_sound();

	cmbt_pause(1);
}

void _PASCAL cmbt_player_is_slain(PLAYER *adv)
{
	char temp[80];

	cmbt_display_slaughter(adv->x,adv->y);

	morale_all_increase(percent()>75?1:2);

	if (percent()>50)
		sprintf(temp,
				"%s%s lifeless body falls in a heap!",
				adv->name,
				end_s(adv->name));
	else
		sprintf(temp,
				"%s falls over, twitches a little, then dies!",
				adv->name);

	cmbt_bad_msg(temp,TRUE);

	num_adv_killed++;
}

void _PASCAL cmbt_player_is_weak(PLAYER *adv)
{
	char temp[80];

	switch(rand()%3)
	{
		case 0 : sprintf(temp,"%s staggers a little!",adv->name);
				 break;

		case 1 : sprintf(temp,"%s loses %s balance!",adv->name,adv->his_her);
				 break;

		default: sprintf(temp,"%s stumbles a litle!",adv->name);
				 break;
	}

	combat_write(13,temp,TRUE);

	solemn_sound();
}

void _PASCAL cmbt_player_phys_misses(PLAYER *adv)
{
	char temp[80];

	sprintf(temp,"%s misses %s foe!",adv->name,adv->his_her);

	cmbt_bad_msg(temp,TRUE);
}

void _PASCAL cmbt_player_phys_hits(PLAYER *adv,MONSTER *mnst,int cmbt_mode)
{
	char temp[80];
	int damage;
	int still_poisoned=FALSE;

	if (cmbt_mode==CMBT_SLING	 ||
		cmbt_mode==CMBT_DART	 ||
		cmbt_mode==CMBT_CROSSBOW ||
		cmbt_mode==CMBT_BOW 	 ||
		cmbt_mode==CMBT_OIL 	 ||
		cmbt_mode==CMBT_HOLYWATER)
	{
		damage=effective_missile_damage(adv,mnst,cmbt_mode);
	}
	else
	{
		if (adv->weapon_used.poisoned)
			still_poisoned=drop_poison_for_weapon_used(adv);

		damage=effective_damage(adv,mnst);
	}

	damage+=adv->level;

	if (cmbt_mode==CMBT_BACKSTAB)
		damage+=(adv->level*BACKSTAB_MULTIPLIER);

	if (damage)
		sprintf(temp,"%s inflicts %d damage.",adv->name,damage);
	else
		sprintf(temp,"%s strikes %s foe, but causes no damage!",
						adv->name,
						adv->his_her);

	cmbt_hit_a_square(mnst->x,mnst->y);

	combat_write(damage?14:4,temp,TRUE);

	if (damage>=CRITICAL_HIT_THRESHOLD)
		if (player_scores_critical_hit(adv,mnst))
			damage=MAX_HP;

	monster_reduce_hp(mnst,damage);

	if (monster_is_dead(mnst))
		cmbt_monster_is_slain(adv,mnst);
	else
	{
		if (still_poisoned && !monster_imm_to_poison(mnst))
		{
			damage=get_dice_roll(6,2,adv->level);       /* Check poison */

			sprintf(temp,"Poison inflicts %d more damage!",damage);

			cmbt_hit_a_square(mnst->x,mnst->y);
			combat_write(2,temp,TRUE);

			monster_reduce_hp(mnst,damage);

			if (monster_is_dead(mnst))
				cmbt_monster_is_slain(adv,mnst);
		}

		if (is_monster_stunned_from_hit(mnst,damage))
			actually_stun_monster(mnst);
	}
}

void _PASCAL cmbt_monster_phys_hits(PLAYER *adv,MONSTER *mnst,int attack)
{
	int damage;
	char temp[60];

	cmbt_hit_a_square(adv->x,adv->y);

	damage=effective_monster_damage(mnst,attack);

	if (damage>=CRITICAL_HIT_THRESHOLD)
		if (monster_scores_critical_hit(adv,mnst))
			damage*=3;

	reduce_hp(adv,damage,NO_DISPLAY);

	sprintf(temp,"Inflicting %d damage on %s!",damage,adv->him_her);

	combat_write(12,temp,TRUE);

	cmbt_pause(1);

	if (player_is_dead(adv))
		cmbt_player_is_slain(adv);
	else
	if (player_is_weak(adv))
		cmbt_player_is_weak(adv);
	else
	{
		check_monster_poison_disease(adv,mnst,attack);

		if (is_player_stunned_from_hit(adv,damage))
			actually_stun_player(adv);
	}
}

void _PASCAL check_monster_poison_disease(PLAYER *adv,MONSTER *mnst,int attack)
{
	int dis=FALSE, poi=FALSE;
	char temp[60];

	if (monster_attack_is_magical(mnst,attack))
		return;

	if (mnst->poison_chance>0)
		poi=TRUE;
	else
	if (mnst->disease_chance>0)
		dis=TRUE;

	if (!poi && !dis)
		return;

	if (poi)
	{
		if ((unsigned)percent()<=mnst->poison_chance)
		{
			if (percent()>effective_poison_immunity(adv) && !adv->is_poisoned)
			{
				adv->is_poisoned= TRUE;

				sprintf(temp,"Poison flows through %s!",adv->name);
				combat_write(2,temp,TRUE);
				solemn_sound();
			}
		}
	}
	else
	{
		if ((unsigned)percent()<=mnst->disease_chance)
		{
			sprintf(temp,"%s feels light headed!",adv->name);
			combat_write(13,temp,TRUE);

			solemn_sound();

			contract_diseases_in_combat(adv,mnst);
		}
	}
}

void _PASCAL cmbt_monster_is_splashed(PLAYER *adv,MONSTER *mnst)
{
	int damage=get_dice_roll(4,1,1);
	char temp[50];

	sprintf(temp,"%s art splashed for %d damage.",
					mnst->name,
					damage);

	cmbt_hit_a_square(mnst->x,mnst->y);

	combat_write(14,temp,TRUE);

	monster_reduce_hp(mnst,damage);

	if (monster_is_dead(mnst))
		cmbt_monster_is_slain(adv,mnst);
	else
		cmbt_pause(1);
}

void _PASCAL cmbt_player_is_splashed(PLAYER *adv)
{
	int damage=get_dice_roll(4,1,1);
	char temp[50];

	sprintf(temp,"%s art splashed for %d damage.",
					adv->name,
					damage);

	cmbt_hit_a_square(adv->x,adv->y);

	cmbt_bad_msg(temp,FALSE);

	reduce_hp(adv,damage,NO_DISPLAY);

	if (player_is_dead(adv))
		cmbt_player_is_slain(adv);
	else
	if (player_is_weak(adv))
		cmbt_player_is_weak(adv);
	else
		cmbt_pause(1);
}

void _PASCAL cmbt_player_is_missiled(PLAYER *from,PLAYER *adv,char *msg,int dam)
{
	int damage=get_dice_roll(dam,1,1);
	char temp[80];
	static char *bit[]={"neck","arm","shoulder","chest","leg","hand"};

	sprintf(temp,"%s%s %s hits %s%s %s, inflicting %d damage!",
					from->name,
					end_s(from->name),
					msg,
					adv->name,
					end_s(adv->name),
					bit[rand()%SIZE(bit)],
					damage);

	cmbt_hit_a_square(adv->x,adv->y);

	cmbt_bad_msg(temp,FALSE);

	reduce_hp(adv,damage,NO_DISPLAY);

	if (player_is_dead(adv))
		cmbt_player_is_slain(adv);
	else
	if (player_is_weak(adv))
		cmbt_player_is_weak(adv);
	else
		cmbt_pause(1);
}

int _PASCAL player_scores_critical_hit(PLAYER *adv,MONSTER *mnst)
{
	if (adv->current_hp > mnst->current_hp)
	{
		if ((unsigned)(percent()+effective_luck(adv)) > (mnst->hd*7))
		{
			combat_write(15,"A Critical Hit!",TRUE);
			good_sound();
			good_sound();

			return(TRUE);
		}
	}

	return(FALSE);
}

int _PASCAL monster_scores_critical_hit(PLAYER *adv,MONSTER *mnst)
{
	char temp[80];

	if (adv->current_hp < mnst->current_hp)
	{
		if ((unsigned)(percent()+effective_luck(adv)) < (mnst->hd*7))
		{
			sprintf(temp,"Thy foe scores a critical hit on %s!",adv->name);

			combat_write(15,temp,TRUE);
			solemn_sound();

			cmbt_half_pause();

			return(TRUE);
		}
	}

	return(FALSE);
}
