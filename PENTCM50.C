#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	Actual combat
 *
 */

int _PASCAL start_combat()
{
	int i,finish,result;
	PLAYER *adv;
	MONSTER *mnst;

	finish=FALSE;

	do
	{
		determine_battle_order();

		next_round_sound();

		Fscroll_combat(21);

		generic_pic_draw(215,170,first_round?"FIRSTRND":"NEXTRND");

		Fscroll_combat(11);
		draw_full_chain();

		if (surprise_nstring!=SURPRISE_MONSTERS || !first_round)
			result=get_next_round_option();
		else
			result=RES_NO_ACTION;

		if (result==RES_PARTY_FLEE	   ||
			result==RES_MONSTERS_SLAIN ||
			result==RES_PARTY_SLAIN    ||
			result==RES_MONSTERS_FLEE  ||
			result==RES_PARLEY)
			  finish=TRUE;

		if (!finish)
		{
			for (i=0; i<MAX_MONSTERS+MAX_PARTY && !finish; i++)
			{
				if (PLAY_MONST_is_alive(&battle_order[i]))
				{
					PLAY_MONST_round(&battle_order[i]);

					if (are_all_monsters_dead_or_flown())
					{
						result=RES_MONSTERS_SLAIN;
						finish=TRUE;
					}
					else
					if (is_all_party_dead())
					{
						result=RES_PARTY_SLAIN;
						finish=TRUE;
					}

					switch(battle_order[i].nocc)
					{
						case IS_PLAYER  : adv=battle_order[i].occ.player;

										  if (adv->is_stunned)
											adv->is_stunned--;

										  break;

						case IS_MONSTER : mnst=battle_order[i].occ.monster;

										  if (mnst->is_stunned)
											mnst->is_stunned--;

										  break;
					}
				}
			}

			update_combat_in_effects();
		}

		first_round=FALSE;

	} while (!finish);

	return(result);
}
