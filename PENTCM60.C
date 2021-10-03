#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	Player Combat Options
 *
 */

void _PASCAL cmbt_handle_options(PLAYER *adv)
{
	GWINDOW win;
	int fin=FALSE;
	int option;
	unsigned char *opt1="TSBMPHWKRCUNOEI ";
	char temp[60];
	int hostile=FALSE;
	static int boundary[]={214,31,237,50,
						   249,30,267,50,
						   276,30,306,50,
						   213,59,239,71,
						   250,57,268,71,
						   281,55,300,71,
						   218,77,233,94,
						   244,79,274,94,
						   284,77,300,94,
						   218,102,235,122,
						   250,102,268,122,
						   281,103,305,122,
						   219,130,234,147,
						   250,130,268,147,
						   280,125,307,147,
						   251,150,267,164,
							-1,-1,-1,-1};

	static int b2[]={0,0,319,199,
					 -1,-1,-1,-1};

	win.x1=27;
	win.y1=4;
	win.x2=40;
	win.y2=22;
	win.back=0;
	win.border=5;

	if (adv->nclass==ILLUSIONIST)
	{
		if (adv->in_effect.allys_dancing_dagger+
			adv->in_effect.allys_dancing_mace  +
			adv->in_effect.allys_dancing_sabre)
		{
			cmbt_buzz_a_square(adv->x,adv->y,BUZZ_SHORT);
			ALLYS_spell_actually_hit(adv);
		}
	}

	if (are_all_monsters_dead_or_flown())
		return;

	while (!fin)
	{
		sprintf(temp,"%s%s turn!",adv->name,end_s(adv->name));
		combat_write(9,temp,FALSE);

		adv->is_parrying=FALSE;

		cmbt_buzz_a_square(adv->x,adv->y,BUZZ_LONG);

		cmbt_grab_image(adv->x,adv->y);
		draw_choose(adv->x,adv->y,14);

		make_gwindow(&win);

		cmbt_handle_options_draw_im();

		option=mouse_in_range(boundary,opt1,"ªªªªªªªªªªªªªªª\xD0");

		cmbt_replace_image(adv->x,adv->y);
		kill_gwindow(&win);

		switch(option)
		{
			case 0 : fin=cmbt_thrust(adv);      hostile=TRUE; break;
			case 1 : fin=cmbt_slash(adv);       hostile=TRUE; break;
			case 2 : fin=cmbt_bludgeon(adv);    hostile=TRUE; break;
			case 3 : fin=cmbt_missile(adv);     hostile=TRUE; break;
			case 4 : fin=cmbt_parry(adv);       hostile=FALSE;break;
			case 5 : fin=cmbt_punch(adv);       hostile=TRUE; break;
			case 6 : fin=cmbt_swap_weapon(adv); hostile=FALSE;break;
			case 7 : fin=cmbt_backstab(adv);    hostile=TRUE; break;
			case 8 : fin=cmbt_turn(adv);        hostile=TRUE; break;
			case 9 : fin=cmbt_cast(adv);        hostile=TRUE; break;
			case 10: fin=cmbt_use(adv);         hostile=TRUE; break;
			case 11: fin=cmbt_potion(adv);      hostile=TRUE; break;
			case 12: fin=cmbt_move(adv);        hostile=FALSE;break;
			case 13: fin=cmbt_sneak(adv);       hostile=TRUE; break;
			case 14: fin=cmbt_inspect(adv);     hostile=FALSE;break;
			case 15: fin=hostile=FALSE;
					 (void)mouse_in_range(b2,STR_ALL_DIGITS,"");
					 break;
		}

		if (hostile && !party_is_hostile)
			party_is_hostile=TRUE;

		if (option!=4 && option!=14 && option!=11)
			adv->is_parrying=FALSE;

		if (adv->sneaking)
			if (option!=13 && option!=14 && option!=11 && option!=5)
				adv->sneaking=FALSE;

		if (!fin)
			short_prompt_sound();
	}
}

int _PASCAL _NEAR cmbt_parry(PLAYER *adv)
{
	char temp[40];

	sprintf(temp,"%s chooses to parry.",adv->he_she);
	combat_write(11,temp,TRUE);

	adv->is_parrying=TRUE;

	return(TRUE);
}

int _PASCAL cmbt_use(PLAYER *adv)
{
	return(actually_use_item(adv));
}

int _PASCAL _NEAR cmbt_swap_weapon(PLAYER *adv)
{
	GWINDOW win;
	int opt;
	int res;
	char temp[50];
	static int boundary[]={216,40,248,75,
						   266,54,280,75,
						   237,82,273,94,
							-1,-1,-1,-1};

	if (bard_is_singing(adv,"swap weapons"))
		return(FALSE);

	win.x1=28;
	win.y1=6;
	win.x2=38;
	win.y2=14;
	win.back=0;
	win.border=8;

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+2,win.y1*8+2,"RINGWEAP");

	opt=mouse_in_range(boundary,"WRQ","");

	kill_gwindow(&win);

	switch(opt)
	{
		case 0 : sprintf(temp,"%s selects a weapon.",adv->he_she);
				 combat_write(11,temp,TRUE);

				 res=ready_an_adventurer_weapon(adv);

				 break;

		case 1 : sprintf(temp,"%s looks for %s rings.",
							 adv->he_she,
							 adv->his_her);

				 combat_write(11,temp,TRUE);

				 res=ready_an_adventurer_ring(adv);

				 break;

		default: res=FALSE;
				 break;
	}

	return(res);
}

int _PASCAL _NEAR cmbt_turn(PLAYER *adv)
{
    MONSTER *mnst;
    int can_turn=FALSE;
	unsigned int x,y;
	int fin;
	int chance;
	char temp[40];

	sprintf(temp,"%s attempts to turn.",adv->he_she);
	combat_write(11,temp,FALSE);

    if (adv->nclass!=CRUSADER && adv->nclass!=PRIEST)
    {
		cmbt_bad_msg("Thou hast no ability to turn!",TRUE);

		return(FALSE);
	}

	if (!player_is_carrying(adv,RELIGIOUS_SYMBOL))
	{
		cmbt_bad_msg("Thou hath no religious symbol!",TRUE);

		return(FALSE);
	}

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if (x==adv->x && y==adv->y)
	{
		fin=FALSE;
	}
	else
	{
        mnst=cmbt_area[x][y].occ.monster;

		if (is_undead_or_demon(mnst))
			can_turn=TRUE;

		chance=(effective_turn_undead(adv))-(mnst->hd*4);

		if (monster_is_weak(mnst))
			chance+=10;

		if ((percent()<=chance) && can_turn)
		{
			cmbt_monster_is_slain(adv,mnst);

			combat_write(15,"Thy foe crumbles to dust!",TRUE);

			good_sound();
		}
		else
		{
			spell_does_naught();
		}

		cmbt_pause(1);

		fin=TRUE;
    }

	return(fin);
}

int _PASCAL _NEAR cmbt_cast(PLAYER *adv)
{
	char temp[40];

	if (bard_is_singing(adv,"cast a spell"))
		return(FALSE);

	sprintf(temp,"%s attempts a spell",adv->he_she);
	combat_write(11,temp,FALSE);

	return(actually_cast_a_spell(adv));
}

int _PASCAL _NEAR cmbt_potion(PLAYER *adv)
{
	char temp[40];

	if (bard_is_singing(adv,"drink a potion"))
		return(FALSE);

	sprintf(temp,"%s chooses to use a potion",adv->he_she);
	combat_write(11,temp,TRUE);

	return(get_potion_to_drink(adv,DRINK_POTION));
}

int _PASCAL _NEAR cmbt_move(PLAYER *adv)
{
	return(cmbt_move_or_sneak(adv,MOVE_MOVE));
}

int _PASCAL _NEAR cmbt_sneak(PLAYER *adv)
{
	if (bard_is_singing(adv,"sneak"))
		return(FALSE);

	return(cmbt_move_or_sneak(adv,MOVE_SNEAK));
}

int _PASCAL _NEAR cmbt_move_or_sneak(PLAYER *adv,int what)
{
	int fin=TRUE;
	char temp[60];
	unsigned int startx=adv->x;
	unsigned int starty=adv->y;
	unsigned int newx,newy;

	if (what==MOVE_SNEAK && adv->nclass!=THIEF)
	{
		cmbt_bad_msg("Only thieves can sneak!",TRUE);
		return(FALSE);
	}

	newx=startx;
	newy=starty;

	sprintf(temp,"%s chooses to %s",
			   adv->he_she,
			   what==MOVE_SNEAK?"sneak":"move");

	combat_write(11,temp,TRUE);

	cmbt_select_sq_around_player(what==MOVE_SNEAK?1:(effective_speed(adv)>10?2:1),
								 &newx,
								 &newy,
								 FALSE,
								 FALSE,
								 TRUE);

	if (startx==newx && starty==newy)	  /* No move! */
	{
		fin=FALSE;

		cmbt_area_nullify_square(adv->x,adv->y);
		pos_party_member(adv,adv->x,adv->y);
	}
	else
	{
		fin=TRUE;

		adv->x=newx;
		adv->y=newy;

		cmbt_area_nullify_square(startx,starty);
		cmbt_area_nullify_square(adv->x,adv->y);
		pos_party_member(adv,adv->x,adv->y);
	}

	if (what==MOVE_SNEAK)
		adv->sneaking=TRUE;
	else
		adv->sneaking=FALSE;

	return(fin);
}

int _PASCAL _NEAR cmbt_inspect(PLAYER *adv)
{
	show_adventurer(adv);

	return(FALSE);
}
