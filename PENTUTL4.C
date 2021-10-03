#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bscreens.h>
#include <bkeybrd.h>

int _PASCAL isvowel(int letter)
{
	letter=toupper(letter);

	if (letter=='A' ||
		letter=='E' ||
		letter=='I' ||
		letter=='O' ||
		letter=='U')
			return(TRUE);
	else
			return(FALSE);
}

void _PASCAL write_little(char *st,int x,int y,int c,int option)
{
	int v,i,j,temp;

	strupr(st);
	_setcolor(c);

	for (i=0; i<(int)strlen(st); i++)
	{
		temp=(int)st[i];

		if (temp==' ')
		{
			if (option==SLOW)
			{
				_setcolor(0);
				_rectangle(_GFILLINTERIOR,x,y,x+2,y+4);
				_setcolor(c);
			}

			x+=4;
			continue;
		}

		if (isalpha(temp))
			v=temp-'A';
		else
		if (isdigit(temp))
			v=(temp-'0')+26;
		else
		switch(temp)
		{
			 case '!' : v=36; break;
			 case '?' : v=37; break;
			 case '.' : v=38; break;
			 case ',' : v=39; break;
			 case '"' : v=40; break;
			 case '(' : v=41; break;
			 case ')' : v=42; break;
			 case ':' : v=43; break;
			 case '~' : v=44; break;
			 case '-' : v=45; break;
			 case '+' : v=46; break;
			 case  39 : v=47; break;
			 default  :       continue;
		}

		v*=5;

		if (option==SLOW)
		{
			_setcolor(0);
			_rectangle(_GFILLINTERIOR,x,y,x+2,y+4);
			_setcolor(c);
		}

		for (j=0; j<5; j++)
		{
			temp=little[v+j];

			if (temp&4)
				FFPLOT(x,y+j,(char)c);

			if (temp&2)
				FFPLOT(x+1,y+j,(char)c);

			if (temp&1)
				FFPLOT(x+2,y+j,(char)c);
		}

		x+=4;
	}
}

void _PASCAL pause(int t)
{
	int i;
	int code;
	char key;

	kbflush();

	for (i=0; i<t*10; i++)
	{
		if (kbready(&key,&code))
		{
			(void)kbgetkey(&code);
			break;
		}

		if (mouse_button_l())
		{
			break;
		}

		delay(t*90);
	}
}

void _PASCAL cmbt_pause(int t)
{
	if (pent_data.combat_speed==CSPEED_FAST)
		return;
	else
	if (pent_data.combat_speed==CSPEED_MED)
		pause(t);
	else
		pause(t*2);
}

void _PASCAL cmbt_half_pause()
{
	if (pent_data.combat_speed==CSPEED_FAST)
		return;
	else
	if (pent_data.combat_speed==CSPEED_MED)
		half_pause();
	else
		pause(1);
}

void _PASCAL half_pause()
{
	int i;
	int code;
	char key;

	kbflush();

	for (i=0; i<5; i++)
	{
		if (kbready(&key,&code))
		{
			(void)kbgetkey(&code);
			break;
		}

		if (mouse_button_l())
			break;

		delay(90);
	}
}

void _PASCAL print_menu_options(char **menu,
								int num,
								char *letters,
								int x,
								int y,
								int col1,
								int col2)
{
	int  i,j;
	char letter[2];

#ifdef DEV
	char temp[40];
#endif

	strupr(letters);

#ifdef DEV

	for (i=0; i<(int)strlen(letters)-1; i++)
		for (j=i+1; j<(int)strlen(letters); j++)
			if (letters[i]==letters[j])
			{
				sprintf(temp,"Non-unique letter %s",letters);
				panic(temp);
			}

	if (num!=(int)strlen(letters))
	{
		sprintf(temp,"Sync error in letters/num");
		panic(temp);
	}

#endif

	for (i=0; i<num; i++)
	{
		_settextcolor(col1);
		_settextposition(y+i,x);

		_outtext(menu[i]);

		for (j=0; j<(int)strlen(menu[i]); j++)
		{
			if ((int)letters[i]==toupper(menu[i][j]))
			{
				_settextcolor(col2);
				_settextposition(y+i,x+j);

				letter[1]='\0';
				letter[0]=menu[i][j];

				_outtext(letter);

				break;
			}
		}
	}
}

char *familiar_type(PLAYER *adv)
{
	static char *temp;

	switch(adv->familiar)
	{
		case FAMILIAR_HAWK  :   temp="Hawk";
								break;

		case FAMILIAR_CAT   :   temp="Cat";
								break;

		case FAMILIAR_RAT   :   temp="Rat";
								break;

		case FAMILIAR_TOAD  :   temp="Toad";
								break;

		case FAMILIAR_FOX   :   temp="Fox";
								break;

		case FAMILIAR_OTTER :   temp="Otter";
								break;

		case FAMILIAR_OWL   :   temp="Owl";
								break;

		case FAMILIAR_RABBIT:   temp="Rabbit";
								break;

		case FAMILIAR_BAT   :   temp="Bat";
								break;

		case FAMILIAR_VIPER :   temp="Viper";
								break;

		default             :   temp="None";
								break;
	}

	return(temp);
}

int _PASCAL distance_between_points(int x1,int y1,int x2,int y2)
{
	return(abs(((x1)-(x2))*((x1)-(x2)) + ((y1)-(y2))*((y1)-(y2))));
}

void _PASCAL make_gplease_wait()
{
	make_gwindow(&please_wait_win);

	print_text("Please Wait..",
			   please_wait_win.x1*8+2,
			   please_wait_win.y1*8+1,
			   NORMAL,
			   15);
}

void _PASCAL kill_gplease_wait()
{
	kill_gwindow(&please_wait_win);
}

char *get_herb_name(int herb_num,int abbrev)
{
	static char *temp;

	switch(herb_num)
	{
		case HERB_EDRAM      : temp="Edram";     break;
		case HERB_MIRENNA	 : temp="Mirenna";	 break;
		case HERB_WYNEWEED	 : temp="Wyneweed";  break;
		case HERB_RUWK       : temp="Ruwk";      break;
		case HERB_LEECHWEED  : temp="Leechweed"; break;
		case HERB_SNOWEED    : temp="Snoweed";   break;
		case HERB_WOLFPETAL  : temp="Wolfpetal"; break;
		case HERB_ICE_NETTLE : temp="Ice Nettle";break;
		case HERB_GYLVIR     : temp="Gylvir";    break;
		case HERB_ANGELSWING : temp=abbrev?"Ang. Wing":"Angel's Wing";break;
		case HERB_BEERBERRY  : temp="Beerberry"; break;
		case HERB_WILDSPRIG  : temp="Wildsprig"; break;
		case HERB_GLOWPETAL  : temp="Glowpetal"; break;
		case HERB_THORNBRIG  : temp="Thornbrig"; break;
		case HERB_PIGWORT    : temp="Pigwort";   break;
		case HERB_ASHLEAF    : temp="Ashleaf";   break;
	}

	return(temp);
}

char *potion_get_colour(int type,int braces)
{
	static char temp[40];

	strcpy(temp,braces?" (":"");

	switch(type)
	{
		case POT_SECRET_DOOR  : strcat(temp,"Saffron");    break;
		case POT_STRENGTH     : strcat(temp,"Azure");      break;
		case POT_STRIKING     : strcat(temp,"Amber");      break;
		case POT_UNDEAD_TURN  : strcat(temp,"Aquamarine"); break;
		case POT_FIRE_RESIST  : strcat(temp,"Ochre");      break;
		case POT_COLD_RESIST  : strcat(temp,"Violet");     break;
		case POT_HEALING      : strcat(temp,"Healing");    break;
		case POT_REVIVING     : strcat(temp,"Reviving");   break;
		case POT_POISON       : strcat(temp,"Poison");     break;
		case POT_HOLYWATER    : strcat(temp,"Holy Water"); break;
		case POT_NOTHING      : strcat(temp,"Sea Green");  break;
		case POT_ALCOHOL      : strcat(temp,"Clear");      break;
		case POT_CURE_DISEASE :
		default               : strcat(temp,"Black");      break;
	}

	if (braces)
		strcat(temp,")");

	return(temp);
}

int _PASCAL number_of_hidden_doors()
{
	int x,y,z,i,j;
	int hidden_door_count=0;
	int SCAN_X=4;
	int SCAN_Y=4;

	z=the_party.dungeon_level;
	x=the_party.dungeon_x;
	y=the_party.dungeon_y;

	for (i=-SCAN_Y; i<SCAN_Y; i++)
		for (j=-SCAN_X; j<SCAN_X; j++)
			if (x+j>=0 && y+i>=0 && x+j<=MAX_DUNGEON_X && y+i<=MAX_DUNGEON_Y)
				if (dungeon.map[z][x+j][y+i].feature==DNG_SECRET_DOOR)
					hidden_door_count++;

	return(hidden_door_count);
}

int _PASCAL party_next_to(int what)
{
	int bit,i;
	static int around[]={-1,-1,
						  0,-1,
						  1,-1,
						  1, 0,
						  1, 1,
						  0, 1,
						 -1, 1,
						 -1, 0,
						  0, 0};

	for (i=0; i<SIZE(around); i+=2)
	{
		bit=map_bit(pent_data.x+around[i],pent_data.y+around[i+1]);

		if (what==TOWN)
		{
			if (bit==TOWN || bit==CITY)
			{
				return(TRUE);
			}
		}
		else
		if (what==DUNGEON)
		{
			if (bit==DUNGEON || bit==RUIN)
			{
				return(TRUE);
			}
		}
		else
			if (bit==what)
				return(TRUE);
	}

	return(FALSE);
}

void _PASCAL set_to_corridor()
{
	int x,y,z;
	int bit;

	x=the_party.dungeon_x;
	y=the_party.dungeon_y;
	z=the_party.dungeon_level;

	bit=dungeon.map[z][x][y].feature;

	if (bit==DNG_SPECIAL || bit==DNG_TRAP || 
            bit==DNG_MONSTER || bit==DNG_VOICE)
	{
		the_party.dungeon_current_feature=DNG_CORRIDOR;
		dungeon.map[z][x][y].feature=DNG_CORRIDOR;
	}
}
