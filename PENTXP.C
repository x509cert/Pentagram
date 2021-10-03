#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL distribute_xp_gc(unsigned long xp)
{
	GWINDOW win;
	int i;
	int total_prof=0;
	unsigned long xp_per_prof;
	unsigned long xp_increase;
	char temp[80];
	char number[16];
	static int boundary[]={134,100,169,112,
							-1,-1,-1,-1};

	distribute_gc();
	check_for_HOE();

	if (xp==0L)
		return;

	for (i=0; i<=P_NUM; i++)
	{
		if (TPP[i].professionalism==0)
			TPP[i].professionalism++;

		if (player_is_alive(&TPP[i]))
			total_prof+=TPP[i].professionalism;
	}

	xp_per_prof=(long)(xp/(long)total_prof);

	win.x1=5;
	win.y1=3;
	win.x2=35;
	win.y2=16;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+54,win.y1*8,"DIST_XP");

	click_box(134,100,B_OK);

	_settextcolor(5);

	for (i=0; i<=P_NUM; i++)
	{
		_settextposition(win.y1+4+i,win.x1+1);

		strcpy(temp,TPP[i].name);

		if (player_is_alive(&TPP[i]))
			xp_increase=xp_per_prof*(long)TPP[i].professionalism;
		else
			xp_increase=0L;

		sprintf(number,"%ld XP",xp_increase);

		while(strlen(temp)+strlen(number)<(size_t)(win.x2-win.x1-2))
			strcat(temp,".");

		strcat(temp,number);

		_outtext(temp);

		TPP[i].xp+=xp_increase;
	}

	good_sound();

	for (i=0; i<=P_NUM; i++)
		TPP[i].professionalism=0;

	the_party.xp_earned=0L;

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

void _PASCAL distribute_gc()
{
	int i;
	unsigned long share;
	int number_alive;
	GWINDOW win;
	int len2;
	char temp[80];
	static int boundary[]={134,102,169,114,
							-1,-1,-1,-1};

	if (the_party.gc_earned<=10L)
		return;

	for (i=0,number_alive=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			number_alive++;

	share=the_party.gc_earned/(long)number_alive;

	sprintf(temp,"Each member earns %lu GC!",share);
	len2=strlen_half(temp);

	win.x1=5;
	win.x2=35;
	win.y1=7;
	win.y2=win.y1+9;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+44,win.y1*8,"DIST_GC");

	_settextposition(win.y1+5,20-len2);
	_settextcolor(11);
	_outtext(temp);

	click_box(134,102,B_OK);

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			TPP[i].cash+=share;

	the_party.gc_earned=0L;

	good_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	if (pent_data.current_feature==CITY)
	{
		share=(share/100L)*THIEVES_GUILD_CUT;

		if (share==0L)
			share++;

		thieves_pay_guild(share);
	}
}

void _PASCAL add_to_professionalism(PLAYER *adv,int amount)
{
	adv->professionalism+=amount;

	if (adv->professionalism>MAX_PROFESSIONALISM)
		adv->professionalism=MAX_PROFESSIONALISM;
}

void _PASCAL add_xp_to_party(unsigned long amount)
{
	the_party.xp_earned+=amount;
}

void _PASCAL check_for_HOE()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			if (TPP[i].kills>=HOE_KILL_THRESHOLD)
				if (!TPP[i].member_of_HOE)
					can_join_HOE(&TPP[i]);
}

void _PASCAL can_join_HOE(PLAYER *adv)
{
	GWINDOW win;
	char temp[60];
	int y,i;
	static char *en[]={"%s art now an honoury",
					   "member of ye most ancient",
					   "High Order of Executioneers",
					   "for slaying ninety monsters!"};
	static int boundary[]={137,100,172,112};

	adv->member_of_HOE=TRUE;

	win.x1=4;
	win.y1=5;
	win.x2=36;
	win.y2=16;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	y=win.y1+4;

	_settextcolor(5);
	sprintf(temp,en[0],adv->name);

	_settextposition(y++,20-strlen_half(temp));
	_outtext(temp);

	for (i=1; i<SIZE(en); i++)
	{
		_settextposition(y++,20-strlen_half(en[i]));
		_outtext(en[i]);
	}

	click_box(137,100,B_OK);
	draw_HOE_coa(144,38);

	HOE_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

void _PASCAL thieves_pay_guild(unsigned long amount)
{
	char temp[100];
	int i;
	int num_thieves=class_in_party(THIEF);

	if (num_thieves==0)
		return;

	sprintf(temp,"Thy th%s pay%sa %luGC cut to ye thieves guild.",
				num_thieves==1?"ief":"ieves",
				num_thieves==1?"s ":" ",
				amount);

	SCROLL(1,14,temp);

	for (i=0; i<=P_NUM; i++)
		if (TPP[i].nclass==THIEF)
			TPP[i].cash-=amount;

	general_low_sound();
	pause(2);
}
