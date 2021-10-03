#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL special_misery(int lev,int passing_looking)
{
	special_misery0();
}

void _PASCAL _NEAR special_misery0()
{
	static char *poem[]={"As sly as a fox in a wood,",
						 "claws so sharp they shred,",
						 "as regal as a perfect lord,",
						 "'tis quiet as lonely dead."};
	static char *close[]={"PUSSY",
						  "TIGER",
						  "LYNX",
						  "LION",
						  "LEOPARD",
						  "PANTHER",
						  "MOGGY",
						  "CHEETAH",
						  "KITTEN"};
	char *answer="CAT";

	if (display_and_solve_riddle(poem,SIZE(poem),answer,close,SIZE(close)))
	{
		good_sound();
		set_to_corridor();
	}
	else
	{
		got_riddle_wrong(TRUE);
	}
}
