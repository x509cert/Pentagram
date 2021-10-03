#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

/*
 *
 * Monster Make combat decision
 *
 */

void _PASCAL make_monster_decision(MONSTER *mnst)
{
	int i;
	int num;
	int make_move=FALSE;
	int moved=FALSE;
	char temp[80];
	int num_attacks=(mnst->is_lethargic?1:MAX_ATTACK);

	if (monster_is_dead(mnst) || mnst->flown)
		return;

	if (!party_is_hostile)
	{
		if (mnst->ethics==LAWFUL)
		{
			combat_write(14,"Thy foe appears not to expect battle!",TRUE);
			good_sound();

			return;
		}
	}

	cmbt_buzz_a_square(mnst->x,mnst->y,BUZZ_SHORT);

	if (mnst->spell_bound)
	{
		sprintf(temp,"%s art spellbound!",mnst->name);
		combat_write(14,temp,TRUE);
		good_sound();

		mnst->spell_bound--;

		return;
	}

	if (mnst->is_lethargic)
		mnst->is_lethargic--;

	if (mnst->time_suspended)
	{
		sprintf(temp,"%s stands motionless!",mnst->name);
		combat_write(14,temp,TRUE);
		good_sound();

		mnst->time_suspended--;

		return;
	}

	morale_check(mnst);

	if (mnst->fleeing && !mnst->flown)
	{
		make_monster_flee(mnst);
		return;
	}

	if (monster_surrounded(mnst))
	{
		monster_stands_firm(mnst);
		return;
	}

	for (i=0; i<num_attacks; i++)
	{
		switch(mnst->attack_type[i])
		{
			case MON_CLAW		:
			case MON_KICK		:
			case MON_WEAPON 	:
			case MON_BITE		:
			case MON_TAIL_LASH	:
			case MON_PUNCH		:
			case MON_STING		:	num=analyse_players_about_monster(mnst);

									if (num==ERR)
										make_move=TRUE;
									else
										if (make_monster_attack(mnst,i)==ERR)
											make_move=TRUE;

									break;
			case MON_FIRE		:
			case MON_ICE		:
			case MON_ELECTRICITY:
			case MON_MAGIC		:
			case MON_GAZE		:
			case MON_SPIT_FIRE  :
			case MON_ROCK		:
			case MON_ARROW		:
			case MON_BREATH 	:	if (make_monster_cast_spell(mnst,i)==FALSE)
										make_move=TRUE;

									break;

			case MON_NO_ATTACK	:
			default 			:	continue;
		}

		if (make_move && !moved)
			make_monster_move(mnst);

		moved=TRUE;
	}
}

int _PASCAL _NEAR monster_surrounded(MONSTER *mnst)
{
	int i;
	static int b[]={ 0, 1,
					 0,-1,
					 1, 0,
					-1, 0,
					-1,-1,
					 1,-1,
					-1, 1,
					 1, 1};

	for (i=0; i<SIZE(b); i+=2)
		if (cmbt_area_contents(mnst->x+b[i],mnst->y+b[i+1])==IS_EMPTY)
			return(FALSE);

	return(TRUE);
}

int _PASCAL analyse_players_about_monster(MONSTER *mnst)
{
	int i;
	int mx=mnst->x,my=mnst->y;
	int count=ERR;
	PLAYER *adv;
	char temp[50];
	static int b[]={ 0, 1,
					 0,-1,
					 1, 0,
					-1, 0,
					-1,-1,
					 1,-1,
					-1, 1,
					 1, 1};

	for (i=0; i<MAX_PARTY; i++)
		about_monsters[i]=(PLAYER *)NULL;

	for (i=0; i<SIZE(b); i+=2)
	{
		if (cmbt_area_contents(mx+b[i],my+b[i+1])==IS_PLAYER)
		{
			adv=cmbt_area[mx+b[i]][my+b[i+1]].occ.player;

			if (adv->sneaking && (percent()<effective_move_silently(adv)))
			{
				sprintf(temp,"%s goes unnoticed by ye foe!",adv->name);
				combat_write(14,temp,TRUE);

				good_sound();
			}
			else
			{
				about_monsters[++count]=adv;
			}
		}
	}

	num_players_about_monster=count;

	return(count);
}

int _PASCAL get_player_to_attack()
{
	int person;

	person=rand()%(num_players_about_monster+1);

	return(person);
}

int _PASCAL make_monster_attack(MONSTER *mnst,int attack)
{
	char temp[80];
	int person;
	int hit=FALSE;
	PLAYER *adv;

	person=get_player_to_attack();

	if (person==ERR)
		return(ERR);

	adv=about_monsters[person];

	if (adv->nclass==THIEF && adv->sneaking)
	{
		sprintf(temp,"%s art spotted!",adv->name);
		combat_write(5,temp,TRUE);

		bad_sound();

		adv->sneaking=FALSE;

		cmbt_pause(1);
	}

	strcpy(temp,monster_phys_attack_string(mnst,adv,attack));
	combat_write(4,temp,FALSE);

	if (get_d20()>=effective_monster_attack(mnst,adv))
	{
		if ((adv->is_parrying && (percent()>effective_parry(adv))	  ||
			!adv->is_parrying))
		{
			cmbt_monster_phys_hits(adv,mnst,attack);
			hit=TRUE;
		}
	}

	if (!hit)
	{
		strcpy(temp,monster_phys_miss_string(mnst,adv,attack));
		combat_write(14,temp,TRUE);
		good_sound();

		cmbt_pause(1);
	}

	return(person);
}

void _PASCAL make_monster_move(MONSTER *mnst)
{
	actually_make_monster_move(mnst);
}

void _PASCAL actually_make_monster_move(MONSTER *mnst)
{
	unsigned int oldx=mnst->x;
	unsigned int oldy=mnst->y;
	char temp[80];

	get_new_monster_location(mnst);

	if (oldx!=mnst->x || oldy!=mnst->y)
	{
		if (mnst->fleeing)
			sprintf(temp,"%s art fleeing!",mnst->name);
		else
			sprintf(temp,"%s doth move!",mnst->name);

		combat_write(4,temp,TRUE);

		cmbt_area_nullify_square(oldx,oldy);
		pos_one_monster(mnst,mnst->x,mnst->y);

		move_monster_sound();

		cmbt_pause(1);
	}
	else
	{
		if (move_monster_randomly(mnst)==FALSE)
		{
			monster_stands_firm(mnst);
		}
	}
}

void _PASCAL _NEAR monster_stands_firm(MONSTER *mnst)
{
	char temp[30];

	sprintf(temp,"%s stands firm!",mnst->name);
	combat_write(4,temp,TRUE);
	cmbt_pause(1);
}

int _PASCAL move_monster_randomly(MONSTER *mnst)
{
	int mx=mnst->x;
	int my=mnst->y;
	int moved=FALSE;
	char temp[50];
	int i;
	static struct _XY {
						 int x,y;

					  } xy[]={ 0, 1,	/* S  */
							   1, 1,	/* SE */
							  -1, 1,	/* SW */
							   1, 0,	/* E  */
							  -1, 0,	/* W  */
							   1,-1,	/* NE */
							  -1,-1,	/* NW */
							   0,-1};   /* N  */

	if (percent()>10)
	{
		for (i=0; i<15; i++)
		{
			i=rand()%SIZE(xy);

			if (cmbt_area_contents(mx+xy[i].x,my+xy[i].y)==IS_EMPTY)
			{
				moved=TRUE;

				mx+=xy[i].x;
				my+=xy[i].y;

				break;
			}
		}
	}

	if (moved)
	{
		sprintf(temp,"%s moves!",mnst->name);

		combat_write(4,temp,TRUE);

		cmbt_area_nullify_square(mnst->x,mnst->y);

		pos_one_monster(mnst,mx,my);

		mnst->x=mx;
		mnst->y=my;

		move_monster_sound();

		cmbt_pause(1);
	}

	return(moved);
}

void _PASCAL get_new_monster_location(MONSTER *mnst)
{
	int px,py,mx,my;
	int n,s,e,w;		/* Monster direction to reach player */
	int moved;

	n=s=e=w=moved=FALSE;

	mx=mnst->x;
	my=mnst->y;

	if (mnst->opponent!=NULL)
	{
		if (mnst->fleeing)
		{
			mnst->opponent=(PLAYER *)NULL;
		}
		else
		if (player_is_dead(mnst->opponent))
		{
			mnst->opponent=(PLAYER *)NULL;

			if (mnst->intelligence>=9)
				build_monster_get_opponent(mnst);
		}
	}

	if (mnst->opponent!=NULL)
	{
		px=mnst->opponent->x;
		py=mnst->opponent->y;
	}
	else
	{
		get_party_combat_location(&px,&py);

		if (percent()>60)
		{
			px+=plus_or_minus_one();
			py+=plus_or_minus_one();
		}			
	}

	if (mnst->fleeing)
	{
		px=mnst->flee_x;
		py=mnst->flee_y;
	}

	if (mx>px)
		w=TRUE;

	if (mx<px)
		e=TRUE;

	if (my>py)
		n=TRUE;

	if (my<py)
		s=TRUE;


	if (n && e)
	{
		if (cmbt_area_contents(mx+1,my-1)==IS_EMPTY)
		{
			mnst->x=mx+1;
			mnst->y=my-1;
			moved=TRUE;
		}
	}
	else
	if (n && w)
	{
		if (cmbt_area_contents(mx-1,my-1)==IS_EMPTY)
		{
			mnst->x=mx-1;
			mnst->y=my-1;
			moved=TRUE;
		}
	}
	else
	if (s && e)
	{
		if (cmbt_area_contents(mx+1,my+1)==IS_EMPTY)
		{
			mnst->x=mx+1;
			mnst->y=my+1;
			moved=TRUE;
		}
	}
	else
	if (s && w)
	{
		if (cmbt_area_contents(mx-1,my+1)==IS_EMPTY)
		{
			mnst->x=mx-1;
			mnst->y=my+1;
			moved=TRUE;
		}
	}

	if (!moved)
	{
		if (s)
		{
			if (cmbt_area_contents(mx,my+1)==IS_EMPTY)
			{
				mnst->y=my+1;
				moved=TRUE;
			}
		}
	}

	if (!moved)
	{
		if (n)
		{
			if (cmbt_area_contents(mx,my-1)==IS_EMPTY)
			{
				mnst->y=my-1;
				moved=TRUE;
			}
		}
	}

	if (!moved)
	{
		if (e)
		{
			if (cmbt_area_contents(mx+1,my)==IS_EMPTY)
			{
				mnst->x=mx+1;
				moved=TRUE;
			}
		}
	}

	if (!moved)
	{
		if (w)
		{
			if (cmbt_area_contents(mx-1,my)==IS_EMPTY)
			{
				mnst->x=mx-1;
				moved=TRUE;
			}
		}
	}
}
