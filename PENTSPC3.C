#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL special_crypt(int lev,int passing_looking)
{
	switch(lev)
	{
		case 0 : special_crypt0(passing_looking); break;
		case 1 : special_crypt1();                break;
	}
}

void _PASCAL _NEAR special_crypt0(int pl)
{
	int i;
	int x,y;
	static int levels[]={4,4,2,4,4,3,1};
	char *title=":YE DUNGEONS OF YE REALMS:";
	static char *names[]={":LOST SOULS:",
						  ":DAMNED:",
						  ":CRYING CRYPT:",
						  ":MORT:",
						  ":HELLS:",
						  ":MORIBUND:",
						  ":MISERY:"};

	if (pl==PASSING)
		special_passing_text();
	else
	{
		special_make_gwindow();

		print_rune_string(title,48,31,6);

		for (i=0; i<MAX_DUNGEONS; i++)
		{
			switch(i)
			{
				case 0 :  x=46 ; y=59 ; break;
				case 1 :  x=191; y=59 ; break;
				case 2 :  x=46 ; y=103; break;
				case 3 :  x=191; y=103; break;
				case 4 :  x=46 ; y=147; break;
				case 5 :  x=191; y=147; break;
				case 6 :  x=120; y=147; break;
			}

			depict_dungeon_levels(x,y,levels[i]);
			print_rune_string(names[i],x,y-11,7);
		}

		special_wait();

		special_kill_gwindow();
	}
}

void _PASCAL _NEAR special_crypt1()
{
	special_found_talisman_bit();
	set_to_corridor();
}
