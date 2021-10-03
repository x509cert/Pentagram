#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

static ANIMALS animals[]={
							"Rabbit",     2 ,0 , COMMON,   1,
							"Fowl",       2 ,0 , COMMON,   1,
							"Small Deer", 3 ,6 , COMMON,   3,
							"Boar",       6 ,10, COMMON,   3,
							"Wolf",       10,4 , UNCOMMON, 2,
							"Small Elk",  8 ,10, UNCOMMON, 5,
							"Small Bison",8 ,10, UNCOMMON, 5,
							"Squirrel",   2 ,0 , UNCOMMON, 1,
							"Stoat",      4 ,0 , RARE,     1,
							"Weasal",     4 ,0 , RARE,     1,
							"Goat",       5 ,10, RARE,     3,
							"Large Deer", 6 ,12, RARE,     6
						 };

void _PASCAL actually_hunt(PLAYER *adv)
{
	ANIMALS animal;
	static char temp[180];
	int i;
	char *str_bow="%s raises %s bow and lets loose an arrow....";
	char str_angry[30];
	static char *angry_strings[]={"disgusted",
								  "annoyed",
								  "angry",
								  "dismayed",
								  "cross",
								  "furious"};

	if (pent_data.current_feature==SEA ||
		pent_data.current_feature==WATER)
	{
		sprintf(temp,"Hunting in water art fishing! But %s hath no rod!",adv->name);
		SCROLL(1,0,temp);

		bad_sound();

		return;
	}

	if (bard_is_singing(adv,"hunt for food"))
		return;

	if (!adv->arrows)
	{
		sprintf(temp,"%s requires arrows to hunt!",adv->name);
		GX(temp,BAD);
		return;
	}

	if (!player_is_carrying(adv,BOW))
	{
		sprintf(temp,"%s requires a long bow to hunt!",adv->name);
		GX(temp,BAD);
		return;
	}

	i=rand()%SIZE(angry_strings);
	strcpy(str_angry,angry_strings[i]);

	if (actually_hunt_find_chance(adv)>=percent() && adv->food<MAX_FOOD)
	{
		i=actually_hunt_get_animal();

		animal=animals[i];

		sprintf(temp,"After a few minutes of stalking, %s spots a %s.",
					adv->name,
					animal.name);

		SCROLL(1,1,temp);

		pause(2);

		if (effective_hunt(adv)>=percent())
		{
			sprintf(temp,str_bow,adv->name,adv->his_her);

			SCROLL(1,1,temp);

			switch(rand()%3)
			{
				case 0: sprintf(temp,"Killing ye %s stone-dead!",
									animal.name);
						break;

				case 1: sprintf(temp,"%s%s arrow pierces ye %s, killing it instantly.",
									adv->name,
									end_s(adv->name),
									animal.name);
						break;

				default:sprintf(temp,"%s%s arrow finds it's mark! Ye %s twitches "
									 "a little, then dies!",
									 adv->name,
									 end_s(adv->name),
									 animal.name);
			}

			SCROLL(1,1,temp);

			good_sound();

			pause(1);

			for (i=0; i<=P_NUM; i++)
			{
				if (player_is_alive(&TPP[i]))
				{
					TPP[i].food+=animal.size;

					if (TPP[i].food>=MAX_FOOD)
						TPP[i].food=MAX_FOOD;

					sprintf(temp,"%s takes some food!",TPP[i].name);
					SCROLL(0,14,temp);

					general_low_sound();
				}
			}

			adv->arrows--;

			add_xp_to_party((long)animal.size*25L);

			add_to_professionalism(adv,1);
		}
		else
		{
			switch(rand()%10)
			{
				case 0:  sprintf(temp,"Ye %s sniffs %s%s scent and scampers away quickly!",
									animal.name,
									adv->name,
									end_s(adv->name));
						 break;

				case 1:  sprintf(temp,"%s looses an arrow, but misses ye %s.",
									adv->name,
									animal.name);

						 adv->arrows--;
						 break;

				case 2:  sprintf(temp,"Ye %s hears %s and runs off quickly!",
									 animal.name,
									 adv->name);
						 break;

				default: strcpy(temp,actually_hunt_get_damaged(adv,&animal));
						 break;
			}

			SCROLL(1,0,temp);
			bad_sound();

			sprintf(temp,"%s returns to %s fellow adventurers %s with %sself.",
						adv->name,
						adv->his_her,
						str_angry,
						adv->him_her);

			SCROLL(1,0,temp);
			solemn_sound();
		}
	}
	else
	{
		sprintf(temp,"Luck shines not on %s! %s returns to thy party "
					 "%s with %sself, with no prey.",
					 adv->name,
					 adv->he_she,
					 str_angry,
					 adv->him_her);

		SCROLL(1,0,temp);
		solemn_sound();
	}
}

int _PASCAL actually_hunt_get_animal()
{
	int i;
	int pc=percent();

	if (pc<=70)
		i=0;                /* COMMON   */
	else
	if (pc>70 && pc<=95)
		i=4;                /* UNCOMMON */
	else
		i=8;                /* RARE     */

	i+=rand()%4;

	return(i);
}

int _PASCAL actually_hunt_find_chance(PLAYER *adv)
{
	int res;

	switch(pent_data.season)
	{
		case SPRING : res=8;  break;
		case SUMMER : res=12; break;
		case AUTUMN : res=7;  break;
		case WINTER : res=4;  break;
	}

	switch(pent_data.current_feature)
	{
		 case GRASS         : res+=1 ; break;
		 case FOREST        : res+=5 ; break;
		 case HILLS         : res+=5 ; break;
		 case MOUNTAINS     : res+=4 ; break;
		 case HIGH_MOUNTAINS: res+=3 ; break;
		 case MARSH         : res+=4 ; break;
		 case PATH          : res+=2 ; break;
		 case CELTIC_CROSS  : res+=5 ; break;
		 default            :          break;
	}

	res+=(effective_luck(adv)/3);

	if (is_night_time())
		res/=2;

	if (adv->nclass==HUNTER)
		res*=2;

	return(res);
}

char *_PASCAL actually_hunt_get_damaged(PLAYER *adv,ANIMALS *animal)
{
	static char temp[160];

	switch(rand()%2)
	{
		case 0 : if (animal->ram_damage)
					strcpy(temp,actually_hunt_ram(adv,animal));
				 else
					strcpy(temp,actually_hunt_bite(adv,animal));

				 break;

		default: if (animal->bite_damage)
					strcpy(temp,actually_hunt_bite(adv,animal));
				 else
					strcpy(temp,actually_hunt_ram(adv,animal));

				 break;
	}

	return(temp);
}

char *_PASCAL actually_hunt_ram(PLAYER *adv,ANIMALS *animal)
{
	static char temp[160];
	int damage;

	damage=rand()%animal->ram_damage;
	damage++;

	adv->current_hp-=damage;

	if (adv->current_hp<=0)                 /* Never die from hunting! */
		adv->current_hp=1;

	sprintf(temp,"Ye %s charges at %s, knocking %s to ye "
				 "ground for %d damage before running off!",
				 animal->name,
				 adv->name,
				 adv->name,
				 damage);

	return(temp);
}

char *_PASCAL actually_hunt_bite(PLAYER *adv,ANIMALS *animal)
{
	static char temp[160];
	int damage;

	damage=rand()%animal->bite_damage;
	damage++;

	adv->current_hp-=damage;

	if (adv->current_hp<=0)                 /* Never die from hunting! */
		adv->current_hp=1;

	sprintf(temp,"%s creeps up on ye %s, but by instinct, it "
				 "bites %s for %d damage, before running off!",
				 adv->name,
				 animal->name,
				 adv->him_her,
				 damage);

	return(temp);
}
