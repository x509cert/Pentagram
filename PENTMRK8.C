#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <string.h>

void _PASCAL market_druid_spells1()
{
	GWINDOW win, win_top;
	static char *t[]	={"Trueflight       (100)",
						  "Walk on Water    (100)",
						  "Flame Sheet      (200)",
						  "Razor Leaves I   (200)",
						  "Poison Immunity  (150)",
						  "Plant Feast      (150)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="TWFRIPB";
	char *t3="ªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,218,30,
						   56,32 ,218,38,
						   56,40 ,218,46,
						   56,48 ,218,54,
						   56,56 ,218,62,
						   56,64 ,218,70,
						   56,72 ,218,78,
						   -1,-1,-1,-1};

	if (cl!=DRUID && cl!=HUNTER)
	{
		class_cannot_use(cl,"1st level Druid Spells");
		return;
	}

#ifndef DEV

	if (!adv.learn_dru1_spells)
	{
		cannot_learn_more(DRUID,1);
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
		if (!adv.learn_dru1_spells)
		{
			cannot_learn_more(DRUID,1);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.druid_spells[TRUEFLIGHT]!=NO_SPELL)
						already_have_spell(STR_TRUEFLIGHT);
					 else
						 if (learn_pri_dru_spell(STR_TRUEFLIGHT,100L,1,&adv))
							 adv.druid_spells[TRUEFLIGHT]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.druid_spells[WALK_ON_WATER]!=NO_SPELL)
						already_have_spell(STR_WALK_ON_WATER);
					 else
						 if (learn_pri_dru_spell(STR_WALK_ON_WATER,100L,1,&adv))
							 adv.druid_spells[WALK_ON_WATER]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.druid_spells[FLAME_SHEET]!=NO_SPELL)
						already_have_spell(STR_FLAME_SHEET);
					 else
						 if (learn_pri_dru_spell(STR_FLAME_SHEET,200L,1,&adv))
							 adv.druid_spells[FLAME_SHEET]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.druid_spells[RAZOR_LEAVES1]!=NO_SPELL)
						already_have_spell(STR_RAZOR_LEAVES1);
					 else
						 if (learn_pri_dru_spell(STR_RAZOR_LEAVES1,200L,1,&adv))
							 adv.druid_spells[RAZOR_LEAVES1]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.druid_spells[POISON_IMMUNITY]!=NO_SPELL)
						already_have_spell(STR_POISON_IMMUNITY);
					 else
						 if (learn_pri_dru_spell(STR_POISON_IMMUNITY,150L,1,&adv))
							 adv.druid_spells[POISON_IMMUNITY]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.druid_spells[PLANT_FEAST]!=NO_SPELL)
						already_have_spell(STR_PLANT_FEAST);
					 else
						 if (learn_pri_dru_spell(STR_PLANT_FEAST,150L,1,&adv))
							 adv.druid_spells[PLANT_FEAST]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_druid_spells2()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Aura of Protection (300)",
						  "Tangle Thorns      (400)",
						  "Razor Leaves II    (400)",
						  "Minds Eye          (350)",
						  "Ice Hammer         (500)",
						  "Invoke Familiar    (666)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="ATRMHIB";
	char *t3="ªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,234,30,
						   56,32 ,234,38,
						   56,40 ,234,46,
						   56,48 ,234,54,
						   56,56 ,234,62,
						   56,64 ,234,70,
						   56,72 ,234,78,
						   -1,-1,-1,-1};

	if (cl!=DRUID)
	{
		class_cannot_use(cl,"2nd level Druid Spells");
		return;
	}

#ifndef DEV

	if (adv.level<LEVEL_2_LEVEL)
	{
		not_powerful_enough(DRUID,2);
		return;
	}

	if (!adv.learn_dru2_spells)
	{
		cannot_learn_more(DRUID,2);
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
		if (!adv.learn_dru2_spells)
		{
			cannot_learn_more(DRUID,2);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.druid_spells[AURA_OF_PROTECTION]!=NO_SPELL)
						already_have_spell(STR_AURA_OF_PROTECTION);
					 else
						 if (learn_pri_dru_spell(STR_AURA_OF_PROTECTION,300L,2,&adv))
							 adv.druid_spells[AURA_OF_PROTECTION]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.druid_spells[TANGLE_THORNS]!=NO_SPELL)
						already_have_spell(STR_TANGLE_THORNS);
					 else
						 if (learn_pri_dru_spell(STR_TANGLE_THORNS,400L,2,&adv))
							 adv.druid_spells[TANGLE_THORNS]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.druid_spells[RAZOR_LEAVES2]!=NO_SPELL)
						already_have_spell(STR_RAZOR_LEAVES2);
					 else
						 if (learn_pri_dru_spell(STR_RAZOR_LEAVES2,400L,2,&adv))
							 adv.druid_spells[RAZOR_LEAVES2]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.druid_spells[MINDS_EYE]!=NO_SPELL)
						already_have_spell(STR_MINDS_EYE);
					 else
						 if (learn_pri_dru_spell(STR_MINDS_EYE,350L,2,&adv))
							 adv.druid_spells[MINDS_EYE]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.druid_spells[ICE_HAMMER]!=NO_SPELL)
						already_have_spell(STR_ICE_HAMMER);
					 else
						 if (learn_pri_dru_spell(STR_ICE_HAMMER,500L,2,&adv))
							 adv.druid_spells[ICE_HAMMER]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.druid_spells[DR_INVOKE_FAMILIAR]!=NO_SPELL)
						already_have_spell(STR_INVOKE_FAMILIAR);
					 else
						 if (learn_pri_dru_spell(STR_INVOKE_FAMILIAR,666L,2,&adv))
							 adv.druid_spells[DR_INVOKE_FAMILIAR]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_druid_spells3()
{
	GWINDOW win, win_top;
	static char *t[]	={"Ascertain Power  (950)",
						  "Banish Elemental (950)",
						  "Razor Leaves III (800)",
						  "Call Hailstorm   (950)",
						  "Maelstrom       (1400)",
						  "Earthquake      (4000)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="ABRCMET";
	char *t3="ªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,218,30,
						   56,32 ,218,38,
						   56,40 ,218,46,
						   56,48 ,218,54,
						   56,56 ,218,62,
						   56,64 ,218,70,
						   56,72 ,218,78,
						   -1,-1,-1,-1};

	if (cl!=DRUID)
	{
		class_cannot_use(cl,"3rd level Druid Spells");
		return;
	}

#ifndef DEV

	if (adv.level<LEVEL_3_LEVEL)
	{
		not_powerful_enough(DRUID,3);
		return;
	}

	if (!adv.learn_dru3_spells)
	{
		cannot_learn_more(DRUID,3);
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
		if (!adv.learn_dru3_spells)
		{
			cannot_learn_more(DRUID,3);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.druid_spells[ASCERTAIN_POWER]!=NO_SPELL)
						already_have_spell(STR_ASCERTAIN_POWER);
					 else
						 if (learn_pri_dru_spell(STR_ASCERTAIN_POWER,950L,3,&adv))
							 adv.druid_spells[ASCERTAIN_POWER]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.druid_spells[BANISH_ELEMENTAL]!=NO_SPELL)
						already_have_spell(STR_BANISH_ELEMENTAL);
					 else
						 if (learn_pri_dru_spell(STR_BANISH_ELEMENTAL,900L,3,&adv))
							 adv.druid_spells[BANISH_ELEMENTAL]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.druid_spells[RAZOR_LEAVES3]!=NO_SPELL)
						already_have_spell(STR_RAZOR_LEAVES3);
					 else
						 if (learn_pri_dru_spell(STR_RAZOR_LEAVES3,800L,3,&adv))
							 adv.druid_spells[RAZOR_LEAVES3]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.druid_spells[CALL_HAILSTORM]!=NO_SPELL)
						already_have_spell(STR_CALL_HAILSTORM);
					 else
						 if (learn_pri_dru_spell(STR_CALL_HAILSTORM,950L,3,&adv))
							 adv.druid_spells[CALL_HAILSTORM]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.druid_spells[MAELSTROM]!=NO_SPELL)
						already_have_spell(STR_MAELSTROM);
					 else
						 if (learn_pri_dru_spell(STR_MAELSTROM,1400L,3,&adv))
							 adv.druid_spells[MAELSTROM]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.druid_spells[EARTHQUAKE]!=NO_SPELL)
						already_have_spell(STR_EARTHQUAKE);
					 else
						 if (learn_pri_dru_spell(STR_EARTHQUAKE,4000L,3,&adv))
							 adv.druid_spells[EARTHQUAKE]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}
