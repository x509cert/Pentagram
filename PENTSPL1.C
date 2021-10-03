#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/* Priest Spells battle magic */

int _PASCAL cast_CAUSE_LIGHT_INJURY(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_priest_cause_spells(adv,spell_name));
}

int _PASCAL cast_HOLY_SPRAY(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,1,TY_ANTI_UNDEAD,WK_NONE,8,1,adv->level*2,FALSE));
}

/************************************************************************/

int _PASCAL cast_CAUSE_SEVERE_INJURY(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_priest_cause_spells(adv,spell_name));
}

int _PASCAL cast_BLADES(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(generic_solitary_battle_magic(adv,spell_name,2,TY_ENERGY,WK_NONE,12,1,adv->level,FALSE));
}

/************************************************************************/

int _PASCAL cast_DISRUPTION(PLAYER *adv,SPELL_NAME *spell_name)
{
	int x,y;
	MONSTER *mnst;
	int base=20;

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,3))
		return(FALSE);

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
	{
		add_lost_spell_pts(adv,3);
		return(FALSE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	if (!is_undead_or_demon(mnst))
		base=0;

	spell_sound();

	if (base && adv->level>mnst->hd)
		cmbt_monster_is_slain(adv,mnst);
	else
		inflict_spell_damage(adv,
							 mnst,
							 WK_NONE,
							 TRUE,
							 base,
							 1,
							 1,
							 cmbt_missile_draw_white,
							 x,y);

	return(TRUE);
}

int _PASCAL cast_CAUSE_CRITICAL_INJURY(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_priest_cause_spells(adv,spell_name));
}

int _PASCAL cast_MISSILE_CLOAK(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;

	if (cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,3))
		{
			res=TRUE;

			adv->in_effect.missile_cloak+=adv->level;

			print_spell_description("A thin veil shrouds thy party!");
		}
	}

	return(res);
}

int _PASCAL cast_priest_cause_spells(PLAYER *adv,SPELL_NAME *spell_name)
{
	int lv;

	switch(spell_name->name)
	{
		case CAUSE_LIGHT_INJURY    : lv=1; break;
		case CAUSE_SEVERE_INJURY   : lv=2; break;
		case CAUSE_CRITICAL_INJURY : lv=3; break;
	}

	return(generic_solitary_battle_magic(adv,spell_name,lv,TY_ENERGY,WK_NONE,8,lv,adv->level,FALSE));
}
