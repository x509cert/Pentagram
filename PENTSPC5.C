#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL special_moribund(int lev,int passing_looking)
{
	switch(lev)
	{
		case 0 :  special_moribund0(); break;
		case 1 :  special_moribund1(); break;
		case 2 :  special_moribund2(); break;
	}
}

void _PASCAL _NEAR special_moribund0()
{
	static char *poem[]={ "Delightfully white in Winter,",
						  "Crystal clear in Spring,",
						  "Carves through ancient rock,",
						  "Life to all it brings."};
	static char *close[]={"RAIN","LIQUID","MOISTURE","SNOW",
						  "ICE", "RIVER", "SEA",     "LAKE"};
	char *answer="WATER";

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

void _PASCAL _NEAR special_moribund1()
{
	int person;
	int fin=FALSE;
	char temp[120];

	SCROLL(2,14,"Thy leader notices a leather bound book covered in webs and dust!");
	good_sound();
	pause(2);
		
	while (!fin)
	{
		person=adv_select_adventurer("Who takes","ye book?",TRUE);

		if (person!=ERR)
		{
			if (number_of_items(&TPP[person])>=MAX_CARRY)
				carry_no_more(&TPP[person]);
			else
				fin=TRUE;
		}
		else
			fin=TRUE;
	}

	if (person==ERR)
	{
		SCROLL(1,0,"Strangely, ye book crumbles before thine eyes!");

		bad_sound2();

		pause(2);
	}
	else
	{
		add_to_player(GRIMOIRE,NO_PLUS,ITEM_CARRIED,FALSE,&TPP[person]);

		sprintf(temp,"%s lifts ye grimoire and notices many blank pages. "
					 "Some, however, are written with a spidery hand!",
					 TPP[person].name);

		SCROLL(2,14,temp);

		good_sound();

		add_xp_to_party(4000L);
		add_to_professionalism(&TPP[person],2);
	}

	set_to_corridor();
}

void _PASCAL _NEAR special_moribund2()
{
	special_found_talisman_bit();
	set_to_corridor();
}
