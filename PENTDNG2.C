#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <butil.h>

static int just_entered_dungeon;

void _PASCAL explore_dungeon(int *out_alive)
{
	int moved;
	int number_steps=0;
	int dummy;
	int fin=FALSE;
	static int boundary[]={196,29,212,45,
						   196,85,212,100,
						   218,60,234,73,
						   172,60,189,73,
						   198,60,212,70,
						   -1,-1,-1,-1};

	*out_alive=TRUE;
	moved=TRUE;
	just_entered_dungeon=TRUE;

	draw_all_mapped_dungeon_level(the_party.dungeon_level);

	dungeon_print_level(the_party.dungeon_level);

	if (check_party_globals_in_effect(IN_EFFECT_LIGHT)==ERR)
	{
		the_party.dungeon_current_feature=
			draw_dungeon_party(the_party.dungeon_level,
							   the_party.dungeon_x,
							   the_party.dungeon_y);

		SCROLL(2,0,"EVEN ELVEN EYES CANNOT PIERCE SUCH DUNGEON BLACKNESS..");
		scroll_wrap_write(14,"HOW ABOUT SOME LIGHT?");
		bad_sound();
	}

	while (!fin && !the_party.all_dead)
	{
		dungeon_view_from_party(the_party.dungeon_level,
								the_party.dungeon_x,
								the_party.dungeon_y);

		the_party.dungeon_current_feature=
			draw_dungeon_party(the_party.dungeon_level,
							   the_party.dungeon_x,
							   the_party.dungeon_y);

		if (moved)
			dungeon_deal_with_feature(the_party.dungeon_current_feature);

		just_entered_dungeon=FALSE;

		if (!the_party.all_dead)
		{
			if (IN_DUNGEON)
			{
				switch(mouse_in_range(boundary,"NSEW ","\xC8\xD0\xCD\xCB\xC4"))
				{
					case 0 : moved=dungeon_move(DIR_NORTH);
							 break;

					case 1 : moved=dungeon_move(DIR_SOUTH);
							 break;

					case 2 : moved=dungeon_move(DIR_EAST);
							 break;

					case 3 : moved=dungeon_move(DIR_WEST);
							 break;

					default: fast_mouse=OFF;
							 deal_with_dungeon_menu();
							 fast_mouse=ON;
							 moved=FALSE;
							 break;
				}

				if (moved)
				{
					number_steps++;

					if (number_steps%DNGN_STEPS_HALF_HOUR==0)
					{
						dummy=STEPS_PER_HALF_HOUR;	/* Process_steps uses a var. */
						process_steps(&dummy);		/* to keep track and update  */
					}								/* the number of steps taken */
													/* As this function uses its */
													/* var. a dummy var. is used */

					if (dungeon.map[the_party.dungeon_level][the_party.dungeon_x][the_party.dungeon_y].mapped)
					{
						if (percent()>66)
							incidentals();
					}
					else
						incidentals();

				}
			}
			else
				fin=TRUE;
		}
	}
}

void _PASCAL dungeon_redraw_feature(int level,int x,int y,int item)
{
	int door_up_down;

	if (item==DNG_DOOR         ||
		item==DNG_HEAVY_DOOR   ||
		item==DNG_LOCKED_DOOR)
		if (dungeon.map[level][x-1][y].feature==DNG_WALL &&
			dungeon.map[level][x+1][y].feature==DNG_WALL)
				door_up_down=FALSE;
		else
				door_up_down=TRUE;

	draw_one_dungeon_bit(x*DUNGEON_BIT_X,
						 y*DUNGEON_BIT_Y,
						 item,
						 door_up_down);
}

void _PASCAL dungeon_deal_with_feature(int feature)
{
	int take;

	switch(feature)
	{
		case DNG_STAIRS_UP      :  if (just_entered_dungeon)
									   return;

								   take=take_dungeon_level_up();

								   if (take)
								   {
										if (the_party.dungeon_level==0)
										{
											IN_DUNGEON=FALSE;
											stairs_up_sound();
										}
										else
										{
											stairs_up_sound();

											the_party.dungeon_level--;

											draw_all_mapped_dungeon_level(the_party.dungeon_level);

											the_party.dungeon_current_feature=
												draw_dungeon_party(the_party.dungeon_level,
																   the_party.dungeon_x,
																   the_party.dungeon_y);

											dungeon_print_level(the_party.dungeon_level);
										}
								   }

								   break;

		case DNG_STAIRS_DOWN    :  take=take_dungeon_level_down();

								   if (take)
								   {
										the_party.dungeon_level++;

										stairs_down_sound();

										check_fall_down_steps();

										draw_all_mapped_dungeon_level(the_party.dungeon_level);

										the_party.dungeon_current_feature=
											draw_dungeon_party(the_party.dungeon_level,
															   the_party.dungeon_x,
															   the_party.dungeon_y);



										dungeon_print_level(the_party.dungeon_level);
								   }

								   break;

		case DNG_VOICE          :  land_on_dungeon_voice();
								   break;

		case DNG_MONSTER		:  combat(SET_MONSTER);
								   break;

		case DNG_TRAP           :  land_on_trap(dungeon.map[the_party.dungeon_level]
														   [the_party.dungeon_x]
														   [the_party.dungeon_y].trap_monst);

								   dungeon.map[the_party.dungeon_level]
											  [the_party.dungeon_x]
											  [the_party.dungeon_y].trap_triggered=TRUE;

								   break;

		case DNG_EMPTY_CHEST    :
		case DNG_TRAPPED_CHEST  :
		case DNG_TR_LOCK_CHEST  :
		case DNG_LOCKED_CHEST   :
		case DNG_CHEST          :  land_on_dungeon_chest();
								   break;

		case DNG_WATER          :  all_party_damaged_swim();
								   break;

		case DNG_WHIRLPOOL		:  GX("Without warning, a whirlpool drags ye party down......",SOLEMN);

								   the_party.dungeon_level++;

								   draw_all_mapped_dungeon_level(the_party.dungeon_level);

								   the_party.dungeon_current_feature=
										draw_dungeon_party(the_party.dungeon_level,
														   the_party.dungeon_x,
														   the_party.dungeon_y);

								   dungeon_print_level(the_party.dungeon_level);

								   GX("Thy party art on ye next lower level of ye dungeon!",GOOD);

								   break;

		case DNG_SPECIAL        :  land_on_dungeon_special(PASSING);
								   break;

		case DNG_DOOR           :  open_dungeon_door();
								   break;


		case DNG_SECRET_DOOR    :  open_secret_dungeon_door();
								   break;

		case DNG_HEAVY_DOOR     :
		case DNG_LOCKED_DOOR    :
		case DNG_WALL           :
		default                 :  break;
	}
}

int _PASCAL dungeon_move(int direction)
{
	int moved=FALSE;
	int item;

	dungeon_redraw_feature(the_party.dungeon_level,
						   the_party.dungeon_x,
						   the_party.dungeon_y,
						   the_party.dungeon_current_feature);

	switch(direction)
	{
		case DIR_NORTH  : item= dungeon.map[the_party.dungeon_level]
										   [the_party.dungeon_x]
										   [the_party.dungeon_y-1].feature;

						  switch(item)
						  {
							case DNG_WALL        : bang_into_dungeon_wall();
												   moved=FALSE;
												   break;

							case DNG_HEAVY_DOOR  : bang_into_heavy_door();
												   moved=FALSE;
												   break;

							case DNG_LOCKED_DOOR : bang_into_locked_door();
												   moved=FALSE;
												   break;

							case DNG_PILLAR      : bang_into_pillar();
												   moved=FALSE;
												   break;

							default              : if (--the_party.dungeon_y<0)
												   {
														the_party.dungeon_y=0;
														moved=FALSE;
												   }
												   else
														moved=TRUE;

												   break;
						  }

						  break;

		case DIR_SOUTH  : item=dungeon.map[the_party.dungeon_level]
										  [the_party.dungeon_x]
										  [the_party.dungeon_y+1].feature;

						  switch(item)
						  {
							case DNG_WALL        : bang_into_dungeon_wall();
												   moved=FALSE;
												   break;

							case DNG_HEAVY_DOOR  : bang_into_heavy_door();
												   moved=FALSE;
												   break;

							case DNG_LOCKED_DOOR : bang_into_locked_door();
												   moved=FALSE;
												   break;

							case DNG_PILLAR      : bang_into_pillar();
												   moved=FALSE;
												   break;

							default              : if (++the_party.dungeon_y>=MAX_DUNGEON_Y)
												   {
													   the_party.dungeon_y=MAX_DUNGEON_Y;
													   moved=FALSE;
												   }
												   else
													  moved=TRUE;

												   break;
						  }

						  break;

		case DIR_EAST   : item=dungeon.map[the_party.dungeon_level]
										  [the_party.dungeon_x+1]
										  [the_party.dungeon_y].feature;

						  switch(item)
						  {
							case DNG_WALL        : bang_into_dungeon_wall();
												   moved=FALSE;
												   break;

							case DNG_HEAVY_DOOR  : bang_into_heavy_door();
												   moved=FALSE;
												   break;

							case DNG_LOCKED_DOOR : bang_into_locked_door();
												   moved=FALSE;
												   break;

							case DNG_PILLAR      : bang_into_pillar();
												   moved=FALSE;
												   break;

							default              : if (++the_party.dungeon_x>=MAX_DUNGEON_X)
												   {
													   the_party.dungeon_x=MAX_DUNGEON_X;
													   moved=FALSE;
												   }
												   else
													   moved=TRUE;

												   break;
						  }

						  break;

		case DIR_WEST   : item=dungeon.map[the_party.dungeon_level]
										  [the_party.dungeon_x-1]
										  [the_party.dungeon_y].feature;

						  switch(item)
						  {
							case DNG_WALL        : bang_into_dungeon_wall();
												   moved=FALSE;
												   break;

							case DNG_HEAVY_DOOR  : bang_into_heavy_door();
												   moved=FALSE;
												   break;

							case DNG_LOCKED_DOOR : bang_into_locked_door();
												   moved=FALSE;
												   break;

							case DNG_PILLAR      : bang_into_pillar();
												   moved=FALSE;
												   break;

							 default             : if (--the_party.dungeon_x<0)
												   {
													  the_party.dungeon_x=0;
													  moved=FALSE;
												   }
												   else
													  moved=TRUE;

												   break;
						  }

						  break;
	}

	return(moved);
}

void _PASCAL dungeon_print_level(int level)
{
	int i,j;
	int xl=261;
	int yl=30;
	int x1=275;
	int x2=272;
	int x3=270;
	int x4=271;
	int yn=40;

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,260,yn,294,yn+10);

	for (i=0; i<33; i++)
		for (j=0; j<7; j++)
			if (dngn_level[j][i])
				FFPLOT(xl+i,yl+j,(char)dngn_level[j][i]);

	switch(level)
	{
		case 0 :    for (i=0; i<4; i++)
						for (j=0; j<6; j++)
							if (level_one[j][i])
								FFPLOT(x1+i,yn+j,(char)level_one[j][i]);
					break;

		case 1 :    for (i=0; i<9; i++)
						for (j=0; j<6; j++)
							if (level_two[j][i])
								FFPLOT(x2+i,yn+j,(char)level_two[j][i]);
					break;

		case 2 :    for (i=0; i<14; i++)
						for (j=0; j<6; j++)
							if (level_three[j][i])
								FFPLOT(x3+i,yn+j,(char)level_three[j][i]);
					break;

		case 3 :    for (i=0; i<12; i++)
						for (j=0; j<6; j++)
							if (level_four[j][i])
								FFPLOT(x4+i,yn+j,(char)level_four[j][i]);
					break;
	}
}

void _PASCAL dungeon_print_description(char *descr)
{
	int mod_len=(strlen(descr)*4)/2;

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,160,107,319,114);

	write_little(descr,238-mod_len,107,12,FAST);
}

void _PASCAL bang_into_heavy_door()
{
	bang_into_dungeon_bit("HEAVY DUNGEON DOOR");
}

void _PASCAL bang_into_locked_door()
{
	bang_into_dungeon_bit("LOCKED DUNGEON DOOR");
}

void _PASCAL bang_into_dungeon_wall()
{
	bang_into_dungeon_bit("WALL");
}

void _PASCAL bang_into_pillar()
{
	bang_into_dungeon_bit("PILLAR");
}

void _PASCAL bang_into_dungeon_bit(char *bit)
{
	char temp[40];

	sprintf(temp,"..OOOPPSS! A %s!",bit);

	SCROLL(1,0,temp);

	if (!NO_SOUND)
		utspkr(100);

	shake_screen();
	utspkr(0);
}

#ifndef DEV
#pragma optimize("za",on)
#endif

void _PASCAL draw_all_mapped_dungeon_level(int level)
{
	int i,j;
	int item;
	int door_up_down;

	generic_pic_draw(10,9,"DUNGBACK");

	for (i=0; i<MAX_DUNGEON_Y; i++)
	{
		for (j=0; j<MAX_DUNGEON_X; j++)
		{
			if (dungeon.map[level][j][i].feature!=DNG_WALL &&
				dungeon.map[level][j][i].mapped)
			{
				item=dungeon.map[level][j][i].feature;

				if (item==DNG_DOOR         ||
					item==DNG_SECRET_DOOR  ||
					item==DNG_HEAVY_DOOR   ||
					item==DNG_LOCKED_DOOR)
					if (dungeon.map[level][j-1][i].feature==DNG_WALL &&
						dungeon.map[level][j+1][i].feature==DNG_WALL)
							door_up_down=FALSE;
					else
							door_up_down=TRUE;

				draw_one_dungeon_bit(j*DUNGEON_BIT_X,
									 i*DUNGEON_BIT_Y,
									 item,
									 door_up_down);
			}
		}
	}

	dungeon_view_from_party(the_party.dungeon_level,
							the_party.dungeon_x,
							the_party.dungeon_y);
}

int _PASCAL draw_dungeon_party(int level,int x,int y)
{
	int i,j;

	dungeon_print_description(
				dungeon.descrip[dungeon.map[level][x][y].descrip_no]);

	for (i=0; i<DUNGEON_BIT_Y; i++)
		for (j=0; j<DUNGEON_BIT_X; j++)
			FFPLOT((x*DUNGEON_BIT_X)+j+DUNGEON_XOFF,
				   (y*DUNGEON_BIT_Y)+i+DUNGEON_YOFF,
				   (char)dngn_party[i][j]);

	return(dungeon.map[level][x][y].feature);
}

void _PASCAL draw_one_dungeon_bit(int x,int y,int feature,int door_up_down)
{
	int i,j;

	switch(feature)
	{
		case    DNG_STAIRS_UP      :    for (i=0; i<DUNGEON_BIT_Y; i++)
											for (j=0; j<DUNGEON_BIT_X; j++)
												FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_st_up[i][j]);

										break;

		case    DNG_STAIRS_DOWN    :    for (i=0; i<DUNGEON_BIT_Y; i++)
											for (j=0; j<DUNGEON_BIT_X; j++)
												FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_st_dn[i][j]);

										break;

		case    DNG_MONSTER        :
		case    DNG_VOICE          :
		case    DNG_TRAP           :
		case    DNG_CORRIDOR       :    for (i=0; i<DUNGEON_BIT_Y; i++)
											for (j=0; j<DUNGEON_BIT_X; j++)
												FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_corridor[i][j]);

										break;

		case    DNG_EMPTY_CHEST    :
		case    DNG_TRAPPED_CHEST  :
		case    DNG_LOCKED_CHEST   :
		case    DNG_TR_LOCK_CHEST  :
		case    DNG_CHEST          :    for (i=0; i<DUNGEON_BIT_Y; i++)
											for (j=0; j<DUNGEON_BIT_X; j++)
												FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_chest[i][j]);

										break;

		case    DNG_LOCKED_DOOR    :
		case    DNG_DOOR           :
		case    DNG_HEAVY_DOOR     :    if (door_up_down)
										{
											for (i=0; i<DUNGEON_BIT_Y; i++)
												for (j=0; j<DUNGEON_BIT_X; j++)
													FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_door_ud[i][j]);
										}
										else
										{
											for (i=0; i<DUNGEON_BIT_Y; i++)
												for (j=0; j<DUNGEON_BIT_X; j++)
													FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_door_lr[i][j]);
										}

										break;

		case    DNG_SPECIAL        :    for (i=0; i<DUNGEON_BIT_Y; i++)
											for (j=0; j<DUNGEON_BIT_X; j++)
												FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_special[i][j]);

										break;

		case    DNG_PILLAR         :    for (i=0; i<DUNGEON_BIT_Y; i++)
											for (j=0; j<DUNGEON_BIT_X; j++)
												FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_pillar[i][j]);

										break;

		case    DNG_WHIRLPOOL      :
		case    DNG_WATER          :    for (i=0; i<DUNGEON_BIT_Y; i++)
											for (j=0; j<DUNGEON_BIT_X; j++)
												FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_water[i][j]);

										break;

		default                    :    for (i=0; i<DUNGEON_BIT_Y; i++)
											for (j=0; j<DUNGEON_BIT_X; j++)
												FFPLOT(x+j+DUNGEON_XOFF, y+i+DUNGEON_YOFF,(char)dngn_wall[i][j]);

										break;
	}
}

#ifndef DEV
#pragma optimize("",on)
#endif

void _PASCAL land_on_dungeon_chest()
{
	int loc=the_party.dungeon_level+
			the_party.dungeon_x+
			the_party.dungeon_y;
	char temp[40];
	static char *desc[]={"a large, oaken",
						 "an old and battered",
						 "a blood stained"};

	sprintf(temp,"%s chest..",desc[loc%3]);

	SCROLL(1,1,temp);
}

void _PASCAL open_dungeon_door()
{
	static char *open[]={"kicks open",
						 "slowly opens",
						 "pushes open",
						 "carefully opens",
						 "opens"};
	char temp[80];

	int i;

	if (player_is_alive(&TPP[0]))
		i=0;
	else
	if (player_is_alive(&TPP[1]))
		i=1;
	else
		i=get_random_live_person();

	sprintf(temp,"%s %s ye dungeon door.",
			TPP[i].name,
			open[rand()%5]);

	scroll_scroll();
	SCROLL(1,1,temp);
}

void _PASCAL open_secret_dungeon_door()
{
	SCROLL(1,14,"Thy party walks through a secret door!");
}
