#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bkeybrd.h>

void _PASCAL check_if_game_finished()
{
	if (!pent_data.finished)
	{
		if (pent_data.talisman_1_found  &&
			pent_data.talisman_2_found  &&
			pent_data.talisman_3_found  &&
			pent_data.talisman_4_found  &&
			pent_data.kaldrutha_defeated)
		{
			pent_data.finished=TRUE;
			game_finished();
		}
	}
}

void _PASCAL game_finished()
{
	static int boundary[]={130,135,182,153,
							-1,-1,-1,-1};

	save_game(FALSE);

	melt_EGA_pages(5,0,63);

	game_finished_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kbflush();
	_setvideomode(_TEXTC80);
	default_cursor();

	exit(0);
}
