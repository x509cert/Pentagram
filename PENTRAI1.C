#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <ctype.h>

void _PASCAL training_grounds()
{
	GWINDOW win;
	static    char *t[]={"Train an Adventurer",
						 "Progress thy Career",
						 "View an Adventurer",
						 "Kill an Adventurer",
						 "Add or Drop Adv.",
						 "Change thy Name",
						 "Leave ye Grounds"};
	char *t2="TPVKACL";
	int fin=FALSE;
	static int boundary[]={88, 40,240, 46,
						   88, 48,240, 54,
						   88, 56,240, 62,
						   88, 64,240, 70,
						   88, 72,240, 78,
						   88, 80,240, 86,
						   88, 88,240, 94,
						   -1,-1,-1,-1};

	log_all_disc_players();

	be_warrior= be_priest     = be_wizard  = be_druid   =
	be_thief  = be_ranger     = be_crusader= be_bard    =
	be_monk   = be_illusionist= be_hunter  = be_duelist = FALSE;

	win.x1=10;
	win.y1=5;
	win.x2=31;
	win.y2=14;
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
		cls_scroll();

		print_large_title("AT YE TRAINING GROUNDS");

		switch(mouse_in_range(boundary,t2,"TPVKACQ"))
		{
			case 0 : train_an_adventurer(); break;
			case 1 : go_up_a_level();       break;
			case 2 : view_an_adventurer();  break;
			case 3 : purge_an_adventurer(); break;
			case 4 : add_take_from_party(); break;
			case 5 : change_adv_name();     break;
			case 6 : fin=TRUE; break;
			default: break;
		}
	}

	kill_gwindow(&win);
}

void _PASCAL set_default_adv()
{
	int i;

	memset((void *)&adv,0,sizeof(PLAYER));

	adv.version=PENTAGRAM_VERSION;

	for (i=0; i<MAX_CARRY; i++)
		adv.items_carried[i].item=NOTHING;

	for (i=0; i<MAX_HERBS_CARRY; i++)
		adv.herbs_carried[i]=HERB_NONE;

	for (i=0; i<MAX_WIZARD_SPELLS; i++)
		adv.wizard_spells[i]=NO_SPELL;

	for (i=0; i<MAX_PRIEST_SPELLS; i++)
		adv.priest_spells[i]=NO_SPELL;

	for (i=0; i<MAX_DRUID_SPELLS; i++)
		adv.druid_spells[i]=NO_SPELL;

	for (i=0; i<MAX_ILLUSIONIST_SPELLS; i++)
		adv.illusionist_spells[i]=NO_SPELL;

	adv.xp				= 0L;
	adv.level           = 1;
	adv.is_dead         = FALSE;
	adv.is_stunned      = FALSE;
	adv.in_party        = FALSE;
	adv.food            = (rand()%60)+20;
	adv.last_food_bias  = (rand()%4)*30;
	adv.disease         = NO_DISEASE;
	adv.familiar        = NO_FAMILIAR;
	adv.guild_member    = FALSE;
	adv.bane_rune       = TYP_NO_RUNES;
	adv.drunkeness      = 0;
	adv.bard_songs_sung = 0;
	adv.member_of_HOE	= FALSE;
	adv.kills           = 0;
	adv.hungry          = NOT_HUNGRY;
	adv.points_cast     = 0;
}

void _PASCAL train_an_adventurer()
{
	unsigned long long_dummy;
	char *cl,*ra;
	char temp[80];
	GWINDOW win;
	char fname[20];

	set_default_adv();

	strcpy(fname,train_get_free_slot());

	if (*fname=='~')
	{
		GX("Ye adventurer roster art full!",BAD);
		return;
	}

	cls_scroll();

	if (train_get_race()!=TRUE)
		return;

	train_get_gender();
	train_generate_base_scores();
	train_generate_scores();

	if (abort_training)
		return;

	train_get_ethics();
	train_get_second_skills();
	train_get_prev_job();
	train_secondary_by_prev_job();
	train_get_money();
	train_get_height_weight();
	train_get_spells();
	train_get_random_spell();

	train_get_hand();
	train_get_age();
	train_get_age_cat();
	train_get_place_of_birth();
	train_get_hp();
	train_get_birthday();
	train_get_deity();
	(void)evaluate_level_details(&long_dummy);
	train_get_languages();
	train_get_speed();
	train_get_max_level();

	adv.max_drunkeness	= (adv.nrace==HALF_OGRE?8:(adv.nrace==DWARF?7:6))+
						  (adv.toughness>=16?1:0);

	cls_scroll();

	show_adventurer(&adv);

	if (gget_yn("Keep this Adventurer?"))
	{
		win.x1=4;
		win.y1=6;
		win.x2=36;
		win.y2=14;
		win.back=0;
		win.border=4;

		make_gwindow(&win);

		cl=get_class_string(adv.nclass,adv.sex);

		switch(adv.nrace)
		{
			case HUMAN      : ra="A Human";       break;
			case HIGH_ELF	: ra="A High Elven";  break;
			case HALF_OGRE  : ra="A Half Ogrish"; break;
			case DWARF      : ra="A Dwarven";     break;
			case GNOME      : ra="A Gnomish";     break;
			case SYLVAN_ELF : ra="A Sylvan Elf";  break;
			case DARK_ELF   : ra="A Dark Elf";    break;
			case HALFLING   : ra="A Halfling";    break;
		}

		sprintf(temp,"%s, %s %s",ra,adv.sex==SX_MALE?"Male":"Female",cl);

		_settextcolor(8);
		_settextposition(win.y1+1,(((win.x2-win.x1)/2)+win.x1)-strlen_half(temp));
		_outtext(temp);

		_settextposition(win.y1+3,win.x1+7);
		_settextcolor(7);
		_outtext("By what name shalt");

		_settextposition(win.y1+4,win.x1+7);
		_outtext("  thou be known?");

		while (!strlen(adv.name))
			strcpy(adv.name,gquery(win.x1+11,win.y1+6,sizeof(adv.name)-1,9,'A',""));

		strcpy(adv.file_name,fname);

		check_for_noble_names(&adv);

		save_adventurer(&adv);

		log_all_disc_players();

		kill_gwindow(&win);
	}
}

void _PASCAL check_for_noble_names(PLAYER *adv)
{
	static char *names[]={"MICHAEL","MIKE","MICK","ALLY"};
	char temp[80];
	int i;

	for (i=0; i<SIZE(names); i++)
	{
		if (strnicmp(adv->name,names[i],strlen(names[i]))==0)
		{
			sprintf(temp,"Ye gods smile down on thee, %s!",adv->name);
			GX(temp,GOOD);

			adv->hp+=3;
			adv->current_hp=adv->hp;

			break;
		}
	}
}

char *get_class_string(int nclass,int sex)
{
	static char *cl;

	switch(nclass)
	{
		case WARRIOR        :   cl="Warrior";
								break;

		case PRIEST         :   cl=(sex==SX_MALE?"Priest":"Priestess");
								break;

		case RANGER         :   cl="Ranger";
								break;

		case DRUID          :   cl="Druid";
								break;

		case THIEF          :   cl="Thief";
								break;

		case WIZARD         :   cl=(sex==SX_MALE?"Wizard":"Witch");
								break;

		case BARD           :   cl="Bard";
								break;

		case MONK           :   cl="Monk";
								break;

		case ILLUSIONIST    :   cl="Illusionist";
								break;

		case HUNTER 		:	cl=(sex==SX_MALE?"Hunter":"Huntress");
								break;

		case DUELIST        :   cl="Duelist";
								break;

		case CRUSADER       :   cl="Crusader";
								break;
	}

	return(cl);
}


void _PASCAL train_get_ethics()
{
	cls_scroll();
	scroll_wrap_write(0,"PLEASE PICK THINE ETHICS");

	if (adv.nrace==DARK_ELF)
	{
		adv.ethics=CHAOTIC;
	}
	else
	{
		switch(adv.nclass)
		{
			case BARD			:
			case PRIEST 		:
			case WARRIOR		:
			case ILLUSIONIST	:
			case HUNTER 		:
			case WIZARD 		:	train_get_ethics_1();
									break;

			case RANGER 		:	train_get_ethics_2();
									break;

			case THIEF			:
			case DUELIST		:	train_get_ethics_3();
									break;

			case MONK			:
			case CRUSADER		:	adv.ethics=LAWFUL;
									break;

			case DRUID			:	adv.ethics=NEUTRAL;
									break;
		}
	}
}

void _PASCAL train_get_ethics_1()
{
	static char *eth[]={"Lawful","Neutral","Chaotic"};
	char *t2="LNC";
	static int boundary[]={72,40,126,46,
						   72,48,126,54,
						   72,56,126,62,
						   -1,-1,-1,-1};
	GWINDOW win;

	win.x1=9;
	win.y1=5;
	win.x2=18;
	win.y2=10;
	win.back=0;
	win.border=7;

	make_gwindow(&win);

	print_menu_options(eth,
					   SIZE(eth),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   3,
					   11);

	short_prompt_sound();

	switch(mouse_in_range(boundary,t2,""))
	{
		case 0 :    adv.ethics=LAWFUL;  break;
		case 1 :    adv.ethics=NEUTRAL; break;
		case 2 :    adv.ethics=CHAOTIC; break;
	}

	kill_gwindow(&win);
}

void _PASCAL train_get_ethics_2()
{
	static char *eth[]={"Lawful","Neutral"};
	char *t2="LN";
	static int boundary[]={72,40,126,46,
						   72,48,126,54,
						   -1,-1,-1,-1};
	GWINDOW win;

	win.x1=9;
	win.y1=5;
	win.x2=18;
	win.y2=9;
	win.back=0;
	win.border=7;

	make_gwindow(&win);

	print_menu_options(eth,
					   SIZE(eth),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   3,
					   11);

	short_prompt_sound();

	switch(mouse_in_range(boundary,t2,""))
	{
		case 0 :    adv.ethics=LAWFUL;  break;
		case 1 :    adv.ethics=NEUTRAL; break;
	}

	kill_gwindow(&win);
}

void _PASCAL train_get_ethics_3()
{
	static char *eth[]={"Neutral","Chaotic"};
	char *t2="NC";
	static int boundary[]={72,40,126,46,
						   72,48,126,54,
						   -1,-1,-1,-1};
	GWINDOW win;

	win.x1=9;
	win.y1=5;
	win.x2=18;
	win.y2=9;
	win.back=0;
	win.border=7;

	make_gwindow(&win);

	print_menu_options(eth,
					   SIZE(eth),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   3,
					   11);

	short_prompt_sound();

	switch(mouse_in_range(boundary,t2,""))
	{
		case 0 :    adv.ethics=NEUTRAL; break;
		case 1 :    adv.ethics=CHAOTIC; break;
	}

	kill_gwindow(&win);
}

void _PASCAL train_get_second_skills()
{
	int i;

	for (i=1; i<=MAX_SKILLS; i++)
		adv.secondary_attrib[i]=15;

	switch(adv.nrace)
	{
		case
		HUMAN:      adv.secondary_attrib[SWIM]      +=10;
					adv.secondary_attrib[SURVIVAL]  +=10;
					adv.secondary_attrib[ATTACK]    +=10;
					adv.secondary_attrib[MISSILE]   +=20;
					adv.secondary_attrib[PICK_LOCK] +=10;
					break;

		case
		HIGH_ELF:	adv.secondary_attrib[HUNT]		+=10;
					adv.secondary_attrib[LISTEN]    +=10;
					adv.secondary_attrib[MISSILE]   +=20;
					adv.secondary_attrib[HERB_LORE] +=10;
					adv.secondary_attrib[MOVE_SILENT]+=10;
					break;

		case
		DWARF:      adv.secondary_attrib[ATTACK]    +=10;
					adv.secondary_attrib[PARRY]     +=10;
					adv.secondary_attrib[PICK_LOCK] +=10;
					adv.secondary_attrib[MOVE_SILENT]+=10;
					adv.secondary_attrib[IMMUNITY_POISON]+=20;
					break;

		case
		HALFLING:   adv.secondary_attrib[LISTEN]    +=10;
					adv.secondary_attrib[FIND_TRAP] +=15;
					adv.secondary_attrib[DISARM_TRAP]+=15;
					adv.secondary_attrib[MOVE_SILENT]+=15;
					adv.secondary_attrib[PICK_LOCK] +=10;
					adv.secondary_attrib[SWIM]       =10;
					break;

		case
		SYLVAN_ELF: adv.secondary_attrib[SURVIVAL]  +=10;
					adv.secondary_attrib[HEAL]      +=10;
					adv.secondary_attrib[HUNT]      +=20;
					adv.secondary_attrib[MISSILE]   +=20;
					break;

		case
		DARK_ELF:   adv.secondary_attrib[SURVIVAL]  +=10;
					adv.secondary_attrib[FIND_TRAP] +=15;
					adv.secondary_attrib[DISARM_TRAP]+=15;
					adv.secondary_attrib[MOVE_SILENT]+=25;
					break;

		case
		GNOME:      adv.secondary_attrib[ATTACK]    +=20;
					adv.secondary_attrib[PARRY]     +=10;
					adv.secondary_attrib[PICK_LOCK] +=10;
					adv.secondary_attrib[HUNT]      +=10;
					adv.secondary_attrib[LISTEN]    +=10;
					break;

		case
		HALF_OGRE:  adv.secondary_attrib[ATTACK]    +=25;
					adv.secondary_attrib[PARRY]     +=20;
					break;
	}

	switch(adv.nclass)
	{
		case
		WARRIOR :   adv.secondary_attrib[ATTACK]    +=17;
					adv.secondary_attrib[PARRY]     +=20;
					adv.secondary_attrib[SURVIVAL]  +=15;
					break;
		case
		WIZARD  :   adv.secondary_attrib[HEAL]      +=10;
					adv.secondary_attrib[HERB_LORE] +=15;
					adv.secondary_attrib[SWIM]      +=10;
					break;
		case
		PRIEST  :   adv.secondary_attrib[HEAL]      +=20;
					adv.secondary_attrib[HERB_LORE] +=5;
					adv.secondary_attrib[LISTEN]    +=15;
					break;
		case
		DRUID   :   adv.secondary_attrib[HEAL]      +=15;
					adv.secondary_attrib[HERB_LORE] +=25;
					break;
		case
		RANGER  :   adv.secondary_attrib[ATTACK]    +=17;
					adv.secondary_attrib[MISSILE]   +=17;
					adv.secondary_attrib[SURVIVAL]  +=20;
					break;
		case
		CRUSADER:   adv.secondary_attrib[ATTACK]    +=17;
					adv.secondary_attrib[PARRY]     +=15;
					adv.secondary_attrib[HEAL]      +=20;
					break;
		case
		THIEF   :   adv.secondary_attrib[PICK_LOCK] +=20;
					adv.secondary_attrib[FIND_TRAP] +=20;
					adv.secondary_attrib[DISARM_TRAP]+=15;
					adv.secondary_attrib[MISSILE]   +=5;
					break;

		case
		BARD    :   adv.secondary_attrib[ATTACK]    +=20;
					adv.secondary_attrib[PARRY]     +=20;
					adv.secondary_attrib[SURVIVAL]  +=20;
					adv.secondary_attrib[PICK_LOCK] +=10;
					adv.secondary_attrib[DISARM_TRAP]+=7;
					adv.secondary_attrib[MISSILE]   +=5;
					break;
		case
		MONK    :   adv.secondary_attrib[LISTEN]    +=10;
					adv.secondary_attrib[ATTACK]    +=30;
					adv.secondary_attrib[PARRY]     +=20;
					adv.secondary_attrib[HEAL]      +=30;
					break;

		case
		ILLUSIONIST:adv.secondary_attrib[HEAL]      +=10;
					adv.secondary_attrib[HERB_LORE] +=10;
					adv.secondary_attrib[MISSILE]   +=10;
					break;

		case
		HUNTER  :   adv.secondary_attrib[ATTACK]    +=10;
					adv.secondary_attrib[MISSILE]   +=10;
					adv.secondary_attrib[SURVIVAL]  +=10;
					adv.secondary_attrib[HUNT]      +=30;
					break;

		case
		DUELIST :   adv.secondary_attrib[ATTACK]    +=20;
					adv.secondary_attrib[PARRY]     +=20;
					break;
	}

	if (adv.sex==SX_MALE)
		adv.secondary_attrib[HUNT]+=15;
	else
		adv.secondary_attrib[HERB_LORE]+=15;

	for (i=1; i<=MAX_SKILLS; i++)
		if (percent()>60)
			adv.secondary_attrib[i]+=(rand()%5);
}

void _PASCAL train_secondary_by_prev_job()
{
	int v=get_dice_roll(3,1,2);

	switch(adv.previous_job)
	{
		case PJ_BODYGUARD	   :
		case PJ_MILITIAMAN	   :
		case PJ_OUTLAW		   :
		case PJ_BOUNTY_HUNTER  :
		case PJ_PIT_FIGHTER    :
		case PJ_SOLDIER 	   :
		case PJ_MERCENARY	   :
		case PJ_STREET_FIGHTER :
		case PJ_LABOURER	   :  adv.secondary_attrib[ATTACK]+=v;
								  break;

		case PJ_GRAVE_ROBBER   :
		case PJ_RAT_CATCHER    :
		case PJ_BEGGAR		   :
		case PJ_TOMB_ROBBER    :  adv.secondary_attrib[IMMUNITY_DISEASE]+=v;
								  break;

		case PJ_HERBALIST	   :
		case PJ_WOODSMAN	   :
		case PJ_FORESTER	   :  adv.secondary_attrib[HERB_LORE]+=v;
								  break;

		case PJ_OUTRIDER       :
		case PJ_GAMEKEEPER	   :
		case PJ_TRAPPER 	   :
		case PJ_SMUGGLER	   :
		case PJ_HUSBANDMAN	   :
		case PJ_PROSPECTOR	   :
		case PJ_RUSTLER 	   :
		case PJ_POACHER 	   :  adv.secondary_attrib[SURVIVAL]+=v;
								  break;

		case PJ_HYPNOTIST	   :
		case PJ_ALCHEMIST_APP  :
		case PJ_WIZARD_APP	   :
		case PJ_LIBRARIAN	   :
		case PJ_CLERIC		   :
		case PJ_SEER		   :
		case PJ_STUDENT 	   :
		case PJ_PHARMACIST	   :
		case PJ_ARTISAN_APP    :
		case PJ_SQUIRE		   :
		case PJ_TRADER		   :
		case PJ_INITIATE	   :
		case PJ_TEACHER 	   :
		case PJ_SCRIBE		   :  adv.secondary_attrib[SWIM]+=v;
								  break;

		case PJ_PEDLAR		   :  adv.secondary_attrib[MOVE_SILENT]+=v;
								  break;

		case PJ_ENGINEER	   :  adv.secondary_attrib[MISSILE]+=v;
								  break;

		case PJ_EXCISEMAN	   :
		case PJ_FOOTPAD 	   :
		case PJ_JEWELLER	   :
		case PJ_WATCHMAN       :
		case PJ_GAMBLER 	   :
		case PJ_JAILER		   :  adv.secondary_attrib[PARRY]+=v;
								  break;
	}
}

void _PASCAL train_get_prev_job()
{
	static char war_list[]={PJ_BODYGUARD,	  PJ_LABOURER,	  PJ_MERCENARY,
							PJ_MILITIAMAN,	  PJ_PIT_FIGHTER, PJ_WATCHMAN,
							PJ_OUTLAW,		  PJ_SOLDIER,	  PJ_STREET_FIGHTER,
							PJ_BOUNTY_HUNTER, PJ_GAMEKEEPER,  PJ_OUTRIDER,
							PJ_PROSPECTOR,	  PJ_TRAPPER,	  PJ_POACHER};

	static char wiz_list[]={PJ_HYPNOTIST,	  PJ_SEER,		  PJ_SCRIBE,
							PJ_ALCHEMIST_APP, PJ_STUDENT,	  PJ_TRADER,
							PJ_WIZARD_APP,	  PJ_PHARMACIST,  PJ_ARTISAN_APP,
							PJ_EXCISEMAN,	  PJ_ENGINEER,	  PJ_INITIATE,
							PJ_LIBRARIAN,	  PJ_TEACHER,	  PJ_JEWELLER};

	static char dru_list[]={PJ_HYPNOTIST,	  PJ_SEER,		  PJ_SCRIBE,
							PJ_ALCHEMIST_APP, PJ_WIZARD_APP,  PJ_INITIATE,
							PJ_HERBALIST,	  PJ_HUSBANDMAN,  PJ_TEACHER,
							PJ_STUDENT, 	  PJ_ARTISAN_APP, PJ_PHARMACIST,
							PJ_GAMEKEEPER,	  PJ_FORESTER,	  PJ_WOODSMAN};

	static char cru_list[]={PJ_BODYGUARD,	  PJ_LABOURER,	  PJ_MILITIAMAN,
							PJ_GAMEKEEPER,	  PJ_CLERIC,	  PJ_INITIATE,
							PJ_SEER,		  PJ_SCRIBE,	  PJ_TEACHER,
							PJ_SOLDIER, 	  PJ_STUDENT,	  PJ_WATCHMAN,
							PJ_PROSPECTOR,	  PJ_SQUIRE,	  PJ_TRADER};

	static char ran_list[]={PJ_BODYGUARD,	  PJ_LABOURER,	  PJ_MERCENARY,
							PJ_MILITIAMAN,	  PJ_PIT_FIGHTER, PJ_WATCHMAN,
							PJ_FORESTER,	  PJ_SOLDIER,	  PJ_STREET_FIGHTER,
							PJ_BOUNTY_HUNTER, PJ_GAMEKEEPER,  PJ_OUTRIDER,
							PJ_PROSPECTOR,	  PJ_TRAPPER};

	static char thi_list[]={PJ_OUTLAW,		  PJ_BEGGAR,	  PJ_GAMBLER,
							PJ_GRAVE_ROBBER,  PJ_FOOTPAD,	  PJ_JAILER,
							PJ_PEDLAR,		  PJ_SMUGGLER,	  PJ_TOMB_ROBBER,
							PJ_RAT_CATCHER,   PJ_OUTRIDER,	  PJ_RUSTLER,
							PJ_RUSTLER};

	switch(adv.nclass)
	{
		case WARRIOR     :
		case HUNTER      :
		case BARD        :
		case DUELIST     : adv.previous_job=(int)war_list[rand()%SIZE(war_list)];
						   break;

		case WIZARD      :
		case ILLUSIONIST :
		case PRIEST      : adv.previous_job=(int)wiz_list[rand()%SIZE(wiz_list)];
						   break;

		case MONK        :
		case DRUID       : adv.previous_job=(int)dru_list[rand()%SIZE(dru_list)];
						   break;

		case CRUSADER    : adv.previous_job=(int)cru_list[rand()%SIZE(cru_list)];
						   break;

		case RANGER      : adv.previous_job=(int)ran_list[rand()%SIZE(ran_list)];
						   break;

		default          : adv.previous_job=(int)thi_list[rand()%SIZE(thi_list)];
						   break;
	}
}

void _PASCAL train_get_money()
{
	int dough, add, banked;

	switch(adv.nclass)
	{
		case WARRIOR     : dough=120; add=50; break;
		case CRUSADER    : dough=100; add=20; break;
		case PRIEST 	 : dough=70 ; add=10; break;
		case RANGER 	 : dough=80 ; add=25; break;
		case DRUID       : dough=50 ; add=5 ; break;
		case THIEF       : dough=50 ; add=10; break;
		case WIZARD      : dough=50 ; add=5 ; break;
		case BARD        : dough=100; add=10; break;
		case MONK        : dough=40 ; add=5 ; break;
		case ILLUSIONIST : dough=50 ; add=10; break;
		case HUNTER      : dough=100; add=10; break;
		case DUELIST     : dough=100; add=10; break;
	}

	if (adv.nrace==HUMAN)
		add+=30;

	switch(adv.charisma)
	{
		case 0 :
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
		case 7 : add=0;    break;
		case 8 :
		case 9 :
		case 10: add+=5;   break;
		case 11:
		case 12:
		case 13: add+=15;  break;
		case 14:
		case 15: add+=25;  break;
		case 16: add+=45;  break;
		case 17: add+=75;  break;
		case 18: add+=95;  break;
		case 19: add+=150; break;
	}

	dough+=get_dice_roll(30,1,2*adv.luck+add);
	banked=get_dice_roll(5*adv.luck,1,adv.luck);

	adv.cash=(long unsigned)dough;
	adv.banked=(long unsigned)banked;
}

void _PASCAL train_get_height_weight()
{
	train_get_height();
	train_get_weight();
}

void _PASCAL train_get_height()
{
	 int i;
	 char str1[40],str2[40],adj[20];
	 int temp, average, over, under;
	 struct hw_percent {
						   int under;
						   int average;
						   int over;
						   int male_ave;
						   int male_minus;
						   int male_plus;
						   int female_ave;
						   int female_minus;
						   int female_plus;
					   };

	 static struct hw_percent  heights[10]= {{0,0,0,	0,0,0,		0,0,0},
											 {1,21,81,	72,12,12,	66,6,8},	/* Human */
											 {1,11,91,	60,4,4, 	54,4,6},	/* High Elf */
											 {1,16,81,	48,4,6, 	46,4,4},	/* Dwarf */
											 {1,11,91,	36,3,6, 	33,3,3},	/* Halfling  */
											 {1,11,91,  60,4,4,     54,4,6},    /* Sylvan Elf */
											 {1,16,81,	48,4,6, 	46,4,4},	/* Gnome */
											 {1,11,71,  84,4,12,    72,3,10},   /* Half Ogre  */
											 {1,11,91,  60,4,4,     54,4,6}};   /* Dark Elf */

	 i=percent();
	 i++;

	 memset(str1,0,sizeof(str1));
	 memset(str2,0,sizeof(str2));

	 average = (adv.sex==SX_MALE ? heights[adv.nrace].male_ave   : heights[adv.nrace].female_ave);
	 under   = (adv.sex==SX_MALE ? heights[adv.nrace].male_minus : heights[adv.nrace].female_minus);
	 over    = (adv.sex==SX_MALE ? heights[adv.nrace].male_plus  : heights[adv.nrace].female_plus);

	 if (i>=heights[adv.nrace].under && i<heights[adv.nrace].average)   /* short */
	 {
		 temp = average - rand()%under;
		 temp++;
		 strcpy(adj,"Short");
	 }

	 if (i>=heights[adv.nrace].average && i<heights[adv.nrace].over)  /* average */
	 {
		 temp = average;

		 if (percent()>50)
			temp++;

		 if (percent()>50)
			temp--;

		 if (percent()>50)
			temp++;

		 if (percent()>50)
			temp--;

		 strcpy(adj,"Average");
	 }

	 if (i>=heights[adv.nrace].over)                              /* tall */
	 {
		temp = average + rand()%over;
		temp++;
		strcpy(adj,"Tall");
	 }

	 adv.nheight=temp;

	 sprintf(adv.height,"%dft %din. (%s)",adv.nheight/12,adv.nheight%12,adj);
}

void _PASCAL train_get_weight()
{
	 int i;
	 char str1[40],str2[40],adj[20];
	 int temp, average, over, under;
	 struct hw_percent {
						   int under;
						   int average;
						   int over;
						   int male_ave;
						   int male_minus;
						   int male_plus;
						   int female_ave;
						   int female_minus;
						   int female_plus;
					   };

	 static struct hw_percent weights[10]= {{0,0,0,    0,0,0,	   0,0,0},
											{1,26,76,  175,36,50,  130,30,48},	   /* Human */
											{1,16,91,  100,10,20,  80,10,12},	   /* High Elf */
											{1,21,66,  120,16,24,  100,16, 20},    /* Dwarf  */
											{1,11,51,  60,8,12,    50,8,8}, 	   /* Halfling	*/
											{1,16,91,  100,10,20,  80,10,12},	   /* Sylvan Elf */
											{1,21,66,  120,16,24,  100,16,20},	   /* Gnome  */
											{1,11,81,  205,40,70,  180,30,50},     /* Half Ogre  */
											{1,16,91,  100,10,20,  80,10,12}};     /* Dark Elf */


	 i=percent();
	 i++;

	 memset(str1,0,sizeof(str1));
	 memset(str2,0,sizeof(str2));

	 average = (adv.sex==SX_MALE ? weights[adv.nrace].male_ave	 : weights[adv.nrace].female_ave);
	 under   = (adv.sex==SX_MALE ? weights[adv.nrace].male_minus : weights[adv.nrace].female_minus);
	 over    = (adv.sex==SX_MALE ? weights[adv.nrace].male_plus  : weights[adv.nrace].female_plus);

	 if (i>=weights[adv.nrace].under && i<weights[adv.nrace].average)   /* under */
	 {
		 temp = average - rand()%under;
		 temp++;
		 strcpy(adj,"Underweight");
	 }

	 if (i>=weights[adv.nrace].average && i<weights[adv.nrace].over)  /* average */
	 {
		 temp = average;
		 if (percent()>50)
			temp+=4;

		 if (percent()>50)
			temp-=4;

		 if (percent()>50)
			temp+=5;

		 if (percent()>50)
			temp-=5;

		 strcpy(adj,"Average");
	 }

	 if (i>=weights[adv.nrace].over)                              /* Heavy */
	 {
		temp = average + rand()%over;
		temp++;
		strcpy(adj,"Overweight");
	 }

	 adv.nweight=temp;

	 sprintf(adv.weight,"%dst %dlbs (%s)",adv.nweight/14,adv.nweight%14,adj);
}

void _PASCAL train_get_random_spell()
{
	int i,j,k;

	j=(percent()>=75)?2:1;

	for (k=0; k<j; k++)
	{
		switch(adv.nclass)
		{
			case DRUID      :
			case HUNTER     : i=rand()%PLANT_FEAST;
							  adv.druid_spells[i]=SPELL_LEARNED;
							  break;

			case PRIEST     :
			case CRUSADER   : i=rand()%DUNGEON_DIVINATION;
							  adv.priest_spells[i]=SPELL_LEARNED;
							  break;

			case MONK       :
			case WIZARD     :
			case RANGER     : i=rand()%MIGHTY_APPEARANCE;
							  adv.wizard_spells[i]=SPELL_LEARNED;
							  break;

			case ILLUSIONIST: i=rand()%AXELS_BLUR;
							  adv.illusionist_spells[i]=SPELL_LEARNED;
							  break;

			default         : break;
		}
	}
}

void _PASCAL train_get_spells()
{
	switch(adv.nclass)
	{
		case WIZARD      : adv.sorcery_points=3; adv.divine_points=0; break;
		case PRIEST      : adv.sorcery_points=0; adv.divine_points=3; break;
		case RANGER      : adv.sorcery_points=1; adv.divine_points=0; break;
		case CRUSADER    : adv.sorcery_points=0; adv.divine_points=1; break;
		case DRUID       : adv.sorcery_points=0; adv.divine_points=3; break;
		case MONK        : adv.sorcery_points=2; adv.divine_points=0; break;
		case ILLUSIONIST : adv.sorcery_points=3; adv.divine_points=0; break;
		case HUNTER      : adv.sorcery_points=0; adv.divine_points=1; break;
		default          : break;
	}

	switch(adv.nclass)
	{
		case WIZARD         :   adv.learn_wiz1_spells=2;
								adv.learn_wiz2_spells=0;
								adv.learn_wiz3_spells=0; break;

		case PRIEST         :   adv.learn_pri1_spells=2;
								adv.learn_pri2_spells=0;
								adv.learn_pri3_spells=0; break;

		case RANGER         :   adv.learn_wiz1_spells=1;
								adv.learn_wiz2_spells=0;
								adv.learn_wiz3_spells=0; break;

		case CRUSADER       :   adv.learn_pri1_spells=1;
								adv.learn_pri2_spells=0;
								adv.learn_pri3_spells=0; break;

		case MONK           :   adv.learn_wiz1_spells=1;
								adv.learn_wiz2_spells=0;
								adv.learn_wiz3_spells=0; break;

		case ILLUSIONIST    :   adv.learn_ill1_spells=2;
								adv.learn_ill2_spells=0;
								adv.learn_ill3_spells=0; break;

		case HUNTER         :   adv.learn_dru1_spells=1;
								adv.learn_dru2_spells=0;
								adv.learn_dru3_spells=0; break;

		default             :   break;
	}

	adv.current_sorcery_points=adv.sorcery_points;
	adv.current_divine_points=adv.divine_points;
}

int _PASCAL train_get_race()
{
	GWINDOW win;
	static	  char *t[]={"Human",
						 "High Elf",
						 "Sylvan Elf",
						 "Dark Elf",
						 "Halfling",
						 "Dwarf",
						 "Gnome",
						 "Half Ogre",
						 "Quit"};
	char *t2="HESDAWGOQ";
	int fin=FALSE;
	static int boundary[]={72,40, 150,46,
						   72,48, 150,54,
						   72,56, 150,62,
						   72,64, 150,70,
						   72,72, 150,78,
						   72,80, 150,86,
						   72,88, 150,94,
						   72,96, 150,102,
						   72,104,150,110,
						   -1,-1,-1,-1};

	cls_scroll();
	scroll_wrap_write(0,"PLEASE PICK THY RACE");

	win.x1=9;
	win.y1=5;
	win.x2=21;
	win.y2=16;
	win.back=0;
	win.border=7;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);

	short_prompt_sound();

	switch (mouse_in_range(boundary,t2,""))
	{
		case 0 :strcpy(adv.race,"Human");
				adv.nrace=HUMAN;
				fin=TRUE;
				break;

		case 1 :strcpy(adv.race,"High Elf");
				adv.nrace=HIGH_ELF;
				fin=TRUE;
				break;

		case 2 :strcpy(adv.race,"Sylvan Elf");
				adv.nrace=SYLVAN_ELF;
				fin=TRUE;
				break;

		case 3 :strcpy(adv.race,"Dark Elf");
				adv.nrace=DARK_ELF;
				fin=TRUE;
				break;

		case 4 :strcpy(adv.race,"Halfling");
				adv.nrace=HALFLING;
				fin=TRUE;
				break;

		case 5 :strcpy(adv.race,"Dwarf");
				adv.nrace=DWARF;
				fin=TRUE;
				break;

		case 6 :strcpy(adv.race,"Gnome");
				adv.nrace=GNOME;
				fin=TRUE;
				break;

		case 7 :strcpy(adv.race,"Half Ogre");
				adv.nrace=HALF_OGRE;
				fin=TRUE;
				break;

		default:fin=ERR; break;
	}

	kill_gwindow(&win);

	if (fin==ERR)
		return(FALSE);
	else
		return(TRUE);
}

void _PASCAL train_get_gender()
{
	GWINDOW win;
	static    char *t[]={" Male",
						 " Female"};
	int i;
	char letter[2];
	static int boundary[]={71,40,140,46,
						   71,48,140,56,
						   -1,-1,-1,-1};

	cls_scroll();
	scroll_wrap_write(0,"PLEASE PICK THY GENDER");

	win.x1=9;
	win.y1=5;
	win.x2=19;
	win.y2=9;
	win.back=0;
	win.border=7;

	make_gwindow(&win);

	draw_sex_sym(SX_MALE,win.x1*8,win.y1*8,9);
	draw_sex_sym(SX_FEMALE,win.x1*8,(win.y1+1)*8,9);

	for (i=0; i<SIZE(t); i++)
	{
		_settextcolor(5);
		_settextposition(win.y1+1+i,win.x1+2);
		_outtext(t[i]);

		_settextcolor(13);
		_settextposition(win.y1+1+i,win.x1+3);
		letter[0]=t[i][1];
		letter[1]='\0';
		_outtext(letter);
	}

	short_prompt_sound();

	switch(mouse_in_range(boundary,"MF",""))
	{
		case 0 :adv.sex=SX_MALE;
				strcpy(adv.sex_title,"Sire");
				strcpy(adv.him_her,"him");
				strcpy(adv.his_her,"his");
				strcpy(adv.he_she, "he");
				break;

		case 1 :adv.sex=SX_FEMALE;
				strcpy(adv.sex_title,"Madam");
				strcpy(adv.him_her,"her");
				strcpy(adv.his_her,"her");
				strcpy(adv.he_she, "she");
				break;
	}

	kill_gwindow(&win);
}
