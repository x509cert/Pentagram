#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

static int      items_in_pool;

void _PASCAL distribute_pool()
{
	int i;
	int item_found=FALSE;
	int person_has_item;

	if (!gget_yn("Distribute Items, art thou sure?"))
		return;

	make_gplease_wait();

	items_in_pool=0;
	nullify_pool();

	for (i=0; i<=P_NUM; i++)
	{
		person_has_item=take_items_from_adv(&TPP[i]);

		if (person_has_item && !item_found)
			item_found=TRUE;
	}

	if (!item_found)
	{
		GX("Thy party should not adventure, ye hath no items!",BAD);
		kill_gplease_wait();

		return;
	}

	sort_pool_items(items_in_pool);

	kill_gplease_wait();

	distribute_all_items(items_in_pool);
}

void _PASCAL distribute_all_items(int num)
{
	GWINDOW win;
	char *t2="123456S";
	unsigned long value,total_money;
	int i;
	int opt;
	int ok;
	char temp[80];
	char desc[40];
	USE_SWAP use_swap;
	static int boundary[]={48, 88, 100,132,
						   120,88, 180,132,
						   200,88, 254,132,
						   48, 140,100,180,
						   120,140,180,180,
						   200,140,254,180,
						   40, 72, 230,78,
							-1,-1,-1,-1};

	distribute_draw_screen(&win);

	for (i=0; i<=P_NUM; i++)
		distribute_update_wahs(&TPP[i],i);

	total_money=0L;

	for (i=0; i<num; i++)
	{
		value=distribute_print_5(i,win.x1,win.y1,desc);

		distribute_display_sell_price(value,win.x1,win.y1+9);

		ok=FALSE;

		while (!ok)
		{
			opt=mouse_in_range(boundary,t2,"");

			if (opt==6 && !party_next_to(TOWN))
			{
				GX("Ye must be within a town boundary to sell thine items!",BAD);
				ok=FALSE;
			}
			else
			if (opt==6)
			{
				total_money+=value;
				ok=TRUE;
			}
			else
			if (opt>P_NUM)
			{
				bad_sound();
				ok=FALSE;
			}
			else
			{
				if ((number_of_items(&TPP[opt])>=MAX_CARRY))
				{
					carry_no_more(&TPP[opt]);

					ok=FALSE;
				}
				else
				{
					use_swap.bit=pool[i];
					strcpy(use_swap.desc,desc);

					if (!validate_item_use(&TPP[opt],&use_swap))
					{
						ok=FALSE;
					}
					else
					{
						add_to_player(pool[i].item,
									  pool[i].type,
									  pool[i].status,
									  pool[i].poisoned,
									  &TPP[opt]);

						distribute_update_wahs(&TPP[opt],opt);

						ok=TRUE;
					}
				}
			}
		}
	}

	kill_gwindow(&win);

	if (total_money!=0L)
	{
		sprintf(temp,"Thy party hath sold items worth %lu GC to ye locals!",total_money);
		GX(temp,GOOD);

		for (i=0; i<=P_NUM; i++)
			TPP[i].cash+=total_money/(P_NUM+1);
	}
}

unsigned long _PASCAL distribute_print_5(int start,int x,int y,char *desc)
{
	int i,j;
	ITEM_POOL nothing;
	unsigned long value_of_top_item,v;
	char temp[50];

	nothing.item     = NOTHING;
	nothing.status   = ITEM_CARRIED;
	nothing.type     = NO_PLUS;
	nothing.poisoned = FALSE;

	for (i=start,j=0; i<start+5; i++,j++)
	{
		if (i>MAX_POOL)
			v=distribute_handle_an_item(x+2,y+3+j,4,&nothing,temp);
		else
			v=distribute_handle_an_item(x+2,y+3+j,4,&pool[i],temp);

		if (i==start)
		{
			strcpy(desc,temp);
			value_of_top_item=v;
		}
	}

	return(value_of_top_item);
}

void _PASCAL distribute_display_sell_price(unsigned long value,int x,int y)
{
	char temp[20];

	_settextposition(y,x+15);
	_outtext("          ");

	sprintf(temp,"%lu GC.",value);

	_settextcolor(5);
	_settextposition(y,x+15);
	_outtext(temp);
}

unsigned long distribute_handle_an_item(int x,int y,int col,ITEM_POOL *item,char *desc)
{
	char temp[50];
	int fin=FALSE;
	unsigned long v;
	unsigned long sell_v;
	int weapon_or_armour=FALSE;
	int string_size=23;

	if (item->item==NOTHING)
	{
		_settextposition(y,x);
		_outtext("                       ");

		strcpy(desc,"");

		return(0L);
	}

	switch(item->item)
	{
		case LEATHER_ARMOUR     : strcpy(temp,STR_LEATHER_ARMOUR);      v=5L;       break;
		case SPLINT_ARMOUR      : strcpy(temp,STR_SPLINT_ARMOUR);       v=70L;      break;
		case CHAIN_ARMOUR       : strcpy(temp,STR_CHAIN_ARMOUR);        v=90L;      break;
		case PLATE_ARMOUR       : strcpy(temp,STR_PLATE_ARMOUR);        v=800L;     break;
		case ELF_ARMOUR         : strcpy(temp,STR_ELF_ARMOUR);          v=2500L;    break;
		case DAGGER             : strcpy(temp,STR_DAGGER);              v=10L;      break;
		case AXE                : strcpy(temp,STR_AXE);                 v=15L;      break;
		case SHORT_SWORD        : strcpy(temp,STR_SHORT_SWORD);         v=20L;      break;
		case LONG_SWORD         : strcpy(temp,STR_LONG_SWORD);          v=50L;      break;
		case RAPIER             : strcpy(temp,STR_RAPIER);              v=80L;      break;
		case CLAYMORE           : strcpy(temp,STR_CLAYMORE);            v=150L;     break;
		case MACE               : strcpy(temp,STR_MACE);                v=15L;      break;
		case FLAIL              : strcpy(temp,STR_FLAIL);               v=40L;      break;
		case BOW                : strcpy(temp,STR_BOW);                 v=20L;      break;
		case CROSSBOW           : strcpy(temp,STR_CROSSBOW);            v=200L;     break;
		case HALBERD            : strcpy(temp,STR_HALBERD);             v=200L;     break;
		case SLING              : strcpy(temp,STR_SLING);               v=5L;       break;
		case SACK               : strcpy(temp,STR_SACK);                v=1L;       break;
		case BACK_PACK          : strcpy(temp,STR_BACK_PACK);           v=4L;       break;
		case TINDER_BOX         : strcpy(temp,STR_TINDER_BOX);          v=10L;      break;
		case HEAVY_CLOAK        : strcpy(temp,STR_HEAVY_CLOAK);         v=2L;       break;
		case HOODED_LANTERN     : strcpy(temp,STR_HOODED_LANTERN);      v=10L;      break;
		case THIEVES_TOOLS      : strcpy(temp,STR_THIEVES_TOOLS);       v=55L;      break;
		case RELIGIOUS_SYMBOL   : strcpy(temp,STR_RELIGIOUS_SYMBOL);    v=40L;      break;
		case LUTE				: strcpy(temp,STR_LUTE);				v=95L;		break;
		case GRIMOIRE			: strcpy(temp,STR_GRIMOIRE);			v=25L;		break;
		case SEXTANT			: strcpy(temp,STR_SEXTANT); 			v=95L;		break;
		case SMALL_SHIELD       : strcpy(temp,STR_SMALL_SHIELD);        v=10L;      break;
		case LARGE_SHIELD       : strcpy(temp,STR_LARGE_SHIELD);        v=60L;      break;
		case MEDIUM_SHIELD      : strcpy(temp,STR_MEDIUM_SHIELD);       v=25L;      break;
		case HELMET             : strcpy(temp,STR_HELMET);              v=15L;      break;
		case WYVERN_RING        : strcpy(temp,STR_WYVERN_RING);         v=5000L;    break;
		case DRAGON_RING        : strcpy(temp,STR_DRAGON_RING);         v=10000L;   break;
		case RING_OF_HEALING    : strcpy(temp,STR_RING_OF_HEALING);     v=5000L;    break;
		case MIND_SHIELD_RING   : strcpy(temp,STR_MIND_SHIELD_RING);    v=4000L;    break;
		case RING_OF_FIRE       : strcpy(temp,STR_RING_OF_FIRE);        v=6000L;    break;
		case RING_OF_ICICLES    : strcpy(temp,STR_RING_OF_ICICLES);     v=6000L;    break;
		case RING_OF_SWIMMING   : strcpy(temp,STR_RING_OF_SWIMMING);    v=3000L;    break;
		case WARMTH_RING        : strcpy(temp,STR_WARMTH_RING);         v=3000L;    break;
		case THUNDER_WAND       : strcpy(temp,STR_THUNDER_WAND);        v=8500L;    break;
		case ICE_WAND           : strcpy(temp,STR_ICE_WAND);            v=8500L;    break;
		case FIRE_WAND          : strcpy(temp,STR_FIRE_WAND);           v=8500L;    break;
		case HEALING_STAVE      : strcpy(temp,STR_HEALING_STAVE);       v=9500L;    break;
		case SUSTENANCE_WAND    : strcpy(temp,STR_SUSTENANCE_WAND);     v=6000L;    break;
		case DEVOURING_ROD		: strcpy(temp,STR_DEVOURING_ROD);		v=15000L;	break;
		case CURIOUS_BOX		: strcpy(temp,STR_CURIOUS_BOX); 		v=10L;		break;
		case ORB_TITAN          : strcpy(temp,STR_ORB_TITAN);           v=9500L;    break;
		case ORB_DEXTERITY      : strcpy(temp,STR_ORB_DEXTERITY);       v=9500L;    break;
		case ORB_WISE           : strcpy(temp,STR_ORB_WISE);            v=9500L;    break;
		case ORB_FORTUNE        : strcpy(temp,STR_ORB_FORTUNE);         v=9500L;    break;
		case ORB_MEDITATION     : strcpy(temp,STR_ORB_MEDITATION);      v=9500L;    break;
		case ORB_STAMINA        : strcpy(temp,STR_ORB_STAMINA);         v=9500L;    break;
		case ORB_BEAUTY         : strcpy(temp,STR_ORB_BEAUTY);          v=9500L;    break;
		case RELIC              : strcpy(temp,STR_RELIC);               v=10000L;   break;
		case TOME               : strcpy(temp,STR_TOME);                v=10000L;   break;
		case ELFIN_CLOAK        : strcpy(temp,STR_ELFIN_CLOAK);         v=6000L;    break;
		case ELFIN_BOOTS        : strcpy(temp,STR_ELFIN_BOOTS);         v=6000L;    break;
		case BRACERS_POISON     : strcpy(temp,STR_BRACERS_POISON);      v=5000L;    break;
		case PENDANT_HEALTH     : strcpy(temp,STR_PENDANT_HEALTH);      v=5000L;    break;
		case GLOVES_NIMBLENESS  : strcpy(temp,STR_GLOVES_NIMBLENESS);   v=6000L;    break;
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
											case PLUS_1     :   strcat(temp," (+1)");  v*=PLUS_1_COST;  break;
											case PLUS_2     :   strcat(temp," (+2)");  v*=PLUS_2_COST;  break;
											case PLUS_3     :   strcat(temp," (+3)");  v*=PLUS_3_COST;  break;
											default         :   break;
										}

										if (item->poisoned)
											strcat(temp," (P)");

										weapon_or_armour=TRUE;

										break;

			case POTION             :   strcat(temp,potion_get_colour(item->type,TRUE));

										switch(item->type)
										{
											case POT_SECRET_DOOR :  v=500L; break;
											case POT_STRENGTH    :  v=500L; break;
											case POT_STRIKING    :  v=500L; break;
											case POT_UNDEAD_TURN :  v=500L; break;
											case POT_FIRE_RESIST :  v=500L; break;
											case POT_COLD_RESIST :  v=500L; break;
											case POT_HEALING     :  v=75L;  break;
											case POT_REVIVING    :  v=80L;  break;
											case POT_POISON      :  v=500L; break;
											case POT_HOLYWATER   :  v=75L;  break;
											case POT_NOTHING     :  v=500L; break;
											case POT_CURE_DISEASE:	v=500L; break;
											case POT_ALCOHOL	 :	v=40L;	break;
										}

										break;

			default                 :   break;
		}
	}
	else
	{
		strcpy(desc,"");
		return(0L);
	}

	strcpy(desc,temp);

	while (strlen(temp)<(size_t)string_size)
		strcat(temp," ");

	_settextcolor(col);
	_settextposition(y,x);
	_outtext(temp);

	sell_v=v;

	if (weapon_or_armour)
		sell_v-=(sell_v/5);
	else
		sell_v-=(sell_v/10);

	if (sell_v==0L)
		sell_v=1L;

	return(sell_v);
}

void _PASCAL distribute_draw_screen(GWINDOW *win)
{
	int i,j;
	int y=85;
	int col=3;
	char *title="Redistributing all items";

	win->x1=5;
	win->y1=1;
	win->x2=34;
	win->y2=25;
	win->back=0;
	win->border=3;

	make_gwindow(win);

	_settextcolor(11);
	_settextposition(win->y1+1,20-strlen_half(title));
	_outtext(title);

	_settextcolor(14);
	_settextposition(win->y1+3,win->x1+1);
	_outtext("                         ");

	distribute_arrange_draw();

	for (i=35,j=0; i<262; i+=3,j++)
	{
		if (j&1)
		{
			FFPLOT(i,  y  ,(char)col);
			FFPLOT(i+1,y  ,(char)col);
			FFPLOT(i+2,y  ,(char)col);

			FFPLOT(i,  y+2,(char)col);
			FFPLOT(i+1,y+2,(char)col);
			FFPLOT(i+2,y+2,(char)col);
		}
		else
		{
			FFPLOT(i,  y+1,(char)col);
			FFPLOT(i+1,y+1,(char)col);
			FFPLOT(i+2,y+1,(char)col);
		}
	}

	_settextcolor(5);
	_settextposition(win->y1+9,win->x1+1);
	_outtext("Sell Item for");

	_settextcolor(13);
	_settextposition(win->y1+9,win->x1+1);
	_outtext("S");
}

void _PASCAL distribute_arrange_draw()
{
	int i,j;
	int xpos,ypos;
	char temp[30];
	int x,y;

	for (i=0; i<=P_NUM; i++)
	{
		switch(i)
		{
			case 0 : xpos=65 ; ypos=90;  break;
			case 1 : xpos=140; ypos=90;  break;
			case 2 : xpos=215; ypos=90;  break;
			case 3 : xpos=65 ; ypos=140; break;
			case 4 : xpos=140; ypos=140; break;
			case 5 : xpos=215; ypos=140; break;
		}

		y=ypos+28;
		x=xpos-14;

		_setcolor(9);

		_rectangle(_GBORDER,x,y,x+42,y+20);
		_moveto(x+42/2,y);
		_lineto(x+42/2,y+20);
		_moveto(x,y+20/2);
		_lineto(x+42,y+20/2);

		FFPLOT(x,y,0);
		FFPLOT(x+42,y,0);
		FFPLOT(x+42,y+20,0);
		FFPLOT(x,y+20,0);

		FFPLOT(x+1,y+1,9);
		FFPLOT(x+41,y+1,9);
		FFPLOT(x+41,y+19,9);
		FFPLOT(x+1,y+19,9);

		draw_adv_image(TPP[i].nclass,xpos,ypos);

		if (player_is_dead(&TPP[i]))
				print_small_dead(xpos-1,
								 ypos+5,
								 14);

		sprintf(temp,"  %s",TPP[i].name);

		j=(xpos+8)-(strlen(temp)*4)/2;

		write_little(temp,
					 j,
					 ypos+22,
					 12,
					 FAST);

		sprintf(temp,"%d",i+1);

		write_little(temp,
					 j,
					 ypos+22,
					 14,
					 FAST);
	}
}

void _PASCAL distribute_update_wahs(PLAYER *adv,int num)  /* weap, arm, helm, shld */
{
	int has_w=FALSE;
	int has_a=FALSE;
	int has_h=FALSE;
	int has_s=FALSE;
	int i;
	int xpos,ypos;

	switch(num)
	{
		case 0 : xpos=65 ; ypos=90;  break;
		case 1 : xpos=140; ypos=90;  break;
		case 2 : xpos=215; ypos=90;  break;
		case 3 : xpos=65 ; ypos=140; break;
		case 4 : xpos=140; ypos=140; break;
		case 5 : xpos=215; ypos=140; break;
	}

	for (i=0; i<MAX_CARRY; i++)
	{
		switch(adv->items_carried[i].item)
		{
			case LEATHER_ARMOUR     :
			case SPLINT_ARMOUR      :
			case CHAIN_ARMOUR       :
			case PLATE_ARMOUR       :
			case ELF_ARMOUR         :  has_a=TRUE; break;

			case DAGGER             :
			case AXE                :
			case SHORT_SWORD        :
			case LONG_SWORD         :
			case RAPIER             :
			case CLAYMORE           :
			case MACE               :
			case FLAIL              :
			case BOW				:
			case SLING				:
			case CROSSBOW           :
			case HALBERD            :  has_w=TRUE; break;

			case SMALL_SHIELD       :
			case MEDIUM_SHIELD      :
			case LARGE_SHIELD       :  has_s=TRUE; break;

			case HELMET             :  has_h=TRUE; break;

			default                 :  break;
		}
	}

	if (has_w)
		draw_wahs_w(xpos-6,ypos+30);

	if (has_a)
		draw_wahs_a(xpos+14,ypos+30);

	if (has_h)
		draw_wahs_h(xpos-6,ypos+41);

	if (has_s)
		draw_wahs_s(xpos+16,ypos+41);
}

int _PASCAL take_items_from_adv(PLAYER *adv)
{
	int i;
	int item_found=FALSE;
	ITEM_POOL nothing;

	nothing.item     = NOTHING;
	nothing.status   = ITEM_CARRIED;
	nothing.type     = NO_PLUS;
	nothing.poisoned = FALSE;

	for (i=0; i<MAX_CARRY; i++)
	{
		if (adv->items_carried[i].item!=NOTHING)
		{
			pool[items_in_pool]=adv->items_carried[i];
			adv->items_carried[i]=nothing;

			if (pool[items_in_pool].status==ITEM_HELD)
				pool[items_in_pool].status=ITEM_CARRIED;

			items_in_pool++;

			item_found=TRUE;
		}
	}

	if (item_found)
	{
		adv->helmet_used=nothing;
		adv->shield_used=nothing;
		adv->weapon_used=nothing;
		adv->armour_used=nothing;
		adv->ring_used  =nothing;
	}

	return(item_found);
}
