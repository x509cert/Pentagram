#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <bkeybrd.h>
#include <bkeys.h>

void _PASCAL oops_here_comes_the_boss()
{
	int dummy;

	move_EGA_pages(0,4);
	move_EGA_pages(3,0);

	kbflush();

	while ((kbgetkey(&dummy)!=KB_C_A_B) || dummy!=KB_S_A_B)
		;

	good_sound();

	move_EGA_pages(4,0);
}

void _PASCAL build_boss_screen()
{
	_setactivepage(3);
	_settextcolor(7);

	_settextposition(1,1);
	_outtext("C:\\DOS>_");

	_setactivepage(0);
}
