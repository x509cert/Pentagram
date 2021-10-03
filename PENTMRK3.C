#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <string.h>

void _PASCAL market_armourer()
{
	GWINDOW win, win_top;
	unsigned long to_pay;
	static char *t[]=    {"Leather Armour  (5)",
						  "Splint Armour  (70)",
						  "Chain Armour   (90)",
						  "Plate Armour  (800)",
						  "Elven Armour (2500)",
						  "Metal Helm     (15)",
						  "Small Shield   (10)",
						  "Medium Shield  (25)",
						  "Large Shield   (60)",
						  "Back to ye Market"};
	char *t2="LSCPEMADRB";
	int i,l=0;
	int fin=FALSE;
	int cl=adv.nclass;
	int pl;
	static int boundary[]={80,40 ,228, 46,
						   80,48 ,228, 54,
						   80,56 ,228, 62,
						   80,64 ,228, 70,
						   80,72 ,228, 78,
						   80,80 ,228, 86,
						   80,88 ,228, 94,
						   80,96 ,228,102,
						   80,104,228,110,
						   80,112,228,118,
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
					   win.x1+1,win.y1+1,
					   5,
					   13);

	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,"LSCPEMADRQ"))
		{
			case 0 :    if (cl==WIZARD || cl==ILLUSIONIST || cl==MONK)
							class_cannot_use(cl,STR_LEATHER_ARMOUR);
						else
						{
							pl=market_get_item_plus(5,STR_LEATHER_ARMOUR,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,LEATHER_ARMOUR,pl);
						}

						break;

			case 1 :    if (cl!=WARRIOR && cl!=PRIEST && cl!=RANGER && cl!=CRUSADER)
							class_cannot_use(cl,STR_SPLINT_ARMOUR);
						else
						{
							pl=market_get_item_plus(70,STR_SPLINT_ARMOUR,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,SPLINT_ARMOUR,pl);
						}

						break;

			case 2 :    if (cl!=WARRIOR && cl!=PRIEST && cl!=RANGER && cl!=CRUSADER)
							class_cannot_use(cl,STR_CHAIN_ARMOUR);
						else
						{
							pl=market_get_item_plus(90,STR_CHAIN_ARMOUR,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,CHAIN_ARMOUR,pl);
						}

						break;

			case 3 :    if (cl!=WARRIOR && cl!=CRUSADER)
							class_cannot_use(cl,STR_PLATE_ARMOUR);
						else
						{
							pl=market_get_item_plus(800,STR_PLATE_ARMOUR,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,PLATE_ARMOUR,pl);
						}

						break;

			case 4 :    if (cl==WIZARD || cl==ILLUSIONIST || cl==MONK)
							class_cannot_use(cl,STR_ELF_ARMOUR);
						else
						{
							pl=market_get_item_plus(2500,STR_ELF_ARMOUR,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,ELF_ARMOUR,pl);
						}

						break;

			case 5 :    if (cl==WIZARD || cl==ILLUSIONIST || cl==MONK ||
							cl==THIEF || cl==HUNTER || cl==DRUID || cl==DUELIST)
							class_cannot_use(cl,"a Metal Helm");
						else
						{
							pl=market_get_item_plus(15,STR_HELMET,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,HELMET,pl);
						}

						break;

			case 6 :    if (cl==WIZARD || cl==DRUID || cl==THIEF ||
							cl==ILLUSIONIST || cl==MONK || cl==DUELIST)
							class_cannot_use(cl," a Small Shield");
						else
						{
							pl=market_get_item_plus(10,STR_SMALL_SHIELD,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,SMALL_SHIELD,pl);
						}

						break;

			case 7 :    if (cl==WIZARD || cl==DRUID || cl==THIEF ||
							cl==ILLUSIONIST || cl==MONK || cl==BARD || cl==DUELIST)
							class_cannot_use(cl,"a Medium Shield");
						else
						{
							pl=market_get_item_plus(25,STR_MEDIUM_SHIELD,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,MEDIUM_SHIELD,pl);
						}

						break;

			case 8 :    if (cl!=WARRIOR && cl!=CRUSADER)
							class_cannot_use(cl,"a Large Shield");
						else
						{
							pl=market_get_item_plus(60,STR_LARGE_SHIELD,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,LARGE_SHIELD,pl);
						}

						break;

			case 9 :    fin=TRUE;
						break;

			default:    break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_black_smith()
{
	GWINDOW win, win_top;
	unsigned long to_pay;
	static char *t[]    ={"Dagger          (10)",
						  "Battle Axe      (15)",
						  "Short Sword     (20)",
						  "Long Sword      (50)",
						  "Rapier          (90)",
						  "Claymore       (150)",
						  "Footman's Mace  (15)",
						  "Footman's Flail (40)",
						  "Long Bow        (20)",
						  "Crossbow       (200)",
						  "Halberd        (300)",
						  "Darts            (1)",
						  "Arrows           (1)",
						  "Quarrels         (5)",
						  "Sling            (5)",
						  "Back to ye Market"};

	char *t2="DBSLRCMFOWHTAUIK";
	char *t3="DBSLRCMFOWHTAUIQ";
	int i,l=0;
	int fin=FALSE;
	int cl=adv.nclass;
	int ra=adv.nrace;
	int pl;
	int num;
	static int boundary[]={72,24 ,228,30,
						   72,32 ,228,38,
						   72,40 ,228,46,
						   72,48 ,228,54,
						   72,56 ,228,62,
						   72,64 ,228,70,
						   72,72 ,228,78,
						   72,80 ,228,86,
						   72,88 ,228,94,
						   72,96 ,228,102,
						   72,104,228,110,
						   72,112,228,118,
						   72,120,228,126,
						   72,128,228,134,
						   72,136,228,142,
						   72,144,228,150,
						   -1,-1,-1,-1};

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
					   win.x1+1,win.y1+1,
					   5,
					   13);
	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 :    if (cl==PRIEST)
							class_cannot_use(cl,"a Dagger");
						else
						{
							pl=market_get_item_plus(10,STR_DAGGER,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,DAGGER,pl);
						}

						break;

			case 1 :    if (cl==BARD || cl==WIZARD || cl==PRIEST || cl==DUELIST ||
							cl==DRUID || cl==MONK || cl==ILLUSIONIST)
							class_cannot_use(cl,"a Battle Axe");
						else
						{
							pl=market_get_item_plus(15,STR_AXE,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,AXE,pl);
						}

						break;

			case 2 :    if (cl==WIZARD || cl==PRIEST ||
							cl==MONK || cl==ILLUSIONIST)
							class_cannot_use(cl,"a Short Sword");
						else
						{
							pl=market_get_item_plus(20,STR_SHORT_SWORD,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,SHORT_SWORD,pl);
						}

						break;


			case 3 :    if (cl==WIZARD || cl==PRIEST ||
							cl==DRUID  || cl==MONK   || cl==ILLUSIONIST)
							class_cannot_use(cl,"a Long Sword");
						else
						{
							pl=market_get_item_plus(50,STR_LONG_SWORD,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,LONG_SWORD,pl);
						}

						break;

			case 4 :    if (cl==WIZARD || cl==PRIEST ||
							cl==DRUID  || cl==MONK || cl==ILLUSIONIST)
							class_cannot_use(cl,"a Rapier");
						else
						{
							pl=market_get_item_plus(90,STR_RAPIER,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,RAPIER,pl);
						}

						break;

			case 5 :    if (cl!=WARRIOR && cl!=RANGER && cl!=CRUSADER && cl!=HUNTER)
							class_cannot_use(cl,"a Claymore");
						else
						if (ra==GNOME || ra==HALFLING || ra==DWARF)
							race_cannot_use(ra,STR_CLAYMORE);
						else
						if (adv.strength<15)
							too_weak_to_use(adv.name,"a Claymore");
						else
						{
							pl=market_get_item_plus(150,STR_CLAYMORE,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,CLAYMORE,pl);
						}

						break;

			case 6 :    if (cl!=WARRIOR && cl!=RANGER && cl!=CRUSADER &&
							cl!=PRIEST && cl!=BARD)
							class_cannot_use(cl,"a Footman's Mace");
						else
						{
							pl=market_get_item_plus(15,STR_MACE,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,MACE,pl);
						}

						break;

			case 7 :    if (cl!=WARRIOR && cl!=RANGER && cl!=CRUSADER && cl!=PRIEST)
							class_cannot_use(cl,"a Footman's Flail");
						else
						if (ra==GNOME || ra==HALFLING || ra==DWARF)
							race_cannot_use(ra,STR_FLAIL);
						else
						{
							pl=market_get_item_plus(40,STR_FLAIL,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,FLAIL,pl);
						}

						break;

			case 8 :    if (cl==WIZARD || cl==PRIEST || cl==DRUID ||
							cl==MONK || cl==ILLUSIONIST || cl==DUELIST)
							class_cannot_use(cl,"a Long Bow");
						else
						{
							pl=market_get_item_plus(20,STR_BOW,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,BOW,pl);
						}

						break;

			case 9 :    if (cl==BARD  || cl==WIZARD || cl==PRIEST ||
							cl==DRUID || cl==MONK   || cl==ILLUSIONIST || cl==DUELIST)
							class_cannot_use(cl,"a Crossbow");
						else
						if (ra==GNOME || ra==HALFLING)
							race_cannot_use(ra,STR_CROSSBOW);
						else
						if (adv.strength<15)
							too_weak_to_use(adv.name,"a Crossbow");
						else
						{
							pl=market_get_item_plus(200,STR_CROSSBOW,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,CROSSBOW,pl);
						}

						break;

			case 10:    if (cl!=WARRIOR && cl!=CRUSADER)
							class_cannot_use(cl,"a Halberd");
						else
						if (ra==GNOME || ra==HALFLING || ra==DWARF)
							race_cannot_use(ra,STR_HALBERD);
						else
						if (adv.strength<16)
							too_weak_to_use(adv.name,"a Halberd");
						else
						{
							pl=market_get_item_plus(300,STR_HALBERD,&to_pay);

							if (pl!=4)
								add_to_adv_carry_money_thanks(&adv,to_pay,HALBERD,pl);
						}

						break;

			case 11:    if ((num=market_get_quantity(STR_DARTS,adv.darts,MAX_DARTS))>0)
						{
							if (got_enough_money_for_misc((long)num,&adv))
							{
								adv.darts+=num;
								thank_you();
							}
						}

						break;

			case 12:    if (cl==WIZARD || cl==PRIEST || cl==DRUID ||
							cl==MONK   || cl==ILLUSIONIST)
							class_cannot_use(cl,STR_ARROWS);
						else
						if ((num=market_get_quantity(STR_ARROWS,adv.arrows,MAX_ARROWS))>0)
						{
							if (got_enough_money_for_misc((long)num,&adv))
							{
								adv.arrows+=num;
								thank_you();
							}
						}

						break;

			case 13:    if (cl==BARD  || cl==WIZARD || cl==PRIEST ||
							cl==DRUID || cl==MONK   || cl==ILLUSIONIST)
							class_cannot_use(cl,STR_QUARRELS);
						else
						if ((num=market_get_quantity(STR_QUARRELS,adv.quarrels,MAX_QUARRELS))>0)
						{
							if (got_enough_money_for_misc((long)5L*num,&adv))
							{
								adv.quarrels+=num;
								thank_you();
							}
						}

						break;

			case 14:	add_to_adv_carry_money_thanks(&adv,5L,SLING,NO_PLUS);
						break;

			case 15:    fin=TRUE;
						break;

			default:    break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}
