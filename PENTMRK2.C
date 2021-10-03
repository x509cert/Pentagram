#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL market_general_store()
{
	GWINDOW win, win_top;
	int num;
	static char *t[]    ={"Hessian Sack      (1)",
						  "Leather Backpack  (4)",
						  "Tinder-box       (10)",
						  "Heavy Cloak       (2)",
						  "Hooded Lantern   (10)",
						  "Thieves Tools    (55)",
						  "Bard's Lute      (95)",
						  "Religious Symbol (40)",
						  "Food              (1)",
						  "Oil Pots          (5)",
						  "Sextant          (95)",
						  "Insurance     (15000)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="HLTEOIBRFPSNY";
	int fin=FALSE;
	static int boundary[]={72,24 ,230, 30,
						   72,32 ,230, 38,
						   72,40 ,230, 46,
						   72,48 ,230, 54,
						   72,56 ,230, 62,
						   72,64 ,230, 70,
						   72,72 ,230, 78,
						   72,80 ,230, 86,
						   72,88 ,230, 94,
						   72,96 ,230,102,
						   72,104,230,110,
						   72,112,230,118,
						   72,120,230,126,
						   -1,-1,-1,-1};

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	--l;

	win.x1=20-(l/2)-1;
	win.y1=3;
	win.x2=20+(l/2)+2;
	win.y2=win.y1+i+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,"HLTEOIBRFPMNQ"))
		{
			case 0 :	add_to_adv_carry_money_thanks(&adv,1L,SACK,NO_PLUS);
						break;

			case 1 :	add_to_adv_carry_money_thanks(&adv,4L,BACK_PACK,NO_PLUS);
						break;

			case 2 :	add_to_adv_carry_money_thanks(&adv,10L,TINDER_BOX,NO_PLUS);
						break;

			case 3 :	add_to_adv_carry_money_thanks(&adv,2L,HEAVY_CLOAK,NO_PLUS);
						break;

			case 4 :	add_to_adv_carry_money_thanks(&adv,10L,HOODED_LANTERN,NO_PLUS);
						break;

			case 5 :	add_to_adv_carry_money_thanks(&adv,55L,THIEVES_TOOLS,NO_PLUS);
						break;

			case 6 :	add_to_adv_carry_money_thanks(&adv,95L,LUTE,NO_PLUS);
						break;

			case 7 :	add_to_adv_carry_money_thanks(&adv,40L,RELIGIOUS_SYMBOL,NO_PLUS);
						break;

			case 8 :    if ((num=market_get_quantity("Food",adv.food,MAX_FOOD))>0)
						{
							if (got_enough_money_for_misc((long)1L*num,&adv))
							{
								adv.food+=num;
								thank_you();
							}
						}

						break;

			case 9 :    if ((num=market_get_quantity("Oil Pots",adv.oil,MAX_OIL))>0)
						{
							if (got_enough_money_for_misc((long)5L*num,&adv))
							{
								adv.oil+=num;
								thank_you();
							}
						}

						break;

			case 10:	add_to_adv_carry_money_thanks(&adv,95L,SEXTANT,NO_PLUS);
						break;

			case 11:    if (got_enough_money_for_misc(15000L,&adv))
						{
							if (adv.insurance)
							{
								GX("Ye art already insured!",BAD);
							}
							else
							{
								adv.insurance=TRUE;
								thank_you();
							}
						}

						break;

			case 12:    fin=TRUE;
						break;

			default:    break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_magic_shoppe()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Magic Rings  ",
						  "Personal Orbs",
						  "Potions      ",
						  "Staves and Wands",
						  "Miscellaneous",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="RPOSMB";
	int fin=FALSE;
	static int boundary[]={80,48 ,220, 54,
						   80,56 ,220, 62,
						   80,64 ,220, 70,
						   80,72 ,220, 78,
						   80,80 ,220, 86,
						   80,88 ,220, 94,
						   -1,-1,-1,-1};

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	win.x1=20-(l/2)-1;
	win.y1=6;
	win.x2=20+(l/2)+2;
	win.y2=win.y1+i+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,"RPOSMQ"))
		{
			case 0 : market_magic_shoppe_rings();   break;
			case 1 : market_magic_shoppe_orbs();    break;
			case 2 : market_magic_shoppe_potions(); break;
			case 3 : market_magic_shoppe_wands();   break;
			case 4 : market_magic_shoppe_misc();    break;
			case 5 : fin=TRUE;                      break;
			default: break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}


void _PASCAL _NEAR market_magic_shoppe_rings()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Wyvern Ring (+1)    (5000)",
						  "Dragon Ring (+2)   (10000)",
						  "Ring of Healing     (5000)",
						  "Mindshield Ring     (4000)",
						  "Ring of Fire        (6000)",
						  "Ring of Icicles     (6000)",
						  "Ring of Swimming    (3000)",
						  "Warmth Ring         (3000)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="WDHMFISAB";
	int fin=FALSE;
	static int boundary[]={48,48 ,254, 54,
						   48,56 ,254, 62,
						   48,64 ,254, 70,
						   48,72 ,254, 78,
						   48,80 ,254, 86,
						   48,88 ,254, 94,
						   48,96 ,254,102,
						   48,104,254,110,
						   48,112,254,118,
						   -1,-1,-1,-1};

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	win.x1=20-(l/2)-1;
	win.y1=6;
	win.x2=20+(l/2)+2;
	win.y2=win.y1+i+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,"WDHMFISAQ"))
		{
			case 0 :	add_to_adv_carry_money_thanks(&adv,5000L,WYVERN_RING,NO_PLUS);
						break;

			case 1 :	add_to_adv_carry_money_thanks(&adv,10000L,DRAGON_RING,NO_PLUS);
						break;

			case 2 :	add_to_adv_carry_money_thanks(&adv,5000L,RING_OF_HEALING,NO_PLUS);
						break;

			case 3 :	add_to_adv_carry_money_thanks(&adv,4000L,MIND_SHIELD_RING,NO_PLUS);
						break;

			case 4 :	add_to_adv_carry_money_thanks(&adv,6000L,RING_OF_FIRE,NO_PLUS);
						break;

			case 5 :	add_to_adv_carry_money_thanks(&adv,6000L,RING_OF_ICICLES,NO_PLUS);
						break;

			case 6 :	add_to_adv_carry_money_thanks(&adv,3000L,RING_OF_SWIMMING,NO_PLUS);
						break;

			case 7 :	add_to_adv_carry_money_thanks(&adv,3000L,WARMTH_RING,NO_PLUS);
						break;

			case 8 :    fin=TRUE;
						break;

			default: break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL _NEAR market_magic_shoppe_orbs()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Orb of ye Titans  (9500)",
						  "Orb of Dexterity  (9500)",
						  "Orb of ye Wise    (9500)",
						  "Orb of Fortune    (9500)",
						  "Orb of Meditation (9500)",
						  "Orb of Stamina    (9500)",
						  "Orb of Beauty     (9500)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="TDWFMSBA";
	int fin=FALSE;
	static int boundary[]={56,48 ,246, 54,
						   56,56 ,246, 62,
						   56,64 ,246, 70,
						   56,72 ,246, 78,
						   56,80 ,246, 86,
						   56,88 ,246, 94,
						   56,96 ,246,102,
						   56,104,246,110,
						   -1,-1,-1,-1};

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	win.x1=20-(l/2)-1;
	win.y1=6;
	win.x2=20+(l/2)+2;
	win.y2=win.y1+i+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,"TDWAMSBQ"))
		{
			case 0 :	add_to_adv_carry_money_thanks(&adv,9500L,ORB_TITAN,NO_PLUS);
						break;

			case 1 :	add_to_adv_carry_money_thanks(&adv,9500L,ORB_DEXTERITY,NO_PLUS);
						break;

			case 2 :	add_to_adv_carry_money_thanks(&adv,9500L,ORB_WISE,NO_PLUS);
						break;

			case 3 :	add_to_adv_carry_money_thanks(&adv,9500L,ORB_FORTUNE,NO_PLUS);
						break;

			case 4 :	add_to_adv_carry_money_thanks(&adv,9500L,ORB_MEDITATION,NO_PLUS);
						break;

			case 5 :	add_to_adv_carry_money_thanks(&adv,9500L,ORB_STAMINA,NO_PLUS);
						break;

			case 6 :	add_to_adv_carry_money_thanks(&adv,9500L,ORB_BEAUTY,NO_PLUS);
						break;

			case 7 :    fin=TRUE;
						break;

			default: break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL _NEAR market_magic_shoppe_potions()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Potion of Reviving (80)",
						  "Potion of Healing  (75)",
						  "Holy Water         (75)",
						  "Poison            (500)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="RHWPB";
	char *t1="RHWPQ";
	int fin=FALSE;
	static int boundary[]={64,48 ,244, 54,
						   64,56 ,244, 62,
						   64,64 ,244, 70,
						   64,72 ,244, 78,
						   64,80 ,244, 86,
						   -1,-1,-1,-1};

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	win.x1=20-(l/2)-1;
	win.y1=6;
	win.x2=20+(l/2)+2;
	win.y2=win.y1+i+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t1))
		{
			case 0 :	add_to_adv_carry_money_thanks(&adv,80L,POTION,POT_REVIVING);
						break;

			case 1 :	add_to_adv_carry_money_thanks(&adv,75L,POTION,POT_HEALING);
						break;

			case 2 :    if (adv.ethics!=LAWFUL)
							GX("Only Lawful adventurers can use Holy Water!",BAD);
						else
							add_to_adv_carry_money_thanks(&adv,75L,POTION,POT_HOLYWATER);

						break;

			case 3 :    if (adv.ethics==LAWFUL)
							GX("Lawful adventurers cannot use poison!",BAD);
						else
							add_to_adv_carry_money_thanks(&adv,500L,POTION,POT_POISON);
						break;

			case 4 :    fin=TRUE;
						break;

			default:    break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL _NEAR market_magic_shoppe_wands()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Wand of Thunder      (9900)",
						  "Wand of Ice          (8500)",
						  "Wand of Fire         (8500)",
						  "Healing Stave        (9500)",
						  "Sustenance Wand      (6000)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="TIFSWB";
	int fin=FALSE;
	static int boundary[]={40,48 ,260, 54,
						   40,56 ,260, 62,
						   40,64 ,260, 70,
						   40,72 ,260, 78,
						   40,80 ,260, 86,
						   40,88 ,260, 94,
						   -1,-1,-1,-1};

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	win.x1=20-(l/2)-1;
	win.y1=6;
	win.x2=20+(l/2)+2;
	win.y2=win.y1+i+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,"TIFSWQ"))
		{
			case 0 :	add_to_adv_carry_money_thanks(&adv,9900L,THUNDER_WAND,NO_PLUS);
						break;

			case 1 :	add_to_adv_carry_money_thanks(&adv,8500L,ICE_WAND,NO_PLUS);
						break;

			case 2 :	add_to_adv_carry_money_thanks(&adv,8500L,FIRE_WAND,NO_PLUS);
						break;

			case 3 :	add_to_adv_carry_money_thanks(&adv,9500L,HEALING_STAVE,NO_PLUS);
						break;

			case 4 :	add_to_adv_carry_money_thanks(&adv,6000L,SUSTENANCE_WAND,NO_PLUS);
						break;

			case 5 :    fin=TRUE;
						break;

			default:    break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL _NEAR market_magic_shoppe_misc()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Ancient Relic    (10000)",
						  "Ancient Tome     (10000)",
						  "Elven Cloak       (6000)",
						  "Elven Boots       (6000)",
						  "Bracers of Poison (5000)",
						  "Pendant of Health (5000)",
						  "Gl. of Nimbleness (6000)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="RTCBPHGM";
	int fin=FALSE;
	static int boundary[]={56,40 ,246, 46,
						   56,48 ,246, 54,
						   56,56 ,246, 62,
						   56,64 ,246, 70,
						   56,72 ,246, 78,
						   56,80 ,246, 86,
						   56,88 ,246, 94,
						   56,96 ,246, 102,
						   -1,-1,-1,-1};

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	win.x1=20-(l/2)-1;
	win.y1=5;
	win.x2=20+(l/2)+2;
	win.y2=win.y1+i+2;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,"RTCBPHGQ"))
		{
			case 0 :	add_to_adv_carry_money_thanks(&adv,10000L,RELIC,NO_PLUS);
						break;

			case 1 :	add_to_adv_carry_money_thanks(&adv,10000L,TOME,NO_PLUS);
						break;

			case 2 :	add_to_adv_carry_money_thanks(&adv,6000L,ELFIN_CLOAK,NO_PLUS);
						break;

			case 3 :	add_to_adv_carry_money_thanks(&adv,6000L,ELFIN_BOOTS,NO_PLUS);
						break;

			case 4 :	add_to_adv_carry_money_thanks(&adv,5000L,BRACERS_POISON,NO_PLUS);
						break;

			case 5 :	add_to_adv_carry_money_thanks(&adv,5000L,PENDANT_HEALTH,NO_PLUS);
						break;

			case 6 :	add_to_adv_carry_money_thanks(&adv,6000L,GLOVES_NIMBLENESS,NO_PLUS);
						break;

			case 7 :    fin=TRUE;
						break;

			default:    break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}
