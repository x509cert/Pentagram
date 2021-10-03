#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

static
LEVELS level_warrior    [MAX_LEVEL] ={{ 0L,         2000L   },
									  { 2001L,      4000L   },
									  { 4001L,      8000L   },
									  { 8001L,      18000L  },
									  { 18001L,     35000L  },
									  { 35001L,     70000L  },
									  { 70001L,     125000L },
									  { 125001L,    250000L },
									  { 250001L,    500000L },
									  { 500001L,    750000L },
									  { 750001L,    1000000L},
									  { 1000001L,   1250000L},
									  { 1250001L,   1500000L},
									  { 1500001L,   1750000L},
									  { 1750001L,   2000000L}};
static
LEVELS level_priest     [MAX_LEVEL] ={{ 0L,         1500L   },
									  { 1501L,      3000L   },
									  { 3001L,      6000L   },
									  { 6001L,      13000L  },
									  { 13001L,     27500L  },
									  { 27501L,     55000L  },
									  { 55001L,     110000L },
									  { 110001L,    225000L },
									  { 225001L,    450000L },
									  { 450001L,    675000L },
									  { 675001L,    900000L },
									  { 900001L,    1200000L},
									  { 1200001L,   1500000L},
									  { 1500001L,   1800000L},
									  { 1800001L,   2100000L}};
static
LEVELS level_wizard     [MAX_LEVEL] ={{ 0L,         2500L   },
									  { 2501L,      5000L   },
									  { 5001L,      10000L  },
									  { 10001L,     22500L  },
									  { 22501L,     40000L  },
									  { 40001L,     60000L  },
									  { 60001L,     90000L  },
									  { 90001L,     135000L },
									  { 135001L,    250000L },
									  { 250001L,    375000L },
									  { 375001L,    750000L },
									  { 750001L,    1125000L},
									  { 1125001L,   1500000L},
									  { 1500001L,   1875000L},
									  { 1875001L,   2250000L}};

static
LEVELS level_druid      [MAX_LEVEL] ={{ 0L,         1250L   },
									  { 1251L,      2500L   },
									  { 2501L,      5000L   },
									  { 5001L,      10000L  },
									  { 10001L,     20000L  },
									  { 20001L,     42500L  },
									  { 42501L,     70000L  },
									  { 70001L,     110000L },
									  { 110001L,    160000L },
									  { 160001L,    220000L },
									  { 220001L,    440000L },
									  { 440001L,    660000L },
									  { 660001L,    880000L },
									  { 880001L,    1100000L},
									  { 1100001L,   1320000L}};
static
LEVELS level_thief      [MAX_LEVEL] ={{ 0L,         1250L   },
									  { 1251L,      2500L   },
									  { 2501L,      5000L   },
									  { 5001L,      10000L  },
									  { 10001L,     20000L  },
									  { 20001L,     42500L  },
									  { 42501L,     70000L  },
									  { 70001L,     110000L },
									  { 110001L,    160000L },
									  { 160001L,    220000L },
									  { 220001L,    440000L },
									  { 440001L,    660000L },
									  { 660001L,    880000L },
									  { 880001L,    1100000L},
									  { 1100001L,   1320000L}};

static
LEVELS level_bard		[MAX_LEVEL] ={{ 0L, 		1250L	},
									  { 1251L,      2500L   },
									  { 2501L,      5000L   },
									  { 5001L,      10000L  },
									  { 10001L,     20000L  },
									  { 20001L,     42500L  },
									  { 42501L,     70000L  },
									  { 70001L,     110000L },
									  { 110001L,    160000L },
									  { 160001L,    220000L },
									  { 220001L,    440000L },
									  { 440001L,    660000L },
									  { 660001L,    880000L },
									  { 880001L,    1100000L},
									  { 1100001L,   1320000L}};
static
LEVELS level_ranger     [MAX_LEVEL] ={{ 0L,         2250L   },
									  { 2251L,      4500L   },
									  { 4501L,      10000L  },
									  { 10001L,     20000L  },
									  { 20001L,     40000L  },
									  { 40001L,     90000L  },
									  { 90001L,     150000L },
									  { 150001L,    225000L },
									  { 225001L,    325000L },
									  { 325001L,    650000L },
									  { 650001L,    975000L },
									  { 975001L,    1300000L},
									  { 1300001L,   1625000L},
									  { 1625001L,   1950000L},
									  { 1950001L,   2275000L}};
static
LEVELS level_crusader   [MAX_LEVEL] ={{ 0L,         2250L   },
									  { 2251L,      4500L   },
									  { 4501L,      10000L  },
									  { 10001L,     20000L  },
									  { 20001L,     40000L  },
									  { 40001L,     90000L  },
									  { 90001L,     150000L },
									  { 150001L,    225000L },
									  { 225001L,    325000L },
									  { 325001L,    650000L },
									  { 650001L,    975000L },
									  { 975001L,    1300000L},
									  { 1300001L,   1625000L},
									  { 1625001L,   1950000L},
									  { 1950001L,   2275000L}};

static
LEVELS level_monk       [MAX_LEVEL] ={{ 0L,         2250L   },
									  { 2251L,      4750L   },
									  { 4751L,      10000L  },
									  { 10001L,     22500L  },
									  { 22501L,     47500L  },
									  { 47501L,     98000L  },
									  { 98001L,     200000L },
									  { 200001L,    350000L },
									  { 350001L,    500000L },
									  { 500001L,    700000L },
									  { 700001L,    950000L },
									  { 950001L,    1250000L},
									  { 1250001L,   1750000L},
									  { 1750001L,   2250000L},
									  { 2250001L,   3250000L}};
static
LEVELS level_illusionist[MAX_LEVEL] ={{ 0L,         2500L   },
									  { 2501L,      5000L   },
									  { 5001L,      10000L  },
									  { 10001L,     22500L  },
									  { 22501L,     40000L  },
									  { 40001L,     60000L  },
									  { 60001L,     90000L  },
									  { 90001L,     135000L },
									  { 135001L,    250000L },
									  { 250001L,    375000L },
									  { 375001L,    750000L },
									  { 750001L,    1125000L},
									  { 1125001L,   1500000L},
									  { 1500001L,   1875000L},
									  { 1875001L,   2250000L}};
static
LEVELS level_hunter     [MAX_LEVEL] ={{ 0L,         1250L   },
									  { 1251L,      2500L   },
									  { 2501L,      5000L   },
									  { 5001L,      10000L  },
									  { 10001L,     20000L  },
									  { 20001L,     42500L  },
									  { 42501L,     70000L  },
									  { 70001L,     110000L },
									  { 110001L,    160000L },
									  { 160001L,    220000L },
									  { 220001L,    440000L },
									  { 440001L,    660000L },
									  { 660001L,    880000L },
									  { 880001L,    1100000L},
									  { 1100001L,   1320000L}};
static
LEVELS level_duelist    [MAX_LEVEL] ={{ 0L,         1250L   },
									  { 1251L,      2500L   },
									  { 2501L,      5000L   },
									  { 5001L,      10000L  },
									  { 10001L,     20000L  },
									  { 20001L,     42500L  },
									  { 42501L,     70000L  },
									  { 70001L,     110000L },
									  { 110001L,    160000L },
									  { 160001L,    220000L },
									  { 220001L,    440000L },
									  { 440001L,    660000L },
									  { 660001L,    880000L },
									  { 880001L,    1100000L},
									  { 1100001L,   1320000L}};

static LVL_MAGIC_TYPE cru[MAX_LEVEL]={{2,1,0,0},    /* 2  */
									  {2,0,1,0},    /* 3  */
									  {2,1,0,0},    /* 4  */
									  {2,1,1,0},    /* 5  */
									  {2,1,0,0},    /* 6  */
									  {2,1,0,0},    /* 7  */
									  {2,0,1,0},    /* 8  */
									  {2,0,1,0},    /* 9  */
									  {2,1,0,0},    /* 10 */
									  {2,0,1,0},    /* 11 */
									  {2,0,1,0},    /* 12 */
									  {2,0,0,0},    /* 13 */
									  {2,0,1,0},    /* 14 */
									  {3,0,0,0}};   /* 15 */

static LVL_MAGIC_TYPE dru[MAX_LEVEL]={{2,1,0,0},    /* 2  */
									  {2,0,1,0},    /* 3  */
									  {2,1,0,0},    /* 4  */
									  {2,0,1,0},    /* 5  */
									  {3,1,0,1},	/* 6  */
									  {2,1,1,0},    /* 7  */
									  {3,0,0,1},    /* 8  */
									  {2,0,1,0},    /* 9  */
									  {3,0,0,1},    /* 10 */
									  {4,0,0,1},    /* 11 */
									  {4,0,1,0},    /* 12 */
									  {4,0,0,1},    /* 13 */
									  {4,0,1,0},    /* 14 */
									  {5,0,0,1}};   /* 15 */

static LVL_MAGIC_TYPE hun[MAX_LEVEL]={{1,1,0,0},    /* 2  */
									  {1,1,0,0},    /* 3  */
									  {1,1,0,0},    /* 4  */
									  {2,1,0,0},    /* 5  */
									  {1,1,0,0},	/* 6  */
									  {2,0,0,0},    /* 7  */
									  {2,0,0,0},    /* 8  */
									  {2,0,0,0},    /* 9  */
									  {2,0,0,0},    /* 10 */
									  {2,0,0,0},    /* 11 */
									  {2,0,0,0},    /* 12 */
									  {2,0,0,0},    /* 13 */
									  {2,0,0,0},    /* 14 */
									  {2,0,0,0}};   /* 15 */

static LVL_MAGIC_TYPE ill[MAX_LEVEL]={{2,1,0,0},    /* 2  */
									  {3,1,1,0},    /* 3  */
									  {3,0,1,0},    /* 4  */
									  {3,1,0,0},    /* 5  */
									  {3,0,1,1},    /* 6  */
									  {3,0,0,1},    /* 7  */
									  {3,1,0,0},    /* 8  */
									  {3,0,1,0},    /* 9  */
									  {3,0,0,1},    /* 10 */
									  {4,1,0,0},    /* 11 */
									  {4,0,1,1},    /* 12 */
									  {4,0,0,1},    /* 13 */
									  {4,0,1,1},    /* 14 */
									  {5,0,1,0}};   /* 15 */

static LVL_MAGIC_TYPE pri[MAX_LEVEL]={{2,1,0,0},    /* 2  */
									  {3,1,1,0},    /* 3  */
									  {3,0,1,0},    /* 4  */
									  {3,1,0,0},    /* 5  */
									  {3,0,1,1},    /* 6  */
									  {3,1,0,1},    /* 7  */
									  {3,1,0,1},    /* 8  */
									  {3,0,1,0},    /* 9  */
									  {3,0,0,1},    /* 10 */
									  {3,1,0,0},    /* 11 */
									  {3,0,1,0},    /* 12 */
									  {3,0,1,1},    /* 13 */
									  {3,0,0,1},    /* 14 */
									  {5,0,1,0}};   /* 15 */

static LVL_MAGIC_TYPE ran[MAX_LEVEL]={{1,1,0,0},    /* 2  */
									  {2,0,1,0},    /* 3  */
									  {2,1,0,0},    /* 4  */
									  {2,1,1,0},    /* 5  */
									  {2,1,0,0},    /* 6  */
									  {2,1,0,0},    /* 7  */
									  {3,0,1,0},    /* 8  */
									  {2,0,1,0},    /* 9  */
									  {2,1,0,0},    /* 10 */
									  {2,0,1,0},    /* 11 */
									  {2,0,1,0},    /* 12 */
									  {2,0,1,0},    /* 13 */
									  {2,0,1,0},    /* 14 */
									  {3,0,0,0}};   /* 15 */

static LVL_MAGIC_TYPE wiz[MAX_LEVEL]={{2,1,0,0},    /* 2  */
									  {3,1,1,0},    /* 3  */
									  {3,0,1,0},    /* 4  */
									  {3,1,1,0},    /* 5  */
									  {3,0,1,1},    /* 6  */
									  {3,1,0,1},    /* 7  */
									  {3,1,0,1},    /* 8  */
									  {3,0,1,0},    /* 9  */
									  {3,0,0,1},    /* 10 */
									  {4,1,0,0},    /* 11 */
									  {4,0,1,1},    /* 12 */
									  {4,0,0,1},    /* 13 */
									  {4,0,1,1},    /* 14 */
									  {5,0,1,0}};   /* 15 */

static LVL_MAGIC_TYPE mon[MAX_LEVEL]={{1,1,0,0},    /* 2  */
									  {1,1,0,0},    /* 3  */
									  {1,1,0,0},    /* 4  */
									  {2,1,0,0},    /* 5  */
									  {2,1,0,0},    /* 6  */
									  {2,1,0,0},    /* 7  */
									  {2,0,0,0},    /* 8  */
									  {2,1,0,0},    /* 9  */
									  {2,0,0,0},    /* 10 */
									  {3,0,0,0},    /* 11 */
									  {2,0,0,0},    /* 12 */
									  {3,0,0,0},    /* 13 */
									  {2,0,0,0},    /* 14 */
									  {3,0,0,0}};   /* 15 */

int _PASCAL evaluate_level_details(unsigned long *xp_next_lvl)
{
	int i;
	int level=adv.level+1;

	switch(adv.nclass)
	{
		case WARRIOR    :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_warrior[i].lower && adv.xp<=level_warrior[i].upper)
								{
									*xp_next_lvl=level_warrior[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case PRIEST     :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_priest[i].lower && adv.xp<=level_priest[i].upper)
								{
									*xp_next_lvl=level_priest[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case WIZARD     :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_wizard[i].lower && adv.xp<=level_wizard[i].upper)
								{
									*xp_next_lvl=level_wizard[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case DRUID      :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_druid[i].lower && adv.xp<=level_druid[i].upper)
								{
									*xp_next_lvl=level_druid[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case THIEF      :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_thief[i].lower && adv.xp<=level_thief[i].upper)
								{
									*xp_next_lvl=level_thief[i].upper+1L;
									level=i+1;

									break;
								}

							break;
		case RANGER     :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_ranger[i].lower && adv.xp<=level_ranger[i].upper)
								{
									*xp_next_lvl=level_ranger[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case CRUSADER   :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_crusader[i].lower && adv.xp<=level_crusader[i].upper)
								{
									*xp_next_lvl=level_crusader[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case BARD       :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_bard[i].lower && adv.xp<=level_bard[i].upper)
								{
									*xp_next_lvl=level_bard[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case MONK       :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_monk[i].lower && adv.xp<=level_monk[i].upper)
								{
									*xp_next_lvl=level_monk[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case ILLUSIONIST:   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_illusionist[i].lower && adv.xp<=level_illusionist[i].upper)
								{
									*xp_next_lvl=level_illusionist[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case HUNTER     :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_hunter[i].lower && adv.xp<=level_hunter[i].upper)
								{
									*xp_next_lvl=level_hunter[i].upper+1L;
									level=i+1;

									break;
								}

							break;

		case DUELIST    :   for (i=0; i<MAX_LEVEL; i++)
								if (adv.xp>=level_duelist[i].lower && adv.xp<=level_duelist[i].upper)
								{
									*xp_next_lvl=level_duelist[i].upper+1L;
									level=i+1;

									break;
								}

							break;
	}

	return(level);
}

void _PASCAL go_up_a_level()
{
	char temp[35];
	int read_disc=TRUE;

	log_all_disc_players();

	if (P_NUM==ERR)
	{
		GX("No Adventurers in roster!",BAD);
		return;
	}

	make_gwindow(&select_win);

	while (select_a_disc_adventurer("Advance who's Career?",read_disc)!=ERR)
	{
		if (player_is_dead(&adv))
		{
			sprintf(temp,"%s art dead!",adv.name);
			GX(temp,BAD);

			read_disc=FALSE;
		}
		else
		{
			if (move_adventurer_up_a_level())
				read_disc=TRUE;
			else
				read_disc=FALSE;
		}
	}

	kill_gwindow(&select_win);
}

int _PASCAL move_adventurer_up_a_level()
{
	char temp[90];
	int current_level;
	int poss_level;
	unsigned long current_xp;
	unsigned long xp_next_lvl;
	int res;
	unsigned long amount_needed;

	current_level   = adv.level;
	current_xp      = adv.xp;
	poss_level      = evaluate_level_details(&xp_next_lvl);

	if (current_level>=MAX_LEVEL || (unsigned)current_level>=adv.max_level)
	{
		sprintf(temp,"%s cannot advance beyond level %d!",adv.name,adv.level);
		GX(temp,BAD);

		return(FALSE);
	}

	if (poss_level>current_level)
	{
		amount_needed=1000L*(long)(current_level+1);

		amount_needed+=(100L*(long)current_level*(15L-(long)adv.charisma));

		if (current_level<5)
			amount_needed/=3L;

		if (amount_needed>adv.cash)
		{
			sprintf(temp,"To advance a level %s needs %luGC!",adv.name,amount_needed);
			GX(temp,BAD);

			return(FALSE);
		}

		adv.cash-=amount_needed;

		sprintf(temp,"%s canst train for level %d!",adv.name,current_level+1);
		GX(temp,NEW_LEVEL);

		advance_attrib();

		switch(adv.nclass)
		{
			case WARRIOR    : advance_a_warrior();                  break;
			case PRIEST     : advance_a_priest(current_level);      break;
			case WIZARD     : advance_a_wizard(current_level);      break;
			case DRUID      : advance_a_druid(current_level);       break;
			case THIEF      : advance_a_thief();                    break;
			case RANGER     : advance_a_ranger(current_level);      break;
			case CRUSADER   : advance_a_crusader(current_level);    break;
			case BARD       : advance_a_bard();                     break;
			case MONK       : advance_a_monk(current_level);        break;
			case ILLUSIONIST: advance_a_illusionist(current_level); break;
			case HUNTER     : advance_a_hunter(current_level);      break;
			case DUELIST    : advance_a_duelist();                  break;
		}

		adv.level++;

		save_adventurer(&adv);

		GX("Thy career art advanced!",GOOD);

		res=TRUE;
	}
	else
	{
		sprintf(temp,"%s needs %lu more XP to advance to level %d!",
							adv.name,
							xp_next_lvl-current_xp,
							current_level+1);

		GX(temp,BAD);

		res=FALSE;
	}

	return(res);
}

void _PASCAL increase_hp(int hd)
{
	adv.hp+=(int)max((rand()%hd+1),(rand()%hd+1));

	if ((unsigned)percent()<=adv.luck)
		adv.hp++;

	switch(effective_toughness(&adv))
	{
		case 15 : adv.hp++;  break;
		case 16 : adv.hp+=2; break;
		case 17 : adv.hp+=3; break;
		case 18 : adv.hp+=4; break;
		case 19 : adv.hp+=5; break;
		case 20 : adv.hp+=6; break;
	}

	adv.current_hp=adv.hp;
}

void _PASCAL advance_a_priest(int from_level)
{
	increase_hp(6);
	advance_spells(from_level,PRIEST);
}

void _PASCAL advance_a_wizard(int from_level)
{
	increase_hp(4);
	advance_spells(from_level,WIZARD);
}

void _PASCAL advance_a_druid(int from_level)
{
	increase_hp(4);
	advance_spells(from_level,DRUID);
}

void _PASCAL advance_a_ranger(int from_level)
{
	increase_hp(8);
	advance_spells(from_level,RANGER);
}

void _PASCAL advance_a_crusader(int from_level)
{
	increase_hp(8);
	advance_spells(from_level,CRUSADER);
}

void _PASCAL advance_a_monk(int from_level)
{
	increase_hp(4);
	advance_spells(from_level,MONK);
}

void _PASCAL advance_a_illusionist(int from_level)
{
	increase_hp(4);
	advance_spells(from_level,ILLUSIONIST);
}

void _PASCAL advance_a_hunter(int from_level)
{
	increase_hp(8);
	advance_spells(from_level,HUNTER);
}

void _PASCAL advance_a_warrior()
{
	increase_hp(10);
}

void _PASCAL advance_a_thief()
{
	increase_hp(6);
}

void _PASCAL advance_a_bard()
{
	increase_hp(6);
}

void _PASCAL advance_a_duelist()
{
	increase_hp(8);
}

void _PASCAL advance_spells(int from_level,int spell_type)
{
	int i=from_level-1;

	switch(spell_type)
	{
		case ILLUSIONIST: adv.learn_ill1_spells+=ill[i].lv1_add;
						  adv.learn_ill2_spells+=ill[i].lv2_add;
						  adv.learn_ill3_spells+=ill[i].lv3_add;
						  adv.sorcery_points+=ill[i].pts_add;
						  adv.current_sorcery_points=adv.sorcery_points;
						  break;

		case WIZARD     : adv.learn_wiz1_spells+=wiz[i].lv1_add;
						  adv.learn_wiz2_spells+=wiz[i].lv2_add;
						  adv.learn_wiz3_spells+=wiz[i].lv3_add;
						  adv.sorcery_points+=wiz[i].pts_add;
						  adv.current_sorcery_points=adv.sorcery_points;
						  break;

		case MONK       : adv.learn_wiz1_spells+=mon[i].lv1_add;
						  adv.learn_wiz2_spells+=mon[i].lv2_add;
						  adv.learn_wiz3_spells+=mon[i].lv3_add;
						  adv.sorcery_points+=mon[i].pts_add;
						  adv.current_sorcery_points=adv.sorcery_points;
						  break;

		case RANGER     : adv.learn_wiz1_spells+=ran[i].lv1_add;
						  adv.learn_wiz2_spells+=ran[i].lv2_add;
						  adv.learn_wiz3_spells+=ran[i].lv3_add;
						  adv.sorcery_points+=ran[i].pts_add;
						  adv.current_sorcery_points=adv.sorcery_points;
						  break;

		case PRIEST     : adv.learn_pri1_spells+=pri[i].lv1_add;
						  adv.learn_pri2_spells+=pri[i].lv2_add;
						  adv.learn_pri3_spells+=pri[i].lv3_add;
						  adv.divine_points+=pri[i].pts_add;
						  adv.current_divine_points=adv.divine_points;
						  break;

		case CRUSADER   : adv.learn_pri1_spells+=cru[i].lv1_add;
						  adv.learn_pri2_spells+=cru[i].lv2_add;
						  adv.learn_pri3_spells+=cru[i].lv3_add;
						  adv.divine_points+=cru[i].pts_add;
						  adv.current_divine_points=adv.divine_points;
						  break;

		case DRUID      : adv.learn_dru1_spells+=dru[i].lv1_add;
						  adv.learn_dru2_spells+=dru[i].lv2_add;
						  adv.learn_dru3_spells+=dru[i].lv3_add;
						  adv.divine_points+=dru[i].pts_add;
						  adv.current_divine_points=adv.divine_points;
						  break;

		case HUNTER     : adv.learn_dru1_spells+=hun[i].lv1_add;
						  adv.learn_dru2_spells+=hun[i].lv2_add;
						  adv.learn_dru3_spells+=hun[i].lv3_add;
						  adv.divine_points+=hun[i].pts_add;
						  adv.current_divine_points=adv.divine_points;
						  break;
	}
}

void _PASCAL advance_attrib()
{
	GWINDOW win;
	char temp[40];
	static char *attrib[]={"Attack",
						   "Parry",
						   "Missile",
						   "Disarm Trap",
						   "Find Trap",
						   "Pick Lock",
						   "Listen",
						   "Move Silently",
						   "Disease Immunity",
						   "Poison Immunity",
						   "Heal",
						   "Herb Lore",
						   "Hunt",
						   "Survival",
						   "Swim"
						   };
	char *t2="APMDFILSUNHRTVW";
	int ok;
	int i,j;
	int skill;
	int value,updated_value;
	int big1, big2, big3;
	int attrib_taken[MAX_SKILLS+1];
	int longest=0;
	static int boundary[]={32, 48,254, 54,
						   32, 56,254, 62,
						   32, 64,254, 70,
						   32, 72,254, 78,
						   32, 80,254, 86,
						   32, 88,254, 94,
						   32, 96,254,102,
						   32,104,254,110,
						   32,112,254,118,
						   32,120,254,126,
						   32,128,254,134,
						   32,136,254,142,
						   32,144,254,150,
						   32,152,254,158,
						   32,160,254,166,
						   -1,-1,-1,-1};

	fast_mouse=OFF;

	for (i=0; i<MAX_SKILLS+1; i++)
	{
		if (i<MAX_SKILLS)
			longest=max(longest,(int)strlen(attrib[i]));

		attrib_taken[i]=FALSE;
	}

	longest++;

	win.x1=4;
	win.y1=2;
	win.x2=35;
	win.y2=25;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(14);
	sprintf(temp,"Increasing %s%s",adv.name,end_s(adv.name));
	_settextposition(win.y1+1,19-strlen_half(temp));
	_outtext(temp);

	strcpy(temp,"Secondary Skills");
	_settextposition(win.y1+2,19-strlen_half(temp));
	_outtext(temp);

	strcpy(temp,"Ye may train in three skills");
	_settextposition(win.y2-2,19-strlen_half(temp));
	_outtext(temp);

	_settextposition(win.y1+4,win.x1+20);
	_settextcolor(4);
	_outtext("Now  After");

	for (i=0; i<SIZE(attrib); i++)
	{
		_settextcolor(5);

		_settextposition(win.y1+5+i,win.x1+1);

		strcpy(temp,attrib[i]);

		while (strlen(temp)<(size_t)longest)
			strcat(temp,"ú");

		strcat(temp,":");

		_outtext(temp);

		for (j=0; j<(int)strlen(attrib[i]); j++)
		{
			if (toupper((int)attrib[i][j])==(int)t2[i])
			{
				_settextcolor(13);
				_settextposition(win.y1+5+i,win.x1+1+j);

				temp[0]=attrib[i][j];
				temp[1]='\0';

				_outtext(temp);

				break;
			}
		}

		switch(i)
		{
			case 0 : skill=ATTACK;          break;
			case 1 : skill=PARRY;           break;
			case 2 : skill=MISSILE;         break;
			case 3 : skill=DISARM_TRAP;     break;
			case 4 : skill=FIND_TRAP;       break;
			case 5 : skill=PICK_LOCK;       break;
			case 6 : skill=LISTEN;          break;
			case 7 : skill=MOVE_SILENT;     break;
			case 8 : skill=IMMUNITY_DISEASE;break;
			case 9 : skill=IMMUNITY_POISON; break;
			case 10: skill=HEAL;            break;
			case 11: skill=HERB_LORE;       break;
			case 12: skill=HUNT;            break;
			case 13: skill=SURVIVAL;        break;
			case 14: skill=SWIM;            break;
		}

		switch(adv.nclass)
		{
			case WARRIOR        :   big1=ATTACK;        /* 7% */
									big2=PARRY;         /* 5% */
									big3=SURVIVAL;      /* 4% */
									break;

			case PRIEST         :   big1=HEAL;
									big2=ATTACK;
									big3=IMMUNITY_POISON;
									break;

			case RANGER         :   big1=ATTACK;
									big2=SURVIVAL;
									big3=HERB_LORE;
									break;

			case DRUID          :   big1=HERB_LORE;
									big2=IMMUNITY_POISON;
									big3=IMMUNITY_DISEASE;
									break;

			case THIEF          :   big1=DISARM_TRAP;
									big2=MOVE_SILENT;
									big3=PICK_LOCK;
									break;

			case WIZARD         :   big1=MISSILE;
									big2=LISTEN;
									big3=SWIM;
									break;

			case BARD           :   big1=ATTACK;
									big2=SURVIVAL;
									big3=PARRY;
									break;

			case MONK           :   big1=ATTACK;
									big2=PARRY;
									big3=IMMUNITY_POISON;
									break;

			case ILLUSIONIST    :   big1=MISSILE;
									big2=PARRY;
									big3=LISTEN;
									break;

			case HUNTER         :   big1=HUNT;
									big2=ATTACK;
									big3=SURVIVAL;
									break;

			case DUELIST        :   big1=ATTACK;
									big2=PARRY;
									big3=IMMUNITY_POISON;
									break;

			case CRUSADER       :   big1=ATTACK;
									big2=PARRY;
									big3=SURVIVAL;
									break;
		}

		value=adv.secondary_attrib[skill];

		if (skill==big1)
			updated_value=value+7;
		else
		if (skill==big2)
			updated_value=value+5;
		else
		if (skill==big3)
			updated_value=value+4;
		else
			updated_value=value+3;

		updated_value=min(updated_value,99);

		_settextposition(win.y1+5+i,win.x1+19);
		sprintf(temp,"%3d   %3d",value,updated_value);
		_settextcolor(12);
		_outtext(temp);
	}

	for (j=0; j<3; j++)
	{
		ok=FALSE;

		while (!ok)
		{
			switch((i=mouse_in_range(boundary,t2,"")))
			{
				case 0 : skill=ATTACK;          break;
				case 1 : skill=PARRY;           break;
				case 2 : skill=MISSILE;         break;
				case 3 : skill=DISARM_TRAP;     break;
				case 4 : skill=FIND_TRAP;       break;
				case 5 : skill=PICK_LOCK;       break;
				case 6 : skill=LISTEN;          break;
				case 7 : skill=MOVE_SILENT;     break;
				case 8 : skill=IMMUNITY_DISEASE;break;
				case 9 : skill=IMMUNITY_POISON; break;
				case 10: skill=HEAL;            break;
				case 11: skill=HERB_LORE;       break;
				case 12: skill=HUNT;            break;
				case 13: skill=SURVIVAL;        break;
				case 14: skill=SWIM;            break;
			}

			if (attrib_taken[skill])
			{
				ok=FALSE;
				bad_sound2();
			}
			else
			{
				value=adv.secondary_attrib[skill];

				if (skill==big1)
					updated_value=value+7;
				else
				if (skill==big2)
					updated_value=value+5;
				else
				if (skill==big3)
					updated_value=value+4;
				else
					updated_value=value+3;

				updated_value=min(updated_value,99);

				adv.secondary_attrib[skill]=updated_value;

				_settextposition(win.y1+5+i,win.x1+19);
				sprintf(temp,"%3d       ",updated_value);
				_settextcolor(12);
				_outtext(temp);

				attrib_taken[skill]=TRUE;

				ok=TRUE;
			}
		}
	}

	good_sound();
	pause(1);

	kill_gwindow(&win);

	fast_mouse=ON;
}
