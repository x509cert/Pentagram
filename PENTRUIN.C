#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bkeybrd.h>

static RUINS ruins[]=
			{
					44, 11,
					"Moon Keep, destroyed by orc invasions between 561 and 563.",
					enter_ruin_moon_keep,

					28, 67 ,
					"an ancient Moon-temple.",
					enter_ruin_moon_temple,

					167,91,
					"once noble Dreadhorn Castle.",
					enter_ruin_dreadhorn,

					94,90,
					"long abandoned Castle Hilar.",
					enter_ruin_castle_hilar,

					146,42,
					"long disused Castle Janus.",
					enter_ruin_castle_janus,

					143,134,
					"long empty Castle Latus.",
					enter_ruin_castle_latus,

					101,162,
					"an old, forsaken village named Windless Haven.",
					enter_ruin_windless_haven,

					31, 184,
					"a solemn, long disused monastery.",
					enter_ruin_monastry,

					151,190,
					"much forlorn Keep Ironlode.",
					enter_ruin_ironlode_keep,

					34, 152,
					"time battered Silverglade Keep.",
					enter_ruin_silverglade_keep,

					24,91,
					"sad and neglected Helmhilde Keep.",
					enter_ruin_helmhilde_keep,

					73,124,
					"weather worn Cragsclaw Keep.",
					enter_ruin_cragsclaw_keep,

					116,57,
					"time worn Helmgaard Keep.",
					enter_ruin_helmgaard_keep,

					170,161,
					"time worn Castle Oldhelm.",
					enter_ruin_oldhelm,

					50,104,
					"derelict Lochgrim Keep.",
					enter_ruin_lochgrim_keep,

					136,100,
					"strangly unnerving remains of Castle Nordhausen.",
					enter_ruin_nordhausen,

					79,45,
					"war-torn Escer Fortress",
					enter_ruin_escer_fortress
			};

void _PASCAL divulge_ruin_info(int x,int y)
{
	char temp[150];
	int i;
	int ruin_num=ERR;

	for (i=0; i<SIZE(ruins); i++)
		if (x==ruins[i].x && y==ruins[i].y)
			ruin_num=i;

	kbflush();

	sprintf(temp,"Thy party art standing by ye ruins of %s.",ruins[ruin_num].description);

	SCROLL(2,1,temp);

	general_low_sound();
}

void _PASCAL enter_a_ruin()
{
	GWINDOW win;
	int res,i;
	char *l1="Doth ye wish to enter";
	char *l2="   ye dark ruins?";
	static int boundary[]={120,65,155,77,
						   175,65,210,77,
						   -1,-1,-1,-1};
	static char *no_enter[]={"Good idea!",
							 "Phew!",
							 "Nice Move!"};
	win.x1=5;
	win.x2=35;
	win.y1=5;
	win.y2=12;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	draw_ruin_image(43,47);

	_settextcolor(6);
	_settextposition(6,13);
	_outtext(l1);

	_settextposition(7,13);
	_outtext(l2);

	click_box(120,65,B_YES);
	click_box(175,65,B_NO);

	switch(mouse_in_range(boundary,"YN","YQ"))
	{
		case 0 : res=TRUE;  break;
		default: res=FALSE; break;
	}

	kill_gwindow(&win);

	if (res)
	{
		IN_RUIN=TRUE;

		for (i=0; i<SIZE(ruins); i++)
		{
			if (pent_data.x==ruins[i].x && pent_data.y==ruins[i].y)
			{
				ruins[i].func();
				break;
			}
		}
	}
	else
	{
		SCROLL(1,0,no_enter[rand()%SIZE(no_enter)]);

		general_low_sound();
	}

	IN_RUIN=FALSE;
}

void _PASCAL draw_ruin_image(int x,int y)
{
	generic_pic_draw(x,y,"RUIN_IM");
}

void _PASCAL ruin_teleport_message()
{
	SCROLL(1,14,"Thy party hath been teleported!");

	good_sound();
}

void _PASCAL enter_ruin_display_msg(char *ruin)
{
	char temp[80];
	static char *t1[]={"thumping","beating","pounding"};
	static char *t2[]={"rapidly","wildly","quickly"};

	sprintf(temp,"Hearts %s %s, thy "
				 "party enters ye ruined %s.",t1[rand()%SIZE(t1)],
											  t2[rand()%SIZE(t2)],
											  ruin);

	SCROLL(2,1,temp);
	general_low_sound();

	pause(2);

	scroll_scroll();
}
