#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <string.h>
#include <butil.h>
#include "mmalloc.h"

#define CBOX_X		74

int _PASCAL use_curious_box(PLAYER *adv)
{
	GWINDOW win;
	char temp[60];
	int dead=FALSE;
	char *t="Select an option..";
	static int boundary[]= {137,115,160,126,	 /* Off 	   */
							137,99, 160,110,	 /* On/Another */
							-1,-1,-1,-1};

	if (IN_COMBAT)
	{
		cmbt_bad_msg("Ye curious box art too cumbersome!",TRUE);
		return(FALSE);
	}

	if (bard_is_singing(adv,"use ye curious box"))
		return(FALSE);

	sprintf(temp,"%s examines ye curious box...",adv->name);
	SCROLL(1,14,temp);

	general_low_sound();
	pause(1);

	win.x1=7;
	win.y1=2;
	win.x2=24;
	win.y2=20;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	generic_pic_draw(58,17,"CM_BOX");

	if (mouse_in_range(boundary,"Q ","")!=0)
	{
		if (pent_data.curious_box_used<=CURIOUS_BOX_DEAD)
		{
			CBOX_turn_on();

			if (pent_data.curious_box_used>30)
				CBOX_battery_low();

			CBOX_handle_place_name();

			CBOX_scroll();
			CBOX_scroll();
			CBOX_write(t,11);

			while(mouse_in_range(boundary,"Q ","")!=0)
			{
				CBOX_handle_place_name();

				CBOX_scroll();
				CBOX_scroll();
				CBOX_write(t,11);
			}

			CBOX_turn_off();
		}
		else
			dead=TRUE;
	}

	kill_gwindow(&win);

	if (dead)
	{
		SCROLL(2,0,"Ye curious box isn't responding!");
		solemn_sound();
	}

	sprintf(temp,"carefully, %s puts ye curious box away..",adv->name);
	SCROLL(1,14,temp);

	return(TRUE);
}

void _PASCAL CBOX_battery_low()
{
	CBOX_led(76,110,12,15);
}

void _PASCAL CBOX_turn_off()
{
	CBOX_scroll();
	CBOX_scroll();

	CBOX_write("THANK YOU FOR USING",15);
	CBOX_scroll();
	CBOX_write("THIS O.C.C. SERVICE",15);
	half_pause();
	
	CBOX_scroll();
	CBOX_scroll();
	CBOX_write("YOUR UNIVERSAL BANK",15);
	CBOX_scroll();
	CBOX_write("ACCOUNT HAS BEEN",15);
	CBOX_scroll();
	CBOX_write("DEBITED ACCORDINGLY.",15);

	half_pause();

	CBOX_scroll();
	CBOX_scroll();
	CBOX_write("Unlinking satellite..",14);

	half_pause();
	
	CBOX_scroll();
	CBOX_write("Comms. Lost",0);

	CBOX_led(76,100,4,12);

	half_pause();
	
	generic_pic_draw(58,17,"CM_BOX");

	half_pause();
}

void _PASCAL CBOX_self_test()
{
	int i;
	static char *t[]={"RAM OK",
					  "ROM OK",
					  "COMMS MODULE OK",
					  "VOICE MODULE OK"};
	half_pause();

	CBOX_scroll();
		
	for (i=0; i<SIZE(t); i++)
	{
		CBOX_write(t[i],14);
		half_pause();
		CBOX_scroll();
	}

	CBOX_print_battery_level();

	CBOX_scroll();
	CBOX_scroll();
}

void _PASCAL CBOX_print_battery_level()
{
	char *t="OK";
	char temp[40];

	if (++pent_data.curious_box_used>10)
		t="HIGH";

	if (pent_data.curious_box_used>20)
		t="MEDIUM";

	if (pent_data.curious_box_used>30)
		t="LOW";

	if (pent_data.curious_box_used>40)
		t="VERY LOW";

	sprintf(temp,"BATTERY %s",t);
	CBOX_write(temp,14);
}

void _PASCAL CBOX_handle_place_name()
{
	char name[30];
	char *t="ENTER SEARCH NAME:";

	CBOX_scroll();
	CBOX_scroll();
	CBOX_write(t,15);

	_settextposition(11,10);
	_outtext("           ");

	do
	{
		strcpy(name,gquery(10,11,10,3,'A',""));

		if (strlen(name)<3)
		{
			CBOX_scroll();
			CBOX_scroll();
			bad_sound();
			CBOX_write("SEARCH NAME TOO SHORT",0);
			CBOX_scroll();
			CBOX_write(t,15);

			_settextposition(11,10);
			_outtext("           ");
		}

	} while (strlen(name)<3);

	CBOX_search_database(name);
}

void _PASCAL CBOX_search_database(char *place)
{
	int i,num;
	int found=FALSE;
	int town=FALSE;
	int deity=FALSE;

	CBOX_scroll();
	CBOX_scroll();
	CBOX_write("SEARCHING...",15);
		
	for (i=0; i<2+rand()%4; i++)
	{
		CBOX_led(76,120,12,15);
		delay(400);
		CBOX_led(76,120,4,12);
		delay(200);
	}

	for (i=0; i<MAX_SMALLTOWNS; i++)
	{
		if (strnicmp(place,small_towns[i].name,strlen(place))==0)
		{
			num=i;
			found=town=TRUE;
		}
	}

	if (!found)
	{
		for (i=0; i<MAX_DEITIES; i++)
		{
			if (strnicmp(place,deities[i].name,strlen(place))==0)
			{
				num=i;
				found=deity=TRUE;
			}
		}
	}

	if (!found)
	{
		for (i=0; i<MAX_DUNGEONS; i++)
		{
			if (stristr(look_dungeons[i].name,place)!=NULL)
			{
				num=i;
				found=TRUE;
			}
		}
	}

	if (found)
	{
		CBOX_scroll();
		good_sound();
		CBOX_write("Found!",15);

		CBOX_scroll();
		CBOX_scroll();

		if (town)
			CBOX_town_found(num);
		else
		if (deity)
			CBOX_deity_found(num);
		else
			CBOX_dungeon_found(num);

		pause(2);
	}
	else
		CBOX_notfound();
}

void _PASCAL CBOX_deity_found(int num)
{
	char temp[80];
	int i;

	sprintf(temp,"Name  : %s",deities[num].name);
	CBOX_write(temp,14);
	CBOX_scroll();

	sprintf(temp,"Sphere: %s",deities[num].sphere);
	CBOX_write(temp,14);
	CBOX_scroll();

	sprintf(temp,"Sex   : %s",deities[num].sex==SX_MALE?"Male":"Female");
	CBOX_write(temp,14);
	CBOX_scroll();

	CBOX_write("Town  :",14);

	for (i=0; i<MAX_SMALLTOWNS; i++)
	{
		if (deities[num].ndeity==small_towns[i].ndeity)
		{
			sprintf(temp,"        %s",small_towns[i].name);
			CBOX_write(temp,14);
			CBOX_scroll();
		}
	}
}

void _PASCAL CBOX_town_found(int num)
{
	char temp[80];
	char ew[10],ns[10];
	char *type;
	int x,y;

	switch(small_towns[num].town_type)
	{
		case TWN_CITY    : type="city";     break;
		case TWN_HAMLET  : type="hamlet";   break;
		case TWN_VILLAGE : type="village";  break;
		case TWN_TOWN    : type="town";     break;
	}

	x=small_towns[num].x_position;
	y=small_towns[num].y_position;

	if (x<=89)
		sprintf(ew,"%d~W",89-x);
	else
		sprintf(ew,"%d~E",x-89);

	if (y<=86)
		sprintf(ns,"%d~N",86-y);
	else
		sprintf(ns,"%d~S",y-86);

	sprintf(temp,"Name  : %s",small_towns[num].name);
	CBOX_write(temp,14);
	CBOX_scroll();

	sprintf(temp,"Status: %s",type);
	CBOX_write(temp,14);
	CBOX_scroll();

	sprintf(temp,"Loc.  : %s, %s",ns,ew);
	CBOX_write(temp,14);
	CBOX_scroll();

	sprintf(temp,"Deity : %s",get_deity_name_in_town(x,y));
	CBOX_write(temp,14);
}

void _PASCAL CBOX_dungeon_found(int num)
{
	char temp[80];
	char ew[10],ns[10];
	int x,y;

	x=look_dungeons[num].x_position;
	y=look_dungeons[num].y_position;

	if (x<=89)
		sprintf(ew,"%d~W",89-x);
	else
		sprintf(ew,"%d~E",x-89);

	if (y<=86)
		sprintf(ns,"%d~N",86-y);
	else
		sprintf(ns,"%d~S",y-86);

	CBOX_write("Name  :",14);
	CBOX_scroll();

	strcpy(temp,look_dungeons[num].name);
	CBOX_write(temp,14);
	CBOX_scroll();

	sprintf(temp,"Loc.  : %s, %s",ns,ew);
	CBOX_write(temp,14);
	CBOX_scroll();

	sprintf(temp,"Levels: %d",look_dungeons[num].number_of_levels);
	CBOX_write(temp,14);
}

void _PASCAL CBOX_notfound()
{
	CBOX_scroll();
	CBOX_write("NOT FOUND!",0);
}

void _PASCAL CBOX_led(int x,int y,int c1,int c2)
{
	static char cm_led[][7]={
							  {0x0,0x4,0x4,0x4,0x4,0x4,0x0},
							  {0x4,0x4,0x4,0x4,0x4,0x4,0x4},
							  {0x4,0xC,0x4,0x4,0x4,0x4,0x4},
							  {0x4,0xC,0x4,0x4,0x4,0x4,0x4},
							  {0x4,0x4,0xC,0xC,0x4,0x4,0x4},
							  {0x0,0x4,0x4,0x4,0x4,0x4,0x0},
							};
	int i,j;
	char c;

	for (i=0; i<6; i++)
		for (j=0; j<7; j++)
			 if (c=cm_led[i][j])
				FFPLOT(x+j,y+i,(char)(c==4?c1:c2));
}

void _PASCAL CBOX_scroll()
{
	char _FAR *image;
	long image_sz;

	image_sz=_imagesize(72,40,159,67);
	image=(char _FAR *)Mmalloc((size_t)image_sz);

	if (image==NULL)
		panic_RAM("Box Scroll");

	_getimage(72,40,159,67,image);

	_setcolor(9);
	_rectangle(_GFILLINTERIOR,72,61,159,67);

	_putimage(72,34,image,_GPSET);

	Mfree(image);
}

void _PASCAL CBOX_write(char *msg,int col)
{
	unsigned i;
	char temp[3];
	
	temp[1]='\0';
	
	for (i=0; i<strlen(msg); i++)
	{
		if (!isspace(msg[i]))
		{
			temp[0]=msg[i];

			write_little(temp,CBOX_X+i*4,62,col,FAST);

			if (!NO_SOUND)
				utspkr(800);

			delay(50);
			utspkr(0);
			delay(20);
		}
	}
}

void _PASCAL CBOX_turn_on()
{
	int i;
	char temp[40];

	generic_pic_draw(70,32,"CM_BOXON");
	CBOX_led(151,23,10,15);
	delay(200);

	CBOX_please_wait();
	CBOX_self_test();

	CBOX_write("ODIN CYBERNETIC CORP.",15);
	CBOX_scroll();
	CBOX_write("Gadget Dept.",15);

	half_pause();

	CBOX_scroll();
	CBOX_scroll();

	CBOX_write("ESTABLISHING LINK..",15);

	half_pause();

	for (i=0; i<4; i++)
	{
		if (!NO_SOUND)
			utspkr(7000);

		delay(100);
		utspkr(0);
		delay(800);
	}

	half_pause();
	CBOX_scroll();

	CBOX_led(76,100,12,15);
	CBOX_write("SATELLITE 'WAYWARD IV'",15);
	CBOX_scroll();
	CBOX_write("RESPONDING....",15);
	CBOX_scroll();
	CBOX_scroll();

	sprintf(temp,"FREQUENCY %u MHz",1200+rand()%200);
	CBOX_write(temp,15);

	half_pause();

	CBOX_scroll();
	CBOX_scroll();

	CBOX_write("YOUR LOCATION:",15);
	CBOX_scroll();
	CBOX_write("COMMAN NAME:",14);
	CBOX_scroll();
	CBOX_write("   REALMS, YE",11);
	CBOX_scroll();
	CBOX_write("GALACTIC LOCATION:",14);
	CBOX_scroll();
	CBOX_write("   TG12-6P1-AA",11);

	half_pause();
}

void _PASCAL CBOX_please_wait()
{
	int i;

	if (!NO_SOUND)
		utspkr(2000);

	delay(100);
	utspkr(0);

	half_pause();

	write_little("Please Wait",CBOX_X,35,15,FAST);

	for (i=0; i<9; i++)
	{
		write_little(".",CBOX_X+i*4,39,15,FAST);
		delay(500);
	}
}
