#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <bstrings.h>

void _PASCAL special_damned(int lev,int passing_looking)
{
	switch(lev)
	{
		case 0 : special_damned0(passing_looking); break;
		case 1 : special_damned1();                break;
		case 2 : special_damned2();                break;
		case 3 : special_damned3();                break;
	}
}

void _PASCAL _NEAR special_damned0(int pl)
{
	int i,p;
	char *lies="Here lieth ye";
	char *body="mortal remains of";
	char *died="Passed away on";
	char *aged="aged %d years";
	char *rest="May %s bones rest in peace.";
	static char *lines[]={"  :AS I AM NOW:",
						  ":SO YOU SHALL BE:",
						  ":PREPARE THY SOUL:",
						  "  :TO FOLLOW ME:"};
	char temp[100];

	if (pl==PASSING)
		special_passing_text();
	else
	{
		special_make_gwindow();

		p=get_random_live_person();

		_settextcolor(6);

		_settextposition(6,20-strlen_half(lies));
		_outtext(lies);

		_settextposition(7,20-strlen_half(body));
		_outtext(body);

		sprintf(temp,"%s of %s",TPP[p].name,TPP[p].where_born);
		_settextcolor(14);
		_settextposition(9,20-strlen_half(temp));
		_outtext(temp);

		_settextcolor(6);

		strcpy(pent_data.st_date,give_date(pent_data.date));

		_settextposition(11,20-strlen_half(died));
		_outtext(died);

		_settextposition(12,20-strlen_half(pent_data.st_date));
		_outtext(pent_data.st_date);

		sprintf(temp,aged,TPP[p].nage);
		_settextposition(13,20-strlen_half(temp));
		_outtext(temp);

		sprintf(temp,rest,TPP[p].his_her);
		_settextposition(15,20-strlen_half(temp));
		_outtext(temp);

		for (i=0; i<4; i++)
			print_rune_string(lines[i],85,127+9*i,12);

		special_wait();
		special_kill_gwindow();

		sprintf(temp,"Such morbid \"dungeon humour\" leaves %s feeling quite grieved!",
					TPP[p].name);

		SCROLL(1,0,temp);

		solemn_sound();
	}
}

void _PASCAL _NEAR special_damned2()
{
	static char *poem[]={"Swing so fast and sway so slow,",
						 "deep deep down I must go,",
						 "beasts I greet from all around,",
						 "bold and noble I stand my ground."};
	static char *close[]={"OAK",
						  "WILLOW",
						  "WOOD",
						  "ELM"};
	char *answer="TREE";

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

void _PASCAL _NEAR special_damned1()
{
	static char *poem[]={"Pure in hues and tall as hill,",
						 "ye daylit sky it may fill,",
						 "to see such beauty once again,",
						 "ye must wait for fallen rain."};
	char *answer="RAINBOW";
	static char *close[]={"RAIN",
						  "WATER",
						  "CLOUD",
						  "SUN"};

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

void _PASCAL _NEAR special_damned3()
{
	if (determine_last_guild_visit()>=14)
	{
		if (!pent_data.visited_guild)
		{
			first_visit_to_guild();
			pent_data.visited_guild=TRUE;
		}
		else
		{
			more_visits_to_guild();
		}
	}
	else
	{
		visit_guild_too_early();
	}
}
