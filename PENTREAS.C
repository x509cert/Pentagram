#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

long _PASCAL non_magic_treasure()
{
	int lv=average_level();
	int i,j,c,fin=FALSE;
	long int value=0L, total_value=0L;
	char temp[160];
	int sw;

	static struct {
						char *name;
						int  base;
						int  mod;

				  } gems[]={"Azurite",              10,  10,
							"Malachite",            10,  10,
							"Lapis Lazuli",         15,  15,
							"Bloodstone",           20,  60,
							"Amber",                0,   600,
							"Onyx",                 10,  60,
							"Turquoise",            0,   30,
							"Agate",                0,   30,
							"Aquamarine",           60,  200,
							"Garnet",               100, 300,
							"Jade",                 300, 400,
							"Alexandrite",          100, 300,
							"Amethyst",             100, 500,
							"Topaz",                100, 400,
							"Jet",                  300, 400,

							"A Pearl",              1000,1500,
							"An Opal",              1000,2000,
							"A Fire Opal",          1000,2000,
							"A Ruby",               1000,2000,
							"A Sapphire",           1200,2000,
							"A Star Sapphire",      1500,2000,
							"An Emerald",           1800,2000,
							"A Diamond",            3000,2000,
							"A King's Tear",        4000,3000    /* 24 */
						   };

	static struct {
						char *name;
						int base;
						int mod;

				  } jewels[]={"An ivory",           5,   5,
							  "A jade",             10,  10,
							  "A silver",           20,  20,
							  "A gold",             50,  50,
							  "A platinum",         100, 100,
							  "A jewelled silver",  200, 200,
							  "A jewelled gold",    500, 500,
							  "A jewelled platinum",1000,1000    /* 8 */
							 };

	static char *items[]={"broach","pendant","ring","necklace","tiara","bracelet","ear-ring"};
	static char *furs[]={"beaver","fox","mink","musk deer","sable","seal","reindeer"};

	int num_gems    = SIZE(gems);
	int num_jewels  = SIZE(jewels);
	int num_items   = SIZE(items);
	int num_furs    = SIZE(furs);

	if (!party_can_carry_treasure())
		return(0L);

	for (;;)
	{
		i=percent()+1;

		if (i>=1 && i<=50)      /* Cash   */
			sw=0;

		if (i>=51 && i<=70)     /* Gems   */
			sw=1;

		if (i>=71 && i<=85)     /* Furs   */
			sw=2;

		if (i>=86 && i<=100)    /* Jewels */
			sw=3;


		switch(sw)
		{
			case 0 :    value=(long)((percent()+10)*(rand()%lv+1));

						while (value<100L)
							value+=rand()%100;

						sprintf(temp,"%lu GC.",value);

						total_value+=value;

						fin=TRUE;

						break;

			case 1 :    j=percent()+1;

						if (j<=85)
							c=rand()%(num_gems/2);
						else
							c=rand()%9+(num_gems/2);

						value=(long)gems[c].base+(rand()%gems[c].mod);
						value*=2L;

						sprintf(temp,"%s %s WORTH %lu GC.",j<=85?j%2?"Some":"A piece of":"",gems[c].name,value);

						total_value+=value;

						break;

			case 2 :    j=rand()%num_furs;

						value=(long)rand()%15+5;
						value*=(lv+4);
						value*=2L;

						sprintf(temp,"A %s %s WORTH %lu GC.",furs[j],i%2?"pelt":"skin",value);

						total_value+=value;

						break;

			default :   j=rand()%num_jewels;
						c=rand()%num_items;

						value=(long)jewels[j].base+(rand()%jewels[j].mod);
						value*=2L;

						sprintf(temp,"%s %s WORTH %lu GC.",jewels[j].name,items[c],value);

						total_value+=value;

						break;
		}

		scroll_wrap_write(14,temp);

		if (fin)
			break;
	}

	return(total_value);
}

void _PASCAL magic_treasure()
{
	int num=1;
	int i;
	int threshold=75-(average_level()*7);
	char temp[80];
	static char *n[]={"A","Two","Three"};

	if (percent()>threshold)
		num++;

	if (percent()>threshold)
		num++;

	sprintf(temp,"Thou hast found %s potion%s",n[num-1],num==1?"!":"s!");
	SCROLL(2,14,temp);
	good_sound();
	half_pause();

	for (i=0; i<num; i++)
		mt_potion();
}

void _PASCAL mt_potion()
{
	static int	poss_pot[]={POT_UNDEAD_TURN,
							POT_HEALING,
							POT_REVIVING,
							POT_COLD_RESIST,
							POT_FIRE_RESIST,
							POT_STRENGTH,
							POT_SECRET_DOOR,
							POT_STRIKING,
							POT_NOTHING,
							POT_ALCOHOL,
							POT_CURE_DISEASE};
	char desc[30];
	char temp[40];
	int fin=FALSE;
	int person;
	int potion=rand()%SIZE(poss_pot);

	strcpy(desc,potion_get_colour(poss_pot[potion],FALSE));

	sprintf(temp,"%s %s potion.",isvowel((int)*desc)?"An":"A",desc);
	SCROLL(2,7,temp);

	general_low_sound();
	pause(1);

	while (!fin)
	{
		person=adv_select_adventurer("Who takes","ye potion?",TRUE);

		if (person!=ERR)
		{
			if (number_of_items(&TPP[person])>=MAX_CARRY)
				carry_no_more(&TPP[person]);
			else
				fin=TRUE;
		}
		else
			fin=TRUE;
	}

	if (person==ERR)
	{
		SCROLL(1,0,"Strangely, ye vial shatters, spilling its contents!");

		bad_sound2();
		pause(2);
	}
	else
	{
		add_to_player(POTION,poss_pot[potion],ITEM_CARRIED,FALSE,&TPP[person]);

		sprintf(temp,"%s takes ye vial!",TPP[person].name);
		SCROLL(0,14,temp);

		good_sound();
		pause(1);
	}
}
