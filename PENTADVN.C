#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bscreens.h>
#include "mmalloc.h"

static int menu_x      = 167;
static int menu_y      = 0;

void _PASCAL adventure()
{
	int traveling=TRUE;
	int steps;
	int moved;
	GWINDOW win;
	int half_inc=0;
	char *title="..thy saga continues!";
	static int boundary[]={196,29,212,45,
						   196,85,212,100,
						   218,60,234,73,
						   172,60,189,73,
						   198,60,212,70,
						   -1,-1,-1,-1};

#ifdef BOMB
	BOMB_check();
#endif

	cls_scroll();

	if (!game_loaded)
	{
		if (!gget_yn("Go Adventuring! Art thou sure?"))
			return;

		if (!init_party_for_adventure())
			return;

		quote_on_leaving_town();
	}
	else
	{
		if (!init_party_for_adventure())
			return;

		win.x1=19-strlen_half(title);
		win.y1=9;
		win.x2=23+strlen_half(title);
		win.y2=win.y1+3;
		win.back=1;
		win.border=14;

		make_gwindow(&win);

		print_text(title,win.x1*8+5,win.y1*8+1,NORMAL,15);

		good_sound();

		pause(2);

		kill_gwindow(&win);

		generate_initial_party_order();

		quote_on_leaving_town();
	}

	if (pent_data.current_feature==CITY)
	{
		pent_data.date_visit_wolfburg=pent_data.date;
		pent_data.year_visit_wolfburg=pent_data.year;

		if (pent_data.finished)
		{
			SCROLL(1,14,"Ye land appears so peaceful and serene!");
			good_sound();
		}
	}

	game_loaded=FALSE;
	night_flagged=FALSE;

	draw_compass_image(172,30);
	draw_first_day_night();

	place_map();

	if (is_night_time())
		draw_night_map();
	else
		draw_first_map();

	steps=0;

	moved=FALSE;

	while (traveling && !the_party.all_dead)
	{
		fast_mouse=ON;

		if (moved)
		{
			switch(pent_data.current_feature)
			{
				case DUNGEON        :
				case RUIN           :
				case TOWN           :
				case CITY           :
				case CELTIC_CROSS   :
				case GRASS          :
				case SIGNPOST       :
				case PATH           :
				case BRIDGE         : half_inc=2; break;

				case HILLS          :
				case MARSH          : half_inc=4; break;

				case MOUNTAINS      :
				case FOREST         : half_inc=6; break;

				case SEA            :
				case WATER			: if (check_party_globals_in_effect(IN_EFFECT_WALK_ON_WATER)==ERR)
										half_inc=6;
									  else
										half_inc=2;

									  break;

				case HIGH_MOUNTAINS : half_inc+=10; break;
			}
		}

		steps+=(is_night_time()?half_inc:half_inc/2);

		moved=FALSE;

		switch(mouse_in_range(boundary,"NSEW ","\xC8\xD0\xCD\xCB\xC4"))
		{
			case 0 : moved=go_north();
					 break;

			case 1 : moved=go_south();
					 break;

			case 2 : moved=go_east();
					 break;

			case 3 : moved=go_west();
					 break;

			default: fast_mouse=OFF;
					 deal_with_adventure_menu();
					 moved=FALSE;
					 break;
		}

		if (moved)
		{
			incidentals();

			switch(pent_data.current_feature)
			{
				case    DUNGEON         : bad_sound2();

										  if (take_dungeon_level_down())
											actually_enter_dungeon();

										  break;

				case	RUIN			: bad_sound2();
										  enter_a_ruin();

										  break;

				case    CELTIC_CROSS    : celtic_cross();
										  break;

				case    TOWN            : if (show_small_town_data(pent_data.x, pent_data.y)==YES)
										  {
											   kill_map();
											   nullify_all_in_effect_party();

											   enter_town(pent_data.x, pent_data.y);

											   quote_on_leaving_town();

											   night_flagged=FALSE;

											   draw_compass_image(172,30);
											   draw_first_day_night();

											   place_map();

											   if (is_night_time())
												   draw_night_map();
											   else
												   draw_first_map();

											   steps=0;

											   moved=FALSE;
										  }

										  break;

				case    CITY            : if (show_small_town_data(pent_data.x, pent_data.y)==YES)
										  {
											   if (!is_night_time())
											   {
												   the_party.in_town=FALSE;
												   the_party.adventuring=FALSE;
												   traveling=FALSE;
											   }
											   else
												   GX("Thy party cannot enter ye bolted "
													  "Wolfburg gates until sunrise!",BAD);
										  }

										  break;

				default                 : break;
			}

			process_steps(&steps);
		}
	}

	if (the_party.all_dead)             /* Back in Wolfburg, Alive or Dead! */
	{
		nullify_all_in_effect_party();
		pent_data.x=89;
		pent_data.y=86;
		pent_data.current_feature=CITY;
		traveling=FALSE;
		the_party.adventuring=FALSE;

		print_all_dead_message();
		perform_death_of_party();
	}
	else
	{
		nullify_all_in_effect_party();
		entering_city_get_taxed();
		distribute_xp_gc(the_party.xp_earned);

		check_if_game_finished();

		save_game(FALSE);

		evaluate_interest();
	}

	kill_map();
}

void _PASCAL draw_compass_image(int x,int y)
{
	generic_pic_draw(x,y,"COMPASS");
}

void _PASCAL clear_adv_menu_heap()
{
	Mfree((void *)adv_menu);
	Mfree((void *)all_menu_bkgrnd);
}

void _PASCAL deal_with_adventure_menu()
{
	int fin=FALSE;
	int resting=FALSE;
	static int boundary[]={180,14,202,33,
						   219,11,237,33,
						   251,12,274,33,
						   287,13,306,33,
						   182,40,201,61,
						   219,40,233,61,
						   248,40,276,61,
						   284,40,307,61,
						   182,68,199,89,
						   213,68,239,89,
						   251,68,271,89,
						   281,68,309,89,
						   226, 95,261,107,
						   -1,-1,-1,-1};

	_getimage(menu_x,menu_y,menu_x+152,menu_y+121,(char _FAR *)all_menu_bkgrnd);

	_putimage(menu_x,menu_y,adv_menu,_GPSET);

	while (!fin)
	{
		switch(mouse_in_range(boundary,"SUPGECHORATIQ","SUPGECHORATIF"))
		{
			case 0 : adv_search();
					 break;

			case 1 : adv_useitem();
					 break;

			case 2 : adv_drink_potion();
					 break;

			case 3 : adv_swap_item();
					 break;

			case 4 : adv_equip();
					 break;

			case 5 : _putimage(menu_x,menu_y,all_menu_bkgrnd,_GPSET);
					 fin=TRUE;
					 adv_cast_spell();
					 break;

			case 6 : adv_hunt();
					 break;

			case 7 : adv_forage();
					 break;

			case 8 : _putimage(menu_x,menu_y,all_menu_bkgrnd,_GPSET);
					 fin=TRUE;
					 resting=TRUE;
					 adv_rest();
					 break;

			case 9 : adv_rearrange();
					 break;

			case 10: adv_eat();
					 break;

			case 11: adv_inspect();
					 break;

			default: fin=TRUE;
					 break;
		}
	}

	if (!resting)
		_putimage(menu_x,menu_y,all_menu_bkgrnd,_GPSET);
}

void _PASCAL adv_search()
{
	char temp[80];
	char temp1[80];
	int i;
	int town_num=ERR;
	int special=FALSE;

	if (!IN_DUNGEON)
	{
		switch(pent_data.current_feature)
		{
			case SIGNPOST   :
				divulge_signpost_info(pent_data.x, pent_data.y);
				special=TRUE;
				break;

			case DUNGEON    :
				divulge_dungeon_info(pent_data.x, pent_data.y);
				special=TRUE;
				break;

			case RUIN       :
				divulge_ruin_info(pent_data.x, pent_data.y);
				special=TRUE;
				break;

			case BRIDGE_UD  :
			case BRIDGE_LR  :
			case BRIDGE     :
				divulge_bridge_info(pent_data.x, pent_data.y);
				special=TRUE;
				break;

			default         :
				switch(pent_data.current_feature)
				{
					case PATH           :   strcpy(temp,"ON A PATHWAY");           break;
					case SEA            :   strcpy(temp,"IN YE SEA!");             break;
					case GRASS          :   strcpy(temp,"IN GRASSLAND");           break;
					case HILLS          :   strcpy(temp,"ON HILLY LAND");          break;
					case MOUNTAINS      :   strcpy(temp,"IN MOUNTAINOUS TERRAIN"); break;
					case HIGH_MOUNTAINS :   strcpy(temp,"IN HIGH MOUNTAINS");      break;
					case WATER          :   strcpy(temp,"IN SHALLOW WATER!");      break;
					case FOREST         :   strcpy(temp,"IN A FOREST");            break;
					case MARSH          :   strcpy(temp,"STANDING IN MARSHLAND");  break;
					case CELTIC_CROSS   :   strcpy(temp,"BY A CELTIC CROSS");      break;
					case CITY           :
					case TOWN           :   for (i=0; i<MAX_SMALLTOWNS; i++)
												if (pent_data.x==small_towns[i].x_position &&
													pent_data.y==small_towns[i].y_position)
													town_num=i;

											if (town_num!=ERR)
											{
												switch(small_towns[town_num].town_type)
												{
													case TWN_CITY    :  strcpy(temp1,"city");
																		break;

													case TWN_HAMLET  :  strcpy(temp1,"hamlet");
																		break;

													case TWN_VILLAGE :  strcpy(temp1,"village");
																		break;

													case TWN_TOWN    :  strcpy(temp1,"town");
																		break;
												}

												sprintf(temp,"BY YE %s OF %s",
															 temp1,
															 small_towns[town_num].name);
											}

											break;

					default             :   break;
				}

				sprintf(temp1,"THOU ART %s.",temp);

				SCROLL(1,1,temp1);

				general_low_sound();

				break;
		}

		if (!special)
			adv_search_province(pent_data.x,
								pent_data.y,
								pent_data.current_feature);
	}
}

void _PASCAL adv_search_province(int x,int y,int f)
{
	char temp[120];
	int i;
	int hp=0;
	int current_hp=0;

	if (f==SEA || f==WATER)
		return;

	for (i=0; i<=P_NUM; i++)
	{
		current_hp+=TPP[i].current_hp;
		hp+=TPP[i].hp;
	}

	sprintf(temp,"THY %s PARTY, LED BY %s ART JOURNEYING %s.",
				 (current_hp<=hp/2)?"WEARY":"STOUT",
				 TPP[0].name,
				 get_province(x,y));

	SCROLL(1,14,temp);
}

void _PASCAL adv_useitem()
{
	int use=0;

	use=adv_select_adventurer("Who's Item","is to be used?",TRUE);

	if (use!=ERR)
		(void)actually_use_item(&TPP[use]);
}

void _PASCAL adv_drink_potion()
{
	drink_or_taste_potion();
}

void _PASCAL adv_swap_item()
{
	int from, to;
	int fin=FALSE;
	GWINDOW win;
	char *t2="GDQ";
	int res;
	static int boundary[]={120,40,250,53,
						   120,60,250,82,
						   170,91,205,103,
						   -1,-1,-1,-1};

	win.x1=15;
	win.y1=5;
	win.x2=33;
	win.y2=15;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	generic_pic_draw(win.x1*8,win.y1*8+2,"DISTR");

	click_box(170,91,B_QUIT);

	res=mouse_in_range(boundary,t2,"");

	kill_gwindow(&win);

	switch(res)
	{
		case 0 : while (!fin)
				 {
					 fin=swap_item_get_people(&from,&to);

					if (!fin)
						 select_swap_type(from,to);
				 }

				 break;

		case 1 : distribute_pool();
				 break;

		default: break;
	}
}

void _PASCAL adv_equip()
{
	int num=0;

	while (num!=ERR)
	{
		num=adv_select_adventurer("Equip Whom?","",TRUE);

		if (num!=ERR)
			ready_an_adventurer(&TPP[num]);
	}
}

void _PASCAL adv_cast_spell()
{
	int num=0;

	num=adv_select_adventurer("Who art","Casting?",TRUE);

	if (num!=ERR)
		actually_cast_a_spell(&TPP[num]);
}

void _PASCAL adv_hunt()
{
	int num;

	num=adv_select_adventurer("Who art","Hunting?",TRUE);

	if (num!=ERR)
		actually_hunt(&TPP[num]);
}

void _PASCAL adv_forage()
{
	int num;

	num=adv_select_adventurer("Who art","Foraging?",TRUE);

	if (num!=ERR)
		actually_forage(&TPP[num]);
}

void _PASCAL adv_rest()
{
	if (pent_data.current_feature==SEA || pent_data.current_feature==WATER)
	{
		GX("Thy party cannot rest in water!",BAD);
		return;
	}

	attempt_to_rest();
}

void _PASCAL adv_rearrange()
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
	int from,to,j;
	char temp[80];
	int xpos, ypos;
	int fin=FALSE;
	PLAYER t;

	win.x1=16;
	win.y1=2;
	win.x2=32;
	win.y2=24;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(14);
	_settextposition(win.y1+1,18);
	_outtext("Adjust Party");

	adv_arrange_draw();
	click_box(170,162,B_FINISH);

	from=to=ERR;

	while (!fin)
	{
		select=mouse_in_range(boundary,"123456Q","123456F");

		if (select==6)
		{
			fin=TRUE;
		}
		else
		{
			if (select>P_NUM)
			{
				bad_sound2();
				continue;
			}

			if (from==ERR)
			{
				from=select;

				switch(from)
				{
					case 0 :    xpos=145; ypos=40;  break;
					case 1 :    xpos=205; ypos=40;  break;
					case 2 :    xpos=145; ypos=80;  break;
					case 3 :    xpos=205; ypos=80;  break;
					case 4 :    xpos=145; ypos=120; break;
					case 5 :    xpos=205; ypos=120; break;
				}

				sprintf(temp,"  %s",TPP[from].name);

				j=(xpos+8)-(strlen(temp)*4)/2;

				write_little(temp,
							 j,
							 ypos+22,
							 15,
							 FAST);
			}
			else
				to=select;

			if (from!=ERR && to!=ERR)
			{
				t=TPP[to];
				TPP[to]=TPP[from];
				TPP[from]=t;

				_setcolor(0);

				switch(from)
				{
					case 0 : xpos=145; ypos=40;  break;
					case 1 : xpos=205; ypos=40;  break;
					case 2 : xpos=145; ypos=80;  break;
					case 3 : xpos=205; ypos=80;  break;
					case 4 : xpos=145; ypos=120; break;
					case 5 : xpos=205; ypos=120; break;
				}

				_rectangle(_GFILLINTERIOR,xpos-20,ypos,xpos+33,ypos+35);

				switch(to)
				{
					case 0 : xpos=145; ypos=40;  break;
					case 1 : xpos=205; ypos=40;  break;
					case 2 : xpos=145; ypos=80;  break;
					case 3 : xpos=205; ypos=80;  break;
					case 4 : xpos=145; ypos=120; break;
					case 5 : xpos=205; ypos=120; break;
				}

				_rectangle(_GFILLINTERIOR,xpos-20,ypos,xpos+33,ypos+35);

				adv_arrange_draw();

				good_sound();

				from=to=ERR;
			}
		}
	}

	kill_gwindow(&win);
}

void _PASCAL adv_eat()
{
	int select=0;
	int opt;
	GWINDOW win;
	char *t2="HFQ";
	static int boundary[]={115,62,187,71,
						   115,83,187,90,
						   132,100,167,112,
						   -1,-1,-1,-1};

	select=adv_select_adventurer("Who art","Eating?",TRUE);

	if (select!=ERR)
	{
		if (bard_is_singing(&TPP[select],"eat"))
			return;

		win.x1=14;
		win.y1=6;
		win.x2=26;
		win.y2=win.y1+10;
		win.back=0;
		win.border=4;

		make_gwindow(&win);

		_settextcolor(12);
		_settextposition(win.y1+1,win.x1+1);
		_outtext("Eat what??");

		generic_pic_draw(win.x1*8+4,win.y1*8+15,"EATWHAT");

		opt=mouse_in_range(boundary,t2,"");

		kill_gwindow(&win);

		switch(opt)
		{
			case 0 : adv_actually_use_herbs(&TPP[select]);
					 break;

			case 1 : adv_actually_eat(&TPP[select]);
					 break;

			default: select=ERR;
					 break;
		}
	}
}

void _PASCAL adv_actually_eat(PLAYER *adv)
{
	char temp[80];
	int eat_num;
	char feeling[80];

	if (adv->hungry==NOT_HUNGRY)
	{
		sprintf(temp,"%s art not hungry!",adv->name);
		GX(temp,BAD);
	}
	else
	{
		switch(adv->hungry)
		{
			case SLIGHT_HUNGER      :   eat_num=1;
										sprintf(feeling,"%s art slightly hungry",adv->he_she);
										break;

			case BELLY_RUMBLE       :   eat_num=1;
										sprintf(feeling,"%s belly rumbles",adv->his_her);
										break;

			case HUNGRY             :   eat_num=2;
										sprintf(feeling,"%s art hungry",adv->he_she);
										break;

			case VERY_HUNGRY        :   eat_num=2;
										sprintf(feeling,"%s art very hungry",adv->he_she);
										break;

			case DANGEROUSLY_HUNGRY :   eat_num=3;
										sprintf(feeling,"%s art famished",adv->he_she);
										break;
		}

		if (adv->food==0)
		{
			sprintf(temp,"%s hath no food and %s.",adv->name,feeling);
			GX(temp,BAD);

			return;
		}

		if (adv->food>=eat_num)
		{
			adv->food-=eat_num;
			adv->hungry=NOT_HUNGRY;

			switch(rand()%4)
			{
				case 0 : strcpy(feeling,"feels quite full now!");   break;
				case 1 : strcpy(feeling,"art no longer hungry!");   break;
				case 2 : strcpy(feeling,"isn't hungry anymore!");   break;
				default: strcpy(feeling,"feels full now!");         break;
			}

			sprintf(temp,"%s eats & %s ",adv->name,feeling);

			if (adv->food==0)
				strcat(temp,"But hath no food left!");

			GX(temp,adv->food?GOOD:BAD);

			return;
		}
		else
		{
			adv->hungry-=eat_num;
			adv->food=0;

			switch(adv->hungry)
			{
				case SLIGHT_HUNGER      :   strcpy(feeling," art still slightly hungry.");
											break;

				case BELLY_RUMBLE       :   sprintf(feeling,"%s belly still rumbles.",adv->his_her);
											break;

				case HUNGRY             :   strcpy(feeling," art still hungry.");
											break;

				case VERY_HUNGRY        :   strcpy(feeling," art still very hungry.");
											break;

				case DANGEROUSLY_HUNGRY :   strcpy(feeling," art still famished");
											break;
			}

			sprintf(temp,"%s eats all %s food but %s",adv->name,
													  adv->his_her,
													  feeling);
			GX(temp,BAD);

			return;
		}
	}
}

void _PASCAL adv_inspect()
{
	int select=0;

	while (select!=ERR)
	{
		select=adv_select_adventurer("Inspect Whom?","",FALSE);

		if (select!=ERR)
			show_adventurer(&TPP[select]);
	}
}

void _PASCAL cannot_go_direction(char *dir)
{
	char temp[80];
	char *t="A strange force prevents you from travelling further";

	sprintf(temp,"%s %s!",t,dir);
	GX(temp,BAD);
}

int _PASCAL go_north()
{
	pent_data.y--;

	if (pent_data.y<=5)
	{
		cannot_go_direction("North");
		pent_data.y=5;
		return(FALSE);
	}

	draw_map(DIR_NORTH);

	return(TRUE);
}

int _PASCAL go_south()
{
	pent_data.y++;

	if (pent_data.y>=MAX_WORLD)
	{
		cannot_go_direction("South");
		pent_data.y=MAX_WORLD;
		return(FALSE);
	}

	draw_map(DIR_SOUTH);

	return(TRUE);
}

int _PASCAL go_east()
{
	pent_data.x++;

	if (pent_data.x>=MAX_WORLD)
	{
		cannot_go_direction("East");
		pent_data.x=MAX_WORLD;
		return(FALSE);
	}

	draw_map(DIR_EAST);

	return(TRUE);
}

int _PASCAL go_west()
{
	pent_data.x--;

	if (pent_data.x<=5)
	{
		cannot_go_direction("West");
		pent_data.x=5;
		return(FALSE);
	}

	draw_map(DIR_WEST);

	return(TRUE);
}
