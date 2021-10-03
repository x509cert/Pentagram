#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 * Morale Checking
 *
 *
 */

void _PASCAL morale_increase(MONSTER *mnst,int inc)
{
	if (mnst->morale_affected)
		mnst->current_morale=min(mnst->current_morale+inc,MORALE_MAX);
}

void _PASCAL morale_decrease(MONSTER *mnst,int dec)
{
	if (mnst->morale_affected)
		mnst->current_morale=max(mnst->current_morale-dec,MORALE_MIN);
}

void _PASCAL morale_all_increase(int inc)
{
    int i;

    for (i=0; i<MAX_MONSTERS; i++)
		if (monster_is_alive(&the_monsters[i]))
			morale_increase(&the_monsters[i],inc);
}

void _PASCAL morale_all_decrease(int dec)
{
    int i;

    for (i=0; i<MAX_MONSTERS; i++)
		if (monster_is_alive(&the_monsters[i]))
			morale_decrease(&the_monsters[i],dec);
}

int _PASCAL effective_morale(MONSTER *mnst)
{
	int mor=mnst->current_morale-((monster_is_weak(mnst)?5:0));

	if (num_monsters<=1 && mnst->humanoid)
		mor--;

	return(mor);
}

void _PASCAL morale_check(MONSTER *mnst)
{
	if (!mnst->morale_affected)
		return;

	if (effective_morale(mnst)<=MORALE_LOWER_THRESHOLD)
		mnst->fleeing=TRUE;
	else
		mnst->fleeing=FALSE;
}

void _PASCAL morale_one_monster_at_start(MONSTER *mnst,int diff)
{
	if (mnst->morale_affected)
	{
		if (percent()>50)
			diff+=plus_or_minus_one();

		mnst->current_morale+=diff;
	}
}

void _PASCAL morale_all_at_start()
{
	int i;
	int mlevel,plevel;
	int diff;

	if (!the_monsters[0].morale_affected)
		return;

	mlevel=plevel=0;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			plevel+=TPP[i].level;

	mlevel=num_monsters*the_monsters[0].hd;

	diff=mlevel-plevel;
	diff=min(6,diff);
	diff=max(-3,diff);

    for (i=0; i<MAX_MONSTERS; i++)
		if (monster_is_alive(&the_monsters[i]))
			morale_one_monster_at_start(&the_monsters[i],diff);
}
