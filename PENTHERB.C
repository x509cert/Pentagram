#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

static HERBS all_herbs[]=
	{

/* 15*/ "Thornbrig",   HERB_THORNBRIG ,COMMON,   HERB_EFF_NOTHING, HERB_BIT_PETAL , HERB_COL_ORANGE      ,FOREST,   HILLS, HILLS, 0  ,
/* 15*/ "Pigwort",     HERB_PIGWORT   ,COMMON,   HERB_EFF_NOTHING, HERB_BIT_PETAL , HERB_COL_YELLOW      ,MOUNTAINS,GRASS, HILLS, 0  ,
/*  9*/ "Wolfpetal",   HERB_WOLFPETAL ,UNCOMMON, HERB_EFF_DIV_PT , HERB_BIT_BERRY , HERB_COL_PINK        ,MOUNTAINS,HILLS, HILLS, 3  ,
/*  9*/ "Ashleaf",     HERB_ASHLEAF   ,UNCOMMON, HERB_EFF_NOTHING, HERB_BIT_FLOWER, HERB_COL_RED         ,PATH,     GRASS, HILLS, 0  ,
/*  9*/ "Wyneweed",    HERB_WYNEWEED  ,UNCOMMON, HERB_EFF_DRUNK  , HERB_BIT_BERRY,  HERB_COL_PASTEL_BLUE ,GRASS,    HILLS, FOREST,-1 ,
/*  5*/ "Mirenna",     HERB_MIRENNA   ,RARE,     HERB_EFF_HP     , HERB_BIT_FLOWER, HERB_COL_PURPLE      ,FOREST,   HILLS, HILLS, 12 ,
/*  5*/ "Ruwk",        HERB_RUWK      ,RARE,     HERB_EFF_HP     , HERB_BIT_BERRY , HERB_COL_WHITE       ,FOREST,   HILLS, HILLS, -10,
/*  5*/ "Leechweed",   HERB_LEECHWEED ,RARE,     HERB_EFF_DISEASE, HERB_BIT_PETAL , HERB_COL_YELLOW      ,MOUNTAINS,MARSH, MARSH, 1  ,
/*  5*/ "Beerberry",   HERB_BEERBERRY ,RARE,     HERB_EFF_SORC_PT, HERB_BIT_PETAL , HERB_COL_PURPLE      ,FOREST,   GRASS, HILLS, -4 ,
/*  5*/ "Wild Sprig",  HERB_WILDSPRIG ,RARE,     HERB_EFF_HP     , HERB_BIT_FLOWER, HERB_COL_WHITE       ,FOREST,   HILLS, HILLS, 5  ,
/*  5*/ "Glowpetal",   HERB_GLOWPETAL ,RARE,     HERB_EFF_NOTHING, HERB_BIT_BERRY , HERB_COL_YELLOW      ,FOREST,   HILLS, HILLS, 0  ,
/*  5*/ "Snoweed",     HERB_SNOWEED   ,RARE,     HERB_EFF_SORC_PT, HERB_BIT_FLOWER, HERB_COL_BRIGHT_GREEN,GRASS,    GRASS, HILLS, 2  ,
/*  5*/ "Gylvir",      HERB_GYLVIR    ,RARE,     HERB_EFF_POISON , HERB_BIT_FLOWER, HERB_COL_PASTEL_BLUE ,FOREST,   HILLS, HILLS, 1  ,
/*  4*/ "Angel's Wing",HERB_ANGELSWING,VERY_RARE,HERB_EFF_DIV_PT , HERB_BIT_BERRY , HERB_COL_RED         ,FOREST,   HILLS, HILLS, -4 ,
/*  4*/ "Edram",       HERB_EDRAM     ,VERY_RARE,HERB_EFF_HP     , HERB_BIT_PETAL , HERB_COL_RED         ,HILLS,    HILLS, HILLS, 10 ,
/*  4*/ "Ice Nettle",  HERB_ICE_NETTLE,VERY_RARE,HERB_EFF_POISON , HERB_BIT_PETAL , HERB_COL_ORANGE      ,MOUNTAINS,HILLS, HILLS, -15,
	};

void _PASCAL actually_forage(PLAYER *adv)
{
	int herb_num     =get_a_random_herb();
	int terrain      =pent_data.current_feature;
	int chance       =chance_of_finding_herb(herb_num,terrain);
	int player_chance=effective_find_herb(adv);
	char temp[80];

	if (terrain==SEA || terrain==WATER)
	{
		sprintf(temp,"%s finds naught but tangled seaweed!",adv->name);
		SCROLL(1,0,temp);

		bad_sound();

		return;
	}

	if (bard_is_singing(adv,"to forage for herbs"))
		return;

	if ((player_chance>=percent()) && (player_chance>=chance))
		herb_found(herb_num,adv);
	else
		herb_not_found(adv);
}

int _PASCAL get_a_random_herb()
{
	int perc,herb_num;
	int i;
	static struct {
						int num,hi,lo;

				  } herb_chances[]={0 ,0 ,14,
									1 ,15,29,
									2 ,30,38,
									3 ,39,47,
									4 ,48,52,
									5 ,53,57,
									6 ,58,62,
									7 ,63,67,
									8 ,68,72,
									9 ,73,77,
									10,78,82,
									11,83,87,
									12,88,91,
									13,92,95,
									14,96,99};
	perc=percent();

	for (i=0; i<SIZE(herb_chances); i++)
	{
		if (perc>=herb_chances[i].hi && perc<=herb_chances[i].lo)
		{
			herb_num=i;
			break;
		}
	}

	return(herb_num);
}

int _PASCAL chance_of_finding_herb(int herb_num,int terrain)
{
	if (all_herbs[herb_num].terrain1==terrain ||
		all_herbs[herb_num].terrain2==terrain ||
		all_herbs[herb_num].terrain3==terrain)
		return(66+terrain);
	else
		return(0);
}

void _PASCAL herb_found(int herb_num,PLAYER *adv)
{
	char temp[100];
	char desc[30];

	strcpy(desc,describe_herb(herb_num));

	sprintf(temp,"After much searching, %s finds a herb with %s.",
				 adv->name,
				 desc);

	SCROLL(1,14,temp);
	good_sound();

	pause(1);

	sprintf(temp,"Ye herb art %s.",all_herbs[herb_num].name);
	SCROLL(1,1,temp);
	good_sound();

	if (gget_yn("Dost thou keep ye herb?")==TRUE)
	{
		add_herb_to_player(herb_num,adv);
		adv_sort_herbs(adv);
	}
	else
	{
		sprintf(temp,"With great care, %s replants ye herb!",adv->name);
		SCROLL(1,0,temp);
		general_low_sound();
	}
}

void _PASCAL herb_not_found(PLAYER *adv)
{
	char temp[110];
	static char *v[]={"searching",
					  "foraging",
					  "probing",
					  "seeking"};

	sprintf(temp,"%s spends much time %s for herbs, but to no avail!",
					adv->name,
					v[rand()%4]);

	SCROLL(1,0,temp);

	bad_sound();
}

char *describe_herb(int herb_num)
{
	int i,ncol,nname;
	static char temp[50];
	static struct {
					int ncol;
					char *col;

				  } desc[]={HERB_COL_RED,         "red",
							HERB_COL_BLUE,        "blue",
							HERB_COL_PURPLE,      "purple",
							HERB_COL_YELLOW,      "yellow",
							HERB_COL_WHITE,       "white",
							HERB_COL_BRIGHT_GREEN,"bright green",
							HERB_COL_PINK,        "pink",
							HERB_COL_ORANGE,      "orange",
							HERB_COL_PASTEL_BLUE, "pastel blue",
						   };
	static struct {
					int nname;
					char *name;

				  } bits[]={HERB_BIT_PETAL, "petals",
							HERB_BIT_FLOWER,"flowers",
							HERB_BIT_BERRY, "berries",
						   };

   for (i=0; i<SIZE(desc); i++)
	if (desc[i].ncol==all_herbs[herb_num].colour)
		ncol=i;

   for (i=0; i<SIZE(bits); i++)
	if (bits[i].nname==all_herbs[herb_num].coloured_part)
		nname=i;

   sprintf(temp,"%s %s",desc[ncol].col,bits[nname].name);

   return(temp);
}

int _PASCAL get_herb_number(int herb_num)
{
	int i,res;

	for (i=0; i<SIZE(all_herbs); i++)
		if (all_herbs[i].nname==herb_num)
			res=i;

	return(res);
}

void _PASCAL add_herb_to_player(int herb_num,PLAYER *adv)
{
	int i;
	char temp[80];
	char temp1[100];
	int empty_slot=FALSE;
	static char *v[]={"a wind blows ye herb from %s hand",
					  "a bird swoops and steals %s herb",
					  "ye herb mysteriously vanishes from %s grip"};

	for (i=0; i<MAX_HERBS_CARRY; i++)
	{
		if (adv->herbs_carried[i]==HERB_NONE)
		{
			empty_slot=TRUE;
			adv->herbs_carried[i]=all_herbs[herb_num].nname;

			sprintf(temp,"%s carefully tucks ye herb away..",adv->name);
			SCROLL(1,14,temp);

			good_sound();

			break;
		}
	}

	if (!empty_slot)
	{
		sprintf(temp,v[rand()%3],adv->his_her);
		sprintf(temp1,"Whilst walking back to ye party, %s!",temp);

		SCROLL(1,0,temp1);
		bad_sound();
		pause(1);

		SCROLL(1,0,"Ye herb art lost......!");
		solemn_sound();
	}
}

void _PASCAL adv_actually_use_herbs(PLAYER *adv)
{
	int herb_num=select_a_herb_from_list(adv);

	if (herb_num!=HERB_NONE)
		actually_eat_herb(adv,herb_num);
}

int _PASCAL select_a_herb_from_list(PLAYER *adv)
{
	int num=adv_num_herbs(adv);
	GWINDOW win;
	int herb_num=HERB_NONE;
	int i;
	char temp[40];
	int sel;
	int fin=FALSE;
	static int boundary[]={ 80,56, 200,62,
							80,64, 200,70,
							80,72, 200,78,
							80,80, 200,86,
							80,88, 200,94,
							123,108,158,120,
							-1,-1,-1,-1};

	if (num==0)
	{
		sprintf(temp,"%s hath no herbs!",adv->name);
		GX(temp,BAD);

		return(HERB_NONE);
	}

	win.x1=10;
	win.y1=6;
	win.x2=27;
	win.y2=win.y1+6+MAX_HERBS_CARRY;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+2);
	_outtext("Select Herb..");

	click_box(123,108,B_QUIT);

	adv_sort_herbs(adv);

	for (i=0; i<MAX_HERBS_CARRY; i++)
	{
		if (adv->herbs_carried[i]!=HERB_NONE)
		{
			_settextcolor(13);
			sprintf(temp,"%cù",i+'A');
			_settextposition(win.y1+2+i,win.x1+1);
			_outtext(temp);

			_settextcolor(5);
			_settextposition(win.y1+2+i,win.x1+3);
			strcpy(temp,get_herb_name(adv->herbs_carried[i],FALSE));
			_outtext(temp);
		}
	}

	while (!fin)
	{
		sel=mouse_in_range(boundary,"ABCDEQ","");

		if (sel!=MAX_HERBS_CARRY)
		{
			if ((sel+1)<=num)
			{
				herb_num=adv->herbs_carried[sel];
				fin=TRUE;
			}
		}
		else
		{
			herb_num=HERB_NONE;
			fin=TRUE;
		}
	}

	kill_gwindow(&win);

	return(herb_num);
}

void _PASCAL actually_eat_herb(PLAYER *adv,int herb_num)
{
	char temp[80];
	int effect;
	int damage_cure;
	int damage;
	int i=get_herb_number(herb_num);
	int nothing_happens=FALSE;

	effect     =all_herbs[i].effect;
	damage_cure=all_herbs[i].damage_cure;

	remove_herb_from_adv(adv,herb_num);

	sprintf(temp,"%s eats ye %s and ...",
				 adv->name,
				 get_herb_name(herb_num,FALSE));

	SCROLL(1,14,temp);

	pause(2);

	if (damage_cure==0)
		nothing_happens=TRUE;
	else
	if (damage_cure<0)
	{
		switch(effect)
		{
			case HERB_EFF_POISON  :
			case HERB_EFF_HP      : sprintf(temp,"%s Feels burning in %s throat!",
												 adv->he_she,
												 adv->his_her);

									scroll_wrap_write(0,temp);
									damage=modified_damage(get_dice_roll(abs(damage_cure),1,1));

									bad_sound();

									pause(1);

									reduce_hp(adv,
											  damage,
											  effect==HERB_EFF_HP?FROM_HERBS
																 :FROM_POISON);

									if (player_is_alive(adv))
									{
										sprintf(temp,"and takes %d damage!",damage);
										SCROLL(1,0,temp);

										bad_sound();
									}

									break;

			case HERB_EFF_SORC_PT :
			case HERB_EFF_DIV_PT  : if ((adv->current_divine_points  && effect==HERB_EFF_DIV_PT) ||
										(adv->current_sorcery_points && effect==HERB_EFF_SORC_PT))
									{
										sprintf(temp,"noticies %s %s power dimishing!",
											adv->his_her,
											effect==HERB_EFF_DIV_PT?"divine":"sorcery");

										SCROLL(1,0,temp);

										damage=modified_damage(get_dice_roll(abs(damage_cure),1,1));

										if (effect==HERB_EFF_DIV_PT)
										{
											adv->current_divine_points-=damage;

											if (adv->current_divine_points<0)
												adv->current_divine_points=0;
										}
										else
										{
											adv->current_sorcery_points-=damage;

											if (adv->current_sorcery_points<0)
												adv->current_sorcery_points=0;
										}

										bad_sound();
										pause(1);
									}
									else
										nothing_happens=TRUE;

									break;

			case HERB_EFF_DRUNK   : adv->drunkeness=adv->max_drunkeness;

									sprintf(temp,"%s sharts to shlur %s shpeech!",
										adv->he_she,
										adv->his_her);

									SCROLL(1,0,temp);
									bad_sound();

									break;

			default               : nothing_happens=TRUE;
									break;
		}
	}
	else
	{
		switch(effect)
		{
			case HERB_EFF_HP      : if (adv->hp==adv->current_hp)
										nothing_happens=TRUE;
									else
									{
										sprintf(temp,"%s feels rejuvinated!",
												adv->he_she);

										damage=modified_damage(get_dice_roll(abs(damage_cure),1,1));

										adv->current_hp+=damage;

										if (adv->current_hp>adv->hp)
											adv->current_hp=adv->hp;

										SCROLL(1,14,temp);

										good_sound();
									}

									break;

			case HERB_EFF_DISEASE : if (adv->disease==NO_DISEASE)
										nothing_happens=TRUE;
									else
									{
										recover_from_disease(adv);

										sprintf(temp,"%s feels healthier!",
													adv->he_she);

										SCROLL(1,14,temp);

										good_sound();
									}

									break;

			case HERB_EFF_POISON  : if (!adv->is_poisoned)
										nothing_happens=TRUE;
									else
									{
										adv->is_poisoned=FALSE;

										sprintf(temp,"%s feels refreshed!",
											adv->he_she);

										SCROLL(1,14,temp);

										good_sound();
									}

									break;

			case HERB_EFF_SORC_PT :
			case HERB_EFF_DIV_PT  : if ((adv->divine_points  && effect==HERB_EFF_DIV_PT) ||
										(adv->sorcery_points && effect==HERB_EFF_SORC_PT))
									{
										if (adv->divine_points!=adv->current_divine_points &&
											adv->sorcery_points!=adv->current_sorcery_points)
										{
											sprintf(temp,"%s noticies %s %s power increasing!",
												adv->he_she,
												adv->his_her,
												effect==HERB_EFF_DIV_PT?"divine":"sorcery");

											SCROLL(1,0,temp);

											damage=modified_damage(get_dice_roll(abs(damage_cure),1,1));

											if (effect==HERB_EFF_DIV_PT)
											{
												adv->current_divine_points+=damage;

												if (adv->current_divine_points>adv->divine_points)
													adv->current_divine_points=adv->divine_points;
											}
											else
											{
												adv->current_sorcery_points+=damage;

												if (adv->current_sorcery_points<adv->sorcery_points)
													adv->current_sorcery_points=adv->sorcery_points;
											}

											good_sound();
											pause(1);
										}
										else
											nothing_happens=TRUE;
									}
									else
										nothing_happens=TRUE;

									break;

			default               : nothing_happens=TRUE;
									break;
		}
	}

	if (nothing_happens)
	{
		sprintf(temp,"Naught seems to happen to %s!",adv->him_her);
		SCROLL(1,1,temp);

		general_low_sound();
	}
}

void _PASCAL remove_herb_from_adv(PLAYER *adv,int herb_num)
{
	int i;

	for (i=0; i<MAX_HERBS_CARRY; i++)
	{
		if (adv->herbs_carried[i]==herb_num)
		{
			adv->herbs_carried[i]=HERB_NONE;
			adv_sort_herbs(adv);

			break;
		}
	}
}

void _PASCAL adv_sort_herbs(PLAYER *adv)
{
	qsort((void *)adv->herbs_carried,
		  MAX_HERBS_CARRY,
		  sizeof(int),
		  herb_sorter);
}

int _CDECL herb_sorter(int *herb1,int *herb2)	   /* Sorts in Reverse order */
{
	if (*herb1<*herb2)
		return(1);

	if (*herb1==*herb2)
		return(0);

	return(ERR);
}

void _PASCAL actually_swap_herbs(int f,int t)
{
	char temp[60];
	int herb_num;
	int pos;
	int i;

	if (adv_num_herbs(&TPP[t])>=MAX_HERBS_CARRY)
	{
		sprintf(temp,"%s hath enough herbs already!",TPP[t].name);
		GX(temp,BAD);
	}
	else
	{
		herb_num=select_a_herb_from_list(&TPP[f]);

		if (herb_num!=HERB_NONE)
		{
			for (i=0; i<SIZE(all_herbs); i++)
				if (all_herbs[i].nname==herb_num)
					pos=i;

			remove_herb_from_adv(&TPP[f],herb_num);
			swap_add_herb_to_player(pos,&TPP[t]);

			good_sound();
		}
	}
}

void _PASCAL swap_add_herb_to_player(int herb_num,PLAYER *adv)
{
	int i;
	char temp[80];

	for (i=0; i<MAX_HERBS_CARRY; i++)
	{
		if (adv->herbs_carried[i]==HERB_NONE)
		{
			adv->herbs_carried[i]=all_herbs[herb_num].nname;

			sprintf(temp,"%s carefully tucks ye herb away..",adv->name);
			GX(temp,GOOD);

			break;
		}
	}
}
