#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL dng_chest()
{
	int l,x,y;
	int feature;
	int person;
	GWINDOW win;
	char *t2="OIPDCAL";
	int fin=FALSE;
	static char *t[]={"Open Chest",
					  "Inspect Chest",
					  "Pick Lock",
					  "Disarm Trap",
					  "Cast Dispel Trap",
					  "Cast Open Chest",
					  "Leave Alone!"};

	static int boundary[]={128,32,250,38,
						   128,40,250,46,
						   128,48,250,54,
						   128,56,250,62,
						   128,64,250,70,
						   128,72,250,78,
						   128,80,250,86,
							-1,-1,-1,-1};

	l=the_party.dungeon_level;
	x=the_party.dungeon_x;
	y=the_party.dungeon_y;

	feature=dungeon.map[l][x][y].feature;

	if (feature!=DNG_EMPTY_CHEST   &&
		feature!=DNG_TRAPPED_CHEST &&
		feature!=DNG_LOCKED_CHEST  &&
		feature!=DNG_TR_LOCK_CHEST &&
		feature!=DNG_CHEST)
	{
		GX("There be no chests by thy party!",BAD);
		return;
	}

	person=adv_select_adventurer("Who's dealing","with ye chest?",TRUE);

	if (person==ERR)
		return;

	win.x1=16;
	win.y1=4;
	win.x2=34;
	win.y2=13;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,
					   13);

	while (!fin)
	{
		feature=dungeon.map[l][x][y].feature;

		switch(mouse_in_range(boundary,t2,"OIPDCAQ"))
		{
			case 0 :  dng_open_chest(&TPP[person],l,x,y,feature);         break;
			case 1 :  dng_inspect_chest(&TPP[person],feature);            break;
			case 2 :  dng_handle_locked_chest(&TPP[person],l,x,y,feature);break;
			case 3 :  dng_disarm_chest(&TPP[person],l,x,y,feature);       break;
			case 4 :  dng_dispel_chest(&TPP[person]);                     break;
			case 5 :  dng_cast_open_chest(&TPP[person]);                  break;
			default:  fin=TRUE; 										  break;
		}
	}

	kill_gwindow(&win);
}

void _PASCAL dng_open_chest(PLAYER *adv,int l,int x,int y,int type)
{
	char temp[90];
	static char *how[]={"slowly",
						"cautiously",
						"warily"};

	if (type==DNG_LOCKED_CHEST || type==DNG_TR_LOCK_CHEST)
	{
		GX("Ye chest art locked!",BAD);
		return;
	}

	sprintf(temp,"%s raises ye chest lid %s...",
			adv->name,
			how[rand()%(SIZE(how))]);

	SCROLL(1,1,temp);

	pause(1);

	if (type==DNG_TRAPPED_CHEST)
		dng_trigger_chest_trap(adv,l,x,y);

	if (type==DNG_EMPTY_CHEST)
	{
		SCROLL(1,0,"Ye chest art empty!");

		bad_sound();

		return;
	}

	look_inside_chest();

	dungeon.map[l][x][y].feature=DNG_EMPTY_CHEST;
}

void _PASCAL look_inside_chest()
{
	long treasure;
	int ave_lv=average_level();

	draw_treasure_message();

	SCROLL(1,1,"Treasure found.....");

	treasure=non_magic_treasure();

	if (percent()<=ave_lv*8)
		magic_treasure();

	the_party.gc_earned+=treasure;
	add_xp_to_party((long)treasure/10L);
}

void _PASCAL dng_handle_locked_chest(PLAYER *adv,int l,int x,int y,int chest_type)
{
	char temp[80];
	int tumblers=dng_lock_difficulty(l,x,y);
	char tumb[10];

	if (chest_type!=DNG_LOCKED_CHEST && chest_type!=DNG_TR_LOCK_CHEST)
	{
		sprintf(temp,"%s noticies ye chest art unlocked!",adv->name);
		SCROLL(1,14,temp);

		good_sound();

		return;
	}

	if (!player_is_carrying(adv,THIEVES_TOOLS))
	{
		sprintf(temp,"%s needs Thieves Tools to unlock ye chest!",adv->name);

		GX(temp,BAD);
		return;
	}

	if (adv->nclass==THIEF)
	{
		switch(tumblers)
		{
			case 1 : strcpy(tumb,"one");    break;
			case 2 : strcpy(tumb,"two");    break;
			default: strcpy(tumb,"three");  break;
		}

		sprintf(temp,"%s notices ye lock hath %s tumbler%s...",
					adv->name,
					tumb,
					tumblers!=1?"s.":".");

		SCROLL(1,1,temp);

		pause(1);
	}

	sprintf(temp,"%s uses %s lockpicks on ye chest lock...",
				adv->name,
				adv->his_her);

	SCROLL(1,1,temp);

	pause(2);

	if (percent()>(effective_pick_lock(adv)-(tumblers*2)))              /* Fail lock */
	{
		SCROLL(1,0,"But Fails.....");
		bad_sound();

		pause(1);

		if (percent()>effective_snap_thieves_tools(adv)) /* Snap pick */
		{
			dng_actually_snap_thieves_tools(adv,TRUE);
			pause(1);
		}
	}
	else
	{
		SCROLL(1,14,"a sharp click indicates success!");
		good_sound();

		if (chest_type==DNG_LOCKED_CHEST)
			dungeon.map[l][x][y].feature=DNG_CHEST;
		else
		if (chest_type==DNG_TR_LOCK_CHEST)
			dungeon.map[l][x][y].feature=DNG_TRAPPED_CHEST;

		pause(1);

		add_to_professionalism(adv,1);
		add_xp_to_party(500L);
	}
}

void _PASCAL dng_inspect_chest(PLAYER *adv,int type)
{
	char temp[120];
	int i=rand()%4;
	int bad;
	static char *notice[]={"nothing.",
						   "nothing special.",
						   "nothing of interest.",
						   "naught."};

	sprintf(temp,"%s notices ",adv->name);

	if (percent()<=effective_find_trap(adv))
	{
		switch(type)
		{
			case DNG_EMPTY_CHEST    : strcat(temp,notice[i]);
									  bad=TRUE;
									  break;

			case DNG_CHEST          : strcat(temp,notice[i]);
									  bad=TRUE;
									  break;

			case DNG_TRAPPED_CHEST  : strcat(temp,"a possible trap.");
									  bad=FALSE;
									  break;

			case DNG_LOCKED_CHEST   : strcat(temp,"an unbroken lock.");
									  bad=FALSE;
									  break;

			case DNG_TR_LOCK_CHEST  : strcat(temp,
											 rand()%2?"a possible trap."
													 :"an unbroken lock.");
									  bad=FALSE;
									  break;
		}
	}
	else
	{
		bad=TRUE;
		strcat(temp,notice[i]);
	}

	SCROLL(1,14,temp);

	if (bad)
		bad_sound();
	else
		good_sound();
}

void _PASCAL dng_trigger_chest_trap(PLAYER *adv,int l,int x,int y)
{
	int chest_trap_type;
	int chance_dodge_trap;
	int prot_traps;
	int poison;
	int damage;
	char temp[80];
	int feature;
	static char *body[]={"Hand",
						 "Wrist",
						 "Neck",
						 "Face"};

	chest_trap_type=dng_chest_trap_type(l,x,y);

	chance_dodge_trap=effective_disarm_trap(adv);
	chance_dodge_trap/=3;
	chance_dodge_trap*=2;

	display_trap_window();

	prot_traps=check_party_globals_in_effect(IN_EFFECT_PROT_FROM_TRAPS);

	if (prot_traps!=ERR)
	{
		sprintf(temp,"Luckily, %s hath cast Protection from Traps!",
					TPP[prot_traps].name);

		GX(temp,GOOD);
	}
	else
	{
		if (percent()>=chance_dodge_trap)            /* Trap not dodged */
		{
			switch(chest_trap_type)
			{
				case CHEST_TRAP_POISON_DART :
					sprintf(temp,"A tiny, poisoned needle pierces %s%s %s.",
									adv->name,
									end_s(adv->name),
									body[rand()%4]);

					poison=TRUE;
					damage=get_dice_roll(4,1,1);

					break;

				case CHEST_TRAP_GAS         :
					sprintf(temp,"A small cloud of yellow gas envelops %s.",
									adv->name);

					poison=FALSE;
					damage=get_dice_roll(8,1,0);

					break;

				case CHEST_TRAP_ELECTRICITY :
					sprintf(temp,"A bolt of electricity jolts through %s%s body.",
									adv->name,
									end_s(adv->name));

					poison=FALSE;
					damage=get_dice_roll(4,2,0);

					if (is_wearing_metal(adv))
						damage*=2;

					break;

				case CHEST_TRAP_DART        :
					sprintf(temp,"An insignificant needle lodges in %s%s %s.",
									adv->name,
									end_s(adv->name),
									body[rand()%4]);

					poison=FALSE;
					damage=get_dice_roll(4,1,1);

					break;

			}

			SCROLL(1,0,temp);

			bad_sound();

			pause(3);

			damage=modified_damage(damage);

			sprintf(temp,"Inflicting %d HP of damage on %s!",
						damage,
						adv->him_her);

			SCROLL(1,0,temp);

			bad_sound();

			pause(1);

			reduce_hp(adv,damage,FROM_TRAP);

			if (player_is_alive(adv) && poison)
			{
				if (percent()>effective_poison_immunity(adv))
				{
					adv->is_poisoned=TRUE;

					sprintf(temp,"Poison seeps through %s veins.",
								adv->his_her);

					SCROLL(1,0,temp);

					solemn_sound();
				}
				else
				{
					sprintf(temp,"Ye gods smile upon %s!",adv->name);

					SCROLL(1,14,temp);

					sprintf(temp,"%s body resists ye poison!",
							adv->his_her);

					scroll_wrap_write(14,temp);

					good_sound();
				}
			}
		}
		else
		{
			switch(chest_trap_type)
			{
				case CHEST_TRAP_POISON_DART :
					sprintf(temp,"A tiny, poisoned needle whistles past %s%s %s.",
									adv->name,
									end_s(adv->name),
									body[rand()%4]);
					break;

				case CHEST_TRAP_GAS         :
					sprintf(temp,"A cloud of yellow gas bellows up, luckily %s hold %s breath!",
									adv->name,
									adv->his_her);
					break;

				case CHEST_TRAP_ELECTRICITY :
					sprintf(temp,"An electric bolt arcs in front of %s, just missing %s!",
									adv->name,
									adv->him_her);
					break;

				case CHEST_TRAP_DART        :
					sprintf(temp,"A tiny needle whistles past %s%s %s.",
									adv->name,
									end_s(adv->name),
									body[rand()%4]);
					break;
			}

			SCROLL(1,1,temp);

			sprintf(temp,"\"Phew! That was close!\", says %s.",adv->name);

			SCROLL(1,14,temp);

			good_sound();

			pause(3);
		}
	}
	feature=dungeon.map[l][x][y].feature;

	if (feature==DNG_TRAPPED_CHEST)
	{
		the_party.dungeon_current_feature=
		dungeon.map[l][x][y].feature	 =DNG_CHEST;
	}
	else
	{
		the_party.dungeon_current_feature=
		dungeon.map[l][x][y].feature	 =DNG_LOCKED_CHEST;
	}
}

void _PASCAL dng_disarm_chest(PLAYER *adv,int l,int x,int y,int feature)
{
	char temp[120];
	static char *adj[]={"dexterity",
						"ability",
						"aptitude",
						"knowledge",
						"prowess",
						"mastery",
						"finesse",
						"talent",
						"expertise"};

	int dis_trap=effective_disarm_trap(adv);

	if (feature!=DNG_TRAPPED_CHEST && feature!=DNG_TR_LOCK_CHEST)
	{
		sprintf(temp,"%s fiddles about for a while - but to no avail!",
				adv->name);

		SCROLL(1,0,temp);

		general_low_sound();

		return;
	}

	if (dis_trap>=percent())				 /* OK! */
	{
		sprintf(temp,"With great %s, %s disarms ye trap!",
				adj[rand()%(SIZE(adj))],
				adv->name);

		SCROLL(1,14,temp);

		good_sound();

		dungeon.map[l][x][y].trap_triggered=TRUE;

		if (feature==DNG_TRAPPED_CHEST)
		{
			the_party.dungeon_current_feature=
			dungeon.map[l][x][y].feature	 =DNG_CHEST;
		}
		else
		{
			the_party.dungeon_current_feature=
			dungeon.map[l][x][y].feature	 =DNG_LOCKED_CHEST;
		}

		add_to_professionalism(adv,1);
		add_xp_to_party(550L);
	}
	else                                        /* ..oopppsss! */
	{
		sprintf(temp,"..ooppsss! %s fails to disarm ye trap!",
				adv->name);

		SCROLL(1,0,temp);
		solemn_sound();

		pause(1);

		dng_trigger_chest_trap(adv,l,x,y);
	}
}

void _PASCAL dng_dispel_chest(PLAYER *adv)
{
	char temp[80];
	static SPELL_NAME spell={DISPEL_TRAP,"Dispel Trap"};

	if (adv->wizard_spells[DISPEL_TRAP]==NO_SPELL)
	{
		sprintf(temp,"%s doesn't know ye Dispel Trap spell!",adv->name);
		GX(temp,BAD);
		return;
	}
	else
	{
		if (cast_DISPEL_TRAP(adv,&spell))
		{
			add_to_professionalism(adv,1);
			add_xp_to_party(250L);
		}
	}
}

void _PASCAL dng_cast_open_chest(PLAYER *adv)
{
	char temp[80];
	static SPELL_NAME spell={OPEN_CHEST,"Open Chest"};

	if (adv->priest_spells[OPEN_CHEST]==NO_SPELL)
	{
		sprintf(temp,"%s doesn't know ye Open Chest spell!",adv->name);
		GX(temp,BAD);
		return;
	}
	else
	{
		if (cast_OPEN_CHEST(adv,&spell))
		{
			add_to_professionalism(adv,1);
			add_xp_to_party(250L);
		}
	}
}

int _PASCAL dng_chest_trap_type(int l,int x,int y)
{
	int pos=(l*x+y)&4;
	int type;

	switch(pos)
	{
		case 0 : type=CHEST_TRAP_POISON_DART; break;
		case 1 : type=CHEST_TRAP_GAS;         break;
		case 2 : type=CHEST_TRAP_ELECTRICITY; break;
		default: type=CHEST_TRAP_DART;        break;
	}

	return(type);
}

int _PASCAL dng_lock_difficulty(int l,int x,int y)
{
	return(((l*x*(y/2))&3)+1+(the_party.dungeon_level/2));
}
