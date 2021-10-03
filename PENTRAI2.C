#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <ctype.h>

void _PASCAL train_get_age()
{
	 int i;
	 int temp;

	 static struct age_cat {
						unsigned int young_adult;
						unsigned int mature;
						unsigned int middle_aged;
						unsigned int old;
						unsigned int venerable;
					} ages[10] = {{0,0,0,0,0},
								  {14,21,41,61,91},           /* Human     */
								  {100,176,551,876,1201},	  /* High Elf  */
								  {35,51,151,251,351},        /* Dwarf     */
								  {22,34,69,102,145},         /* Halfling  */
								  {100,176,551,876,1201},     /* Sylvan Elf*/
								  {50,91,301,451,601},        /* Gnome     */
								  {40,61,176,276,401},        /* Half Ogre */
								  {100,176,551,876,1201}};    /* Dark Elf  */

	 i=percent();             /* 1 = Young, 2 = Mature, etc */
	 i++;
	 switch(adv.nclass)
	 {
		 case DUELIST       :
		 case HUNTER        :
		 case BARD          :
		 case WARRIOR       :
								if (i<=60)
								   temp = 1;
								else
								   temp = 2;
								break;

		 case WIZARD        :
		 case ILLUSIONIST   :
								if (i<=33)
								   temp = 2;
								else if (i<=60)
								   temp = 3;
								else
								   temp = 4;
								break;

		 case PRIEST        :
		 case MONK          :
								if (i<=50)
								   temp = 2;
								else
								   temp = 3;
								break;

		 case RANGER        :
								if (i<=70)
								   temp = 2;
								else
								   temp = 3;
								break;

		 case CRUSADER      :
								if (i<=10)
								   temp = 1;
								else if (i<=80)
								   temp = 2;
								else
								   temp = 3;
								break;

		 case DRUID         :
								if (i<=33)
								   temp = 2;
								else if (i<=50)
								   temp = 3;
								else
								   temp = 4;
								break;

		 case THIEF         :
								if(i<=60)
									temp=1;
								else
									temp=2;
								break;
	 }

	 switch(temp)
	 {
		   case 1 : adv.nage = ages[adv.nrace].young_adult; adv.nage += rand()%6;  break;
		   case 2 : adv.nage = ages[adv.nrace].mature;      adv.nage += rand()%18; break;
		   case 3 : adv.nage = ages[adv.nrace].middle_aged; adv.nage += rand()%18; break;
		   case 4 : adv.nage = ages[adv.nrace].old;         adv.nage += rand()%26; break;
		   case 5 : adv.nage = ages[adv.nrace].venerable;   adv.nage += rand()%25; break;
	 }
}

void _PASCAL train_get_age_cat()
{
	 static char *age_types[] =  {"(Young Adult)",
								  "(Mature)",
								  "(Middle Aged)",
								  "(Old)",
								  "(Venerable)"};

	 static struct age_cat {
								int young_adult;
								int mature;
								int middle_aged;
								int old;
								int venerable;
					} ages[10] = {{0,0,0,0,0},
								  {12,21,41,61,91}, 	   /* Human 	*/
								  {90,176,551,876,1201},   /* High Elf	*/
								  {25,51,151,251,351},	   /* Dwarf 	*/
								  {12,34,69,102,145},	   /* Halfling	*/
								  {90,176,551,876,1201},   /* Sylvan Elf*/
								  {40,91,301,451,601},	   /* Gnome 	*/
								  {30,61,176,276,401},	   /* Half Ogre */
								  {90,176,551,876,1201}};  /* Dark Elf  */

	  if (adv.nage > ages[adv.nrace].young_adult)
		 strcpy(adv.age,age_types[0]);

	  if (adv.nage > ages[adv.nrace].mature)
		 strcpy(adv.age,age_types[1]);

	  if (adv.nage > ages[adv.nrace].middle_aged)
		 strcpy(adv.age,age_types[2]);

	  if (adv.nage > ages[adv.nrace].old)
		 strcpy(adv.age,age_types[3]);

	  if (adv.nage > ages[adv.nrace].venerable)
		 strcpy(adv.age,age_types[4]);
}

void _PASCAL train_get_hand()
{
	int D5=get_dice_roll(5,1,0);
	int D10=get_dice_roll(10,1,0);

	if (D5>D10)
		adv.hand=HAND_LEFT;
	else
	if (D5<D10)
		adv.hand=HAND_RIGHT;
	else
		adv.hand=HAND_AMBIDEXTROUS;
}

void _PASCAL train_get_place_of_birth()
{
	int i;

	i=rand()%22;

	strcpy(adv.where_born,small_towns[i].name);
}

void _PASCAL train_get_hp()
{
	int hp;

	switch(adv.nclass)
	{
		case WARRIOR    : hp=10; break;

		case PRIEST     :
		case CRUSADER   :
		case HUNTER     :
		case DUELIST    :
		case RANGER     : hp=8; break;

		case BARD       :
		case MONK       :
		case THIEF      : hp=6; break;

		case ILLUSIONIST:
		case DRUID      :
		case WIZARD     : hp=4; break;
	}

	adv.hp=rand()%hp+1;

	if (adv.nrace==HALF_OGRE)
		adv.hp+=3;

	if (adv.nrace==DWARF)
		adv.hp+=2;

	switch(effective_toughness(&adv))
	{
		case 15 : adv.hp++;  break;
		case 16 : adv.hp+=2; break;
		case 17 : adv.hp+=3; break;
		case 18 : adv.hp+=4; break;
		case 19 : adv.hp+=5; break;
		case 20 : adv.hp+=6; break;
	}

	adv.hp=(adv.hp<4?3:adv.hp);
	adv.current_hp=adv.hp;
}

void _PASCAL train_get_birthday()
{
	unsigned int i;
	char temp1[50],temp2[50];

	i=rand()%340;
	i+=10;

	strcpy(temp1,give_date(i));
	strcpy(temp2,strchr(temp1,','));
	strcpy(adv.birthday,&temp2[2]);
	adv.birth_date=i;
}

void _PASCAL train_get_speed()
{
	switch(adv.nrace)
	{
		case DWARF      :  adv.speed=10;
						   break;

		case HIGH_ELF	:  adv.speed=12;
						   break;

		case GNOME      :  adv.speed=10;
						   break;

		case HALF_OGRE  :  adv.speed=8;
						   break;

		case HALFLING   :  adv.speed=13;
						   break;

		case HUMAN      :  adv.speed=10;
						   break;

		case SYLVAN_ELF :  adv.speed=12;
						   break;

		case DARK_ELF   :  adv.speed=12;
						   break;
	}
}

void _PASCAL train_get_max_level()
{
	switch(adv.nrace)
	{
		case DWARF      :   switch(adv.nclass)
							{
								case WARRIOR    : adv.max_level=15; break;
								case PRIEST     : adv.max_level=10; break;
								case WIZARD     : adv.max_level=8 ; break;
								case DRUID      : adv.max_level=10; break;
								case THIEF      : adv.max_level=15; break;
								case RANGER     : adv.max_level=10; break;
							}

							break;

		case HIGH_ELF	:	switch(adv.nclass)
							{
								case WARRIOR    : adv.max_level=12; break;
								case PRIEST     : adv.max_level=12; break;
								case WIZARD     : adv.max_level=10; break;
								case DRUID      : adv.max_level=12; break;
								case THIEF      : adv.max_level=15; break;
								case BARD       : adv.max_level=15; break;
								case RANGER     : adv.max_level=10; break;
								case ILLUSIONIST: adv.max_level=8 ; break;
								case DUELIST    : adv.max_level=10; break;
							}

							break;

		case GNOME      :   switch(adv.nclass)
							{
								case WARRIOR    : adv.max_level=12; break;
								case PRIEST     : adv.max_level=10; break;
								case THIEF      : adv.max_level=15; break;
								case RANGER     : adv.max_level=10; break;
								case ILLUSIONIST: adv.max_level=15; break;
							}

							break;

		case HALF_OGRE  :   switch(adv.nclass)
							{
								case WARRIOR    : adv.max_level=8;  break;
								case HUNTER     : adv.max_level=9;  break;
							}

							break;

		case HALFLING   :   switch(adv.nclass)
							{
								case WARRIOR    : adv.max_level=10; break;
								case THIEF      : adv.max_level=15; break;
							}

							break;

		case HUMAN      :   adv.max_level=15;
							break;

		case SYLVAN_ELF :   switch(adv.nclass)
							{
								case WARRIOR    : adv.max_level=10; break;
								case THIEF      : adv.max_level=12; break;
								case BARD       : adv.max_level=15; break;
								case DUELIST    : adv.max_level=8 ; break;
								case HUNTER     : adv.max_level=15; break;
								case DRUID      : adv.max_level=15; break;
								case RANGER     : adv.max_level=15; break;
							}

							break;

		case DARK_ELF   :   switch(adv.nclass)
							{
								case WARRIOR    : adv.max_level=12; break;
								case THIEF      : adv.max_level=15; break;
								case WIZARD     : adv.max_level=12; break;
								case ILLUSIONIST: adv.max_level=10; break;
							}

							break;
	}
}

void _PASCAL train_get_languages()
{
	int i,j;

	switch(adv.nrace)
	{
		case DWARF      :  adv.languages=LAN_OLD_TONGUE|LAN_DWARFISH;
						   break;

		case HIGH_ELF	:  adv.languages=LAN_OLD_TONGUE|LAN_ELVISH;
						   break;

		case GNOME      :  adv.languages=LAN_OLD_TONGUE|LAN_DWARFISH;
						   break;

		case HALF_OGRE  :  adv.languages=LAN_OLD_TONGUE|LAN_OGRISH;
						   break;

		case HALFLING   :  adv.languages=LAN_OLD_TONGUE;
						   break;

		case HUMAN      :  adv.languages=LAN_OLD_TONGUE;
						   break;

		case SYLVAN_ELF :  adv.languages=LAN_OLD_TONGUE|LAN_ELVISH;
						   break;

		case DARK_ELF   :  adv.languages=LAN_OLD_TONGUE|LAN_UNDERWURLDE;
						   break;
	}

	if (((strnicmp(adv.deity_name,"Solon",5)==0) || (adv.intelligence>=16))
		  && (adv.nrace==HALFLING || adv.nrace==HUMAN))
	{
		i=rand()%6;
		i++;

		j=1<<i;

		adv.languages|=j;
	}
}
