#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _CDECL enter_ruin_monastry()		/* Kaldrutha & Lord Mangreth */
{
	int res;
	char *t="A great plume of grey smoke issues "
			"forth as ye body of thy foe putrifies before thee..";

	enter_ruin_display_msg("monastry");

	if (pent_data.kaldrutha_defeated && pent_data.mangreth_defeated)
	{
		SCROLL(1,14,"Thy quest art done here, ye monastery lies at peace!");

		good_sound();
		pause(1);

		return;
	}

	if (!pent_data.mangreth_defeated)
	{
		res=combat(MANGRETH_MONSTER);

		if (res!=RES_PARTY_SLAIN && res!=RES_PARTY_FLEE)
		{
			pent_data.mangreth_defeated=TRUE;

			SCROLL(2,14,t);
			good_sound();
		}
	}
	else
	if (pent_data.mangreth_defeated && !is_all_party_dead())
	{
		res=combat(KALDRUTHA_MONSTER);

		if (res!=RES_PARTY_SLAIN && res!=RES_PARTY_FLEE)
		{
			pent_data.kaldrutha_defeated=TRUE;

			SCROLL(2,14,t);
			good_sound();
		}
	}

	if (!is_all_party_dead())
	{
		SCROLL(1,14,"Thy party leave ye monastery quite exhausted!");
		bad_sound();
		pause(1);

		if (pent_data.kaldrutha_defeated && pent_data.mangreth_defeated)
			ruin_monastry_cleansed();
	}
}

static void _PASCAL _NEAR ruin_monastry_cleansed()
{
	GWINDOW win;
	static int boundary[]={143,112,178,124,-1,-1,-1,-1};

	win.x1=4;
	win.y1=2;
	win.x2=37;
	win.y2=18;
	win.back=0;
	win.border=1;

	make_gwindow(&win);

	generic_pic_draw(win.x1*8,win.y1*8,"KALKILL");

	good_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}
