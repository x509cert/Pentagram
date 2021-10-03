#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

int _PASCAL swap_item_get_people(int *from,int *to)
{
	GWINDOW win;
	static int boundary[]={132, 38,176, 66,
						   198, 38,232, 66,
						   132, 78,176,106,
						   198, 78,232,106,
						   132,120,176,146,
						   198,120,232,146,
						   170,162,205,174,
						   -1,-1,-1,-1};
	int select;
	char temp[80];
	int xpos, ypos;
	int fin=FALSE;
	int error=TRUE;

	*from=*to=ERR;

	win.x1=16;
	win.y1=2;
	win.x2=32;
	win.y2=24;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+1);
	_outtext("Who art giving");
	_settextposition(win.y1+2,win.x1+1);
	_outtext("    ye item?  ");

	adv_arrange_draw();
	click_box(170,162,B_QUIT);

	while (!fin)
	{
		select=mouse_in_range(boundary,"123456Q","");

		if (select==6)
		{
			fin=TRUE;
			error=TRUE;

			*from=ERR;
			*to=ERR;
		}
		else
		{
			if (select>P_NUM)
			{
				bad_sound2();
				continue;
			}

			if (*from==ERR)
			{
				*from=select;

				switch(*from)
				{
					case 0 :    xpos=145; ypos=40;  break;
					case 1 :    xpos=205; ypos=40;  break;
					case 2 :    xpos=145; ypos=80;  break;
					case 3 :    xpos=205; ypos=80;  break;
					case 4 :    xpos=145; ypos=120; break;
					case 5 :    xpos=205; ypos=120; break;
				}

				sprintf(temp,"  %s",TPP[*from].name);

				write_little(temp,
							 (xpos+8)-(strlen(temp)*4)/2,
							 ypos+22,
							 15,
							 FAST);

				_settextposition(win.y1+1,win.x1+1);
				_outtext("   Who wants  ");
			}
			else
			{
				*to=select;
				fin=TRUE;
			}

			error=FALSE;
		}

		if (*from==*to && *from!=ERR && *to!=ERR)
		{
			sprintf(temp,"%s can't give an item to %sself!",
					TPP[*from].name,
					TPP[*from].him_her);

			GX(temp,BAD);

			fin=TRUE;
			error=TRUE;

			*from=ERR;
			*to=ERR;
		}
		else
		if (*from==ERR && *to==ERR)
		{
			fin=TRUE;
			error=TRUE;
		}
		else
		if (*to!=ERR				  &&
			*from!=ERR				  &&
			player_is_dead(&TPP[*to]) &&
			player_is_dead(&TPP[*from]))
		{
			sprintf(temp,"%s and %s are dead!",TPP[*to].name,TPP[*from].name);

			GX(temp,SOLEMN);

			fin=TRUE;
			error=TRUE;

			*from=ERR;
			*to=ERR;
		}
		else
		if (*from!=ERR && *to!=ERR)
		{
			fin=TRUE;
			error=FALSE;
		}
	}

	kill_gwindow(&win);

	return(error);
}

void _PASCAL select_swap_type(int f,int t)	 /* Select consumable or not ! */
{
	GWINDOW win,win2;
	static char temp[80];
	PLAYER *from,*to;
	int fin=FALSE;
	int i;
	char *t2="FHOAUDGIQ";
	static int boundary[]={ 40,48, 150,54,
							40,56, 150,62,
							40,64, 150,70,
							40,72, 150,78,
							40,80, 150,86,
							40,88, 150,94,
							40,96, 150,102,
							40,104,150,110,
							76,118,111,128,
							-1,-1,-1,-1};
	static struct no_tag {
							int  offset;
							char *letter;

						  } list[]={1,"F",
									1,"H",
									1,"O",
									1,"A",
									2,"u",
									1,"D",
									1,"G",
									7,"I"};

	from = &TPP[f];
	to   = &TPP[t];

	sprintf(temp,"From %s to %s",from->name,
								 to->name);

	win2.x1=18-strlen_half(temp);
	win2.y1=2;
	win2.x2=22+strlen_half(temp);
	win2.y2=5;
	win2.back=0;
	win2.border=5;

	make_gwindow(&win2);

	_settextcolor(13);
	_settextposition(win2.y1+1,20-strlen_half(temp));
	_outtext(temp);

	win.x1=5;
	win.y1=6;
	win.x2=win.x1+16;
	win.y2=win.y1+12;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	click_box(76,116,B_QUIT);

	while (!fin)
	{
		from = &TPP[f];
		to   = &TPP[t];

		_settextcolor(5);

		_settextposition(win.y1+1,win.x1+1);
		sprintf(temp,"Food      (%2d)",from->food);
		_outtext(temp);

		_settextposition(win.y1+2,win.x1+1);
		sprintf(temp,"Herbs     (%2d)",adv_num_herbs(from));
		_outtext(temp);

		_settextposition(win.y1+3,win.x1+1);
		sprintf(temp,"Oil       (%2d)",from->oil);
		_outtext(temp);

		_settextposition(win.y1+4,win.x1+1);
		sprintf(temp,"Arrows    (%2d)",from->arrows);
		_outtext(temp);

		_settextposition(win.y1+5,win.x1+1);
		sprintf(temp,"Quarrels  (%2d)",from->quarrels);
		_outtext(temp);

		_settextposition(win.y1+6,win.x1+1);
		sprintf(temp,"Darts     (%2d)",from->darts);
		_outtext(temp);

		_settextposition(win.y1+7,win.x1+1);
		sprintf(temp,"Gold    (%4lu)",
					from->cash>(long)MAX_GOLD_SWAP?(long)MAX_GOLD_SWAP
												  :(long)from->cash);
		_outtext(temp);

		_settextposition(win.y1+8,win.x1+1);
		_outtext("Other Items");

		_settextcolor(13);

		for (i=0; i<SIZE(list); i++)
		{
			_settextposition(win.y1+1+i,win.x1+list[i].offset);
			_outtext(list[i].letter);
		}

		switch(mouse_in_range(boundary,t2,""))
		{
			case 0 :    if (from->food)
							actually_swap_item_multiple(f,t,SWAP_FOOD);
						else
						{
							sprintf(temp,"%s hath no food to give!",from->name);
							GX(temp,BAD);
						}

						break;

			case 1 :    if (adv_num_herbs(from))
							actually_swap_herbs(f,t);
						else
						{
							sprintf(temp,"%s hath no herbs to give!",from->name);
							GX(temp,BAD);
						}
						break;

			case 2 :    if (from->oil)
							actually_swap_item_multiple(f,t,SWAP_OIL);
						else
						{
							sprintf(temp,"%s hath no oil to give!",from->name);
							GX(temp,BAD);
						}

						break;

			case 3 :    if (from->arrows)
							actually_swap_item_multiple(f,t,SWAP_ARROWS);
						else
						{
							sprintf(temp,"%s hath no arrows to give!",from->name);
							GX(temp,BAD);
						}

						break;

			case 4 :    if (from->quarrels)
							actually_swap_item_multiple(f,t,SWAP_QUARRELS);
						else
						{
							sprintf(temp,"%s hath no quarrels to give!",from->name);
							GX(temp,BAD);
						}

						break;

			case 5 :    if (from->darts)
							actually_swap_item_multiple(f,t,SWAP_DARTS);
						else
						{
							sprintf(temp,"%s hath no darts to give!",from->name);
							GX(temp,BAD);
						}

						break;

			case 6 :    if (from->cash)
							actually_swap_item_multiple(f,t,SWAP_GOLD);
						else
						{
							sprintf(temp,"%s hath no gold to give!",from->name);
							GX(temp,BAD);
						}

						break;

			case 7 :    actually_swap_item_single(f,t);
						break;

			default:    fin=TRUE; break;
		}
	}

	kill_gwindow(&win);
	kill_gwindow(&win2);
}

void _PASCAL _NEAR actually_swap_item_multiple(int f,int t,int ntype)
{
	PLAYER *from,*to;
	char type[30];
	static char temp[120];
	unsigned long int amount;
	int amount_wanted;
	int too_much=FALSE;

	from = &TPP[f];
	to   = &TPP[t];

	switch(ntype)
	{
		case SWAP_FOOD      :   amount=(unsigned long)from->food;
								strcpy(type,"Food");
								break;

		case SWAP_OIL       :   amount=(unsigned long)from->oil;
								strcpy(type,"Oil");
								break;

		case SWAP_ARROWS    :   amount=(unsigned long)from->arrows;
								strcpy(type,"Arrows");
								break;

		case SWAP_QUARRELS  :   amount=(unsigned long)from->quarrels;
								strcpy(type,"Quarrels");
								break;

		case SWAP_DARTS     :   amount=(unsigned long)from->darts;
								strcpy(type,"Darts");
								break;

		case SWAP_GOLD      :   amount=from->cash;
								strcpy(type,"Gold");
								break;
	}

	amount_wanted=get_swap_amount(from->name,to->name,type,amount);

	if (!amount_wanted)
		return;

	switch(ntype)
	{
		case SWAP_FOOD      :   if (to->food+amount_wanted>MAX_FOOD)
									too_much=TRUE;
								else
								{
									from->food-=amount_wanted;
									to->food+=amount_wanted;
								}

								break;

		case SWAP_OIL       :   if (to->oil+amount_wanted>MAX_OIL)
									too_much=TRUE;
								else
								{
									from->oil-=amount_wanted;
									to->oil+=amount_wanted;
								}

								break;

		case SWAP_ARROWS    :   if (to->arrows+amount_wanted>MAX_ARROWS)
									too_much=TRUE;
								else
								{
									from->arrows-=amount_wanted;
									to->arrows+=amount_wanted;
								}

								break;

		case SWAP_QUARRELS  :   if (to->quarrels+amount_wanted>MAX_QUARRELS)
									too_much=TRUE;
								else
								{
									from->quarrels-=amount_wanted;
									to->quarrels+=amount_wanted;
								}

								break;

		case SWAP_DARTS     :   if (to->darts+amount_wanted>MAX_DARTS)
									too_much=TRUE;
								else
								{
									from->darts-=amount_wanted;
									to->darts+=amount_wanted;
								}

								break;

		case SWAP_GOLD      :   from->cash-=(unsigned long)amount_wanted;
								to->cash+=(unsigned long)amount_wanted;

								break;
	}

	if (too_much)
	{
		sprintf(temp,"%s shouldn't be so greedy!",to->name);
		GX(temp,BAD);
	}
	else
	{
		GX(" Done! ",GOOD);
	}
}

int _PASCAL _NEAR get_swap_amount(char *from,char *to,char *type,unsigned long amount)
{
	static char line1[40];
	static char line2[40];
	static char line3[40];
	char temp[80];
	int food_oil=FALSE;
	int gold=FALSE;
	int num;
	int fin=FALSE;
	int longest;
	char *pic1="[   ]";
	char *pic2="[     ]";
	GWINDOW win;

	if (stricmp(type,"Food")==0 ||
		stricmp(type,"Oil")==0)
	{
			food_oil=TRUE;
			strcpy(temp,"much");
	}
	else
	if (stricmp(type,"Gold")==0)
	{
		gold=TRUE;
		strcpy(temp,"much");
	}
	else
		strcpy(temp,"many");

	sprintf(line1,"How %s %s doth",temp,type);
	sprintf(line2,"%s give %s?",from,to);
	sprintf(line3,"%s hath %lu.",from,amount);

	longest=max(strlen(line1),strlen(line2));
	longest=max(longest,(int)strlen(line3));
	longest/=2;

	win.x1=18-longest;
	win.y1=7;
	win.x2=22+longest;
	win.y2=14;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	while (!fin)
	{
		_settextcolor(7);

		_settextposition(win.y1+1,20-strlen_half(line1));
		_outtext(line1);

		_settextposition(win.y1+2,20-strlen_half(line2));
		_outtext(line2);

		_settextposition(win.y1+3,20-strlen_half(line3));
		_outtext(line3);

		_settextposition(win.y1+5,gold?17:18);
		_outtext(gold?pic2:pic1);

		strcpy(temp,gquery(gold?18:19,win.y1+5,gold?4:2,2,'N',""));

		num=atoi(temp);

		if (num==0)
		{
			fin=TRUE;
			break;
		}

		if ((unsigned long)num>amount)
		{
			sprintf(temp,"%s hath only got %lu %s%s!",from,
													amount,
													food_oil?"lots of ":"",
													type);
			GX(temp,BAD);
		}
		else
			fin=TRUE;
	}

	kill_gwindow(&win);

	return(strlen(temp)?num:0);
}

void _PASCAL _NEAR actually_swap_item_single(int f,int t)
{
	PLAYER *from,*to;
	char temp[80];

	from = &TPP[f];
	to   = &TPP[t];

	if (number_of_items(to)>=MAX_CARRY)
	{
		carry_no_more(to);
		return;
	}

	strcpy(temp,select_swap_item(from,to));

	if (*temp!='~')
	{
		GX(temp,GOOD);
	}
}

char *select_swap_item(PLAYER *from,PLAYER *to)
{
	GWINDOW win;
	int i;
	int num_items;
	int select;
	char pronoun[20];
	int fin;
	static char temp[80];
	static USE_SWAP items[MAX_CARRY];
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

	win.x1=4;
	win.y1=6;
	win.x2=28;
	win.y2=win.y1+5+MAX_CARRY;
	win.back=0;
	win.border=3;

	for (i=0,num_items=ERR; i<MAX_CARRY; i++)
	{
		if (from->items_carried[i].item!=NOTHING)
		{
			num_items++;
			items[num_items].bit=from->items_carried[i];
		}

		switch(from->items_carried[i].item)
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
			case SLING              : strcpy(temp,get_weapon_name(from->items_carried[i].item));
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
			case TOME               : strcpy(temp,STR_TOME);                break;
			case CURIOUS_BOX		: strcpy(temp,STR_CURIOUS_BOX); 		break;
			case ELFIN_CLOAK		: strcpy(temp,STR_ELFIN_CLOAK); 		break;
			case ELFIN_BOOTS        : strcpy(temp,STR_ELFIN_BOOTS);         break;
			case BRACERS_POISON     : strcpy(temp,STR_BRACERS_POISON);      break;
			case PENDANT_HEALTH     : strcpy(temp,STR_PENDANT_HEALTH);      break;
			case GLOVES_NIMBLENESS  : strcpy(temp,STR_GLOVES_NIMBLENESS);   break;
			case POTION             : strcpy(temp,"Potion");                break;
			default                 : fin=TRUE;                             break;
		}

		switch(from->items_carried[i].item)
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
			case HELMET             :   switch(from->items_carried[i].type)
										{
											case PLUS_1 : strcat(temp," (+1)");    break;
											case PLUS_2 : strcat(temp," (+2)");    break;
											case PLUS_3 : strcat(temp," (+3)");    break;
											default     : break;
										}

										if (from->items_carried[i].poisoned)
											strcat(temp," (P)");

										break;

			case POTION             :   strcat(temp,potion_get_colour(from->items_carried[i].type,TRUE));
										break;

			default                 :   break;
		}

		strcpy(items[num_items].desc,temp);
	}

	if (num_items==ERR)
	{
		sprintf(temp,"%s has nothing to give %s!",from->name,to->name);
		GX(temp,BAD);

		return("~");
	}

	make_gwindow(&win);

	click_box(98,158,B_QUIT);

	_settextposition(win.y1+1,win.x1+5);
	_settextcolor(14);
	_outtext("Select Item..");

	for (i=0; i<=num_items; i++)
	{
		_settextcolor(13);
		sprintf(temp,"%cù",i+'A');                /* PC */
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

		if (select==12)
			fin=TRUE;
		else
		if (validate_item_use(to,&items[select]))
			fin=TRUE;
	}

	kill_gwindow(&win);

	if (select!=12)
	{
		for (i=0; i<MAX_CARRY; i++)
		{
			if (from->items_carried[i].item    ==items[select].bit.item &&
				from->items_carried[i].type    ==items[select].bit.type &&
				from->items_carried[i].poisoned==items[select].bit.poisoned)
			{
				from->items_carried[i].item     = NOTHING;
				from->items_carried[i].type     = 0;
				from->items_carried[i].status   = ITEM_CARRIED;
				from->items_carried[i].poisoned = FALSE;

				break;
			}
		}

		add_to_player(items[select].bit.item,
					  items[select].bit.type,
					  items[select].bit.poisoned,
					  ITEM_CARRIED,
					  to);

		(void)number_of_items(to);
		(void)number_of_items(from);

		sort_adv_items(to);
		sort_adv_items(from);

		if (isvowel((int)*items[select].desc))
			strcpy(pronoun,"an");
		else
			strcpy(pronoun,"a");

		switch(items[select].bit.item)
		{
			case LEATHER_ARMOUR :
			case SPLINT_ARMOUR  :
			case CHAIN_ARMOUR   :
			case PLATE_ARMOUR   :
			case ELF_ARMOUR     :
			case THIEVES_TOOLS  :
			case ELFIN_BOOTS    :   strcpy(pronoun,"some");
									break;
			default             :   break;
		}

		if (from->helmet_used.item==items[select].bit.item &&
			from->helmet_used.type==items[select].bit.type)
		{
			from->helmet_used.item      = NOTHING;
			from->helmet_used.type      = NO_PLUS;
			from->helmet_used.status    = ITEM_CARRIED;
		}
		else
		if (from->shield_used.item==items[select].bit.item &&
			from->shield_used.type==items[select].bit.type)
		{
			from->shield_used.item      = NOTHING;
			from->shield_used.type      = NO_PLUS;
			from->shield_used.status    = ITEM_CARRIED;
		}
		else
		if (from->weapon_used.item==items[select].bit.item &&
			from->weapon_used.type==items[select].bit.type)
		{
			from->weapon_used.item      = NOTHING;
			from->weapon_used.type      = NO_PLUS;
			from->weapon_used.status    = ITEM_CARRIED;
			from->weapon_used.poisoned  = FALSE;
		}
		else
		if (from->armour_used.item==items[select].bit.item &&
			from->armour_used.type==items[select].bit.type)
		{
			from->armour_used.item      = NOTHING;
			from->armour_used.type      = NO_PLUS;
			from->armour_used.status    = ITEM_CARRIED;
		}
		else
		if (from->ring_used.item==items[select].bit.item &&
			from->ring_used.type==items[select].bit.type)
		{
			from->ring_used.item        = NOTHING;
			from->ring_used.type        = NO_PLUS;
			from->ring_used.status      = ITEM_CARRIED;
		}

		if (player_is_dead(from))
		{
			sprintf(temp,"%s takes %s %s from %s.",
						  to->name,
						  pronoun,
						  items[select].desc,
						  from->name);
		}
		else
		{
			sprintf(temp,"%s gives %s %s to %s.",
						  from->name,
						  pronoun,
						  items[select].desc,
						  to->name);
		}
	}
	else
	{
		strcpy(temp,"~");
	}

	return(temp);
}

int _PASCAL validate_item_use(PLAYER *to,USE_SWAP *item)
{
	char temp[80];
	int result=TRUE;
	int cl=to->nclass;
	int ra=to->nrace;
	int thing=item->bit.item;

	if ((thing==POTION              &&
		item->bit.type==POT_POISON  &&
		to->ethics==LAWFUL)         ||
		(item->bit.poisoned 		&&
		to->ethics==LAWFUL))
	{
		sprintf(temp,"%s, being Lawful, cannot use poison!",to->name);
		GX(temp,BAD);
		result=FALSE;
	}
	else
	if (thing==POTION                 &&
		item->bit.type==POT_HOLYWATER &&
		to->ethics!=LAWFUL)
	{
		sprintf(temp,"As %s is not Lawful, %s cannot use Holy Water!",
				to->name,
				to->he_she);

		GX(temp,BAD);
		result=FALSE;
	}
	else
	switch(thing)
	{
		case LEATHER_ARMOUR :
					switch(cl)
					{
						case WIZARD 	:
						case ILLUSIONIST:
						case MONK       : class_cannot_use(cl,STR_LEATHER_ARMOUR);
										  result=FALSE;
										  break;

						default 		: break;
					}

					break;

		case SPLINT_ARMOUR :
					if (cl!=WARRIOR && cl!=PRIEST && cl!=RANGER && cl!=CRUSADER)
					{
						class_cannot_use(cl,STR_SPLINT_ARMOUR);
						result=FALSE;
					}

					break;

		case CHAIN_ARMOUR	:
					if (cl!=WARRIOR && cl!=PRIEST && cl!=RANGER && cl!=CRUSADER)
					{
						class_cannot_use(cl,STR_CHAIN_ARMOUR);
						result=FALSE;
					}

					break;

		case PLATE_ARMOUR	:
					if (cl!=WARRIOR && cl!=CRUSADER)
					{
						class_cannot_use(cl,STR_PLATE_ARMOUR);
						result=FALSE;
					}

					break;

		case ELF_ARMOUR :
					if (cl==WIZARD || cl==ILLUSIONIST || cl==MONK)
					{
						class_cannot_use(cl,STR_ELF_ARMOUR);
						result=FALSE;
					}

					break;

		case HELMET :
					if (cl==WIZARD || cl==ILLUSIONIST || cl==MONK ||
						cl==THIEF  || cl==HUNTER || cl==DRUID || cl==DUELIST)
					{
						class_cannot_use(cl,"a Metal Helm");
						result=FALSE;
					}

					break;

		case SMALL_SHIELD	:
					if (cl==WIZARD || cl==DRUID || cl==THIEF ||
						cl==ILLUSIONIST || cl==MONK || cl==DUELIST)
					{
						class_cannot_use(cl,"a Small Shield");
						result=FALSE;
					}

					break;

		case MEDIUM_SHIELD	:
					if (cl==WIZARD || cl==DRUID || cl==THIEF ||
						cl==ILLUSIONIST || cl==MONK || cl==DUELIST)
					{
						class_cannot_use(cl,"a Medium Shield");
						result=FALSE;
					}

					break;

		case LARGE_SHIELD	:
					if (cl!=WARRIOR && cl!=CRUSADER)
					{
						class_cannot_use(cl,"a Large Shield");
						result=FALSE;
					}

					break;

		case DAGGER :
					if (cl==PRIEST)
					{
						class_cannot_use(cl,"a Dagger");
						result=FALSE;
					}

						break;

		case AXE	:
					if (cl==BARD || cl==WIZARD || cl==PRIEST ||
						cl==DRUID || cl==MONK || cl==ILLUSIONIST || cl==DUELIST)
					{
						class_cannot_use(cl,"a Battle Axe");
						result=FALSE;
					}

					break;

		case SHORT_SWORD	:
					if (cl==WIZARD || cl==PRIEST || cl==MONK || cl==ILLUSIONIST)
					{
						class_cannot_use(cl,"a Short Sword");
						result=FALSE;
					}

					break;

		case LONG_SWORD :
					if (cl==WIZARD || cl==PRIEST || cl==MONK ||
						cl==ILLUSIONIST || cl==DRUID)
					{
						class_cannot_use(cl,"a Long Sword");
						result=FALSE;
					}

					break;

		case RAPIER :
					if (cl==WIZARD || cl==PRIEST || cl==MONK ||
						cl==ILLUSIONIST || cl==DRUID)
					{
						class_cannot_use(cl,"a Rapier");
						result=FALSE;
					}

					break;

		case CLAYMORE	:
					if (cl!=WARRIOR && cl!=RANGER && cl!=CRUSADER && cl!=HUNTER)
					{
						class_cannot_use(cl,"a Claymore");
						result=FALSE;
					}
					else
					{
						if (ra==GNOME || ra==HALFLING || ra==DWARF)
						{
							race_cannot_use(ra,STR_CLAYMORE);
							result=FALSE;
						}
					}

					break;

		case MACE	:
					if (cl!=WARRIOR && cl!=RANGER && cl!=CRUSADER &&
						cl!=PRIEST && cl!=BARD)
					{
						class_cannot_use(cl,"a Footman's Mace");
						result=FALSE;
					}

					break;

		case FLAIL	:
					if (cl!=WARRIOR && cl!=RANGER && cl!=CRUSADER && cl!=PRIEST)
					{
						class_cannot_use(cl,"a Footman's Flail");
						result=FALSE;
					}
					else
					{
						if (ra==GNOME || ra==HALFLING || ra==DWARF)
						{
							race_cannot_use(ra,STR_FLAIL);
							result=FALSE;
						}
					}

					break;

		case CROSSBOW	:
					if (cl==WIZARD || cl==PRIEST || cl==DRUID ||
						cl==MONK   || cl==ILLUSIONIST || cl==BARD || cl==DUELIST)
					{
						class_cannot_use(cl,"a Crossbow");
						result=FALSE;
					}
					else
					if (to->strength<15)
					{
						too_weak_to_use(to->name,"a Crossbow");
						result=FALSE;
					}
					else
					{
						if (ra==GNOME || ra==HALFLING)
						{
							race_cannot_use(ra,STR_CROSSBOW);
							result=FALSE;
						}
					}

					break;

		case BOW	:
					if (cl==WIZARD || cl==PRIEST || cl==DRUID ||
						cl==MONK   || cl==ILLUSIONIST || cl==DUELIST)
					{
						class_cannot_use(cl,"a Long Bow");
						result=FALSE;
					}

					break;

		case HALBERD	:
					if (cl!=WARRIOR && cl!=CRUSADER)
					{
						class_cannot_use(cl,"a Halberd");
						result=FALSE;
					}
					else
					if (to->strength<16)
					{
						too_weak_to_use(to->name,"a Halberd");
						result=FALSE;
					}
					else
					{
						if (ra==GNOME || ra==HALFLING || ra==DWARF)
						{
							race_cannot_use(ra,STR_HALBERD);
							result=FALSE;
						}
					}

		default :   result=TRUE; break;
	}

	return(result);
}
