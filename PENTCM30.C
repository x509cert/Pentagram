#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

/*
 *
 *  Combat Initiative & Surprise
 *
 */

void _PASCAL determine_surprise()
{
	int mo,pl,pl1,pl2;

	pl1=effective_surprise(&TPP[0]);
	pl2=effective_surprise(&TPP[1]);
	pl=max(pl1,pl2);

	mo=effective_monster_surprise(&the_monsters[0]);

	pl+=get_dice_roll(6,1,-3);
	mo+=get_dice_roll(6,1,-3);

	if (pl<=SURPRISE_LOW_THRESHOLD && mo<=SURPRISE_LOW_THRESHOLD)
	{
		surprise_mod=0;
		surprise_nstring=SURPRISE_BOTH;
	}
	else
	if (abs(pl-mo)<=2)
	{
		surprise_mod=0;
		surprise_nstring=SURPRISE_NEITHER;
	}
	else
	if (pl>mo)
	{
		surprise_mod=-SURPRISE_MOD;
		surprise_nstring=SURPRISE_PARTY;
		combat_write(14,"Thy party surprises thy foe!",TRUE);

		good_sound();
		cmbt_half_pause();
	}
	else
	{
		surprise_mod=SURPRISE_MOD;
		surprise_nstring=SURPRISE_MONSTERS;
		combat_write(12,"Thy party art surprised by thy foe!",TRUE);

		bad_sound();
		cmbt_half_pause();
	}
}

int _PASCAL determine_battle_order()
{
	int all_dead=TRUE;
	int num_in_battle=0;
	int i;

	num_monsters=0;

	memset((void *)&battle_order[0],0,sizeof(battle_order));

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			battle_order[num_in_battle].occ.player=&TPP[i];
			battle_order[num_in_battle].nocc=IS_PLAYER;

			num_in_battle++;

			all_dead=FALSE;
		}
	}

	for (i=0; i<MAX_MONSTERS; i++)
	{
		if (monster_is_alive(&the_monsters[i]))
		{
			battle_order[num_in_battle].occ.monster=&the_monsters[i];
			battle_order[num_in_battle].nocc=IS_MONSTER;

			num_in_battle++;
			num_monsters++;

			all_dead=FALSE;
		}
	}

	determine_battle_order_sort(num_in_battle);

	return(all_dead);
}

void _PASCAL determine_battle_order_sort(int num_in_battle)
{
	qsort((void *)&battle_order[0],
		  (size_t)num_in_battle,
		  sizeof(CMBT_CELL),
		  PLAY_MONST_compare_initiative);
}
