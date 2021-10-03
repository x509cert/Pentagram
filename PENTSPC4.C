#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL special_mort(int lev,int passing_looking)
{
	switch(lev)
	{
		case 0 :  special_mort0(passing_looking); break;
		case 1 :  special_mort1();                break;
		case 2 :  special_mort2(passing_looking); break;
		case 3 :  special_mort3();                break;
	}
}

void _PASCAL _NEAR special_mort0(int pl)
{
	int person;
	int i;
	static char *t[]={"Beautifully carved",
					  "writing etched into",
					  "ye dank dungeon wall!",
					  "",
					  "Ye inscription stinks",
					  "of ooze and slime!"};

	if (pl==PASSING)
		special_passing_text();
	else
	{
		person=adv_select_adventurer("Who reads","ye writing?",TRUE);

		if (person==ERR)
		{
			general_low_sound();
			return;
		}

		special_make_gwindow();

		_settextcolor(4);

		for (i=0; i<SIZE(t); i++)
		{
			_settextposition(6+i,19-strlen_half(t[i]));
			_outtext(t[i]);
		}

		generic_pic_draw(60,100,"MORT_CRS");

		special_wait();
		special_kill_gwindow();

		curse_a_player(&TPP[person]);
	}
}

void _PASCAL _NEAR special_mort1()
{
	static char *poem[]={"To darkest pit it bring'th light,",
						 "to frail body it bring'th might,",
						 "to evil beast it bring'th pain,",
						 "to driest land it bring'th rain."};
	static char *close[]={"WIZARD",
						  "PRIEST",
						  "SPELL",
						  "SPELLS",
						  "SORCERY"};
	char *answer="MAGIC";

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

void _PASCAL _NEAR special_mort2(int pl)
{
	if (pl==PASSING)
		special_passing_text();
	else
		read_guild_flyer(1);
}

void _PASCAL _NEAR special_mort3()
{
	special_found_talisman_bit();
	set_to_corridor();
}
