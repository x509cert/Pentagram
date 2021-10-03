#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <io.h>
#include <string.h>
#include <bstrings.h>
#include "mmalloc.h"

static RUMOUR_INDEX     *rumour_index;

void _PASCAL rumour_divulge_info(int bartenders_sex)
{
	int i;
	int subject;
	char subject_str[50];
	char temp[80];
	static char *fr[]={"\"Be gone - I have a husband!\"",
					   "\"hhmmm....another boring adventurer!\"",
					   "\"You've got more chance with an old witch!\"",
					   "\"Get lost!\""};
	static char *mr[]={"\"I have a wife!\"",
					   "\"I'm married!\"",
					   "\"Sex? hhmmm I remember that!\"",
					   "\"Sex? Wotsat?\""};

	rumour_open_index_file();

	strcpy(subject_str,rumour_get_subject());
	subject=rumour_parse_data(subject_str);

	if (subject==R_SWEAR)
	{
		swear_at_barman();
	}
	else
	if (subject==R_SEX)
	{
		if (bartenders_sex==SX_FEMALE)
			GX(fr[rand()%4],BAD);
		else
			GX(mr[rand()%4],BAD);
	}
	else
	if (subject==R_0)
	{
		i=percent();

		sprintf(temp,"\"I KNOW NOT OF %s, BUT THIS MAY HELP...\"",subject_str);
		SCROLL(1,0,temp);

		bad_sound();
		pause(1);

		scroll_scroll();

		if (i>=0 && i<=22)
			rumour_town_info();

		if (i>=23 && i<=40)
			rumour_dungeon_info(TRUE);

		if (i>=41)
			rumour_general_info(R_0);
	}
	else
	{
		scroll_scroll();

		if (subject==R_TOWN && percent()>=66)
			rumour_town_info();
		else
		if (subject==R_DUNGEON1 && percent()>=66)
			rumour_dungeon_info(TRUE);
		else
			rumour_general_info(subject);
	}

	rumour_close_index_file();
}

char *rumour_get_subject()
{
	static char temp[80];
	int fin=FALSE;
	GWINDOW win;
	char *line="[                    ]";
	char *t1="What subject art of";
	char *t2="interest to thee?";

	win.x1=5;
	win.y1=5;
	win.x2=35;
	win.y2=11;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(5);
	_settextposition(win.y1+1,20-strlen_half(t1));
	_outtext(t1);

	_settextposition(win.y1+2,20-strlen_half(t2));
	_outtext(t2);

	_settextcolor(2);
	_settextposition(9,20-strlen_half(line));
	_outtext(line);

	while (!fin)
	{
		strcpy(temp,gquery(win.x1+5,win.y2-2,strlen(line)-3,2,'A',""));
		if (strlen(temp))
			fin=TRUE;
		else
			GX("Surely, something must interest thee!",BAD);
	}

	kill_gwindow(&win);

	strupr(temp);

	return(temp);
}

int _PASCAL rumour_parse_data(char *data)
{
	int i;
	static struct
		   {
				char *syn;
				int  subject;

		   } synonyms[]={"MANGRETH",    R_MANGRETH,
						 "HERB",        R_HERB1,        "GUILD",       R_GUILD,
						 "DUNGEONEE",   R_GUILD,        "TALISMAN",    R_TALISMAN,
						 "CLASS",       R_CLASS,        "PROFESSION",  R_CLASS,
						 "JOB",         R_CLASS,        "HALF OGRE",   R_HALF_OGRE,
						 "HALFOGRE",    R_HALF_OGRE,    "OGRE",        R_HALF_OGRE,
						 "HALFLING",    R_HALFLING,     "HOBBIT",      R_HALFLING,
						 "DWARF",       R_DWARF,        "DWARVE",      R_DWARF,
						 "HUMAN",		R_HUMAN,		"MAN",		   R_HUMAN,
						 "MEN",         R_HUMAN,        "SYLVA",       R_SYLVAN_ELF,
						 "WARRIOR",     R_WARRIOR,      "FIGHTER",     R_WARRIOR,
						 "CRUSAD",      R_CRUSADER,     "RANGER",      R_RANGER,
						 "WIZARD",      R_WIZARD,       "WITCH",       R_WIZARD,
						 "PRIEST",      R_PRIEST,       "ILLUSION",    R_ILLUSIONIST,
						 "DRUID",       R_DRUID,        "DUEL",        R_DUELIST,
						 "HUNTER",      R_HUNTER,       "THIEF",       R_THIEF,
						 "THIEVE",      R_THIEF,        "MONK",        R_MONK,
						 "BROTHERH",    R_MONK,         "BARD",        R_BARD,
						 "MOONTEMPLE",  R_MOON_TEMPLE,  "TEMPLE",      R_MOON_TEMPLE,
						 "MOON TEMPL",  R_MOON_TEMPLE,  "UNDEAD",      R_UNDEAD,
						 "ZOMBIE",      R_UNDEAD,       "SKELETON",    R_UNDEAD,
						 "ARMOUR",      R_ARMOUR,       "ARMOR",       R_ARMOUR,
						 "BANE",        R_BANE_RUNE,    "RUNE",        R_BANE_RUNE,
						 "POISON",      R_POISON,       "WEAPON",      R_WEAPON,
						 "RACE",        R_RACE,         "TOWN",        R_TOWN,
						 "HAMLET",      R_TOWN,         "VILLAGE",     R_TOWN,
						 "WOMAN",       R_WOMAN,        "WOMEN",       R_WOMAN,
						 "LADY",        R_WOMAN,        "SEASON",      R_SEASON,
						 "WINTER",      R_SEASON,       "SUMMER",      R_SEASON,
						 "SPRING",      R_SEASON,       "AUTUMN",      R_SEASON,
						 "DISEASE",     R_DISEASE,      "DEATH",       R_DEATH,
						 "DEAD",        R_DEATH,        "FIRE",        R_FIRE,
						 "FLAME",       R_FIRE,         "MAGIC",       R_MAGIC,
						 "SPELL",       R_MAGIC,        "HUNTING",     R_HUNTING,
						 "WEATHER",     R_WEATHER,      "MONTH",       R_MONTH,
						 "PICK",        R_PICK_LOCK,    "TOOLS",       R_TOOLS,
						 "ANGHARAD",    R_ANGHARAD,     "BACKSTAB",    R_BACKSTAB,
						 "MONSTER",     R_MONSTER,      "CREATURE",    R_MONSTER,
						 "SNOTLING",    R_SNOTLING,     "MIST WARR",   R_MIST_WARRIOR,
						 "DRAGON",      R_DRAGON,       "SNAKE",       R_SNAKE,
						 "HELL",        R_HELLS,        "MISERY",      R_MISERY,
						 "DAMNED",      R_DAMNED,       "MORIB",       R_MORIBUND,
						 "CATHEDRAL",   R_CATHEDRAL,    "HEAL",        R_HEALING,
						 "DEMON",       R_DEMON,        "POTION",      R_POTION,
						 "FATE",        R_TALISMAN,     "FOXHOLLOW",   R_FOXHOLLOW,
						 "INSURANCE",   R_INSURANCE,    "GOD",         R_GODS,
						 "GAMBL",       R_GAMBLING,     "GOLD",        R_TREASURE,
						 "SILVER",      R_TREASURE,     "GEM",         R_TREASURE,
						 "TREASU",      R_TREASURE,     "KAITLIN",     R_KAITLIN,
						 "LOCK",        R_LOCK,         "MORT",        R_MORT,
						 "MUSIC",       R_MUSIC,        "PENTAGR",     R_PENTAGRAM,
						 "PEIRCER",     R_PIERCER,      "PRAY",        R_PRAY,
						 "RAYEK",       R_RAYEK,        "THREE",       R_3_TRAITORS,
						 "TRAITOR",     R_3_TRAITORS,   "RIVERNECK",   R_RIVERNECK,
						 "SOUTH RHYDE", R_SOUTH_RHYDE,  "NORTH RHYDE", R_NORTH_RHYDE,
						 "WOLFBURG",    R_WOLFBURG,     "SEA",         R_SEA,
						 "RUIN",        R_RUIN,         "RUWK",        R_RUWK,
						 "BANK",        R_BANK,         "LOSTSOUL",    R_LOSTSOUL,
						 "LOST SOUL",   R_LOSTSOUL,     "TRAP",        R_TRAP,
						 "TORCH",       R_TORCH,        "TINDER",      R_TORCH,
						 "FLINT",       R_TORCH,        "OAKVALE",     R_OAK_VALE,
						 "OAK VAL",     R_OAK_VALE,     "WAND",        R_WAND,
						 "HAG",         R_OLD_HAG,      "KALDRUTH",    R_OLD_HAG,
						 "GHOST SHIP",  R_GHOST_SHIP,   "EYE OF HELL", R_EYE_OF_HELL,
						 "EYE",         R_EYE_OF_HELL,  "HOLY WATER",  R_HOLY_WATER,
						 "COMBAT",      R_COMBAT,       "MELEE",       R_COMBAT,
						 "FOREST",      R_FOREST,       "WOODS",       R_FOREST,
						 "WOODLAN",     R_FOREST,       "REST",        R_REST,
						 "SLEEP",       R_REST,         "MONEY",       R_MONEY,
						 "CROWN",       R_MONEY,        "GC",          R_MONEY,
						 "DRINK",       R_DRINK,        "ALE",         R_DRINK,
						 "BEER",        R_DRINK,        "MEAD",        R_DRINK,
						 "BOOZE",       R_DRINK,        "ALCOH",       R_DRINK,
						 "GRAVE ROT",   R_GRAVE_ROT,    "POX",         R_POX,
						 "GNOME",       R_GNOME,        "RUMOUR",      R_RUMOUR,
						 "STORY",       R_RUMOUR,       "MOON",        R_MOON,
						 "CLOAK",       R_CLOAK,        "CRYPT",       R_CRYPT,
						 "FOOD",        R_FOOD,         "SUMMON",      R_SUMMON,
						 "INVOKE",      R_SUMMON,       "ANIMAL",      R_ANIMAL,
						 "CHEST",       R_CHEST,        "GIANT",       R_GIANT,
						 "SAGE",        R_SAGE,         "ISLAND",      R_ISLAND,
						 "RIVERDAWN",   R_RIVERDAWN,    "RIVER DAWN",  R_RIVERDAWN,
						 "LANDIR" , 	R_LANDIR,		"LANDIR",	   R_LANDIR,
						 "SEA POINT",   R_SEA_POINT,    "SEA PT",      R_SEA_POINT,
						 "SEAPOINT",    R_SEA_POINT,    "TIRAVEL",     R_TIRAVEL,
						 "ERIHN",       R_ERIHN,        "DUN CIRA",    R_DUN_CIRACH,
						 "DUNCIRA",     R_DUN_CIRACH,   "DUN TARI",    R_DUN_TARITH,
						 "DUNTAR",      R_DUN_TARITH,   "FROSTHAVEN",  R_FROSTHAVEN,
						 "FORST HAV",   R_FROSTHAVEN,   "MINASH",      R_MINASH,
						 "CAPE DAWN",   R_CAPE_DAWN,    "CAPEDAWN",    R_CAPE_DAWN,
						 "TELKAR",      R_TELKAR,       "KANRAITH",    R_KANRAITH,
						 "MIST POINT",  R_MIST_POINT,   "MIST PT",     R_MIST_POINT,
						 "MISTPOINT",   R_MIST_POINT,   "BLACKLOCK",   R_BLACKLOCK,
						 "BLACK LOCK",  R_BLACKLOCK,    "EDRAM",       R_EDRAM,
						 "MIRENNA", 	R_MIRENNA,		"LEECHWEED",   R_LEECHWEED,
						 "SNOWEED", 	R_SNOWEED,		"WOLFPETAL",   R_WOLFPETAL,
						 "ICE NETTLE",	R_ICE_NETTLE,	"GYLVIR",	   R_GYLVIR,
						 "GILVIR",      R_GYLVIR,       "GILVYR",      R_GYLVIR,
						 "ANGEL WING",  R_ANGELS_WING,  "ANGELS WI",   R_ANGELS_WING,
						 "ANGELSWI",	R_ANGELS_WING,	"BEERBERRY",   R_BEERBERRY,
						 "WILDSPRIG",   R_WILD_SPRIG,   "WILD SPR",    R_WILD_SPRIG,
						 "GLOWPETA",    R_GLOWPETAL,    "GLOW PET",    R_GLOWPETAL,
						 "THORNBRIG",   R_THORNBRIG,    "THORN BR",    R_THORNBRIG,
						 "ASHLEAF", 	R_ASHLEAF,		"PIGWORT",	   R_PIGWORT,
						 "DUNGEON", 	R_DUNGEON1, 	"WYNEWEED",    R_WYNEWEED,
						 "ATHIN",       R_ATHIN,        "TARL",        R_TARL,
						 "AERDRI",		R_AERDRI,		"CELANIL",	   R_CELANIL,
						 "CYRR",		R_CYRR, 		"MAGMI",	   R_MAGMI,
						 "RHYAA",       R_RHYAA,        "SOLONIR",     R_SOLONIR,
						 "OLRIC",       R_OLRIC,        "DUMATHIN",    R_DUMATHIN,
						 "MORR",		R_MORR, 		"ENORETH",	   R_ENORETH,
						 "DARK E",		R_DARK_ELF,
						 "ELF", 		R_ELF,			"ELVE", 	   R_ELF,};

	if (rumour_data_has_swearing(data))
		return(R_SWEAR);

	if (rumour_data_is_about_sex(data))
		return(R_SEX);

	for (i=0; i<SIZE(synonyms); i++)
		if (strstr(data,synonyms[i].syn)!=NULL)
			return(synonyms[i].subject);

	return(R_0);
}

int _PASCAL rumour_data_has_swearing(char *data)
{
	int i;
	static char *swear[]={"KCUF","SSIP","TNUC","TIHS","PARC",
						  "KNAW","DRATSAB","TIHSLLUB","STIT",
						  "ETABRUTSAM"};

	if (swear[0][0]!='F')
		for (i=0; i<SIZE(swear); i++)
			strrev(swear[i]);

	for (i=0; i<SIZE(swear); i++)
		if (strstr(data,swear[i])!=NULL)
			return(TRUE);

	return(FALSE);
}

int _PASCAL rumour_data_is_about_sex(char *data)
{
	return((strstr(data,"SEX")==NULL)?FALSE:TRUE);
}

void _PASCAL swear_at_barman()
{
	static char *t[]={ "With feline  reflexes ye bartender",
					   "picks up  an  empty  wine  bottle,",
					   "smashes it  against  ye  bar,  and",
					   "cruelly thrusts it into thy neck.",
					   "",
					   "Falling down  heavily, ye  kick  a",
					   "little, ooze,  spurt and  gurgle a",
					   "lot, and  finally die  in a puddle",
					   "of blood! Ouch!",
					   "",
					   "A few  patrons look around, but on",
					   "realising ye  mess art  caused  by",
					   "another   loud  mouthed adventurer",
					   "swearing at a bartender,they cont-",
					   "inue about their mundane business."};
	int i;
	GWINDOW win;
	static int boundary[]={140,144,175,156,
							-1,-1,-1,-1};

	killed_by_barman=TRUE;

	player_has_died_set(&adv);

	if (!the_party.in_town)
		save_adventurer(&adv);
	else
		TPP[rumr_person]=adv;

	win.x1=3;
	win.y1=1;
	win.x2=39;
	win.y2=22;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	_settextcolor(4);

	for (i=0; i<SIZE(t); i++)
	{
		_settextposition(win.y1+1+i,win.x1+1);
		_outtext(t[i]);
	}

	click_box(140,144,B_OK);

	solemn_sound();

	mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

void _PASCAL rumour_close_index_file()
{
	Mfree((void *)rumour_index);
}

void _PASCAL rumour_open_index_file()
{
	FILE *f;
	char temp[40];

	rumour_index=(RUMOUR_INDEX *)Mmalloc(50+(sizeof(RUMOUR_INDEX)*R_END));

	if (rumour_index==NULL)
		panic_RAM("Rumours");

	sprintf(temp,"%sRUM.IDX",PIC_DIRECTORY);

	f=fopen(temp,"rb");

	if (f==NULL)
		panic_FILE(temp);

	fread((void *)rumour_index,(size_t)(sizeof(RUMOUR_INDEX)*R_END),1,f);

	fclose(f);
}

void _PASCAL rumour_general_info(int subject)
{
	unsigned int offset;
	int rumour_num;
	char temp[100];

	if (subject==R_DUNGEON1 && percent()>50)
		subject=R_DUNGEON2;

	if (subject==R_HERB1 && percent()>50)
		subject=R_HERB2;

	if (subject!=R_0)
	{
		rumour_num=rand()%rumour_index[subject].rumour_number;
		offset=rumour_index[subject].rumour_pos[rumour_num];
	}
	else
		offset=0xFFFF;

	strcpy(temp,rumour_read_quote(offset));

	SCROLL(1,1,temp);

	if (!IN_DUNGEON)
		pause(8);
}

char *rumour_read_quote(int rumour_num)
{
	int j;
	FILE *f_rumour;
	char file[20];
	long length;
	int num;
	char temp[90];
	static char quote[90];

	sprintf(file,"%sRUM.FIL",PIC_DIRECTORY);

	f_rumour=fopen(file,"rb");

	if (f_rumour==NULL)
		panic_FILE(file);

	if (rumour_num==ERR)
	{
		length=filelength(fileno(f_rumour));

		num=(int)(length/(long)RUMOUR_SIZE);

		rumour_num=rand()%num;
	}

	if (fseek(f_rumour,(long)((long)rumour_num*(long)RUMOUR_SIZE),SEEK_SET))
		panic_FILE("RUM.FIL");

	if (fread((void *)temp,(size_t)RUMOUR_SIZE,1,f_rumour)==0)
		panic_FILE("RUM.FIL");

	fclose(f_rumour);

	for (j=0; j<80; j++)
		temp[j]^=XOR_CODE;

	stpcvt(temp,REDUCE|RLWHITE|RTWHITE);

	sprintf(quote,"\"%s\"",temp);

	return(quote);
}

void _PASCAL rumour_town_info()
{
	char temp[120];
	char details[40];
	char ns[15],ew[15];
	int town;
	int x,y;

	town=rand()%(MAX_SMALLTOWNS-1);
	town++;

	x=small_towns[town].x_position;
	y=small_towns[town].y_position;

	strcpy(details,get_town_details(x,y));

	x+=rand()%5;
	x-=rand()%5;

	y+=rand()%5;
	y-=rand()%5;

	if (x<=89)
		sprintf(ew,"%d~W",89-x);
	else
		sprintf(ew,"%d~E",x-89);

	if (y<=86)
		sprintf(ns,"%d~N",86-y);
	else
		sprintf(ns,"%d~S",y-86);

	sprintf(temp,"\"Ye %s is located at %s %s.\"",details,ns,ew);

	SCROLL(1,1,temp);

	pause(5);
}

void _PASCAL rumour_dungeon_info(int should_pause)
{
	char temp[120];
	char details[40];
	char ns[15],ew[15];
	int dung;
	int x,y;

	dung=rand()%MAX_DUNGEONS;

	x=look_dungeons[dung].x_position;
	y=look_dungeons[dung].y_position;

	strcpy(details,look_dungeons[dung].name);

	x+=rand()%5;
	x-=rand()%5;

	y+=rand()%5;
	y-=rand()%5;

	if (x<=89)
		sprintf(ew,"%d~W",89-x);
	else
		sprintf(ew,"%d~E",x-89);

	if (y<=86)
		sprintf(ns,"%d~N",86-y);
	else
		sprintf(ns,"%d~S",y-86);

	sprintf(temp,"\"%s is located at %s %s.\"",details,ns,ew);

	SCROLL(1,1,temp);

	if (should_pause)
	{
		scroll_scroll();
		pause(5);
	}
}

void _PASCAL land_on_dungeon_voice()
{
	SCROLL(1,14,"A magical voice booms out..");
	scroll_scroll();

	voice_sound();

	pause(1);

	rumour_general_info(R_0);       /* R_0 means get a random quote */

	set_to_corridor();
}
