#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

static char *res_first="%s must be resurrected first!";

void _PASCAL cathedral()
{
	GWINDOW win;
	char temp[80];
	static PLAYER aid,payer;
	int choice;
	unsigned long cost;
	static    char *t[]={"Resurrect    (10000)",
						 "Heal          (1000)",
						 "Cure Disease   (800)",
						 "Exorcise      (2000)",
						 "Remove Poison  (500)",
						 "Pray in Cathedral",
						 "Leave ye Cathedral"};
	static int boundary[]={80,48, 240,54,
						   80,56, 240,62,
						   80,64, 240,70,
						   80,72, 240,78,
						   80,80, 240,86,
						   80,88, 240,94,
						   80,96, 240,102,
						   -1,-1,-1,-1};
	char *t2="RHCEPIL";

	if (who_is_going("Who seeks aid from ye cathedral?")==ERR)
		return;

	sprintf(temp,"What aid doth %s need?",adv.name);
	_settextposition(4,20-strlen_half(temp));
	_settextcolor(6);
	_outtext(temp);
	
	sprintf(temp,"CATHDERAL OF %s",get_deity_name_in_town(pent_data.x,pent_data.y));
	print_large_title(temp);

	win.x1=10;
	win.y1=6;
	win.x2=32;
	win.y2=15;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,win.y1+1,
					   5,
					   13);

	memcpy(&aid,&adv,sizeof(PLAYER));

	if (aid.is_dust)
	{
		sprintf(temp,"There art naught I can do, %s is dust!",aid.name);
		GX(temp,SOLEMN);
		return;
	}
	else
	{
		choice=mouse_in_range(boundary,"RHCEPIQ",t2);

		switch(choice)
		{
			case 0 : cost=10000L;   break;
			case 1 : cost=1000L;    break;
			case 2 : cost=800L;     break;
			case 3 : cost=2000L;    break;
			case 4 : cost=500L;     break;
			case 5 :				break;
			default:                break;
		}

		cath_error=FALSE;

		if (choice==5)
		{
			cath_pray(&aid);
			save_adventurer(&aid);
		}
		else
		if (choice!=6)
		{
			if (cath_who_is_paying(cost,&aid,&payer)!=FALSE)
			{
				if (same_people)
				{
					switch(choice)
					{
						case 0 :  cath_resurrect(&aid,&aid,cost);     break;
						case 1 :  cath_heal(&aid,&aid,cost);          break;
						case 2 :  cath_cure_disease(&aid,&aid,cost);  break;
						case 3 :  cath_exorcise(&aid,&aid,cost);      break;
						case 4 :  cath_remove_poison(&aid,&aid,cost); break;
						default:                                      break;
					}
				}
				else
				{
					switch(choice)
					{
						case 0 :  cath_resurrect(&aid,&payer,cost);     break;
						case 1 :  cath_heal(&aid,&payer,cost);          break;
						case 2 :  cath_cure_disease(&aid,&payer,cost);  break;
						case 3 :  cath_exorcise(&aid,&payer,cost);      break;
						case 4 :  cath_remove_poison(&aid,&payer,cost); break;
						default:                                        break;
					}
				}

				if (!cath_error)
				{
					if (!same_people)
						save_adventurer(&payer);

					save_adventurer(&aid);
				}
			}
		}
	}

	kill_gwindow(&win);
}

void _PASCAL cath_resurrect(PLAYER *aid,PLAYER *payer,unsigned long cost)
{
	char temp[80];

	if (player_is_alive(aid))
	{
		GX("Be gone dolt, thou art alive!",BAD);
		cath_take_1pc_for_trouble(payer,cost);

		return;
	}

	payer->cash-=cost;

	aid->is_dead=aid->is_dust=FALSE;

	aid->current_hp=1;

	sprintf(temp,"After much praying, %s rises from death!",
				aid->name);

	GX(temp,GOOD);

	cath_determine_insurance(aid,payer,cost);
}

void _PASCAL cath_heal(PLAYER *aid,PLAYER *payer,unsigned long cost)
{
	char temp[80];
	int i;
	static char *beat[]={"beaten",
						 "battered",
						 "scarred",
						 "bruised",
						 "injured",
						 "hacked",
						 "bloodied"};

	if (aid->current_hp==aid->hp)
	{
		GX("Be gone dolt, thy flesh art unscathed!",BAD);
		cath_take_1pc_for_trouble(payer,cost);

		return;
	}

	if (aid->is_dead)
	{
		sprintf(temp,res_first,aid->name);
		GX(temp,BAD);

		cath_error=TRUE;

		return;
	}

	payer->cash-=cost;

	aid->current_hp=aid->hp;

	i=rand()%SIZE(beat);

	sprintf(temp,"Ye Cleric heals %s%s %s body!",
				aid->name,
				end_s(aid->name),
				beat[i]);

	GX(temp,GOOD);

	cath_determine_insurance(aid,payer,cost);
}

void _PASCAL cath_cure_disease(PLAYER *aid,PLAYER *payer,unsigned long cost)
{
	char temp[80];
	char *disease;

	if (aid->disease==NO_DISEASE)
	{
		GX("Be gone dolt, thy body art free of disease!",BAD);
		cath_take_1pc_for_trouble(payer,cost);

		return;
	}

	if (aid->is_dead)
	{
		sprintf(temp,res_first,aid->name);
		GX(temp,BAD);

		cath_error=TRUE;

		return;
	}

	payer->cash-=cost;

	switch(aid->disease)
	{
		case GRAVE_ROT  : disease="Grave Rot"; break;
		case POX        : disease="ye Pox";    break;
		default         : disease="ye Plague"; break;
	}

	recover_from_disease(aid);

	sprintf(temp,"Ye Cleric cures %s of %s!",
				aid->name,
				disease);

	GX(temp,GOOD);

	cath_determine_insurance(aid,payer,cost);
}

void _PASCAL cath_exorcise(PLAYER *aid,PLAYER *payer,unsigned long cost)
{
	char temp[80];
	int i;
	int cursed=FALSE;

	for (i=0; i<MAX_CARRY; i++)
	{
		if (aid->items_carried[i].type==CURSED)
		{
			aid->items_carried[i].type=NO_PLUS;
			cursed=TRUE;
			break;
		}
	}

	if (!cursed)
	{
		GX("Be gone dolt, thy body art free of curses!",BAD);
		cath_take_1pc_for_trouble(payer,cost);

		return;
	}

	if (aid->is_dead)
	{
		sprintf(temp,res_first,aid->name);
		GX(temp,BAD);

		cath_error=TRUE;

		return;
	}

	payer->cash-=cost;

	sprintf(temp,"Ye Cleric chants over %s%s cursed body!",
				aid->name,
				end_s(aid->name));

	GX(temp,GOOD);

	cath_determine_insurance(aid,payer,cost);
}

void _PASCAL cath_remove_poison(PLAYER *aid,PLAYER *payer,unsigned long cost)
{
	char temp[80];

	if (!aid->is_poisoned)
	{
		GX("Be gone dolt, thy body art free of poison!",BAD);
		cath_take_1pc_for_trouble(payer,cost);

		return;
	}

	if (aid->is_dead)
	{
		sprintf(temp,res_first,aid->name);
		GX(temp,BAD);

		cath_error=TRUE;

		return;
	}

	payer->cash-=cost;

	aid->is_poisoned=FALSE;

	sprintf(temp,"Ye Cleric removes ye poisons from %s%s body!",
				aid->name,
				end_s(aid->name));

	GX(temp,GOOD);

	cath_determine_insurance(aid,payer,cost);
}

int _PASCAL cath_who_is_paying(unsigned long cost, PLAYER *aid,PLAYER *payer)
{
	char temp[80];
	int fin=FALSE;
	int res;

	while (!fin)
	{
		sprintf(temp,"Who pays ye %lu GC?",cost);

		if (who_is_going(temp)==ERR)
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

void _PASCAL cath_determine_insurance(PLAYER *aid,PLAYER *payer,unsigned long cost)
{
	char temp[80];
	unsigned long rebate;

	if (aid->insurance)
	{
		rebate=cost-(cost/10L);

		sprintf(temp,"As %s art insured, %s gets a rebate of %lu GC!",
								aid->name,
								payer->name,
								rebate);

		payer->cash+=rebate;

		GX(temp,GOOD);
	}
}

void _PASCAL cath_take_1pc_for_trouble(PLAYER *payer,unsigned long amount)
{
	char temp[80];
	unsigned long take=amount/100L;

	if (take==0L)
		take++;

	sprintf(temp,"For thy stupidity, ye cathedral shall take %lu GC!",
				take);

	GX(temp,BAD);

	payer->cash-=take;
}
