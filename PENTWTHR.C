#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <ctype.h>
#include <bstrings.h>

struct weather_type {
						char month1;     /* Winter */
						char month2;     /* Spring */
						char month3;     /* Spring */
						char month4;     /* Spring */
						char month5;     /* Summer */
						char month6;     /* Summer */
						char month7;     /* Summer */
						char month8;     /* Autumn */
						char month9;     /* Autumn */
						char month10;    /* Autumn */
						char month11;    /* Winter */
						char month12;    /* Winter */
						char month13;    /* Winter */
					};

struct temp_type    {
						int type;
						int high;
						int low;
					};


static struct weather_type weather=  {'E','E','F','J','K','L','M',
									  'M','K','J','G','E','D'};

static struct temp_type temps[]=
								{'A',-10,-20,
								 'B',-8 ,-16,
								 'C',-5 ,-14,
								 'D',-3 ,-10,
								 'E',-1 ,-8 ,
								 'F',-1 ,-7 ,
								 'G', 0 ,-7 ,
								 'H', 1 ,-6 ,
								 'I', 2 ,-5 ,
								 'J', 4 ,-4 ,
								 'K', 9 ,-3 ,
								 'L', 16, 2 ,
								 'M', 18, 7 ,
								 'N', 21, 10};

void _PASCAL generate_the_weather()
{
	int i,k;
	int month,int_temp,ran,hi,lo;

	int_temp=pent_data.degrees_c;

	month=pent_data.date/28;

	ran=(rand()%6+1)+(rand()%6+1);

	if (ran<5 || ran>9)
	{
		switch(month)
		{
			case 0  : k=weather.month1;  pent_data.season=WINTER; break;
			case 1  : k=weather.month2;  pent_data.season=SPRING; break;
			case 2  : k=weather.month3;  pent_data.season=SPRING; break;
			case 3  : k=weather.month4;  pent_data.season=SPRING; break;
			case 4  : k=weather.month5;  pent_data.season=SUMMER; break;
			case 5  : k=weather.month6;  pent_data.season=SUMMER; break;
			case 6  : k=weather.month7;  pent_data.season=SUMMER; break;
			case 7  : k=weather.month8;  pent_data.season=AUTUMN; break;
			case 8  : k=weather.month9;  pent_data.season=AUTUMN; break;
			case 9  : k=weather.month10; pent_data.season=AUTUMN; break;
			case 10 : k=weather.month11; pent_data.season=WINTER; break;
			case 11 : k=weather.month12; pent_data.season=WINTER; break;
			default : k=weather.month13; pent_data.season=WINTER; break;
		}

		k-='A';

		hi=temps[k].high;
		lo=temps[k].low;

		i=hi-lo;

		int_temp=(rand()%i)+lo;

		pent_data.degrees_c=int_temp;
	}

	if (percent()>70)                                /* Check Rain */
	{
		i=(rand()%2);

		switch(i)
		{
			case 0 : if (pent_data.rain_level>PRECIP_NONE)
						pent_data.rain_level--;
					 break;

			case 1 : if (pent_data.rain_level<PRECIP_HEAVY)
						pent_data.rain_level++;
					 break;
		}
	}

	if (percent()>40)                                 /* Check Wind */
	{
		i=(rand()%2);

		switch(i)
		{
			case 0 : if (pent_data.wind_level>NO_WIND)
						pent_data.wind_level--;
					 break;

			case 1 : if (pent_data.wind_level<STRONG_WIND)
						pent_data.wind_level++;
					 break;
		}
	}

	switch(pent_data.rain_level)                        /* Check Clouds */
	{
		case PRECIP_NONE    : pent_data.cloud_level=CLEAR_SKY;      break;
		case PRECIP_LIGHT   : pent_data.cloud_level=LIGHT_CLOUD;    break;
		case PRECIP_MEDIUM  : pent_data.cloud_level=LIGHT_CLOUD;    break;
		case PRECIP_HEAVY   : pent_data.cloud_level=CLOUDY;         break;
	}

	switch(pent_data.season)
	{
		case SPRING :   i=79; break;
		case SUMMER :   i=83; break;
		case AUTUMN :   i=75; break;
		case WINTER :   i=65; break;
	}

	while ((percent()>i) && (pent_data.cloud_level<DARK_CLOUDS))
		pent_data.cloud_level++;

	switch(pent_data.season)
	{
		case SUMMER : if (pent_data.cloud_level>CLOUDY)
						pent_data.cloud_level=CLOUDY;

					  if (pent_data.rain_level>PRECIP_LIGHT)
						pent_data.rain_level=PRECIP_LIGHT;
					  break;

		case SPRING :
		case AUTUMN : if (pent_data.cloud_level>CLOUDY)
						pent_data.cloud_level=CLOUDY;

					  if (pent_data.rain_level>PRECIP_MEDIUM)
						pent_data.rain_level=PRECIP_MEDIUM;
					  break;

		case WINTER : break;
	}

	if (pent_data.rain_level>PRECIP_NONE)
	{
		if (pent_data.degrees_c>1)
			pent_data.rain_type=RAIN;

		if (pent_data.degrees_c==0 || pent_data.degrees_c==1)
			pent_data.rain_type=SLEET;

		if (pent_data.degrees_c<0)
			pent_data.rain_type=SNOW;
	}
}

static void _PASCAL _NEAR modify_temp_for_latitude(int *temperature)
{
	int temp;
	int lat_modifier=pent_data.y/40;

	temp=*temperature+(lat_modifier-4);

	*temperature=temp;
}

static void _PASCAL _NEAR modify_temp_for_terrain(int *temperature,int terrain)
{
	int diff;

	switch(terrain)
	{
		case HILLS          :   diff=-2; break;
		case MOUNTAINS      :   diff=-3; break;
		case HIGH_MOUNTAINS :   diff=-5; break;

		case WATER          :   diff=-1; break;
		case SEA            :   diff=-2; break;

		case TOWN           :   diff=+1; break;
		case DUNGEON        :   diff=+1; break;
		case RUIN           :   diff=+1; break;

		case CITY           :   diff=+2; break;

		default             :   diff=0;  break;
	}

	*temperature+=diff;
}

char *get_the_weather()
{
	char d_temp[40], *d_temp2, *d_rain, *d_cloud,
		 *d_wind, *d_descrip, d_date[40];
	static char big_string[300];
	int temp_temp;

	temp_temp=effective_temperature();

	sprintf(d_temp,"%d~C",temp_temp);

	pent_data.temperature=DANGEROUSLY_COLD;     /* start here */
	d_temp2=" BITTERLY COLD";

	if (temp_temp>=-9)
	{
		pent_data.temperature=FREEZING;
		d_temp2=" FREEZING COLD";
	}

	if (temp_temp>=1)
	{
		pent_data.temperature=COLD;
		d_temp2=" COLD";
	}

	if (temp_temp>=9)
	{
		pent_data.temperature=COMFORTABLE;
		d_temp2=" COMFORTABLE";
	}

	if (temp_temp>=15)
	{
		pent_data.temperature=WARM;
		d_temp2=" WARM";
	}

	d_descrip="~";

	switch(pent_data.rain_level)
	{
		case PRECIP_NONE	: d_rain="NO RAIN"; break;

		case PRECIP_LIGHT   : switch(pent_data.rain_type)
							  {
								  case RAIN  : d_rain="IT DRIZZLES";		break;
								  case SLEET : d_rain="LIGHT SLEET FALLS";	break;
								  case SNOW  : d_rain="LIGHT SNOW FALLS";	break;
							  }
							  break;

		case PRECIP_MEDIUM  : switch(pent_data.rain_type)
							  {
								  case RAIN  : d_rain="IT IS SHOWERY";	break;
								  case SLEET : d_rain="SLEET FALLS";	break;
								  case SNOW  : d_rain="SNOW FALLS"; 	break;
							  }
							  break;

		case PRECIP_HEAVY   : switch(pent_data.rain_type)
							  {
								  case RAIN  : d_rain="HEAVY RAIN ART DRIVING DOWN"; break;
								  case SLEET : d_rain="HEAVY SLEET FALLS";			 break;
								  case SNOW  : d_rain="HEAVY SNOW FALLS";			 break;
							  }
							  break;
	}

	switch(pent_data.wind_level)
	{
		case NO_WIND	: d_wind="NO WIND"; 		break;
		case LIGHT_WIND : d_wind="SLIGHTLY WINDY";	break;
		case WINDY		: d_wind="QUITE WINDY"; 	break;
		case STRONG_WIND: d_wind="VERY WINDY";		break;
	}

	switch(pent_data.cloud_level)
	{
		case CLEAR_SKY	: d_cloud="YE SKY ART CLEAR!";
						  break;

		case HIGH_CLOUD : d_cloud="THERE IS A LITTLE HIGH CLOUD.";
						  break;

		case LIGHT_CLOUD: d_cloud="THERE ARE A FEW CLOUDS ABOUT.";
						  break;

		case CLOUDY 	: d_cloud="QUITE CLOUDY.";

						  if (percent()>50)
							 d_cloud="CLOUDY.";

						  break;

		case DARK_CLOUDS: d_cloud="VERY CLOUDY.";
						  break;
	}

	if (pent_data.cloud_level==DARK_CLOUDS && pent_data.rain_level>=PRECIP_MEDIUM)
		d_descrip=" IT IS A MISERABLE DAY!";

	if (pent_data.cloud_level==CLEAR_SKY && pent_data.degrees_c>-4)
		d_descrip=" A BEAUTIFUL BUT CHILLY DAY!";

	if (pent_data.cloud_level==CLEAR_SKY && pent_data.degrees_c>3)
		d_descrip=" A BEAUTIFUL, CRISP DAY!";

	if (pent_data.cloud_level==CLEAR_SKY && pent_data.degrees_c>10)
		d_descrip=" A BEAUTIFUL DAY!";

	strcpy(d_date,give_date(pent_data.date));
	sprintf(pent_data.st_date,"%s %d.",d_date,pent_data.year);

	sprintf(big_string,"%s, %s. %s, %s AND %s",d_temp,
											   d_temp2,
											   d_rain,
											   d_wind,
											   d_cloud);

	if (isalnum((int)*d_descrip))
		strcat(big_string,d_descrip);

	stpcvt(big_string,REDUCE);

	return(big_string);
}

int _PASCAL effective_temperature()
{
	int temp;

	switch(pent_data.time_hour)
	{
		case 1 :
		case 2 :
		case 3 : temp=pent_data.degrees_c-4 ; break;
		case 4 :
		case 5 : temp=pent_data.degrees_c-3 ; break;
		case 6 :
		case 7 :
		case 8 : temp=pent_data.degrees_c-2 ; break;
		case 9 :
		case 10:
		case 11: temp=pent_data.degrees_c-1 ; break;
		case 12:
		case 13:
		case 14:
		case 15:
		case 16: temp=pent_data.degrees_c-0 ; break;
		case 17:
		case 18:
		case 19: temp=pent_data.degrees_c-1 ; break;
		case 20:
		case 21:
		case 22: temp=pent_data.degrees_c-2 ; break;
		case 23:
		default: temp=pent_data.degrees_c-3 ; break;
	}

	modify_temp_for_latitude(&temp);
	modify_temp_for_terrain(&temp,pent_data.current_feature);

	return(temp);
}
