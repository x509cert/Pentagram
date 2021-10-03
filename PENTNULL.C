#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL nullify_party()
{
	memset((void *)&the_party,0,sizeof(THE_PARTY)); /* Nullify THE_PARTY */
}

void _PASCAL nullify_all_combat_spells()
{
	int i;

	for (i=0; i<=P_NUM; i++)
	{
		TPP[i].in_effect.mighty_appearance	  =
		TPP[i].in_effect.aura_protection	  =
		TPP[i].in_effect.swiftness			  =
		TPP[i].in_effect.axels_blur 		  =
		TPP[i].in_effect.axels_shimmer		  =
		TPP[i].in_effect.axels_shadow		  =
		TPP[i].in_effect.hammerhand 		  =
		TPP[i].in_effect.tangle_thorns		  =
		TPP[i].in_effect.missile_cloak		  =
		TPP[i].in_effect.trueflight 		  =
		TPP[i].in_effect.allys_dancing_dagger =
		TPP[i].in_effect.allys_dancing_mace   =
		TPP[i].in_effect.allys_dancing_sabre  =0;

		TPP[i].in_effect.allys_opponent 	  =NULL;
	}
}

void _PASCAL nullify_allys_spells(PLAYER *adv)
{
	adv->in_effect.allys_opponent=0;

	adv->in_effect.allys_dancing_dagger=
	adv->in_effect.allys_dancing_mace  =
	adv->in_effect.allys_dancing_sabre =0;
}

void _PASCAL nullify_all_in_effect_party()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		nullify_all_in_effect(&TPP[i]);
}

void _PASCAL nullify_all_in_effect(PLAYER *adv)
{
	memset((void *)&adv->in_effect,0,sizeof(IN_EFFECT));
}

void _PASCAL nullify_all_songs(PLAYER *adv)
{
	adv->in_effect.windsong       =
	adv->in_effect.wayfarers_tune =
	adv->in_effect.alethran       =
	adv->in_effect.tale_of_yuldar =
	adv->in_effect.palisors_dream =
	adv->in_effect.daylight_falls =
	adv->in_effect.hunters_poem   =FALSE;
}

void _PASCAL null_all_professionalism()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		TPP[i].professionalism=5;
}

void _PASCAL nullify_pool()
{
	int i;
	ITEM_POOL nothing;

	nothing.item     = NOTHING;
	nothing.status   = ITEM_CARRIED;
	nothing.type     = NO_PLUS;
	nothing.poisoned = FALSE;

	for (i=0; i<MAX_POOL; i++)
		pool[i]=nothing;
}

void _PASCAL nullify_combat_area()
{
	int i,j;

	for (i=0; i<CMBT_AREA_X; i++)
		for (j=0; j<CMBT_AREA_Y; j++)
			cmbt_area[i][j].nocc = IS_EMPTY;
}

void _PASCAL nullify_all_parrying_flags()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			TPP[i].is_parrying=FALSE;
}

void _PASCAL nullify_all_unbroken_flasks()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			nullify_one_unbroken_flasks(&TPP[i]);
}

void _PASCAL _NEAR nullify_one_unbroken_flasks(PLAYER *adv)
{
	adv->oil_left=adv->holywater_left=0;
}

void _PASCAL nullify_all_sneaking_flags()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			TPP[i].sneaking=FALSE;
}
