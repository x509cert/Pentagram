#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

int _PASCAL player_has_dragon_wyvern_ring(PLAYER *adv)
{
	if (player_is_wearing(adv,WYVERN_RING))
		return(5);

	if (player_is_wearing(adv,DRAGON_RING))
		return(10);

	return(0);
}

int _PASCAL player_is_drunk(PLAYER *adv)
{
	return(adv->drunkeness>=adv->max_drunkeness?TRUE:FALSE);
}

int _PASCAL player_is_tipsy(PLAYER *adv)
{
	return(adv->drunkeness>=(((adv->max_drunkeness)/3)*2)?TRUE:FALSE);
}

int _PASCAL player_is_alive(PLAYER *adv)
{
	if (adv->is_dead || adv->is_dust || adv->current_hp==0)
		return(FALSE);
	else
		return(TRUE);
}

int _PASCAL player_is_weak(PLAYER *adv)
{
	if ((adv->current_hp<=adv->hp/4) || (adv->current_hp==1))
		return(TRUE);
	else
		return(FALSE);
}

int _PASCAL player_is_dead(PLAYER *adv)
{
	return(player_is_alive(adv)==TRUE?FALSE:TRUE);
}

int  _PASCAL effective_strength(PLAYER *adv)
{
	int res;

	res=adv->strength;

	if (player_is_carrying(adv,ORB_TITAN))
		res++;

	if (adv->in_effect.pot_strength)
		res++;

	if (player_is_dead(adv))
		res=0;

	return(min(res,MAX_ABILITY));
}

int  _PASCAL effective_intelligence(PLAYER *adv)
{
	int res;

	res=adv->intelligence;

	if (player_is_carrying(adv,ORB_MEDITATION))
		res++;

	if (player_is_dead(adv))
		res=0;

	return(min(res,MAX_ABILITY));
}

int  _PASCAL effective_piety(PLAYER *adv)
{
	int res;

	res=adv->piety;

	if (player_is_carrying(adv,ORB_WISE))
		res++;

	if (player_is_dead(adv))
		res=0;

	return(min(res,MAX_ABILITY));
}

int  _PASCAL effective_agility(PLAYER *adv)
{
	int res;

	res=adv->agility;

	if (player_is_carrying(adv,ORB_DEXTERITY))
		res++;

	if (player_is_carrying(adv,GLOVES_NIMBLENESS))
		res++;

	if (check_party_globals_in_effect(IN_EFFECT_WAYFARERS_TUNE)!=ERR)
		res++;

	if (player_is_drunk(adv))
		res-=2;

	if (player_is_dead(adv))
		res=0;

	return(min(res,MAX_ABILITY));
}

int  _PASCAL effective_toughness(PLAYER *adv)
{
	int res;

	res=adv->toughness;

	if (player_is_carrying(adv,ORB_STAMINA))
		res++;

	if (player_is_dead(adv))
		res=0;

	return(min(res,MAX_ABILITY));
}

int  _PASCAL effective_luck(PLAYER *adv)
{
	int res;

	res=adv->luck;

	if (player_is_carrying(adv,ORB_FORTUNE))
		res++;

	if (player_is_dead(adv))
		res=0;

	return(min(res,MAX_ABILITY));
}

int  _PASCAL effective_spell_luck(PLAYER *adv)
{
	int res=effective_luck(adv);

	if (adv->nclass==WIZARD || adv->nclass==RANGER)
		if (pent_data.moon_phase==FULL_MOON)
			res++;

	if (adv->nclass==PRIEST || adv->nclass==CRUSADER)
		if (pent_data.moon_phase==NEW_MOON)
			res++;

	if (good_for_dark_elf(adv)==TRUE)
		res++;

	if (good_for_dark_elf(adv)==FALSE)
		res--;

	if (player_overdue_at_praying(adv))
		res/=2;

	return(res);
}

int  _PASCAL effective_charisma(PLAYER *adv)
{
	int res;

	res=adv->charisma;

	if (player_is_carrying(adv,ORB_BEAUTY))
		res++;

	if (player_is_dead(adv))
		res=0;

	if (player_is_drunk(adv))
		res-=2;

	return(min(res,MAX_ABILITY));
}

int  _PASCAL effective_speed(PLAYER *adv)
{
	int res;

	res=adv->speed;

	switch(adv->armour_used.item)
	{
		case LEATHER_ARMOUR     :   switch(adv->armour_used.type)
									{
										case NO_PLUS    :   res--;  break;
										case PLUS_1     :
										case PLUS_2     :
										case PLUS_3     :           break;
										case CURSED     :   res-=2; break;
									}

									break;

		case SPLINT_ARMOUR      :
		case CHAIN_ARMOUR       :   switch(adv->armour_used.type)
									{
										case NO_PLUS    :   res-=2; break;
										case PLUS_1     :   res-=1; break;
										case PLUS_2     :
										case PLUS_3     :           break;
										case CURSED     :   res-=3; break;
									}

									break;

		case ELF_ARMOUR         :   switch(adv->armour_used.type)
									{
										case NO_PLUS    :
										case PLUS_1     :
										case PLUS_2     :
										case PLUS_3     :           break;
										case CURSED     :   res-=2; break;
									}

									break;

		case PLATE_ARMOUR       :   switch(adv->armour_used.type)
									{
										case NO_PLUS    :   res-=3; break;
										case PLUS_1     :   res-=2; break;
										case PLUS_2     :   res-=1; break;
										case PLUS_3     :           break;
										case CURSED     :   res-=4; break;
									}

									break;

		default                 :   break;
	}

	if (adv->in_effect.swiftness)
		res+=2;

	if (player_is_drunk(adv))
		res-=2;

	if (check_player_is_spell_drained(adv))
		res--;

	if (effective_agility(adv)>=17)
		res++;

	if (good_for_dark_elf(adv)==TRUE)
		res++;

	if (good_for_dark_elf(adv)==FALSE)
		res--;

	if (adv->nrace==SYLVAN_ELF && pent_data.current_feature==FOREST)
		res++;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL get_base_ac(PLAYER *adv)
{
	int ac;

	switch(adv->armour_used.item)
	{
		case LEATHER_ARMOUR : ac=8;  break;
		case SPLINT_ARMOUR  : ac=6;  break;
		case ELF_ARMOUR     : ac=6;  break;
		case CHAIN_ARMOUR   : ac=4;  break;
		case PLATE_ARMOUR   : ac=3;  break;
		default             : ac=10; break;
	}

	switch(adv->armour_used.type)
	{
		case NO_PLUS    :           break;
		case PLUS_1     :   ac--;   break;
		case PLUS_2     :   ac-=2;  break;
		case PLUS_3     :   ac-=3;  break;
		case CURSED     :   ac+=2;  break;
		default         :           break;
	}

	if (player_is_wearing(adv,HELMET))
		ac--;

	if (player_is_weak(adv))
		ac++;

	if (player_is_wearing(adv,WYVERN_RING))
		ac--;

	if (player_is_wearing(adv,DRAGON_RING))
		ac-=2;

	if (check_party_globals_in_effect(IN_EFFECT_AURA_OF_PROTECTION)!=ERR)
		ac--;

	if (check_party_globals_in_effect(IN_EFFECT_HUNTERS_POEM)!=ERR)
		ac--;

	if (adv->in_effect.axels_shadow || adv->in_effect.axels_shimmer)
		ac-=2;
	else
	if (adv->in_effect.axels_blur)
		ac--;

	if (adv->in_effect.tangle_thorns)
		ac--;

	if (check_player_is_spell_drained(adv))
		ac++;

	if (good_for_dark_elf(adv)==TRUE)
		ac--;

	if (good_for_dark_elf(adv)==FALSE)
		ac++;

	if (player_is_drunk(adv))
		ac+=2;

	return(ac);
}

int  _PASCAL effective_ac(PLAYER *adv)
{
	int ac;
	int i;
	int fin=FALSE;

	ac=get_base_ac(adv);

	switch(effective_agility(adv))
	{
		case 3  :
		case 4  :
		case 5  : ac+=2; break;
		case 6  :
		case 7  :
		case 8  :
		case 9  :
		case 10 : ac++;  break;
		case 11 :
		case 12 :
		case 13 : break;
		case 14 :
		case 15 :
		case 16 : ac--;  break;
		case 17 : ac-=2; break;
		case 18 : ac-=3; break;
	}

	if (player_is_wearing(adv,SMALL_SHIELD)  ||
		player_is_wearing(adv,MEDIUM_SHIELD) ||
		player_is_wearing(adv,LARGE_SHIELD))
		ac--;

	for (i=0; i<MAX_CARRY; i++)
	{
		switch(adv->items_carried[i].item)
		{
			case SMALL_SHIELD   :
			case MEDIUM_SHIELD  :
			case LARGE_SHIELD   :   if (adv->items_carried[i].status==ITEM_HELD)
									{
										switch(adv->items_carried[i].type)
										{
											case NO_PLUS    :           break;
											case PLUS_1     : ac--;     break;
											case PLUS_2     : ac-=2;    break;
											case PLUS_3     : ac-=3;    break;
											case CURSED     : ac+=2;    break;
										}

										fin=TRUE;
									}

									break;

			default             :   break;
		}

		if (fin)
			break;
	}

	if (player_overdue_at_praying(adv))
		ac++;

	ac=min(ac,10);
	ac=max(ac,-10);

	if (player_is_dead(adv))
		ac=10;

	return(ac);
}

int  _PASCAL effective_ac_back(PLAYER *adv)
{
	int ac=get_base_ac(adv);

	switch(effective_agility(adv))
	{
		case 3  :
		case 4  :
		case 5  : ac+=2; break;
		case 6  :
		case 7  :
		case 8  :
		case 9  :
		case 10 : ac++;  break;
		case 11 :
		case 12 :
		case 13 :
		case 14 :
		case 15 :
		case 16 :
		case 17 :
		case 18 : break;
	}

	ac=min(ac,10);
	ac=max(ac,-10);

	if (player_is_dead(adv))
		ac=10;

	return(ac);
}

int _PASCAL effective_attack(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[ATTACK];

	switch(adv->weapon_used.type)                      /* 4% per +1 */
	{
		case NO_PLUS    :          break;
		case PLUS_1     : res+=4;  break;
		case PLUS_2     : res+=8 ; break;
		case PLUS_3     : res+=12; break;
		case CURSED     : res-=12; break;
		default         :          break;
	}

	switch(effective_strength(adv))
	{
		case 3  :
		case 4  :
		case 5  : res-=10; break;
		case 6  :
		case 7  :
		case 8  :
		case 9  :
		case 10 : res-=5;  break;
		case 11 :
		case 12 :
		case 13 : break;
		case 14 :
		case 15 :
		case 16 : res+=5;  break;
		case 17 : res+=10; break;
		case 18 : res+=15; break;
		case 19 : res+=18; break;
		case 20 : res+=22; break;
	}

	if (adv->in_effect.pot_striking)
		res+=7;

	if (check_party_globals_in_effect(IN_EFFECT_TALE_OF_YULDAR)!=ERR)
		res+=10;

	if (adv->nclass==MONK)
		res++;

	if (player_is_drunk(adv))
		res-=15;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_parry(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[PARRY];

	switch(adv->weapon_used.type)                      /* 4% per +1 */
	{
		case NO_PLUS    :          break;
		case PLUS_1     : res+=4;  break;
		case PLUS_2     : res+=8;  break;
		case PLUS_3     : res+=12; break;
		case CURSED     : res-=12; break;
		default         :          break;
	}

	switch(effective_strength(adv))
	{
		case 3  :
		case 4  :
		case 5  : res-=10; break;
		case 6  :
		case 7  :
		case 8  :
		case 9  :
		case 10 : res-=5;  break;
		case 11 :
		case 12 :
		case 13 : break;
		case 14 :
		case 15 :
		case 16 : res+=5;  break;
		case 17 : res+=10; break;
		case 18 : res+=15; break;
		case 19 : res+=18; break;
		case 20 : res+=23; break;
	}

	if (player_is_drunk(adv))
		res-=15;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_missile(PLAYER *adv)
{
	int res,per;

	res=adv->secondary_attrib[MISSILE];

	switch(effective_agility(adv))
	{
		case 3  :
		case 4  :
		case 5  : res-=10; break;
		case 6  :
		case 7  :
		case 8  :
		case 9  :
		case 10 : res-=5; ; break;
		case 11 :
		case 12 :
		case 13 : break;
		case 14 :
		case 15 :
		case 16 : res+=7;  ; break;
		case 17 : res+=14  ; break;
		case 18 : res+=21  ; break;
		case 19 : res+=25  ; break;
		case 20 : res+=30  ; break;
	}

	if (player_is_weak(adv))
		res-=10;

	res+=player_has_dragon_wyvern_ring(adv);

	res+=effective_luck(adv)/2;

	if (player_is_drunk(adv))
		res-=15;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if ((per=check_party_globals_in_effect(IN_EFFECT_TRUEFLIGHT))!=ERR)
		res+=(15+TPP[per].level);

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_disarm_trap(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[DISARM_TRAP];

	res+=effective_agility(adv)/2;

	if (!player_is_carrying(adv,THIEVES_TOOLS))
		res-=25;

	if (player_is_drunk(adv))
		res-=15;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_find_trap(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[FIND_TRAP];

	if (adv->in_effect.cats_eyes)
		res+=25;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (player_is_drunk(adv))
		res-=15;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_pick_lock(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[PICK_LOCK];

	res+=effective_agility(adv)/2;

	if (player_is_drunk(adv))
		res-=15;

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (!player_is_carrying(adv,THIEVES_TOOLS))
		res=0;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_snap_thieves_tools(PLAYER *adv)
{
	int res;

	res=(effective_pick_lock(adv)/2)+
		(effective_disarm_trap(adv)/2)+
		(effective_luck(adv))+
		(adv->level*5);

	return(min(max(res,0),99));
}

int _PASCAL effective_listen(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[LISTEN];

	res+=player_has_dragon_wyvern_ring(adv);

	if (player_is_wearing(adv,HELMET))
		res-=25;

	if (adv->in_effect.sly_ears)
		res+=25;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_move_silently(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[MOVE_SILENT];

	switch(effective_agility(adv))
	{
		case 3  :
		case 4  :
		case 5  : res-=10; break;
		case 6  :
		case 7  :
		case 8  :
		case 9  :
		case 10 : res-=5 ; break;
		case 11 :
		case 12 :
		case 13 : break;
		case 14 :
		case 15 :
		case 16 : res+=5   ; break;
		case 17 : res+=10  ; break;
		case 18 : res+=15  ; break;
		case 19 : res+=20  ; break;
		case 20 : res+=25  ; break;
	}

	res+=player_has_dragon_wyvern_ring(adv);

	res+=effective_luck(adv);

	if (adv->nrace==HALFLING)
		res+=5;

	if (player_is_wearing(adv,ELFIN_CLOAK))
		res+=10;

	if (player_is_wearing(adv,ELFIN_BOOTS))
		res+=10;

	if (player_is_drunk(adv))
		res-=15;

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_disease_immunity(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[IMMUNITY_DISEASE];

	res+=effective_luck(adv)/2;
	res+=effective_toughness(adv)/2;

	if (adv->in_effect.pot_holy_water)
		res+=10;

	if (player_is_carrying(adv,PENDANT_HEALTH))
		res+=25;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_poison_immunity(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[IMMUNITY_POISON];

	res+=effective_luck(adv)/2;
	res+=effective_toughness(adv)/2;

	if (adv->in_effect.pot_holy_water)
		res+=10;

	if (adv->in_effect.poison_immunity)
		res+=33;

	if (player_is_carrying(adv,BRACERS_POISON))
		res+=25;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_heal(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[HEAL];

	res+=effective_luck(adv)/2;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_heal_rate(PLAYER *adv)	/* Heal rate per Unit (.5 Hour) of rest */
{
	int res=1;
	int eff_heal=effective_heal(adv);

	if (eff_heal>=90)
		res+=3;
	else
	if (eff_heal>=75)
		res+=2;
	else
	if (eff_heal>=50)
		res+=1;
	else
		res+=0;

	if (adv->is_diseased)
		res=0;

	if (adv->is_poisoned)
		res-=(rand()%6);

	if (adv->in_effect.pot_holy_water)
		res+=2;

	if (check_party_globals_in_effect(IN_EFFECT_DAYLIGHT_FALLS) && res>=0)
	{
		res*=3;
		res/=2;     /* x1.5 */
	}

	if (player_is_wearing(adv,RING_OF_HEALING))
		res+=((rand()%4)+1);

	if (good_for_dark_elf(adv)==TRUE)
		res++;

	if (good_for_dark_elf(adv)==FALSE)
		res--;

	if (adv->nrace==SYLVAN_ELF && pent_data.current_feature==FOREST)
		res++;

	if (check_player_is_spell_drained(adv))
		res--;

	if (player_is_dead(adv))
		res=0;

	return(res);
}

int _PASCAL effective_find_herb(PLAYER *adv)
{
	int res=effective_luck(adv)+effective_herb_lore(adv);

	if (adv->nrace==SYLVAN_ELF)
		res+=10;

	if (adv->nrace==HIGH_ELF)
		res+=8;

	if (is_night_time())
		res-=25;

	if (player_is_drunk(adv))
		res-=15;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_herb_lore(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[HERB_LORE];

	res+=effective_luck(adv)/2;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_hunt(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[HUNT];

	res+=effective_luck(adv)/2;
	res+=effective_agility(adv)/2;

	if (is_night_time() && adv->nclass!=DARK_ELF)
		res-=25;

	if (player_is_drunk(adv))
		res-=15;

	if (!player_is_carrying(adv,BOW))
		res=0;

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	res+=(effective_move_silently(adv)/10);

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_survival(PLAYER *adv)
{
	int res;

	res=adv->secondary_attrib[SURVIVAL];

	res+=effective_luck(adv)/2;

	if (player_is_carrying(adv,HEAVY_CLOAK))
		res+=10;

	if (adv->armour_used.item!=NOTHING && adv->armour_used.item!=0)
		res+=10;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (adv->nrace==SYLVAN_ELF && pent_data.current_feature==FOREST)
		res+=10;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_swim(PLAYER *adv)
{
	int res;
	int i=0;

	res=adv->secondary_attrib[SWIM];

	switch(adv->armour_used.item)
	{
		case LEATHER_ARMOUR : i-=5;  break;
		case SPLINT_ARMOUR  : i-=20; break;
		case CHAIN_ARMOUR   : i-=30; break;
		case ELF_ARMOUR     : i-=5;  break;
		case PLATE_ARMOUR   : i-=50; break;
		default             : i-=0;  break;
	}

	switch(adv->armour_used.type)
	{
		case NO_PLUS :          break;
		case PLUS_1  :   i+=5;  break;
		case PLUS_2  :   i+=10; break;
		case PLUS_3  :   i+=15; break;
		case CURSED  :   i-=25; break;
	}

	switch(effective_strength(adv))
	{
		case 3  :
		case 4  :
		case 5  : i-=10; break;
		case 6  :
		case 7  :
		case 8  :
		case 9  :
		case 10 : i-=5 ; break;
		case 11 :
		case 12 :
		case 13 : break;
		case 14 :
		case 15 :
		case 16 : i+=5;  break;
		case 17 : i+=10; break;
		case 18 : i+=20; break;
		case 19 : i+=25; break;
		case 20 : i+=30; break;
	}

	res+=effective_luck(adv)/2;

	if (player_is_wearing(adv,RING_OF_SWIMMING))
		res+=25;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (player_is_weak(adv))
		res-=25;

	if (player_is_drunk(adv))
		res-=15;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res+i,0),99));
}

int _PASCAL player_is_carrying_potion(PLAYER *adv,int potion)
{
	int i;

	for (i=0; i<MAX_CARRY; i++)
	{
		if (adv->items_carried[i].item==POTION &&
			adv->items_carried[i].type==(unsigned)potion)
			return(TRUE);
	}

	return(FALSE);
}

int _PASCAL player_is_carrying(PLAYER *adv,int item)
{
	int i;

	for (i=0; i<MAX_CARRY; i++)
		if (adv->items_carried[i].item==(unsigned)item)
			return(TRUE);

	return(FALSE);
}

int _PASCAL player_is_wearing(PLAYER *adv,int item)
{
	int i;

	for (i=0; i<MAX_CARRY; i++)
		if ((adv->items_carried[i].item==(unsigned)item) &&
			(adv->items_carried[i].status==ITEM_HELD))
			return(TRUE);

	return(FALSE);
}

int _PASCAL effective_trap_save(PLAYER *adv,int type)
{
	int res=adv->luck;

	switch(type)
	{
		case TRAP_SPEAR             : res+=adv->agility; break;
		case TRAP_ACID_SQUIRT       : res+=adv->agility; break;
		case TRAP_ARROW             : res+=adv->agility; break;
		case TRAP_POISON_ARROW      : res+=adv->agility; break;
		case TRAP_GAS               : break;
		case TRAP_PIT               : res+=adv->agility; break;
		case TRAP_SPIKED_PIT        : res+=adv->agility; break;
		case TRAP_POISON_SPIKED_PIT : res+=adv->agility; break;
		case TRAP_ROCKS             : res+=adv->agility; break;
		case TRAP_ELECTRICITY       : break;
		case TRAP_FIREBALL          : if (adv->in_effect.pot_fire_resist ||
										  adv->in_effect.prot_fire)
										  res=100;

									  break;
	}

	res+=(effective_survival(adv)/10);

	if (check_party_globals_in_effect(IN_EFFECT_AURA_OF_PROTECTION)!=ERR)
		res+=10;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (percent()>(rand()%effective_survival(adv)))
		res+=10;

	if (good_for_dark_elf(adv)==TRUE)
		res+=5;

	if (good_for_dark_elf(adv)==FALSE)
		res-=5;

	if (player_is_drunk(adv))
		res-=15;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(res,99));
}

int _PASCAL effective_open_heavy_door(PLAYER *adv)
{
	int res;

	res=(effective_strength(adv)*3)+effective_luck(adv);

	switch(adv->nrace)
	{
		case HALF_OGRE      :  res+=10; break;
		case DWARF          :  res+=8;  break;
		case GNOME          :  res+=5;  break;
		case HALFLING       :  res-=10; break;
		default             :  break;
	}

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (player_is_drunk(adv))
		res+=5;

	if (player_is_weak(adv))
		res-=20;

	if (check_player_is_spell_drained(adv))
		res-=5;

	if (player_is_dead(adv))
		res=0;

	return(min(res,99));
}

int _PASCAL effective_chance_spot_snotling(PLAYER *adv)
{
	int res=effective_luck(adv)+effective_agility(adv);

	res+=player_has_dragon_wyvern_ring(adv);

	if (player_is_wearing(adv,ELFIN_CLOAK))
		res+=10;

	if (player_is_wearing(adv,ELFIN_BOOTS))
		res+=10;

	if (check_party_globals_in_effect(IN_EFFECT_AURA_OF_PROTECTION)!=ERR)
		res+=10;

	if (check_party_globals_in_effect(IN_EFFECT_LIGHT)==ERR)
		res-=25;

	if (player_is_drunk(adv))
		res-=15;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (adv->in_effect.cats_eyes)
		res+=20;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),99));
}

int _PASCAL effective_attacks_per_round(PLAYER *adv)
{
	int num=1;
	int lv=adv->level;

	switch(adv->nclass)
	{
		case DUELIST	   :  if (lv>=4)
								num=2;

							  if (lv>=8)
								num=3;

							  if (lv>=13)
								num=4;

							  break;

		case HUNTER 	   :  if(lv>=6)
								num=2;

							  if (lv>=10)
								num=3;

							  break;

		case DRUID		   :
		case PRIEST 	   :
		case BARD		   :  if (lv>=6)
								num=2;

							  break;

		case WARRIOR	   :  if (lv>=3)
								num=2;

							  if (lv>=6)
								num=3;

							  if (lv>=9)
								num=4;

							  break;

		case MONK		   :  if (lv>=3)
								num=2;

							  if (lv>=6)
								num=3;

							  if (lv>=8)
								num=4;

							  if (lv>=10)
								num=5;

							  break;

		case THIEF		   :
		case RANGER 	   :
		case CRUSADER	   :  if (lv>=4)
								num=2;

							  if (lv>=8)
								num=3;

							  if (lv>=11)
								num=4;

							  break;

		default             : break;
	}

	if (adv->weapon_used.item==HALBERD ||
		adv->weapon_used.item==FLAIL   ||
		adv->weapon_used.item==SLING   ||
		adv->weapon_used.item==BOW     ||
		adv->weapon_used.item==CROSSBOW)
		num=1;

	if (adv->weapon_used.item==NOTHING ||
		adv->weapon_used.item==0)
		num++;

	return(min(num,5));
}

void _PASCAL player_is_drunk_so_leave(PLAYER *adv,char *where)
{
	char temp[80];

	sprintf(temp,"As %s art drunk, a guard warns %s not to enter ye %s!",
					adv->name,
					adv->him_her,
					where);

	GX(temp,BAD);

	sprintf(temp,"Begrudgingly, %s obeys ye guard and leaves!",adv->name);

	GX(temp,BAD);
}

char *get_adv_status(PLAYER *adv)
{
	if (adv->is_dust)
		return("Dust");

	if (adv->is_dead)
		return("Dead");

	if (adv->is_stunned)
		return("Stunned");

	if (check_player_is_spell_drained(adv))
		return("Spell Drained");

	if (adv->is_asleep)
		return("Asleep");

	if (player_is_drunk(adv))
		return("Drunk!");

	if (player_is_weak(adv))
		return("Weak");

	if (adv->is_poisoned && adv->is_diseased && adv->disease_symptoms_given)
		return("Poisoned & Diseased");

	if (adv->is_poisoned)
		return("Poisoned");

	if (adv->is_diseased && adv->disease_symptoms_given)
		return("Diseased");

	return("Okay");
}

int _PASCAL get_status_colour(PLAYER *adv)
{
	if (adv->is_dust || adv->is_dead)
		return(8);

	if (adv->is_stunned                    ||
		check_player_is_spell_drained(adv) ||
		adv->is_asleep                     ||
		player_is_drunk(adv)               ||
		player_is_weak(adv))
		return(12);

	if (adv->is_poisoned && adv->is_diseased && adv->disease_symptoms_given)
		return(10);

	if (adv->is_poisoned)
		return(10);

	if (adv->is_diseased && adv->disease_symptoms_given)
		return(10);

	return(3);
}

char *get_adv_status_abbr(PLAYER *adv)
{
	if (adv->is_dust)
		return("Dust");

	if (adv->is_dead)
		return("Dead");

	if (adv->is_stunned)
		return("Stun");

	if (check_player_is_spell_drained(adv))
		return("SDrn");

	if (adv->is_asleep)
		return("Slep");

	if (player_is_drunk(adv))
		return("Drnk");

	if (player_is_weak(adv))
		return("Weak");

	if (adv->is_poisoned)
		return("Pois");

	if (adv->is_diseased && adv->disease_symptoms_given)
		return("Disd");

	return("Okay");
}

int _PASCAL is_wearing_metal(PLAYER *adv)
{
	if (player_is_wearing(adv,CHAIN_ARMOUR) ||
		player_is_wearing(adv,PLATE_ARMOUR))
		return(TRUE);
	else
		return(FALSE);
}

int _PASCAL player_holding_edged_weapon(PLAYER *adv)
{
	int res;

	switch(adv->weapon_used.item)
	{
		case DAGGER       :
		case AXE          :
		case SHORT_SWORD  :
		case LONG_SWORD   :
		case RAPIER       :
		case CLAYMORE     :
		case HALBERD      : res=TRUE; break;
		default           : res=FALSE;break;
	}

	return(res);
}

void _PASCAL carry_no_more(PLAYER *player)
{
	char temp[60];

	sprintf(temp,"%s canst carry no more!",player->name);
	GX(temp,BAD);
}

int _PASCAL adv_num_herbs(PLAYER *adv)
{
	int i;
	int count=0;

	for (i=0; i<MAX_HERBS_CARRY; i++)
		if (adv->herbs_carried[i]!=HERB_NONE)
			count++;

	return(count);
}

long _PASCAL days_since_last_pray(PLAYER *adv)
{
	long ltoday,ladv;

	if (adv->nclass!=CRUSADER &&
		adv->nclass!=PRIEST   &&
		adv->nclass!=MONK)
		return((long)ERR);

	ltoday=(long)((long)pent_data.year*DAYS_PER_YEAR + (long)pent_data.date);
	ladv  =(long)((long)adv->year_last_pray*DAYS_PER_YEAR + (long)adv->day_last_pray);

	return(ltoday<=ladv?0L:ltoday-ladv);
}

int _PASCAL player_overdue_at_praying(PLAYER *adv)
{
	return((days_since_last_pray(adv)>=PRAYER_TIME_THRESHOLD)?TRUE:FALSE);
}

int _PASCAL max_points_cast_per_day(PLAYER *adv)
{
	return(adv->level*3);
}

int _PASCAL check_player_is_spell_drained(PLAYER *adv)
{
	return(adv->points_cast>=max_points_cast_per_day(adv)?TRUE:FALSE);
}

void _PASCAL player_is_spell_drained(PLAYER *adv)
{
	char temp[80];

	sprintf(temp,"%s art Spell Drained!",adv->name);

	GX(temp,SOLEMN);
}

int _PASCAL good_for_dark_elf(PLAYER *adv)
{
	if (adv->nclass!=DARK_ELF)
		return(ERR);

	if (IN_DUNGEON)
		return(TRUE);

	if (pent_data.current_feature==FOREST)
		return(TRUE);

	if (pent_data.cloud_level>=CLOUDY)
		return(TRUE);

	if (is_night_time())
		return(TRUE);

	return(FALSE);
}

int _PASCAL effective_spot_secret_door(PLAYER *adv)
{
	int res=effective_luck(adv)+effective_find_trap(adv);

	res+=player_has_dragon_wyvern_ring(adv);

	if (check_party_globals_in_effect(IN_EFFECT_LIGHT)!=ERR)
		res+=10;

	if (player_is_drunk(adv))
		res-=15;

	if (check_party_globals_in_effect(IN_EFFECT_WINDSONG)!=ERR)
		res+=10;

	if (adv->in_effect.cats_eyes)
		res+=20;

	if (adv->nrace==HIGH_ELF || adv->nrace==DARK_ELF)
		res+=10;

	if (adv->nrace==DWARF || adv->nrace==GNOME)
		res+=15;

	if (adv->nclass==THIEF)
		res+=10;

	if (player_is_dead(adv))
		res=0;

	return(min(max(res,0),85));     /* Never >85% chance */
}
