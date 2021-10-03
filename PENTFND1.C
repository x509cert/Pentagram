#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <io.h>
#include <ctype.h>
#include "mmalloc.h"

#ifdef DEV
static void _PASCAL dump_monsters(int,int,int);
#endif

static MONSTER		*monster_database;

int _PASCAL build_monsters(int encounter)					 /* Build Monsters from */
{															 /* database */
	int i,hd,poss_monst,rec_no,skip_morale=FALSE;

	memset(the_monsters,0,sizeof(the_monsters));
	num_monsters=0;

	load_monster_database();

	if (encounter==MANGRETH_MONSTER)
	{
		hd=load_mangreth_stats();
		skip_morale=TRUE;
	}
	else
	if (encounter==KALDRUTHA_MONSTER)
	{
		hd=load_kaldrutha_stats();
		skip_morale=TRUE;
	}
	else
	{
		poss_monst=get_monster_type();

		rec_no=get_fuzzy_monster_type(poss_monst,encounter);

		if (monster_database[rec_no].max_number==1)
		{
			num_monsters=1;
		}
		else
		{
			num_monsters=get_dice_roll(monster_database[rec_no].max_number,1,0);

			if (num_monsters<(signed)monster_database[rec_no].min_number)
				num_monsters=monster_database[rec_no].min_number;

			i=modified_average_level();

			if (i<KINDNESS_THRESHOLD)
			{
				if (monster_attack_is_magical(&monster_database[rec_no],0))
					num_monsters=1;
				else
					num_monsters=min(num_monsters,i+3);
			}
		}

		if (wizard_mode)
		{
			strcpy(monster_database[rec_no].name,monster_database[rec_no].silly_name);

			for (i=0; i<strlen(monster_database[rec_no].name); i++)
				monster_database[rec_no].name[i]--;
		}

		for (i=0; i<num_monsters; i++)
			hd=build_monster(i,&monster_database[rec_no]);
	}

#ifdef DEV

	dump_monsters(rec_no,num_monsters,encounter);

#endif

	kill_monster_database();

	load_monster_mask();
	load_monster_image();

	if (!skip_morale)
		morale_all_at_start();

	return(hd);
}

int _PASCAL _NEAR load_mangreth_stats()
{
	int rec_no=num_database_monsters;

	memcpy(&the_monsters[0],&monster_database[rec_no],sizeof(MONSTER));

	set_monster_defaults(&the_monsters[0]);
	the_monsters[0].current_hp = 180;

	num_monsters=1;

	build_monster_get_opponent(&the_monsters[0]);

	return(the_monsters[0].hd);
}

int _PASCAL _NEAR load_kaldrutha_stats()
{
	int rec_no=num_database_monsters+1;

	memcpy(&the_monsters[0],&monster_database[rec_no],sizeof(MONSTER));

	set_monster_defaults(&the_monsters[0]);
	the_monsters[0].current_hp = 140;

	num_monsters=1;

	build_monster_get_opponent(&the_monsters[0]);

	return(the_monsters[0].hd);
}

void _PASCAL _NEAR set_monster_defaults(MONSTER *mnst)
{
	mnst->condition       = OKAY;
	mnst->fleeing         = FALSE;
	mnst->flown           = FALSE;
	mnst->spell_bound     = FALSE;
	mnst->is_stunned      = FALSE;
	mnst->is_lethargic    = FALSE;
	mnst->weak_msg_given  = FALSE;
}

int _PASCAL _NEAR get_fuzzy_monster_type(int poss_monst,int wandering)
{
	int num_eligible;						/* passes through */
	int rec_no,i;							/* database looking */
	int highest;							/* for Eligibles */

	nullify_monster_eligible();

	fuzzy_by_level(wandering);
	fuzzy_by_type(poss_monst,wandering);
	fuzzy_mask_dungeon_monsters();
	fuzzy_mask_outdoor_monsters();
	fuzzy_mask_day_nite();
	fuzzy_promote_hill_monsters();

	num_eligible=fuzzy_get_num_eligible(&highest);

	if (num_eligible==0)
	{
		for (i=0; i<num_database_monsters; i++)
		{
			if (strnicmp(monster_database[i].name,"ogre",4)==0)
			{
				rec_no=i;
				break;
			}
		}
	}
	else
		rec_no=choose_monster_from_eligibles(num_eligible,highest);

	return(rec_no);
}

void _PASCAL _NEAR fuzzy_promote_hill_monsters()
{
	int i;
	int feature=pent_data.current_feature;

	if (feature!=HILLS && feature!=MOUNTAINS && feature!=HIGH_MOUNTAINS)
		return;

	for (i=0; i<num_database_monsters; i++)
		if (monster_database[i].hills)
			monster_database[i].eligible++;
}

void _PASCAL _NEAR fuzzy_mask_dungeon_monsters()
{
	int i;

	if (!IN_DUNGEON)
		return;

	for (i=0; i<num_database_monsters; i++)
		if (monster_database[i].dungeon==FALSE)
			monster_database[i].eligible=NOT_ELIGIBLE;
}

void _PASCAL _NEAR fuzzy_mask_outdoor_monsters()
{
	int i;

	if (IN_DUNGEON)
		return;

	for (i=0; i<num_database_monsters; i++)
		if (monster_database[i].outdoors==FALSE)
			monster_database[i].eligible=NOT_ELIGIBLE;
}

void _PASCAL _NEAR fuzzy_mask_day_nite()
{
	int i;

	if (is_night_time())			/* All Monsters at night! */
		return;

	if (IN_DUNGEON)                 /* All Day monsters OK in dungeon */
		return;

	for (i=0; i<num_database_monsters; i++)
		if (monster_database[i].night_day==MON_NIGHT)
			monster_database[i].eligible=NOT_ELIGIBLE;
}

int _PASCAL _NEAR choose_monster_from_eligibles(int num_eligible,int highest)
{
	int chosen,current,rec_no,i;
	unsigned lv=modified_average_level();

	if (lv<1)
		lv=1;

	if (lv>12)
		lv=12;

	if (num_eligible==0)
	{
		nullify_monster_eligible();

		highest=ELIGIBLE_THRESHOLD;

		for (i=0; i<num_database_monsters; i++)
		{
			if (monster_database[i].hd==lv               &&
				monster_database[i].dungeon==TRUE        &&
				monster_database[i].outdoors==TRUE       &&
				monster_database[i].night_day==MON_BOTH)
			{
				monster_database[i].eligible=ELIGIBLE_THRESHOLD;
				num_eligible++;
			}
		}
	}

	chosen=rand()%num_eligible;
	current=0;

	for (i=0; i<num_database_monsters; i++)
	{
		if (monster_database[i].eligible>=highest)
		{
			if (current==chosen)
			{
				rec_no=i;
				break;
			}
			else
				current++;
		}
	}

	return(rec_no);
}

void _PASCAL _NEAR fuzzy_by_type(int type,int wandering)
{
	int i;

	for (i=0; i<num_database_monsters; i++)
	{
		if (type!=DMON_RANDOM)
		{
			if ((wandering==WANDERING_MONSTER && monster_database[i].wandering)
				 || wandering==SET_MONSTER)
			{
				if ((IN_DUNGEON && monster_database[i].dungeon)
					 || !IN_DUNGEON)
				{
					if ((unsigned)monster_database[i].monster_type==(unsigned)type)
					{
						monster_database[i].eligible++;
					}
				}
				else
					monster_database[i].eligible=NOT_ELIGIBLE;
			}
			else
				monster_database[i].eligible=NOT_ELIGIBLE;
		}
		else
		{
			if (wandering==WANDERING_MONSTER && monster_database[i].wandering)
				monster_database[i].eligible++;
			else
				monster_database[i].eligible=NOT_ELIGIBLE;
		}
	}
}

int _PASCAL _NEAR fuzzy_get_num_eligible(int *highest)
{
	int i;
	int num=0;

	*highest=0;

	for (i=0; i<num_database_monsters; i++)
		if (monster_database[i].eligible>*highest)
			*highest=monster_database[i].eligible;

	if (*highest>0)
		for (i=0; i<num_database_monsters; i++)
			if (monster_database[i].eligible==*highest)
				num++;

	return(num);
}

int _PASCAL _NEAR get_monster_type()						 /* Determine monster type */
{															 /* Uses set_monst */
	int type=DMON_RANDOM;

	if (IN_DUNGEON)
	{
		type=dungeon.map[the_party.dungeon_level]
						[the_party.dungeon_x]
						[the_party.dungeon_y].trap_monst;

		if (type==DMON_NONE)	  /* ie; Random Encounter */
		{
			if (percent()>75)
				type=DMON_RANDOM;
			else
			{
				switch(dungeon.most_monster_type)
				{
					case DM_ALL 	 : type=DMON_RANDOM; break;
					case DM_UNDEAD	 : type=DMON_UNDEAD; break;
					case DM_GOBLINOID: type=DMON_GOBLIN; break;
					case DM_DEMONS   : type=DMON_DEMON;  break;
					default          : type=DMON_RANDOM; break;
				}
			}
		}
	}

	return(type);
}

void _PASCAL _NEAR fuzzy_by_level(int wandering)
{
	int lv=modified_average_level();
	int start,end;
	int i;
	unsigned mhd;
	int lv1,lv2;

	start=lv-2;
	end=lv+3;

	if (start<=1 || end<=1)
	{
		start=1;
		end=4;
	}
	else
	if (start>=9 || end>=13)
	{
		start=9;
		end=15;
	}

	lv1=lv2=lv;

	if (percent()>65)
		lv1--;

	if (percent()>65)
		lv2++;

	for (i=0; i<num_database_monsters; i++)
	{
		mhd=monster_database[i].hd;

		if (mhd>=(unsigned)start && mhd<=(unsigned)end)
		{
			monster_database[i].eligible+=((mhd>=lv1 && mhd<=lv2)?2:1);

			if (wandering==WANDERING_MONSTER)
				monster_database[i].eligible++;
		}
		else
			monster_database[i].eligible=NOT_ELIGIBLE;
	}
}

void _PASCAL _NEAR load_monster_mask()
{
	FILE *fptr;
	char temp[60];

	sprintf(temp,"%s%s.MSK",MONSTER_DIRECTORY,the_monsters[0].mask_image);

	if ((fptr=fopen(temp,"rb"))==NULL)
		panic_FILE(temp);

	fread((void *)monster_mask_image,1,MONSTER_IMAGE_SIZE,fptr);

	fclose(fptr);
}

void _PASCAL _NEAR load_monster_image()
{
	char temp[60];
	FILE *fptr;

	sprintf(temp,"%s%s.PIC",MONSTER_DIRECTORY,the_monsters[0].image);

	if ((fptr=fopen(temp,"rb"))==NULL)
		panic_FILE(temp);

	fread((void *)monster_image,MONSTER_IMAGE_SIZE,1,fptr);

	fclose(fptr);
}

void _PASCAL _NEAR kill_monster_database()
{
	Mfree((void *)monster_database);
}

void _PASCAL _NEAR nullify_monster_eligible()
{
	int i;

	for (i=0; i<num_database_monsters; i++)
		monster_database[i].eligible=0;
}

int _PASCAL _NEAR build_monster(int num,MONSTER *mnst)
{
	int dice_base=10;
	int av=modified_average_level();

	if ((unsigned)av>mnst->hd)
		dice_base+=(av-mnst->hd);

	if (mnst->hd>6)
		dice_base+=(mnst->hd-6);

	if (strstr(mnst->name,"ragon")!=NULL)
		dice_base+=4;

	memcpy(&the_monsters[num],mnst,sizeof(MONSTER));

	set_monster_defaults(&the_monsters[num]);
	the_monsters[num].current_hp = get_dice_roll(dice_base,mnst->hd,1);

	if (modified_average_level()<KINDNESS_THRESHOLD)
	{
		if (percent()>33)
			the_monsters[num].current_hp=min(get_dice_roll(4+mnst->hd,1,mnst->hd+2),
										 the_monsters[num].current_hp);

		the_monsters[num].attack_damage[0]=min(5,the_monsters[num].attack_damage[0]);
		the_monsters[num].attack_damage[1]=min(5,the_monsters[num].attack_damage[1]);

		the_monsters[num].ac+=get_dice_roll(2,1,1);
	}

	if (percent()>65)
		the_monsters[num].agility+=get_dice_roll(3,1,0);

	if (percent()>65)
		the_monsters[num].agility-=get_dice_roll(3,1,0);

	the_monsters[num].opponent=(PLAYER *)NULL;

	if (the_monsters[num].intelligence>=10)
		build_monster_get_opponent(&the_monsters[num]);

	if ((the_monsters[num].intelligence<10))
		if (((unsigned)percent()/3)<=the_monsters[num].intelligence)
			build_monster_get_opponent(&the_monsters[num]);

	return(mnst->hd);
}

void _PASCAL build_monster_get_opponent(MONSTER *mnst)
{
	int person=get_random_live_person();

	if (person!=ERR)
		mnst->opponent=(PLAYER *)&TPP[person];
}

void _PASCAL _NEAR load_monster_database()
{
	long size;
	FILE *fptr;
	char temp[60];

	sprintf(temp,"%s%s",MONSTER_DIRECTORY,MONSTER_DATABASE);

	fptr=fopen(temp,"rb");

	if (fptr==NULL)
		panic_FILE(temp);

	size=filelength(fileno(fptr));

	monster_database=(MONSTER *)Mmalloc((size_t)size);

	if (monster_database==(MONSTER *)NULL)
		panic_RAM(temp);

	fread((void *)monster_database,(size_t)size,1,fptr);

	fclose(fptr);

	num_database_monsters=((size_t)size)/sizeof(MONSTER);

	num_database_monsters-=2;
}

#ifdef DEV

static void _PASCAL dump_monsters(int rec_no,int num,int encounter)
{
	FILE *fptr;
	int i;

	fptr=fopen("MNSTDUMP.LOG","w");

	fprintf(fptr,"Selection of Land, Underworld and DunGeon Encounters\nSLUDGE! (c) 1990 Odin Software Development\n\n"
				 "Average Level  : %d\n"
				 "Random?        : %s\n"
				 "Dungeon?       : %s\n"
				 "Day/Night      : %s\n"
				 "Monster Chosen : %s (AC:%d, Att1:%d, Att2:%d)\n"
				 "Magic to hit?  : %s\n"
				 "# Monster      : %d\n\n",
				 modified_average_level(),
				 encounter==WANDERING_MONSTER?"Yes":"No",
				 IN_DUNGEON?"Yes":"No",
				 is_night_time()?"Night":"Day",
				 monster_database[rec_no].name,
				 monster_database[rec_no].ac,
				 monster_database[rec_no].attack_damage[0],
				 monster_database[rec_no].attack_damage[1],
				 monster_database[rec_no].magic_weapon_to_hit?"Yes":"No",
				 num);

	for (i=0; i<num_database_monsters; i++)
		fprintf(fptr,"%20s %c %3d %3d\n",
					 monster_database[i].name,
					 i==rec_no?'*':' ',
					 monster_database[i].hd,
					 monster_database[i].eligible);

	fclose(fptr);
}

#endif
