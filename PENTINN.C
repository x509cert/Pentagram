#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <bstrings.h>
#include <string.h>

void _PASCAL inn(char *inn_name)
{
	GWINDOW win;
	char temp[40];
	static	  char *t[]={"Stay at Inn  (20)",
						 "Buy a Drink   (1)",
						 "Leave ye Inn"};
	int fin=FALSE;
	static int boundary[]={88,48,224,54,
						   88,56,224,62,
						   88,64,224,70,
						   -1,-1,-1,-1};
	win.x1=11;
	win.y1=6;
	win.x2=30;
	win.y2=11;
	win.back=0;
	win.border=4;

	killed_by_barman=FALSE;

	while (!fin)
	{
		sprintf(temp,"AT YE \"%s\" INN",inn_name);

		print_large_title(temp);

		make_gwindow(&win);

		print_menu_options(t,
						   SIZE(t),
						   "SBL",
						   win.x1+1,
						   win.y1+1,
						   5,13);

		switch(mouse_in_range(boundary,"SBL","ªªQ"))
		{
			case 0 : kill_gwindow(&win);
					 stay_a_night(inn_name);
					 break;

			case 1 : kill_gwindow(&win);
					 buy_a_drink(inn_name);
					 break;

			default: kill_gwindow(&win);
					 fin=TRUE;
					 break;
		}

		if (killed_by_barman)
			fin=TRUE;
	}
}

void _PASCAL stay_a_night(char *inn_name)
{
	char temp[80];
	GWINDOW win;
	FILE *fptr;
	int i,j;
	int day_nite;
	int col;
	static int boundary1[]={130,140,165,152,
							-1,-1,-1,-1};

	static int boundary2[]={130,104,165,116,
							-1,-1,-1,-1};

	if (the_party.in_town)
	{
		rumr_person=adv_select_adventurer("Who pays","ye 20 GC?",TRUE);

		if (rumr_person!=ERR)
			memcpy((void *)&adv,(void *)&TPP[rumr_person],sizeof(PLAYER));
		else
			return;
	}
	else
	{
		if (who_is_going("Who art paying ye 20 GC?")==ERR)
		{
			return;
		}
	}

	if (player_is_dead(&adv))
	{
		sprintf(temp,"%s art dead!",adv.name);
		GX(temp,BAD);
		return;
	}

	if (adv.guild_member)
		GX("\"Dungeoneers Guild members need pay only 10 GC!\"",GOOD);

	if (!got_enough_money_not_inv(adv.guild_member?10L:20L,&adv))
		return;

	win.x1=3;
	win.y1=4;
	win.x2=37;
	win.y2=win.y1+(the_party.in_town?12:17);
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	click_box(130,the_party.in_town?104:140,B_OK);

	_settextcolor(14);

	sprintf(temp,"Resting at ye %s Inn",inn_name);

	_settextposition(win.y1+1,(win.x1+(win.x2-win.x1)/2)-strlen_half(temp));
	_outtext(temp);

	if (the_party.in_town)
	{
		memcpy((void *)&TPP[rumr_person],(void *)&adv,sizeof(PLAYER));

		for (i=0; i<=P_NUM; i++)
		{
			strcpy(temp,inn_rest_one_person(&TPP[i],&col));

			_settextcolor(col);
			_settextposition(win.y1+3+i,win.x1+1);
			_outtext(temp);
		}
	}
	else
	{
		for (i=0,j=0; i<=MAX_ON_DISC; i++)
		{
			sprintf(temp,ADV_PREFIX,i);

			fptr=fopen(temp,"rb");

			if (fptr==(FILE *)NULL)
				continue;

			fread((void *)&adv,sizeof(PLAYER),1,fptr);

			fclose(fptr);

			if (the_party.in_town && !adv.in_party)
				continue;

			strcpy(temp,inn_rest_one_person(&adv,&col));

			_settextcolor(col);
			_settextposition(win.y1+3+j,win.x1+1);
			_outtext(temp);

			save_adventurer(&adv);

			j++;
		}
	}

	set_next_day_dawn();

	day_nite=determine_day_nite_icon();

	if (pent_data.current_day_night_icon!=day_nite)
		pent_data.current_day_night_icon=day_nite;

	if (the_party.in_town)
		inn_town_awaken();

	wake_up_sound();

	(void)mouse_in_range(the_party.in_town?boundary2:boundary1,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

void _PASCAL inn_town_awaken()
{
	static char *awake[]={"a cock crowing",
						  "a wagon rolling past thy window",
						  "townfolk outside thy window",
						  "ye town-crier",
						  "a stream of light through thy window",
						  "a barking dog"};
	static char *dawn[]={"'tis dawn",
						 "Dawn breaks",
						 "Day breaks",
						 "'tis 7:30"};
	char temp[110];

	sprintf(temp,"%s and thy party art awakened by %s.",
				 dawn[rand()%4],
				 awake[rand()%6]);

	scroll_wrap_write(14,temp);
}

char *inn_rest_one_person(PLAYER *adv,int *colour)
{
	static char temp[80];
	int diff;

	if (!adv->is_dead     &&
		!adv->is_dust     &&
		!adv->is_poisoned &&
		!adv->is_diseased)
	{
		if ((diff=adv->hp-adv->current_hp)>2)
			adv->current_hp+=get_dice_roll(diff,1,0);
		else
			adv->current_hp=adv->hp;

		if ((diff=adv->sorcery_points-adv->current_sorcery_points)>2)
			adv->current_sorcery_points+=get_dice_roll(diff,1,0);
		else
			adv->current_sorcery_points=adv->sorcery_points;

		if ((diff=adv->divine_points-adv->current_divine_points)>2)
			adv->current_divine_points+=get_dice_roll(diff,1,0);
		else
			adv->current_divine_points=adv->divine_points;

		update_one_wand_ring(adv);

		adv->drunkeness=0;

		sprintf(temp,"%s art rested!",adv->name);

		*colour=6;
	}
	else
	{
		if (player_is_dead(adv))
		{
			sprintf(temp,"%s rests in peace!",adv->name);
		}
		else
		if (adv->is_poisoned || adv->is_diseased)
		{
			adv->current_hp-=rand()%10;

			if (adv->current_hp<=0)
			{
				adv->current_hp=0;
				adv->is_dead=TRUE;

				sprintf(temp,"%s died of %s!",
							 adv->name,
							 adv->is_diseased?"disease":"poison");

			}
			else
			{
				sprintf(temp,"%s art feeling unwell!",adv->name);
			}
		}

		*colour=4;
	}

	return(temp);
}

void _PASCAL buy_a_drink(char *inn_name)
{
	char temp[80],temp2[80];
	int bartenders_sex=(percent()>60)?SX_FEMALE:SX_MALE;
	char *line="Who art paying for a drink?";
	static char *lines[]={ "\"I HEAR THOU ART AFTER SOME USEFUL INFORMATION",
						   "\"I MAY HAVE SOME VALUABLE INFORMATION FOR YE",
						   "\"I CAN BE OF AID TO THY QUEST",
						   "\"I KNOW A FEW THINGS THAT MAY BE OF ASSISTANCE",
						   "\"I AM SURE I CAN BE OF IMMENSE AID TO THY QUEST",
						   "\"I CAN BE OF GREAT AID TO THY PRESENT CAUSE",
						   "\"I HAVE KNOWLEDGE OF THINGS THAT MAY AID THEE"};

	if (the_party.in_town)
	{
		rumr_person=adv_select_adventurer("Who's to pay","for a drink?",TRUE);

		if (rumr_person!=ERR)
			memcpy((void *)&adv,(void *)&TPP[rumr_person],sizeof(PLAYER));
		else
			return;
	}
	else
		if (who_is_going(line)==ERR)
			return;

	if (player_is_dead(&adv))
	{
		sprintf(temp,"%s art dead!",adv.name);
		GX(temp,BAD);
		return;
	}

	if (!got_enough_money_not_inv(1L,&adv))
		return;

	if (player_is_drunk(&adv))
	{
		sprintf(temp,"Ye %s refuses to serve thee as ye hath had enough to drink!",
					  (bartenders_sex==SX_MALE)?"bartender":"barmaid");

		GX(temp,BAD);

		sprintf(temp,"Ye realise %s is right and leave Ye %s",
					  (bartenders_sex==SX_MALE)?"he":"she",
					  inn_name);

		GX(temp,BAD);

		TPP[rumr_person]=adv;

		if (!the_party.in_town)
			save_adventurer(&adv);

		return;
	}

	switch(rand()%5)
	{
		case 0 : strcpy(temp,"AN ALE");     break;
		case 1 : strcpy(temp,"A PINT");     break;
		case 2 : strcpy(temp,"SOME MEAD");  break;
		case 3 : strcpy(temp,"A DRINK");    break;
		default: strcpy(temp,"SOME GROG");  break;
	}

	if (player_is_tipsy(&adv))
	{
		sprintf(temp2,"%s art feeling a little dizzy..!",adv.name);
		scroll_wrap_write(1,temp2);
		scroll_scroll();

		pause(1);
	}

	sprintf(temp2,"YE PAY 1GC FOR %s AND..",temp);
	scroll_wrap_write(1,temp2);

	pause(2);
	scroll_scroll();

	switch(rand()%6)
	{
		case 0 : strcpy(temp,"QUIETLY");         break;
		case 1 : strcpy(temp,"SOFTLY");          break;
		case 2 : strcpy(temp,"CONFIDENTLY");     break;
		case 3 : strcpy(temp,"SILENTLY");        break;
		case 4 : sprintf(temp,"UNDER %s BREATH",bartenders_sex==SX_MALE?"HIS":"HER"); break;
		default: strcpy(temp,"IN HUSHED TONES"); break;
	}

	sprintf(temp2,"Ye %s %s %s,",
				bartenders_sex==SX_MALE?"bartender":"barmaid",
				percent()>50?"SAYS":"MUTTERS",
				temp);

	scroll_wrap_write(0,temp2);

	pause(2);

	strcpy(temp,lines[rand()%SIZE(lines)]);

	if (percent()>50)
	{
		strcat(temp," ");
		strcat(temp,adv.sex_title);
	}

	stpcvt(temp,RTWHITE|REDUCE);
	strcat(temp,"\"");

	SCROLL(1,1,temp);

	pause(2);
	scroll_scroll();

	rumour_divulge_info(bartenders_sex);

	adv.drunkeness++;

	cls_scroll();

	if (!the_party.in_town)
		save_adventurer(&adv);
	else
		TPP[rumr_person]=adv;
}
