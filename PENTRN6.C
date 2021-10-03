#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _CDECL enter_ruin_castle_janus()
{
	SCROLL(1,0,"Upon entering ye castle gate, thy party step on a "
			   "squeeky board, and in doing so hear a loud click!");

	general_low_sound();
	pause(3);

	teleport_up_sound();

	pent_data.x=144;
	pent_data.y=134;

	if (is_night_time())
		draw_night_map();
	else
		draw_first_map();

	draw_map(99);       /* 99= No Direction */

	teleport_down_sound();

	ruin_teleport_message();
}
