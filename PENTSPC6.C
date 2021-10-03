#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL special_hells(int lev,int passing_looking)
{
	switch(lev)
	{
		case 0 : special_hells0(passing_looking); break;
		case 1 : special_hells1();                break;
		case 2 : special_hells2(passing_looking); break;
		case 3 : special_hells3(passing_looking); break;
	}
}

void _PASCAL _NEAR special_hells0(int pl)
{
	if (pl==PASSING)
		special_passing_text();
	else
		read_guild_flyer(2);
}

void _PASCAL _NEAR special_hells1()
{
	int person;
	int fin=FALSE;
	char temp[100];

	SCROLL(1,14,"In ye dim dungeon light, thy party notices "
				"a curiously coloured metal box covered in dust..");
	good_sound();
	pause(3);

	while (!fin)
	{
		person=adv_select_adventurer("Who takes","ye box?",TRUE);

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
		SCROLL(1,0,"Strangely, ye metal box shatters, crumbling into a light dust!");

		bad_sound2();

		pause(2);
	}
	else
	{
		add_to_player(CURIOUS_BOX,NO_PLUS,ITEM_CARRIED,FALSE,&TPP[person]);

		sprintf(temp,"%s takes ye box and dusts it carefully, "
					 "revealing many intricate symbols!",
					 TPP[person].name);

		SCROLL(2,14,temp);

		good_sound();

		add_xp_to_party(3000L);
		add_to_professionalism(&TPP[person],2);
	}

	set_to_corridor();
}

void _PASCAL _NEAR special_hells2(int pl)
{
	char *msg1="Bundled unceremoniously in a dark dungeon corner "
			   "lies a rotting corpse.";

	char *msg2="Judging by its garb, a purple robe and soft leather boots, "
			   "ye corpse was probably once a wizard or illusionist.";

	char *msg3="His eyes, full of pain and anguish, almost wishing to say "
			   "something of importance, stare straight back at thee!";

	SCROLL(1,pl==PASSING?0:1,pl==PASSING?msg1:msg2);

	general_low_sound();

	if (pl!=PASSING)
	{
		pause(3);

		SCROLL(1,0,msg3);

		solemn_sound();
	}
}

void _PASCAL special_hells2_resurrect()
{
	GWINDOW win;
	static int boundary[]={102,164,137,176,
							-1,-1,-1,-1};

	SCROLL(1,14,"As ye resurrection spell comes to an end, thy "
				"party stand startled as life enters ye corpse "
				"after centuries of death.");

	spell_sound();
	pause(3);

	SCROLL(1,14,"A new life in its eyes gestures to thy party, and "
				"in heartless and miserable words, its cold voice murmurs...");

	general_low_sound();
	pause(3);

	win.x1=4;
	win.y1=5;
	win.x2=29;
	win.y2=24;
	win.border=4;
	win.back=0;

	make_gwindow(&win);

	click_box(102,164,B_OK);

	generic_pic_draw(win.x1*8+2,win.y1*8+2,"HELLS2");
	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	SCROLL(1,0,"As ye last stanza draws to its end, ye corpse fades "
			   "slowly away - released from this weary world!");

	general_low_sound();

	set_to_corridor();

	add_xp_to_party(2000L);
}

void _PASCAL _NEAR special_hells3(int pl)
{
	char temp[120];
	int person;
	GWINDOW win;
	int page=0;
	static int boundary[]={132,162,167,174,
							-1,-1,-1,-1};

	if (pl==PASSING)
	{
		SCROLL(1,1,"Lying on a small wooden table lies a large "
				   "crystal ball of incredible luminance!");

		general_low_sound();
	}
	else
	{
		person=adv_select_adventurer("Who looks","into ye ball?",TRUE);

		if (person==ERR)
			return;

		if (TPP[person].sex!=SX_FEMALE)
		{
			sprintf(temp,"%s sees naught as ye ball art misted over!",
						TPP[person].name);

			GX(temp,BAD);
		}
		else
		{
			sprintf(temp,"Peering into ye ball, %s sees many eerie sights!",TPP[person].name);
			SCROLL(2,14,temp);

			good_sound();
			pause(3);

			win.x1=4;
			win.y1=5;
			win.x2=36;
			win.y2=24;
			win.border=4;
			win.back=0;

			make_gwindow(&win);

			click_box(132,162,B_OK);

			while (page==0 || page==1)
			{
				_setcolor(0);
				_rectangle(_GFILLINTERIOR,34,42,276,158);

				sprintf(temp,"XTAL%d",page+1);
				generic_pic_draw(34,39,temp);

				(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

				page++;
			}

			kill_gwindow(&win);

			sprintf(temp,"Almost spellbound, %s manages "
						 "to drag %sself from ye ball..",
						 TPP[person].name,
						 TPP[person].him_her);

			SCROLL(1,1,temp);
		}
	}
}
