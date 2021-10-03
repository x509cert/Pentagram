#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <butil.h>
#include <bstrings.h>

void _PASCAL market()
{
	GWINDOW win, win_top;
	static char *t[]={"Armourer",
					  "Black Smith",
					  "Magic Shoppe",
					  "Spell-Users Guild",
					  "General Store",
					  "Leave ye Market"};
	char *t2="ABMSGL";
	int fin=FALSE;
	char temp[35];
	static int boundary[]={88,48,224,54,
						   88,56,224,62,
						   88,64,224,70,
						   88,72,224,78,
						   88,80,224,86,
						   88,88,224,94,
						   -1,-1,-1,-1};

	if (check_today_is_sunday_msg("Market"))
		return;

	if (is_night_time())
	{
		GX("Alas! Ye Market art closed. Try again tomorrow morning!",SOLEMN);
		return;
	}

	in_spell_section=FALSE;

	print_large_title("AT YE MARKETS");

	if (who_is_going("Who enters ye Markets?")==ERR)
		return;

	if (player_is_dead(&adv))
	{
		sprintf(temp,"%s art dead!",adv.name);
		GX(temp,BAD);
		return;
	}

	if (player_is_drunk(&adv))
	{
		player_is_drunk_so_leave(&adv,"Markets");
		return;
	}

	win.x1=11;
	win.y1=6;
	win.x2=30;
	win.y2=14;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,win.y1+1,
					   5,
					   13);

	while (!fin)
	{
		market_put_person_details(&win_top);

		switch(mouse_in_range(boundary,t2,"ABMSGQ"))
		{
			case 0 :    kill_gwindow(&win_top);
						market_armourer();
						break;

			case 1 :    kill_gwindow(&win_top);
						market_black_smith();
						break;

			case 2 :    kill_gwindow(&win_top);
						market_magic_shoppe();
						break;

			case 3 :    kill_gwindow(&win_top);
						market_spell_guild();
						break;

			case 4 :    kill_gwindow(&win_top);
						market_general_store();
						break;

			case 5 :    kill_gwindow(&win_top);
						fin=TRUE;
						break;

			default:    break;
		}
	}

	save_adventurer(&adv);

	kill_gwindow(&win);
}

void _PASCAL market_put_person_details(GWINDOW *win_top)
{
	char person[80];
	char spell_s[70];
	char *little;
	int longest;
	int cl=adv.nclass;
	int l1=adv.learn_wiz1_spells+adv.learn_ill1_spells+
		   adv.learn_pri1_spells+adv.learn_dru1_spells;

	int l2=adv.learn_wiz2_spells+adv.learn_ill2_spells+
		   adv.learn_pri2_spells+adv.learn_dru2_spells;

	int l3=adv.learn_wiz3_spells+adv.learn_ill3_spells+
		   adv.learn_pri3_spells+adv.learn_dru3_spells;

	switch(cl)
	{
		case WARRIOR        : cl=FALSE;     break;
		case PRIEST         : cl=TRUE ;     break;
		case WIZARD         : cl=TRUE ;     break;
		case DRUID          : cl=TRUE ;     break;
		case THIEF          : cl=FALSE;     break;
		case RANGER         : cl=TRUE ;     break;
		case CRUSADER       : cl=TRUE ;     break;
		case BARD           : cl=TRUE ;     break;
		case MONK           : cl=TRUE ;     break;
		case ILLUSIONIST    : cl=TRUE ;     break;
		case HUNTER         : cl=TRUE ;     break;
		case DUELIST        : cl=FALSE;     break;
	}

	if (cl)
	{
		if (adv.learn_wiz1_spells+adv.learn_wiz2_spells+adv.learn_wiz3_spells+
			adv.learn_ill1_spells+adv.learn_ill2_spells+adv.learn_ill3_spells+
			adv.learn_pri1_spells+adv.learn_pri2_spells+adv.learn_pri3_spells+
			adv.learn_dru1_spells+adv.learn_dru2_spells+adv.learn_dru3_spells<=0)
				strcpy(spell_s,"Thou canst learn no more spells!");
		else
		{
			strcpy(spell_s,"Ye may learn more spells-");

			if (l1)
				little="1st";

			if (l2)
				little="2nd";

			if (l3)
				little="3rd";

			if (l1 && l2)
				little="1st & 2nd";

			if (l1 && l3)
				little="1st & 3rd";

			if (l2 && l3)
				little="2nd & 3rd";

			if (l1 && l2 && l3)
				little="1st 2nd 3rd";

			strcat(spell_s,little);
		}
	}

	if (adv.cash==0L)
		sprintf(person,"%s hath no cash!",adv.name);
	else
		sprintf(person,"%s hath %lu GC",adv.name,adv.cash);

	if (in_spell_section)
		longest=max(strlen(person),strlen(spell_s));
	else
		longest=(int)strlen(person);

	longest/=2;

	win_top->x1=19-longest;
	win_top->y1=in_spell_section?(cl?21:22):22;
	win_top->x2=22+longest;
	win_top->y2=win_top->y1+(in_spell_section?(cl?4:3):3);
	win_top->back=0;
	win_top->border=7;

	make_gwindow(win_top);

	_settextposition(win_top->y1+1,20-strlen_half(person));
	_settextcolor(9);
	_outtext(person);

	if (cl && in_spell_section)
	{
		_settextposition(win_top->y1+2,20-strlen_half(spell_s));
		_settextcolor(9);
		_outtext(spell_s);
	}
}

void _PASCAL not_powerful_enough(int class,int level)
{
	char temp[80];
	char *lev, *cl;

	switch(level)
	{
		case 2 :  lev="2nd"; break;
		case 3 :  lev="3rd"; break;
	}

	switch(class)
	{
		case WIZARD     : cl="Wizard";      break;
		case ILLUSIONIST: cl="Illusionist"; break;
		case DRUID      : cl="Druid";       break;
		case PRIEST     : cl="Priest";      break;
	}

	sprintf(temp,"Thou are not powerful enough to cast %s level %s spells!",lev,cl);

	GX(temp,BAD);
}

void _PASCAL cannot_learn_more(int class,int level)
{
	char temp[80];
	char *lev, *cl;

	switch(level)
	{
		case 1 : lev="1st"; break;
		case 2 : lev="2nd"; break;
		case 3 : lev="3rd"; break;
	}

	switch(class)
	{
		case WIZARD     : cl="Wizard";      break;
		case ILLUSIONIST: cl="Illusionist"; break;
		case DRUID      : cl="Druid";       break;
		case PRIEST     : cl="Priest";      break;
	}

	sprintf(temp,"Thou canst learn no more %s level %s spells!",lev,cl);

	GX(temp,BAD);
}

void _PASCAL class_cannot_use(int class, char *mess)
{
	char temp[80];
	char *cl;

	switch(class)
	{
		case WARRIOR		:	cl="Warriors";
								break;

		case PRIEST 		:	cl="Priests";
								break;

		case RANGER 		:	cl="Rangers";
								break;

		case DRUID			:	cl="Druids";
								break;

		case THIEF			:	cl="Thieves";
								break;

		case WIZARD 		:	cl="Wizards";
								break;

		case BARD			:	cl="Bards";
								break;

		case MONK			:	cl="Monks";
								break;

		case ILLUSIONIST	:	cl="Illusionists";
								break;

		case HUNTER 		:	cl="Hunters";
								break;

		case DUELIST		:	cl="Duelists";
								break;

		case CRUSADER		:	cl="Crusaders";
								break;
	}

	sprintf(temp,"%s can't use %s",cl,mess);

	GX(temp,BAD);
}

void _PASCAL too_weak_to_use(char *person,char *mess)
{
	char temp[80];

	sprintf(temp,"%s art too weak to use %s",
			person,
			mess);

	GX(temp,BAD);
}

void _PASCAL race_cannot_use(int class, char *mess)
{
	char temp[80];
	char *dont;
	char *ra;

	switch(rand()%3)
	{
		case 0  : dont="short";  break;
		case 1  : dont="small";  break;
		default : dont="little"; break;
	}

	switch(class)
	{
		case DWARF	   :   ra="Dwarves";   break;
		case HALFLING  :   ra="Halflings"; break;
		case GNOME	   :   ra="Gnomes";    break;
	}

	sprintf(temp,"%s are too %s to use a %s",ra,dont,mess);

	GX(temp,BAD);
}

int _PASCAL got_enough_money(unsigned long amount,PLAYER *player)
{
	char temp[80];

	if ((number_of_items(player)>=MAX_CARRY) && (!in_spell_section))
	{
		carry_no_more(player);
		return(FALSE);
	}

	if (player->cash<amount)
	{
		if (player->cash==0L)
			sprintf(temp,"%s hast no money!",player->name);
		else
			sprintf(temp,"%s hath only %lu GC in cash!",player->name,player->cash);

		GX(temp,BAD);

		return(FALSE);
	}
	else
	{
		player->cash-=amount;
		return(TRUE);
	}
}

int _PASCAL got_enough_money_not_inv(unsigned long amount,PLAYER *player)
{
	char temp[80];

	if (player->cash<amount)
	{
		if (player->cash==0L)
			sprintf(temp,"%s hast no money!",player->name);
		else
			sprintf(temp,"%s hath only %lu GC in cash!",player->name,player->cash);

		GX(temp,BAD);

		return(FALSE);
	}
	else
	{
		player->cash-=amount;
		return(TRUE);
	}
}

int _PASCAL got_enough_money_for_misc(unsigned long amount,PLAYER *player)
{
	char temp[80];

	if (player->cash<amount)
	{
		if (player->cash==0L)
			sprintf(temp,"%s hast no money!",player->name);
		else
			sprintf(temp,"%s hath only %lu GC in cash!",player->name,player->cash);

		GX(temp,BAD);

		return(FALSE);
	}
	else
	{
		player->cash-=amount;
		return(TRUE);
	}
}

void _PASCAL thank_you()
{
	static char *th[]={"Just what ye need!",
					   "Just what ye require.",
					   " Thank you ",
					   "A Fine choice indeed!",
					   "Done!",
					   "A Fine choice!"};

	GWINDOW win;
	char text[80];
	int i;
	static int boundary[]={137,68,172,80,
						   -1,-1,-1,-1};

	i=rand()%6;

	strcpy(text,th[i]);

	if (strlen(text)<10)
	{
		win.x1=15;
		win.x2=25;
	}
	else
	{
		win.x1=19-strlen_half(text);
		win.x2=22+strlen_half(text);
	}

	win.y1=6;
	win.y2=12;
	win.border=11;
	win.back=0;

	make_gwindow(&win);

	_settextposition(win.y1+1,20-strlen_half(text));
	_settextcolor(4);
	_outtext(text);

	click_box(137,68,B_OK);

	if (!NO_SOUND)
	{
		utspkr(1200);
		delay(70);
		utspkr(2100);
		delay(70);
		utspkr(0);
	}

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

void _PASCAL dungeon_warfare_act( char *item,int max_allowed)
{
	char line2[80], line3[80];
	char *line4="So that's all ye get!";
	int longest=0;
	GWINDOW win;
	static int boundary[]={144,100,180,112,
						   -1,-1,-1,-1};

	static char *ac[]={{"Section 42 of ye Dungeon Warfare"},
					   {"Act stipulates that \"An adventurer"},
					   {"shall possess no more than %d"},
					   {"%s at any particular time.\""}};

	if (max_allowed==MAX_FOOD)                 /* Food */
	{
		sprintf(line2,"shall possess no more than %d lots",max_allowed);
		sprintf(line3,"of %s at any particular time.\"",item);
	}
	else
	{
		sprintf(line2,ac[2],max_allowed);
		sprintf(line3,ac[3],item);
	}

	longest=max(strlen(ac[0]),strlen(ac[1]));
	longest=max((int)strlen(line2),longest);
	longest=max((int)strlen(line3),longest);

	win.x1=19-longest/2;
	win.x2=22+longest/2;
	win.y1=5;
	win.y2=17;
	win.back=0;
	win.border=9;

	make_gwindow(&win);

	_settextcolor(6);

	_settextposition(win.y1+1,20-strlen_half(ac[0]));
	_outtext(ac[0]);

	_settextposition(win.y1+2,20-strlen_half(ac[1]));
	_outtext(ac[1]);

	_settextposition(win.y1+3,20-strlen_half(line2));
	_outtext(line2);

	_settextposition(win.y1+4,20-strlen_half(line3));
	_outtext(line3);

	_settextcolor(14);
	_settextposition(win.y1+6,20-strlen_half(line4));
	_outtext(line4);

	click_box(144,100,B_OK);

	bad_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

int  _PASCAL market_get_quantity( char *item,int num_item,int max_allowed)
{
	char temp[80];
	GWINDOW win;
	int num;
	char *pic="[   ]";

	if (num_item>max_allowed)
	{
		if (max_allowed==MAX_FOOD)                        /* Food */
			sprintf(temp,"Thou hath %d lots of %s already!",num_item,item);
		else
			sprintf(temp,"Thou hath %d %s already!",num_item,item);

		GX(temp,BAD);
		return(ERR);
	}

	win.x1=2;
	win.y1=5;
	win.x2=38;
	win.y2=11;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(7);

	if (max_allowed==MAX_FOOD)                            /* Food or */
		sprintf(temp,"How much %s dost thou want?",item);
	else
		sprintf(temp,"How many %s dost thou want?",item);

	_settextposition(win.y1+1,20-strlen_half(temp));
	_outtext(temp);

	if (num_item)
	{
		if (max_allowed==MAX_FOOD)                        /* Food */
			sprintf(temp,"Thou hast %d lots already!",num_item);
		else
			sprintf(temp,"Thou hast %d already!",num_item);
	}
	else
		strcpy(temp,"Thou hast none at present");

	_settextposition(win.y1+2,20-strlen_half(temp));
	_outtext(temp);

	_settextposition(win.y1+4,18);
	_outtext(pic);

	strcpy(temp,gquery(19,win.y1+4,2,2,'N',""));

	kill_gwindow(&win);

	num=atoi(temp);

	if (num_item+num>max_allowed)
	{
		dungeon_warfare_act(item,max_allowed);
		return(max_allowed-num_item);
	}

	return(strlen(temp)?num:0);
}

int _PASCAL market_get_item_plus(int base_price,  char *item, unsigned long *pay)
{
	GWINDOW win;
	char temp[80];
	char temp1[20];
	int i,j;
	long price;
	char *dont="Don't Buy";
	char *t2="?123U";
	char *t1="?123Q";
	int index;
	static int boundary[]={40,32,200,38,
						   40,40,200,46,
						   40,48,200,54,
						   40,56,200,62,
						   40,64,200,70,
						   -1,-1,-1,-1};

	j=strlen(dont);

	t2[0]=item[0];
	t1[0]=item[0];

	for (i=0; i<4; i++)
	{
		switch(i)
		{
			case 1 : price=(long)base_price*PLUS_1_COST; break;
			case 2 : price=(long)base_price*PLUS_2_COST; break;
			case 3 : price=(long)base_price*PLUS_3_COST; break;
			default: price=(long)base_price;             break;
		}

		if (i)
			sprintf(temp,"%s +%d (%lu)",item,i,price);
		else
			sprintf(temp,"%s (%lu)",item,price);

		j=max(j,(int)strlen(temp));
	}

	win.x1=5;
	win.y1=4;
	win.x2=win.x1+j+2;
	win.y2=win.y1+7;
	win.back=0;
	win.border=8;

	make_gwindow(&win);

	for (i=0; i<4; i++)
	{
		switch(i)
		{
			case 0 : price=(long)base_price;             break;
			case 1 : price=(long)base_price*PLUS_1_COST; break;
			case 2 : price=(long)base_price*PLUS_2_COST; break;
			case 3 : price=(long)base_price*PLUS_3_COST; break;
		}

		sprintf(temp1,"(%lu)",price);

		if (i)
			sprintf(temp,"%s +%d ",item,i);
		else
			sprintf(temp,"%s ",item);

		while ((strlen(temp)+strlen(temp1))<(size_t)j)
			strcat(temp," ");

		strcat(temp,temp1);

		_settextposition(win.y1+1+i,win.x1+1);
		_settextcolor(5);
		_outtext(temp);

		index=stschind(t2[i],temp);

		if (index!=ERR)
		{
			temp[1]='\0';
			temp[0]=t2[i];

			_settextcolor(13);
			_settextposition(win.y1+1+i,win.x1+1+index);
			_outtext(temp);
		}
	}

	boundary[2]=
	boundary[6]=
	boundary[10]=
	boundary[14]=
	boundary[18]= win.x2*8-16;


	_settextcolor(5);
	_settextposition(win.y1+5, win.x1+1);
	_outtext(dont);

	_settextcolor(13);
	_settextposition(win.y1+5, win.x1+8);
	_outtext("u");

	switch(mouse_in_range(boundary,t1,t2))
	{
		case 0 : *pay=(long)base_price;             j=NO_PLUS; break;
		case 1 : *pay=(long)base_price*PLUS_1_COST; j=PLUS_1;  break;
		case 2 : *pay=(long)base_price*PLUS_2_COST; j=PLUS_2;  break;
		case 3 : *pay=(long)base_price*PLUS_3_COST; j=PLUS_3;  break;
		default: *pay=-1L;                          j=4;       break;
	}

	kill_gwindow(&win);

	return(j);
}

int _PASCAL learn_wiz_ill_spell( char *spell,long cost,int level,PLAYER *ply)
{
	char temp[80];
	int chance;
	int rolled;
	int sound;

	if (!got_enough_money(cost,ply))
		return(FALSE);

	switch(ply->intelligence)
	{
		case 9 :    chance=35;  break;
		case 10:    chance=45;  break;
		case 11:    chance=45;  break;
		case 12:    chance=45;  break;
		case 13:    chance=55;  break;
		case 14:    chance=55;  break;
		case 15:    chance=65;  break;
		case 16:    chance=65;  break;
		case 17:    chance=75;  break;
		case 18:    chance=85;  break;

		default:    if (ply->intelligence<9)
						chance=9;

					if (ply->intelligence>18)
						chance=95;

					break;
	}

	rolled=percent();

	if ((unsigned)((rand()%20))<ply->luck)
		rolled-=(rand()%20);

	if (rolled<=chance)
	{
		sprintf(temp,"Ye hath successfully learned '%s'",spell);

		switch(level)
		{
			case 1 :if (ply->learn_wiz1_spells)
						ply->learn_wiz1_spells--;
					else
					if (ply->learn_ill1_spells)
						ply->learn_ill1_spells--;

					break;

			case 2 :if (ply->learn_wiz2_spells)
						ply->learn_wiz2_spells--;
					else
					if (ply->learn_ill2_spells)
						ply->learn_ill2_spells--;

					break;

			case 3 :if (ply->learn_wiz3_spells)
						ply->learn_wiz3_spells--;
					else
					if (ply->learn_ill3_spells)
						ply->learn_ill3_spells--;

					break;
		}

		sound=GOOD;
	}
	else
	{
		sprintf(temp,"Ye hath failed to learn '%s'",spell);
		sound=BAD;
	}

	GX(temp,sound);

	return(rolled<=chance?TRUE:FALSE);
}

int _PASCAL learn_pri_dru_spell(char *spell,long cost,int level,PLAYER *ply)
{
	char temp[80];
	int chance;
	int rolled;
	int sound;

	if (!got_enough_money(cost,ply))
		return(FALSE);

	switch(ply->piety)
	{
		case 9 :    chance=35;  break;
		case 10:    chance=45;  break;
		case 11:    chance=45;  break;
		case 12:    chance=45;  break;
		case 13:    chance=55;  break;
		case 14:    chance=55;  break;
		case 15:    chance=65;  break;
		case 16:    chance=65;  break;
		case 17:    chance=75;  break;
		case 18:    chance=85;  break;

		default:    if (ply->piety<9)
						chance=9;

					if (ply->piety>18)
						chance=95;

					break;
	}

	rolled=percent();

	if ((unsigned)((rand()%20))<ply->luck)
		rolled-=(rand()%20);

	if (rolled<=chance)
	{
		sprintf(temp,"Ye hath successfully learned '%s'",spell);

		switch(level)
		{
			case 1 :if (ply->learn_pri1_spells)
						ply->learn_pri1_spells--;
					else
					if (ply->learn_dru1_spells)
						ply->learn_dru1_spells--;

					break;

			case 2 :if (ply->learn_pri2_spells)
						ply->learn_pri2_spells--;
					else
					if (ply->learn_dru2_spells)
						ply->learn_dru2_spells--;

					break;

			case 3 :if (ply->learn_pri3_spells)
						ply->learn_pri3_spells--;
					else
					if (ply->learn_dru3_spells)
						ply->learn_dru3_spells--;

					break;
		}

		sound=GOOD;
	}
	else
	{
		sprintf(temp,"Ye hath failed to learn '%s'",spell);
		sound=BAD;
	}

	GX(temp,sound);

	return(rolled<=chance?TRUE:FALSE);
}

void _PASCAL already_have_spell( char *spell)
{
	char temp[80];

	sprintf(temp,"Thou dost know '%s' already",spell);

	GX(temp,BAD);
}

void _PASCAL add_to_adv_carry_money_thanks(PLAYER *adv,long dough,
										   int item,int type)
{
	if (got_enough_money(dough,adv))
	{
		add_to_player(item,type,FALSE,ITEM_CARRIED,adv);
		thank_you();
	}
}
