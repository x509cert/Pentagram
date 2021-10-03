#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _CDECL enter_ruin_castle_hilar()
{
	SCROLL(1,0,"Inadvertently, thy party trips over a wire "
			   "and in doing so hear a loud click!");

	general_low_sound();
	pause(3);

	teleport_up_sound();

	pent_data.x=146;
	pent_data.y=43;

	if (is_night_time())
		draw_night_map();
	else
		draw_first_map();

	draw_map(99);       /* 99= No Direction */

	teleport_down_sound();

	ruin_teleport_message();
}
