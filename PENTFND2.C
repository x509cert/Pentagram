#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

int _PASCAL effective_monster_attack(MONSTER *mnst,PLAYER *player)
{
	return((18-mnst->hd)-effective_ac(player));
}

int _PASCAL effective_monster_damage(MONSTER *mnst,int att_num)
{
	return(get_dice_roll(mnst->attack_damage[att_num],1,1));
}

char *monster_phys_attack_string(MONSTER *mnst,PLAYER *player,int attack_num)
{
	char temp[80];
	static char final[100];

	switch(mnst->attack_type[attack_num])
	{
		case MON_CLAW	   :	strcpy(temp,"claws at");
								break;

		case MON_KICK	   :	strcpy(temp,"kicks");
								break;

		case MON_WEAPON    :	switch(mnst->weapon_type)
								{
									case MWPN_CLUB		  : sprintf(temp,"attacks %s with a club",player->name);
															break;

									case MWPN_SHORT_SWORD : sprintf(temp,"swings a sword at %s",player->name);
															break;

									case MWPN_AXE		  : sprintf(temp,"swings an axe at %s",player->name);
															break;

									case MWPN_HALBERD	  : sprintf(temp,"lunges at %s with a halberd",player->name);
															break;

									case MWPN_DAGGER      : sprintf(temp,"slashes at %s with a dagger",player->name);
															break;

									case MWPN_LONG_SWORD  : sprintf(temp,"swings a longsword at %s",player->name);
															break;
								}

								break;

		case MON_BITE	   :	strcpy(temp,"bites");
								break;

		case MON_TAIL_LASH :	strcpy(temp,"lashes its tail at");
								break;

		case MON_STING	   :	strcpy(temp,"attempts to sting");
								break;

		case MON_PUNCH	   :	strcpy(temp,"punches");
								break;
	}

	if (mnst->attack_type[attack_num]==MON_WEAPON)
		sprintf(final,"%s %s..",mnst->name,temp);
	else
		sprintf(final,"%s %s %s..",mnst->name,temp,player->name);

	return(final);
}

char *monster_phys_miss_string(MONSTER *mnst,PLAYER *player,int attack_num)
{
	static char temp[100];

	if (!player->is_parrying)
	{
		switch(mnst->attack_type[attack_num])
		{
			case MON_CLAW	   : sprintf(temp,"but it's claws swish past %s!",player->him_her);
								 break;

			case MON_KICK      : sprintf(temp,"but ye %s loses balance, missing %s!",mnst->name,player->him_her);
								 break;

			case MON_WEAPON    : sprintf(temp,"but ye weapon misses %s!",player->him_her);
								 break;

			case MON_BITE	   : sprintf(temp,"but it's bite inflicts no damage!");
								 break;

			case MON_TAIL_LASH : sprintf(temp,"but it's tail falls short!");
								 break;

			case MON_STING	   : sprintf(temp,"but it's stinger just misses %s",player->him_her);
								 break;

			case MON_PUNCH	   : sprintf(temp,"but ye %s loses balance, missing %s!",mnst->name,player->him_her);
								 break;
		}
	}
	else
		sprintf(temp,"skillfully, %s parries ye attack!",player->name);

	return(temp);
}

int _PASCAL effective_monster_dodge_splash(MONSTER *mnst)
{
	return((mnst->hd*5)+(mnst->agility*2)+get_dice_roll(20,1,0));
}

int _PASCAL effective_monster_surprise(MONSTER *mnst)
{
	int res;

	res=mnst->surprise;

	switch(num_monsters)
	{
		case 1 : res+=4; break;
		case 2 : res+=2; break;
		case 3 : res+=1; break;
		case 4 :         break;
		case 5 : res-=1; break;
		case 6 : res-=3; break;
		default: res-=4; break;
	}

	return(min(max(0,res),20));
}

int _PASCAL effective_monster_initiative(MONSTER *mnst)
{
	int res=mnst->agility;

	if (first_round)
		res+=surprise_mod;

	if (monster_is_weak(mnst))
		res-=2;

	if (mnst->attack_type[0]==MON_CLAW ||
		mnst->attack_type[0]==MON_KICK ||
		mnst->attack_type[0]==MON_BITE)
		res+=2;

	if (mnst->is_lethargic)
		res-=2;

	if (mnst->spell_bound || mnst->time_suspended)
		res-=5;

	if (mnst->is_stunned)
		res/=2;

	return(res);
}

int _PASCAL monster_is_alive(MONSTER *mnst)
{
	return(mnst->current_hp>0?TRUE:FALSE);
}

int _PASCAL monster_is_dead(MONSTER *mnst)
{
	return((monster_is_alive(mnst)==TRUE)?FALSE:TRUE);
}

int _PASCAL monster_imm_to_poison(MONSTER *mnst)
{
	return(mnst->poison_immunity);
}

int _PASCAL monster_imm_to_fire(MONSTER *mnst)
{
	return(mnst->fire_immunity);
}

int _PASCAL monster_imm_to_ice(MONSTER *mnst)
{
	return(mnst->ice_immunity);
}

int _PASCAL monster_imm_to_electricity(MONSTER *mnst)
{
	return(mnst->electricity_immunity);
}

int _PASCAL monster_imm_to_mind_spells(MONSTER *mnst)
{
	return(mnst->mind_spell_immunity);
}

void _PASCAL monster_perform_death_throes(MONSTER *mnst)
{
	cmbt_display_slaughter(mnst->x,mnst->y);
}

int _PASCAL monster_is_weak(MONSTER *mnst)
{
	int average=mnst->hd*5;

	if ((mnst->current_hp<=average/3) || (mnst->current_hp==1))
		return(TRUE);
	else
		return(FALSE);
}

void _PASCAL monster_reduce_hp(MONSTER *mnst,int damage)
{
	mnst->current_hp-=damage;

	if (mnst->current_hp<=0)
		mnst->current_hp=0;
	else
		cmbt_check_monster_weak_msg(mnst);
}

void _PASCAL _NEAR cmbt_check_monster_weak_msg(MONSTER *mnst)
{
	if (!mnst->weak_msg_given && monster_is_weak(mnst))
	{
		mnst->weak_msg_given=TRUE;

		combat_write(11,mnst->humanoid?"Thy foe staggers a little!"
									  :"Thy foe art weakened!",TRUE);
		good_sound();
		cmbt_pause(1);
	}
}

int _PASCAL are_all_monsters_dead_or_flown()
{
	int i;

	if (num_monsters==0)
		return(TRUE);

	for (i=0; i<MAX_MONSTERS; i++)
		if (monster_is_alive(&the_monsters[i]) && (!the_monsters[i].flown))
			return(FALSE);

	return(TRUE);
}

int _PASCAL monster_attack_is_physical(MONSTER *mnst,int att_no)
{
	static int attacks[]={MON_CLAW, 	MON_KICK,
						  MON_WEAPON,	MON_BITE,
						  MON_TAIL_LASH,MON_STING,
						  MON_PUNCH};
	int i;

	for (i=0; i<SIZE(attacks); i++)
		if (mnst->attack_type[att_no]==attacks[i])
			return(TRUE);

	return(FALSE);
}

int _PASCAL monster_attack_is_magical(MONSTER *mnst,int att_no)
{
	return(monster_attack_is_physical(mnst,att_no)?FALSE:TRUE);
}

int _PASCAL effective_monster_saving_throw(MONSTER *mnst,PLAYER *adv,int mode)
{
	int res=(mnst->hd*8)+(mnst->agility/2);

	if (mode==WAND_MODE_SOLITARY)
		res/=2;

	if (mnst->fleeing)
		res-=15;

	if (monster_is_weak(mnst))
		res-=15;

	if (mode==NORMAL_SPELL_SAVE)
		res+=((mnst->intelligence*3)/2);

	if (adv!=(PLAYER *)NULL)
		res-=(adv->level*4);

	return(min(max(res,0),99));
}

int _PASCAL is_undead_or_demon(MONSTER *mnst)
{
	if ((mnst->bane_rune_type & TYP_UNDEAD) ||
		(mnst->bane_rune_type & TYP_DEMONIC))
		return(TRUE);
	else
		return(FALSE);
}

int _PASCAL is_an_elemental(MONSTER *mnst)
{
	return((strstr(mnst->image,"ELEM")==NULL)?FALSE:TRUE);
}
