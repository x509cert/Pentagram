#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include "butil.h"

static char *USE_WAND=  "use a wand";

int _PASCAL use_thunder_wand(PLAYER *adv)
{
	char temp[100];
	int res;

	if (bard_is_singing(adv,USE_WAND))
		return(FALSE);

	if (++adv->thunder_wand_used>MAX_WAND_USE)
		if (check_wand_ring_explodes(adv,THUNDER_WAND))
			return(TRUE);

	if (!IN_COMBAT)
	{
		sprintf(temp,"A small puff of grey smoke coughs from %s%s thunder wand!",
				 adv->name,
				 end_s(adv->name));

		SCROLL(1,0,temp);

		bad_sound();

		res=TRUE;
	}
	else
	{
		res=actually_use_wand(adv,THUNDER_WAND);
	}

	return(res);
}

int _PASCAL use_ice_wand(PLAYER *adv)
{
	char temp[100];
	int res;

	if (bard_is_singing(adv,USE_WAND))
		return(FALSE);

	if (++adv->ice_wand_used>MAX_WAND_USE)
		if (check_wand_ring_explodes(adv,ICE_WAND))
			return(TRUE);

	if (!IN_COMBAT)
	{
		sprintf(temp,"A small snowball plops out of %s%s ice wand!",
				  adv->name,
				  end_s(adv->name));

		SCROLL(1,0,temp);

		bad_sound();

		res=TRUE;
	}
	else
	{
		res=actually_use_wand(adv,ICE_WAND);
	}

	return(res);
}

int _PASCAL use_fire_wand(PLAYER *adv)
{
	char temp[100];
	int res;

	if (bard_is_singing(adv,USE_WAND))
		return(FALSE);

	if (++adv->fire_wand_used>MAX_WAND_USE)
		if (check_wand_ring_explodes(adv,FIRE_WAND))
			return(TRUE);

	if (!IN_COMBAT)
	{
		sprintf(temp,"%s%s wand glows red for a little, then returns to normal!",
				   adv->name,
				   end_s(adv->name));

		SCROLL(1,0,temp);

		bad_sound();

		res=TRUE;
	}
	else
	{
		res=actually_use_wand(adv,FIRE_WAND);
	}

	return(res);
}

int _PASCAL use_healing_stave(PLAYER *adv)
{
	int whom=1;
	PLAYER *on;
	int all_healed=FALSE;
	int hp_gained;
	char temp[100];
	char hpz[20];
	int same_people=FALSE;

	if (bard_is_singing(adv,USE_WAND))
		return(FALSE);

	if (IN_COMBAT)
	{
		cmbt_bad_msg("A healing stave art too slow to use in melee!",TRUE);
		return(FALSE);
	}

	whom=adv_select_adventurer("Use Healing","Stave on whom?",TRUE);

	if (whom!=ERR)
	{
		if (strcmp(adv->file_name,TPP[whom].file_name)==0)
		{
			on=adv;
			same_people=TRUE;
		}
		else
			on=&TPP[whom];

		if (++adv->stave_healing_used>MAX_WAND_USE)
			if (check_wand_ring_explodes(adv,HEALING_STAVE))
				return(TRUE);

		if (on->current_hp!=on->hp)
		{
			hp_gained=rand()%20+5;

			if (effective_heal(adv)>50)
				hp_gained+=2;

			if (effective_heal(adv)>70)
				hp_gained+=2;

			if (effective_heal(adv)>80)
				hp_gained+=3;

			on->current_hp+=hp_gained;

			if (on->current_hp>=on->hp)
			{
				all_healed=TRUE;
				on->current_hp=on->hp;
			}

			sprintf(hpz,"%d",hp_gained);

			sprintf(temp,"%s uses %s Healing Stave on %s, recuping %s hp.",
						 adv->name,
						 adv->his_her,
						 same_people?(on->sex==SX_MALE?"himself":"herself")
									:on->name,
						 all_healed?"all lost":hpz);

			SCROLL(1,14,temp);

			staff_sound();
		}
		else
		{
			sprintf(temp,"%s uses %s Healing Stave on %s, but %s art uninjured!",
						 adv->name,
						 adv->his_her,
						 same_people?(on->sex==SX_MALE?"himself":"herself")
									:on->name,
						 on->he_she);

			SCROLL(1,14,temp);
			bad_sound();
		}

		return(TRUE);
	}
	else
		return(FALSE);
}

int _PASCAL use_sustenance_wand(PLAYER *adv)
{
	char temp[100];
	int num;

	if (bard_is_singing(adv,USE_WAND))
		return(FALSE);

	if (IN_COMBAT)
	{
		cmbt_bad_msg("A Sustenance Wand cannot be used in melee!",TRUE);
		return(FALSE);
	}

	if (++adv->sustenance_wand_used>MAX_WAND_USE)
		if (check_wand_ring_explodes(adv,SUSTENANCE_WAND))
			return(TRUE);

	num=get_dice_roll(4,2,1);
	adv->food+=num;
	adv->food=min(adv->food, MAX_FOOD);

	sprintf(temp,"%s creates %d lots of food with %s wand!",
					adv->name,
					num,
					adv->his_her);

	SCROLL(1,14,temp);

	wand_sound();

	return(TRUE);
}

int _PASCAL use_rod_of_devouring(PLAYER *adv)
{
	char temp[100];
	int res;

	if (bard_is_singing(adv,USE_WAND))
		return(FALSE);

	if (++pent_data.devouring_rod_used>MAX_DEVOURING_ROD_USE)
		if (check_wand_ring_explodes(adv,DEVOURING_ROD))
			return(TRUE);

	if (!IN_COMBAT)
	{
		sprintf(temp,"A small rumbling sound issues from %s%s Devouring Rod!",
				   adv->name,
				   end_s(adv->name));

		SCROLL(1,0,temp);

		bad_sound();

		res=TRUE;
	}
	else
	{
		res=actually_use_wand(adv,DEVOURING_ROD);
	}

	return(res);
}

int _PASCAL check_wand_ring_explodes(PLAYER *adv,int item)
{
	int explodes=((unsigned)percent()>((adv->level*5)+effective_luck(adv)));
	int is_ring;
	int damage;
	int i;
	char *str_item;
	char temp[140];

	if (explodes)
	{
		if (!NO_SOUND)
		{
			for (i=0; i<200; i++)
			{
				utspkr(rand()%(780-i*3)+20);
				delay(4);
			}

			utspkr(0);
		}

		is_ring=FALSE;
		str_item="wand";

		switch(item)
		{
			case RING_OF_HEALING :
			case RING_OF_FIRE    :
			case RING_OF_ICICLES :	is_ring=TRUE;
									str_item="ring";
									break;

			case HEALING_STAVE	 :	str_item="staff";
									break;

			case DEVOURING_ROD	 :	str_item="rod";
									break;
		}

		damage=get_dice_roll(10,1,is_ring?1:8);
		damage=modified_damage(damage);

		sprintf(temp,"%s%s %s explodes!",adv->name,end_s(adv->name),str_item);

		if (!IN_COMBAT)
		{
			SCROLL(1,0,temp);
		}
		else
		{
			cmbt_hit_a_square(adv->x,adv->y);
			combat_write(4,temp,TRUE);
		}

		bad_sound();

		if (!IN_COMBAT)
		{
			sprintf(temp,"..and a blinding white ball of energy scorches %s for %d damage!",
							adv->him_her,
							damage);

			scroll_wrap_write(0,temp);
		}
		else
		{
			sprintf(temp,"..scorching %s for %d damage!",adv->him_her,damage);
			combat_write(4,temp,TRUE);
		}

		solemn_sound();

		pause(4);

		for (i=0; i<MAX_CARRY; i++)
		{
			if (adv->items_carried[i].item==(unsigned)item)
			{
				adv->items_carried[i].item=NOTHING;
				adv->items_carried[i].type=NO_PLUS;

				break;
			}
		}

		reduce_hp(adv,damage,IN_COMBAT?NO_DISPLAY:FROM_BURNT);

		if (IN_COMBAT)
		{
			if (player_is_dead(adv))
				cmbt_display_slaughter(adv->x,adv->y);
		}
	}

	return(explodes);
}
