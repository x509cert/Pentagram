#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <memory.h>

void _PASCAL check_fall_down_steps()
{
	int person;

	person=get_random_live_person();

	if (person==ERR)
		return;

	if (effective_fall_down_steps(&TPP[person])<percent())
		fall_down_steps(&TPP[person]);
}

int _PASCAL effective_fall_down_steps(PLAYER *adv)
{
	int chance=20                           +
			   effective_agility(adv)       +
			   effective_luck(adv)          +
			   adv->level                   +
			   effective_speed(adv)         +
			   (effective_survival(adv)/2)  +
			   (effective_move_silently(adv)/2);

	if (check_party_globals_in_effect(IN_EFFECT_LIGHT)==ERR)
		chance-=15;

	return(percent()>=95?99:chance);
}

void _PASCAL fall_down_steps(PLAYER *adv)
{
	int potion=FALSE;
	int which_potion;
	ITEM_POOL *item;
	char *weap;
	char temp[120];
	int i,damage;
	static char *slip[]={"a banana skin",
						 "a bone",
						 "some slime",
						 "some fungi"};

	if (modified_average_level()==1)
		return;

	sprintf(temp,"Whilst walking down ye dungeon steps, "
				 "%s slips on %s and falls!",
				 adv->name,
				 slip[rand()%SIZE(slip)]);

	SCROLL(2,0,temp);
	bad_sound();
	pause(2);

	if (adv->weapon_used.item!=0 && adv->weapon_used.item!=NOTHING)
	{
		item=&adv->weapon_used;

		for (i=0; i<MAX_CARRY; i++)
		{
			if (memcmp(item,&adv->items_carried[i],sizeof(ITEM_POOL))==0)
			{
				weap=get_weapon_name(adv->items_carried[i].item);

				sprintf(temp,"In doing so %s snaps %s %s!",
							adv->he_she,adv->his_her,weap);

				SCROLL(1,0,temp);
				bad_sound();
				solemn_sound();
				pause(2);

				adv->weapon_used.item=adv->items_carried[i].item    =NOTHING;
				adv->weapon_used.type=adv->items_carried[i].type    =NO_PLUS;
				adv->weapon_used.status=adv->items_carried[i].status=ITEM_CARRIED;

				break;
			}
		}
	}
	else
	{
		for (i=0; i<MAX_CARRY; i++)
		{
			if (adv->items_carried[i].item==POTION)
			{
				potion=TRUE;
				which_potion=i;

				break;
			}
		}

		if (potion)
		{

			sprintf(temp,"smashing a vial of %s potion!",
				potion_get_colour(adv->items_carried[which_potion].type,
								 FALSE));

			SCROLL(1,0,temp);
			bad_sound();
			solemn_sound();
			pause(2);

			potion_remove_from_player(adv,
									  adv->items_carried[which_potion].type);
		}
		else
		{
			damage=modified_damage(get_dice_roll(6,1,0));

			sprintf(temp,"Thy tumble inflicts %d damage!",damage);

			SCROLL(1,0,temp);

			bad_sound();

			reduce_hp(adv,damage,FROM_FELL);
		}
	}
}
