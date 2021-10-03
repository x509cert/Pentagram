#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _CDECL enter_ruin_ironlode_keep()
{
	display_keep_runes("RUINWRT1");
}

void _CDECL enter_ruin_silverglade_keep()
{
	display_keep_runes("RUINWRT2");
}

void _CDECL enter_ruin_helmhilde_keep()
{
	display_keep_runes("RUINWRT3");
}

void _CDECL enter_ruin_helmgaard_keep()
{
	display_keep_runes("RUINWRT4");
}

void _CDECL enter_ruin_cragsclaw_keep()
{
	display_keep_runes("RUINWRT5");
}

void _CDECL enter_ruin_lochgrim_keep()
{
	display_keep_runes("RUINWRT6");
}

void _CDECL enter_ruin_escer_fortress()
{
	int i;
	int can_read=ERR;
	char temp[80];
	GWINDOW win;
	static int boundary[]={133,94,166,106,
							-1,-1,-1,-1};

	win.x1=3;
	win.y1=3;
	win.x2=37;
	win.y2=15;
	win.back=0;
	win.border=4;

	SCROLL(1,14,"Searching among ye ruins thou dost find "
				"some writing hurridly scribbled on a fallen rampart.");
	general_low_sound();
	pause(1);

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+7,win.y1*8+4,"RUINWRT7");

	click_box(133,94,B_OK);

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	for (i=0; i<=P_NUM; i++)
		if (TPP[i].languages & LAN_UNDERWURLDE)
			can_read=i;

	if (can_read==ERR)
	{
		SCROLL(1,0,"No members of thy party can read ye script!");
		bad_sound();
	}
	else
	{
		sprintf(temp,"%s reads ye script and mutters..",TPP[can_read].name);
		SCROLL(1,14,temp);
		good_sound();
		pause(1);

		SCROLL(1,1,"\"'tis written in ye tongue of ye underwurlde.\"");
		general_low_sound();
		pause(1);

		SCROLL(1,14,"\"It reads - 'Talisman ... Lost Souls, "
					"Crying Crypt, Mort, Moribund.\"");

		general_low_sound();
	}
}

void _CDECL enter_ruin_nordhausen()
{
	int res;

	enter_ruin_display_msg("castle");

	if (!pent_data.finished)
	{
		res=combat(WANDERING_MONSTER);

		if (res!=RES_PARTY_SLAIN && res!=RES_PARTY_FLEE)
		{
			SCROLL(1,14,"Thy party choose to leave ye castle!");
			good_sound();
		}
	}
	else
	{
		SCROLL(1,0,"Thy party search ye ruins, but find naught and leave!");
		bad_sound();
	}
}

void _PASCAL display_keep_runes(char *filename)
{
	GWINDOW win;
	static int boundary[]={133,94,166,106,
							-1,-1,-1,-1};

	win.x1=3;
	win.y1=3;
	win.x2=37;
	win.y2=15;
	win.back=0;
	win.border=4;

	SCROLL(1,14,"Thy party search among ye ruins for some time..");
	general_low_sound();
	pause(1);

	SCROLL(1,14,"Smeared on a broken wall art some writing.");
	general_low_sound();
	pause(1);

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+7,win.y1*8+4,filename);

	click_box(133,94,B_OK);

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	SCROLL(1,0,"Alas! continuing thy search finds naught else!");

	bad_sound();
}
