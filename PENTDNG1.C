#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <bkeybrd.h>
#include "mmalloc.h"

static char _FAR  *dungeon_buffer;

DUNGEON_LOOK_TY look_dungeons[MAX_DUNGEONS]=
	  {
		{"Dungeon of Lost Souls",
		 "Suicidal Adventurers Apply Within!",
		 "LOSTSOUL",
		 DN_LOSTSOUL,
		 16,172, 3,
		 DD_DIFFICULT},

		{"Catacombs of ye Damned",
		 "Fun Awaits Inside!",
		 "DAMNED",
		 DN_DAMNED,
		 43, 37,
		 4,
		 DD_DIFFICULT},

		{"Ye Crying Crypt",
		 "No Care or Responsibility taken!",
		 "CRYPT",
		 DN_CRYPT,
		 101,55,
		 2,
		 DD_TOUGH},

		{"Dungeon Mort",
		 "Have a nice day!",
		 "MORT",
		 DN_MORT,
		 176,11,
		 4,
		 DD_SUICIDAL},

		{"Dungeon Moribund",
		 "Sacrificial Adventurers Welcome!",
		 "MORIBUND",DN_MORIBUND,
		 94,131,
		 3,
		 DD_DANGEROUS},

		{"Hells Vault",
		 "Monster Feeding Time Soon!",
		 "HELLS",
		 DN_HELLS,
		 169,41,
		 4,
		 DD_VERY_DANGEROUS},

		{"Tomb of Misery",
		 "Absolutely no refunds!",
		 "MISERY",
		 DN_MISERY,
		 50,187,
		 1,
		 DD_SUICIDAL}
	  };

void _PASCAL divulge_dungeon_info(int x,int y)
{
	int i;
	int dun_num=ERR;
	char temp[100];

	for (i=0; i<SIZE(look_dungeons); i++)
		if (x==look_dungeons[i].x_position && y==look_dungeons[i].y_position)
			dun_num=i;

	kbflush();

	sprintf(temp,"\"Welcome to %s. %s\"",
				 look_dungeons[dun_num].name,
				 look_dungeons[dun_num].message);

	SCROLL(2,0,"A wooden sign reads:");
	SCROLL(2,14,temp);

	general_low_sound();
}

int _PASCAL get_dungeon_number(int x,int y)
{
	int i,j;

	for (i=0; i<SIZE(look_dungeons); i++)
	{
		if (x==look_dungeons[i].x_position && y==look_dungeons[i].y_position)
		{
			switch(i)
			{
				case 0 :  j=DN_LOSTSOUL; break;
				case 1 :  j=DN_DAMNED;   break;
				case 2 :  j=DN_CRYPT;    break;
				case 3 :  j=DN_MORT;     break;
				case 4 :  j=DN_MORIBUND; break;
				case 5 :  j=DN_HELLS;    break;
				default:  j=DN_MISERY;   break;
			}

			break;
		}
	}

	return(j);
}

char *get_dungeon_basename(int number)
{
	int i;

	for (i=0; i<MAX_DUNGEONS; i++)
		if (number==look_dungeons[i].nname)
			return(look_dungeons[i].file_name);
}

void _PASCAL place_dungeon_map()
{
	unsigned long size;

	size=_imagesize(0,0,153,119);

	dungeon_buffer=(char _FAR *)Mmalloc((size_t)size);

	if (dungeon_buffer==(char _FAR *)NULL)
		panic_RAM("DUNGEON");

	_getimage(0,0,
			  153,119,
			  (char _FAR *)dungeon_buffer);

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,0,0,153,117);

	_setcolor(4);
	_rectangle(_GFILLINTERIOR,6,6,153,115);

	generic_pic_draw(10,9,"DUNGBACK");
}

void _PASCAL kill_dungeon_map()
{
	_setcolor(0);
	_rectangle(_GFILLINTERIOR,202,23,230,29);

	_putimage(0,0,(char _FAR *)dungeon_buffer,_GPSET);

	Mfree((void *)dungeon_buffer);
}

void _PASCAL actually_enter_dungeon()
{
	int out_alive;
	char dungeon_basename[20];
	int dungeon_num;
	unsigned long in_time, out_time;

	kill_map();

	place_dungeon_map();

	dungeon_num=get_dungeon_number(pent_data.x, pent_data.y);
	strcpy(dungeon_basename,get_dungeon_basename(dungeon_num));

	load_dungeon(dungeon_basename);
	load_dungeon_menu();

	init_dungeon_entry();

	if (dungeon.nname==DN_MISERY)
		nullify_all_in_effect_party();

	in_time=convert_date_to_half_hours(pent_data.date,
									   pent_data.time_hour,
									   pent_data.time_minute);

	SCROLL(2,1,"Thy party descends ye dungeon steps...");

	stairs_down_sound();

	check_fall_down_steps();

	if (dungeon.nname==DN_MISERY)
	{
		SCROLL(1,0,"A dull, lethargic sensation envelops thy party!");

		bad_sound();
		pause(1);
	}

	explore_dungeon(&out_alive);

	save_dungeon(dungeon_basename);

	clr_dng_menu_heap();

	kill_dungeon_map();

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,260,29,295,45);   /* Remove "Level #" */

	IN_DUNGEON=FALSE;

	night_flagged=FALSE;

	draw_first_day_night();

	place_map();

	if (is_night_time())
		draw_night_map();
	else
		draw_first_map();

	draw_map(99);       /* 99= No Direction */

	out_time=convert_date_to_half_hours(pent_data.date,
										pent_data.time_hour,
										pent_data.time_minute);

	remark_on_leaving_dungeon(in_time,out_time);
}

void _PASCAL remark_on_leaving_dungeon(unsigned long in,unsigned long out)
{
	static char temp[200];
	static char *welcome[]={"welcomes",
							"greets",
							"embraces"};

	static char *air[]={"rotten",
						"putrid",
						"filthy",
						"disgusting",
						"gross",
						"smelly",
						"ransid",
						"reeking",
						"humid",
						"damp",
						"dirty"};
	int which;
	unsigned long diff;

	if (is_all_party_dead())
		return;

	diff=(unsigned long)((long)out-(long)in);
	diff/=2L;

	if (diff<=2L)
		return;

	which=rand()%(SIZE(air));

	sprintf(temp,"After breathing %s dungeon air for %lu hours, "
				 "Thy party %s ye fresh, clean outdoors!",
				 air[which],
				 diff,
				 welcome[rand()%3]);

	SCROLL(1,14,temp);

	good_sound();
}

void _PASCAL init_dungeon_entry()
{
	int i,j;

	the_party.dungeon_current_feature=DNG_STAIRS_UP;
	IN_DUNGEON=TRUE;

	the_party.dungeon_level=0;

	for (i=0; i<MAX_DUNGEON_Y; i++)
	{
		for (j=0; j<MAX_DUNGEON_X; j++)
		{
			if (dungeon.map[0][j][i].feature==DNG_STAIRS_UP)
			{
				the_party.dungeon_x=j;
				the_party.dungeon_y=i;

				break;
			}
		}
	}
}

void _PASCAL load_dungeon(char *name)
{
	char file[35];
	FILE *fptr;

	sprintf(file,"%s%s.%s",DUNGEON_DIRECTORY,
						   name,
						   DUNGEON_SAVED_SUFFIX);

	fptr=fopen(file,"rb");

	if (fptr==(FILE *)NULL)
		panic_FILE(file);

	fread((void *)&dungeon,sizeof(dungeon),1,fptr);
	fclose(fptr);

	decrypt_dungeon_descriptions();
}

void _PASCAL save_dungeon(char *name)
{
	char file[35];
	FILE *fptr;

	sprintf(file,"%s%s.%s",DUNGEON_DIRECTORY,
						   name,
						   DUNGEON_SAVED_SUFFIX);

	encrypt_dungeon_descriptions();

	fptr=fopen(file,"wb");

	if (fptr==(FILE *)NULL)
		panic_FILE(name);

	fwrite((void *)&dungeon,sizeof(dungeon),1,fptr);
	fclose(fptr);

	decrypt_dungeon_descriptions();
}

void _PASCAL encrypt_dungeon_descriptions()
{
	decrypt_dungeon_descriptions();
}

void _PASCAL decrypt_dungeon_descriptions()
{
	int i,j;

	for (i=0; i<MAX_DUNGEON_DESCRIP; i++)
		for (j=0; j<40; j++)
			dungeon.descrip[i][j]^=DNGN_ENCRYPT_CODE;
}

int _PASCAL take_dungeon_level_down()
{
	return(handle_dungeon_up_down("down ye dungeon steps?"));
}

int _PASCAL take_dungeon_level_up()
{
	return(handle_dungeon_up_down("up ye dungeon steps?"));
}

int _PASCAL handle_dungeon_up_down(char *line2)
{
	GWINDOW win;
	int res;
	int col;
	int down=(strstr(line2,"dow")!=NULL);
	char *l1=" Doth ye wish to go";
	static int boundary[]={120,65,155,77,
						   175,65,210,77,
						   -1,-1,-1,-1};

	win.x1=5;
	win.x2=35;
	win.y1=5;
	win.y2=12;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	if (down)
		draw_dungeon_in(50,45);
	else
		draw_dungeon_out(50,45);

	_settextcolor(6);
	_settextposition(6,12);
	_outtext(l1);

	_settextposition(7,12);
	_outtext(line2);

	click_box(120,65,B_YES);
	click_box(175,65,B_NO);

	if (down)
	{
		if (percent()>50)
		{
			switch(rand()%6)
			{
				case 0 : col= 4; break;
				case 1 : col= 9; break;
				case 2 : col=10; break;
				case 3 : col=12; break;
				case 4 : col=13; break;
				default: col=14; break;
			}

			delay(400);

			FFPLOT(64,57,(char)col);
			FFPLOT(66,57,(char)col);

			delay(500);

			FFPLOT(64,57,(char)0);
			FFPLOT(66,57,(char)0);
		}
	}

	switch(mouse_in_range(boundary,"YN","YQ"))
	{
		case 0 : res=TRUE; break;
		default: res=FALSE; break;
	}

	kill_gwindow(&win);

	return(res);
}

void _PASCAL draw_dungeon_in(int x,int y)
{
	generic_pic_draw(x,y,"DUNGIN");
}

void _PASCAL draw_dungeon_out(int x,int y)
{
	generic_pic_draw(x,y,"DUNGOUT");
}
