#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL want_to_poison_weapon(PLAYER *adv)
{
	GWINDOW win;
	int res;
	static int boundary[]={95, 80,130,92,
						   170,80,205,92,
							-1,-1,-1,-1};

	if (player_has_poison(adv)           &&
		player_holding_edged_weapon(adv) &&
		adv->weapon_used.poisoned==FALSE)
	{
		win.x1=5;
		win.y1=6;
		win.x2=35;
		win.y2=14;
		win.back=0;
		win.border=10;

		make_gwindow(&win);

		generic_pic_draw(win.x1*8+68,win.y1*8-2,"WEAPOIS");

		_settextcolor(2);
		_settextposition(win.y1+3,win.x1+1);
		_outtext("Dost thou poison thy weapon?");

		click_box(95, 80,B_YES);
		click_box(170,80,B_NO);

		res=mouse_in_range(boundary,"YN","YQ");

		kill_gwindow(&win);

		if (res==0)
			poison_weapon(adv);
	}
}

static void _PASCAL _NEAR poison_weapon(PLAYER *adv)
{
	remove_one_poison_vial(adv);
	put_poison_on_weapon(adv);
	check_for_poison_cut(adv);
}

static void _PASCAL _NEAR check_for_poison_cut(PLAYER *adv)
{
	int chance;
	char temp[80];

	chance=35+adv->level+
		   effective_luck(adv)/2+
		   effective_poison_immunity(adv)+
		   effective_agility(adv);

	chance=min(99,chance);

	if (percent()>chance)
	{
		adv->is_poisoned=TRUE;

		sprintf(temp,"%s cuts %sself and poison enters ye wound!",adv->name,adv->him_her);

		if (IN_COMBAT)
			combat_write(4,temp,TRUE);
		else
			SCROLL(1,0,temp);

		solemn_sound();
		pause(1);
	}
}

static void _PASCAL _NEAR put_poison_on_weapon(PLAYER *adv)
{
	int i;
	char temp[120];
	char *weapon;

	switch(adv->weapon_used.item)
	{
		case DAGGER 	  : weapon=STR_DAGGER;		 break;
		case AXE		  : weapon=STR_AXE; 		 break;
		case SHORT_SWORD  : weapon=STR_SHORT_SWORD;  break;
		case LONG_SWORD   : weapon=STR_LONG_SWORD;	 break;
		case RAPIER 	  : weapon=STR_RAPIER;		 break;
		case CLAYMORE	  : weapon=STR_CLAYMORE;	 break;
		case HALBERD	  : weapon=STR_HALBERD; 	 break;
	}

	if (IN_COMBAT)
		sprintf(temp,"Poison oozes down thy blade!");
	else
		sprintf(temp,"Ye viscous poison glistens "
					 "as it oozes slowly onto %s%s %s.",
					adv->name,
					end_s(adv->name),
					weapon);

	if (IN_COMBAT)
		combat_write(2,temp,TRUE);
	else
	{
		SCROLL(1,0,temp);
	}

	solemn_sound();

	for (i=0; i<MAX_CARRY; i++)
	{
		if (adv->items_carried[i].item==adv->weapon_used.item &&
			adv->items_carried[i].type==adv->weapon_used.type)
		{
			adv->items_carried[i].poisoned=adv->weapon_used.poisoned=get_dice_roll(2,1,0);

			if ((percent()/2)<=effective_luck(adv))
			{
				adv->items_carried[i].poisoned++;
				adv->weapon_used.poisoned++;
			}

			break;
		}
	}
}

static int _PASCAL _NEAR player_has_poison(PLAYER *adv)
{
	int i;

	for (i=0; i<MAX_CARRY; i++)
		if (adv->items_carried[i].item==POTION &&
			adv->items_carried[i].type==POT_POISON)
			return(TRUE);

	return(FALSE);
}

static void _PASCAL _NEAR remove_one_poison_vial(PLAYER *adv)
{
	int i;

	for (i=0; i<MAX_CARRY; i++)
	{
		if (adv->items_carried[i].item==POTION &&
			adv->items_carried[i].type==POT_POISON)
		{
			adv->items_carried[i].item=NOTHING;
			adv->items_carried[i].type=NO_PLUS;

			break;
		}
	}
}

int _PASCAL drop_poison_for_weapon_used(PLAYER *adv)
{
	int i;
	int still_poisoned=FALSE;

	if (!adv->weapon_used.poisoned)
		return(FALSE);

	for (i=0; i<MAX_CARRY; i++)
	{
		if (adv->weapon_used.item == adv->items_carried[i].item &&
			adv->weapon_used.type == adv->items_carried[i].type &&
			adv->items_carried[i].poisoned)
		{
			still_poisoned=TRUE;

			adv->items_carried[i].poisoned--;
			adv->weapon_used.poisoned--;

			break;
		}
	}

	return(still_poisoned);
}
