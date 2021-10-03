#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

static GWINDOW spec_win;

void _PASCAL land_on_dungeon_special(int passing_looking)
{
	int l;

	l=the_party.dungeon_level;

	switch(dungeon.nname)
	{
		case DN_LOSTSOUL :  special_lostsoul(l,passing_looking); break;
		case DN_DAMNED   :  special_damned(l,passing_looking);   break;
		case DN_CRYPT    :  special_crypt(l,passing_looking);    break;
		case DN_MORT     :  special_mort(l,passing_looking);     break;
		case DN_MORIBUND :  special_moribund(l,passing_looking); break;
		case DN_HELLS    :  special_hells(l,passing_looking);    break;
		case DN_MISERY   :  special_misery(l,passing_looking);   break;
	}
}

void _PASCAL special_make_gwindow()
{
	char *desc="Closer inspection reveals-";

	spec_win.x1=5;
	spec_win.y1=2;
	spec_win.x2=35;
	spec_win.y2=25;
	spec_win.back=0;
	spec_win.border=2;

	make_gwindow(&spec_win);

	_settextcolor(10);
	_settextposition(spec_win.y1+1,20-strlen_half(desc));
	_outtext(desc);

	click_box(134,172,B_OK);
}

void _PASCAL special_kill_gwindow()
{
	kill_gwindow(&spec_win);
}

void _PASCAL special_wait()
{
	static int boundary[]={134,172,169,184,
							-1,-1,-1,-1};

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");
}

void _PASCAL special_passing_text()
{
	static char *desc[]={"etched into",
						 "carved into",
						 "written on",
						 "cut into",
						 "inscribed in"};

	static char *text[]={"symbols",
						 "shapes",
						 "lettering",
						 "sigils",
						 "wording"};
	int num_d, num_t;
	char temp[80];
	int i=get_random_live_person();

	num_d=rand()%SIZE(desc);
	num_t=rand()%SIZE(text);

	sprintf(temp,"%s notices %s %s ye dungeon wall.",
				TPP[i].name,
				text[num_t],
				desc[num_d]);

	SCROLL(1,1,temp);

	general_low_sound();
}

void _PASCAL special_found_talisman_bit()
{
	int part;
	GWINDOW win;
	static int boundary[]={120,124,155,136,
							-1,-1,-1,-1};
	static char *where[]={"dank",
						  "dark",
						  "dusty",
						  "dirty",
						  "soiled",
						  "filthy"};
	static char temp[150];
	char person[30];
	int i=rand()%SIZE(where);
	static char *lines[]={"Thy party hath found",
						  "a part of ye fabled",
						  "Talisman of Fate!"};

	part=special_update_talisman_details();

	if (part)
	{
		i=get_random_live_person();

		strcpy(person,TPP[i].name);

		sprintf(temp,"IN A %s CORNER OF YE DUNGEON, "
					 "%s NOTICES A SMALL SHINY OBJECT.",
					 where[i],
					 person);

		scroll_scroll();
		SCROLL(1,14,temp);

		good_sound();

		win.x1=6;
		win.y1=5;
		win.x2=30;
		win.y2=19;
		win.back=0;
		win.border=3;

		make_gwindow(&win);

		_settextcolor(5);

		for (i=0; i<SIZE(lines); i++)
		{
			_settextposition(win.y1+1+i,18-strlen_half(lines[i]));
			_outtext(lines[i]);
		}

		draw_talisman_part(118,77,part);

		_setcolor(6);

		_rectangle(_GBORDER,110,71,167,114);
		_rectangle(_GBORDER,109,70,168,115);

		FFPLOT(109,70, 0);
		FFPLOT(109,115,0);
		FFPLOT(168,70, 0);
		FFPLOT(168,115,0);

		FFPLOT(111,72, 6);
		FFPLOT(111,113,6);
		FFPLOT(166,72, 6);
		FFPLOT(166,113,6);

		click_box(120,124,B_OK);

		found_talisman_bit_sound();

		(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

		kill_gwindow(&win);

		add_xp_to_party(3500L);
	}
	else
	{
		tell_talisman_story();
		add_xp_to_party(2000L);
	}
}

int _PASCAL special_update_talisman_details()
{
	int part;

	if (!pent_data.told_about_talisman)
	{
		pent_data.told_about_talisman=TRUE;
		part=0;
	}
	else
	if (!pent_data.talisman_1_found)
	{
		pent_data.talisman_1_found=TRUE;
		part=1;
	}
	else
	if (!pent_data.talisman_2_found)
	{
		pent_data.talisman_2_found=TRUE;
		part=2;
	}
	else
	if (!pent_data.talisman_3_found)
	{
		pent_data.talisman_3_found=TRUE;
		part=3;
	}
	else
	if (!pent_data.talisman_4_found)
	{
		pent_data.talisman_4_found=TRUE;
		part=4;
	}

	return(part);
}

void _PASCAL tell_talisman_story()
{
	GWINDOW win;
	int i;
	char temp[40];
	static int boundary[]={108,170,143,182,
							-1,-1,-1,-1};
	static char *text[]={"A bloodied skull",
						 "forms before thee."};

	static char *story[]={"\"All thy party doth see",
						  "art what remains  of me,",
						  "Gravm–r,  ye  long  dead",
						  "magus of ancient times.\"",
						  "",
						  "\"Scattered about yonder",
						  "vile  dungeons  doth lie",
						  "ye broken  remains  of a",
						  "potent, magic  gem named",
						  "'Ye Talisman of Fate'\"",
						  "",
						  "\"Leave now in haste and",
						  "forgather all four parts",
						  "of ye precious jewel.\""};
	win.x1=3;
	win.y1=1;
	win.x2=30;
	win.y2=25;
	win.back=0;
	win.border=11;

	make_gwindow(&win);

	_settextcolor(4);

	for (i=0; i<SIZE(text); i++)
	{
		_settextposition(win.y1+5+i,16-strlen_half(text[i]));
		_outtext(text[i]);
	}

	draw_eddie_blood_materialise(115,12);

	pause(3);

	_settextcolor(5);

	for (i=0; i<SIZE(story); i++)
	{
		sprintf(temp," %s",story[i]);

		while (strlen(temp)<(size_t)((win.x2-win.x1)-2))
			strcat(temp," ");

		_settextposition(win.y1+5+i,win.x1+1);
		_outtext(temp);
	}

	click_box(108,170,B_OK);

	general_low_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	SCROLL(1,1,"Ye skull fades before thy very eyes...");

	general_low_sound();
}

int _PASCAL display_and_solve_riddle(char **riddle,
									 int riddle_lines,
									 char *answer,
									 char **close,
									 int close_num)
{
	GWINDOW win;
	char temp[40];
	char res_string[80];
	int i;
	int result;
	int fin=FALSE;
	char *talk="A voice from ye skull mutters..";
	char *what="To what doth ye riddle refer?";
	static char *text[]= {"A decaying skull",
						  "forms before thee."};

	static char *lines[]={"\"Thy party must answer a",
						  "    riddle before venturing    ",
						  "a step further!\""};
	win.x1=3;
	win.y1=1;
	win.x2=38;
	win.y2=23;
	win.back=0;
	win.border=11;

	make_gwindow(&win);

	_settextcolor(5);

	for (i=0; i<SIZE(text); i++)
	{
		_settextposition(win.y1+7+i,20-strlen_half(text[i]));
		_outtext(text[i]);
	}

	draw_eddie_blood_materialise(142,12);

	general_low_sound();

	pause(3);

	_settextposition(win.y1+5,20-strlen_half(talk));
	_outtext(talk);

	_settextcolor(4);

	for (i=0; i<SIZE(lines); i++)
	{
		_settextposition(win.y1+7+i,win.x1+1);
		_outtext("                             ");

		_settextposition(win.y1+7+i,20-strlen_half(lines[i]));
		_outtext(lines[i]);
	}

	general_low_sound();

	pause(3);

	_settextcolor(5);

	for (i=0; i<riddle_lines; i++)
	{
		_settextposition(win.y1+11+i,20-strlen_half(riddle[i]));
		_outtext(riddle[i]);
	}

	general_low_sound();

	_settextcolor(4);
	_settextposition(win.y1+17,20-strlen_half(what));
	_outtext(what);

	_settextcolor(2);
	_settextposition(win.y1+19,win.x1+11);
	_outtext("[           ]");

	while (!fin)
	{
		strcpy(temp,gquery(win.x1+12,win.y1+19,10,2,'A',""));

		if (strlen(temp))
			fin=TRUE;
		else
			GX("If ye answer be unclear...take a guess!",BAD);
	}

	if (stricmp(answer,temp)!=0)
	{
		result=FALSE;

		strcpy(res_string,"Thou art Wrong!");

		for (i=0; i<close_num; i++)
		{
			if (stricmp(temp,close[i])==0)
				strcat(res_string," But Close!");
		}
	}
	else
	{
		strcpy(res_string,"Ah, thy party possesses lore in ye riddle game! Ye may pass!");

		add_xp_to_party(2000L);

		result=TRUE;
	}

	kill_gwindow(&win);

	GX(res_string,result==TRUE?GOOD:SOLEMN);

	SCROLL(1,14,"Ye disgusting skull fades away into nothingness...");

	return(result);
}

void _PASCAL got_riddle_wrong(int skull)
{
	SCROLL(1,0,skull?"Ye putrid skull utters some strange words..."
					:"Some strange words art uttered by ye voice...");

	teleport_up_sound();

	init_dungeon_entry();

	draw_all_mapped_dungeon_level(the_party.dungeon_level);

	the_party.dungeon_current_feature=
		draw_dungeon_party(the_party.dungeon_level,
						   the_party.dungeon_x,
						   the_party.dungeon_y);

	teleport_down_sound();

	SCROLL(1,0,"...thy party art teleported back to ye dungeon entrance!");

	dungeon_print_level(the_party.dungeon_level);
}

void _PASCAL depict_dungeon_levels(int x,int y,int num_levels)	 /* x,y of top level */
{
	int i,j,k;
	static int cols[]={15,11,9,1};

	for (i=num_levels-1; i>=0; i--)
		for (j=0; j<8; j++)
			for (k=0; k<23; k++)
				if (dunlayer[j][k])
					FFPLOT(x+k,y+j+(i*5),(char)cols[i]);
}

void _PASCAL read_guild_flyer(int flyer_num)
{
	GWINDOW win;
	char temp[20];
	static int boundary[]={114,167,149,179,
						   -1,-1,-1,-1};

	win.x1=3;
	win.y1=2;
	win.x2=33;
	win.y2=24;
	win.back=0;
	win.border=4;

	SCROLL(1,14,"In ye gloom, thy party spot a sheet of parchment nailed to a dungeon wall!");
	good_sound();

	pause(1);

	if (!someone_in_guild())
	{
		SCROLL(2,0,"Unfortunately a sudden wind carries it away "
				   "into ye inky dungeon blackness!");

		solemn_sound();

		return;
	}

	make_gwindow(&win);

	click_box(114,167,B_OK);

	sprintf(temp,"G_HINT%d",flyer_num);

	generic_pic_draw(win.x1*8+4,win.y1*8-2,temp);

	mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	SCROLL(1,0,"Ye sheet crumbles to dust, no doubt due to age!");
	bad_sound();

	set_to_corridor();
}
