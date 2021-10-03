#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	Player Thrust/Slash/Bludgeon options
 *
 */

static char         *attack_names[]={"First","Second","Third","Fourth","Fifth"};

int _PASCAL cmbt_thrust(PLAYER *adv)
{
	int fin=TRUE;
	int quit=FALSE;
	unsigned int x,y;
	int i;
	int ok=FALSE;
	char temp[80];
	MONSTER *mnst;

	if (bard_is_singing(adv,"thrust at a foe"))
		return(FALSE);

	switch(adv->weapon_used.item)
	{
		case DAGGER 	:
		case SHORT_SWORD:
		case LONG_SWORD :
		case RAPIER 	:
		case CLAYMORE	:
		case HALBERD	: ok=TRUE; break;
		default 		: break;
	}

	if (!ok)
	{
		if (adv->weapon_used.item==0 || adv->weapon_used.item==NOTHING)
			sprintf(temp,"%s carries no weapon!",adv->he_she);
		else
			sprintf(temp,"Ye cannot thrust with a %s!",
					 get_weapon_name(adv->weapon_used.item));

		cmbt_bad_msg(temp,TRUE);

		return(FALSE);
	}

	sprintf(temp,"%s thrusts at %s foe.",adv->he_she,adv->his_her);
	combat_write(11,temp,FALSE);

	for (i=0; i<effective_attacks_per_round(adv); i++)
	{
		x=adv->x;
		y=adv->y;

		display_hit_name(adv,i);

		select_a_foe_msg();

		cmbt_select_sq_around_player(adv->weapon_used.item==HALBERD?2:1,
									 &x,&y,TRUE,FALSE,FALSE);

		if (x==adv->x && y==adv->y)
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

			if (effective_player_attack(mnst,adv)>=get_d20())
				cmbt_player_phys_hits(adv,mnst,CMBT_THRUST);
			else
				cmbt_player_phys_misses(adv);
		}

		if (are_all_monsters_dead_or_flown() || quit)
			break;
	}

	return(fin);
}

int _PASCAL cmbt_slash(PLAYER *adv)
{
	int quit=FALSE;
	int fin=TRUE;
	int i;
	unsigned int x,y;
	int ok=FALSE;
	char temp[80];
	MONSTER *mnst;

	if (bard_is_singing(adv,"slash at an enemy"))
		return(FALSE);

	switch(adv->weapon_used.item)
	{
		case DAGGER 	 :
		case AXE		 :
		case SHORT_SWORD :
		case LONG_SWORD  :
		case RAPIER 	 :
		case CLAYMORE	 : ok=TRUE; break;
		default 		 : break;
	}

	if (!ok)
	{
		fin=FALSE;

		if (adv->weapon_used.item==0 || adv->weapon_used.item==NOTHING)
			sprintf(temp,"%s carries no weapon!",adv->he_she);
		else
			sprintf(temp,"Ye cannot slash with a %s!",
					 get_weapon_name(adv->weapon_used.item));

		cmbt_bad_msg(temp,TRUE);

		return(FALSE);
	}

	sprintf(temp,"%s slashes at %s foe.",adv->he_she,adv->his_her);
	combat_write(11,temp,FALSE);

	for (i=0; i<effective_attacks_per_round(adv); i++)
	{
		x=adv->x;
		y=adv->y;

		display_hit_name(adv,i);

		select_a_foe_msg();

		cmbt_select_sq_around_player(1,&x,&y,TRUE,FALSE,FALSE);

		if (x==adv->x && y==adv->y)
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

			if (effective_player_attack(mnst,adv)>=(get_d20()+2))
				cmbt_player_phys_hits(adv,mnst,CMBT_SLASH);
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

int _PASCAL cmbt_bludgeon(PLAYER *adv)
{
	int i;
	int fin=TRUE;
	int quit=FALSE;
	unsigned int x,y;
	int ok=FALSE;
	char temp[80];
	MONSTER *mnst;

	if (bard_is_singing(adv,"bludgeon a foe"))
		return(FALSE);

	switch(adv->weapon_used.item)
	{
		case FLAIL		 :
		case MACE		 : ok=TRUE; break;
		default 		 : break;
	}

	if (!ok)
	{
		fin=FALSE;

		if (adv->weapon_used.item==0 || adv->weapon_used.item==NOTHING)
			sprintf(temp,"%s carries no weapon!",adv->he_she);
		else
			sprintf(temp,"Ye cannot bludgeon with a %s!",
					 get_weapon_name(adv->weapon_used.item));

		cmbt_bad_msg(temp,TRUE);

		return(FALSE);
	}

	sprintf(temp,"%s bludgeons %s foe.",adv->he_she,adv->his_her);
	combat_write(11,temp,FALSE);

	for (i=0; i<effective_attacks_per_round(adv); i++)
	{
		x=adv->x;
		y=adv->y;

		display_hit_name(adv,i);

		select_a_foe_msg();

		cmbt_select_sq_around_player(1,&x,&y,TRUE,FALSE,FALSE);

		if (x==adv->x && y==adv->y)
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

			if (effective_player_attack(mnst,adv)>=get_d20())
				cmbt_player_phys_hits(adv,mnst,CMBT_BLUDGEON);
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

void _PASCAL display_hit_name(PLAYER *adv,int hit_num)
{
	char temp[50];

	if (effective_attacks_per_round(adv)<=1)
		return;

	sprintf(temp,"%s attack",attack_names[hit_num]);
	combat_write(12,temp,FALSE);
}

void _PASCAL cmbt_player_does_naught(PLAYER *adv)
{
	char temp[40];

	sprintf(temp,"%s does naught!",adv->name);
	combat_write(11,temp,TRUE);
}
