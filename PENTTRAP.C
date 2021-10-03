#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

static char *DEAD_STR="%s art dead!";

void _PASCAL land_on_trap(int type)
{
	char trap_name[60];
	static char temp[180];
	int i;
	int trap_spotted=ERR;
	int prot_traps;
	int poor_sod;
	static char *verb[]={"notices",
						 "sees",
						 "spots",
						 "glimpses"};

	strcpy(trap_name,get_trap_name(type));

	if (dungeon.map[the_party.dungeon_level]
				   [the_party.dungeon_x]
				   [the_party.dungeon_y].trap_triggered)
	{
		sprintf(temp,"Remains of %s %s!",
				isvowel((int)*trap_name)?"an":"a",
				trap_name);

		SCROLL(1,1,temp);
		return;
	}

	display_trap_window();

	prot_traps=check_party_globals_in_effect(IN_EFFECT_PROT_FROM_TRAPS);

	if (prot_traps!=ERR)
	{
		sprintf(temp,"Luckily, %s hath cast Protection from Traps!",
					TPP[prot_traps].name);

		GX(temp,GOOD);

		return;
	}

	for (i=0; i<2; i++)
		if (spot_trap(&TPP[i]))
			trap_spotted=i;

	if (trap_spotted==ERR)
	{
		trigger_trap(type);
	}
	else
	{

		sprintf(temp,"%s %s %s %s in ye dim dungeon light.",
				TPP[trap_spotted].name,
				verb[rand()%4],
				isvowel((int)*trap_name)?"an":"a",
				trap_name);

		SCROLL(1,14,temp);

		good_sound();

		pause(2);

		poor_sod=select_person_to_disarm_trap();
		disarm_trap(&TPP[poor_sod],type);
	}
}

void _PASCAL disarm_trap(PLAYER *adv,int type)
{
	char temp[120];
	static SPELL_NAME spell={DISPEL_TRAP,"Dispel Trap"};
	static char *adj[]={"dexterity",
						"ability",
						"aptitude",
						"knowledge",
						"prowess",
						"mastery",
						"finesse",
						"talent",
						"expertise"};

	int disarm_trap_per=effective_disarm_trap(adv);

	if (adv->wizard_spells[DISPEL_TRAP] &&      /* Can use Dispel Trap? */
		adv->current_sorcery_points>=2)
	{
		if (gget_yn("Doth ye cast Dispel Trap?"))
		{
			if (cast_DISPEL_TRAP(adv,&spell))
			{
				sprintf(temp,"%s hath dispelled ye trap!",adv->name);

				SCROLL(1,14,temp);

				good_sound();

				add_to_professionalism(adv,1);
				add_xp_to_party(100L);

				return;
			}
		}
	}

	if (percent()<=disarm_trap_per)                 /* OK!         */
	{
		sprintf(temp,"With great %s, %s disarms ye trap!",
				adj[rand()%9],
				adv->name);

		SCROLL(1,14,temp);

		add_to_professionalism(adv,1);
		add_xp_to_party(900L);

		good_sound();
	}
	else                                        /* ..oopppsss! */
	{
		sprintf(temp,"..ooppsss! %s fails to disarm ye trap!",
				adv->name);

		SCROLL(1,0,temp);
		solemn_sound();

		pause(1);

		trigger_trap(type);
	}
}

int _PASCAL spot_trap(PLAYER *adv)
{
	return(percent()<=effective_find_trap(adv));
}

int _PASCAL select_person_to_disarm_trap()
{
	int select=ERR;

	while (select<0)
		select=adv_select_adventurer("Who Disarms","ye Trap?",TRUE);

	return(select);
}

char *get_trap_name(int type)
{
	static char name[30];

	switch(type)
	{
		case TRAP_SPEAR             : strcpy(name,"Spear");             break;
		case TRAP_ACID_SQUIRT       : strcpy(name,"Acid");              break;
		case TRAP_ARROW             : strcpy(name,"Arrow");             break;
		case TRAP_POISON_ARROW      : strcpy(name,"Poison Arrow");      break;
		case TRAP_GAS               : strcpy(name,"Gas");               break;
		case TRAP_PIT               : strcpy(name,"Pit");               break;
		case TRAP_SPIKED_PIT        : strcpy(name,"Spiked Pit");        break;
		case TRAP_POISON_SPIKED_PIT : strcpy(name,"Poisoned Spike Pit");break;
		case TRAP_ROCKS             : strcpy(name,"Falling Rock");      break;
		case TRAP_ELECTRICITY       : strcpy(name,"Electricity");       break;
		case TRAP_FIREBALL          : strcpy(name,"Fireball");          break;
	}

	strcat(name," Trap");

	return(name);
}

void _PASCAL trigger_trap(int type)
{
	switch(type)
	{
		case TRAP_SPEAR             : trigger_TRAP_SPEAR();            break;
		case TRAP_ACID_SQUIRT       : trigger_TRAP_ACID_SQUIRT();      break;
		case TRAP_ARROW             : trigger_TRAP_ARROW();            break;
		case TRAP_POISON_ARROW      : trigger_TRAP_POISON_ARROW();     break;
		case TRAP_GAS               : trigger_TRAP_GAS();              break;
		case TRAP_PIT               : trigger_TRAP_PIT();              break;
		case TRAP_SPIKED_PIT        : trigger_TRAP_SPIKED_PIT();       break;
		case TRAP_POISON_SPIKED_PIT : trigger_TRAP_POISON_SPIKED_PIT();break;
		case TRAP_ROCKS             : trigger_TRAP_ROCKS();            break;
		case TRAP_ELECTRICITY       : trigger_TRAP_ELECTRICITY();      break;
		case TRAP_FIREBALL          : trigger_TRAP_FIREBALL();         break;
	}

	(void)is_all_party_dead();
}

void _PASCAL trigger_TRAP_SPEAR()			 /* One Person Damage */
{											 /* 1-8 damage		  */
	char *mess=STR_TRAP_SPEAR;
	int person;
	char temp[120];
	int damage;

	trigger_trap_message(mess);

	person=get_random_live_person();

	if (person==ERR)
		return;

	if (percent()<=effective_trap_save(&TPP[person],TRAP_SPEAR))
	{
		sprintf(temp,"With great agility, %s dodges ye deadly spear!",
				TPP[person].name);

		SCROLL(1,14,temp);

		good_sound();
	}
	else
	{
		damage=get_dice_roll(8,1,0);
		damage=modified_damage(damage);

		sprintf(temp,"Ye spear hits %s, sending %s to ye ground, "
					 "inflicting %d HP of damage.",
					 TPP[person].name,
					 TPP[person].him_her,
					 damage);

		SCROLL(1,0,temp);

		bad_sound();

		reduce_hp(&TPP[person],
				  damage,
				  FROM_TRAP);
	}
}

void _PASCAL trigger_TRAP_ACID_SQUIRT() 	 /* One Person Damage */
{											 /* 2-16 damage 	  */
	char *mess=STR_TRAP_ACID;
	int person;
	char temp[120];
	int damage;

	trigger_trap_message(mess);

	person=get_random_live_person();

	if (person==ERR)
		return;

	if (percent()<=effective_trap_save(&TPP[person],TRAP_ACID_SQUIRT))
	{
		sprintf(temp,"With superb reflexes, %s dodges ye squirt of acid!",
				TPP[person].name);

		SCROLL(1,14,temp);

		good_sound();
	}
	else
	{
		damage=get_dice_roll(8,2,0);
		damage=modified_damage(damage);

		sprintf(temp,"Ye acid splatters %s, inflicting %d HP of damage.",
					 TPP[person].name,
					 damage);

		SCROLL(1,0,temp);

		bad_sound();

		reduce_hp(&TPP[person],
				  damage,
				  FROM_TRAP);
	}
}

void _PASCAL trigger_TRAP_ARROW()			 /* One Person Damage */
{											 /* 1-6 damage		  */
	int person;
	char temp[120];
	int damage;
	char *mess=STR_TRAP_ARROW;

	trigger_trap_message(mess);

	person=get_random_live_person();

	if (person==ERR)
		return;

	if (percent()<=effective_trap_save(&TPP[person],TRAP_ARROW))
	{
		sprintf(temp,"Ye gods smile upon %s ye arrow misses %s!",
				TPP[person].name,
				TPP[person].him_her);

		SCROLL(1,14,temp);

		good_sound();
	}
	else
	{
		damage=get_dice_roll(6,1,0);
		damage=modified_damage(damage);

		sprintf(temp,"Ye arrow hits %s, inflicting %d HP of damage.",
					 TPP[person].name,
					 damage);

		SCROLL(1,0,temp);

		bad_sound();

		reduce_hp(&TPP[person],
				  damage,
				  FROM_TRAP);
	}
}

void _PASCAL trigger_TRAP_POISON_ARROW()	 /* One Person Damage */
{											 /* 1-6 damage		  */
	int person; 							 /* Check for Poison! */
	char *mess=STR_TRAP_POISON_ARROW;
	char temp[120];
	char poison_mess[60];
	int damage;
	int poisoned;

	trigger_trap_message(mess);

	person=get_random_live_person();

	if (person==ERR)
		return;

	if (percent()<=effective_trap_save(&TPP[person],TRAP_POISON_ARROW))
	{
		sprintf(temp,"What luck! As ye poisoned arrow misses %s!",
				TPP[person].name);

		SCROLL(1,14,temp);

		good_sound();
	}
	else
	{
		damage=get_dice_roll(6,1,0);
		damage=modified_damage(damage);

		poisoned=(percent()>effective_poison_immunity(&TPP[person]));

		if (!TPP[person].is_poisoned)
			poisoned=FALSE;

		if (poisoned)
		{
			TPP[person].is_poisoned=TRUE;

			sprintf(poison_mess,". Poison seeps through %s veins.",
						TPP[person].his_her);
		}
		else
			strcpy(poison_mess,".");

		sprintf(temp,"Ye poison arrow hits %s, inflicting %d HP of damage%s",
					 TPP[person].name,
					 damage,
					 poison_mess);

		SCROLL(1,0,temp);

		bad_sound();

		reduce_hp(&TPP[person],
				  damage,
				  FROM_TRAP);
	}
}

void _PASCAL trigger_TRAP_GAS() 			 /* Global Damage */
{											 /* 1-10 damage   */
	char *mess=STR_TRAP_GAS;
	GWINDOW win;
	char temp[60];
	char dam_desc[60];
	int i;
	int damage;
	int dead;
	int inj=FALSE;

	trigger_trap_message(mess);

	create_damage_window(&win);

	_settextcolor(DAMAGE_WINDOW_COL);

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (percent()<=effective_trap_save(&TPP[i],TRAP_GAS))
			{
				strcpy(dam_desc,"avoids inhaling!");
			}
			else
			{
				damage=get_dice_roll(10,1,0);
				damage=modified_damage(damage);

				inj=TRUE;

				reduce_hp(&TPP[i],
						  damage,
						  NO_DISPLAY);

				dead=FALSE;

				if (TPP[i].current_hp<=0)
				{
					dead=TRUE;

					player_has_died_set(&TPP[i]);
				}

				sprintf(dam_desc,"suffers %d damage%s",
						damage,
						dead?" & dies.":".");
			}

			sprintf(temp,"%s %s",TPP[i].name,dam_desc);
		}
		else
		{
			sprintf(temp,DEAD_STR,TPP[i].name);
		}

		_settextposition(win.y1+DAMAGE_WINDOW_Y+i,win.x1+1);
		_outtext(temp);
	}

	damage_window_wait_kill(&win,inj);
}

void _PASCAL trigger_TRAP_PIT() 			 /* Global Damage */
{											 /* 1-8 damage	  */
	char *mess=STR_TRAP_PIT;
	GWINDOW win;
	char temp[60];
	char dam_desc[60];
	int i;
	int damage;
	int dead;
	int inj=FALSE;

	trigger_trap_message(mess);

	create_damage_window(&win);

	_settextcolor(DAMAGE_WINDOW_COL);

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (percent()<=effective_trap_save(&TPP[i],TRAP_PIT))
			{
				strcpy(dam_desc,"luckily jumps aside!");
			}
			else
			{
				damage=get_dice_roll(8,1,0);
				damage=modified_damage(damage);

				inj=TRUE;

				reduce_hp(&TPP[i],
						  damage,
						  NO_DISPLAY);

				dead=FALSE;

				if (TPP[i].current_hp<=0)
				{
					dead=TRUE;

					player_has_died_set(&TPP[i]);
				}

				sprintf(dam_desc,"suffers %d damage%s",
						damage,
						dead?" & dies.":".");
			}

			sprintf(temp,"%s %s",TPP[i].name,dam_desc);
		}
		else
		{
			sprintf(temp,DEAD_STR,TPP[i].name);
		}

		_settextposition(win.y1+DAMAGE_WINDOW_Y+i,win.x1+1);
		_outtext(temp);
	}

	damage_window_wait_kill(&win,inj);
}

void _PASCAL trigger_TRAP_SPIKED_PIT()		 /* Global Damage */
{											 /* 2-16 damage   */
	char *mess=STR_TRAP_SPIKED_PIT;
	GWINDOW win;
	char temp[60];
	char dam_desc[60];
	int i;
	int damage;
	int dead;
	int inj=FALSE;

	trigger_trap_message(mess);

	create_damage_window(&win);

	_settextcolor(DAMAGE_WINDOW_COL);

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (percent()<=effective_trap_save(&TPP[i],TRAP_SPIKED_PIT))
			{
				strcpy(dam_desc,"doesn't fall in!");
			}
			else
			{
				damage=get_dice_roll(8,2,0);
				damage=modified_damage(damage);

				inj=TRUE;

				reduce_hp(&TPP[i],
						  damage,
						  NO_DISPLAY);

				dead=FALSE;

				if (TPP[i].current_hp<=0)
				{
					dead=TRUE;

					player_has_died_set(&TPP[i]);
				}

				sprintf(dam_desc,"suffers %d damage%s",
						damage,
						dead?" & dies.":".");
			}

			sprintf(temp,"%s %s",TPP[i].name,dam_desc);
		}
		else
		{
			sprintf(temp,DEAD_STR,TPP[i].name);
		}

		_settextposition(win.y1+DAMAGE_WINDOW_Y+i,win.x1+1);
		_outtext(temp);
	}

	damage_window_wait_kill(&win,inj);
}

void _PASCAL trigger_TRAP_POISON_SPIKED_PIT() /* Global Damage */
{											  /* 2-16 damage   */
	char *mess=STR_TRAP_SPIKED_POISON_PIT;	  /* Poison Check! */
	GWINDOW win;
	char temp[60];
	char dam_desc[60];
	int i;
	int damage;
	int dead;
	int poisoned;
	int inj=FALSE;

	trigger_trap_message(mess);

	create_damage_window(&win);

	_settextcolor(DAMAGE_WINDOW_COL);

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (percent()<=effective_trap_save(&TPP[i],TRAP_POISON_SPIKED_PIT))
			{
				strcpy(dam_desc,"luckily jumps aside!");
			}
			else
			{
				damage=get_dice_roll(8,2,0);
				damage=modified_damage(damage);

				inj=TRUE;

				reduce_hp(&TPP[i],
						  damage,
						  NO_DISPLAY);

				dead=poisoned=FALSE;

				if (TPP[i].current_hp<=0)
				{
					dead=TRUE;

					player_has_died_set(&TPP[i]);
				}
				else
				{
					if (!TPP[i].is_dead)
					{
						TPP[i].is_poisoned=TRUE;
						poisoned=TRUE;
					}
				}

				sprintf(dam_desc,"suffers %d damage%s%s",
						damage,
						dead?" & dies.":".",
						poisoned?" Poison!":"");
			}

			sprintf(temp,"%s %s",TPP[i].name,dam_desc);
		}
		else
		{
			sprintf(temp,DEAD_STR,TPP[i].name);
		}

		_settextposition(win.y1+DAMAGE_WINDOW_Y+i,win.x1+1);
		_outtext(temp);
	}

	damage_window_wait_kill(&win,inj);
}

void _PASCAL trigger_TRAP_ROCKS()			  /* Global Damage */
{											  /* 2-16 damage   */
	char *mess=STR_TRAP_ROCKS;
	GWINDOW win;
	char temp[60];
	char dam_desc[60];
	int i;
	int damage;
	int dead;
	int inj=FALSE;

	trigger_trap_message(mess);

	create_damage_window(&win);

	_settextcolor(DAMAGE_WINDOW_COL);

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (percent()<=effective_trap_save(&TPP[i],TRAP_ROCKS))
			{
				strcpy(dam_desc,"dodges ye debris!");
			}
			else
			{
				damage=get_dice_roll(8,2,0);
				damage=modified_damage(damage);

				if (is_wearing_metal(&TPP[i]))
				{
					damage/=3;       /* Div by 1.5 */
					damage*=2;

					if (damage<=0)
						damage=1;
				}

				if (player_is_wearing(&TPP[i],HELMET))
				{
					damage/=3;       /* Div by 1.5 */
					damage*=2;

					if (damage<=0)
						damage=1;
				}

				inj=TRUE;

				reduce_hp(&TPP[i],
						  damage,
						  NO_DISPLAY);

				dead=FALSE;

				if (TPP[i].current_hp<=0)
				{
					dead=TRUE;

					player_has_died_set(&TPP[i]);
				}

				sprintf(dam_desc,"suffers %d damage%s",
						damage,
						dead?" & dies.":".");
			}

			sprintf(temp,"%s %s",TPP[i].name,dam_desc);
		}
		else
		{
			sprintf(temp,DEAD_STR,TPP[i].name);
		}

		_settextposition(win.y1+DAMAGE_WINDOW_Y+i,win.x1+1);
		_outtext(temp);
	}

	damage_window_wait_kill(&win,inj);
}

void _PASCAL trigger_TRAP_ELECTRICITY() 	  /* Global Damage		 */
{											  /* 2-16 damage		 */
	char *mess=STR_TRAP_ELECTRICITY;		  /* Check metal armour  */
	GWINDOW win;
	char temp[60];
	char dam_desc[60];
	int i;
	int damage;
	int dead;
	int inj=FALSE;

	trigger_trap_message(mess);

	create_damage_window(&win);

	_settextcolor(DAMAGE_WINDOW_COL);

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (percent()<=effective_trap_save(&TPP[i],TRAP_ELECTRICITY))
			{
				strcpy(dam_desc,"misses ye bolt!");
			}
			else
			{
				damage=get_dice_roll(8,2,0);
				damage=modified_damage(damage);

				if (is_wearing_metal(&TPP[i]))
					damage*=2;

				inj=TRUE;

				reduce_hp(&TPP[i],
						  damage,
						  NO_DISPLAY);

				dead=FALSE;

				if (TPP[i].current_hp<=0)
				{
					dead=TRUE;

					player_has_died_set(&TPP[i]);
				}

				sprintf(dam_desc,"suffers %d damage%s",
						damage,
						dead?" & dies.":".");
			}

			sprintf(temp,"%s %s",TPP[i].name,dam_desc);
		}
		else
		{
			sprintf(temp,DEAD_STR,TPP[i].name);
		}

		_settextposition(win.y1+DAMAGE_WINDOW_Y+i,win.x1+1);
		_outtext(temp);
	}

	damage_window_wait_kill(&win,inj);
}

void _PASCAL trigger_TRAP_FIREBALL()		  /* Global Damage */
{											  /* 5-15 damage   */
	char *mess=STR_TRAP_FIREBALL;
	GWINDOW win;
	char temp[60];
	char dam_desc[60];
	int i;
	int damage;
	int dead;
	int inj=FALSE;

	trigger_trap_message(mess);

	create_damage_window(&win);

	_settextcolor(DAMAGE_WINDOW_COL);

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (percent()<=effective_trap_save(&TPP[i],TRAP_FIREBALL))
			{
				strcpy(dam_desc,"dodges ye inferno!");
			}
			else
			{
				damage=get_dice_roll(6,2,3);
				damage=modified_damage(damage);

				inj=TRUE;

				reduce_hp(&TPP[i],
						  damage,
						  NO_DISPLAY);

				dead=FALSE;

				if (TPP[i].current_hp<=0)
				{
					dead=TRUE;

					player_has_died_set(&TPP[i]);
				}

				sprintf(dam_desc,"suffers %d damage%s",
						damage,
						dead?" & dies.":".");
			}

			sprintf(temp,"%s %s",TPP[i].name,dam_desc);
		}
		else
		{
			sprintf(temp,DEAD_STR,TPP[i].name);
		}

		_settextposition(win.y1+DAMAGE_WINDOW_Y+i,win.x1+1);
		_outtext(temp);
	}

	damage_window_wait_kill(&win,inj);
}

void _PASCAL trigger_trap_message(char *mess)
{
	SCROLL(1,7,mess);

	bad_sound();

	pause(2);
}

void _PASCAL display_trap_window()
{
	GWINDOW trap_window;

	trap_window.x1=12;
	trap_window.y1=5;
	trap_window.x2=28;
	trap_window.y2=11;
	trap_window.back=0;
	trap_window.border=14;

	make_gwindow(&trap_window);

	print_trap_sign(111,trap_window.y1*8+2);

	trap_sound();

	pause(2);

	kill_gwindow(&trap_window);
}
