#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <ctype.h>

void _PASCAL show_adventurer(PLAYER *adv)
{
	int show_page=1;
	int fin=FALSE;
	GWINDOW win;
	int update;
	int max_page;
	int num_spells;
	static int boundary[]={26, 162,63, 174,
						   98, 162,132,174,
						   176,162,211,174,
						   250,162,285,174,
						   -1,  -1, -1, -1};

	win.x1=2;
	win.y1=2;
	win.x2=39;
	win.y2=24;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	click_box(26, 162,B_PREV);
	click_box(98, 162,B_NEXT);
	click_box(176,162,B_PRINT);
	click_box(250,162,B_FINISH);

	update=TRUE;

	sort_adv_items(adv);

	num_spells=show_determine_spells(adv);

	max_page=num_spells>15?6:5;

	while (!fin)
	{
		if (update)
			switch(show_page)
			{
				case 1 : show_adventurer_1(adv);			break;
				case 2 : show_adventurer_2(adv);			break;
				case 3 : show_adventurer_3(adv);			break;
				case 4 : show_adventurer_4(adv);			break;
				case 5 : show_adventurer_5(adv,num_spells); break;
				case 6 : show_adventurer_6(num_spells);     break;
			}

		update=FALSE;

		switch(mouse_in_range(boundary,"PNOF","PNOQ"))
		{
			case 0 : if (show_page>1)
					 {
						update=TRUE;
						show_page--;
					 }

					 break;

			case 1 : if (show_page<max_page)
					 {
						update=TRUE;
						show_page++;
					 }

					 break;

			case 2 : print_adventurer(adv);
					 break;

			case 3 : fin=TRUE;
					 break;
		}
	}

	kill_gwindow(&win);
}

void _PASCAL _NEAR cls_show_adventurer()
{
	int col=_getcolor();

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,14,13,299,160);
	_setcolor(col);
}

void _PASCAL _NEAR show_adventurer_1(PLAYER *adv)
{
	int i,y;
	int longest=0;
	char temp[80],nkills[20];
	char *fmt="%2u (%2u)";
	static char *items1[]={"Name",
						   "Race",
						   "Profession",
						   "Level",
						   "Experience",
						   "Sorcery Pts",
						   "Divine Pts",
						   "Strength",
						   "Intelligence",
						   "Piety",
						   "Agility",
						   "Toughness",
						   "Charisma",
						   "Luck",
						   "Hit Points"};

	cls_show_adventurer();

	_settextcolor(4);

	_settextposition(3,3);

	_outtext("Personal Details (1 of 3)");

	for (i=0; i<SIZE(items1); i++)
		longest=max(longest,(int)strlen(items1[i]));

	for (i=0; i<SIZE(items1); i++)
	{
		strcpy(temp,items1[i]);

		while ((int)strlen(temp)<longest)
			strcat(temp,"\xFA");

		strcat(temp,":");

		_settextcolor(6);
		_settextposition(5+i,3);
		_outtext(temp);
	}

	_settextcolor(3);

	_settextposition(5,longest+5);
	_outtext(adv->name);

	_settextposition(6,longest+5);
	_outtext(adv->race);

	draw_sex_sym(adv->sex,(longest+5+strlen(adv->race))*8,40,9);

	_settextposition(7,longest+5);
	_outtext(adv_title(adv));

	_settextposition(8,longest+5);
	sprintf(temp,"%u (%u)",adv->level,adv->max_level);
	_outtext(temp);

	_settextposition(9,longest+5);

	if (adv->kills==0)
		strcpy(nkills,"no kills yet!");
	else
		sprintf(nkills,"%u kill%s",adv->kills,(adv->kills==1?".":"s."));

	sprintf(temp,"%lu, %s",adv->xp,nkills);
	_outtext(temp);

	_settextposition(10,longest+5);

	if (adv->sorcery_points)
		sprintf(temp,"%u left from %u",adv->current_sorcery_points,adv->sorcery_points);
	else
		strcpy(temp,"None");

	_outtext(temp);

	_settextposition(11,longest+5);

	if (adv->divine_points)
		sprintf(temp,"%u left from %u",adv->current_divine_points,adv->divine_points);
	else
		strcpy(temp,"None");

	_outtext(temp);

	_settextposition(12,longest+5);
	sprintf(temp,fmt,adv->strength,effective_strength(adv));
	_outtext(temp);

	_settextposition(13,longest+5);
	sprintf(temp,fmt,adv->intelligence,effective_intelligence(adv));
	_outtext(temp);

	_settextposition(14,longest+5);
	sprintf(temp,fmt,adv->piety,effective_piety(adv));
	_outtext(temp);

	_settextposition(15,longest+5);
	sprintf(temp,fmt,adv->agility,effective_agility(adv));
	_outtext(temp);

	_settextposition(16,longest+5);
	sprintf(temp,fmt,adv->toughness,effective_toughness(adv));
	_outtext(temp);

	_settextposition(17,longest+5);
	sprintf(temp,fmt,adv->charisma,effective_charisma(adv));
	_outtext(temp);

	_settextposition(18,longest+5);
	sprintf(temp,fmt,adv->luck,effective_luck(adv));
	_outtext(temp);

	_settextposition(19,longest+5);
	sprintf(temp,"%u left from %u",adv->current_hp,adv->hp);
	_outtext(temp);

	draw_adv_image(adv->nclass,273,13);

	y=40;

	if (adv->bane_rune!=TYP_NO_RUNES)
	{
		bane_rune_draw(adv->bane_rune,275,y,FALSE);
		y+=30;
	}

	if (adv->guild_member)
	{
		draw_guild_coa(273,y);
		y+=30;
	}

	if (adv->member_of_HOE)
		draw_HOE_coa(273,y);
}

void _PASCAL near show_adventurer_2(PLAYER *adv)
{
	char temp[80];
	int i,longest=0;
	static char *items2[]={"Languages",
						   "Ethics",
						   "Status",
						   "Height",
						   "Weight",
						   "Age",
						   "Hand",
						   "Birthday",
						   "Birthtown",
						   "Prev Job",
						   "Deity",
						   "Familiar",
						   "Cash",
						   "Banked",
						   "Insurance"};

	cls_show_adventurer();

	_settextcolor(4);

	_settextposition(3,3);

	_outtext("Personal Details (2 of 3)");

	for (i=0; i<SIZE(items2); i++)
		longest=max(longest,(int)strlen(items2[i]));

	for (i=0; i<SIZE(items2); i++)
	{
		strcpy(temp,items2[i]);

		while ((int)strlen(temp)<longest)
			strcat(temp,"\xFA");

		strcat(temp,":");

		_settextcolor(6);
		_settextposition(5+i,3);
		_outtext(temp);
	}

	_settextcolor(3);

	_settextposition(5,longest+5);

	strcpy(temp,"Old Tongue");

	if (adv->languages & LAN_ORCISH)
		strcat(temp,", Orcish");

	if (adv->languages & LAN_OGRISH)
		strcat(temp,", Ogrish");

	if (adv->languages & LAN_DWARFISH)
		strcat(temp,", Dwarven");

	if (adv->languages & LAN_ELVISH)
		strcat(temp,", Elvish");

	if (adv->languages & LAN_GOBLIN)
		strcat(temp,", Goblin");

	if (adv->languages & LAN_UNDERWURLDE)
		strcat(temp,", Underwurlde");

	_outtext(temp);

	_settextposition(6,longest+5);

	if (adv->ethics==LAWFUL)
		_outtext("Lawful");
	else
	if (adv->ethics==NEUTRAL)
		_outtext("Neutral");
	else
		_outtext("Chaotic");

	_settextposition(7,longest+5);


	strcpy(temp,get_adv_status(adv));

	_settextcolor(get_status_colour(adv));
	_outtext(temp);

	_settextcolor(3);
	_settextposition(8,longest+5);
	_outtext(adv->height);

	_settextposition(9,longest+5);
	_outtext(adv->weight);

	_settextposition(10,longest+5);
	sprintf(temp,"%u yrs, %s",adv->nage,adv->age);
	_outtext(temp);

	_settextposition(11,longest+5);
	_outtext((adv->hand==HAND_LEFT?"Left":(adv->hand==HAND_RIGHT?"Right":"Ambidextrous")));

	_settextposition(12,longest+5);
	_outtext(adv->birthday);

	_settextposition(13,longest+5);
	_outtext(adv->where_born);

	_settextposition(14,longest+5);
	_outtext(adv_previous_job(adv));

	_settextposition(15,longest+5);
	if (strnicmp("None",adv->deity_name,4)==0)
	{
		sprintf(temp,"None");
	}
	else
	{
		if (adv->nclass==DRUID)
			sprintf(temp,"%s (%s)",
					adv->deity_name,
					adv->deity_control);
		else
			sprintf(temp,"%s (%s) (%lu)",
					adv->deity_name,
					adv->deity_control,
					days_since_last_pray(adv));
	}

	_outtext(temp);

	_settextposition(16,longest+5);
	strcpy(temp,familiar_type(adv));
	_outtext(temp);

	_settextposition(17,longest+5);
	sprintf(temp,"%lu GC",adv->cash);
	_outtext(temp);

	_settextposition(18,longest+5);
	sprintf(temp,"%lu GC",adv->banked);
	_outtext(temp);

	_settextposition(19,longest+5);
	_outtext(adv->insurance==TRUE?"Yes":"No");
}

void _PASCAL _NEAR show_adventurer_3(PLAYER *adv)
{
	int i,longest=0;
	char temp[80];
	int y;
	int something;
	char *t="%2d (%2d)";
	static char *items3[]={"Attack",
						   "Parry",
						   "Missile",
						   "Disarm Trap",
						   "Find Trap",
						   "Pick Lock",
						   "Listen",
						   "Move Silently",
						   "Disease Immunity",
						   "Poison Immunity",
						   "Heal",
						   "Herb Lore",
						   "Hunt",
						   "Survival",
						   "Swim"
						   };

	static char *items4[]={"Speed:",
						   "Armour:",
						   "# Attacks",
						   "Herbs:"};

	cls_show_adventurer();

	_settextcolor(4);

	_settextposition(3,3);

	_outtext("Personal Details (3 of 3)");

	for (i=0; i<SIZE(items3); i++)
		longest=max(longest,(int)strlen(items3[i]));

	for (i=0; i<SIZE(items3); i++)
	{
		strcpy(temp,items3[i]);

		while ((int)strlen(temp)<longest)
			strcat(temp,"\xFA");

		strcat(temp,":");

		_settextcolor(6);
		_settextposition(5+i,3);
		_outtext(temp);
	}

	_settextposition(5,longest+13);
	_outtext(items4[0]);

	_settextposition(8,longest+13);
	_outtext(items4[1]);

	_settextposition(11,longest+13);
	_outtext(items4[2]);

	_settextposition(14,longest+13);
	_outtext(items4[3]);

	_settextcolor(3);

	_settextposition(6,longest+13);
	sprintf(temp,"%-2d (%-2d)",adv->speed,effective_speed(adv));
	_outtext(temp);

	_settextposition(9,longest+13);
	sprintf(temp,"%-2d, %-2d",effective_ac(adv),effective_ac_back(adv));
	_outtext(temp);

	something=FALSE;

	for (i=0,y=15; i<MAX_HERBS_CARRY;i++)
	{
		if (adv->herbs_carried[i]!=HERB_NONE)
		{
			something=TRUE;

			strcpy(temp,get_herb_name(adv->herbs_carried[i],TRUE));

			_settextposition(y++,longest+13);
			_outtext(temp);
		}
	}

	if (!something)
	{
		_settextposition(15,longest+13);
		_outtext("None!");
	}


	_settextposition(12,longest+13);
	sprintf(temp,"%d",effective_attacks_per_round(adv));
	_outtext(temp);

	_settextposition(5,longest+5);
	sprintf(temp,t,adv->secondary_attrib[ATTACK],effective_attack(adv));
	_outtext(temp);

	_settextposition(6,longest+5);
	sprintf(temp,t,adv->secondary_attrib[PARRY],effective_parry(adv));
	_outtext(temp);

	_settextposition(7,longest+5);
	sprintf(temp,t,adv->secondary_attrib[MISSILE],effective_missile(adv));
	_outtext(temp);

	_settextposition(8,longest+5);
	sprintf(temp,t,adv->secondary_attrib[DISARM_TRAP],effective_disarm_trap(adv));
	_outtext(temp);

	_settextposition(9,longest+5);
	sprintf(temp,t,adv->secondary_attrib[FIND_TRAP],effective_find_trap(adv));
	_outtext(temp);

	_settextposition(10,longest+5);
	sprintf(temp,t,adv->secondary_attrib[PICK_LOCK],effective_pick_lock(adv));
	_outtext(temp);

	_settextposition(11,longest+5);
	sprintf(temp,t,adv->secondary_attrib[LISTEN],effective_listen(adv));
	_outtext(temp);

	_settextposition(12,longest+5);
	sprintf(temp,t,adv->secondary_attrib[MOVE_SILENT],effective_move_silently(adv));
	_outtext(temp);

	_settextposition(13,longest+5);
	sprintf(temp,t,adv->secondary_attrib[IMMUNITY_DISEASE],effective_disease_immunity(adv));
	_outtext(temp);

	_settextposition(14,longest+5);
	sprintf(temp,t,adv->secondary_attrib[IMMUNITY_POISON],effective_poison_immunity(adv));
	_outtext(temp);

	_settextposition(15,longest+5);
	sprintf(temp,t,adv->secondary_attrib[HEAL],effective_heal(adv));
	_outtext(temp);

	_settextposition(16,longest+5);
	sprintf(temp,t,adv->secondary_attrib[HERB_LORE],effective_herb_lore(adv));
	_outtext(temp);

	_settextposition(17,longest+5);
	sprintf(temp,t,adv->secondary_attrib[HUNT],effective_hunt(adv));
	_outtext(temp);

	_settextposition(18,longest+5);
	sprintf(temp,t,adv->secondary_attrib[SURVIVAL],effective_survival(adv));
	_outtext(temp);

	_settextposition(19,longest+5);
	sprintf(temp,t,adv->secondary_attrib[SWIM],effective_swim(adv));
	_outtext(temp);
}

void _PASCAL _NEAR show_adventurer_4(PLAYER *adv)
{
	char temp[80];
	int fin=FALSE;
	int i;
	int count=0;
	int xoff=4;
	int yoff=5;
	int col=6;
	int bottom=15;
	int something=FALSE;
	int mx=xoff+25;
	int my=5;
	static char *v[]={"Food:",
					  "Darts:",
					  "Arrows:",
					  "Quarrels:",
					  "Oil Pots:"};

	cls_show_adventurer();

	_settextcolor(4);
	_settextposition(3,3);
	_outtext("Trappings & Provisions");

	i=0;

	_settextcolor(col);

	while (!fin)
	{
		if (adv->items_carried[i].item!=NOTHING)
			something=TRUE;

		fin=get_full_item_descrip(&adv->items_carried[i],temp);

		if (!fin)
		{
			if (adv->items_carried[i].status==ITEM_HELD)
				tick((xoff-2)*8-2,(yoff+count-1)*8,ON);

			_settextposition(yoff+count,xoff);
			_outtext(temp);

			if (++count>bottom)
				general_low_sound();
		}

		if (++i>MAX_CARRY)
			fin=TRUE;
	}

	for (i=0; i<SIZE(v); i++)
	{
		_settextposition(my+(i*3),mx);
		_outtext(v[i]);
	}

	_settextcolor(3);

	_settextposition(my+1,mx);
	if (adv->food)
		sprintf(temp,"%-d",adv->food);
	else
		strcpy(temp,"None");

	_outtext(temp);

	_settextposition(my+4,mx);
	if (adv->darts)
		sprintf(temp,"%-d",adv->darts);
	else
		strcpy(temp,"None");

	_outtext(temp);


	_settextposition(my+7,mx);
	if (adv->arrows)
		sprintf(temp,"%-d",adv->arrows);
	else
		strcpy(temp,"None");

	_outtext(temp);


	_settextposition(my+10,mx);
	if (adv->quarrels)
		sprintf(temp,"%-d",adv->quarrels);
	else
		strcpy(temp,"None");

	_outtext(temp);


	_settextposition(my+13,mx);
	if (adv->oil)
		sprintf(temp,"%d",adv->oil);
	else
		strcpy(temp,"None");

	_outtext(temp);


	if (!something)
	{
		_settextposition(yoff+6,xoff+1);
		_settextcolor(6);
		_outtext("No Trappings!");

		general_low_sound();
	}
}

void _PASCAL _NEAR show_adventurer_5(PLAYER *adv,int num_spells)
{
	int i,j;
	int xoff=3;
	int yoff=5;
	int col=6;
	int num_spell_pages=(num_spells>15?2:1);
	char temp[40];

	cls_show_adventurer();

	_settextcolor(4);
	_settextposition(3,3);

	_outtext(num_spell_pages==1?"Spells":"Spells (1 of 2)");

	_settextcolor(col);

	if (num_spells!=0)
	{
		for (i=0,j=0; i<min(num_spells,15); i++,j++)
		{
			_settextposition(yoff+i,xoff);
			_outtext(adv_spells[i].descrip);
		}
	}
	else
	{
		if (strlen(adv->name))
			sprintf(temp,"%s hath no spells!",adv->name);
		else
			strcpy(temp,"Thy adventurer hath no spells!");

		_settextposition(yoff+6,20-strlen_half(temp));
		_settextcolor(6);

		_outtext(temp);

		general_low_sound();
	}
}

void _PASCAL _NEAR show_adventurer_6(int num_spells)
{
	int i,j;
	int xoff=3;
	int yoff=5;
	int col=6;

	cls_show_adventurer();

	_settextcolor(4);
	_settextposition(3,3);

	_outtext("Spells (2 of 2)");

	_settextcolor(col);

	for (i=15,j=0; i<num_spells; i++,j++)
	{
		_settextposition(yoff+i-15,xoff);
		_outtext(adv_spells[i].descrip);
	}
}

int _PASCAL get_full_item_descrip(ITEM_POOL *item,char *temp)
{
	int fin=FALSE;

	switch(item->item)
	{
		case LEATHER_ARMOUR     : strcpy(temp,STR_LEATHER_ARMOUR);      break;
		case SPLINT_ARMOUR      : strcpy(temp,STR_SPLINT_ARMOUR);       break;
		case CHAIN_ARMOUR       : strcpy(temp,STR_CHAIN_ARMOUR);        break;
		case PLATE_ARMOUR       : strcpy(temp,STR_PLATE_ARMOUR);        break;
		case ELF_ARMOUR         : strcpy(temp,STR_ELF_ARMOUR);          break;
		case DAGGER 			:
		case AXE				:
		case SHORT_SWORD		:
		case LONG_SWORD 		:
		case RAPIER 			:
		case CLAYMORE			:
		case MACE				:
		case FLAIL				:
		case BOW				:
		case CROSSBOW			:
		case HALBERD			:
		case SLING				: strcpy(temp,get_weapon_name(item->item));
								  break;

		case SACK               : strcpy(temp,STR_SACK);                break;
		case BACK_PACK          : strcpy(temp,STR_BACK_PACK);           break;
		case TINDER_BOX         : strcpy(temp,STR_TINDER_BOX);          break;
		case HEAVY_CLOAK        : strcpy(temp,STR_HEAVY_CLOAK);         break;
		case HOODED_LANTERN     : strcpy(temp,STR_HOODED_LANTERN);      break;
		case THIEVES_TOOLS      : strcpy(temp,STR_THIEVES_TOOLS);       break;
		case RELIGIOUS_SYMBOL   : strcpy(temp,STR_RELIGIOUS_SYMBOL);    break;
		case LUTE				: strcpy(temp,STR_LUTE);				break;
		case GRIMOIRE			: strcpy(temp,STR_GRIMOIRE);			break;
		case SEXTANT			: strcpy(temp,STR_SEXTANT); 			break;
		case SMALL_SHIELD       : strcpy(temp,STR_SMALL_SHIELD);        break;
		case LARGE_SHIELD       : strcpy(temp,STR_LARGE_SHIELD);        break;
		case MEDIUM_SHIELD      : strcpy(temp,STR_MEDIUM_SHIELD);       break;
		case HELMET             : strcpy(temp,STR_HELMET);              break;
		case WYVERN_RING        : strcpy(temp,STR_WYVERN_RING);         break;
		case DRAGON_RING        : strcpy(temp,STR_DRAGON_RING);         break;
		case RING_OF_HEALING    : strcpy(temp,STR_RING_OF_HEALING);     break;
		case MIND_SHIELD_RING   : strcpy(temp,STR_MIND_SHIELD_RING);    break;
		case RING_OF_FIRE       : strcpy(temp,STR_RING_OF_FIRE);        break;
		case RING_OF_ICICLES    : strcpy(temp,STR_RING_OF_ICICLES);     break;
		case RING_OF_SWIMMING   : strcpy(temp,STR_RING_OF_SWIMMING);    break;
		case WARMTH_RING        : strcpy(temp,STR_WARMTH_RING);         break;
		case THUNDER_WAND       : strcpy(temp,STR_THUNDER_WAND);        break;
		case ICE_WAND           : strcpy(temp,STR_ICE_WAND);            break;
		case FIRE_WAND          : strcpy(temp,STR_FIRE_WAND);           break;
		case HEALING_STAVE      : strcpy(temp,STR_HEALING_STAVE);       break;
		case SUSTENANCE_WAND    : strcpy(temp,STR_SUSTENANCE_WAND);     break;
		case DEVOURING_ROD      : strcpy(temp,STR_DEVOURING_ROD);       break;
		case ORB_TITAN          : strcpy(temp,STR_ORB_TITAN);           break;
		case ORB_DEXTERITY      : strcpy(temp,STR_ORB_DEXTERITY);       break;
		case ORB_WISE           : strcpy(temp,STR_ORB_WISE);            break;
		case ORB_FORTUNE        : strcpy(temp,STR_ORB_FORTUNE);         break;
		case ORB_MEDITATION     : strcpy(temp,STR_ORB_MEDITATION);      break;
		case ORB_STAMINA        : strcpy(temp,STR_ORB_STAMINA);         break;
		case ORB_BEAUTY         : strcpy(temp,STR_ORB_BEAUTY);          break;
		case RELIC              : strcpy(temp,STR_RELIC);               break;
		case TOME				: strcpy(temp,STR_TOME);				break;
		case CURIOUS_BOX		: strcpy(temp,STR_CURIOUS_BOX); 		break;
		case ELFIN_CLOAK        : strcpy(temp,STR_ELFIN_CLOAK);         break;
		case ELFIN_BOOTS        : strcpy(temp,STR_ELFIN_BOOTS);         break;
		case BRACERS_POISON     : strcpy(temp,STR_BRACERS_POISON);      break;
		case PENDANT_HEALTH     : strcpy(temp,STR_PENDANT_HEALTH);      break;
		case GLOVES_NIMBLENESS  : strcpy(temp,STR_GLOVES_NIMBLENESS);   break;
		case POTION             : strcpy(temp,"Potion");                break;
		default                 : fin=TRUE;                             break;
	}

	if (!fin)
	{
		switch(item->item)
		{
			case LEATHER_ARMOUR     :
			case SPLINT_ARMOUR      :
			case CHAIN_ARMOUR       :
			case PLATE_ARMOUR       :
			case ELF_ARMOUR         :
			case DAGGER             :
			case AXE                :
			case SHORT_SWORD        :
			case LONG_SWORD         :
			case RAPIER             :
			case CLAYMORE           :
			case MACE               :
			case FLAIL              :
			case BOW                :
			case CROSSBOW           :
			case HALBERD            :
			case SMALL_SHIELD       :
			case MEDIUM_SHIELD      :
			case LARGE_SHIELD       :
			case HELMET             :   switch(item->type)
										{
											case PLUS_1     :   strcat(temp," (+1)");    break;
											case PLUS_2     :   strcat(temp," (+2)");    break;
											case PLUS_3     :   strcat(temp," (+3)");    break;
											default         :   break;
										}

										if (item->poisoned)
											strcat(temp," (P)");

										break;

			case POTION             :   strcat(temp,potion_get_colour(item->type,TRUE));
										break;

			default                 :   break;
		}
	}

	return(fin);
}

char *adv_title(PLAYER *adv)
{
	static char *t;

	if (adv->level<TITLE_LEVEL)
		return(adv->class);

	switch(adv->nclass)
	{
		case DUELIST    : t="Master Duelist";    break;
		case HUNTER     : t="Master Hunter";     break;
		case DRUID      : t="Hierophant Druid";  break;
		case PRIEST     : t="High Priest";       break;
		case BARD       : t="Bard Loremaster";   break;
		case WARRIOR    : t="Warrior Knight";    break;
		case RANGER     : t="Ranger Lord";       break;
		case CRUSADER   : t="Crusader Knight";   break;
		case WIZARD     : t="Archmage";          break;
		case ILLUSIONIST: t="Mystic Illusionist";break;
		case MONK       : t="Great Monk";        break;
		case THIEF      : t="Master Thief";      break;
		default         : t=adv->class;          break;
	}

	if (adv->sex==SX_FEMALE)
	{
		switch(adv->nclass)
		{
			case HUNTER 	: t="Master Huntress";	break;
			case PRIEST 	: t="High Priestess";	break;
			case RANGER 	: t="Ranger Lady";		break;
			case WARRIOR	: t="Warrior Lady"; 	break;
			default 		: break;
		}
	}

	return(t);
}

char *adv_previous_job(PLAYER *adv)
{
	switch(adv->previous_job)
	{
		case PJ_BODYGUARD	   : return("Bodyguard");
		case PJ_MILITIAMAN	   : return("Militiaman");
		case PJ_OUTLAW		   : return("Outlaw");
		case PJ_BOUNTY_HUNTER  : return("Bounty Hunter");
		case PJ_PROSPECTOR	   : return("Prospector");
		case PJ_HYPNOTIST      : return("Hypnotist");
		case PJ_ALCHEMIST_APP  : return("Apprentice Alchemist");
		case PJ_WIZARD_APP	   : return("Apprentice Wizard");
		case PJ_EXCISEMAN	   : return("Exciseman");
		case PJ_LIBRARIAN	   : return("Librarian");
		case PJ_HERBALIST	   : return("Herbalist");
		case PJ_FORESTER	   : return("Forester");
		case PJ_CLERIC		   : return("Cleric");
		case PJ_GRAVE_ROBBER   : return("Grave Robber");
		case PJ_PEDLAR		   : return("Pedlar");
		case PJ_RAT_CATCHER    : return("Rat Catcher");
		case PJ_LABOURER	   : return("Labourer");
		case PJ_PIT_FIGHTER    : return("Pit Fighter");
		case PJ_SOLDIER 	   : return("Soldier");
		case PJ_GAMEKEEPER	   : return("Gamekeeper");
		case PJ_TRAPPER 	   : return("Trapper");
		case PJ_SEER		   : return("Seer");
		case PJ_STUDENT 	   : return("Student");
		case PJ_PHARMACIST	   : return("Pharmacist");
		case PJ_ENGINEER	   : return("Engineer");
		case PJ_TEACHER 	   : return("Teacher");
		case PJ_HUSBANDMAN	   : return("Husbandman");
		case PJ_WOODSMAN	   : return("Woodsman");
		case PJ_BEGGAR		   : return("Beggar");
		case PJ_FOOTPAD 	   : return("Footpad");
		case PJ_SMUGGLER	   : return("Smuggler");
		case PJ_OUTRIDER	   : return("Outrider");
		case PJ_MERCENARY	   : return("Mercenary");
		case PJ_WATCHMAN	   : return("Watchman");
		case PJ_STREET_FIGHTER : return("Street Fighter");
		case PJ_POACHER 	   : return("Poacher");
		case PJ_SCRIBE		   : return("Scribe");
		case PJ_TRADER		   : return("Trader");
		case PJ_ARTISAN_APP    : return("Apprentice Artisan");
		case PJ_INITIATE	   : return("Initiate");
		case PJ_JEWELLER	   : return("Jeweller");
		case PJ_SQUIRE		   : return("Squire");
		case PJ_GAMBLER 	   : return("Gambler");
		case PJ_JAILER		   : return("Jailer");
		case PJ_TOMB_ROBBER    : return("Tomb Robber");
		case PJ_RUSTLER 	   : return("Rustler");
		default                : return("Spy");
	}
}
