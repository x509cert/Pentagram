#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _CDECL enter_ruin_oldhelm()	/* Scrolls */
{
	int fin=FALSE;
	int num;
	char temp[100];

	enter_ruin_display_msg("castle");

	SCROLL(1,1,"After a few seconds, thine eyes adjust "
			   "to ye gloom and ye notice a mischevious looking imp "
			   "dressed in green and red, sat upon a dead body..");

	general_low_sound();
	pause(3);

	SCROLL(1,14,"\"Welcome to my ruined abode\", utters ye "
				"imp in a shrill voice. \"Pay me 20 GC and "
				"I will show thee some valuable lore\"");
	pause(3);

	while (!fin)
	{
		num=adv_select_adventurer("Who pays","ye 20 GC?",TRUE);

		if (num!=ERR)
		{
			if (TPP[num].cash<20L)
			{
				sprintf(temp,"%s hath not ye 20 GC!",TPP[num].name);
				GX(temp,BAD);
			}
			else
			{
				TPP[num].cash-=20L;
				fin=TRUE;

				sprintf(temp,"Ye imp snatches 20 GC from %s%s hands and "
							 "scampers off into ye blackness!",
							 TPP[num].name,
							 end_s(TPP[num].name));

				SCROLL(1,1,temp);

				pause(2);

				ruin_oldhelm_show();
			}
		}
		else
		{
			SCROLL(1,0,"Disgusted, ye imp runs off into ye gloom!");
			bad_sound();

			fin=TRUE;
		}
	}

	SCROLL(1,0,"Thy party scouts about Oldhelm castle but finds naught!");
}

void _PASCAL ruin_oldhelm_show()
{
	char temp[30];
	GWINDOW win;
	static int boundary[]={120,125,155,137,
							-1,-1,-1,-1};

	win.x1=8;
	win.y1=3;
	win.x2=29;
	win.y2=19;
	win.back=0;
	win.border=4;

	SCROLL(1,14,"An image of an old scroll forms before thee..");

	good_sound();

	pause(1);

	sprintf(temp,"RUIN_SC%d",rand()%4+1);

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+3,win.y1*8+1,temp);

	click_box(120,125,B_OK);

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}
