#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	Player Punch & Backstab
 *
 */

int _PASCAL cmbt_backstab(PLAYER *adv)
{
	int fin=TRUE;
	unsigned int x,y;
	int ok=FALSE;
	char temp[80];
	MONSTER *mnst;
	int effc_silent;

	if (bard_is_singing(adv,"attempt a backstab"))
		return(FALSE);

	if (adv->nclass!=THIEF)
	{
		cmbt_bad_msg("Only thieves may backstab!",TRUE);
		return(FALSE);
	}

	switch(adv->weapon_used.item)
	{
		case DAGGER     :
		case SHORT_SWORD:
		case LONG_SWORD : ok=TRUE; break;
		default         : break;
	}

	if (!ok)
	{
		fin=FALSE;

		if (adv->weapon_used.item==0 || adv->weapon_used.item==NOTHING)
			sprintf(temp,"%s carries no weapon!",adv->he_she);
		else
			sprintf(temp,"Ye cannot backstab with a %s!",
					 get_weapon_name(adv->weapon_used.item));

		cmbt_bad_msg(temp,TRUE);

		return(FALSE);
	}

	x=adv->x;
	y=adv->y;

	sprintf(temp,"%s attempts a backstab.",adv->he_she);
	combat_write(11,temp,FALSE);

	select_a_foe_msg();

	cmbt_select_sq_around_player(1,&x,&y,TRUE,FALSE,FALSE);

	if (x==adv->x && y==adv->y)
		fin=FALSE;
	else
	{
		mnst=cmbt_area[x][y].occ.monster;

		fin=TRUE;

		effc_silent=effective_move_silently(adv);

		if (!adv->sneaking)
			effc_silent-=50;

		if (percent()>=effc_silent)
		{
			sprintf(temp,"%s art spotted, and %s backstab misses!",
						adv->name,
						adv->his_her);

			combat_write(5,temp,TRUE);

			bad_sound();

			adv->sneaking=FALSE;

			cmbt_pause(1);
		}
		else
		{
			if (percent()>=effective_backstab(mnst,adv))
			{
				cmbt_player_phys_hits(adv,mnst,CMBT_BACKSTAB);
			}
			else
			{
				cmbt_player_phys_misses(adv);
			}
		}
	}

	return(fin);
}

int _PASCAL cmbt_punch(PLAYER *adv)
{
	int x,y;
	int i;
	MONSTER *mnst;
	int fin=TRUE;
	int quit=FALSE;
	char temp[50];

	if (bard_is_singing(adv,"punch a foe"))
		return(FALSE);

	if (!(adv->weapon_used.item==0 || adv->weapon_used.item==NOTHING))
	{
		cmbt_bad_msg("Thou art holding something!",TRUE);
		return(FALSE);
	}

	sprintf(temp,"%s punches %s foe.",adv->he_she,adv->his_her);
	combat_write(11,temp,FALSE);

	for (i=0; i<effective_attacks_per_round(adv); i++)
	{
		x=adv->x;
		y=adv->y;

		display_hit_name(adv,i);

		select_a_foe_msg();

		cmbt_select_sq_around_player(1,&x,&y,TRUE,FALSE,FALSE);

		if ((unsigned)x==adv->x && (unsigned)y==adv->y)
		{
			if (!i)
			{
				quit=TRUE;
				fin=FALSE;
			}
			else
			{
				cmbt_player_does_naught(adv);
			}
		}
		else
		{
			mnst=cmbt_area[x][y].occ.monster;

			fin=TRUE;

			if (effective_player_attack(mnst,adv)>=get_d20())
				cmbt_player_phys_hits(adv,mnst,CMBT_PUNCH);
			else
				cmbt_player_phys_misses(adv);
		}

		if (are_all_monsters_dead_or_flown())
			break;

		if (quit)
			break;
	}

	return(fin);

}
