#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL enter_town(int x,int y)
{
	char name[40];
	int option=ERR;
	int fin=FALSE;

	strcpy(name,get_town_details(x,y));

	memcpy((void *)&town,
		   (void *)&small_towns[get_town_num(x,y)],
		   sizeof(SMALL_TOWN));

	game_loaded=FALSE;

	the_party.in_town=TRUE;

	while (!fin)
	{
		option=enter_town_draw_menu(name);

		switch(option)
		{
			case 1 : town_cathedral();
					 break;

			case 2 : town_inn();
					 break;

			case 3 : town_food_market();
					 break;

			case 4 : adv_inspect();
					 break;

			case 5 : if (town_go_adventuring())
						 fin=TRUE;

					 break;

			case 6 : town_saga_options();
					 break;

			default: town_quit_program();
					 break;
		}
	}

	the_party.in_town=FALSE;
}

int _PASCAL enter_town_draw_menu(char *name)
{
	static  char *opt[]={"Chapel",
						 "Inn",
						 "Food Market",
						 "View Adventurer",
						 "Go Adventuring",
						 "Saga Options",
						 "Quit Pentagram"};

	char *t2="CIFVGSQ";
	static int boundary[]={96,40,202,46,
						   96,48,202,54,
						   96,56,202,62,
						   96,64,202,70,
						   96,72,202,78,
						   96,80,202,86,
						   96,88,202,94,
						   -1,-1,-1,-1};

	int fin=FALSE;
	GWINDOW win;

	cls();
	cls_scroll();

	print_large_title(name);

	win.x1=12;
	win.x2=win.x1+17;
	win.y1=5;
	win.y2=14;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(opt,
					   SIZE(opt),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,13);

	distribute_gc();

	fin=mouse_in_range(boundary,t2,"");

	kill_gwindow(&win);

	return(fin+1);
}

void _PASCAL town_inn()
{
	inn(town.inn_name);
}

void _PASCAL town_saga_options()
{
	front_options();
}

int _PASCAL  town_go_adventuring()
{
	int result;

	result=gget_yn("Go Adventuring! Art thou sure?");

	return(result);
}

void _PASCAL town_quit_program()
{
	shut_program_down(TRUE);
}
