#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL town_cathedral()
{
	GWINDOW win;
	static PLAYER aid,payer;
	int choice;
	unsigned long cost;
	char temp[80];
	int aid_select, payer_select;
	static    char *t[]={"Heal          (1100)",
						 "Cure Disease   (850)",
						 "Remove Poison  (600)",
						 "Pray at Chapel",
						 "Return to Town"};
	char *t2="HCRPT";
	static int boundary[]={80,56,240,62,
						   80,64,240,70,
						   80,72,240,78,
						   80,80,240,86,
						   80,88,240,94,
						   -1,-1,-1,-1};

	aid_select=adv_select_adventurer("Who seeks aid","at ye chapel?",FALSE);

	if (aid_select==ERR)
		return;

	memcpy((void *)&aid,(void *)&TPP[aid_select],sizeof(PLAYER));

	if (aid.is_dust)
	{
		sprintf(temp,"We can do naught, %s art dust!",aid.name);
		GX(temp,SOLEMN);
		return;
	}

	sprintf(temp,"What aid doth %s need?",adv.name);
	_settextposition(5,20-strlen_half(temp));
	_settextcolor(6);
	_outtext(temp);

	sprintf(temp,"CHAPEL OF %s",get_deity_name_in_town(pent_data.x,pent_data.y));
	print_large_title(temp);

	win.x1=10;
	win.y1=7;
	win.x2=32;
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

	choice=mouse_in_range(boundary,t2,"HCRPQ");

	switch(choice)
	{
		case 0 : cost=1100;  break;
		case 1 : cost=850;   break;
		case 2 : cost=600;   break;
		default:             break;
	}

	cath_error=FALSE;

	if (choice==3)
	{
		cath_pray(&aid);

		memcpy((void *)&TPP[aid_select],
			   (void *)&aid,
			   sizeof(PLAYER));
	}
	else
	if (choice!=4)
	{
		if (town_cath_who_is_paying(cost,&aid,&payer,&payer_select)!=FALSE)
		{
			if (same_people)
			{
				switch(choice)
				{
					case 0 : cath_heal(&aid,&aid,cost);          break;
					case 1 : cath_cure_disease(&aid,&aid,cost);  break;
					case 2 : cath_remove_poison(&aid,&aid,cost); break;
					default:                                     break;
				}
			}
			else
			{
				switch(choice)
				{
					case 0 : cath_heal(&aid,&payer,cost);          break;
					case 1 : cath_cure_disease(&aid,&payer,cost);  break;
					case 2 : cath_remove_poison(&aid,&payer,cost); break;
					default:                                       break;
				}
			}

			if (!cath_error)
			{
				if (!same_people)
					memcpy((void *)&TPP[payer_select],
						   (void *)&payer,
						   sizeof(PLAYER));

				memcpy((void *)&TPP[aid_select],
					   (void *)&aid,
					   sizeof(PLAYER));
			}
		}
	}

	kill_gwindow(&win);
}

int _PASCAL town_cath_who_is_paying(unsigned long cost,PLAYER *aid,PLAYER *payer,int *payer_select)
{
	char temp[80];
	int fin=FALSE;
	int res;

	while (!fin)
	{
		sprintf(temp,"%lu GC?",cost);

		if ((*payer_select=adv_select_adventurer("Who pays ye",temp,TRUE))==ERR)
		{
			fin=TRUE;
			res=FALSE;
		}
		else
		{
			if (adv.cash<cost)
			{
				sprintf(temp,"%s hath but %lu GC!",adv.name,adv.cash);
				GX(temp,BAD);
			}
			else
			{
				if (strcmp(adv.file_name,aid->file_name)==0)
				{
					same_people=TRUE;
					*payer=*aid;
				}
				else
				{
					memcpy((void *)payer,(void *)&adv,sizeof(PLAYER));
					same_people=FALSE;
				}

				res=TRUE;
				fin=TRUE;
			}
		}
	}

	return(res);
}

void _PASCAL town_food_market()
{
	int sel;
	int num;

	if (check_today_is_sunday_msg("Market"))
		return;

	if (is_night_time())
	{
		GX("Alas! Ye Market is closed. Try again tomorrow morning!",SOLEMN);
		return;
	}

	sel=adv_select_adventurer("Who doth","need food?",TRUE);

	if (sel==ERR)
		return;

	if ((num=market_get_quantity("Food",TPP[sel].food,MAX_FOOD))>0)
	{
		if (got_enough_money_for_misc((long)2*num,&TPP[sel]))
		{
			TPP[sel].food+=num;
			thank_you();
		}
	}
}
