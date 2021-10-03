#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL bank()
{
	GWINDOW win,win2;
	char line1[40],line2[40];
	int longest;
	static    char *t[]={"Withdraw All",
						 "Withdraw Some",
						 "Deposit All",
						 "Deposit Some",
						 "Pool all Cash",
						 "Disperse Cash",
						 "Leave ye Bank"};
	char *t2="WIDEPSL";
	int fin=FALSE;
	static int boundary[]={98,48,214,54,
						   98,56,214,62,
						   98,64,214,70,
						   98,72,214,78,
						   98,80,214,86,
						   98,88,214,94,
						   98,96,214,102,
						   -1,-1,-1,-1};

	if (check_today_is_sunday_msg("Bank"))
		return;

	if (is_night_time())
	{
		GX("Alas! Ye Bank is closed. Try again tomorrow morning!",SOLEMN);
		return;
	}

	print_large_title("AT YE WOLFBURG SAVINGS BANK");

	if (who_is_going("Who art going to ye Bank?")==ERR)
		return;

	if (player_is_dead(&adv))
	{
		sprintf(line1,"%s art dead!",adv.name);
		GX(line1,BAD);
		return;
	}

	if (player_is_drunk(&adv))
	{
		player_is_drunk_so_leave(&adv,"Bank");
		return;
	}

	win.x1=13;
	win.y1=6;
	win.x2=28;
	win.y2=15;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,
					   13);
	while (!fin)
	{
		sprintf(line1,"%s ye %s hath",adv.name,adv.class);
		sprintf(line2,"%lu GC banked & %lu GC in cash",adv.banked,adv.cash);

		longest=max(strlen(line1),strlen(line2));

		win2.x1=18-longest/2;
		win2.y1=2;
		win2.x2=22+longest/2;
		win2.y2=win2.y1+4;
		win2.back=0;
		win2.border=3;

		make_gwindow(&win2);

		_settextcolor(6);

		_settextposition(win2.y1+1,20-strlen_half(line1));
		_outtext(line1);
		_settextposition(win2.y1+2,20-strlen_half(line2));
		_outtext(line2);

		switch(mouse_in_range(boundary,"WIDEPSQ",t2))
		{
			case 0 :  bank_withdraw_all();       break;
			case 1 :  bank_withdraw_some();      break;
			case 2 :  bank_deposit_all();        break;
			case 3 :  bank_deposit_some();       break;
			case 4 :  bank_pool_all();           break;
			case 5 :  bank_disperse();           break;
			case 6 :  fin=TRUE;                  break;
			default:                             break;
		}

		kill_gwindow(&win2);
	}

	save_adventurer(&adv);

	kill_gwindow(&win);
}

static void _PASCAL _NEAR bank_withdraw_all()
{
	char temp[80];

	if (adv.banked==0L)
	{
		sprintf(temp,"%s hath no money to withdraw!",adv.name);
		GX(temp,BAD);
		return;
	}

	adv.cash+=adv.banked;
	adv.banked=0L;

	GX("All money withdrawn",GOOD);
}

static void _PASCAL _NEAR bank_withdraw_some()
{
	char temp[9];
	char temp1[80];
	GWINDOW win;
	unsigned long amount;
	char *title="Withdraw [        ]";

	if (adv.banked==0L)
	{
		sprintf(temp1,"%s hath no money to withdraw!",adv.name);
		GX(temp1,BAD);
		return;
	}

	win.x1=6;
	win.y1=7;
	win.y2=10;
	win.x2=win.x1+strlen(title)+2;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	_settextcolor(3);
	_settextposition(win.y1+1,win.x1+1);
	_outtext(title);

	strcpy(temp,gquery(win.x1+11,win.y1+1,sizeof(temp)-2,2,'N',""));

	kill_gwindow(&win);

	amount=(unsigned long)atol(temp);

	if (!strlen(temp))
		return;

	if (amount>adv.banked)
	{
		if (adv.banked==0L)
			sprintf(temp1,"%s hath no money banked!",adv.name);
		else
			sprintf(temp1,"%s hath but %lu GC banked!",adv.name,adv.banked);

		GX(temp1,BAD);
		return;
	}

	sprintf(temp1,"%lu GC withdrawn",amount);

	adv.banked-=amount;
	adv.cash+=amount;

	GX(temp1,GOOD);
}

static void _PASCAL _NEAR bank_deposit_all()
{
	char temp[50];

	if (adv.cash==0L)
	{
		sprintf(temp,"%s hath no money to deposit!",adv.name);
		GX(temp,BAD);
		return;
	}

	adv.banked+=adv.cash;
	adv.cash=0L;

	GX("All cash deposited",GOOD);
}

static void _PASCAL _NEAR bank_deposit_some()
{
	char temp[9];
	char temp1[80];
	GWINDOW win;
	unsigned long amount;
	char *title="Deposit  [        ]";

	if (adv.cash==0L)
	{
		sprintf(temp1,"%s hath no cash to deposit!",adv.name);
		GX(temp1,BAD);
		return;
	}

	win.x1=6;
	win.y1=7;
	win.y2=10;
	win.x2=win.x1+strlen(title)+2;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	_settextcolor(3);
	_settextposition(win.y1+1,win.x1+1);
	_outtext(title);

	strcpy(temp,gquery(win.x1+11,win.y1+1,sizeof(temp)-2,2,'N',""));

	kill_gwindow(&win);

	amount=atol(temp);

	if (!strlen(temp))
		return;

	if (amount>adv.cash)
	{
		if (adv.cash==0L)
			sprintf(temp1,"%s hath no cash on you!",adv.name);
		else
			sprintf(temp1,"%s hath only %lu GC in cash!",adv.name,adv.cash);

		GX(temp1,BAD);
		return;
	}

	sprintf(temp1,"%lu GC deposited",amount);

	adv.banked+=amount;
	adv.cash-=amount;

	GX(temp1,GOOD);
}

static void _PASCAL _NEAR bank_pool_all()
{
	int i;
	GWINDOW win;
	static PLAYER local;
	char temp[20];
	FILE *fptr;
	int found=FALSE;

	win.x1=11;
	win.y1=9;
	win.x2=29;
	win.y2=12;
	win.back=0;
	win.border=1;

	make_gwindow(&win);

	_settextcolor(9);

	for (i=0; i<MAX_ON_DISC; i++)
	{
		sprintf(temp,ADV_PREFIX,i);

		if (strcmp(temp,adv.file_name)==0)
			continue;

		fptr=fopen(temp,"rb");

		if (fptr==(FILE *)NULL)
			continue;

		found=TRUE;

		fread((void *)&local,sizeof(PLAYER),1,fptr);

		_settextposition(win.y1+1,win.x1+1);
		_outtext("               ");

		_settextposition(win.y1+1,20-strlen_half(local.name));
		_outtext(local.name);

		fclose(fptr);

		adv.cash+=local.cash;
		local.cash=0L;

		fptr=fopen(temp,"wb");
		fwrite((void *)&local,sizeof(PLAYER),1,fptr);
		fclose(fptr);
	}

	kill_gwindow(&win);

	GX(found?"All cash pooled":"No one found to pool cash with!",
			 found?GOOD:BAD);
}

static void _PASCAL _NEAR bank_disperse()
{
	int i;
	GWINDOW win;
	static PLAYER local;
	char temp[40];
	FILE *fptr;
	int found=FALSE;
	unsigned long num_on_disc, cash, split_amount;
	char *hang_on="Dispersing...!";

	win.x1=11;
	win.y1=9;
	win.x2=29;
	win.y2=12;
	win.back=0;
	win.border=1;

	make_gwindow(&win);

	_settextcolor(9);

	num_on_disc=cash=split_amount=0L;

	save_adventurer(&adv);

	for (i=0; i<MAX_ON_DISC; i++)
	{
		sprintf(temp,ADV_PREFIX,i);

		fptr=fopen(temp,"rb");

		if (fptr==(FILE *)NULL)
			continue;

		found=TRUE;
		num_on_disc++;

		fread((void *)&local,sizeof(PLAYER),1,fptr);
		fclose(fptr);

		_settextposition(win.y1+1,win.x1+1);
		_outtext("               ");

		_settextposition(win.y1+1,20-strlen_half(local.name));
		_outtext(local.name);

		cash+=local.cash;
		local.cash=0L;

		fptr=fopen(temp,"wb");
		fwrite((void *)&local,sizeof(PLAYER),1,fptr);
		fclose(fptr);
	}

	if (num_on_disc)
	{
		_settextposition(win.y1+1,win.x1+1);
		_outtext("               ");

		_settextposition(win.y1+1,20-strlen_half(hang_on));
		_outtext(hang_on);

		split_amount=cash/num_on_disc;

		for (i=0; i<MAX_ON_DISC; i++)
		{
			sprintf(temp,ADV_PREFIX,i);

			fptr=fopen(temp,"rb");

			if (fptr==(FILE *)NULL)
				continue;

			fread((void *)&local,sizeof(PLAYER),1,fptr);
			fclose(fptr);

			local.cash=split_amount;

			fptr=fopen(temp,"wb");
			fwrite((void *)&local,sizeof(PLAYER),1,fptr);
			fclose(fptr);
		}

		fptr=fopen(adv.file_name,"rb");

		fread((void *)&adv,sizeof(PLAYER),1,fptr);
	}

	kill_gwindow(&win);

	GX(found?"All cash dispersed":"No one found to disperse cash with!",
			 found?GOOD:BAD);
}
