#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

/* Wizard Spells non-battle magic */

int _PASCAL cast_FIND_HIDDEN_DOOR(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[80];
	int hidden_door_count=0;

	if (!IN_DUNGEON)
	{
		cast_in_dungeon_only(spell_name->descrip);
		return(FALSE);
	}

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			sprintf(temp,"After mumbling to %sself, a mystic voice whispers to %s..",
						adv->him_her,
						adv->name);

			print_spell_description(temp);

			hidden_door_count=number_of_hidden_doors();

			if (hidden_door_count)
			{
				res=GOOD;

				if (hidden_door_count==1)
					strcpy(temp,"\"There is a hidden door within thy vicinity!\"");
				else
					sprintf(temp,"\"There art %d hidden doors within thy vicinity!\"",
								hidden_door_count);
			}
			else
			{
				strcpy(temp,"\"There be no hidden doors nearby...\"");
				res=BAD;
			}

			SCROLL(1,res==GOOD?14:0,temp);

			if (res==BAD)
				bad_sound();
			else
				good_sound();
		}
	}

	return(res);
}

/************************************************************************/

int _PASCAL cast_DISPEL_TRAP(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	int feature;
	char temp[90];

	if (!IN_DUNGEON)
	{
		cast_in_dungeon_only(spell_name->descrip);
		return(FALSE);
	}

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,2))
		{
			feature=dungeon.map[the_party.dungeon_level]
							   [the_party.dungeon_x]
							   [the_party.dungeon_y].feature;

			sprintf(temp,"%s waves %s arms about, invoking a thin mist....",
						adv->name,
						adv->his_her);

			print_spell_description(temp);
			pause(2);

			if (feature==DNG_TRAP           ||
				feature==DNG_TRAPPED_CHEST  ||
				feature==DNG_TR_LOCK_CHEST)
			{
				if (feature==DNG_TRAP)
				{
					dungeon.map[the_party.dungeon_level]
							   [the_party.dungeon_x]
							   [the_party.dungeon_y].trap_triggered=TRUE;
				}
				else
				if (feature==DNG_TRAPPED_CHEST)
				{
					dungeon.map[the_party.dungeon_level]
							   [the_party.dungeon_x]
							   [the_party.dungeon_y].feature=DNG_CHEST;
				}
				else
				{
					dungeon.map[the_party.dungeon_level]
							   [the_party.dungeon_x]
							   [the_party.dungeon_y].feature=DNG_LOCKED_CHEST;
				}

				res=TRUE;

				print_spell_description("Ye mist turns crystal blue before vanishing..");
			}
			else
			{
				SCROLL(1,0,"But naught seems to happen!");
				bad_sound();
			}
		}
	}

	return(res);
}

int _PASCAL cast_SINK(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[100];
	int x,y;

	if (!IN_DUNGEON)
	{
		cast_in_dungeon_only(spell_name->descrip);
		return(FALSE);
	}

	if (!cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
		return(FALSE);

	if (the_party.dungeon_level==dungeon.number_of_levels-1)
	{
		GX("Ye can sink no further in ye dungeon!",BAD);
		return(FALSE);
	}

	if (enough_spell_points_to_cast(adv,2))
	{
		sprintf(temp,"%s lowers %s head and looks at ye dungeon floor.",
					adv->name,
					adv->his_her);

		print_spell_description(temp);

		pause(2);

		SCROLL(1,14,"Slowly, thy party sinks into ye dungeon floor!");

		sink_sound();

		pause(1);

		scroll_scroll();

		if (!cast_SINK_lower_xy(&x,&y))
		{
			sprintf(temp,"%s senses ye spell art unsafe and stops casting!",
							adv->name);

			SCROLL(1,0,temp);
			solemn_sound();
			res=FALSE;
		}
		else
		{
			scroll_wrap_write(14,"Thy party emerges on ye next level down!");
			good_sound();
			res=TRUE;

			the_party.dungeon_level++;
			the_party.dungeon_x=x;
			the_party.dungeon_y=y;

			draw_all_mapped_dungeon_level(the_party.dungeon_level);

			dungeon_print_level(the_party.dungeon_level);

			the_party.dungeon_current_feature=
				draw_dungeon_party(the_party.dungeon_level,
								   the_party.dungeon_x,
								   the_party.dungeon_y);

		}
	}

	return(res);
}

int _PASCAL _NEAR cast_SINK_lower_xy(int *x,int *y)
{
	int nl=the_party.dungeon_level+1;
	int nx=the_party.dungeon_x;
	int ny=the_party.dungeon_y;
	int i;
	int fin=FALSE;

	if (dungeon.map[nl][nx][ny].feature==DNG_CORRIDOR)
	{
		*x=nx;
		*y=ny;

		fin=TRUE;
	}

	if (!fin)
	{
		for (i=1; i<4; i++)         /* Check -Y */
		{
			if (ny-i>1 && dungeon.map[nl][nx][ny-i].feature==DNG_CORRIDOR)
			{
				*x=nx;
				*y=ny-i;

				fin=TRUE;
			}
		}
	}

	if (!fin)
	{
		for (i=1; i<4; i++)     /* Check +Y */
		{
			if (ny+i<MAX_DUNGEON_Y && dungeon.map[nl][nx][ny+i].feature==DNG_CORRIDOR)
			{
				*x=nx;
				*y=ny+i;

				fin=TRUE;
			}
		}
	}

	if (!fin)
	{
		for (i=1; i<4; i++)     /* Check -X */
		{
			if (nx-i>1 && dungeon.map[nl][nx-i][ny].feature==DNG_CORRIDOR)
			{
				*x=nx-i;
				*y=ny;

				fin=TRUE;
			}
		}
	}

	if (!fin)
	{
		for (i=1; i<4; i++)     /* Check +X */
		{
			if (nx+i<MAX_DUNGEON_X && dungeon.map[nl][nx+i][ny].feature==DNG_CORRIDOR)
			{
				*x=nx+i;
				*y=ny;

				fin=TRUE;
			}
		}
	}

	return(fin);
}

/************************************************************************/

int _PASCAL cast_TELEPORT(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	static char temp[200];
	int x,y;

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,3))
		{
			res=TRUE;

			if (IN_DUNGEON)
			{
				sprintf(temp,"%s holds %s hands aloft and speaks some arcane words. "
							 "Immediately, thy party begins to dissolve......",
						adv->name,
						adv->his_her);

				SCROLL(1,14,temp);

				teleport_up_sound();

				init_dungeon_entry();

				the_party.dungeon_y++;

				draw_all_mapped_dungeon_level(the_party.dungeon_level);

				the_party.dungeon_current_feature=
					draw_dungeon_party(the_party.dungeon_level,
									   the_party.dungeon_x,
									   the_party.dungeon_y);

				teleport_down_sound();

				SCROLL(1,14,"Thy party reforms at ye dungeon entrance..");
			}
			else
			{
				cast_TELEPORT_get_xy(&x,&y);

				if (x==ERR && y==ERR)
				{
					sprintf(temp,"%s chooses to abort ye teleport spell!",
						adv->name);

					SCROLL(1,0,temp);
					bad_sound();

					add_lost_spell_pts(adv,3);

					return(TRUE);
				}

				sprintf(temp,"%s holds %s hands aloft and speaks some arcane words. "
							 "Immediately, thy party begins to dissolve......",
						adv->name,
						adv->his_her);

				SCROLL(1,14,temp);

				teleport_up_sound();

				pent_data.x=x+((rand()%4)-(rand()%4));
				pent_data.y=y+((rand()%4)-(rand()%4));

				if (pent_data.x<=0)
					pent_data.x=0;

				if (pent_data.y<=0)
					pent_data.y=0;

				if (pent_data.x>=(MAP_SIZE-2))
					pent_data.x=MAP_SIZE-2;

				if (pent_data.y>=(MAP_SIZE-2))
					pent_data.y=MAP_SIZE-2;

				if (is_night_time())
					draw_night_map();
				else
					draw_first_map();

				draw_map(JUST_TELEPORTED);	  /* 99= No Direction */

				teleport_down_sound();

				SCROLL(1,14,"Thy party slowly reforms at a new location in ye realms..");
			}
		}
	}

	return(res);
}

void _PASCAL cast_TELEPORT_get_xy(int *x,int *y)
{
	GWINDOW win;
	char *temp;
	char str_ns[20], str_we[20];
	int ns=86;
	int we=89;
	int fin=FALSE;
	char *letters1="NSWE Q";
	char *letters2="\xC8\xD0\xCB\xCD \x51";
	static int boundary[]={128,89 ,138,99,
						   116,89 ,127,99,
						   178,90 ,188,99,
						   180,90 ,199,99,
						   110,108,145,120,
						   170,108,205,120,
							-1,-1,-1,-1};

	win.x1=7;
	win.y1=6;
	win.x2=33;
	win.y2=17;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	temp="Teleport to where?";
	_settextcolor(14);
	_settextposition(win.y1+1,20-strlen_half(temp));
	_outtext(temp);

	print_up_down(116,90);
	print_left_right(178,90);

	click_box(110,108,B_OK);
	click_box(170,108,B_QUIT);

	_setcolor(6);
	_rectangle(_GBORDER,95, 66,219,84);
	_rectangle(_GBORDER,96, 67,218,83);
	_rectangle(_GBORDER,159,66,160,84);

	fast_mouse=ON;

	while (!fin)
	{
		if (we<=89)
			sprintf(str_we,"%3døW",89-we);
		else
			sprintf(str_we,"%3døE",we-89);

		if (ns<=86)
			sprintf(str_ns,"%3døN",86-ns);
		else
			sprintf(str_ns,"%3døS",ns-86);

		_settextcolor(14);

		_settextposition(win.y1+4,14);
		_outtext(str_ns);

		_settextposition(win.y1+4,22);
		_outtext(str_we);

		switch(mouse_in_range(boundary,letters1,letters2))
		{
			case 0 : ns--;     break;
			case 1 : ns++;     break;
			case 2 : we--;     break;
			case 3 : we++;     break;
			case 4 : fin=TRUE; break;
			default: *x=*y=ERR;
					 fin=TRUE;
					 break;
		}

		if (ns<=5)
			ns=5;

		if (ns>=195)
			ns=195;

		if (we<=5)
			we=5;

		if (we>=195)
			we=195;

		if (mouse_installed)
			delay(10);
	}

	fast_mouse=OFF;

	kill_gwindow(&win);

	if (*x!=ERR)
	{
		*x=we;
		*y=ns;
	}
}

int _PASCAL cast_INVOKE_FAMILIAR(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char type[20];
	char temp[180];
	char *benefits;
	int i;
	int pts=(adv->nclass==DRUID?2:3);

	if (IN_DUNGEON || IN_RUIN)
	{
		GX("Invoke Familiar can only be cast outdoors!",BAD);
		return(FALSE);
	}

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,pts))
		{
			if (adv->familiar!=NO_FAMILIAR)
			{
				strcpy(type,familiar_type(adv));

				sprintf(temp,"%s hath a familiar - %s %s!",
					adv->name,
					*type=='O'?"an":"a",
					type);

				GX(temp,BAD);
			}
			else
			{
				if (pent_data.moon_phase==NEW_MOON &&
					pent_data.time_hour==0         &&
					pent_data.time_minute==0)
				{
					res=TRUE;

					i=rand()%10;
					i++;

					adv->familiar=i;

					strcpy(type,familiar_type(adv));

					sprintf(temp,"An image of %s %s forms at ye midst "
								 "of a sparkling ring of flame created by %s.",
							*type=='O'?"an":"a",
							type,
							adv->name);

					print_spell_description(temp);

					pause(3);

					switch(adv->familiar)
					{
						case FAMILIAR_HAWK  :   benefits="great speed";
												adv->speed+=4;
												break;

						case FAMILIAR_CAT   :   benefits="improved dexterity";
												adv->agility++;
												break;

						case FAMILIAR_RAT   :   benefits="better disease immunity";
												adv->secondary_attrib[IMMUNITY_DISEASE]+=15;
												break;

						case FAMILIAR_TOAD  :   benefits="superb survival skills";
												adv->secondary_attrib[SURVIVAL]+=15;
												break;

						case FAMILIAR_FOX	:	benefits="greater cunning";
												adv->intelligence++;
												break;

						case FAMILIAR_OTTER :   benefits="magnificent swimming ability";
												adv->secondary_attrib[SWIM]+=20;
												break;

						case FAMILIAR_OWL   :   benefits="greater wisdom";
												adv->piety++;
												break;

						case FAMILIAR_RABBIT:   benefits="superior herb knowledge";
												adv->secondary_attrib[HERB_LORE]+=20;
												break;

						case FAMILIAR_BAT   :   benefits="acute hearing";
												adv->secondary_attrib[LISTEN]+=20;
												break;

						case FAMILIAR_VIPER :   benefits="better poison immunity";
												adv->secondary_attrib[IMMUNITY_POISON]+=20;
												break;
					}

					sprintf(temp,"%s now hath %s %s as a familiar, conveying %s to %s.",
								adv->name,
								*type=='O'?"an":"a",
								type,
								benefits,
								adv->him_her);

					SCROLL(1,14,temp);
					good_sound();
				}
				else
				{
					GX("Invoke Familiar may only be cast at Midnight during a New Moon!",SOLEMN);
				}
			}
		}
	}

	return(res);
}
