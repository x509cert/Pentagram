#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bkeybrd.h>

void _PASCAL draw_main_screen(int quick_load)
{
	if (!quick_load)
		EGA_origin(0,200,40);

	generic_pic_draw(0,117,"SCROLL");
	generic_pic_draw(0,0,"TOP");

	if (!quick_load)
	{
		generic_pic_draw(70,25,"MIDDLE");

		FFpent_pan();

		kbflush();

		pause(2);

		Fscroll_shield();
	}
	
	cls();
}
