#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

#define READY_QUIT	 9

static char *ready_string="ABCDEFGHIQ";
static int boundary[]={61, 32,245, 38,
					   61, 40,245, 46,
					   61, 48,245, 54,
					   61, 56,245, 62,
					   61, 64,245, 70,
					   61, 72,245, 78,
					   61, 80,245, 86,
					   61, 88,245, 94,
					   61, 96,245,102,
					   140,106,175,118,
					   -1,-1,-1,-1};

int _PASCAL ready_an_adventurer(PLAYER *adv)
{
	GWINDOW win;
	int fin=FALSE;
	int res;
	static int lil_boundary[]={ 126,22,140,48,
								160,22,179,48,
								198,26,212,48,
								230,26,243,48,
								259,26,275,48,
								180,53,215,65,
								-1,-1,-1,-1};

	if (bard_is_singing(adv,"ready an item"))
		return(FALSE);

	win.x1=15;
	win.y1=3;
	win.x2=37;
	win.y2=10;
	win.back=0;
	win.border=8;

	make_gwindow(&win);

	generic_pic_draw(120,21,"READY");

	click_box(180,53,B_FINISH);

	while (!fin)
	{
		switch (mouse_in_range(lil_boundary,"AWSHRF","AWSHRQ"))
		{
			case 0 : res=ready_an_adventurer_armour(adv); break;
			case 1 : res=ready_an_adventurer_weapon(adv); break;
			case 2 : res=ready_an_adventurer_shield(adv); break;
			case 3 : res=ready_an_adventurer_helmet(adv); break;
			case 4 : res=ready_an_adventurer_ring(adv);   break;
			case 5 : fin=TRUE; res=FALSE;				  break;
		}
	}

	kill_gwindow(&win);

	return(res);
}

int _PASCAL ready_an_adventurer_armour(PLAYER *adv)
{
	GWINDOW win;
	char temp[50];
	int number=0;
	int max_num=8;
	int fin=FALSE;
	int i;
	int res=FALSE;
	ITEM_POOL bit;
	int selected;
	int armour_flag=FALSE;
	ITEM_POOL items[MAX_CARRY];
	char *title="Select Thine Armour";
	int held_flag=FALSE;

	if (adv->nclass==WIZARD 	 ||
		adv->nclass==ILLUSIONIST ||
		adv->nclass==MONK)
	{
		class_cannot_use(adv->nclass,"Armour");
		return(FALSE);
	}

	for (i=0; i<MAX_CARRY; i++)
		items[i].item=NOTHING;

	win.x1=8;
	win.y1=2;
	win.x2=33;
	win.y2=win.y1+max_num+7;
	win.back=0;
	win.border=3;

	for (i=0; i<MAX_CARRY; i++)
	{
		bit=adv->items_carried[i];

		if (bit.item==LEATHER_ARMOUR || bit.item==SPLINT_ARMOUR ||
			bit.item==CHAIN_ARMOUR   || bit.item==PLATE_ARMOUR  ||
			bit.item==ELF_ARMOUR)
			   items[++number]=bit;

		if (number>=max_num)
			break;
	}

	if (number==0)
	{
		sprintf(temp,"%s hath no armour!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	make_gwindow(&win);

	click_box(140,106,B_QUIT);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+3);
	_outtext(title);

	_settextcolor(13);
	_settextposition(win.y1+3,win.x1+2);
	_outtext("Aù");

	_settextcolor(5);
	_settextposition(win.y1+3,win.x1+4);
	_outtext("Cloak Only");

	if (adv->armour_used.item==0 || adv->armour_used.item==NOTHING)
	{
		armour_flag=TRUE;
		tick(win.x1*8-3,(win.y1+2)*8,ON);
	}

	for (i=1; i<=number; i++)
	{
		_settextcolor(13);
		_settextposition(i+win.y1+3,win.x1+2);
		sprintf(temp,"%cù",i+'A');
		_outtext(temp);

		switch(items[i].item)
		{
			case LEATHER_ARMOUR :   strcpy(temp,STR_LEATHER_ARMOUR); break;
			case SPLINT_ARMOUR  :   strcpy(temp,STR_SPLINT_ARMOUR);  break;
			case CHAIN_ARMOUR   :   strcpy(temp,STR_CHAIN_ARMOUR);   break;
			case PLATE_ARMOUR   :   strcpy(temp,STR_PLATE_ARMOUR);   break;
			case ELF_ARMOUR     :   strcpy(temp,STR_ELF_ARMOUR);     break;
		}

		switch(items[i].type)
		{
			case NO_PLUS        :   strcat(temp,"");             break;
			case PLUS_1         :   strcat(temp," (+1)");        break;
			case PLUS_2         :   strcat(temp," (+2)");        break;
			case PLUS_3         :   strcat(temp," (+3)");        break;
			case CURSED         :   strcat(temp,"");             break;
		}

		_settextcolor(5);
		_settextposition(i+win.y1+3,win.x1+4);
		_outtext(temp);

		if (items[i].item==adv->armour_used.item &&
			items[i].type==adv->armour_used.type)
		{
			if (!armour_flag)
			{
				armour_flag=TRUE;
				tick(win.x1*8-3,(win.y1+i+2)*8,ON);
			}
		}
	}

	while (!fin)
	{
		selected=mouse_in_range(boundary,ready_string,"");

		if (selected==READY_QUIT)
		{
			fin=TRUE;
			res=FALSE;
		}
		else
		if (selected>number)
		{
			bad_sound();
			continue;
		}
		else
		if (selected==0)
		{
			memset((void *)&adv->armour_used,
				   0,
				   sizeof(ITEM_POOL));

			for (i=0; i<MAX_CARRY; i++)
			{
				switch(adv->items_carried[i].item)
				{
					case LEATHER_ARMOUR :
					case SPLINT_ARMOUR  :         /* to the CARRIED status   */
					case CHAIN_ARMOUR   :         /* Set all previous armour */
					case PLATE_ARMOUR   :
					case ELF_ARMOUR 	:	adv->items_carried[i].status=ITEM_CARRIED; break;
					default             :   break;
				}
			}

		}
		else
		{
			for (i=0; i<MAX_CARRY; i++)
			{
				switch(adv->items_carried[i].item)
				{
					case LEATHER_ARMOUR :
					case SPLINT_ARMOUR  :
					case CHAIN_ARMOUR   :
					case PLATE_ARMOUR   :
					case ELF_ARMOUR 	:	adv->items_carried[i].status=ITEM_CARRIED; break;
					default             :   break;
				}

				adv->armour_used.item=items[selected].item;
				adv->armour_used.type=items[selected].type;
				adv->armour_used.status=ITEM_HELD;

				if (adv->armour_used.item==adv->items_carried[i].item &&
					adv->armour_used.type==adv->items_carried[i].type &&
					!held_flag)
				{
						held_flag=TRUE;
						adv->items_carried[i].status=ITEM_HELD;
				}
			}
		}

		fin=res=TRUE;
	}

	good_sound();

	kill_gwindow(&win);

	return(res);
}

int _PASCAL ready_an_adventurer_weapon(PLAYER *adv)
{
	GWINDOW win;
	char temp[80];
	char weap[30];
	int number=0;
	int max_num=8;
	int fin=FALSE;
	int i;
	int res=FALSE;
	ITEM_POOL bit;
	int selected;
	int weapon_flag=FALSE;
	ITEM_POOL items[MAX_CARRY];
	char *title="Select Thy Weapon";
	int held_flag=FALSE;

	for (i=0; i<MAX_CARRY; i++)
		items[i].item=NOTHING;

	win.x1=8;
	win.y1=2;
	win.x2=33;
	win.y2=win.y1+max_num+7;
	win.back=0;
	win.border=3;

	for (i=0; i<MAX_CARRY; i++)
	{
		bit=adv->items_carried[i];

		if (bit.item==DAGGER      || bit.item==AXE        ||
			bit.item==SHORT_SWORD || bit.item==LONG_SWORD ||
			bit.item==RAPIER      || bit.item==CLAYMORE   ||
			bit.item==MACE        || bit.item==FLAIL      ||
			bit.item==BOW         || bit.item==CROSSBOW   ||
			bit.item==HALBERD     || bit.item==SLING)
			   items[++number]=bit;

		if (number>=max_num)
			break;
	}

	if (number==0)
	{
		sprintf(temp,"%s hath no weapons!",adv->name);

		if (IN_COMBAT)
			cmbt_bad_msg(temp,TRUE);
		else
			GX(temp,BAD);

		return(FALSE);
	}

	make_gwindow(&win);

	click_box(140,106,B_QUIT);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+4);
	_outtext(title);

	_settextcolor(13);
	_settextposition(win.y1+3,win.x1+2);
	_outtext("Aù");

	_settextcolor(5);
	_settextposition(win.y1+3,win.x1+4);
	_outtext("Empty Hands");

	if (adv->weapon_used.item==0 || adv->weapon_used.item==NOTHING)
	{
		weapon_flag=TRUE;
		tick(win.x1*8-3,(win.y1+2)*8,ON);
	}

	for (i=1; i<=number; i++)
	{
		_settextcolor(13);
		_settextposition(i+win.y1+3,win.x1+2);
		sprintf(temp,"%cù",i+'A');
		_outtext(temp);

		switch(items[i].item)
		{
			case DAGGER 		 :
			case AXE			 :
			case SHORT_SWORD	 :
			case LONG_SWORD 	 :
			case RAPIER 		 :
			case CLAYMORE		 :
			case MACE			 :
			case FLAIL			 :
			case BOW			 :
			case CROSSBOW		 :
			case HALBERD		 :
			case SLING			 : strcpy(temp,get_weapon_name(items[i].item));
								   break;
			default              : strcpy(temp,"");                   break;
		}

		switch(items[i].type)
		{
			case PLUS_1          : strcat(temp," (+1)");              break;
			case PLUS_2          : strcat(temp," (+2)");              break;
			case PLUS_3          : strcat(temp," (+3)");              break;
			default              : strcat(temp,"");                   break;
		}

		if (items[i].poisoned)
			strcat(temp," (P)");

		_settextcolor(5);
		_settextposition(i+win.y1+3,win.x1+4);
		_outtext(temp);

		if (items[i].item==adv->weapon_used.item &&
			items[i].type==adv->weapon_used.type)
		{
			if (!weapon_flag)
			{
				weapon_flag=TRUE;
				tick(win.x1*8-3,(win.y1+i+2)*8,ON);
			}
		}
	}

	while (!fin)
	{
		selected=mouse_in_range(boundary,ready_string,"");

		if (selected==READY_QUIT)
		{
			fin=TRUE;
			res=FALSE;
		}
		else
		if (selected>number)
		{
			bad_sound();
			continue;
		}
		else
		if (selected==0)
		{
			memset((void *)&adv->weapon_used,0,sizeof(ITEM_POOL));

			for (i=0; i<MAX_CARRY; i++)
			{
				switch(adv->items_carried[i].item)
				{
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
					case SLING				: adv->items_carried[i].status=ITEM_CARRIED; break;
					default                 : break;
				}
			}

			res=TRUE;
		}
		else
		{
			for (i=0; i<MAX_CARRY; i++)
			{
				switch(adv->items_carried[i].item)
				{
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
					case SLING				: adv->items_carried[i].status=ITEM_CARRIED; break;
					default                 : break;
				}

				adv->weapon_used.item	 =items[selected].item;
				adv->weapon_used.type	 =items[selected].type;
				adv->weapon_used.status  =ITEM_HELD;
				adv->weapon_used.poisoned=items[selected].poisoned;

				if (adv->weapon_used.item==adv->items_carried[i].item &&
					adv->weapon_used.type==adv->items_carried[i].type &&
					!held_flag)
				{
						adv->items_carried[i].status=ITEM_HELD;
						held_flag=TRUE;
				}
			}

			res=TRUE;
		}

		fin=TRUE;
	}

	good_sound();

	kill_gwindow(&win);

	bit=adv->weapon_used;

	if (bit.item==HALBERD  || bit.item==CLAYMORE ||
		bit.item==BOW      || bit.item==CROSSBOW ||
		bit.item==FLAIL)
	{
		if (adv->shield_used.item==SMALL_SHIELD  ||
			adv->shield_used.item==MEDIUM_SHIELD ||
			adv->shield_used.item==LARGE_SHIELD)
		{
			for (i=0; i<MAX_CARRY; i++)
				if (adv->items_carried[i].item==SMALL_SHIELD  ||
					adv->items_carried[i].item==MEDIUM_SHIELD ||
					adv->items_carried[i].item==LARGE_SHIELD)
						adv->items_carried[i].status=ITEM_CARRIED;

			adv->shield_used.item=NOTHING;
			adv->shield_used.status=ITEM_CARRIED;
			adv->shield_used.type=NO_PLUS;

			switch(adv->weapon_used.item)
			{
				case DAGGER      : strcpy(weap,STR_DAGGER);      break;
				case AXE         : strcpy(weap,STR_AXE);         break;
				case SHORT_SWORD : strcpy(weap,STR_SHORT_SWORD); break;
				case LONG_SWORD  : strcpy(weap,STR_LONG_SWORD);  break;
				case RAPIER      : strcpy(weap,STR_RAPIER);      break;
				case CLAYMORE    : strcpy(weap,STR_CLAYMORE);    break;
				case MACE        : strcpy(weap,STR_MACE);        break;
				case FLAIL       : strcpy(weap,STR_FLAIL);       break;
				case BOW         : strcpy(weap,STR_BOW);         break;
				case CROSSBOW    : strcpy(weap,STR_CROSSBOW);    break;
				case HALBERD     : strcpy(weap,STR_HALBERD);     break;
				case SLING       : strcpy(weap,STR_SLING);       break;
				default          : strcpy(weap,"");              break;
			}

			switch(adv->weapon_used.type)
			{
				case PLUS_1          : strcat(weap," (+1)");              break;
				case PLUS_2          : strcat(weap," (+2)");              break;
				case PLUS_3          : strcat(weap," (+3)");              break;
				default              : strcat(weap,"");                   break;
			}

			sprintf(temp,"%s puts %s shield away to use %s %s",
						 adv->name,
						 adv->his_her,
						 adv->his_her,
						 weap);

			GX(temp,BAD);
		}
	}

	want_to_poison_weapon(adv);

	return(res);
}

int _PASCAL ready_an_adventurer_shield(PLAYER *adv)
{
	GWINDOW win;
	char temp[50];
	char weap[50];
	int number=0;
	int max_num=8;
	int fin=FALSE;
	int i;
	int res=FALSE;
	ITEM_POOL bit;
	int selected;
	int shield_flag=FALSE;
	ITEM_POOL items[MAX_CARRY];
	char *title="Select Thy Shield";
	int held_flag=FALSE;

	if (adv->nclass==WIZARD || adv->nclass==ILLUSIONIST || adv->nclass==MONK ||
		adv->nclass==THIEF	|| adv->nclass==DUELIST 	|| adv->nclass==DRUID)
	{
		class_cannot_use(adv->nclass,"Shields");
		return(FALSE);
	}

	for (i=0; i<MAX_CARRY; i++)
		items[i].item=NOTHING;

	win.x1=8;
	win.y1=2;
	win.x2=33;
	win.y2=win.y1+max_num+7;
	win.back=0;
	win.border=3;

	for (i=0; i<MAX_CARRY; i++)
	{
		bit=adv->items_carried[i];

		if (bit.item==SMALL_SHIELD  ||
			bit.item==MEDIUM_SHIELD ||
			bit.item==LARGE_SHIELD)
			   items[++number]=bit;

		if (number>=max_num)
			break;
	}

	if (number==0)
	{
		sprintf(temp,"%s hath no shield!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	make_gwindow(&win);

	click_box(140,106,B_QUIT);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+4);
	_outtext(title);

	_settextcolor(13);
	_settextposition(win.y1+3,win.x1+2);
	_outtext("Aù");

	_settextcolor(5);
	_settextposition(win.y1+3,win.x1+4);
	_outtext("Remove Shield");

	if (adv->shield_used.item==0 || adv->shield_used.item==NOTHING)
	{
		shield_flag=TRUE;
		tick(win.x1*8-3,(win.y1+2)*8,ON);
	}

	for (i=1; i<=number; i++)
	{
		_settextcolor(13);
		_settextposition(i+win.y1+3,win.x1+2);
		sprintf(temp,"%cù",i+'A');
		_outtext(temp);

		switch(items[i].item)
		{
			case SMALL_SHIELD   :   strcpy(temp,STR_SMALL_SHIELD);    break;
			case MEDIUM_SHIELD  :   strcpy(temp,STR_MEDIUM_SHIELD);   break;
			case LARGE_SHIELD   :   strcpy(temp,STR_LARGE_SHIELD);    break;
		}

		switch(items[i].type)
		{
			case PLUS_1         :   strcat(temp," (+1)");           break;
			case PLUS_2         :   strcat(temp," (+2)");           break;
			case PLUS_3         :   strcat(temp," (+3)");           break;
			default             :   strcat(temp,"");                break;
		}

		_settextcolor(5);
		_settextposition(i+win.y1+3,win.x1+4);
		_outtext(temp);

		if (items[i].item==adv->shield_used.item &&
			items[i].type==adv->shield_used.type)
		{
			if (!shield_flag)
			{
				shield_flag=TRUE;
				tick(win.x1*8-3,(win.y1+i+2)*8,ON);
			}
		}
	}

	while (!fin)
	{
		selected=mouse_in_range(boundary,ready_string,"");

		if (selected==READY_QUIT)
		{
			fin=TRUE;
			res=FALSE;
		}
		else
		if (selected>number)
		{
			bad_sound();
			continue;
		}
		else
		if (selected==0)
		{
			memset((void *)&adv->shield_used,
				   0,
				   sizeof(ITEM_POOL));

			for (i=0; i<MAX_CARRY; i++)
				switch(adv->items_carried[i].item)
				{
					case MEDIUM_SHIELD  :         /* to the CARRIED status   */
					case LARGE_SHIELD   :         /* Set all previous shield */
					case SMALL_SHIELD	:	adv->items_carried[i].status=ITEM_CARRIED; break;
					default             :   break;
				}

		}
		else
		{
			for (i=0; i<MAX_CARRY; i++)
			{
				switch(adv->items_carried[i].item)
				{
					case MEDIUM_SHIELD  :         /* to the CARRIED status   */
					case LARGE_SHIELD   :         /* Set all previous shield */
					case SMALL_SHIELD	:	adv->items_carried[i].status=ITEM_CARRIED; break;
					default             :   break;
				}

				adv->shield_used.item=items[selected].item;
				adv->shield_used.type=items[selected].type;
				adv->shield_used.status=ITEM_HELD;

				if (adv->shield_used.item==adv->items_carried[i].item &&
					adv->shield_used.type==adv->items_carried[i].type &&
					!held_flag)
				{
						adv->items_carried[i].status=ITEM_HELD;
						held_flag=TRUE;
				}
			}
		}

		fin=res=TRUE;
	}

	good_sound();

	kill_gwindow(&win);

	bit=adv->weapon_used;

	if (bit.item==HALBERD  || bit.item==CLAYMORE ||
		bit.item==RAPIER   || bit.item==BOW      ||
		bit.item==CROSSBOW || bit.item==FLAIL)
	{
		if (adv->shield_used.item==SMALL_SHIELD  ||
			adv->shield_used.item==MEDIUM_SHIELD ||
			adv->shield_used.item==LARGE_SHIELD)
		{
			for (i=0; i<MAX_CARRY; i++)
			{
				bit=adv->items_carried[i];

				if (bit.item==HALBERD   ||
					bit.item==CLAYMORE  ||
					bit.item==RAPIER    ||
					bit.item==BOW       ||
					bit.item==CROSSBOW  ||
					bit.item==FLAIL)
						adv->items_carried[i].status=ITEM_CARRIED;
			}

			switch(adv->weapon_used.item)
			{
				case DAGGER        : strcpy(weap,STR_DAGGER);      break;
				case AXE           : strcpy(weap,STR_AXE);         break;
				case SHORT_SWORD   : strcpy(weap,STR_SHORT_SWORD); break;
				case LONG_SWORD    : strcpy(weap,STR_LONG_SWORD);  break;
				case RAPIER        : strcpy(weap,STR_RAPIER);      break;
				case CLAYMORE      : strcpy(weap,STR_CLAYMORE);    break;
				case MACE          : strcpy(weap,STR_MACE);        break;
				case FLAIL         : strcpy(weap,STR_FLAIL);       break;
				case BOW           : strcpy(weap,STR_BOW);         break;
				case CROSSBOW      : strcpy(weap,STR_CROSSBOW);    break;
				case HALBERD       : strcpy(weap,STR_HALBERD);     break;
				case SLING         : strcpy(weap,STR_SLING);       break;
				default            : strcpy(weap,"");              break;
			}

			switch(adv->weapon_used.type)
			{
				case PLUS_1          : strcat(weap," (+1)");             break;
				case PLUS_2          : strcat(weap," (+2)");             break;
				case PLUS_3          : strcat(weap," (+3)");             break;
				default              : strcat(weap,"");                  break;
			}

			adv->weapon_used.item=NOTHING;
			adv->weapon_used.status=ITEM_CARRIED;
			adv->weapon_used.type=NO_PLUS;

			sprintf(temp,"%s puts %s %s away to use ye shield",
						 adv->name,
						 adv->his_her,
						 weap);

			GX(temp,BAD);
		}
	}

	return(res);
}

int _PASCAL ready_an_adventurer_helmet(PLAYER *adv)
{
	GWINDOW win;
	char temp[50];
	int number=0;
	int max_num=8;
	int fin=FALSE;
	int i;
	int res=FALSE;
	ITEM_POOL bit;
	int selected;
	int helmet_flag=FALSE;
	ITEM_POOL items[MAX_CARRY];
	char *title="Select Thine Helmet";
	int held_flag=FALSE;

	if (adv->nclass==WIZARD || adv->nclass==ILLUSIONIST || adv->nclass==MONK   ||
		adv->nclass==DRUID	|| adv->nclass==THIEF		|| adv->nclass==HUNTER ||
		adv->nclass==DUELIST)
	{
		class_cannot_use(adv->nclass,"Helmets");
		return(FALSE);
	}

	for (i=0; i<MAX_CARRY; i++)
		items[i].item=NOTHING;

	win.x1=8;
	win.y1=2;
	win.x2=32;
	win.y2=win.y1+max_num+7;
	win.back=0;
	win.border=3;

	for (i=0; i<MAX_CARRY; i++)
	{
		bit=adv->items_carried[i];

		if (bit.item==HELMET)
			   items[++number]=bit;

		if (number>=max_num)
			break;
	}

	if (number==0)
	{
		sprintf(temp,"%s hath no helmet!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	make_gwindow(&win);

	click_box(140,106,B_QUIT);

	_settextcolor(13);
	_settextposition(win.y1+3,win.x1+2);
	_outtext("Aù");

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+3);
	_outtext(title);

	_settextcolor(5);
	_settextposition(win.y1+3,win.x1+4);
	_outtext("Remove Helmet");

	if (adv->helmet_used.item==0 || adv->helmet_used.item==NOTHING)
	{
		helmet_flag=TRUE;
		tick(win.x1*8-3,(win.y1+2)*8,ON);
	}

	for (i=1; i<=number; i++)
	{
		_settextcolor(13);
		_settextposition(i+win.y1+3,win.x1+2);
		sprintf(temp,"%cù",i+'A');
		_outtext(temp);

		if (items[i].item==HELMET)
			strcpy(temp,"Metal Helm ");

		switch(items[i].type)
		{
			case PLUS_1   :   strcat(temp,"(+1)");   break;
			case PLUS_2   :   strcat(temp,"(+2)");   break;
			case PLUS_3   :   strcat(temp,"(+3)");   break;
			default       :   strcat(temp,"");       break;
		}

		_settextcolor(5);
		_settextposition(i+win.y1+3,win.x1+4);
		_outtext(temp);

		if (items[i].item==adv->helmet_used.item &&
			items[i].type==adv->helmet_used.type)
		{
			if (!helmet_flag)
			{
				helmet_flag=TRUE;
				tick(win.x1*8-3,(win.y1+i+2)*8,ON);
			}
		}
	}

	while (!fin)
	{
		selected=mouse_in_range(boundary,ready_string,"");

		if (selected==READY_QUIT)
		{
			fin=TRUE;
			res=FALSE;
		}
		else
		if (selected>number)
		{
			bad_sound();
			continue;
		}
		else
		if (selected==0)
		{
			memset((void *)&adv->helmet_used,
				   0,
				   sizeof(ITEM_POOL));

			for (i=0; i<MAX_CARRY; i++)
				if (adv->items_carried[i].item==HELMET)
					adv->items_carried[i].status=ITEM_CARRIED;

		}
		else
		{
			for (i=0; i<MAX_CARRY; i++)
			{
				if (adv->items_carried[i].item==HELMET)
					adv->items_carried[i].status=ITEM_CARRIED;

				adv->helmet_used.item=items[selected].item;
				adv->helmet_used.type=items[selected].type;
				adv->helmet_used.status=ITEM_HELD;

				if (adv->helmet_used.item==adv->items_carried[i].item &&
					adv->helmet_used.type==adv->items_carried[i].type &&
					!held_flag)
				{
						adv->items_carried[i].status=ITEM_HELD;
						held_flag=TRUE;
				}
			}
		}

		fin=res=TRUE;
	}

	good_sound();

	kill_gwindow(&win);

	return(res);
}

int _PASCAL ready_an_adventurer_ring(PLAYER *adv)
{
	GWINDOW win;
	char temp[50];
	int number=0;
	int max_num=8;
	int fin=FALSE;
	int i;
	int res=FALSE;
	ITEM_POOL bit;
	int selected;
	int ring_flag=FALSE;
	ITEM_POOL items[MAX_CARRY];
	char *title="Select Thy Ring";
	int held_flag=FALSE;

	for (i=0; i<MAX_CARRY; i++)
		items[i].item=NOTHING;

	win.x1=8;
	win.y1=2;
	win.x2=32;
	win.y2=win.y1+max_num+7;
	win.back=0;
	win.border=3;

	for (i=0; i<MAX_CARRY; i++)
	{
		bit=adv->items_carried[i];

		if (bit.item==WYVERN_RING         ||
			bit.item==DRAGON_RING         ||
			bit.item==RING_OF_HEALING     ||
			bit.item==MIND_SHIELD_RING    ||
			bit.item==RING_OF_FIRE        ||
			bit.item==RING_OF_ICICLES     ||
			bit.item==RING_OF_SWIMMING    ||
			bit.item==WARMTH_RING)
			   items[++number]=bit;

		if (number>=max_num)
			break;
	}

	if (number==0)
	{
		sprintf(temp,"%s hath no rings!",adv->name);

		if (IN_COMBAT)
			cmbt_bad_msg(temp,TRUE);
		else
			GX(temp,BAD);

		return(FALSE);
	}

	make_gwindow(&win);

	click_box(140,106,B_QUIT);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+4);
	_outtext(title);

	_settextcolor(13);
	_settextposition(win.y1+3,win.x1+2);
	_outtext("Aù");

	_settextcolor(5);
	_settextposition(win.y1+3,win.x1+4);
	_outtext("Remove Ring");

	if (adv->ring_used.item==0 || adv->ring_used.item==NOTHING)
	{
		ring_flag=TRUE;
		tick(win.x1*8-3,(win.y1+2)*8,ON);
	}

	for (i=1; i<=number; i++)
	{
		_settextcolor(13);
		_settextposition(i+win.y1+3,win.x1+2);
		sprintf(temp,"%cù",i+'A');
		_outtext(temp);

		switch(items[i].item)
		{
			case WYVERN_RING        :   strcpy(temp,STR_WYVERN_RING);         break;
			case DRAGON_RING        :   strcpy(temp,STR_DRAGON_RING);         break;
			case RING_OF_HEALING    :   strcpy(temp,STR_RING_OF_HEALING);     break;
			case MIND_SHIELD_RING   :   strcpy(temp,STR_MIND_SHIELD_RING);    break;
			case RING_OF_FIRE       :   strcpy(temp,STR_RING_OF_FIRE);        break;
			case RING_OF_ICICLES    :   strcpy(temp,STR_RING_OF_ICICLES);     break;
			case RING_OF_SWIMMING   :   strcpy(temp,STR_RING_OF_SWIMMING);    break;
			case WARMTH_RING        :   strcpy(temp,STR_WARMTH_RING);         break;
		}

		_settextcolor(5);
		_settextposition(i+win.y1+3,win.x1+4);
		_outtext(temp);

		if (items[i].item==adv->ring_used.item &&
			items[i].type==adv->ring_used.type)
		{
			if (!ring_flag)
			{
				ring_flag=TRUE;
				tick(win.x1*8-3,(win.y1+i+2)*8,ON);
			}
		}
	}

	while (!fin)
	{
		selected=mouse_in_range(boundary,ready_string,"");

		if (selected==READY_QUIT)
		{
			fin=TRUE;
			res=FALSE;
		}
		else
		if (selected>number)
		{
			bad_sound();
			continue;
		}
		else
		if (selected==0)
		{
			memset((void *)&adv->ring_used,
				   0,
				   sizeof(ITEM_POOL));

			for (i=0; i<MAX_CARRY; i++)
			{
				switch(adv->items_carried[i].item)
				{
					case WYVERN_RING        :
					case DRAGON_RING        :
					case RING_OF_HEALING    :
					case MIND_SHIELD_RING   :
					case RING_OF_FIRE       :
					case RING_OF_ICICLES    :
					case RING_OF_SWIMMING   :
					case WARMTH_RING		: adv->items_carried[i].status=ITEM_CARRIED; break;
					default                 : break;
				}
			}

			res=TRUE;
		}
		else
		{
			for (i=0; i<MAX_CARRY; i++)
			{
				switch(adv->items_carried[i].item)
				{
					case WYVERN_RING        :
					case DRAGON_RING        :
					case RING_OF_HEALING    :
					case MIND_SHIELD_RING   :
					case RING_OF_FIRE       :
					case RING_OF_ICICLES    :
					case RING_OF_SWIMMING   :
					case WARMTH_RING		: adv->items_carried[i].status=ITEM_CARRIED; break;
					default                 : break;
				}

				adv->ring_used.item=items[selected].item;
				adv->ring_used.type=items[selected].type;
				adv->ring_used.status=ITEM_HELD;

				if (adv->ring_used.item==adv->items_carried[i].item &&
					adv->ring_used.type==adv->items_carried[i].type &&
					!held_flag)
				{
						adv->items_carried[i].status=ITEM_HELD;
						held_flag=TRUE;
				}
			}

			res=TRUE;
		}

		fin=TRUE;
	}

	good_sound();

	kill_gwindow(&win);

	return(res);
}
