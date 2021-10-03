#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *  Player/Monster stun routines
 *
 */

static int _PASCAL monster_is_stunnable(MONSTER *mnst)
{
	return(mnst->stunnable);
}

int _PASCAL is_monster_stunned_from_hit(MONSTER *mnst,int damage)
{
	int stunned=FALSE;

	if (monster_is_stunnable(mnst))
		stunned=((unsigned)damage>((mnst->hd*7)/3) && percent()<=damage)?TRUE:FALSE;

	if (monster_is_dead(mnst))
		stunned=FALSE;

	return(stunned);
}

void _PASCAL actually_stun_monster(MONSTER *mnst)
{
	mnst->is_stunned=2+(percent()>75?1:0);

	combat_write(14,"Thy foe art stunned!",TRUE);
	good_sound();
}

int _PASCAL is_player_stunned_from_hit(PLAYER *adv,int damage)
{
	int stunned=(damage>(adv->hp/3) && percent()<=damage)?TRUE:FALSE;

	if (player_is_dead(adv))
		stunned=FALSE;

	return(stunned);
}

void _PASCAL actually_stun_player(PLAYER *adv)
{
	char temp[30];

	adv->is_stunned=2+(percent()>75?1:0);

	sprintf(temp,"%s art stunned!",adv->name);
	cmbt_bad_msg(temp,TRUE);
}
