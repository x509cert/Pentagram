#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <string.h>

void _PASCAL market_spell_guild()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Wizard Spells      Lv1",
						  "Wizard Spells      Lv2",
						  "Wizard Spells      Lv3",
						  "Illusionist Spells Lv1",
						  "Illusionist Spells Lv2",
						  "Illusionist Spells Lv3",
						  "Priest Spells      Lv1",
						  "Priest Spells      Lv2",
						  "Priest Spells      Lv3",
						  "Druid Spells       Lv1",
						  "Druid Spells       Lv2",
						  "Druid Spells       Lv3",
						  "Back to ye Market"};
	int i,l=0;
	int opt;
	int fin=FALSE;
	char *t2="WIZLUSPRE123B";
	int cl=adv.nclass;
	static int boundary[]={64,24 ,244,30,
						   64,32 ,244,38,
						   64,40 ,244,46,
						   64,48 ,244,54,
						   64,56 ,244,62,
						   64,64 ,244,70,
						   64,72 ,244,78,
						   64,80 ,244,86,
						   64,88 ,244,94,
						   64,96 ,244,102,
						   64,104,244,110,
						   64,112,244,118,
						   64,120,244,126,
						   -1,-1,-1,-1};

	if (cl==WARRIOR)
	{
		GX("Warriors canst use not spells. Stick to smashing skulls!",BAD);
		return;
	}

	if (cl==THIEF)
	{
		GX("Thieves cannot use spells. Stick to pilfering!",BAD);
		return;
	}

	if (cl==DUELIST)
	{
		GX("Duelists cannot use spells. Stick by thine sword!",BAD);
		return;
	}

	if (cl==BARD)
	{
		GX("Bards cannot use spells. Stick to songs and poems!",BAD);
		return;
	}

	in_spell_section=TRUE;

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	win.x1=20-(l/2)-1;
	win.y1=3;
	win.x2=20+(l/2)+1;
	win.y2=win.y1+i+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,
					   13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		opt=mouse_in_range(boundary,t2,"WIZLUSPRE123Q");

		kill_gwindow(&win_top);

		switch(opt)
		{
			case 0 :    market_wizard_spells1();
						break;

			case 1 :    market_wizard_spells2();
						break;

			case 2 :    market_wizard_spells3();
						break;

			case 3 :    market_illusionist_spells1();
						break;

			case 4 :    market_illusionist_spells2();
						break;

			case 5 :    market_illusionist_spells3();
						break;

			case 6 :    market_priest_spells1();
						break;

			case 7 :    market_priest_spells2();
						break;

			case 8 :    market_priest_spells3();
						break;

			case 9 :    market_druid_spells1();
						break;

			case 10:    market_druid_spells2();
						break;

			case 11:    market_druid_spells3();
						break;

			default:    fin=TRUE;
						break;
		}
	}

	in_spell_section=FALSE;

	kill_gwindow(&win);
}
