#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

/*
 *
 *	Party get-next-round options
 *
 *
 */

int _PASCAL get_next_round_option()
{
	GWINDOW win;
	int opt,res;
	static int boundary[]={96, 66,118,85,
						   136,65,170,85,
						   190,63,213,85,
						   -1,-1,-1,-1};

	win.x1=11;
	win.y1=6;
	win.x2=29;
	win.y2=13;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+2,win.y1*8,"CMBTOPTS");

	opt=mouse_in_range(boundary,"FPC","");

	kill_gwindow(&win);

	switch(opt)
	{
		case 0 : res=next_round_flee();     break;
		case 1 : res=next_round_parley();   break;
		default: res=RES_NO_ACTION; 		break;	/* Combat selected */
	}                                               /* so fight! */

	if (party_is_hostile)
		the_monsters[0].speak_type=MSPK_SWEAR;

	return(res);
}

int _PASCAL next_round_flee()
{
	int i;
	int tot_speed=0;
	int tot_luck=0;
	int num_dead=0, num_alive=0;
	int res;
	int all_monst_fleeing=TRUE;

	for (i=0; i<MAX_MONSTERS; i++)
		if (monster_is_alive(&the_monsters[i]))
			if (!the_monsters[i].fleeing && !the_monsters[i].flown)
				all_monst_fleeing=FALSE;

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			tot_speed+=effective_speed(&TPP[i]);
			tot_luck+=((effective_luck(&TPP[i])>15?1:0));

			num_alive++;
		}
		else
			num_dead++;
	}

	tot_speed/=num_alive;
	tot_speed-=(num_dead*2);

	if (surprise_nstring==SURPRISE_PARTY)
		tot_speed+=get_dice_roll(4,1,1);

	if (((tot_speed+tot_luck) > (signed)the_monsters[0].speed) ||
		all_monst_fleeing)
	{
		res=RES_PARTY_FLEE;
		combat_write(14,"Thy party manages to escape!",TRUE);

		flee_sound();
	}
	else
	{
		res=RES_NO_ACTION;
		cmbt_bad_msg("Thy party fails to escape thy foe",TRUE);
	}

	return(res);
}

int _PASCAL next_round_parley()
{
	int speak_type=the_monsters[0].speak_type;

	switch(speak_type)
	{
		case MSPK_NONE	   : next_round_MSPK_NONE();	 break;
		case MSPK_GRUNT    : next_round_MSPK_GRUNT();	 break;
		case MSPK_SWEAR    : next_round_MSPK_SWEAR();	 break;
		case MSPK_MOAN	   : next_round_MSPK_MOAN();	 break;
		case MSPK_FRIENDLY : next_round_MSPK_FRIENDLY(); break;
		case MSPK_OFF_HAND : next_round_MSPK_OFF_HAND(); break;
		case MSPK_HROOM    : next_round_MSPK_HROOM();	 break;
	}

	return((speak_type==MSPK_FRIENDLY ||
			speak_type==MSPK_HROOM)
			?RES_PARLEY:RES_NO_ACTION);
}

void _PASCAL next_round_MSPK_NONE()
{
	display_monster_speak("No Reply!",BAD);
}

void _PASCAL next_round_MSPK_HROOM()
{
	static char *t[]={"HRUM ", "HROOM ",
					  "BARUM ","BUROOM ",
					  "HOOM ", "HAROOM ",
					  "BOOM ", "HOOOM "};
	int i;
	char temp[80];

	strcpy(temp,"\"");

	for (i=0; i<4; i++)
		strcat(temp,t[rand()%SIZE(t)]);

	strcat(temp,"fair well good people!\"");

	display_monster_speak(temp,GOOD);
}

void _PASCAL next_round_MSPK_GRUNT()
{
	static char *l[]={"loudly","mockingly","annoyingly","menacingly"};
	char temp[80];

	if (num_monsters==1)
		sprintf(temp,"Ye %s grunts %s at thy party!",
					  the_monsters[0].name,
					  l[(rand()%SIZE(l))]);
	else
		sprintf(temp,"Ye %ss grunt %s at thy party!",
					  the_monsters[0].name,
					  l[(rand()%SIZE(l))]);

	display_monster_speak(temp,BAD);
}

void _PASCAL next_round_MSPK_SWEAR()
{
	char temp[90];
	char *a[]={"loathsome", "useless", "disgusting",
			   "smelly",    "snotty",  "yellow",
			   "gutless",   "lowly",   "fat",
			   "weak",      "feeble",  "spineless",
			   "inept",     "foolish"};

	char *n[]={"cowards","worms","snails","wolf fodder","slugs","turds"};

	switch(rand()%2)
	{
		case 0 : sprintf(temp,"\"Thou art %s %s. Cut ye verbal and fight %s!\"",
							  a[(rand()%SIZE(a))],
							  n[(rand()%SIZE(n))],
							  num_monsters==1?"me":"us");
				 break;

		default: sprintf(temp,"\"Die %s %s!\"",a[(rand()%SIZE(a))],n[(rand()%SIZE(n))]);
				 break;
	}

	display_monster_speak(temp,BAD);
}

void _PASCAL next_round_MSPK_MOAN()
{
	char temp[80];
	static char *n[]={"solemnly","deeply"};

	sprintf(temp,"Ye %s%s moan%s %s!",
					 the_monsters[0].name,
					 num_monsters==1?"":"s",
					 num_monsters==1?"s":"",
					 n[(rand()%SIZE(n))]);

	display_monster_speak(temp,BAD);
}

void _PASCAL next_round_MSPK_FRIENDLY()
{
	display_monster_speak("\"Hail! Fair thee well on thy quest!\"",GOOD);
}

void _PASCAL next_round_MSPK_OFF_HAND()
{
	next_round_MSPK_SWEAR();
}

void _PASCAL display_monster_speak(char *mess,int sound)
{
	combat_write(sound==BAD?4:14,mess,TRUE);

	if (sound==BAD)
		bad_sound();
	else
		good_sound();

	cmbt_pause(2);
}
