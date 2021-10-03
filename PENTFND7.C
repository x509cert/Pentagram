#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <bstrings.h>

/*
 *
 * Monster Treasure
 *
 */

void _PASCAL combat_end_determine_treasure(int hd)
{
	long gc=0L;
	int i;
	char temp[80];
	int type;
	int magic_given=FALSE;

	if (!num_monsters_killed)
	{
		cmbt_gold_gained=0L;
		return;
	}

	type=the_monsters[0].treasure_type;

	SCROLL(1,11,"Looting thy foe's remains reveals..");

	general_low_sound();
	pause(1);

	scroll_scroll();

	if (!party_can_carry_treasure())
		return;

	if (type==TRE_NONE)
		num_monsters_killed=1;

	for (i=0; i<num_monsters_killed; i++)
	{
		if (type==TRE_MAGIC && magic_given)
			type=TRE_LOT_MONEY;

		switch(type)
		{
			case TRE_LOW_MONEY : gc+=monsters_treasure_TRE_LOW_MONEY(hd);
								 break;

			case TRE_MED_MONEY : gc+=monsters_treasure_TRE_MED_MONEY(hd);
								 break;

			case TRE_LOT_MONEY : gc+=monsters_treasure_TRE_LOT_MONEY(hd);
								 break;

			case TRE_JEWELS    : gc+=monsters_treasure_TRE_JEWELS(hd);
								 break;

			case TRE_MAGIC     : gc+=monsters_treasure_TRE_MAGIC();
								 magic_given=TRUE;
								 break;

			default            : gc+=monsters_treasure_TRE_NONE();
								 break;
		}
	}

	if (gc!=0L)
	{
		the_party.gc_earned+=gc;

		sprintf(temp,"%lu GC value!",gc);
		SCROLL(1,11,temp);

		good_sound();
	}

	cmbt_gold_gained=gc;
}

static long _PASCAL _NEAR monsters_treasure_TRE_NONE()
{
	SCROLL(0,0,"Nothing!");
	bad_sound();
	pause(1);

	return(0L);
}

static long _PASCAL _NEAR monsters_treasure_TRE_LOW_MONEY(int hd)
{
	return(monsters_treasure_money(1,hd));
}

static long _PASCAL _NEAR monsters_treasure_TRE_MED_MONEY(int hd)
{
	return(monsters_treasure_money(2,hd));
}

static long _PASCAL _NEAR monsters_treasure_TRE_LOT_MONEY(int hd)
{
	return(monsters_treasure_money(4,hd));
}

static long _PASCAL _NEAR monsters_treasure_TRE_JEWELS(int hd)
{
	unsigned long gc=0L;
	unsigned long total=0L;
	int t,i;
	int j,num=1;
	char temp[80];
	static char *items[]={"broach",  "pendant",
						  "ear-ring","ring",
						  "necklace","bracelet"};
	static struct {
						char *item;
						long value;

				   } tre[]={"gold",               200L,
							"platinum",           500L,
							"jewelled silver",   2000L,
							"jewelled gold",     3000L,
							"jewelled platinum", 4000L};

	if (hd>4)
		num++;

	if (hd>6)
		num++;

	for (j=0; j<num; j++)
	{
		i=rand()%SIZE(items);
		t=rand()%SIZE(tre);

		gc=(unsigned long)(tre[t].value+(rand()%(tre[t].value/5)));
		gc*=2L;

		if (gc>=1000L)
			gc-=(gc%5L);
		else
			gc-=(gc%10L);

		sprintf(temp,"A %s %s valued at %lu GC.",tre[t].item,items[i],gc);
		SCROLL(0,14,temp);
		general_low_sound();

		total+=gc;
	}

	return(total);
}

static long _PASCAL _NEAR monsters_treasure_TRE_MAGIC()
{
	magic_treasure();

	return(0L);
}

static long _PASCAL _NEAR monsters_treasure_money(int num,int hd)
{
	long gc=0L;
	int i;
	int base=hd*50;
	char temp[80];
	static char *des[]={"dirty","mouldy","filthy","worn",""};
	static char *pou[]={"cotton","leather","silk",""};

	for (i=0; i<num; i++)
		gc+=(long)((rand()%base)+2L);

	gc*=2L;

	sprintf(temp,"A %s %s %s holding %lu GC",des[rand()%SIZE(des)],
											 pou[rand()%SIZE(pou)],
											 percent()>50?"bag":"pouch",
											 gc);
	stpcvt(temp,REDUCE);

	SCROLL(0,14,temp);

	general_low_sound();
	cmbt_half_pause();

	return(gc);
}
