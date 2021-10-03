#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <bstrings.h>

static
char *night_mess[]={
					"a hooting owl breaks ye solemn silence!",
					"a barking dog startles %s.",
					"an eerie loneliness grips %s!",
					"an owl flies past %s.",
					"ye nightly shadows play tricks on %s!",
					"%s hears a wolf howling in ye distance.",
					"a small animal runs into ye shrubs.",
					"%s feels something art following!",
					};

static
char *advent_mess[]={
					"a small rabbit runs past %s and scurries into ye undergrowth.",
					"%s sneezes!",
					"a black crow swoops past %s, just missing %s head.",
					"%s hath stood in some cattle dung!",
					"%s hath stood in some sheep droppings!",
					"%s feels something art following!",
					"%s brushes something from %s face!",
					"Through worry, %s bites %s fingernails!"
					};

static
char *dungeon_mess[]={
					"%s sees a pool of fresh blood just in front of thy party.",
					"%s feels uneasy.",
					"%s feels ill at ease.",
					"%s senses ye ransid smell of death.",
					"%s senses something odd.",
					"%s brushes a cobweb off %s face.",
					};

void _PASCAL incidentals()
{
	if ((percent()+percent())>=9)
	{
		check_wandering_monsters();
		return;
	}

	if (is_all_party_dead())
		return;

	if (pent_data.current_feature==WATER ||
		pent_data.current_feature==SEA)
			return;

	if (percent()>90)
		incidental_special();
	else
	if (IN_DUNGEON)
		incidental_dungeon();
	else
		incidental_adventuring();
}

void _PASCAL incidental_adventuring()
{
	int i;
	char mess[120];

	if (is_night_time())
	{                                                           /* Night */
		i=rand()%SIZE(night_mess);
		strcpy(mess,night_mess[i]);
	}
	else
	{                                                           /* Day   */
		if (percent()>70)
			strcpy(mess,incidental_daytime_adventuring());
		else
		{
			i=rand()%SIZE(advent_mess);
			strcpy(mess,advent_mess[i]);
		}
	}

	incidental_dispatcher(mess);
}

char *incidental_daytime_adventuring()
{
	 static char *stuff[]={ "a broken sword",
							"a rusty axe",
							"a broken flail",
							"a discarded oil flask",
							"a used torch",
							"a dented helmet",
							"a broken oar",
							"some rotting rope",
							"a broken basket",
							"a rotting backpack",
							"a rusty shield",
							"a broken shield",
							"an empty scabbard",
							"an orc skull",
							"a human skull",
							"an elven skull",
							"a broken arrow head"
						   };

	 static char *sees[]={"%s notices ",
						  "%s cannot help but notice ",
						  "%s stands on ",
						  "%s sees ",
						  "%s catches sight of "};

	 static char temp[150];
	 int i;

	 i=rand()%SIZE(stuff);

	 strcpy(temp,sees[rand()%SIZE(sees)]);
	 strcat(temp,stuff[i]);

	 if (percent()>80)
	 {
		 switch(rand()%3)
		 {
			 case 0 : strcat(temp,", but leaves it alone when some maggots crawl over it!");          break;
			 case 1 : strcat(temp,", but leaves it alone when some worms wriggle over it!");          break;
			 default: strcat(temp,", but leaves it alone upon seeing it is covered in corpse flies!");break;
		 }
	 }
	 else
	 {
		 strcat(temp,".");
	 }

	 return(temp);
}

void _PASCAL incidental_dungeon()
{
	int i;
	char mess[120];

	if (percent()>80)
	{
		if (percent()>60)
			dungeon_encounter_snotling();
		else
		if (percent()>75)
			incidental_khazad_dum();
		else
			incidental_dungeon_sounds();
	}
	else
	if (percent()>15)
	{
		dungeon_blow_out_light();
	}
	else
	{
		i=rand()%SIZE(dungeon_mess);
		strcpy(mess,dungeon_mess[i]);

		incidental_dispatcher(mess);
	}
}

void _PASCAL incidental_khazad_dum()
{
	int dwarf=ERR;
	int i;
	char temp[60];
	static char *t="\"Such blackness brings memories of tales my "
				   "grandfather told of a great realm named "
				   "khazad-dum buried deep under a mountain "
				   "in a distant land.\"";

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]) && TPP[i].nrace==DWARF)
			dwarf=i;

	if (dwarf)
	{
		sprintf(temp,"In a deep voice %s mutters, ",TPP[dwarf].name);
		SCROLL(2,1,temp);

		general_low_sound();
		pause(1);

		SCROLL(1,1,t);
		solemn_sound();
	}
}

void _PASCAL dungeon_blow_out_light()
{
	int person=ERR;
	char temp[100];
	char *s;
	static char *t[]={"'s Twilight Spell stops functioning",
					  "'s Lantern blows out",
					  " suddenly forgets ye words to Alethran"};

	person=check_party_globals_in_effect(IN_EFFECT_LIGHT);

	if (person!=ERR)
	{
		if (TPP[person].in_effect.twilight)
		{
			s=t[0];
			TPP[person].in_effect.twilight=0;
		}
		else
		if (TPP[person].in_effect.lantern_lit)
		{
			s=t[1];
			TPP[person].in_effect.lantern_lit=0;
		}
		else
		{
			s=t[2];
			TPP[person].in_effect.alethran=0;
		}

		sprintf(temp,"Quite mysteriously %s%s!",TPP[person].name,s);
		SCROLL(1,0,temp);

		solemn_sound();
	}
}

void _PASCAL incidental_dungeon_sounds()
{
	int i1,i2,i3,i4,i5;
	static char name[30];
	static char mess[120];
	static char *t1[]={"hears",
					   "can hear",
					   "noticies",
					   "notices",
					   "hears"};

	static char *t2[]={"",
					   "sounds of",
					   "ye sound of"};

	static char *t3[]={"",
					   "soft",
					   "loud",
					   "muffled"};

	static char *t4[]={"banging",
					   "chanting",
					   "chiming",
					   "clanking",
					   "coughing",
					   "creaking",
					   "foosteps",
					   "giggling",
					   "groaning",
					   "hissing",
					   "howling",
					   "knocking",
					   "laughter",
					   "moaning",
					   "murmuring",
					   "music",
					   "rattling",
					   "rattling chains",
					   "scratching",
					   "screaming",
					   "slithering",
					   "sobbing",
					   "splashing",
					   "tapping",
					   "whining"};

	static char *t5[]={"",
					   "ahead",
					   "from behind",
					   "nearby",
					   "far away",
					   "in ye distance"};


	if (percent()>90)
	{
		strcpy(name,"thy party");

	}
	else
	{
		i3=get_random_live_person();

		if (i3==ERR)	  /* Can't find someone alive etc */
			return;

		strcpy(name,TPP[i3].name);
	}

	i1=rand()%SIZE(t1);
	i2=rand()%SIZE(t2);
	i3=rand()%SIZE(t3);
	i4=rand()%SIZE(t4);
	i5=rand()%SIZE(t5);

	sprintf(mess,"%s %s %s %s %s %s.",name,
									  t1[i1],
									  t2[i2],
									  t3[i3],
									  t4[i4],
									  t5[i5]);

	stpcvt(mess,RLWHITE|RTWHITE|REDUCE);

	incidental_dispatcher(mess);
}

void _PASCAL incidental_special()
{
	if (pent_data.current_feature==FOREST)
	{
		treebeard();
	}
	else
	if (!IN_DUNGEON && someone_in_guild())
	{
		meet_random_party();
	}
	else
	if (is_night_time() || IN_DUNGEON)
	{
		if (percent()>60)
			bane_rune_acquire();
	}
}

void _PASCAL incidental_dispatcher(char *mess)
{
	static char temp[200];
	int i;
	char *sub_str;

	i=get_random_live_person();

	if (i==ERR)
		return;

	sub_str=strstr(mess,"%s");

	if (sub_str!=NULL)
	{
		if (strstr(sub_str,"%s")!=NULL)
		{
			sprintf(temp,
					mess,
					TPP[i].name,
					(TPP[i].his_her));
		}
		else
		{
			sprintf(temp,
					mess,
					TPP[i].name);
		}
	}
	else
	{
		strcpy(temp,mess);
	}

	incidental_sound();

	SCROLL(2,11,temp);
}
