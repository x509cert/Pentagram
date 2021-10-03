#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _CDECL enter_ruin_moon_keep()			/* Thieves not allowed */
{
	int num_thieves=class_in_party(THIEF);
	int thieves_outside=FALSE;
	char temp[40];
	GWINDOW win;
	int i;
	static int boundary[]={128,118,163,130,
							-1,-1,-1,-1};
	static char *no_th[]={"Thy party notice ye doors art",
						  "shut tight.  Not even a giant",
						  "could open them!",
						  "",
						  "Suddenly, from within ye keep",
						  "a mighty,  magically  created",
						  "voice  booms  loudly  -  \"For",
						  "thy party to enter Moon Keep",
						  "all thieves shall remain out-",
						  "side and not venture within!\""};
	win.x1=4;
	win.y1=3;
	win.x2=35;
	win.y2=18;
	win.back=0;
	win.border=4;

	if (num_thieves)
	{
		make_gwindow(&win);

		_settextcolor(5);

		for (i=0; i<SIZE(no_th); i++)
		{
			_settextposition(win.y1+1+i,win.x1+1);
			_outtext(no_th[i]);
		}

		click_box(128,118,B_OK);

		bad_sound2();

		(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

		kill_gwindow(&win);

		sprintf(temp,"Dost thou enter without thy thie%s?",
							num_thieves==1?"f":"ves");

		thieves_outside=gget_yn(temp);

		if (!thieves_outside)
		{
			GX("Ye keep doors stay firmly shut!",BAD);
			return;
		}
	}

	actually_enter_moon_keep();

	if (thieves_outside)
		kill_thieves_at_moon_keep(num_thieves);
}

void _PASCAL actually_enter_moon_keep()
{
	enter_ruin_display_msg("keep");

	scroll_wrap_write(1,"After a few seconds, thine eyes adjust "
						"to ye gloom and ye notice many corpses "
						"scattered about ye room...!");

	general_low_sound();
	pause(3);

	SCROLL(1,0,"Thy party doth search ye keep and find naught!");

	bad_sound2();
	pause(2);
}

void _PASCAL kill_thieves_at_moon_keep(int num_thieves)
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			if (TPP[i].nclass==THIEF)
				player_has_died_set(&TPP[i]);

	GX("Upon leaving ye keep, thy party witnesses an appalling sight..",BAD);

	GX(num_thieves==1?"Thy thief lies beheaded outside ye keep doors!"
						   :"Thy thieves lie beheaded outside ye keep doors!",SOLEMN);
}
