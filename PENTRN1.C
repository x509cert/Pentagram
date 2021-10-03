#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _CDECL enter_ruin_moon_temple()	/* Seer */
{
	GWINDOW win;
	char temp[120];
	int i;
	int kicked_out;
	int fin=FALSE;
	static char *clo[]={"ORION",
						"HUNTER"};

	static char *c[]={"Muttering some enchantments",
					  "to himself, Jiax conjurs an",
					  "image of stars  floating in",
					  "mid air before ye. He says:"};

	static char *s[]={"\"Which star  shape  of  old",
					  "doth ye image represent?\""};

	if (pent_data.seer_visited && pent_data.spell_given)
	{
		GX("Ye Moon Temple doors art firmly shut!",BAD);
		return;
	}

	if (!class_in_party(PRIEST))
	{
		SCROLL(1,0,"A voice within shouts, "
				   "\"Thy party art devoid of "
				   "priests - come back with one!\"");

		kicked_out_of_moon_temple(BAD);
		return;
	}

	enter_ruin_display_msg("temple");

	scroll_wrap_write(1,"After a few seconds, thine eyes adjust "
						"to ye gloom and ye notice a dark figure sat "
						"upon a broken alter...");

	general_low_sound();
	pause(3);

	if (pent_data.seer_visited)
	{
		SCROLL(1,14,"So ye wish to try my puzzle again? Fare thee well!");
		good_sound();
	}
	else
	{
		pent_data.seer_visited=TRUE;

		SCROLL(1,1, "An elderly man, dressed in a "
					"tatty white tunic, a uniform "
					"of ye Order of Seers, speaks:");

		general_low_sound();
		pause(3);

		SCROLL(1,14,"\"Welcome adventurers, 'tis so "
					"nice to see some fresh faces, "
					"it gets quite lonely in here "
					"at times!\".");

		general_low_sound();
		pause(3);

		SCROLL(1,14,"\"Oh, my manners seem to have "
					"slipped! My name art Jiax, I "
					"once governed this temple in "
					"it's more prosperous days.\"");

		general_low_sound();
		pause(3);

		SCROLL(1,14,"\"I have a gift for thee if thou "
					"doth answer a simple question..\"");

		general_low_sound();
		pause(2);
	}

	win.x1=2;
	win.y1=1;
	win.x2=33;
	win.y2=21;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	for (i=0; i<SIZE(c); i++)
	{
		_settextposition(win.y1+1+i,win.x1+2);
		_outtext(c[i]);
	}

	_settextcolor(12);

	for (i=0; i<SIZE(s); i++)
	{
		_settextposition(win.y1+6+i,win.x1+2);
		_outtext(s[i]);
	}

	stars_draw_kayne(24,70);

	_settextcolor(4);
	_settextposition(12,17);
	_outtext("What doth ye");

	_settextposition(13,15);
	_outtext("image represent?");

	_settextcolor(2);
	_settextposition(15,16);
	_outtext("[           ]");

	short_prompt_sound();

	while (!fin)
	{
		strcpy(temp,gquery(17,15,10,2,'A',""));

		if (strlen(temp))
			fin=TRUE;
		else
			GX("Thou hast naught to lose! Take a guess!",BAD);
	}

	kill_gwindow(&win);

	strupr(temp);

	kicked_out=FALSE;

	if (strstr(temp,"KAYNE")!=NULL)
	{
		SCROLL(2,14,"\"Well done, Kayne ye Goblin Slayer art quite correct!\"");
		good_sound();

		pause(2);

		for (i=0; i<=P_NUM; i++)
		{
			if (TPP[i].nclass==PRIEST)
			{
				TPP[i].priest_spells[SPELL_OF_PASSAGE]=SPELL_LEARNED;
				pent_data.spell_given=TRUE;

				sprintf(temp,"\"As thy trophy, I give a spell named 'Spell of Passage' "
							 "to %s to help thee journey through mountains. "
							 "Use it well!",
							 TPP[i].name);

				SCROLL(1,14,temp);
				good_sound();

				pause(3);

				kicked_out_of_moon_temple(GOOD);

				break;
			}
		}
	}
	else
	{
		for (i=0; i<SIZE(clo); i++)
		{
			if (strstr(temp,clo[i])!=NULL)
			{
				SCROLL(1,0,"\"Thou art extremely close, wrong mythos!\"");
				bad_sound();

				pause(2);

				kicked_out=TRUE;
			}
		}

		if (!kicked_out)
		{
			SCROLL(1,0,"\"No I'm afraid not! Out ye go!\"");
			bad_sound();

			pause(2);

			kicked_out=TRUE;
		}

		kicked_out_of_moon_temple(BAD);
	}
}

void _PASCAL kicked_out_of_moon_temple(int status)
{
	SCROLL(2,1,"Jiax magically creates a small wind that lifts "
			   "thy party out of ye Moon Temple!");

	if (status==BAD)
		bad_sound();
	else
		good_sound();
}
