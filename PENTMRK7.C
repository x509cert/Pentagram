#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <string.h>

void _PASCAL market_priest_spells1()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Twilight           (200)",
						  "Neutralise Poison  (500)",
						  "Prot. from Cold    (400)",
						  "Prot. from Fire    (400)",
						  "Cure Light Injury  (150)",
						  "Cause Light Injury (200)",
						  "Holy Spray         (200)",
						  "Dungeon Divination (200)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="TNCFUASDB";
	char *t3="ªªªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,234,30,
						   56,32 ,234,38,
						   56,40 ,234,46,
						   56,48 ,234,54,
						   56,56 ,234,62,
						   56,64 ,234,70,
						   56,72 ,234,78,
						   56,80 ,234,86,
						   56,88 ,234,94,
						   -1,-1,-1,-1};

	if (cl!=PRIEST && cl!=CRUSADER)
	{
		class_cannot_use(cl,"1st level Priest Spells");
		return;
	}

#ifndef DEV

	if (!adv.learn_pri1_spells)
	{
		cannot_learn_more(PRIEST,1);
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
		if (!adv.learn_pri1_spells)
		{
			cannot_learn_more(PRIEST,1);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.priest_spells[TWILIGHT]!=NO_SPELL)
						already_have_spell(STR_TWILIGHT);
					 else
						 if (learn_pri_dru_spell(STR_TWILIGHT,200L,1,&adv))
							 adv.priest_spells[TWILIGHT]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.priest_spells[NEUTRALISE_POISON]!=NO_SPELL)
						already_have_spell(STR_NEUTRALISE_POISON);
					 else
						 if (learn_pri_dru_spell(STR_NEUTRALISE_POISON,500L,1,&adv))
							 adv.priest_spells[NEUTRALISE_POISON]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.priest_spells[PROT_FROM_COLD]!=NO_SPELL)
						already_have_spell(STR_PROT_FROM_COLD);
					 else
						 if (learn_pri_dru_spell(STR_PROT_FROM_COLD,400L,1,&adv))
							 adv.priest_spells[PROT_FROM_COLD]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.priest_spells[PROT_FROM_FIRE]!=NO_SPELL)
						already_have_spell(STR_PROT_FROM_FIRE);
					 else
						 if (learn_pri_dru_spell(STR_PROT_FROM_FIRE,400L,1,&adv))
							 adv.priest_spells[PROT_FROM_FIRE]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.priest_spells[CURE_LIGHT_INJURY]!=NO_SPELL)
						already_have_spell(STR_CURE_LIGHT_INJURY);
					 else
						 if (learn_pri_dru_spell(STR_CURE_LIGHT_INJURY,150L,1,&adv))
							 adv.priest_spells[CURE_LIGHT_INJURY]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.priest_spells[CAUSE_LIGHT_INJURY]!=NO_SPELL)
						already_have_spell(STR_CAUSE_LIGHT_INJURY);
					 else
						 if (learn_pri_dru_spell(STR_CAUSE_LIGHT_INJURY,200L,1,&adv))
							 adv.priest_spells[CAUSE_LIGHT_INJURY]=SPELL_LEARNED;

					 break;

			case 6 : if (adv.priest_spells[HOLY_SPRAY]!=NO_SPELL)
						already_have_spell(STR_HOLY_SPRAY);
					 else
						 if (learn_pri_dru_spell(STR_HOLY_SPRAY,200L,1,&adv))
							 adv.priest_spells[HOLY_SPRAY]=SPELL_LEARNED;

					 break;

			case 7 : if (adv.priest_spells[DUNGEON_DIVINATION]!=NO_SPELL)
						already_have_spell(STR_DUNGEON_DIVINATION);
					 else
						 if (learn_pri_dru_spell(STR_DUNGEON_DIVINATION,200L,1,&adv))
							 adv.priest_spells[DUNGEON_DIVINATION]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_priest_spells2()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Open Chest          (900)",
						  "Remove Curse        (900)",
						  "Cure Disease        (800)",
						  "Blades             (1000)",
						  "Cure Severe Injury  (800)",
						  "Cause Severe Injury (900)",
						  "Prot. from Traps    (800)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="ORCBUAPM";
	char *t3="ªªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,242,30,
						   56,32 ,242,38,
						   56,40 ,242,46,
						   56,48 ,242,54,
						   56,56 ,242,62,
						   56,64 ,242,70,
						   56,72 ,242,78,
						   56,80 ,242,86,
						   -1,-1,-1,-1};

	if (cl!=PRIEST && cl!=CRUSADER)
	{
		class_cannot_use(cl,"2nd level Priest Spells");
		return;
	}

#ifndef DEV

	if (adv.level<LEVEL_2_LEVEL)
	{
		not_powerful_enough(PRIEST,2);
		return;
	}

	if (!adv.learn_pri2_spells)
	{
		cannot_learn_more(PRIEST,2);
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
		if (!adv.learn_pri2_spells)
		{
			cannot_learn_more(PRIEST,2);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.priest_spells[OPEN_CHEST]!=NO_SPELL)
						already_have_spell(STR_OPEN_CHEST);
					 else
						 if (learn_pri_dru_spell(STR_OPEN_CHEST,900L,2,&adv))
							 adv.priest_spells[OPEN_CHEST]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.priest_spells[REMOVE_CURSE]!=NO_SPELL)
						already_have_spell(STR_REMOVE_CURSE);
					 else
						 if (learn_pri_dru_spell(STR_REMOVE_CURSE,900L,2,&adv))
							 adv.priest_spells[REMOVE_CURSE]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.priest_spells[CURE_DISEASE]!=NO_SPELL)
						already_have_spell(STR_CURE_DISEASE);
					 else
						 if (learn_pri_dru_spell(STR_CURE_DISEASE,800L,2,&adv))
							 adv.priest_spells[CURE_DISEASE]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.priest_spells[BLADES]!=NO_SPELL)
						already_have_spell(STR_BLADES);
					 else
						 if (learn_pri_dru_spell(STR_BLADES,1000L,2,&adv))
							 adv.priest_spells[BLADES]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.priest_spells[CURE_SEVERE_INJURY]!=NO_SPELL)
						already_have_spell(STR_CURE_SEVERE_INJURY);
					 else
						 if (learn_pri_dru_spell(STR_CURE_SEVERE_INJURY,800L,2,&adv))
							 adv.priest_spells[CURE_SEVERE_INJURY]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.priest_spells[CAUSE_SEVERE_INJURY]!=NO_SPELL)
						already_have_spell(STR_CAUSE_SEVERE_INJURY);
					 else
						 if (learn_pri_dru_spell(STR_CAUSE_SEVERE_INJURY,900L,2,&adv))
							 adv.priest_spells[CAUSE_SEVERE_INJURY]=SPELL_LEARNED;

					 break;

			case 6 : if (adv.priest_spells[PROT_FROM_TRAPS]!=NO_SPELL)
						already_have_spell(STR_PROT_FROM_TRAPS);
					 else
						 if (learn_pri_dru_spell(STR_PROT_FROM_TRAPS,800L,2,&adv))
							 adv.priest_spells[PROT_FROM_TRAPS]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_priest_spells3()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Disruption           (1600)",
						  "Resurrect            (2900)",
						  "Cure Critical Injury (2000)",
						  "Cause Critical Injury(2200)",
						  "Missile Cloak        (1500)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="DRUAMB";
	char *t3="ªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,258,30,
						   56,32 ,258,38,
						   56,40 ,258,46,
						   56,48 ,258,54,
						   56,56 ,258,62,
						   56,64 ,258,70,
						   -1,-1,-1,-1};

	if (cl!=PRIEST)
	{
		class_cannot_use(cl,"3rd level Priest Spells");
		return;
	}

#ifndef DEV

	if (adv.level<LEVEL_3_LEVEL)
	{
		not_powerful_enough(PRIEST,3);
		return;
	}

	if (!adv.learn_pri3_spells)
	{
		cannot_learn_more(PRIEST,3);
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
		if (!adv.learn_pri3_spells)
		{
			cannot_learn_more(PRIEST,3);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.priest_spells[DISRUPTION]!=NO_SPELL)
						already_have_spell(STR_DISRUPTION);
					 else
						 if (learn_pri_dru_spell(STR_DISRUPTION,1600L,3,&adv))
							 adv.priest_spells[DISRUPTION]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.priest_spells[RESURRECT]!=NO_SPELL)
						already_have_spell(STR_RESURRECT);
					 else
						 if (learn_pri_dru_spell(STR_RESURRECT,2900L,3,&adv))
							 adv.priest_spells[RESURRECT]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.priest_spells[CURE_CRITICAL_INJURY]!=NO_SPELL)
						already_have_spell(STR_CURE_CRITICAL_INJURY);
					 else
						 if (learn_pri_dru_spell(STR_CURE_LIGHT_INJURY,2000L,3,&adv))
							 adv.priest_spells[CURE_CRITICAL_INJURY]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.priest_spells[CAUSE_CRITICAL_INJURY]!=NO_SPELL)
						already_have_spell(STR_CAUSE_CRITICAL_INJURY);
					 else
						 if (learn_pri_dru_spell(STR_CAUSE_CRITICAL_INJURY,2200L,3,&adv))
							 adv.priest_spells[CAUSE_CRITICAL_INJURY]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.priest_spells[MISSILE_CLOAK]!=NO_SPELL)
						already_have_spell(STR_MISSILE_CLOAK);
					 else
						 if (learn_pri_dru_spell(STR_MISSILE_CLOAK,1500L,3,&adv))
							 adv.priest_spells[MISSILE_CLOAK]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}
