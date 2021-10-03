#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	Player Effective functions in Combat
 *
 */

int _PASCAL effective_surprise(PLAYER *adv)
{
	int res=0;

	res=effective_agility(adv)   +
		effective_luck(adv)      +
		(effective_listen(adv)/2)+
		(effective_move_silently(adv)/2);

	res+=(adv->level*2);

	if (is_wearing_metal(adv) && IN_DUNGEON)
		res-=15;

	if (check_party_globals_in_effect(IN_EFFECT_LIGHT) &&
	   (IN_DUNGEON || is_night_time()) &&
		adv->nclass!=DARK_ELF)
		res-=15;

	if (good_for_dark_elf(adv)==TRUE)
		res+=10;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (check_party_globals_in_effect(IN_EFFECT_AURA_OF_PROTECTION))
		res+=15;

	if (adv->nclass==BARD)  /* Check if bard singing */
	{
		if (adv->in_effect.windsong       || adv->in_effect.wayfarers_tune ||
			adv->in_effect.alethran       || adv->in_effect.tale_of_yuldar ||
			adv->in_effect.palisors_dream || adv->in_effect.daylight_falls ||
			adv->in_effect.hunters_poem)
			res-=15;
	}

	if (adv->member_of_HOE)
		res+=10;

	if (adv->in_effect.axels_shadow || adv->in_effect.axels_shimmer)
		res+=20;
	else
	if (adv->in_effect.axels_blur)
		res+=10;

	if (player_overdue_at_praying(adv))
		res-=25;

	res+=((MAX_PARTY-P_NUM)*5);

	if (!IN_DUNGEON &&
		(adv->nclass==DRUID || adv->nclass==RANGER || adv->nclass==HUNTER))
		res+=15;

	if (res)
		res/=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(0,res),20));
}

int _PASCAL effective_player_initiative(PLAYER *adv)
{
	int res=effective_agility(adv);
	int weapon_mod=0,in_hand=FALSE;

	switch(adv->weapon_used.item)
	{
		case DAGGER 	: in_hand=TRUE; weapon_mod=1; break;
		case AXE		:
		case SHORT_SWORD:
		case RAPIER 	: in_hand=TRUE; weapon_mod=2; break;
		case LONG_SWORD :
		case MACE		: in_hand=TRUE; weapon_mod=3; break;
		case CLAYMORE	:
		case FLAIL		: in_hand=TRUE; weapon_mod=4; break;
		case HALBERD	: in_hand=TRUE; weapon_mod=5; break;

		case SLING		: in_hand=TRUE; weapon_mod=1; break;
		case BOW		: in_hand=TRUE; weapon_mod=2; break;
		case CROSSBOW	: in_hand=TRUE; weapon_mod=3; break;

		default 		: break;
	}

	if ((adv->nrace==DWARF      && adv->weapon_used.item==AXE)        ||
		(adv->nrace==HIGH_ELF	&& adv->weapon_used.item==BOW)		  ||
		(adv->nrace==HIGH_ELF	&& adv->weapon_used.item==LONG_SWORD) ||
		(adv->nrace==SYLVAN_ELF && adv->weapon_used.item==LONG_SWORD) ||
		(adv->nrace==SYLVAN_ELF && adv->weapon_used.item==BOW)        ||
		(adv->nclass==DUELIST	&& adv->weapon_used.item==RAPIER))
		weapon_mod=0;

	if (in_hand)
	{
		switch(adv->weapon_used.type)
		{
			case NO_PLUS  : break;
			case PLUS_1   : weapon_mod-=1; break;
			case PLUS_2   : weapon_mod-=2; break;
			case PLUS_3   : weapon_mod-=3; break;
			case CURSED   : weapon_mod+=3; break;
		}
	}

	res-=max(0,weapon_mod);

	if (good_for_dark_elf(adv)==TRUE)
		res++;

	if (good_for_dark_elf(adv)==FALSE)
		res--;

	if (adv->in_effect.swiftness)
		res++;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res++;

	if (player_is_weak(adv))
		res-=2;

	if (player_is_drunk(adv))
		res--;

	if (effective_luck(adv)<=10)
		res--;

	if (effective_luck(adv)>=14)
		res++;

	if (effective_luck(adv)>=17)
		res++;

	if (adv->is_stunned)
		res/=2;

	if (player_is_dead(adv))
		res=0;

	return(min(res,MAX_ABILITY));
}

int  _PASCAL effective_magic_save(PLAYER *adv,int magic_type)
{
	int res=0;
	int person;

	switch(magic_type)
	{
		case MON_FIRE       :  if (adv->in_effect.pot_fire_resist || adv->in_effect.prot_fire)
									res+=50;

							   break;

		case MON_ICE        :  if (adv->in_effect.pot_cold_resist || adv->in_effect.prot_cold)
									res+=50;

							   break;

		case MON_ELECTRICITY:  if (is_wearing_metal(adv))
									res-=33;

							   break;

		case MON_ARROW		:
		case MON_ROCK		:  res+=((effective_agility(adv)+effective_luck(adv))/2);

							   if ((person=check_party_globals_in_effect(IN_EFFECT_MISSILE_CLOAK))!=ERR)
									res+=(TPP[person].level*7);

							   break;

		case MON_MAGIC      :
		default             :  break;
	}

	if (percent()>(rand()%effective_survival(adv)))
		res+=15;

	res+=player_has_dragon_wyvern_ring(adv);

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=15;

	if (check_party_globals_in_effect(IN_EFFECT_AURA_OF_PROTECTION)!=ERR)
		res+=15;

	return(min(max(res,0),99));
}

int  _PASCAL effective_dragon_breath_save(PLAYER *adv)
{
	int res=effective_magic_save(adv,MON_FIRE)-15;

	return(max(res,0));
}

int _PASCAL effective_backstab(MONSTER *mnst,PLAYER *adv)
{
	int base=20;

	if (adv->level<=11)
		base+=(adv->level*5);
	else
		base=70;

	base+=effective_luck(adv);

	switch(adv->weapon_used.item)
	{
		case DAGGER           : switch(adv->weapon_used.type)
								{
									case NO_PLUS    :   base+=3; break;
									case PLUS_1     :   base+=6; break;
									case PLUS_2     :   base+=9; break;
									case PLUS_3     :   base+=12;break;
									case CURSED     :   base-=10;break;
								}

								break;

		case SHORT_SWORD      : switch(adv->weapon_used.type)
								{
									case NO_PLUS    :   base+=2; break;
									case PLUS_1     :   base+=4; break;
									case PLUS_2     :   base+=6; break;
									case PLUS_3     :   base+=8; break;
									case CURSED     :   base-=12;break;
								}

								break;

		case LONG_SWORD       : switch(adv->weapon_used.type)
								{
									case NO_PLUS    :   base+=1; break;
									case PLUS_1     :   base+=2; break;
									case PLUS_2     :   base+=4; break;
									case PLUS_3     :   base+=6; break;
									case CURSED     :   base-=14;break;
								}

								break;

		default               : base=0;  break;
	}

	switch(effective_strength(adv))
	{
		case 3  :
		case 4  :
		case 5  : base-=5; break;
		case 6  :
		case 7  :
		case 8  :
		case 9  :
		case 10 : base-=2; break;
		case 11 :
		case 12 :
		case 13 : break;
		case 14 :
		case 15 :
		case 16 : base+=5; break;
		case 17 : base+=10; break;
		case 18 : base+=15; break;
		case 19 : base+=20; break;
		case 20 : base+=25; break;
	}

	if (player_is_dead(adv) ||
		adv->nclass!=THIEF  ||
		!mnst->backstabbable)
		base=0;

	if ((adv->weapon_used.type==NO_PLUS ||
		 adv->weapon_used.type==CURSED) &&
		 mnst->magic_weapon_to_hit)
		 base=0;

	return(min(max(base,0),99));
}

int _PASCAL effective_player_attack(MONSTER *mnst,PLAYER *adv)
{
	int res;

	if ((adv->weapon_used.type==NO_PLUS ||
		 adv->weapon_used.type==CURSED) &&
		 mnst->magic_weapon_to_hit)
	   return(ERR); 					/* Never Hit! */

	res=(effective_attack(adv)/5)+mnst->ac;

	if (good_for_dark_elf(adv)==TRUE)
		res+=2;

	if (good_for_dark_elf(adv)==FALSE)
		res-=2;

	if (mnst->is_lethargic || mnst->spell_bound || mnst->time_suspended)
		res+=2;

	return(res);
}

int _PASCAL effective_damage(PLAYER *adv,MONSTER *mon)
{
	int res,base,add;
	int person;
	int punch=FALSE;

	switch(adv->weapon_used.item)
	{
		case DAGGER         : base=3;  break;
		case AXE            : base=5;  break;
		case MACE           : base=6;  break;
		case FLAIL          : base=8;  break;
		case SHORT_SWORD    : base=6;  break;
		case LONG_SWORD     : base=8;  break;
		case RAPIER         : base=8;  break;
		case CLAYMORE       : base=12; break;
		case HALBERD        : base=12; break;
		default             : base=2;
							  punch=TRUE;
							  break;
	}

	if (!punch)
	{
		switch(adv->weapon_used.type)
		{
			case PLUS_1     : add=1;  break;
			case PLUS_2     : add=2;  break;
			case PLUS_3     : add=3;  break;
			case CURSED     : add=-2; break;
			case NO_PLUS    :
			default         : add=0;  break;
		}
	}
	else
		add=0;

	switch(effective_strength(adv))
	{
		case 3	:
		case 4	:
		case 5	: add-=2; break;
		case 6	:
		case 7	:
		case 8	:
		case 9	:
		case 10 : add-- ; break;
		case 11 :
		case 12 :
		case 13 : break;
		case 14 :
		case 15 :
		case 16 : add++ ; break;
		case 17 : add+=2; break;
		case 18 : add+=4; break;
		case 19 : add+=5; break;
		case 20 : add+=7; break;
	}

	if (player_is_weak(adv))
		add--;

	if (adv->bane_rune!=TYP_NO_RUNES)
		if (adv->bane_rune==mon->monster_type)
			add+=(rand()%5);

	if (percent()<=effective_luck(adv))
		add++;

	res=get_dice_roll(base,1,add);

	if ((person=check_party_globals_in_effect(IN_EFFECT_PALISORS_DREAM)!=ERR))
	{
		res+=((TPP[person].level-1)/2);
		res++;
	}

	if (punch)
	{
		if (adv->in_effect.hammerhand)
			res+=get_dice_roll(6,1,adv->level);

		if (adv->nclass==MONK)
			res+=(adv->level*2);
	}

	if (good_for_dark_elf(adv)==TRUE)
		res++;

	if (player_overdue_at_praying(adv))
		res/=2;

	if (player_is_dead(adv))
		res=0;

	return(max(0,res));
}

int _PASCAL effective_missile_damage(PLAYER *adv,MONSTER *mon,int weapon)
{
	int base,res,plus=0;

	switch(weapon)
	{
		case CMBT_BOW       : base=6;  break;
		case CMBT_CROSSBOW  : base=8;  break;
		case CMBT_DART      : base=3;  break;
		case CMBT_SLING     : base=2;  break;
		case CMBT_OIL       : base=8;  break;
		case CMBT_HOLYWATER : base=10; break;
	}

	if (weapon==CMBT_BOW || weapon==CMBT_CROSSBOW)
	{
		switch(adv->weapon_used.type)
		{
			case PLUS_1 	: plus=1;  break;
			case PLUS_2 	: plus=2;  break;
			case PLUS_3 	: plus=3;  break;
			case CURSED 	: plus=-2; break;
			default 		: plus=0;  break;
		}
	}

	res=get_dice_roll(base,1,plus);

	if (weapon==CMBT_OIL)
		if (monster_imm_to_fire(mon))
			res=0;

	if (weapon==CMBT_HOLYWATER)
		res+=mon->hd;

	if (player_overdue_at_praying(adv))
		res/=2;

	if (good_for_dark_elf(adv)==TRUE)
		res++;

	if (player_is_dead(adv))
		res=0;

	return(max(res,0));
}

int _PASCAL effective_turn_undead(PLAYER *adv)
{
	int res=0;
	int cl=adv->nclass;

	if (cl!=PRIEST && cl!=CRUSADER)
		return(0);

	res=adv->level*7;

	if (cl==PRIEST)
		res+=20;

	if (cl==CRUSADER)
		res+=10;

	if (adv->in_effect.pot_undead_turn)
		res+=20;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (player_is_dead(adv))
		res=0;

	return(min(res,99));
}
