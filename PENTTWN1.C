#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

SMALL_TOWN small_towns[]=
		{

			"Wolfburg",   0 , "Pentagram",		TWN_CITY,	  89, 86,
			"Two imposing towers flank a great gateway bristling with murder holes and an iron portcullis, behind which lies ye capital city of Ye Realms.",
			D_ATHIN,

			"Foxhollow",  1 , "Fiery Dragon",	TWN_HAMLET,   82, 60,
			"A sedate hamlet nestled amongst ye Encircling Mts.",
			D_DUMATHIN,

			"Riverdawn",  9 , "Haunted Keep",	TWN_VILLAGE,  48,141,
			"A lively fishing village famed for it's resilient fishing equipment.",
			D_CYRR,

			"Riverneck",  23, "Dancing Goblin", TWN_TOWN,	  54,152,
			"A picturesque fishing village. Much rivalry exists between Riverneck and Riverdawn.",
			D_CYRR,

			"Landir",	  22, "Greedy Dwarf",	TWN_VILLAGE, 113,189,
			"Along with Tiravel, ye most southerly and warmest village.",
			D_MAGMI,

			"Sea Point",  16, "Mermaid's Rest", TWN_TOWN,	  15, 71,
			"A bustling whaling town. Smaller than Frosthaven, but renowned for its whale blubber.",
			D_AERDRI,

			"Tiravel",	  4 , "Broken Mast",	TWN_HAMLET,   89,189,
			"Along with Landir, ye most southerly and warmest village",
			D_TARL,

			"Erihn",	  7 , "Wayside",		TWN_VILLAGE, 114, 36,
			"A beautiful village surrounded by ye Encircling Mts and River Iceway.",
			D_OLRIC,

			"Kaitlin",	  10, "Raven's Return", TWN_TOWN,	 110,146,
			"A town built to accomodate adventurers on their way to explore nearby dungeons and ruins.",
			D_ENORETH,

			"Dun Cirach", 2 , "Wayfarers Rest", TWN_HAMLET,  162,145,
			"A tiny, boring hamlet. No one remembers much about Dun Cirach.",
			D_MORR,

			"Dun Tarith", 11, "Crossed Swords", TWN_VILLAGE,  13, 48,
			"A lonely village, founded on a profitable boat building industry.",
			D_TARL,

			"Frosthaven", 12, "Bleeding Heart", TWN_TOWN,	  66, 12,
			"By far ye largest fishing and whaling town in Ye Realms.",
			D_OLRIC,

			"Minash",	  13, "Dwarven Forge",	TWN_HAMLET,  182,165,
			"A hamlet renowned for its earthenware and school of pottery.",
			D_SOLONIR,

			"Angharad",   8 , "Crucible",		TWN_VILLAGE, 156, 21,
			"A fishing village used as a stop over for adventurers travelling north to Dungeon Mort.",
			D_MAGMI,

			"North Rhyde",15, "Golden Chalice", TWN_TOWN,	 121, 73,
			"A town renowned for its hospitality and vice!",
			D_CELANIL,

			"Cape Dawn",  6 , "King's Head",	TWN_HAMLET,  185, 85,
			"Ye first town to witness sunrise. Cape Dawn was once ye most important sea town in Ye Realms.",
			D_CELANIL,

			"Telkar",	  17, "Four Winds", 	TWN_VILLAGE,  26,137,
			"A busy seaside village, infamous for gusty winds and frequent storms.",
			D_AERDRI,

			"Kanraith",   18, "Red Barn",		TWN_TOWN,	 178,182,
			"A small but wealthy town rebuilt after it was destroyed by a great fire in 846.",
			D_RHYAA,

			"South Rhyde",19, "Stag's Head",	TWN_HAMLET,  121, 83,
			"A quiet hamlet and birthplace of ye \"Father of Astronomy\", Andre Yarak.",
			D_RHYAA,

			"Rayek",	  20, "Staff and Wand", TWN_VILLAGE, 178, 47,
			"A tiny village at ye throat of Fools Valley.",
			D_ATHIN,

			"Oak Vale",   5 , "Druid's Rest",	TWN_HAMLET,   55, 51,
			"This hamlet, positioned in Greatwood, art often called \"Druids Retreat\" because of its solitude.",
			D_DUMATHIN,

			"Mist Point", 21, "Shipwreck",		TWN_TOWN,	 170,106,
			"A large naval base and greatest trading port in ye Realms.",
			D_CYRR,

			"Blacklock",  25, "Fiery Pit",      TWN_TOWN,     34,181,
			"A bleak, almost deserted town. Rumour tells of a great terror beyond ye moutains.",
			D_MORR,
		};

int _PASCAL show_small_town_data(int x,int y)
{
	GWINDOW win;
	char temp[80];
	int  town_num=ERR;
	int  res;
	static int boundary[]={110,77,145,89,
						   170,77,205,89,
						   -1,-1,-1,-1};

	win.x1=4;
	win.y1=5;
	win.x2=36;
	win.y2=13;
	win.back=0;
	win.border=14;

	town_num=get_town_num(x,y);

	sprintf(temp,"%s:",get_town_details(x,y));
	SCROLL(1,14,temp);
	scroll_wrap_write(1,small_towns[town_num].descrip);

	sprintf(temp,"%sCOA%02d.ICN",
			COA_DIRECTORY,
			small_towns[town_num].coat_of_arms);

	make_gwindow(&win);

	generic_pic_draw(40,50,temp);

	_settextcolor(5);
	_settextposition(win.y1+2,win.x1+8);
	_outtext("Doth thy party enter ye");

	strcpy(temp,get_town_details(x,y));
	strcat(temp,"?");

	_settextposition(win.y1+4,win.x1+19-strlen_half(temp));
	_outtext(temp);

	click_box(110,77,B_YES);
	click_box(170,77,B_NO);

	short_prompt_sound();

	switch(mouse_in_range(boundary,"YN","YQ"))
	{
		case 0 : res=YES; break;
		default: res=NO;  break;
	}

	kill_gwindow(&win);

	return(res);
}

int _PASCAL get_town_num(int x,int y)
{
	int i;
	int town_num=ERR;

	for (i=0; i<MAX_SMALLTOWNS; i++)
		if (x==small_towns[i].x_position && y==small_towns[i].y_position)
			town_num=i;

	return(town_num);
}

char *get_town_details(int x,int y)
{
	static char temp[80];
	int town_num;
	char *type;

	town_num=get_town_num(x,y);

	switch(small_towns[town_num].town_type)
	{
		case TWN_CITY    : type="city";     break;
		case TWN_HAMLET  : type="hamlet";   break;
		case TWN_VILLAGE : type="village";  break;
		case TWN_TOWN    : type="town";     break;
	}

	sprintf(temp,"%s of %s",type,small_towns[town_num].name);

	return(temp);
}

void _PASCAL entering_city_get_taxed()
{
	long int tax_amount;
	char temp[140];

	if (the_party.gc_earned!=0L)
	{
		tax_amount=(the_party.gc_earned/100L)+1L;

		sprintf(temp,"Upon entering Wolfburg, city exciseman take %luGC "
					 "of thy party's treasure in taxes!",
				tax_amount);

		SCROLL(1,0,temp);

		bad_sound();

		pause(5);
	}
}

void _PASCAL quote_on_leaving_town()
{
	char temp[100];
	char town_city[45];
	char day[80];

	if (pent_data.current_feature==CITY)
		strcpy(town_city,"city of wolfburg");
	else
		strcpy(town_city,get_town_details(pent_data.x,pent_data.y));

	if (pent_data.time_hour==7 || pent_data.time_hour==8)
	{
		if (pent_data.degrees_c<=0)
		{
			sprintf(temp,"%s covers ye ground",
					pent_data.rain_level>PRECIP_NONE?"Snow":"A Frost");

			sprintf(day,"Tis daybreak, and %s. ",temp);
		}
		else
			strcpy(day,"Tis daybreak. ");

	}
	else
		strcpy(day,"");

	cls_scroll();

	sprintf(temp,"%sThy party, led by %s, leaves ye %s.",
						 day,
						 TPP[get_first_live_person()].name,
						 town_city);

	scroll_wrap_write(1,temp);
}
