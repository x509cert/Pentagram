#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL special_lostsoul(int lev,int passing_looking)
{
	switch(lev)
	{
		case 0 :  special_lostsoul0(passing_looking); break;
		case 1 :  special_lostsoul1(passing_looking); break;
		case 2 :  special_lostsoul2();                break;
	}
}

void _PASCAL _NEAR special_lostsoul0(int pl)
{
	if (pl==PASSING)
		special_passing_text();
	else
	{
		special_make_gwindow();

		stars_draw_gellen(50,9);
		stars_draw_incuus(155,117);
		stars_draw_line(46,110);

		print_rune_string("Gellen",148,50,6);
		print_rune_string("Ye Sword",138,60,6);
		print_rune_string("Incuus",68,128,6);
		print_rune_string("Ye Dwarven",56,138,6);
		print_rune_string("Anvil",74,148,6);

		special_wait();
		special_kill_gwindow();
	}
}

void _PASCAL _NEAR special_lostsoul1(int pl)
{
	if (pl==PASSING)
		special_passing_text();
	else
	{
		special_make_gwindow();

		stars_draw_kayne(40,20);
		stars_draw_glamhelm(130,102);
		stars_draw_line(46,110);

		print_rune_string("Kayne",166,50,6);
		print_rune_string("Ye Goblin Slayer",122,60,6);
		print_rune_string("Glahmelm",60,138,6);
		print_rune_string("Axe of Kayne",46,148,6);

		special_wait();
		special_kill_gwindow();
	}
}

void _PASCAL _NEAR special_lostsoul2()
{
	special_found_talisman_bit();
	set_to_corridor();
}
