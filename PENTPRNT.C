#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <bios.h>

static int  num_spells;
static int  prn_type;
static char *bon, *boff;

void _PASCAL print_adventurer(PLAYER *adv)
{
	char temp[80];
	GWINDOW win;

	sort_adv_items(adv);

	num_spells=show_determine_spells(adv);

	general_low_sound();

	if (strlen(adv->name))
		sprintf(temp,"Print out %s?",adv->name);
	else
		sprintf(temp,"Print out this adventurer?");

	if (!gget_yn(temp))
		return;

	if (get_printer_type()==ERR)
		return;

	switch(prn_type)
	{
		case PRN_EPSON  : get_printer_EPSON(); break;
		case PRN_IBM    : get_printer_IBM();   break;
		case PRN_LASER  : get_printer_LASER(); break;
	}

	GX("Set up thy printer...",GOOD);

	if (!test_printer())
		return;

	win.x1=13;
	win.y1=6;
	win.x2=27;
	win.y2=12;
	win.back=0;
	win.border=4;

	make_gwindow(&win);
	generic_pic_draw(win.x1*8+2,win.y1*8,"PRINT");

	print_banner();
	prn("");

	print_adventurer_1(adv);
	print_adventurer_2(adv);
	prn("");
	print_adventurer_3(adv);
	prn("");
	print_adventurer_4(adv);
	prn("");
	print_adventurer_5(adv);
	prn("\f");

	pause(1);

	kill_gwindow(&win);
}

int _PASCAL get_printer_type()
{
	GWINDOW win;
	static int boundary[]={40,56,146,62,
						   40,64,146,70,
						   40,72,146,78,
						   40,80,146,86,
						   -1,-1,-1,-1};
	static char *t[]={"Epson Printer","IBM Printer","Laser Printer","Quit"};
	char *t2="EILQ";

	win.x1=5;
	win.y1=5;
	win.x2=20;
	win.y2=13;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(12);
	_settextposition(win.y1+1,win.x1+1);
	_outtext("Printer Type");

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+3,
					   5,
					   13);

	short_prompt_sound();

	switch(mouse_in_range(boundary,t2,""))
	{
		case 0 : prn_type=PRN_EPSON; break;
		case 1 : prn_type=PRN_IBM;   break;
		case 2 : prn_type=PRN_LASER; break;
		default: prn_type=ERR;       break;
	}

	kill_gwindow(&win);

	return(prn_type);
}

void _PASCAL get_printer_EPSON()
{
	get_printer_IBM();
}

void _PASCAL get_printer_IBM()
{
	bon ="\x1B""\x45";
	boff="\x1B""\x46";
}

void _PASCAL get_printer_LASER()
{
	bon ="\x1B""\x28""\x73""\x33""\x42";
	boff="\x1B""\x28""\x73""\x2D""\x42";
}

int _PASCAL test_printer()
{
	int s;
	int data=34;
	int on_line;
	int not_busy;
	int fin=FALSE;
	int ret;

	while (!fin)
	{
		s=_bios_printer(_PRINTER_STATUS,0,data);

		on_line     =s&16;
		not_busy    =s&128;

		if (on_line && not_busy)
		{
			ret=TRUE;
			fin=TRUE;
		}
		else
		{
			if (gget_yn("Printer not ready. Retry?"))
				fin=FALSE;
			else
			{
				fin=TRUE;
				ret=FALSE;
			}
		}
	}

	return(ret);
}

void _PASCAL prn(char *mess)
{
	static char temp[200];

	sprintf(temp,"%s\n\r",mess);
	fprintf(stdprn,temp);
}

void _PASCAL print_banner()
{
	int i;
	static char temp[140];
	static char temp1[90];
	char *season;

	switch(pent_data.season)
	{
		case SPRING : season="Spring"; break;
		case SUMMER : season="Summer"; break;
		case AUTUMN : season="Autumn"; break;
		default     : season="Winter"; break;
	}

	sprintf(temp,"                            %sPentagram Adventurer%s\n\r",
			bon,boff);

	prn(temp);

	sprintf(temp1,"Printed in %s, on %s",
				   season,
				   pent_data.st_date);

	strcpy(temp,"");

	for (i=0; i<40-strlen_half(temp1); i++)
		strcat(temp," ");

	strcat(temp,temp1);
	prn(temp);
}

void _PASCAL print_adventurer_1(PLAYER *adv)
{
	char temp[120],nkills[30];
	char bane[20];

	sprintf(temp,"%s%s a %s, %s %s.%s\n\r",
			bon,
			adv->name,
			adv->sex==SX_MALE?"Male":"Female",
			adv->race,
			adv_title(adv),
			boff);

	prn(temp);

	if (adv->guild_member && adv->member_of_HOE)
		prn("Member of ye Dungeoneers Guild & Ye High Order of Executioneers\n\r");
	else
	if (adv->guild_member)
		prn("Member of Ye Dungeoneers Guild\n\r");
	else
	if (adv->member_of_HOE)
		prn("Member of Ye High Order of Executioneers\n\r");

	sprintf(temp,"Level........: %2u, maximum level is %2u",
			adv->level,
			adv->max_level);

	prn(temp);

	if (adv->kills==0)
		strcpy(nkills,"no kills yet!");
	else
		sprintf(nkills,"%u kill%s",adv->kills,(adv->kills==1?".":"s."));

	sprintf(temp,"Experience...: %lu, %s",adv->xp,nkills);

	prn(temp);

	if (adv->sorcery_points)
		sprintf(temp,"Sorcery Pts..: %2d left from %2d",
				adv->current_sorcery_points,
				adv->sorcery_points);
	else
		strcpy(temp,"Sorcery Pts..: None");

	prn(temp);

	if (adv->divine_points)
		sprintf(temp,"Divine Pts...: %2d left from %2d",
				adv->current_divine_points,
				adv->divine_points);
	else
		strcpy(temp,"Divine Pts...: None");

	prn(temp);

	sprintf(temp,"Strength.....: %2u (%2u)",adv->strength,effective_strength(adv));
	prn(temp);

	sprintf(temp,"Intelligence.: %2u (%2u)",adv->intelligence,effective_intelligence(adv));
	prn(temp);

	sprintf(temp,"Piety........: %2u (%2u)",adv->piety,effective_piety(adv));
	prn(temp);

	sprintf(temp,"Agility......: %2u (%2u)",adv->agility,effective_agility(adv));
	prn(temp);

	sprintf(temp,"Toughness....: %2u (%2u)",adv->toughness,effective_toughness(adv));
	prn(temp);

	sprintf(temp,"Charisma.....: %2u (%2u)",adv->charisma,effective_charisma(adv));
	prn(temp);

	sprintf(temp,"Luck.........: %2u (%2u)",adv->luck,effective_luck(adv));
	prn(temp);

	sprintf(temp,"Hit Points...: %u left from %u",adv->current_hp,adv->hp);
	prn(temp);

	if (adv->bane_rune!=TYP_NO_RUNES)
	{
		switch(adv->bane_rune)
		{
			case    TYP_NO_RUNES    :   strcpy(bane,"None");        break;
			case    TYP_UNDEAD      :   strcpy(bane,"Undead");      break;
			case    TYP_FIRE        :   strcpy(bane,"Fire");        break;
			case    TYP_WATER       :   strcpy(bane,"Water");       break;
			case    TYP_EARTH       :   strcpy(bane,"Earth");       break;
			case    TYP_AERIAL      :   strcpy(bane,"Aerial");      break;
			case    TYP_DEMONIC     :   strcpy(bane,"Demonic");     break;
			case    TYP_NOCTURNAL   :   strcpy(bane,"Nocturnal");   break;
			case    TYP_ICE         :   strcpy(bane,"Ice");         break;
		}

		sprintf(temp,"Bane Rune....: %s",bane);
		prn(temp);
	}
}

void _PASCAL print_adventurer_2(PLAYER *adv)
{
	char temp[120];
	char temp1[40];

	strcpy(temp,"Languages....: Old Tongue");

	if (adv->languages & LAN_ORCISH)
		strcat(temp,", Orcish");

	if (adv->languages & LAN_OGRISH)
		strcat(temp,", Ogrish");

	if (adv->languages & LAN_DWARFISH)
		strcat(temp,", Dwarven");

	if (adv->languages & LAN_ELVISH)
		strcat(temp,", Elven");

	if (adv->languages & LAN_GOBLIN)
		strcat(temp,", Goblin");

	if (adv->languages & LAN_UNDERWURLDE)
		strcat(temp,", Underwurlde");

	prn(temp);

	if (adv->ethics==LAWFUL)
		strcpy(temp1,"Lawful");
	else
	if (adv->ethics==NEUTRAL)
		strcpy(temp1,"Neutral");
	else
		strcpy(temp1,"Chaotic");

	sprintf(temp,"Ethics.......: %s",temp1);
	prn(temp);

	strcpy(temp1,get_adv_status(adv));
	sprintf(temp,"Status.......: %s",temp1);
	prn(temp);

	if (adv->disease!=NO_DISEASE)
	{
		switch(adv->disease)
		{
			case GRAVE_ROT	: prn("But thy skin art quite pale!"); break;
			case POX		: prn("But thy skin hath red sores!"); break;
			case PLAGUE     : prn("But thou feel'th very weak!)"); break;
		}
	}

	sprintf(temp,"Height.......: %s",adv->height);
	prn(temp);

	sprintf(temp,"Weight.......: %s",adv->weight);
	prn(temp);

	sprintf(temp,"Age..........: %u yrs, %s",adv->nage,adv->age);
	prn(temp);

	sprintf(temp,"Hand.........: %s",(adv->hand==HAND_LEFT?"Left":(adv->hand==HAND_RIGHT?"Right":"Ambidextrous")));
	prn(temp);

	sprintf(temp,"Birthday.....: %s",adv->birthday);
	prn(temp);

	sprintf(temp,"Birthtown....: %s",adv->where_born);
	prn(temp);

	sprintf(temp,"Prev. Job....: %s",adv_previous_job(adv));
	prn(temp);

	if (strnicmp("None",adv->deity_name,4)==0)
		sprintf(temp1,"None");
	else
		sprintf(temp1,"%s (%s)",adv->deity_name,adv->deity_control);

	if (adv->nclass==PRIEST || adv->nclass==CRUSADER || adv->nclass==MONK)
		sprintf(temp,"Deity........: %s (Prayed %lu days ago)",
					temp1,
					days_since_last_pray(adv));
	else
		sprintf(temp,"Deity........: %s",temp1);

	prn(temp);

	strcpy(temp1,familiar_type(adv));

	sprintf(temp,"Familiar.....: %s",temp1);
	prn(temp);

	sprintf(temp,"Cash.........: %lu GC",adv->cash);
	prn(temp);

	sprintf(temp,"Banked.......: %lu GC",adv->banked);
	prn(temp);

	sprintf(temp,"Insurance....: %s",adv->insurance==TRUE?"Yes":"No");
	prn(temp);
}

void _PASCAL print_adventurer_3(PLAYER *adv)
{
	static char temp[120];

	sprintf(temp,"%sSecondary Skills%s",bon,boff);
	prn(temp);

	sprintf(temp,"Attack.......: %2d (%2d)         Parry........: %2d (%2d)",
			adv->secondary_attrib[ATTACK],		 effective_attack(adv),
			adv->secondary_attrib[PARRY],		 effective_parry(adv));
	prn(temp);

	sprintf(temp,"Missile......: %2d (%2d)         Disarm Trap..: %2d (%2d)",
			adv->secondary_attrib[MISSILE], 	 effective_missile(adv),
			adv->secondary_attrib[DISARM_TRAP],   effective_disarm_trap(adv));
	prn(temp);

	sprintf(temp,"Find Trap....: %2d (%2d)         Pick Lock....: %2d (%2d)",
			adv->secondary_attrib[FIND_TRAP],	 effective_find_trap(adv),
			adv->secondary_attrib[PICK_LOCK],	 effective_pick_lock(adv));
	prn(temp);

	sprintf(temp,"Listen.......: %2d (%2d)         Move Silently: %2d (%2d)",
			adv->secondary_attrib[LISTEN],		 effective_listen(adv),
			adv->secondary_attrib[MOVE_SILENT],  effective_move_silently(adv));
	prn(temp);

	sprintf(temp,"Disease Imm..: %2d (%2d)         Poison Imm...: %2d (%2d)",
			adv->secondary_attrib[IMMUNITY_DISEASE], effective_disease_immunity(adv),
			adv->secondary_attrib[IMMUNITY_POISON],  effective_poison_immunity(adv));
	prn(temp);

	sprintf(temp,"Heal.........: %2d (%2d)         Herb Lore....: %2d (%2d)",
			adv->secondary_attrib[HEAL],		 effective_heal(adv),
			adv->secondary_attrib[HERB_LORE],	 effective_herb_lore(adv));
	prn(temp);

	sprintf(temp,"Hunt.........: %2d (%2d)         Survival.....: %2d (%2d)",
			adv->secondary_attrib[HUNT],		 effective_hunt(adv),
			adv->secondary_attrib[SURVIVAL],	 effective_survival(adv));
	prn(temp);

	sprintf(temp,"Swim.........: %2d (%2d)\n\r",
			adv->secondary_attrib[SWIM],		 effective_swim(adv));
	prn(temp);

	sprintf(temp,"Speed........: %2d (%2d)",	adv->speed,effective_speed(adv));
	prn(temp);

	sprintf(temp,"Armour.......: Front %-2d, Back %-2d",
												effective_ac(adv),
												effective_ac_back(adv));
	prn(temp);

	sprintf(temp,"Melee Attacks: %-2d",effective_attacks_per_round(adv));
	prn(temp);
}

void _PASCAL print_adventurer_4(PLAYER *adv)
{
	char temp[80];
	int fin=FALSE;
	int i;
	int something=FALSE;

	sprintf(temp,"%sHerbs%s",bon,boff);
	prn(temp);

	for (i=0; i<MAX_HERBS_CARRY;i++)
	{
		if (adv->herbs_carried[i]!=HERB_NONE)
		{
			something=TRUE;

			prn(get_herb_name(adv->herbs_carried[i],FALSE));
		}
	}

	if (!something)
		prn("None!");


	prn("");
	sprintf(temp,"%sTrappings & Provisions%s",bon,boff);
	prn(temp);

	something=FALSE;

	i=0;

	while (!fin)
	{
		if (adv->items_carried[i].item!=NOTHING)
			something=TRUE;

		fin=get_full_item_descrip(&adv->items_carried[i],temp);

		if (!fin)
			prn(temp);

		if (++i>MAX_CARRY)
			fin=TRUE;
	}

	if (adv->food)
	{
		sprintf(temp,"Food     (x%d)",adv->food);
		prn(temp);
		something=TRUE;
	}

	if (adv->darts)
	{
		sprintf(temp,"Darts    (x%d)",adv->darts);
		prn(temp);
		something=TRUE;
	}

	if (adv->arrows)
	{
		sprintf(temp,"Arrows   (x%d)",adv->arrows);
		something=TRUE;
		prn(temp);
	}

	if (adv->quarrels)
	{
		sprintf(temp,"Quarrels (x%d)",adv->quarrels);
		prn(temp);
		something=TRUE;
	}

	if (adv->oil)
	{
		sprintf(temp,"Oil Pots (x%d)",adv->oil);
		prn(temp);
		something=TRUE;
	}

	if (!something)
	{
		if (strlen(adv->name))
			sprintf(temp,"%s owns nothing!",adv->name);
		else
			strcpy(temp,"Thy adventurer hath no items!");

		prn(temp);
	}
}

void _PASCAL print_adventurer_5(PLAYER *adv)
{
	int i;
	char temp[40];

	sprintf(temp,"%sSpells%s",bon,boff);
	prn(temp);

	if (num_spells!=0)
	{
		for (i=0; i<num_spells; i++)
			prn(adv_spells[i].descrip);
	}
	else
	{
		if (strlen(adv->name))
			sprintf(temp,"%s hath no spells!",adv->name);
		else
			strcpy(temp,"Thy adventurer hath no spells!");

		prn(temp);
	}
}
