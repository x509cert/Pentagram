#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <bstrings.h>


void _PASCAL drink_or_taste_potion()
{
	int num;
	GWINDOW win;
	int select;
	char *t2="TDQ";
	static int boundary[]={125,40,241,53,
						   125,60,241,76,
						   170,77,205,89,
							-1,-1,-1,-1};

	win.x1=15;
	win.y1=5;
	win.x2=33;
	win.y2=13;
	win.border=4;
	win.back=0;

	num=adv_select_adventurer("Who uses","a Potion?",TRUE);

	if (num==ERR)
		return;

	if (bard_is_singing(&TPP[num],"use a potion"))
		return;

	make_gwindow(&win);

	click_box(170,77,B_QUIT);
	generic_pic_draw(win.x1*8+7,win.y1*8,"POTNWHAT");

	select=mouse_in_range(boundary,t2,"");

	kill_gwindow(&win);

	if (select!=2)
		get_potion_to_drink(&TPP[num],select?DRINK_POTION:TASTE_POTION);
}

int _PASCAL get_potion_to_drink(PLAYER *adv,int do_what)
{
	GWINDOW win;
	int i,j;
	int num_items;
	static char temp[80];
	int fin;
	static USE_SWAP items[MAX_CARRY];
	int select;
	static int boundary[]={32, 56,210, 62,
						   32, 64,210, 70,
						   32, 72,210, 78,
						   32, 80,210, 86,
						   32, 88,210, 94,
						   32, 96,210,102,
						   32,104,210,110,
						   32,112,210,118,
						   32,120,210,126,
						   32,128,210,134,
						   32,136,210,142,
						   32,144,210,150,
						   98,158,133,170,
							-1,-1,-1,-1};

	if (bard_is_singing(adv,"imbibe a potion"))
		return(FALSE);

	win.x1=4;
	win.y1=6;
	win.x2=28;
	win.y2=win.y1+5+MAX_CARRY;
	win.back=0;
	win.border=3;

	for (i=0,num_items=ERR; i<MAX_CARRY; i++)
	{
		j=adv->items_carried[i].item;

		if (j==POTION)
		{
			num_items++;

			strcpy(temp,potion_get_colour(adv->items_carried[i].type,FALSE));

			items[num_items].bit=adv->items_carried[i];
			strcpy(items[num_items].desc,temp);
		}
	}

	if (num_items==ERR)
	{
		sprintf(temp,"%s hath no potions!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	make_gwindow(&win);

	click_box(98,158,B_QUIT);

	_settextposition(win.y1+1,win.x1+2);
	_settextcolor(14);
	_outtext("Select Potion to Use");

	for (i=0; i<=num_items; i++)
	{
		_settextcolor(13);
		sprintf(temp,"%cù",i+'A');
		_settextposition(win.y1+2+i,win.x1+1);
		_outtext(temp);

		_settextcolor(5);
		_settextposition(win.y1+2+i,win.x1+3);
		_outtext(items[i].desc);
	}

	fin=FALSE;

	while (!fin)
	{
		select=mouse_in_range(boundary,"ABCDEFGHIJKLQ","");

		if ((select>num_items) && (select!=12))
			continue;

		fin=TRUE;
	}

	kill_gwindow(&win);

	if (select!=12)
	{
		if (do_what==DRINK_POTION)
		{
			potion_down_the_hatch_drink(adv,items[select].bit.type);
			potion_remove_from_player(adv,items[select].bit.type);

			num_items=ERR;
		}
		else
			potion_down_the_hatch_taste(adv,
										items[select].bit.type,
										items[select].desc);
	}

	return(select==12?FALSE:TRUE);
}

void _PASCAL potion_remove_from_player(PLAYER *adv,int potion)
{
	int i;

	for (i=0; i<MAX_CARRY; i++)
	{
		if (adv->items_carried[i].item==POTION &&
			adv->items_carried[i].type==(unsigned)potion)
		{
			adv->items_carried[i].item	   = NOTHING;
			adv->items_carried[i].type	   = 0;
			adv->items_carried[i].status   = ITEM_CARRIED;
			adv->items_carried[i].poisoned = FALSE;

			break;
		}
	}
}

void _PASCAL potion_down_the_hatch_drink(PLAYER *adv,int type)
{
	char *drink;

	switch(rand()%4)
	{
		case 0 : drink="drinks"; break;
		case 1 : drink="quaffs"; break;
		case 2 : drink="gulps";  break;
		default: drink="swigs";  break;
	}

	switch(type)
	{
		case POT_SECRET_DOOR : drink_POT_SECRET_DOOR(adv,drink,"Potion of Secret Door Detection"); break;
		case POT_STRENGTH    : drink_POT_STRENGTH(adv,drink,"Potion of Strength");                 break;
		case POT_STRIKING    : drink_POT_STRIKING(adv,drink,"Potion of Striking");                 break;
		case POT_UNDEAD_TURN : drink_POT_UNDEAD_TURN(adv,drink,"Potion of Undead Turning");        break;
		case POT_FIRE_RESIST : drink_POT_FIRE_RESIST(adv,drink,"Potion of Fire Resistance");       break;
		case POT_COLD_RESIST : drink_POT_COLD_RESIST(adv,drink,"Potion of Cold Resistance");       break;
		case POT_HEALING     : drink_POT_HEALING(adv,drink,"Potion of Healing");                   break;
		case POT_REVIVING    : drink_POT_REVIVING(adv,drink,"Potion of Reviving");                 break;
		case POT_POISON      : drink_POT_POISON(adv,drink,"Vial of Poison");                       break;
		case POT_HOLYWATER   : drink_POT_HOLYWATER(adv,drink,"Vial of Holy Water");                break;
		case POT_NOTHING     : drink_POT_NOTHING(adv,drink,"Potion");                              break;
		case POT_CURE_DISEASE: drink_POT_CURE_DISEASE(adv,drink,"Potion of Cure Disease");         break;
		case POT_ALCOHOL	 : drink_POT_ALCOHOL(adv,drink,"Potion of Alcohol");				   break;
		default              : break;
	}
}

void _PASCAL drink_POT_SECRET_DOOR(PLAYER *adv, char *verb, char *name)
{
	char temp[120];
	int hidden_door_count=0;
	int res;

	sprintf(temp,"%s %s ye %s %s.",
				adv->name,
				verb,
				potion_get_colour(POT_SECRET_DOOR,FALSE),
				name);

	print_potion_description(temp,GOOD);

	pause(1);

	if (!IN_DUNGEON)
	{
		print_potion_description("But naught seems to happen!",BAD);
	}
	else
	{
		hidden_door_count=number_of_hidden_doors();

		if (hidden_door_count)
		{
			if (hidden_door_count==1)
				strcpy(temp,"\"There is a hidden door within thy vicinity!\"");
			else
				sprintf(temp,"\"There art %d hidden doors within thy vicinity!\"",
							hidden_door_count);

			res=GOOD;
		}
		else
		{
			strcpy(temp,"\"There art no hidden doors nearby...\"");
			res=BAD;
		}

		print_potion_description(temp,res);
	}
}

void _PASCAL drink_POT_STRENGTH(PLAYER *adv,char *verb,char *name)
{
	char temp[120];

	adv->in_effect.pot_strength+=POT_DURATION;

	sprintf(temp,"%s %s ye %s %s increasing %s strength to %d.",
				adv->name,
				verb,
				potion_get_colour(POT_STRENGTH,FALSE),
				name,
				adv->his_her,
				effective_strength(adv));

	print_potion_description(temp,GOOD);
}

void _PASCAL drink_POT_STRIKING(PLAYER *adv,char *verb,char *name)
{
	char temp[120];

	adv->in_effect.pot_striking+=POT_DURATION;

	sprintf(temp,"%s %s ye %s %s and %s melee ability seems to increase!",
				adv->name,
				verb,
				potion_get_colour(POT_STRIKING,FALSE),
				name,
				adv->his_her);

	print_potion_description(temp,GOOD);
}

void _PASCAL drink_POT_UNDEAD_TURN(PLAYER *adv,char *verb,char *name)
{
	char temp[120];

	if (adv->nclass!=PRIEST && adv->nclass!=CRUSADER)
	{
		sprintf(temp,"%s %s ye %s potion, but naught seems to happen!",
				adv->name,
				verb,
				potion_get_colour(POT_UNDEAD_TURN,FALSE));

		print_potion_description(temp,BAD);
	}
	else
	{
		adv->in_effect.pot_undead_turn+=POT_DURATION;

		sprintf(temp,"%s %s ye %s %s and %s undead turning ability seems to increase!",
					adv->name,
					verb,
					potion_get_colour(POT_UNDEAD_TURN,FALSE),
					name,
					adv->his_her);

		print_potion_description(temp,GOOD);
	}
}

void _PASCAL drink_POT_FIRE_RESIST(PLAYER *adv,char *verb,char *name)
{
	char temp[120];

	adv->in_effect.pot_fire_resist+=POT_DURATION;

	sprintf(temp,"%s %s ye %s %s.",
				adv->name,
				verb,
				potion_get_colour(POT_FIRE_RESIST,FALSE),
				name);

	print_potion_description(temp,GOOD);
}

void _PASCAL drink_POT_COLD_RESIST(PLAYER *adv,char *verb,char *name)
{
	char temp[120];

	adv->in_effect.pot_cold_resist+=POT_DURATION;

	sprintf(temp,"%s %s ye %s %s.",
				adv->name,
				verb,
				potion_get_colour(POT_COLD_RESIST,FALSE),
				name);

	print_potion_description(temp,GOOD);
}

void _PASCAL drink_POT_HEALING(PLAYER *adv,char *verb,char *name)
{
	char temp[120];
	char effect[20];
	int hp=adv->hp;
	int healed;
	int current_hp=adv->current_hp;

	if (hp==current_hp)
	{
		sprintf(temp,"Ye %s hath no effect on %s!",
					name,
					adv->name);

		print_potion_description(temp,BAD);
	}
	else
	{
		healed=get_dice_roll(12,1,adv->level);

		adv->current_hp=min(adv->current_hp+healed,adv->hp);

		if (adv->current_hp==hp)
			strcpy(effect,"all");
		else
			sprintf(effect,"%d hp of",healed);

		sprintf(temp,"%s %s ye %s, healing %s physical damage!",
					adv->name,
					verb,
					name,
					effect);

		print_potion_description(temp,GOOD);
	}
}

void _PASCAL drink_POT_REVIVING(PLAYER *adv,char *verb,char *name)
{
	char temp[120];
	char effect[20];
	int pt;
	int cp;
	int no_effect=FALSE;
	int sorcery_type;
	int healed;

	switch(adv->nclass)
	{
		case PRIEST         :
		case CRUSADER       :
		case DRUID          :
		case HUNTER         :   sorcery_type=FALSE;
								pt=adv->divine_points;
								cp=adv->current_divine_points;
								break;
		case MONK           :
		case RANGER         :
		case WIZARD         :
		case ILLUSIONIST    :   sorcery_type=TRUE;
								pt=adv->sorcery_points;
								cp=adv->current_sorcery_points;
								break;

		default             :   no_effect=TRUE;
								sorcery_type=FALSE;
								break;
	}

	if (pt==cp || no_effect)
	{
		sprintf(temp,"Ye %s hath no effect on %s!",
					name,
					adv->name);

		print_potion_description(temp,BAD);
	}
	else
	{
		healed=get_dice_roll(12,1,adv->level);

		if (sorcery_type)
		{
			adv->current_sorcery_points=
					min(adv->current_sorcery_points+healed,
						adv->sorcery_points);

			if (adv->current_sorcery_points==pt)
				strcpy(effect,"all");
			else
				sprintf(effect,"%d",healed);
		}
		else
		{
			adv->current_divine_points=
					min(adv->current_divine_points+healed,
						adv->divine_points);

			if (adv->current_divine_points==pt)
				strcpy(effect,"all");
			else
				sprintf(effect,"%d",healed);
		}

		sprintf(temp,"%s %s ye %s, gaining %s %s points!",
					adv->name,
					verb,
					name,
					effect,
					sorcery_type?"sorcery":"divine");

		print_potion_description(temp,GOOD);
	}
}

void _PASCAL drink_POT_POISON(PLAYER *adv,char *verb,char *name)
{
	char temp[80];

	player_has_died_set(adv);

	sprintf(temp,"Instantly %s falls over...dead!",adv->name);

	if (!IN_COMBAT)
	{
		SCROLL(1,0,temp);
	}
	else
	{
		combat_write(4,temp,TRUE);
	}

	solemn_sound();
}

void _PASCAL drink_POT_HOLYWATER(PLAYER *adv,char *verb,char *name)
{
	char temp[100];

	adv->in_effect.pot_holy_water+=POT_DURATION;
	adv->in_effect.pot_holy_water+=rand()*20;

	sprintf(temp,"%s %s ye Holy Water!",
				adv->name,
				verb);

	print_potion_description(temp,GOOD);
}

void _PASCAL drink_POT_NOTHING(PLAYER *adv,char *verb,char *name)
{
	char temp[120];

	sprintf(temp,"%s %s ye %s %s, but naught seems to happen!",
					adv->name,
					verb,
					potion_get_colour(POT_NOTHING,FALSE),
					name);

	print_potion_description(temp,BAD);
}

void _PASCAL drink_POT_CURE_DISEASE(PLAYER *adv,char *verb,char *name)
{
	char temp[120];
	char *disease;

	sprintf(temp,"%s %s ye %s %s.",
				adv->name,
				verb,
				potion_get_colour(POT_CURE_DISEASE,FALSE),
				name);

	print_potion_description(temp,GOOD);

	pause(1);

	if (adv->disease==NO_DISEASE)
	{
		sprintf(temp,"But naught seems to happen to %s!",adv->him_her);
		print_potion_description(temp,BAD);
	}
	else
	{
		switch(adv->disease)
		{
			case GRAVE_ROT  : disease="Grave Rot"; break;
			case POX        : disease="ye Pox";    break;
			case PLAGUE     : disease="ye Plague"; break;
		}

		recover_from_disease(adv);

		sprintf(temp,"..Curing %s of %s!",adv->him_her,disease);
		print_potion_description(temp,GOOD);
	}
}

void _PASCAL drink_POT_ALCOHOL(PLAYER *adv,char *verb,char *name)
{
	char temp[120];

	adv->drunkeness=adv->max_drunkeness;

	sprintf(temp,"%s %s ye %s %s and utters, \"Thish ish a good poshun!\"",
				adv->name,
				verb,
				potion_get_colour(POT_ALCOHOL,FALSE),
				name);

	print_potion_description(temp,BAD);

	pause(1);
}

void _PASCAL potion_down_the_hatch_taste(PLAYER *adv,int type,char *desc)
{
	char temp1[80];
	static char temp2[120];
	char *verb;
	char *potion;
	char *taste;
	int good;
	char *naught="but naught seems to happen!";
	static char *v[]={"sips","tastes","samples","drinks a little of"};

	if (type==POT_HOLYWATER || type==POT_POISON)
		potion="";
	else
		potion="potion ";

	verb=v[rand()%SIZE(v)];

	switch(type)
	{
		case POT_SECRET_DOOR  : taste="salty";	   break;
		case POT_STRENGTH	  : taste="sour";	   break;
		case POT_CURE_DISEASE :
		case POT_UNDEAD_TURN  : taste="sweet";     break;
		case POT_STRIKING     :
		case POT_ALCOHOL      :
		case POT_FIRE_RESIST  : taste="bitter";    break;
		case POT_COLD_RESIST  : taste="tasteless"; break;
		case POT_HEALING	  :
		case POT_REVIVING	  :
		case POT_POISON 	  :
		case POT_HOLYWATER	  : taste="";		   break;
		case POT_NOTHING	  : taste="acrid";	   break;
	}

	sprintf(temp1,"%s %s ye %s %s %s..",adv->name,verb,desc,taste,potion);
	stpcvt(temp1,REDUCE);

	switch(type)
	{
		case POT_SECRET_DOOR    :   sprintf(temp2,"and for a moment a vision of an oaken door appears.");
									good=TRUE;
									break;

		case POT_STRENGTH		:	sprintf(temp2,"and %s has a feeling of renewed vigour!",
									adv->he_she);
									good=TRUE;
									break;

		case POT_STRIKING		:	sprintf(temp2,"and %s feels violent!",
									adv->he_she);
									good=TRUE;
									break;

		case POT_UNDEAD_TURN	:	sprintf(temp2,"and %s tastes garlic in %s mouth!",
									adv->he_she,adv->his_her);
									good=TRUE;
									break;

		case POT_FIRE_RESIST    :   sprintf(temp2,"sending a chill up %s spine!",
									adv->his_her);
									good=TRUE;
									break;

		case POT_COLD_RESIST    :   sprintf(temp2,"leaving a bit of a sweat on %s brow.",
									adv->his_her);
									good=TRUE;
									break;

		case POT_HEALING		:	if (adv->current_hp==adv->hp)
									{
										strcpy(temp2,naught);
										good=FALSE;
									}
									else
									{
										sprintf(temp2,"and %s feels healthier.",
										adv->he_she);
										good=TRUE;
									}

									break;

		case POT_REVIVING		:	if (adv->nclass==WARRIOR || adv->nclass==THIEF ||
										adv->nclass==BARD	 || adv->nclass==DUELIST)
									{
										strcpy(temp2,naught);
										good=FALSE;
									}
									else
									{
										sprintf(temp2,"%s now feels magically inclined!",
										adv->he_she);
										good=TRUE;
									}

									break;

		case POT_POISON 		:	sprintf(temp2,"\n\n..aaarrrgggg! %s drops to "
												  "ye floor. After a while, %s "
												  "gets to %s feet, feeling weaker!",
											adv->name,
											adv->he_she,
											adv->his_her);

									good=FALSE;

									reduce_hp(adv,get_dice_roll(adv->level,1,1),FROM_POISON);
									adv->is_poisoned=TRUE;

									break;

		case POT_HOLYWATER		:	if (adv->ethics==CHAOTIC)
									{
										sprintf(temp2,"\n..aarrggh! %s falls over in agony! "
													  "Finally, %s stands up, feeling weaker!",
												 adv->name,
												 adv->he_she);

										good=FALSE;

										reduce_hp(adv,get_dice_roll(adv->level,1,1),FROM_POISON);
									}
									else
									{
										sprintf(temp2,"and %s feels more at ease.",
										adv->he_she);
										good=TRUE;
									}

									break;

		case POT_NOTHING		:	strcpy(temp2,naught);
									good=FALSE;
									break;

		case POT_ALCOHOL		:	sprintf(temp2,"and %s feels very lightheaded!",adv->he_she);
									good=FALSE;
									break;

		case POT_CURE_DISEASE	:	if (adv->disease==NO_DISEASE)
									{
										strcpy(temp2,naught);
										good=FALSE;
									}
									else
									{
										sprintf(temp2,"and begins to feel better.");
										good=TRUE;
									}

									break;

		default                 :   break;
	}

	if (player_is_alive(adv))
	{
		SCROLL(1,14,temp1);
		general_low_sound();
		pause(1);

		SCROLL(1,good?14:0,temp2);

		if (good)
			good_sound();
		else
			bad_sound();
	}
}

void _PASCAL give_potion_to_player(PLAYER *adv,int potion_type)
{
	add_to_player(POTION,potion_type,FALSE,ITEM_CARRIED,adv);
}

void _PASCAL print_potion_description(char *mess,int sound)
{
	if (!IN_COMBAT)
	{
		SCROLL(1,sound==GOOD?14:0,mess);
	}
	else
		combat_write(sound==GOOD?14:4,mess,TRUE);

	if (sound==GOOD)
		potion_sound();
	else
		bad_sound();
}
