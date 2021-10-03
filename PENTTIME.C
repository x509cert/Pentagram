#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

#define DNX 251
#define DNY  52

static char *daysl[]={"Sunday",  "Moonday","Tuesday","Wandsday",
					  "Thorsday","Fryday", "Satyrday"};

void _PASCAL day_night()
{
	int day_nite;

	if (pent_data.time_minute>=60)
	{
		pent_data.time_hour++;
		pent_data.time_minute=0;

		if (pent_data.time_hour==24)
		{
			new_day(CHECK_BIRTHDAYS,TRUE);
			pent_data.time_hour=0;
		}
	}

	day_nite=determine_day_nite_icon();

	if (pent_data.current_day_night_icon!=day_nite)
	{
		pent_data.current_day_night_icon=day_nite;
		draw_first_day_night();
	}
}

void _PASCAL set_next_day_dawn()
{
	new_day(CHECK_BIRTHDAYS,FALSE);

	pent_data.time_hour=7;
	pent_data.time_minute=30;

	determine_day_nite_icon();
}

int _PASCAL determine_day_nite_icon()
{
	int day_nite;

	switch(pent_data.time_hour)
	{
		case 7 :
		case 8 :	day_nite=1;  break;
		case 9 :
		case 10:	day_nite=2;  break;
		case 11:
		case 12:
		case 13:	day_nite=4;  break;
		case 14:
		case 15:    day_nite=5;  break;
		case 16:
		case 17:    day_nite=6;  break;
		case 18:
		case 19:    day_nite=7;  break;
		case 20:
		case 21:    day_nite=11; break;
		case 22:    day_nite=12; break;
		case 23:
		case 0 :    day_nite=13; break;
		case 1 :
		case 2 :    day_nite=14; break;
		case 3 :    day_nite=15; break;
		case 4 :    day_nite=16; break;
		case 5 :
		default:    day_nite=17; break;
	}

	return(day_nite);
}

void _PASCAL draw_first_day_night()
{
	char _FAR *icon;

	switch(pent_data.current_day_night_icon)
	{
		case 0	:
		case 1	: icon=day_nite_icon_1;  break;
		case 2	: icon=day_nite_icon_2;  break;
		case 4	: icon=day_nite_icon_4;  break;
		case 5	: icon=day_nite_icon_5;  break;
		case 6	: icon=day_nite_icon_6;  break;
		case 7	: icon=day_nite_icon_7;  break;
		case 11 : icon=day_nite_icon_11; break;
		case 12 : icon=day_nite_icon_12; break;
		case 13 : icon=day_nite_icon_13; break;
		case 14 : icon=day_nite_icon_14; break;
		case 15 : icon=day_nite_icon_15; break;
		case 16 : icon=day_nite_icon_16; break;
		case 17 : icon=day_nite_icon_17; break;
	}

	_putimage(DNX,DNY,icon,_GPSET);
}

void _PASCAL check_birthdays()
{
	int i;
	char temp[80];

	for (i=0; i<=P_NUM; i++)
	{
		if (TPP[i].birth_date==pent_data.date)
		{
			if (player_is_alive(&TPP[i]))
			{
				sprintf(temp,"Today, ye %s, art %s%s birthday!",
							 TPP[i].birthday,
							 TPP[i].name,
							 end_s(TPP[i].name));

				GX(temp,GOOD);

				TPP[i].nage++;
				adv=TPP[i];
				train_get_age_cat();
				TPP[i]=adv;
			}
		}
	}
}

void _PASCAL new_day(int check_births,int check_deity)
{
	pent_data.date++;

	if (pent_data.date>359)
	{
		pent_data.date=0;
		pent_data.year++;
	}

	pent_data.day++;

	if (pent_data.day==7)
		pent_data.day=0;

	switch((pent_data.date%28)+1)
	{
		case 1  :
		case 2  :
		case 3  :   pent_data.moon_phase=NEW_MOON ; break;
		case 4  :
		case 5  :   pent_data.moon_phase=PHASE_2  ; break;
		case 6  :
		case 7  :   pent_data.moon_phase=PHASE_3  ; break;
		case 8  :   pent_data.moon_phase=PHASE_3  ; break;
		case 9  :
		case 10 :   pent_data.moon_phase=PHASE_4  ; break;
		case 11 :
		case 12 :   pent_data.moon_phase=PHASE_5  ; break;
		case 13 :
		case 14 :   pent_data.moon_phase=PHASE_6  ; break;
		case 15 :
		case 16 :
		case 17 :   pent_data.moon_phase=FULL_MOON; break;
		case 18 :
		case 19 :   pent_data.moon_phase=PHASE_8  ; break;
		case 20 :
		case 21 :
		case 22 :   pent_data.moon_phase=PHASE_9  ; break;
		case 23 :
		case 24 :   pent_data.moon_phase=PHASE_10 ; break;
		case 25 :
		case 26 :   pent_data.moon_phase=PHASE_11 ; break;
		case 27 :
		default :   pent_data.moon_phase=PHASE_12 ; break;
	}

	generate_the_weather();
	disease_update_all_players();
	update_wands_rings_at_midnight();

	if (the_party.resting)
		check_hypothermia();

	update_all_spell_drains();

	if (check_deity)
		check_deity_angry();

	if (check_births==CHECK_BIRTHDAYS)
		check_birthdays();
}

static void _PASCAL _NEAR update_all_spell_drains()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (TPP[i].points_cast)
			TPP[i].points_cast=0;
}

void _PASCAL check_hypothermia()
{
	int i;

	if (pent_data.degrees_c>=0 || the_party.fire_lit || IN_DUNGEON)
		return;

	for (i=0; i<=P_NUM; i++)
		check_hypothermia_one(&TPP[i]);
}

void _PASCAL check_hypothermia_one(PLAYER *adv)
{
	if (player_is_dead(adv))
		return;

	if (percent()>effective_survival(adv))
		inflict_hypothermia_damage(adv);
}

void _PASCAL inflict_hypothermia_damage(PLAYER *adv)
{
	char temp[80];
	int damage=get_dice_roll((abs(pent_data.degrees_c)),2,1);

	if (adv->ring_used.item==WARMTH_RING)
		return;

	sprintf(temp,"%s takes %d damage from hypothermia!",adv->name,damage);

	SCROLL(1,0,temp);

	bad_sound();
	half_pause();

	reduce_hp(adv,damage,FROM_CHILL);
}

void _PASCAL check_deity_angry()
{
	int i;

	for (i=0; i<P_NUM; i++)
		if (player_overdue_at_praying(&TPP[i]))
			deity_angry(&TPP[i]);
}

void _PASCAL update_wands_rings_at_midnight()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			update_one_wand_ring(&TPP[i]);
}

void _PASCAL update_one_wand_ring(PLAYER *adv)
{
	adv->thunder_wand_used	   = 0;
	adv->fire_wand_used 	   = 0;
	adv->ice_wand_used		   = 0;
	adv->stave_healing_used    = 0;
	adv->sustenance_wand_used  = 0;

	adv->ring_of_fire_used	   = 0;
	adv->ring_of_icicles_used  = 0;

	adv->bard_songs_sung	   = 0;
}

int _PASCAL is_night_time()
{
	if (pent_data.time_hour>=20 || pent_data.time_hour<7)
		return(TRUE);
	else
		return(FALSE);
}

unsigned long _PASCAL convert_date_to_half_hours(int day_of_year,int hour,int minutes)
{
	unsigned long res;
	unsigned long month;
	unsigned long day;

	day=(unsigned long)day_of_year%28;
	day++;

	month=(unsigned long)day_of_year/28;
	month++;

	res=(unsigned long)(((unsigned long)hour*2L)+
						((unsigned long)day*48L)+
						((unsigned long)month*1344L));

	if (minutes)
		res++;

	return(res);
}

char *get_time_string(int h,int m)
{
	static char time[50];

	if (m==0 && (h==0 || h==24 || h==12))
	{
		if (h==0 || h==24)
			strcpy(time,"Midnight");
		else
		if (h==12)
			strcpy(time,"Midday");
	}
	else
	{
		sprintf(time,"%d:%02d %s", h>12?h-12:h,
								   m,
								   h>=12?(h>=24?"AM":"PM"):"AM");
	}

	return(time);
}

char *give_date(unsigned int in)   /* 13 Months of 28 days each */
{
	 int i, month, day;
	 char days[20], temp[40];
	 static char week_day[40];
	 static char *monthsl[]={"Januari",  "Februari","March",   "Aprile",
							 "Mai", 	 "June",	"Juli",    "August",
							 "Septembre","Oktobre", "Novembre","Decembre",
							 "Yulesend"};
	 i = in % 364;
	 day = in % 28;
	 day++;

	 month = i / 28;
	 month++;

	 sprintf(days,"%s,",daysl[day%7]);

	 strcpy(temp,monthsl[month-1]);

	 sprintf(week_day,"%s %d",days,day);

	 i=(day % 10);

	 if (day<11 || day>19)
	 {
		switch (i)
		{
			  case 1 : strcat(week_day,"st"); break;
			  case 2 : strcat(week_day,"nd"); break;
			  case 3 : strcat(week_day,"rd"); break;
			  default: strcat(week_day,"th"); break;
		}
	 }
	 else
	 {
		strcat(week_day,"th");
	 }

	 strcat(week_day," of ");
	 strcat(week_day,temp);

	 return(week_day);
}

int _PASCAL check_today_is_sunday_msg(char *where)
{
	char d_date[80];
	int res=FALSE;

	strcpy(d_date,give_date(pent_data.date));
	strlwr(d_date);

	if (strstr(d_date,"sun")!=NULL)
	{
		sprintf(d_date,"Alas! Ye %ss close on Sunday!",where);
		GX(d_date,SOLEMN);
		res=TRUE;
	}

	return(res);
}
