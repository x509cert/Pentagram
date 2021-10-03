#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include "mmalloc.h"

static char _FAR  *rest_im_hg[NUM_HG_IMAGES];
static char _FAR  *rest_im_hgframe;

void _PASCAL attempt_to_rest()
{
	int hours,mins;

	adv_get_rest_time(&hours, &mins);

	if (hours || mins)
		actually_rest(hours,mins);
	else
	{
		SCROLL(1,0,"Thy party chooses not to rest..");

		general_low_sound();
	}
}

void _PASCAL adv_get_rest_time(int *hr,int *mi)
{
	char temp[20];
	GWINDOW win;
	int fin=FALSE;
	int h,m;
	int till_daybreak=FALSE;
	char *line1="Rest for how long?";
	static int boundary[]={125,81,135,90,
						   137,81,147,90,
						   165,81,174,90,
						   177,81,186,90,
						   140,95,175,107,
							-1,-1,-1,-1};
	h=0;
	m=0;

	if (is_night_time())
		till_daybreak=gget_yn("Rest until daybreak?");

	if (!till_daybreak)
	{
		win.x1=10;
		win.y1=5;
		win.x2=30;
		win.y2=15;
		win.back=0;
		win.border=4;

		make_gwindow(&win);

		_settextcolor(14);
		_settextposition(win.y1+1,20-strlen_half(line1));
		_outtext(line1);

		click_box(140,95,B_FINISH);

		print_up_down(125,81);
		print_left_right(165,81);

		_setcolor(6);
		_rectangle(_GBORDER,117,60,192,74);
		_rectangle(_GBORDER,116,59,193,75);
		_rectangle(_GBORDER,155,59,156,75);

		write_little("HOURS",125,52,15,FAST);
		write_little("MINS",168,52,15,FAST);

		fast_mouse=ON;

		while (!fin)
		{
			sprintf(temp,"%02d",h);
			_settextposition(win.y1+4,win.x1+7);
			_outtext(temp);

			sprintf(temp,"%02d",m);
			_settextposition(win.y1+4,win.x1+12);
			_outtext(temp);

			switch(mouse_in_range(boundary,"\xD0\xC8\xCB\xCD\x20","\xD0\xC8\xCB\xCD\x51"))
			{
				case 0 : h--;       break;
				case 1 : h++;       break;
				case 2 : m-=30;     break;
				case 3 : m+=30;     break;
				default: fin=TRUE;  break;
			}

			if (m>59)
			{
				m=0;
				h++;
			}

			if (m<0)
			{
				m=30;
				h--;
			}

			if (h>23)
				h=0;

			if (h<0)
				h=23;

			if (mouse_installed)
				delay(25);
		}

		fast_mouse=OFF;

		kill_gwindow(&win);
	}
	else
	{
		if (pent_data.time_hour<=24 && pent_data.time_hour>19)
			h=7+(24-pent_data.time_hour);
		else
			h=7-pent_data.time_hour;

		m=30;
	}

	*hr=h;
	*mi=m;
}

void _PASCAL rest_light_fire()
{
	int res=FALSE;
	int ok_to_light=ERR;
	int i;
	char temp[80];
	GWINDOW win;
	char *t="Dost thou light a fire?";
	static int boundary[]={100,90,135,102,
						   165,90,200,102,
							-1,-1,-1,-1};

	win.x1=7;
	win.y1=6;
	win.x2=33;
	win.y2=15;
	win.back=0;
	win.border=4;

	the_party.fire_lit=FALSE;

	make_gwindow(&win);

	generic_pic_draw(140,win.y1*8,"CAMPFIRE");

	_settextposition(win.y1+4,20-strlen_half(t));
	_settextcolor(14);
	_outtext(t);

	click_box(100,90,B_YES);
	click_box(165,90,B_NO);

	res=mouse_in_range(boundary,"YN","YQ");

	kill_gwindow(&win);

	if (res==0)
	{
		for (i=0; i<=P_NUM; i++)
			if (player_is_carrying(&TPP[i],TINDER_BOX) && player_is_alive(&TPP[i]))
				ok_to_light=i;

		if (ok_to_light!=ERR)
		{
			sprintf(temp,"After a few moments, %s lights a roaring fire..",
						 TPP[ok_to_light].name);
			SCROLL(1,14,temp);
			good_sound();

			the_party.fire_lit=TRUE;
		}
		else
		{
			SCROLL(1,0,"No-one has a tinderbox!");
			bad_sound();
		}
	}
	else
	{
		SCROLL(1,0,"Ye choose not to light a fire!");
		general_low_sound();
	}
}

void _PASCAL actually_rest(int hours, int minutes)
{
	int i,j;
	int rest_units;
	int interrupt_this_unit=FALSE;
	char temp[80];
	int old_time, new_time;
	GWINDOW win;

	rest_units=hours*2;

	if (minutes==30)
		rest_units++;

	the_party.resting=TRUE;

	rest_bed_down_message();

	if (!IN_DUNGEON)
		rest_light_fire();

	rest_hg_load_all_images();

	win.x1=21;
	win.y1=5;
	win.x2=32;
	win.y2=15;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_text("Resting",177,38,NORMAL_HEIGHT,6);
	print_text("..zzzZZZ!",168,88,NORMAL_HEIGHT,6);

	for (i=0; i<rest_units && !interrupt_this_unit; i++)
	{
		if (i%4==0) 								/* Only every 2 hours! */
			if (hours>=4)							/* Need to rest at	*/
				for (j=0; j<=P_NUM; j++)			/* least 4 hours to */
					actually_rest_one_adv(&TPP[j]); /* to benefit       */

		if (i%2==0)
		{
			interrupt_this_unit=interrupt_rest();

			if (!interrupt_this_unit)
			{
				rest_animate_hourglass(192,51);

				sprintf(temp,"Hour %d",i/2+1);
				_settextcolor(6);
				_settextposition(11,(i/2+1)>9?23:24);
				_outtext(temp);

				_settextposition(12,22);
				_outtext("passes by");
				_settextposition(13,23);
				_outtext("quietly");

				delay(180);
			}
		}

		old_time=is_night_time();

		pent_data.time_minute+=30;

		day_night();

		new_time=is_night_time();

		update_in_effects();
		update_in_effects();
		update_in_effects();

		if (!IN_DUNGEON)
		{
			if (old_time!=new_time)
			{
				night_flagged=FALSE;

				if (is_night_time())
					draw_night_map();
				else
					draw_first_map();
			}
		}
	}

	kill_gwindow(&win);
	rest_hg_free_all_images();

	the_party.resting=FALSE;

	if (interrupt_this_unit)
	{
		if (!pent_data.finished)
		{
			GX("Thy slumber art disturbed!",SOLEMN);
			combat(WANDERING_MONSTER);
		}
	}
	else
	{
		rest_get_up_message();
	}
}

void _PASCAL actually_rest_one_adv(PLAYER *adv)
{
	int hp_healed;                                           /* Update HP */

	if (player_is_dead(adv))
		return;

	hp_healed=effective_heal_rate(adv);

	adv->current_hp+=hp_healed;

	if (adv->current_hp > adv->hp)
		adv->current_hp=adv->hp;

	if (adv->points_cast)									 /* Update Spell Drain */
		adv->points_cast--;

	if (adv->current_sorcery_points < adv->sorcery_points)   /* Update Sorcery Pts */
	{
		if (player_is_carrying(adv,RELIC))
			adv->current_sorcery_points++;
		else
		if (percent()<=effective_luck(adv)*2)
			adv->current_sorcery_points++;
	}

	if (adv->current_divine_points < adv->divine_points)     /* Update Sorcery Pts */
	{
		if (player_is_carrying(adv,TOME))
			adv->current_divine_points++;
		else
		if (percent()<=effective_luck(adv)*2)
			adv->current_divine_points++;
	}

	adv->drunkeness=max(adv->drunkeness-1,0);                /* Update drunkeness! */
}

void _PASCAL rest_bed_down_message()
{
	int i;
	char temp[120];
	static struct {
						int  feature;
						char *location1;

				  } loc[]={
						   {PATH        , "by ye wayside"},
						   {GRASS       , "in a small dell"},
						   {TOWN        , "in ye towns shadow"},
						   {SIGNPOST    , "next to ye signpost"},
						   {HILLS       , "in a cairn of rocks"},
						   {BRIDGE_UD   , "by ye bridge"},
						   {BRIDGE_LR   , "next to ye bridge"},
						   {MOUNTAINS   , "by some huge boulders"},
						   {FOREST      , "under an ancient tree"},
						   {MARSH       , "in a dry patch of marsh"},
						   {CELTIC_CROSS, "by ye cross"},
						   {DUNGEON     , "by ye dungeon entrance"},
						   {RUIN        , "next to ye ruin"},
						   {CITY        , "against ye city walls"}
						  };

	static char *lie_down[]={"lies down",
							 "makes camp",
							 "rests"};

	if (IN_DUNGEON)
	{
		strcpy(temp,"Thy party rests in ye dungeon gloom.");
	}
	else
	{
		for (i=0; i<SIZE(loc); i++)
		{
			if (pent_data.current_feature==loc[i].feature)
			{
				sprintf(temp,"Thy party %s %s.",
							 lie_down[rand()%SIZE(lie_down)],
							 loc[i].location1);

				break;
			}
		}
	}

	SCROLL(1,14,temp);
	scroll_scroll();
	good_sound();
}

void _PASCAL rest_get_up_message()
{
	char temp[120];
	char time[30];
	int person=get_random_live_person();
	static char *awake[]={"wakes up",
						  "awakes",
						  "stirs"};

	strcpy(time,get_time_string(pent_data.time_hour,pent_data.time_minute));

	sprintf(temp,"It is %s and %s %s ye party!",
			time,
			TPP[person].name,
			awake[rand()%3]);

	SCROLL(1,14,temp);

	wake_up_sound();

	the_party.fire_lit=FALSE;
}

int _PASCAL interrupt_rest()
{
	int i, total_luck=0;
	int chance_of_encounter;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			total_luck+=effective_luck(&TPP[i]);

	if (percent()<=total_luck)
		chance_of_encounter=5;
	else
		chance_of_encounter=10;

	if (IN_DUNGEON || party_next_to(DUNGEON))
		chance_of_encounter+=10;

	if (the_party.fire_lit)
		chance_of_encounter+=10;

	if (party_next_to(TOWN))
		chance_of_encounter=0;

	if (check_party_globals_in_effect(IN_EFFECT_MIRAGE))
		chance_of_encounter=0;

	return(percent()<=chance_of_encounter?TRUE:FALSE);
}

void _PASCAL rest_animate_hourglass(int x,int y)
{
	int i;

	for (i=0; i<NUM_HG_IMAGES; i++)
	{
		rest_update_hourglass(x,y,i);
		rest_trickle_sand(x,y,i);
	}

	rest_update_hourglass(x,y,4);
}

void _PASCAL rest_hg_load_all_images()
{
	char temp[40];
	int size_hg=180;
	int size_fr=300;
	FILE *fptr;
	int i;

	for (i=0; i<NUM_HG_IMAGES; i++)
	{
		rest_im_hg[i]=(char _FAR *)Mmalloc((size_t)size_hg);

		if (rest_im_hg[i]==NULL)
			panic_RAM("Hourglass");

		sprintf(temp,"%sHG%d.PIC",HOURGLASS_DIRECTORY,i+1);

		fptr=fopen(temp,"rb");

		if (fptr==NULL)
			panic_FILE(temp);

		fread((void *)rest_im_hg[i],size_hg,1,fptr);

		fclose(fptr);
	}

	rest_im_hgframe=(char _FAR *)Mmalloc((size_t)size_fr);

	if (rest_im_hgframe==NULL)
		panic_RAM("Hourglass");

	sprintf(temp,"%sHG_FRAME.PIC",HOURGLASS_DIRECTORY);

	fptr=fopen(temp,"rb");

	if (fptr==NULL)
		panic_FILE(temp);

	fread((void *)rest_im_hgframe,size_fr,1,fptr);

	fclose(fptr);
}

void _PASCAL rest_hg_free_all_images()
{
	int i;

	for (i=0; i<NUM_HG_IMAGES; i++)
		Mfree((void *)rest_im_hg[i]);

	Mfree((void *)rest_im_hgframe);
}

void _PASCAL rest_draw_hourglass_frame(int x,int y)
{
	_putimage(x,y,rest_im_hgframe,_GPSET);
}

void _PASCAL rest_update_hourglass(int x,int y,int num)
{
	if (!num)
		rest_draw_hourglass_frame(x,y);

	x+=6;
	y+=2;

	_putimage(x,y,rest_im_hg[num],_GPSET);
}

void _PASCAL rest_trickle_sand(int x,int y,int num)
{
	int i,j,extra;

	switch(num)
	{
		case 0 : extra=4;  break;
		case 1 : extra=2;  break;
		case 2 : extra=1;  break;
		case 4 : extra=-1; break;
		default: extra=0;
	}

	for (i=0; i<26; i++)
	{
		for (j=0; j<6+extra; j++)
			FFPLOT(x+11,
				   y+j+12,
				   (char)((i+j)%3?0:14));

		delay(7);
	}
}
