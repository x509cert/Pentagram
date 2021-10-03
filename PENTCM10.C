#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include "bkeybrd.h"
#include "bkeys.h"

/*
 *
 *	Initiate Combat
 *
 */

int _PASCAL combat(int encounter)
{
	int result;
	int hd;

#ifdef DEV

	KEYSTATUS kstat;

	(void)kbstatus(&kstat);

	if (kstat.scroll_state)
		return(RES_PARTY_FLEE);

#endif

	if (pent_data.finished || no_monsters)
		return(RES_PARTY_FLEE);

	cmbt_xp_gained=cmbt_gold_gained=0L;
	num_monsters_killed=num_adv_killed=0;
	first_round=IN_COMBAT=TRUE;
	party_is_hostile=FALSE;

	GX("An Encounter!",BAD);

	nullify_combat_area();
	nullify_all_parrying_flags();
	nullify_all_sneaking_flags();
	nullify_all_unbroken_flasks();

	hd=build_entire_combat_arena(encounter);

	encounter_sound();

	cmbt_initial_msg(encounter);

	determine_surprise();

	result=start_combat();

	handle_combat_result(result);

	if (IN_DUNGEON)
	{
		if (result!=RES_PARTY_SLAIN &&
			result!=RES_PARTY_FLEE	&&
			result!=RES_PARLEY)
		{
			set_to_corridor();
		}
	}

	kill_cmbt_images();

	page_out_cmbt_screen();

	IN_COMBAT=FALSE;

	if (result!=RES_PARTY_SLAIN &&
		result!=RES_PARTY_FLEE	&&
		result!=RES_PARLEY)
	{
		cmbt_end_msg(num_monsters_killed,num_adv_killed);
		add_xp_to_party(cmbt_xp_gained);
		combat_end_determine_treasure(hd);
		display_post_combat_stats();
		pick_up_flasks_after_combat();
	}

	nullify_all_parrying_flags();
	nullify_all_sneaking_flags();
	nullify_all_unbroken_flasks();
	nullify_all_combat_spells();

	fast_mouse=ON;

	return(result);
}

void _PASCAL cmbt_initial_msg(int encounter)
{
	char temp[140];
	char met[40];
	static char *nums[]={"A","Two","Three","Four","Five","Six","Seven","Eight"};
	static char *wand[]={"Luck art against thee..",
						 "Fate plays an ill trick on thee..",
						 "Thy luck falters..",
						 "Fortune deals a cruel blow on thee.."};

	static char *meet[]={"encountered",
						 "met",
						 "stumbled upon",
						 "happened upon"};

	if (encounter==MANGRETH_MONSTER)
	{
		cmbt_bad_msg("Thy party hath encountered Lord Mangreth!",FALSE);
		solemn_sound();
		cmbt_half_pause();

		return;
	}
	else
	if (encounter==KALDRUTHA_MONSTER)
	{
		cmbt_bad_msg("Thy party hath encountered Kaldrutha!",FALSE);
		solemn_sound();
		cmbt_half_pause();

		return;
	}
	else
	if (encounter==WANDERING_MONSTER)
	{
		combat_write(4,wand[rand()%SIZE(wand)],TRUE);
		bad_sound();
		delay(200);
	}

	sprintf(temp,"Thy party hath %s..",meet[rand()%SIZE(meet)]);
	combat_write(4,temp,FALSE);

	sprintf(met,"%s %s%s",(num_monsters==1 && isvowel((int)*the_monsters[0].name))
								?"An":nums[num_monsters-1],
						  the_monsters[0].name,
						  num_monsters>1?"s!":"!");

	combat_write(8,met,TRUE);
	solemn_sound();
}

void _PASCAL cmbt_end_msg(int m_killed,int a_killed)
{
	char *t=NULL;
	int good_bad;

	if (m_killed==0 && a_killed==0)
		return;

	if (the_monsters[0].ethics==LAWFUL)
	{
		t="Murdering lawful creatures are deemed an evil act!";
		good_bad=BAD;
	}
	else
	if (m_killed+a_killed>7)
	{
		t="It was a bloody battle indeed!";
		good_bad=BAD;
	}
	else
	if (!the_party.all_dead)
	{
		if (a_killed>=4)
		{
			t="Alas! thy party lost many good adventurers during battle!";
			good_bad=BAD;
		}
		else
		if (a_killed)
		{
			t="Perhaps thy party ought to re-consider battle tactics?!";
			good_bad=BAD;
		}
		else
		{
			switch(rand()%5)
			{
				case 0 : t="Thy tactics paid off handsomely for thee!";
							break;

				case 1 : t="More evil blood did spill during battle!";
							break;

				case 2 : t="A battle well won and well fought!";
							break;

				case 3 : t="Well fought! but do not think all victories come so easily!";
							break;

				default: t="It was a well fought battle for thy party!";
							break;
			}

			good_bad=GOOD;
		}
	}

	if (t!=(char *)NULL)
	{
		SCROLL(1,(good_bad==BAD?0:14),t);

		if (good_bad==BAD)
			bad_sound();
		else
			good_sound();

		cmbt_pause(1);
	}
}
