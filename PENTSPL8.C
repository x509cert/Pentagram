#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/* Druid Spells non-battle magic */

int _PASCAL cast_WALK_ON_WATER(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	static char temp[140];

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			res=TRUE;

			adv->in_effect.walk_on_water+=10+adv->level*4;

			sprintf(temp,"%s holds %s hands aloft and shouts "
						 "\"Hear me O Skrymyyr, lord of all nature, allow "
						 "thy humble servant to travel on thy hallowed "
						 "waters unhindered..\"",
						 adv->name,
						 adv->his_her);

			print_spell_description(temp);
		}
	}

	return(res);
}

int _PASCAL cast_POISON_IMMUNITY(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	PLAYER *on;
	char temp[120];
	int whom;

	if (enough_spell_points_to_cast(adv,1))
	{
		whom=adv_select_adventurer("Cast Poison","Immunity on?",TRUE);

		if (whom!=ERR)
		{
			res=TRUE;

			on=&TPP[whom];

			on->in_effect.poison_immunity+=(2+adv->level);

			sprintf(temp,"A yellow mist shrouds %s.",on->name);

			print_spell_description(temp);

			if (IN_COMBAT)
				twinkle(CMBT_X(on->x),CMBT_Y(on->y));

			if (on->is_poisoned)
			{
				sprintf(temp,"But %s art already poisoned!",on->name);

				if (IN_COMBAT)
					cmbt_bad_msg(temp,TRUE);
				else
					SCROLL(1,0,temp);

				bad_sound();
			}
		}
		else
			add_lost_spell_pts(adv,1);
	}

	return(res);
}

int _PASCAL cast_PLANT_FEAST(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[120];
	int amount=adv->level*2;

	if (pent_data.current_feature!=FOREST &&
		pent_data.current_feature!=CELTIC_CROSS)
	{
		GX("Plant Feast functions only in woodlands!",BAD);
		return(FALSE);
	}

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			if (pent_data.current_feature==CELTIC_CROSS)
				amount*=2;

			res=TRUE;

			sprintf(temp,"%s picks up some grass and rubs it in %s hands.",
				adv->name,
				adv->his_her);

			SCROLL(1,14,temp);

			pause(1);

			sprintf(temp,"%s drops ye grass, and instantly it turns "
						 "into %d lots of food!",
						 adv->he_she,
						 amount);

			print_spell_description(temp);

			adv->food+=amount;
			adv->food=min(adv->food, MAX_FOOD);
		}
	}

	return(res);
}

/************************************************************************/

int _PASCAL cast_AURA_OF_PROTECTION(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[120];

	if (enough_spell_points_to_cast(adv,2))
	{
		res=TRUE;

		adv->in_effect.aura_protection+=((adv->level*4)+
								effective_spell_luck(adv)/2);

		sprintf(temp,"%s claps %s hands, and a glimmering "
					 "shield engulfs thy party.",
					 adv->name,
					 adv->his_her);

		print_spell_description(temp);
	}

	return(res);
}

int _PASCAL cast_MINDS_EYE(PLAYER *adv,SPELL_NAME *spell_name)
{
	if (IN_DUNGEON)
	{
		GX("Minds Eye functions only above ground!",BAD);
		return(FALSE);
	}

	return(actually_cast_MINDS_EYE(adv,spell_name));
}

#ifndef DEV
#pragma optimize("saz",on)
#endif

int _PASCAL actually_cast_MINDS_EYE(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	GWINDOW win;
	int x,y;
	int i,j,k;
	int xoff,yoff;
	int fin=FALSE;
	int option;
	int col;
	int ok;
	char temp[80];
	char *item;
	static int boundary[]={15,85,50,97,
						   62,85,97,97,
							-1,-1,-1,-1};
	static int things[]={GRASS,          2 ,
						 FOREST,         10,
						 WATER,          9 ,
						 SEA,            1 ,
						 HILLS,          5 ,
						 MOUNTAINS,      7 ,
						 HIGH_MOUNTAINS, 8 ,
						 MARSH,          3 ,
						 PATH,           0 ,
						 TOWN,           11,
						 RUIN,           14,
						 DUNGEON,        13,
						 CELTIC_CROSS,   12,
						 SIGNPOST,       4 ,
						 CITY,           15,
						 BRIDGE,         6};

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,2))
		{
			res=TRUE;

			sprintf(temp,"%s drops to %s knees and clasps %s hands. ",
					adv->name,adv->his_her,adv->his_her);

			SCROLL(1,14,temp);
			half_pause();

			sprintf(temp,"Within seconds, an image of ye land about "
						 "%s forms in %s mind.",
						 adv->name,
						 adv->his_her);

			SCROLL(1,14,temp);
			spell_sound();

			win.x1=2;
			win.y1=2;
			win.x2=14;
			win.y2=14;
			win.back=0;
			win.border=14;

			xoff=win.x1*8+40;
			yoff=win.y1*8+30;

			make_gwindow(&win);

			click_box(15,85,B_SCAN);
			click_box(62,85,B_FINISH);

			x=pent_data.x;
			y=pent_data.y;

			for (i=-30; i<30; i++)
			{
				for (j=-30; j<30; j++)
				{
					if (x+j<=0 || x+j>=MAP_SIZE || y+i<=0 || y+i>=MAP_SIZE)
					{
						FFPLOT(j+xoff,i+yoff,1);
					}
					else
					{
						for (k=0; k<SIZE(things)*2; k+=2)
						{
							if ((int)map_bit(x+j,y+i)==things[k])
							{
								FFPLOT(j+xoff,i+yoff,(char)things[k+1]);
								break;
							}
						}
					}
				}
			}

			cast_MINDS_EYE_display_party(x,y);

			while (!fin)                                               /* Main Loop */
			{
				option=mouse_in_range(boundary,"SF","SQ");

				if (option==0)                                         /* Do Scan */
				{
					for (i=-30; i<30; i++)
					{
						for (j=-30; j<30; j++)
						{
							if (x+j>0 && x+j<MAP_SIZE && y+i>0 && y+i<MAP_SIZE)
							{
								for (k=0; k<SIZE(things)*2; k+=2)
								{
									if ((int)map_bit(x+j,y+i)==things[k])
									{
										col=things[k+1];
										break;
									}
								}

								ok=TRUE;

								switch((int)map_bit(x+j,y+i))
								{
									case TOWN		  : item="  TOWN  "; break;
									case CITY		  : item="WOLFBURG"; break;
									case SIGNPOST	  : item="SIGNPOST"; break;
									case CELTIC_CROSS : item="  CROSS "; break;
									case RUIN		  : item="  RUIN  "; break;
									case DUNGEON	  : item=" DUNGEON"; break;
									default 		  : ok=FALSE;
														break;
								}

								if (!i && !j)
									cast_MINDS_EYE_display_party(x,y);

								if (ok)
								{
									write_little(item,
												 40,
												 78,
												 15,
												 FAST);

									cast_MINDS_EYE_make_sound();

									for (k=0; k<15; k++)
									{
										FFPLOT(j+xoff,i+yoff,15);
										delay(70);

										FFPLOT(j+xoff,i+yoff,0);
										delay(70);

										FFPLOT(j+xoff,i+yoff,(char)col);
										delay(70);
									}

									write_little("        ",
												 40,
												 78,
												 0,
												 SLOW);
								}
							}
						}
					}
				}
				else
					fin=TRUE;
			}

			kill_gwindow(&win);
		}
	}

	return(res);
}

void _PASCAL cast_MINDS_EYE_display_party(int x,int y)
{
	int col;
	static int things[]={GRASS,          2 ,
						 FOREST,         10,
						 WATER,          9 ,
						 SEA,            1 ,
						 HILLS,          5 ,
						 MOUNTAINS,      7 ,
						 HIGH_MOUNTAINS, 8 ,
						 MARSH,          3 ,
						 PATH,           0 ,
						 TOWN,           11,
						 RUIN,           14,
						 DUNGEON,        13,
						 CELTIC_CROSS,   12,
						 SIGNPOST,       4 ,
						 CITY,           15,
						 BRIDGE,         6};
	int j,k;
	int xoff,yoff;

	xoff=2*8+40;
	yoff=2*8+30;


	write_little("THY PARTY",
				 38,
				 78,
				 15,
				 FAST);

	for (k=0; k<SIZE(things)*2; k+=2)     /* Flash Party */
	{
		if ((int)map_bit(x,y)==things[k])
		{
			col=things[k+1];
			break;
		}
	}

	cast_MINDS_EYE_make_sound();

	for (k=0; k<10; k++)
	{
		for (j=0; j<16; j++)
		{
			FFPLOT(xoff,yoff,(char)j);
			delay(20);
		}

		FFPLOT(xoff,yoff,(char)col);
		delay(10);
	}

	write_little("         ",
				 38,
				 78,
				 0,
				 SLOW);
}

#ifndef DEV
#pragma optimize("",on)
#endif
