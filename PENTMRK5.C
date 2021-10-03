#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <string.h>

void _PASCAL market_wizard_spells1()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Dragonflame I     (1000)",
						  "Arc Lightning  I  (1000)",
						  "Find Hidden Door   (800)",
						  "Gravmur's Rage    (1200)",
						  "Frozen Wind I     (1000)",
						  "Mighty Appearance  (900)",
						  "Hammerhand        (1000)",
						  "Fire Mist         (1000)",
						  "Back to ye Market"};
	int i,l=0;
	int fin=FALSE;
	char *t2="DAFGWMHRB";
	char *t3="ªªªªªªªªQ";
	int cl=adv.nclass;
	static int boundary[]={56,24 ,246,30,
						   56,32 ,246,38,
						   56,40 ,246,46,
						   56,48 ,246,54,
						   56,56 ,246,62,
						   56,64 ,246,70,
						   56,72 ,246,78,
						   56,80 ,246,86,
						   56,88 ,246,94,
						   -1,-1,-1,-1};

	if (cl!=WIZARD && cl!=RANGER && cl!=MONK)
	{
		class_cannot_use(cl,"1st level Wizard Spells");
		return;
	}

#ifndef DEV

	if (!adv.learn_wiz1_spells)
	{
		cannot_learn_more(WIZARD,1);
		return;
	}

#endif

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

#ifndef DEV
		if (!adv.learn_wiz1_spells)
		{
			cannot_learn_more(WIZARD,1);
			kill_gwindow(&win);
			return;
		}
#endif

		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.wizard_spells[DRAGONFLAME1]!=NO_SPELL)
						already_have_spell(STR_DRAGONFLAME1);
					 else
						 if (learn_wiz_ill_spell(STR_DRAGONFLAME1,1000L,1,&adv))
							 adv.wizard_spells[DRAGONFLAME1]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.wizard_spells[ARC_LIGHTNING1]!=NO_SPELL)
						already_have_spell(STR_ARC_LIGHTNING1);
					 else
						 if (learn_wiz_ill_spell(STR_ARC_LIGHTNING1,1000L,1,&adv))
							 adv.wizard_spells[ARC_LIGHTNING1]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.wizard_spells[FIND_HIDDEN_DOOR]!=NO_SPELL)
						already_have_spell(STR_FIND_HIDDEN_DOOR);
					 else
						 if (learn_wiz_ill_spell(STR_FIND_HIDDEN_DOOR,800L,1,&adv))
							 adv.wizard_spells[FIND_HIDDEN_DOOR]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.wizard_spells[GRAVMUR_RAGE]!=NO_SPELL)
						already_have_spell(STR_GRAVMUR_RAGE);
					 else
						 if (learn_wiz_ill_spell(STR_GRAVMUR_RAGE,1200L,1,&adv))
							 adv.wizard_spells[GRAVMUR_RAGE]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.wizard_spells[FROZEN_WIND1]!=NO_SPELL)
						already_have_spell(STR_FROZEN_WIND1);
					 else
						 if (learn_wiz_ill_spell(STR_FROZEN_WIND1,1000L,1,&adv))
							 adv.wizard_spells[FROZEN_WIND1]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.wizard_spells[MIGHTY_APPEARANCE]!=NO_SPELL)
						already_have_spell(STR_MIGHTY_APPEARANCE);
					 else
						 if (learn_wiz_ill_spell(STR_MIGHTY_APPEARANCE,900L,1,&adv))
							 adv.wizard_spells[MIGHTY_APPEARANCE]=SPELL_LEARNED;

					 break;


			case 6 : if (adv.wizard_spells[HAMMERHAND]!=NO_SPELL)
						already_have_spell(STR_HAMMERHAND);
					 else
						 if (learn_wiz_ill_spell(STR_HAMMERHAND,1000L,1,&adv))
							 adv.wizard_spells[HAMMERHAND]=SPELL_LEARNED;

					 break;

			case 7 : if (adv.wizard_spells[FIRE_MIST]!=NO_SPELL)
						already_have_spell(STR_FIRE_MIST);
					 else
						 if (learn_wiz_ill_spell(STR_FIRE_MIST,1000L,1,&adv))
							 adv.wizard_spells[FIRE_MIST]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_wizard_spells2()
{
	GWINDOW win, win_top;
	static char *t[]	={"Dragonflame II    (2000)",
						  "Arc Lightning II  (2000)",
						  "Swiftness         (1700)",
						  "Lethargy          (1700)",
						  "Sink              (2400)",
						  "Frozen Wind II    (2000)",
						  "Dispel Trap       (1600)",
						  "Blinding Flash    (1800)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="DASLNFTIB";
	char *t3="ªªªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,246,30,
						   56,32 ,246,38,
						   56,40 ,246,46,
						   56,48 ,246,54,
						   56,56 ,246,62,
						   56,64 ,246,70,
						   56,72 ,246,78,
						   56,80 ,246,86,
						   56,88 ,246,94,
						   -1,-1,-1,-1};

	if (cl!=WIZARD && cl!=RANGER)
	{
		class_cannot_use(cl,"2nd level Wizard Spells");
		return;
	}

#ifndef DEV

	if (adv.level<LEVEL_2_LEVEL)
	{
		not_powerful_enough(WIZARD,2);
		return;
	}

	if (!adv.learn_wiz2_spells)
	{
		cannot_learn_more(WIZARD,2);
		return;
	}

#endif

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

#ifndef DEV
		if (!adv.learn_wiz2_spells)
		{
			cannot_learn_more(WIZARD,2);
			kill_gwindow(&win);
			return;
		}
#endif

		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.wizard_spells[DRAGONFLAME2]!=NO_SPELL)
						already_have_spell(STR_DRAGONFLAME2);
					 else
						 if (learn_wiz_ill_spell(STR_DRAGONFLAME2,2000L,2,&adv))
							 adv.wizard_spells[DRAGONFLAME2]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.wizard_spells[ARC_LIGHTNING2]!=NO_SPELL)
						already_have_spell(STR_ARC_LIGHTNING2);
					 else
						 if (learn_wiz_ill_spell(STR_ARC_LIGHTNING2,2000L,2,&adv))
							 adv.wizard_spells[ARC_LIGHTNING2]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.wizard_spells[SWIFTNESS]!=NO_SPELL)
						already_have_spell(STR_SWIFTNESS);
					 else
						 if (learn_wiz_ill_spell(STR_SWIFTNESS,1700L,2,&adv))
							 adv.wizard_spells[SWIFTNESS]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.wizard_spells[LETHARGY]!=NO_SPELL)
						already_have_spell(STR_LETHARGY);
					 else
						 if (learn_wiz_ill_spell(STR_LETHARGY,1700L,2,&adv))
							 adv.wizard_spells[LETHARGY]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.wizard_spells[SINK]!=NO_SPELL)
						already_have_spell(STR_SINK);
					 else
						 if (learn_wiz_ill_spell(STR_SINK,2400L,2,&adv))
							 adv.wizard_spells[SINK]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.wizard_spells[FROZEN_WIND2]!=NO_SPELL)
						already_have_spell(STR_FROZEN_WIND2);
					 else
						 if (learn_wiz_ill_spell(STR_FROZEN_WIND2,2000L,2,&adv))
							 adv.wizard_spells[FROZEN_WIND2]=SPELL_LEARNED;

					 break;

			case 6 : if (adv.wizard_spells[DISPEL_TRAP]!=NO_SPELL)
						already_have_spell(STR_DISPEL_TRAP);
					 else
						 if (learn_wiz_ill_spell(STR_DISPEL_TRAP,1600L,2,&adv))
							 adv.wizard_spells[DISPEL_TRAP]=SPELL_LEARNED;

					 break;

			case 7 : if (adv.wizard_spells[BLINDING_FLASH]!=NO_SPELL)
						already_have_spell(STR_BLINDING_FLASH);
					 else
						 if (learn_wiz_ill_spell(STR_BLINDING_FLASH,1800L,2,&adv))
							 adv.wizard_spells[BLINDING_FLASH]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_wizard_spells3()
{
	GWINDOW win, win_top;
	static char *t[]	={"Dragonflame III    (3300)",
						  "Arc Lightning III  (3300)",
						  "Bind Demon         (3700)",
						  "Teleport           (3700)",
						  "Death Curse        (4000)",
						  "Frozen Wind III    (3300)",
						  "Invoke Familiar    (4000)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="DABTCFIM";
	char *t3="ªªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,250,30,
						   56,32 ,250,38,
						   56,40 ,250,46,
						   56,48 ,250,54,
						   56,56 ,250,62,
						   56,64 ,250,70,
						   56,72 ,250,78,
						   56,80 ,250,86,
						   -1,-1,-1,-1};

	if (cl!=WIZARD)
	{
		class_cannot_use(cl,"3rd level Wizard Spells");
		return;
	}

#ifndef DEV

	if (adv.level<LEVEL_3_LEVEL)
	{
		not_powerful_enough(WIZARD,3);
		return;
	}

	if (!adv.learn_wiz3_spells)
	{
		cannot_learn_more(WIZARD,3);
		return;
	}

#endif

	for (i=0; i<SIZE(t); i++)
		l=max(l,(int)strlen(t[i]));

	win.x1=20-(l/2)-1;
	win.y1=3;
	win.x2=21+(l/2)+1;
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

#ifndef DEV
		if (!adv.learn_wiz3_spells)
		{
			cannot_learn_more(WIZARD,3);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.wizard_spells[DRAGONFLAME3]!=NO_SPELL)
						already_have_spell(STR_DRAGONFLAME3);
					 else
						 if (learn_wiz_ill_spell(STR_DRAGONFLAME3,3300L,3,&adv))
							 adv.wizard_spells[DRAGONFLAME3]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.wizard_spells[ARC_LIGHTNING3]!=NO_SPELL)
						already_have_spell(STR_ARC_LIGHTNING3);
					 else
						 if (learn_wiz_ill_spell(STR_ARC_LIGHTNING3,3300L,3,&adv))
							 adv.wizard_spells[ARC_LIGHTNING3]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.wizard_spells[BIND_DEMON]!=NO_SPELL)
						already_have_spell(STR_BIND_DEMON);
					 else
						 if (learn_wiz_ill_spell(STR_BIND_DEMON,3700L,3,&adv))
							 adv.wizard_spells[BIND_DEMON]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.wizard_spells[TELEPORT]!=NO_SPELL)
						already_have_spell(STR_TELEPORT);
					 else
						 if (learn_wiz_ill_spell(STR_TELEPORT,3700L,3,&adv))
							 adv.wizard_spells[TELEPORT]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.wizard_spells[DEATH_CURSE]!=NO_SPELL)
						already_have_spell(STR_DEATH_CURSE);
					 else
						 if (learn_wiz_ill_spell(STR_DEATH_CURSE,4000L,3,&adv))
							 adv.wizard_spells[DEATH_CURSE]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.wizard_spells[FROZEN_WIND3]!=NO_SPELL)
						already_have_spell(STR_FROZEN_WIND3);
					 else
						 if (learn_wiz_ill_spell(STR_FROZEN_WIND3,3300L,3,&adv))
							 adv.wizard_spells[FROZEN_WIND3]=SPELL_LEARNED;

					 break;

			case 6 : if (adv.wizard_spells[INVOKE_FAMILIAR]!=NO_SPELL)
						already_have_spell(STR_INVOKE_FAMILIAR);
					 else
						 if (learn_wiz_ill_spell(STR_INVOKE_FAMILIAR,4000L,3,&adv))
							 adv.wizard_spells[INVOKE_FAMILIAR]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}
