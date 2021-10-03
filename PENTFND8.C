#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *  Determine Wandering Monsters Chance
 *
 */

void _PASCAL check_wandering_monsters()
{
	int chance=(IN_DUNGEON?55:20);

	if (check_party_globals_in_effect(IN_EFFECT_MIRAGE)!=ERR)
		chance/=3;

	if ((rand()%1050)<chance)
		if (!party_next_to(TOWN)			 &&
			pent_data.current_feature!=SEA	 &&
			pent_data.current_feature!=WATER)
			combat(WANDERING_MONSTER);
}
