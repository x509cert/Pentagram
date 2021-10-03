#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	End of Combat
 *
 */

void _PASCAL handle_combat_result(int result)
{
	switch(result)
	{
		case RES_PARTY_SLAIN	:  cmbt_gold_gained=cmbt_xp_gained=0L;
								   break;

		case RES_MONSTERS_SLAIN :  GX("Thy galant party hath defeated thy foe!",VICTORY);

								   break;

		case RES_MONSTERS_FLEE  :  GX("Thy foe doth flee from thee!",VICTORY);

								   break;

		case RES_PARTY_FLEE     :  GX("'Tis often quite wise to flee from demise!",BAD);
								   cmbt_gold_gained=cmbt_xp_gained=0L;

								   break;
	}
}

void _PASCAL pick_up_flasks_after_combat()
{
	int num_flasks=0;
	int i;

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (TPP[i].holywater_left)
				give_potion_to_player(&TPP[i],POT_HOLYWATER);

			if (TPP[i].oil_left)
				TPP[i].oil+=TPP[i].oil_left;

			num_flasks+=(TPP[i].holywater_left+TPP[i].oil_left);
		}
	}

	if (num_flasks)
	{
		SCROLL(1,14,"Thy party members pick up ye unbroken flasks!");
		good_sound();
	}
}

void _PASCAL display_post_combat_stats()
{
	GWINDOW win;
	char temp[60];
	char *tre="Treasure Value";
	char *exp="Experience Points";
	static int boundary[]={145,118,190,130,
							-1,-1,-1,-1};

	if (cmbt_xp_gained==0L && cmbt_gold_gained==0L)
		return;

	win.x1=8;
	win.y1=2;
	win.x2=34;
	win.y2=18;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	generic_pic_draw(70,win.y1*8-2,"CMBTEND");
	click_box(145,118,B_OK);

	_settextcolor(3);
	_settextposition(10,21-strlen_half(tre));
	_outtext(tre);

	_settextposition(13,21-strlen_half(exp));
	_outtext(exp);

	_settextcolor(11);

	sprintf(temp,"%ld GC",cmbt_gold_gained);
	_settextposition(11,21-strlen_half(temp));
	_outtext(temp);

	sprintf(temp,"%ld XP",cmbt_xp_gained);
	_settextposition(14,21-strlen_half(temp));
	_outtext(temp);

	good_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}
