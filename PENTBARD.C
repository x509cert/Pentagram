#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

int _PASCAL use_lute(PLAYER *adv)
{
	static char temp[140];

	if ((pent_data.current_feature==SEA   ||
		pent_data.current_feature==WATER) &&
		check_party_globals_in_effect(IN_EFFECT_WALK_ON_WATER)==ERR)
	{
		GX("Have you ever played a lute whilst swimming? Forget it!",BAD);
		return(FALSE);
	}

	if (adv->nclass!=BARD)
	{
		if (IN_COMBAT)
		{
			cmbt_bad_msg("Thou art no bard!",TRUE);
			pause(1);

			return(FALSE);
		}

		sprintf(temp,"AFTER A FEW CHORDS ON %s LUTE, %s REALISES THAT MUSIC ART FOR YE BARDS!",
					 adv->his_her,
					 adv->name);

		SCROLL(1,0,temp);
		bad_sound();

		return(TRUE);
	}
	else
		select_song_to_sing(adv);

	return(TRUE);
}

void _PASCAL select_song_to_sing(PLAYER *adv)
{
	GWINDOW win;
	char temp[80];
	char *t2="SWTAYPDH";
	char *t3="SWTAYPDHQ";
	int len;
	static char *songs[]={"Stop Singing",
						  "Windsong",
						  "Wayfarers Tune",
						  "Alethran",
						  "Tale of Yuldar",
						  "Palisor's Dream",
						  "Daylight Falls",
						  "Hunter's Poem"
						 };
	int select;
	int fin;
	int y;
	static int boundary[]={32, 56,162, 62,
						   32, 64,162, 70,
						   32, 72,162, 78,
						   32, 80,162, 86,
						   32, 88,162, 94,
						   32, 96,162,102,
						   32,104,162,110,
						   32,112,162,118,
						   76,126,111,138,
							-1,-1,-1,-1};

	if (adv->bard_songs_sung>=bard_max_songs(adv))
	{
		sprintf(temp,"%s must rest a while due to a sore throat!",adv->name);
		GX(temp,BAD);

		return;
	}

	win.x1=3;
	win.y1=6;
	win.x2=22;
	win.y2=win.y1+5+SIZE(songs);
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(songs,
					   SIZE(songs),
					   t2,
					   win.x1+2,win.y1+2,
					   5,
					   13);

	click_box(76,126,B_QUIT);

	_settextposition(win.y1+1,win.x1+2);
	_settextcolor(6);
	_outtext("Sing which Song?");

	y=56;

	if (adv->in_effect.windsong)
		y=64;

	if (adv->in_effect.wayfarers_tune)
		y=72;

	if (adv->in_effect.alethran)
		y=80;

	if (adv->in_effect.tale_of_yuldar)
		y=88;

	if (adv->in_effect.palisors_dream)
		y=96;

	if (adv->in_effect.daylight_falls)
		y=104;

	if (adv->in_effect.hunters_poem)
		y=112;

	tick(win.x1*8-3,y,ON);

	fin=FALSE;

	general_low_sound();

	while (!fin)
	{
		select=mouse_in_range(boundary,t3,"");

		if (select==8)
			fin=TRUE;

		if (select!=8)
		{
			len=get_song_duration(adv);

			nullify_all_songs(adv);

			switch(select)
			{
				case 0 :    break;

				case 1 :	adv->in_effect.windsong=len;
							break;

				case 2 :    adv->in_effect.wayfarers_tune=len;
							break;

				case 3 :    adv->in_effect.alethran=len;
							break;

				case 4 :    adv->in_effect.tale_of_yuldar=len;
							break;

				case 5 :    adv->in_effect.palisors_dream=len;
							break;

				case 6 :    adv->in_effect.daylight_falls=len;
							break;

				case 7 :    adv->in_effect.hunters_poem=len;
							break;
			}

			adv->bard_songs_sung++;

			fin=TRUE;
		}
	}

	kill_gwindow(&win);

	if (select!=8 && select!=0)
	{
		if (IN_COMBAT)
		{
			sprintf(temp,"%s sings %s.",adv->name,songs[select]);
			combat_write(11,temp,TRUE);
		}
		else
		{
			sprintf(temp,"%s begins to play %s on %s lute.",
						 adv->name,
						 songs[select],
						 adv->his_her);

			SCROLL(1,14,temp);
		}

		lute_sound();
	}
}

int _PASCAL bard_max_songs(PLAYER *adv)
{
	return(adv->level+2);
}

int _PASCAL get_song_duration(PLAYER *adv)
{
	return(adv->level*5);
}

int _PASCAL bard_is_singing(PLAYER *adv,char *msg)
{
	char line1[60];
	char line2[60];
	GWINDOW win;
	int res;
	static int boundary[]={100,60,135,72,
						   175,60,250,72,
						   -1,-1,-1,-1};

	if (adv->nclass!=BARD)
		res=0;
	else
		res=adv->in_effect.windsong 	 +
			adv->in_effect.wayfarers_tune+
			adv->in_effect.alethran 	 +
			adv->in_effect.tale_of_yuldar+
			adv->in_effect.palisors_dream+
			adv->in_effect.daylight_falls+
			adv->in_effect.hunters_poem;

	if (res)
	{
		sprintf(line1,"Dost %s stop singing",adv->name);
		sprintf(line2,"so %s may %s?",adv->he_she,msg);

		if (strlen(line1)>=strlen(line2))
		{
			win.x1=19-strlen_half(line1);
			win.x2=22+strlen_half(line1);
		}
		else
		{
			win.x1=19-strlen_half(line2);
			win.x2=22+strlen_half(line2);
		}

		win.y1=4;
		win.y2=11;
		win.border=5;
		win.back=0;

		make_gwindow(&win);

		_settextposition(win.y1+1,20-strlen_half(line1));
		_settextcolor(4);
		_outtext(line1);

		_settextposition(win.y1+2,20-strlen_half(line2));
		_outtext(line2);

		click_box(100,60,B_YES);
		click_box(175,60,B_NO);

		general_low_sound();

		if (mouse_in_range(boundary,"YN","YQ")==0)
		{
			res=FALSE;

			nullify_all_songs(adv);
		}

		kill_gwindow(&win);
	}

	return(res?TRUE:FALSE);
}
