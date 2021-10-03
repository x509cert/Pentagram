#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <string.h>

void _PASCAL market_illusionist_spells1()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Horrify               (900)",
						  "Sly Ears              (900)",
						  "Cat's Eyes            (900)",
						  "Phantasm I            (900)",
						  "Star Flare            (900)",
						  "Axel's Blur           (900)",
						  "Ally's Dancing Dagger (950)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="HSCPFADB";
	char *t3="ªªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,258,30,
						   56,32 ,258,38,
						   56,40 ,258,46,
						   56,48 ,258,54,
						   56,56 ,258,62,
						   56,64 ,258,70,
						   56,72 ,258,78,
						   56,80 ,258,86,
						   56,88 ,258,94,
						   -1,-1,-1,-1};

	if (cl!=ILLUSIONIST)
	{
		class_cannot_use(cl,"1st level Illusionist Spells");
		return;
	}

#ifndef DEV
	if (!adv.learn_ill1_spells)
	{
		cannot_learn_more(ILLUSIONIST,1);
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
		if (!adv.learn_ill1_spells)
		{
			cannot_learn_more(ILLUSIONIST,1);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.illusionist_spells[HORRIFY]!=NO_SPELL)
						already_have_spell(STR_HORRIFY);
					 else
						 if (learn_wiz_ill_spell(STR_HORRIFY,900L,1,&adv))
							 adv.illusionist_spells[HORRIFY]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.illusionist_spells[SLY_EARS]!=NO_SPELL)
						already_have_spell(STR_SLY_EARS);
					 else
						 if (learn_wiz_ill_spell(STR_SLY_EARS,900L,1,&adv))
							 adv.illusionist_spells[SLY_EARS]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.illusionist_spells[CATS_EYES]!=NO_SPELL)
						already_have_spell(STR_CATS_EYES);
					 else
						 if (learn_wiz_ill_spell(STR_CATS_EYES,900L,1,&adv))
							 adv.illusionist_spells[CATS_EYES]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.illusionist_spells[PHANTASM1]!=NO_SPELL)
						already_have_spell(STR_PHANTASM1);
					 else
						 if (learn_wiz_ill_spell(STR_PHANTASM1,900L,1,&adv))
							 adv.illusionist_spells[PHANTASM1]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.illusionist_spells[STAR_FLARE]!=NO_SPELL)
						already_have_spell(STR_STAR_FLARE);
					 else
						 if (learn_wiz_ill_spell(STR_STAR_FLARE,900L,1,&adv))
							 adv.illusionist_spells[STAR_FLARE]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.illusionist_spells[AXELS_BLUR]!=NO_SPELL)
						already_have_spell(STR_AXELS_BLUR);
					 else
						 if (learn_wiz_ill_spell(STR_AXELS_BLUR,900L,1,&adv))
							 adv.illusionist_spells[AXELS_BLUR]=SPELL_LEARNED;

					 break;

			case 6 : if (adv.illusionist_spells[ALLYS_DANCING_DAGGER]!=NO_SPELL)
						already_have_spell(STR_ALLYS_DANCING_DAGGER);
					 else
						 if (learn_wiz_ill_spell(STR_ALLYS_DANCING_DAGGER,950L,1,&adv))
							 adv.illusionist_spells[ALLYS_DANCING_DAGGER]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_illusionist_spells2()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Jonas' Spook        (1800)",
						  "Korina's Leap       (1800)",
						  "Phantasm II         (1800)",
						  "Moon Flare          (1800)",
						  "Create Artifacts    (1800)",
						  "Axel's Shimmer      (1800)",
						  "Ally's Dancing Mace (1900)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="JKPFCADB";
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

	if (cl!=ILLUSIONIST)
	{
		class_cannot_use(cl,"2nd level Illusionist Spells");
		return;
	}

#ifndef DEV

	if (adv.level<LEVEL_2_LEVEL)
	{
		not_powerful_enough(ILLUSIONIST,2);
		return;
	}

	if (!adv.learn_ill2_spells)
	{
		cannot_learn_more(ILLUSIONIST,2);
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
		if (!adv.learn_ill2_spells)
		{
			cannot_learn_more(ILLUSIONIST,2);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.illusionist_spells[JONAS_SPOOK]!=NO_SPELL)
						already_have_spell(STR_JONAS_SPOOK);
					 else
						 if (learn_wiz_ill_spell(STR_JONAS_SPOOK,1800L,2,&adv))
							 adv.illusionist_spells[JONAS_SPOOK]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.illusionist_spells[KORINAS_LEAP]!=NO_SPELL)
						already_have_spell(STR_KORINAS_LEAP);
					 else
						 if (learn_wiz_ill_spell(STR_KORINAS_LEAP,1800L,2,&adv))
							 adv.illusionist_spells[KORINAS_LEAP]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.illusionist_spells[PHANTASM2]!=NO_SPELL)
						already_have_spell(STR_PHANTASM2);
					 else
						 if (learn_wiz_ill_spell(STR_PHANTASM2,1800L,2,&adv))
							 adv.illusionist_spells[PHANTASM2]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.illusionist_spells[MOON_FLARE]!=NO_SPELL)
						already_have_spell(STR_MOON_FLARE);
					 else
						 if (learn_wiz_ill_spell(STR_MOON_FLARE,1800L,2,&adv))
							 adv.illusionist_spells[MOON_FLARE]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.illusionist_spells[CREATE_ARTIFACTS]!=NO_SPELL)
						already_have_spell(STR_CREATE_ARTIFACTS);
					 else
						 if (learn_wiz_ill_spell(STR_CREATE_ARTIFACTS,1800L,2,&adv))
							 adv.illusionist_spells[CREATE_ARTIFACTS]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.illusionist_spells[AXELS_SHIMMER]!=NO_SPELL)
						already_have_spell(STR_AXELS_SHIMMER);
					 else
						 if (learn_wiz_ill_spell(STR_AXELS_SHIMMER,1800L,2,&adv))
							 adv.illusionist_spells[AXELS_SHIMMER]=SPELL_LEARNED;

					 break;

			case 6 : if (adv.illusionist_spells[ALLYS_DANCING_MACE]!=NO_SPELL)
						already_have_spell(STR_ALLYS_DANCING_MACE);
					 else
						 if (learn_wiz_ill_spell(STR_ALLYS_DANCING_MACE,1900L,2,&adv))
							 adv.illusionist_spells[ALLYS_DANCING_MACE]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);
}

void _PASCAL market_illusionist_spells3()
{
	GWINDOW win, win_top;
	static char *t[]    ={"Axel's Shadow        (3300)",
						  "Mirage               (3800)",
						  "Phantasm III         (3700)",
						  "Sun Flare            (3900)",
						  "Suspend Time         (5000)",
						  "Ally's Dancing Sabre (3900)",
						  "Back to ye Market"};
	int i,l=0;
	char *t2="AMPFTDB";
	char *t3="ªªªªªªQ";
	int fin=FALSE;
	int cl=adv.nclass;
	static int boundary[]={56,24 ,258,30,
						   56,32 ,258,38,
						   56,40 ,258,46,
						   56,48 ,258,54,
						   56,56 ,258,62,
						   56,64 ,258,70,
						   56,72 ,258,78,
						   -1,-1,-1,-1};

	if (cl!=ILLUSIONIST)
	{
		class_cannot_use(cl,"3rd level Illusionist Spells");
		return;
	}

#ifndef DEV

	if (adv.level<LEVEL_3_LEVEL)
	{
		not_powerful_enough(ILLUSIONIST,3);
		return;
	}

	if (!adv.learn_ill3_spells)
	{
		cannot_learn_more(ILLUSIONIST,3);
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
		if (!adv.learn_ill3_spells)
		{
			cannot_learn_more(ILLUSIONIST,3);
			kill_gwindow(&win);
			return;
		}
#endif
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,t3))
		{
			case 0 : if (adv.illusionist_spells[AXELS_SHADOW]!=NO_SPELL)
						already_have_spell(STR_AXELS_SHADOW);
					 else
						 if (learn_wiz_ill_spell(STR_AXELS_SHADOW,3300L,3,&adv))
							 adv.illusionist_spells[AXELS_SHADOW]=SPELL_LEARNED;

					 break;

			case 1 : if (adv.illusionist_spells[MIRAGE]!=NO_SPELL)
						already_have_spell(STR_MIRAGE);
					 else
						 if (learn_wiz_ill_spell(STR_MIRAGE,3800L,3,&adv))
							 adv.illusionist_spells[MIRAGE]=SPELL_LEARNED;

					 break;

			case 2 : if (adv.illusionist_spells[PHANTASM3]!=NO_SPELL)
						already_have_spell(STR_PHANTASM3);
					 else
						 if (learn_wiz_ill_spell(STR_PHANTASM3,3700L,3,&adv))
							 adv.illusionist_spells[PHANTASM3]=SPELL_LEARNED;

					 break;

			case 3 : if (adv.illusionist_spells[SUN_FLARE]!=NO_SPELL)
						already_have_spell(STR_SUN_FLARE);
					 else
						 if (learn_wiz_ill_spell(STR_SUN_FLARE,3900L,3,&adv))
							 adv.illusionist_spells[SUN_FLARE]=SPELL_LEARNED;

					 break;

			case 4 : if (adv.illusionist_spells[SUSPEND_TIME]!=NO_SPELL)
						already_have_spell(STR_SUSPEND_TIME);
					 else
						 if (learn_wiz_ill_spell(STR_SUSPEND_TIME,5000L,3,&adv))
							 adv.illusionist_spells[SUSPEND_TIME]=SPELL_LEARNED;

					 break;

			case 5 : if (adv.illusionist_spells[ALLYS_DANCING_SABRE]!=NO_SPELL)
						already_have_spell(STR_ALLYS_DANCING_SABRE);
					 else
						 if (learn_wiz_ill_spell(STR_ALLYS_DANCING_SABRE,3900L,3,&adv))
							 adv.illusionist_spells[ALLYS_DANCING_SABRE]=SPELL_LEARNED;

					 break;

			default: fin=TRUE; break;
		}

		kill_gwindow(&win_top);
	}

	kill_gwindow(&win);

}
