#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	Player/Monster Combat Helper functions
 *
 *
 */

int _CDECL PLAY_MONST_compare_initiative(CMBT_CELL *comb1, CMBT_CELL *comb2)
{
	int init1, init2;

	if (comb1->nocc==IS_PLAYER)
	{
		init1=effective_player_initiative(comb1->occ.player);
	}
	else
	if (comb1->nocc==IS_MONSTER)
	{
		init1=effective_monster_initiative(comb1->occ.monster);
	}

	if (comb2->nocc==IS_PLAYER)
	{
		init2=effective_player_initiative(comb2->occ.player);
	}
	else
	if (comb2->nocc==IS_MONSTER)
	{
		init2=effective_monster_initiative(comb2->occ.monster);
	}

	if (init1<init2)
		return(1);
	else
	if (init1==init2)
		return(0);
	else
		return(-1);
}

int _PASCAL PLAY_MONST_is_alive(CMBT_CELL *comb)
{
	if (comb->nocc==IS_PLAYER)
		return(player_is_alive(comb->occ.player));
	else
	if (comb->nocc==IS_MONSTER)
		return(monster_is_alive(comb->occ.monster));
	else
		return(FALSE);
}

void _PASCAL PLAY_MONST_round(CMBT_CELL *comb)
{
	if (comb->nocc==IS_PLAYER)
		cmbt_handle_options(comb->occ.player);
	else
		make_monster_decision(comb->occ.monster);
}
