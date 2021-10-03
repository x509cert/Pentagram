#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <bstrings.h>
#include <ctype.h>
#include <malloc.h>

#ifdef DEV
#include "bkeybrd.h"
#endif

void _PASCAL situation_details()
{
	GWINDOW win;
	int fin=FALSE;
	int page=1;
	int opt;
	int update;
	int mouse_status=fast_mouse;
	int TALISMAN_PAGE=5;
	static int boundary[]={49, 108,84, 120,
						   115,108,150,120,
						   181,108,216,120,
						   -1,-1,-1,-1};

	win.x1=5;
	win.y1=6;
	win.x2=30;
	win.y2=17;
	win.border=5;
	win.back=0;

	situation_status=ON;

	fast_mouse=OFF;

	make_gwindow(&win);

	click_box(49, 108,B_PREV);
	click_box(115,108,B_NEXT);
	click_box(181,108,B_FINISH);

	situation_details_page1();

	while (!fin)
	{
		opt=mouse_in_range(boundary,"PNF","PNQ");

		update=FALSE;

		switch(opt)
		{
			case 0 : if (page>1)
					 {
						page--;

						if (!pent_data.told_about_talisman &&
							page==TALISMAN_PAGE)
							page=TALISMAN_PAGE-1;

						update=TRUE;
					 }

					 break;

			case 1 : if (page<9)
					 {
						page++;

						if (!pent_data.told_about_talisman &&
							page==TALISMAN_PAGE)
							page=TALISMAN_PAGE+1;

						update=TRUE;
					 }

					 break;

			default: fin=TRUE;
					 break;
		}

		if (update)
		{
			switch(page)
			{
				case 1 : situation_details_page1(); break;
				case 2 : situation_details_page2(); break;
				case 3 : situation_details_page3(); break;
				case 4 : situation_details_page4(); break;
				case 5 : situation_details_page5(); break;
				case 6 : situation_details_page6(); break;
				case 7 : situation_details_page7(); break;
				case 8 : situation_details_page8(); break;
				case 9 : situation_details_page9(); break;
			}
		}
	}

	kill_gwindow(&win);

	situation_status=OFF;

	fast_mouse=mouse_status;
}

void _PASCAL _NEAR situation_details_cls()
{
	int col=_getcolor();

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,37,43,228,105);

	_setcolor(col);
}

void _PASCAL _NEAR situation_details_page1()
{
	int i,j,k;
	int XM=200;
	int YM=45;
	int XW=89;
	int YW=58;
	static char weat[250];
	char temp[40];
	int MAX_SIT1_WEATHER=35;

#ifdef DEV
	unsigned int ram;
	char *heap_stat;
	KEYSTATUS kstat;
#endif

	situation_details_cls();

	strcpy(weat,get_the_weather());

	situation_header("ENVIRONMENT");

	write_little("MOON PHASE :",40,58,6,FAST);

	switch(pent_data.moon_phase)
	{
		case NEW_MOON   :   draw_moon(XM,YM,moon_a);
							write_little("NEW MOON (DIVINE)",XW,YW,14,FAST);
							break;

		case PHASE_2    :   draw_moon(XM,YM,moon_b);
							write_little("CRESCENT WAXING",XW,YW,14,FAST);
							break;

		case PHASE_3    :   draw_moon(XM,YM,moon_c);
							write_little("CRESCENT WAXING",XW,YW,14,FAST);
							break;

		case PHASE_4    :   draw_moon(XM,YM,moon_d);
							write_little("FIRST QUARTER",XW,YW,14,FAST);
							break;

		case PHASE_5    :   draw_moon(XM,YM,moon_e);
							write_little("GIBBOUS WAXING",XW,YW,14,FAST);
							break;

		case PHASE_6    :   draw_moon(XM,YM,moon_f);
							write_little("GIBBOUS WAXING",XW,YW,14,FAST);
							break;

		case FULL_MOON  :   draw_moon(XM,YM,moon_g);
							write_little("FULL MOON (SORCERY)",XW,YW,14,FAST);
							break;

		case PHASE_8    :   draw_moon(XM,YM,moon_h);
							write_little("GIBBOUS WANING",XW,YW,14,FAST);
							break;

		case PHASE_9    :   draw_moon(XM,YM,moon_i);
							write_little("GIBBOUS WANING",XW,YW,14,FAST);
							break;

		case PHASE_10   :   draw_moon(XM,YM,moon_j);
							write_little("LAST QUARTER",XW,YW,14,FAST);
							break;

		case PHASE_11   :   draw_moon(XM,YM,moon_k);
							write_little("CRESCENT WANING",XW,YW,14,FAST);
							break;

		default         :   draw_moon(XM,YM,moon_l);
							write_little("CRESCENT WANING",XW,YW,14,FAST);
							break;
	}

	write_little("TIME       :",40,64,6,FAST);
	write_little(get_time_string(pent_data.time_hour,
								pent_data.time_minute),
				 XW,YW+6,14,FAST);

	write_little("DATE       :",40,70,6,FAST);

	strcpy(temp,give_date(pent_data.date));
	sprintf(pent_data.st_date,"%s, %u",temp,pent_data.year);
	write_little(pent_data.st_date,XW,YW+12,14,FAST);

	write_little("SEASON     :",40,76,6,FAST);

	switch(pent_data.season)
	{
		case SPRING : write_little("SPRING",XW,YW+18,14,FAST); break;
		case SUMMER : write_little("SUMMER",XW,YW+18,14,FAST); break;
		case AUTUMN : write_little("AUTUMN",XW,YW+18,14,FAST); break;
		case WINTER : write_little("WINTER",XW,YW+18,14,FAST); break;
	}

	write_little("WEATHER    :",40,82,6,FAST);

	for (i=0,k=0; i<(int)strlen(weat); i++,k++)
	{
		if (k>=MAX_SIT1_WEATHER)
		{
			k=0;

			for (j=i; !isspace((int)weat[j]); j--, k++)
				;

			weat[j]=(char)'\n';
		}
	}

	temp[1]='\0';

	for (i=0,j=0,k=3; i<(int)strlen(weat); i++)
	{
		temp[0]=weat[i];

		if (temp[0]!='\n')
		{
			write_little(temp,XW+(j*4),YW+6+(k*6),14,FAST);
			j++;
		}
		else
		{
			j=0;
			k++;
		}
	}

#ifdef DEV

	(void)kbstatus(&kstat);

	if (kstat.caps_state)
	{
		switch(_heapchk())
		{
			case _HEAPOK	   :
			case _HEAPEMPTY    :
			case _HEAPEND	   : heap_stat="Okay!"; 		break;

			case _HEAPBADBEGIN : heap_stat="Header Naffed"; break;
			case _HEAPBADNODE  : heap_stat="Bad Node";		break;
			case _HEAPBADPTR   : heap_stat="Bad Ptr";		break;
		}

		ram=mem_left();

		sprintf(temp,"HEAP: %uk (%s)",ram,heap_stat);
		write_little(temp,130,48,15,FAST);
	}
#endif
}

void _PASCAL _NEAR situation_details_page2()
{
	static char temp[180];
	char temp2[20];
	char *ra;
	char *cl;
	char st[10],shp[10];
	int i,j;
	int strongest=ERR;
	int dextrous=ERR;
	int max_str=0;
	int max_dex=0;
	int YW=64;

	situation_details_cls();

	situation_header("PARTY DETAILS");

	for (i=0; i<6; i++)
	{
		sprintf(temp,"%d)",i+1);

		write_little(temp,40,YW+(i*6),6,FAST);
	}

	if (!the_party.adventuring)
	{
		write_little("PARTY NOT ADVENTURING!",95,65,14,FAST);
		return;
	}

	for (i=0; i<=P_NUM; i++)
	{
		if (max_str<(j=(2*effective_strength(&TPP[i])) +
					   (2*effective_toughness(&TPP[i]))+
					   TPP[i].current_hp))
		{
			if (!TPP[i].is_dead)
			{
				max_str=j;
				strongest=i;
			}
		}

		if (max_dex<(j=(2*effective_agility(&TPP[i]))+
					   (2*effective_luck(&TPP[i]))   +
					   effective_speed(&TPP[i])))
		{
			if (!TPP[i].is_dead)
			{
				max_dex=j;
				dextrous=i;
			}
		}
	}

	write_little("NAME        RACE CLS LV STAT  HP SO DV AR",54,YW-7,6,FAST);

	for (i=0; i<=P_NUM; i++)
	{
		switch(TPP[i].nrace)
		{
			case HUMAN			: ra="Hmn"; 	break;
			case DWARF			: ra="Dwf"; 	break;
			case HIGH_ELF		: ra="Elf"; 	break;
			case GNOME			: ra="Gnm"; 	break;
			case HALF_OGRE		: ra="HfO"; 	break;
			case HALFLING		: ra="Hlf"; 	break;
			case SYLVAN_ELF 	: ra="Syl"; 	break;
			case DARK_ELF		: ra="Drk"; 	break;
		}

		switch(TPP[i].nclass)
		{
			case WARRIOR		: cl="War"; 	break;
			case PRIEST 		: cl="Pri"; 	break;
			case WIZARD 		: cl="Wiz"; 	break;
			case DRUID			: cl="Dru"; 	break;
			case THIEF			: cl="Thi"; 	break;
			case RANGER 		: cl="Ran"; 	break;
			case CRUSADER		: cl="Cru"; 	break;
			case BARD			: cl="Brd"; 	break;
			case MONK			: cl="Mnk"; 	break;
			case ILLUSIONIST	: cl="Ill"; 	break;
			case HUNTER 		: cl="Hun"; 	break;
			case DUELIST		: cl="Due"; 	break;
		}

		strcpy(st,get_adv_status_abbr(&TPP[i]));

		sprintf(shp,"%3d",TPP[i].current_hp);

		sprintf(temp,"%-12s%-5s%-4s%-3d%-5s%-4s%-3d%-3d%-4d",
								TPP[i].name,
								ra,
								cl,
								TPP[i].level,
								st,
								shp,
								TPP[i].current_sorcery_points,
								TPP[i].current_divine_points,
								effective_ac(&TPP[i]));

		strcpy(temp2,"");

		if (dextrous==i && strongest==i)
			strcpy(temp2,"B");
		else
		if (strongest==i)
			strcpy(temp2,"S");
		else
		if (dextrous==i)
			strcpy(temp2,"A");

		write_little(temp,54,YW+(i*6),player_is_alive(&TPP[i])?14:12,FAST);

		write_little(temp2,224,YW+(i*6),15,FAST);
	}
}

void _PASCAL _NEAR situation_details_page3()
{
	char temp[80];
	char weap[40];
	char dho[10];
	int i;
	int YW=64;
	PLAYER *adv;

	situation_details_cls();
	situation_header("WEAPON DETAILS");

	for (i=0; i<6; i++)
	{
		sprintf(temp,"%d)",i+1);

		write_little(temp,40,YW+(i*6),6,FAST);
	}

	if (!the_party.adventuring)
	{
		write_little("PARTY NOT ADVENTURING!",95,65,14,FAST);
		return;
	}

	write_little("NAME        WEAPON                D  H  O",54,YW-7,6,FAST);

	for (i=0; i<=P_NUM; i++)
	{
		adv=&TPP[i];

		sprintf(temp,"%-12s",adv->name);

		write_little(temp,54,YW+(i*6),player_is_dead(adv)?12:14,FAST);

		strcpy(temp,"");

		if (player_is_alive(adv))
		{
			strcpy(weap,get_weapon_name(adv->weapon_used.item));

			strcpy(dho,"        ");

			if (strlen(weap))
			{
				switch(adv->weapon_used.type)
				{
					case PLUS_1 : strcat(weap," (+1)"); break;
					case PLUS_2 : strcat(weap," (+2)"); break;
					case PLUS_3 : strcat(weap," (+3)"); break;
					default 	: break;
				}

				if (adv->weapon_used.poisoned)
					strcat(weap," (P)");
			}

			if (adv->darts)
				dho[0]='Y';

			if (player_is_carrying_potion(adv,POT_HOLYWATER))
				dho[3]='Y';

			if (adv->oil)
				dho[6]='Y';

			sprintf(temp,"%-12s%-20s  %-s",adv->name,weap,dho);

			write_little(temp,54,YW+(i*6),player_is_alive(adv)?14:12,FAST);
		}
	}
}

void _PASCAL _NEAR situation_details_page4()
{
	static char temp[300];
	int i,j;
	int YW=64;
	static IN_EFFECT effect;

	situation_details_cls();

	situation_header("SPELLS, POTIONS ETC. IN EFFECT");

	for (i=0; i<6; i++)
	{
		sprintf(temp,"%d)",i+1);

		write_little(temp,40,YW+(i*6),6,FAST);
	}

	if (!the_party.adventuring)
	{
		write_little("NO SPELLS OR POTIONS IN EFFECT!",80,65,14,FAST);
		return;
	}

	write_little("Name              In Effect",54,YW-7,6,FAST);

	for (i=0; i<=P_NUM; i++)
	{
		sprintf(temp,"%-12s",TPP[i].name);

		write_little(temp,54,YW+(i*6),player_is_dead(&TPP[i])?12:14,FAST);

		strcpy(temp,"");

		if (player_is_alive(&TPP[i]))
		{
			if (TPP[i].sneaking)
				strcat(temp,"Sneaking!");

			effect=TPP[i].in_effect;

			if (effect.windsong)
				strcat(temp,"Windsong, ");

			if (effect.wayfarers_tune)
				strcat(temp,"Wayfarers Tune, ");

			if (effect.alethran)
				strcat(temp,"Alethran, ");

			if (effect.tale_of_yuldar)
				strcat(temp,"Tale of Yuldar, ");

			if (effect.palisors_dream)
				strcat(temp,"Palisors Dream, ");

			if (effect.daylight_falls)
				strcat(temp,"Daylight Falls, ");

			if (effect.hunters_poem)
				strcat(temp,"Hunters Poem, ");


			if (effect.lantern_lit)
				strcat(temp,"Lantern Lit, ");

			if (effect.twilight)
				strcat(temp,"Twilight, ");

			if (effect.prot_fire)
				strcat(temp,"Prot. Fire, ");

			if (effect.prot_cold)
				strcat(temp,"Prot. Cold, ");

			if (effect.prot_traps)
				strcat(temp,"Prot. Traps, ");

			if (effect.trueflight)
				strcat(temp,"Trueflight, ");

			if (effect.walk_on_water)
				strcat(temp,"Walk Water, ");

			if (effect.tangle_thorns)
				strcat(temp,"Tang. Thorns, ");

			if (effect.mighty_appearance)
				strcat(temp,"Mighty App., ");

			if (effect.axels_shadow)
				strcat(temp,"Axels Shad., ");

			if (effect.mirage)
				strcat(temp,"Mirage, ");

			if (effect.sly_ears)
				strcat(temp,"Sly Ears, ");

			if (effect.cats_eyes)
				strcat(temp,"Cats Eyes, ");

			if (effect.poison_immunity)
				strcat(temp,"Imm. Poison, ");

			if (effect.aura_protection)
				strcat(temp,"Aura Prot., ");

			if (effect.swiftness)
				strcat(temp,"Swiftness, ");

			if (effect.find_hidden_doors)
				strcat(temp,"Find Hidd., ");

			if (effect.hammerhand)
				strcat(temp,"Hammerhand, ");

			if (effect.axels_blur)
				strcat(temp,"Axels Blur, ");

			if (effect.axels_shimmer)
				strcat(temp,"Axels Shim., ");

			if (effect.allys_dancing_dagger)
				strcat(temp,"Allys Dagger, ");

			if (effect.allys_dancing_mace)
				strcat(temp,"Allys Mace, ");

			if (effect.allys_dancing_sabre)
				strcat(temp,"Allys Sabre, ");

			if (effect.spell_of_passage)
				strcat(temp,"Passage, ");

			if (effect.missile_cloak)
				strcat(temp,"M. Cloak, ");


			if (effect.pot_striking)
				strcat(temp,"Striking, ");

			if (effect.pot_strength)
				strcat(temp,"Strength, ");

			if (effect.pot_holy_water)
				strcat(temp,"Holy W., ");

			if (effect.pot_undead_turn)
				strcat(temp,"Undead Turn, ");

			if (effect.pot_fire_resist)
				strcat(temp,"Fire Res., ");

			if (effect.pot_cold_resist)
				strcat(temp,"Cold Res., ");


			if (strlen(temp)>2)
			{
				for (j=strlen(temp); j>0; j--)
				{
					if (temp[j]==',')
					{
						temp[j]=' ';
						break;
					}
				}
			}

			stpcvt(temp,REDUCE|RLWHITE|RTWHITE);

			temp[32]='\0';
		}
		else
			strcpy(temp,"");

		write_little(temp,102,YW+(i*6),player_is_dead(&TPP[i])?3:11,FAST);
	}
}

#ifndef DEV
#pragma optimize("saz",on)
#endif

void _PASCAL _NEAR situation_details_page5()
{
	int any_bits=FALSE;
	int i,j;
	int k;
#define x1  145
#define y1  47
#define x2  x1+40
#define y2  y1
#define x3  x1+40
#define y3  y1+30
#define x4  x1
#define y4  y1+30
#define MOD 2

	situation_details_cls();

	situation_header("TALISMAN DETAILS");

	if (pent_data.talisman_1_found)
	{
		any_bits=TRUE;
		draw_talisman_part(x1,y1,1);
	}
	else
	{
		for (i=0; i<30; i++)
			for (j=0; j<40; j++)
				if (!((i+j)%MOD))
					if (TALISMAN_BIT(tal1,j,i)==7)
						FFPLOT(x1+j,y1+i,7);
	}

	if (pent_data.talisman_2_found)
	{
		any_bits=TRUE;
		draw_talisman_part(x2,y2,2);
	}
	else
	{
		for (i=0; i<30; i++)
			for (j=0; j<40; j++)
				if (!((i+j)%MOD))
					if (TALISMAN_BIT(tal2,j,i)==7)
						FFPLOT(x2+j,y2+i,7);
	}

	if (pent_data.talisman_4_found)
	{
		any_bits=TRUE;
		draw_talisman_part(x4,y4,4);
	}
	else
	{
		for (i=0; i<27; i++)
			for (j=0; j<40; j++)
				if (!((i+j)%MOD))
					if (TALISMAN_BIT(tal4,j,i)==7)
						FFPLOT(x4+j,y4+i,7);
	}

	if (pent_data.talisman_3_found)
	{
		any_bits=TRUE;
		draw_talisman_part(x3,y3,3);
	}
	else
	{
		for (i=0; i<26; i++)
			for (j=0; j<40; j++)
				if (!((i+j)%MOD))
					if (TALISMAN_BIT(tal3,j,i)==7)
						FFPLOT(x3+j,y3+i,7);
	}

	if (any_bits)
	{
		k=0;

		if (pent_data.talisman_1_found &&
			pent_data.talisman_2_found &&
			pent_data.talisman_3_found &&
			pent_data.talisman_4_found)
		{
			write_little("YE ENTIRE TALISMAN",40,65+(6*k++),14,FAST);
			write_little("    ART FOUND!    ",40,65+(6*k++),14,FAST);
		}
		else
		{
			if (pent_data.talisman_1_found)
				write_little("PART 1 IS FOUND.",40,65+(6*k++),14,FAST);

			if (pent_data.talisman_2_found)
				write_little("PART 2 IS FOUND.",40,65+(6*k++),14,FAST);

			if (pent_data.talisman_3_found)
				write_little("PART 3 IS FOUND.",40,65+(6*k++),14,FAST);

			if (pent_data.talisman_4_found)
				write_little("PART 4 IS FOUND.",40,65+(6*k++),14,FAST);
		}
	}
	else
	{
		write_little("YE HATH NO PARTS",40,65,14,FAST);
		write_little(" TO YE TALISMAN", 40,75,14,FAST);
	}

#undef x1
#undef y1
#undef x2
#undef y2
#undef x3
#undef y3
#undef x4
#undef y4
#undef MOD
}

#ifndef DEV
#pragma optimize("",on)
#endif

void _PASCAL _NEAR situation_details_page6()
{
	static char *titles[]={"TREASURE COLLECTED",
						   "EXPERIENCE GAINED",
						   "TIME SINCE START OF SAGA"};
	int i;
	char temp[80];
	char temp1[40];
	int Y5POS=125;
	int years, months, days;

	situation_details_cls();

	situation_header("ADVENTURE DETAILS");

	if (!the_party.adventuring)
	{
		write_little("PARTY NOT ADVENTURING!",95,65,14,FAST);
		return;
	}

	for (i=0; i<SIZE(titles); i++)
		write_little(titles[i],
					 Y5POS-(strlen(titles[i])*3/2),
					 58+i*17,
					 6,
					 FAST);

	sprintf(temp,"%lu GOLD CROWNS",the_party.gc_earned);
	write_little(temp,Y5POS-(strlen(temp)*3/2),65,14,FAST);

	sprintf(temp,"%lu XP",the_party.xp_earned);
	write_little(temp,Y5POS-(strlen(temp)*3/2),82,14,FAST);

	years =pent_data.year-START_YEAR;
	days  =pent_data.date-(START_DATE);
	months=days/28;
	days  =days%28;

	strcpy(temp,"");

	if (years)
	{
		sprintf(temp1,"%d Year%s",years,years!=1?"s":"");

		if (months || days)
			strcat(temp1,", ");
		else
			strcat(temp1," ");

		strcat(temp,temp1);
	}

	if (months)
	{
		sprintf(temp1,"%d Month%s",months,months!=1?"s ":" ");

		if (days)
			strcat(temp1,", ");
		else
			strcat(temp1," ");

		strcat(temp,temp1);
	}

	if (days)
	{
		sprintf(temp1,"%d Day%s",days,days!=1?"s":"");
		strcat(temp,temp1);
	}

	write_little(temp,Y5POS-(strlen(temp)*3/2),99,14,FAST);
}

void _PASCAL _NEAR situation_details_page7()
{
	static char _FAR *t[]={"Dagger               Battle Axe",
						   "Short Sword          Long Sword",
						   "Rapier               Claymore",
						   "Footmans Mace        Footmans Flail",
						   "Long Bow             Crossbow",
						   "Halberd              Dart",
						   "Sling                Flaming Oil"};

	static char _FAR *d[]={"1-3", "1-5",
						   "1-6", "1-8",
						   "1-8", "1-12",
						   "1-6", "1-8",
						   "1-6", "1-8",
						   "1-12","1-3",
						   "1-2", "1-8"};

	int i;

	situation_details_cls();

	situation_header("WEAPON QUICK REFERENCE");

	write_little("WEAPON        DAMG   WEAPON         DAMG",52,57,11,FAST);

	for (i=0; i<SIZE(t); i++)
	{
		write_little(t[i],52,65+(i*6),6,FAST);

		write_little(d[i*2],  108,65+(i*6),14,FAST);
		write_little(d[i*2+1],196,65+(i*6),14,FAST);
	}
}

void _PASCAL _NEAR situation_details_page8()
{
	static char _FAR *t[]={"None                Leather",
						   "Splint              Chain",
						   "Plate               Elven Chain"};

	static char _FAR *d[]={"10", "8",
						   "6",  "4",
						   "3",  "6"};

	static char _FAR *n[]={"All Shields and helmets subract 1 point",
						   "   from an adventurers armour value."};

	int i;

	situation_details_cls();

	situation_header("ARMOUR QUICK REFERENCE");

	write_little("ARMOUR     VALUE    ARMOUR          VALUE",52,57,11,FAST);

	for (i=0; i<SIZE(t); i++)
	{
		write_little(t[i],52,65+(i*6),6,FAST);

		write_little(d[i*2],  96,65+(i*6),14,FAST);
		write_little(d[i*2+1],196,65+(i*6),14,FAST);
	}

	for (i=0; i<SIZE(n); i++)
		write_little(n[i],56,92+(i*6),3,FAST);
}

void _PASCAL _NEAR situation_details_page9()
{
	int i;
	int across=7;
	char temp[3];
	int x,y;

	situation_details_cls();

	situation_header("RUNE TRANSLATION");

	for (i=0; i<26; i++)
	{
		temp[0]=(char)((char)i+'A');
		temp[1]='\0';

		x=(i%across)*26+46;
		y=(i/across)*11+60;

		print_text(temp,x,y,NORMAL_HEIGHT,6);
		print_rune(*temp-'A',x+10,y,14);
	}
}

#ifndef DEV
#pragma optimize("taz",on)
#endif

void _PASCAL draw_talisman_part(int x,int y,int part)
{
	int i,j;
	int c;

	switch(part)
	{
		case 1: for (i=0; i<30; i++)
					for (j=0; j<40; j++)
						if (c=TALISMAN_BIT(tal1,j,i))
							FFPLOT(x+j,y+i,(char)c);
				break;

		case 2: for (i=0; i<30; i++)
					for (j=0; j<40; j++)
						if (c=TALISMAN_BIT(tal2,j,i))
							FFPLOT(x+j,y+i,(char)c);
				break;

		case 3: for (i=0; i<26; i++)
					for (j=0; j<40; j++)
						if (c=TALISMAN_BIT(tal3,j,i))
							FFPLOT(x+j,y+i,(char)c);
				break;

		case 4: for (i=0; i<27; i++)
					for (j=0; j<40; j++)
						if (c=TALISMAN_BIT(tal4,j,i))
							FFPLOT(x+j,y+i,(char)c);
				break;
	}
}

void _PASCAL _NEAR draw_moon(int x,int y,unsigned *moon)
{
	unsigned v;
	int i,j;

	for (j=0; j<7; j++)
	{
		v=*(moon+j);

		for (i=0; i<16; i++)
		{
			if (v&(unsigned)0x8000)
			{
				FFPLOT(x+i,y+j,15);
				FFPLOT(x+i,(y+13)-j,15);
			}

			v<<=1;
		}
	}
}

#ifndef DEV
#pragma optimize("",on)
#endif

void _PASCAL _NEAR situation_header(char *mess)
{
	char temp[80];

	sprintf(temp,"SITUATION: %s",mess);
	write_little(temp,40,48,3,FAST);
}
