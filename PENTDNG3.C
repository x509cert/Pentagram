#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <io.h>
#include <string.h>
#include "butil.h"
#include "mmalloc.h"

static char _FAR *dng_menu;

void _PASCAL load_dungeon_menu()
{
	long size;
	FILE *fptr;
	char temp[80];

	sprintf(temp,"%sDUNGMENU.PIC",PIC_DIRECTORY);

	fptr=fopen(temp,"rb");

	if (fptr==NULL)
		panic_FILE(temp);

	size=filelength(fileno(fptr));

	dng_menu=(char _FAR *)Mmalloc((size_t)size);

	if (dng_menu==(char _FAR *)NULL)
		panic_RAM("DUNGMENU.PIC");

	fread((void *)dng_menu,(size_t)size,1,fptr);

	fclose(fptr);
}

void _PASCAL clr_dng_menu_heap()
{
	Mfree((void *)dng_menu);
}

void _PASCAL deal_with_dungeon_menu()
{
	int x=167;
	int y=0;
	int fin=FALSE;
	int mouse_status=fast_mouse;
	int resting=FALSE;
	static int boundary[]={180,14,202,33,
						   219,11,237,33,
						   251,12,274,33,
						   287,13,306,33,
						   182,40,201,61,
						   219,40,233,61,
						   252,40,271,61,
						   284,40,307,61,
						   182,68,199,89,
						   213,68,239,89,
						   251,68,271,89,
						   281,68,309,89,
						   226, 95,261,107,
						   -1,-1,-1,-1};

	_getimage(x,y,x+152,y+121,(char _FAR *)all_menu_bkgrnd);

	_putimage(x,y,dng_menu,_GPSET);

	while (!fin)
	{
		switch(mouse_in_range(boundary,"SUPGECHDRATIF","SUPGECHDRATIQ"))
		{
			case 0 : dng_search();
					 break;

			case 1 : dng_useitem();
					 break;

			case 2 : dng_drink_potion();
					 break;

			case 3 : dng_swap_item();
					 break;

			case 4 : dng_equip();
					 break;

			case 5 : _putimage(x,y,all_menu_bkgrnd,_GPSET);
					 fin=TRUE;
					 dng_cast_spell();
					 break;

			case 6 : dng_chest();
					 break;

			case 7 : dng_door();
					 break;

			case 8 : _putimage(x,y,all_menu_bkgrnd,_GPSET);
					 fin=TRUE;
					 resting=TRUE;
					 dng_rest();
					 break;

			case 9 : dng_rearrange();
					 break;

			case 10: dng_eat();
					 break;

			case 11: dng_inspect();
					 break;

			default: fin=TRUE;
					 break;
		}
	}

	if (!resting)
		_putimage(x,y,all_menu_bkgrnd,_GPSET);

	dungeon_print_level(the_party.dungeon_level);

	fast_mouse=mouse_status;
}

void _PASCAL dng_search()
{
	static char temp[120];
	char *desc;
	char name[30];
	char *level;
	int i;
	int look;
	DUNGEON_SQUARE feat;

	memcpy((void *)&feat,
		   (void *)&dungeon.map[the_party.dungeon_level]
							   [the_party.dungeon_x]
							   [the_party.dungeon_y],
		   sizeof(feat));

	for (i=0; i<MAX_DUNGEONS; i++)
		if (pent_data.x==look_dungeons[i].x_position &&
			pent_data.y==look_dungeons[i].y_position)
			strcpy(name,look_dungeons[i].name);

	look=TRUE;

	switch(feat.feature)
	{
		case DNG_STAIRS_UP		:	desc="by some upward winding steps";
									break;

		case DNG_STAIRS_DOWN	:	desc="by some steps leading down";
									break;

		case DNG_TRAP			:	desc="in a dungeon passage, next to a triggered trap";
									break;
		case DNG_EMPTY_CHEST    :
		case DNG_TRAPPED_CHEST  :
		case DNG_TR_LOCK_CHEST  :
		case DNG_LOCKED_CHEST   :
		case DNG_CHEST			:	desc="by a chest";
									break;

		case DNG_WATER			:	desc="in some water";
									break;

		case DNG_SECRET_DOOR	:	desc="in a secret doorway";
									break;
		case DNG_DOOR           :
		case DNG_HEAVY_DOOR     :
		case DNG_LOCKED_DOOR	:	desc="in a doorway";
									break;

		case DNG_SPECIAL        :   land_on_dungeon_special(LOOKING);
									look=FALSE;
									break;

		case DNG_VOICE			:	desc="in a passage. A dweomer art vaguely present";
									break;
		case DNG_MONSTER        :
		case DNG_CORRIDOR		:	desc="in a dungeon passage";
									break;
	}

	if (look)
	{
		switch(the_party.dungeon_level+1)
		{
			case 1 :  level="first";  break;
			case 2 :  level="second"; break;
			case 3 :  level="third";  break;
			case 4 :  level="fourth"; break;
		}

		sprintf(temp,"Thy party art in %s, %s, on ye %s level.",
						name,
						desc,
						level);

		SCROLL(1,1,temp);

		determine_secret_doors_nearby();
	}
}

void _PASCAL determine_secret_doors_nearby()
{
	int x=the_party.dungeon_x;
	int y=the_party.dungeon_y;
	int z=the_party.dungeon_level;
	int i,j;
	int chance=0;
	static int srch[]={-1,-1,  0,-1,  1,-1,
					   -1, 0,		  1, 0,
					   -1, 1,  0, 1,  1, 1};

	for (i=0; i<=P_NUM; i++)
		chance=max(chance,effective_spot_secret_door(&TPP[i]));

	for (i=0; i<SIZE(srch); i+=2)
	{
		if (dungeon.map[z][x+srch[i]][y+srch[i+1]].feature==DNG_SECRET_DOOR)
		{
			if (percent()<=chance)
			{
				for (j=0; j<4; j++)
				{
					draw_one_dungeon_bit((x+srch[i])*DUNGEON_BIT_X,
										 (y+srch[i+1])*DUNGEON_BIT_Y,
										 DNG_CORRIDOR,0);

					if (!NO_SOUND)
						utspkr(500);

					delay(30);

					draw_one_dungeon_bit((x+srch[i])*DUNGEON_BIT_X,
										 (y+srch[i+1])*DUNGEON_BIT_Y,
										 DNG_SECRET_DOOR,0);

					if (!NO_SOUND)
						utspkr(300);

					delay(30);

					utspkr(0);
				}

				SCROLL(2,14,"A Hidden Door!");
			}
		}
	}
}

void _PASCAL dng_rest()
{
	if (dungeon.map[the_party.dungeon_level]
				   [the_party.dungeon_x]
				   [the_party.dungeon_y].feature==DNG_WATER)
	{
		GX("Thy party cannot rest in water!",BAD);
		return;
	}
	else
	{
		attempt_to_rest();
	}
}

void _PASCAL dng_rearrange()
{
	adv_rearrange();
}

void _PASCAL dng_eat()
{
	adv_eat();
}

void _PASCAL dng_inspect()
{
	adv_inspect();
}
void _PASCAL dng_useitem()
{
	adv_useitem();
}

void _PASCAL dng_drink_potion()
{
	drink_or_taste_potion();
}

void _PASCAL dng_swap_item()
{
	adv_swap_item();
}

void _PASCAL dng_equip()
{
	adv_equip();
}

void _PASCAL dng_cast_spell()
{
	adv_cast_spell();
}

void _PASCAL dng_door()
{
	int l,x,y;
	int dn,ds,de,dw;
	int fn,fs,fe,fw,fc;
	int person;
	char temp[80];
	int door;
	int door_type;

	l=the_party.dungeon_level;
	x=the_party.dungeon_x;
	y=the_party.dungeon_y;

	fn=dungeon.map[l][x][y-1].feature;
	fs=dungeon.map[l][x][y+1].feature;
	fe=dungeon.map[l][x+1][y].feature;
	fw=dungeon.map[l][x-1][y].feature;

	dn=ds=de=dw=FALSE;

	if (fn==DNG_HEAVY_DOOR || fn==DNG_DOOR || fn==DNG_LOCKED_DOOR)
		dn=TRUE;

	if (fs==DNG_HEAVY_DOOR || fs==DNG_DOOR || fs==DNG_LOCKED_DOOR)
		ds=TRUE;

	if (fe==DNG_HEAVY_DOOR || fe==DNG_DOOR || fe==DNG_LOCKED_DOOR)
		de=TRUE;

	if (fw==DNG_HEAVY_DOOR || fw==DNG_DOOR || fw==DNG_LOCKED_DOOR)
		dw=TRUE;

	if (!dn && !ds && !de && !dw)
	{
		fc=dungeon.map[l][x][y].feature;

		if (fc==DNG_HEAVY_DOOR || fc==DNG_DOOR || fc==DNG_LOCKED_DOOR)
			GX("Thy party art stood in a dungeon doorway!",BAD);
		else
			GX("There are no doors by ye party!",BAD);

		return;
	}

	person=adv_select_adventurer("Who's dealing","with ye door?",TRUE);

	if (person==ERR)
		return;

	if (abs(dn+ds+de+dw)>TRUE)
	{
		door=dng_handle_multiple_doors(dn,ds,de,dw,the_party.player[person].nclass);

		switch(door)
		{
			case DIR_NORTH  : door_type=fn; break;
			case DIR_SOUTH  : door_type=fs; break;
			case DIR_EAST   : door_type=fe; break;
			case DIR_WEST   : door_type=fw; break;
			default 		: return;
		}
	}
	else
	{
		if (dn)
		{
			door=DIR_NORTH;
			door_type=fn;
		}
		else
		if (ds)
		{
			door=DIR_SOUTH;
			door_type=fs;
		}
		else
		if (de)
		{
			door=DIR_EAST;
			door_type=fe;
		}
		else
		{
			door=DIR_WEST;
			door_type=fw;
		}
	}

	switch(door_type)
	{
		case DNG_HEAVY_DOOR  :  dng_deal_with_heavy_door(door,&the_party.player[person]);
								break;

		case DNG_LOCKED_DOOR :  dng_deal_with_locked_door(door,&the_party.player[person]);
								break;

		case DNG_DOOR        :  sprintf(temp,"%s opens Ye dungeon door quite easily!",
										the_party.player[person].name);

								SCROLL(1,14,temp);
								break;
	}
}

int _PASCAL dng_handle_multiple_doors(int dn,int ds,int de,int dw,int class)
{
	GWINDOW win;
	int direction;
	int fin=FALSE;
	static int boundary[]={219,48,231,61,
						   219,93,231,106,
						   244,70,256,82,
						   194,70,206,82,
						   210,114,245,126,
							-1,-1,-1,-1};

	win.x1=22;
	win.y1=4;
	win.x2=36;
	win.y2=18;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	click_box(210,114,B_QUIT);

	_settextcolor(11);
	_settextposition(win.y1+1,win.x1+2);
	_outtext("Which Door?");

	draw_adv_image(class,219,70);

	if (dn)
		print_big_dungeon_door(220,49);

	if (ds)
		print_big_dungeon_door(220,94);

	if (de)
		print_big_dungeon_door(245,70);

	if (dw)
		print_big_dungeon_door(195,70);

	while (!fin)
	{
		switch(mouse_in_range(boundary,"NSEWQ","\xC8\xD0\xCD\xCB\x46"))
		{
			case 0 : if (dn)
					 {
						direction=DIR_NORTH;
						fin=TRUE;
					 }
					 else
						bad_sound();

					 break;

			case 1 : if (ds)
					 {
						direction=DIR_SOUTH;
						fin=TRUE;
					 }
					 else
						bad_sound();

					 break;

			case 2 : if (de)
					 {
						direction=DIR_EAST;
						fin=TRUE;
					 }
					 else
						bad_sound();

					 break;

			case 3 : if (dw)
					 {
						direction=DIR_WEST;
						fin=TRUE;
					 }
					 else
						bad_sound();

					 break;

			default: fin=TRUE;
					 direction=ERR;
					 break;
		}
	}

	kill_gwindow(&win);

	return(direction);
}

void _PASCAL dng_deal_with_heavy_door(int door,PLAYER *adv)
{
	char temp[80];
	int res;

	res=effective_open_heavy_door(adv);

	sprintf(temp,"%s tries to open ye door with all %s strength!",
					adv->name,
					adv->his_her);

	SCROLL(1,1,temp);

	pause(1);

	if (percent()<=res)
	{
		SCROLL(1,14,"and Succeeds..!");
		good_sound();

		dng_door_handled_ok(door);

		add_xp_to_party(50L);
	}
	else
	{
		SCROLL(1,0,"But Fails.....");
		bad_sound();
	}
}

void _PASCAL dng_deal_with_locked_door(int door,PLAYER *adv)
{
	char temp[80];
	int res;
	char *tumb;
	int tumblers=dng_lock_difficulty(the_party.dungeon_level,
									 the_party.dungeon_x,
									 the_party.dungeon_y);

	if (!player_is_carrying(adv,THIEVES_TOOLS))
	{
		sprintf(temp,"%s needs Thieves Tools to unlock ye door!",
						adv->name);

		GX(temp,BAD);
		return;
	}

	res=effective_pick_lock(adv)-(tumblers*2);

	if (adv->nclass==THIEF)
	{
		switch(tumblers)
		{
			case 1 : tumb="one";    break;
			case 2 : tumb="two";    break;
			case 3 : tumb="three";  break;
		}

		sprintf(temp,"%s notices ye lock hath %s tumbler%s...",
					adv->name,
					tumb,
					tumblers!=1?"s.":".");

		SCROLL(1,1,temp);

		pause(1);
	}

	sprintf(temp,"In %s attempt to unlock ye door, %s inserts a pick in ye lock..",
					adv->his_her,
					adv->name);

	SCROLL(1,1,temp);

	pause(2);

	if (percent()<=res)
	{
		SCROLL(1,14,"a sharp click indicates success!");
		good_sound();

		dng_door_handled_ok(door);

		add_xp_to_party(100L);
	}
	else
	{
		SCROLL(1,0,"But Fails.....");
		bad_sound();

		pause(1);

		res=effective_snap_thieves_tools(adv);

		if (percent()>res)
			dng_actually_snap_thieves_tools(adv,TRUE);
	}
}

void _PASCAL dng_actually_snap_thieves_tools(PLAYER *adv,int print_yn)
{
	int i;
	char temp[80];

	if (print_yn)
	{
		sprintf(temp,"To make matters worse, %s breaks %s lockpick!",
					adv->name,
					adv->his_her);

		SCROLL(1,0,temp);
		bad_sound();
	}

	for (i=0; i<MAX_CARRY; i++)
	{
		if (adv->items_carried[i].item==THIEVES_TOOLS)
		{
			adv->items_carried[i].item     = NOTHING;
			adv->items_carried[i].type     = 0;
			adv->items_carried[i].status   = ITEM_CARRIED;
			adv->items_carried[i].poisoned = FALSE;

			break;
		}
	}
}

void _PASCAL dng_door_handled_ok(int direction)
{
	switch(direction)
	{
		case DIR_NORTH  :   dungeon.map[the_party.dungeon_level]
									   [the_party.dungeon_x]
									   [the_party.dungeon_y-1].feature=DNG_DOOR;
							break;

		case DIR_SOUTH  :   dungeon.map[the_party.dungeon_level]
									   [the_party.dungeon_x]
									   [the_party.dungeon_y+1].feature=DNG_DOOR;
							break;

		case DIR_EAST   :   dungeon.map[the_party.dungeon_level]
									   [the_party.dungeon_x+1]
									   [the_party.dungeon_y].feature=DNG_DOOR;
							break;

		case DIR_WEST   :   dungeon.map[the_party.dungeon_level]
									   [the_party.dungeon_x-1]
									   [the_party.dungeon_y].feature=DNG_DOOR;
							break;
	}
}
