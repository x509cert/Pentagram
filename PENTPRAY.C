#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

DEITY_TYPE  deities[]={
					   {"Athin",	"Father",	   "of",	"Battle",  SX_MALE,    D_ATHIN},
					   {"Tarl",     "Deity",       "of",    "Wealth",  SX_MALE,    D_TARL},
					   {"Olric",    "Mother",      "of",    "Safety",  SX_FEMALE,  D_OLRIC},
					   {"Aerdri",   "Deity",       "of",    "Weather", SX_FEMALE,  D_AERDRI},
					   {"Celanil",  "Deity",       "of",    "Love",    SX_FEMALE,  D_CELANIL},
					   {"Dumathin", "Keeper",      "of ye", "Earth",   SX_MALE,    D_DUMATHIN},
					   {"Cyrr",     "Lord",        "of ye", "Seas",    SX_MALE,    D_CYRR},
					   {"Magmi",    "Deity",       "of",    "Fire",    SX_MALE,    D_MAGMI},
					   {"Morr",     "Lady",        "of",    "Death",   SX_FEMALE,  D_MORR},
					   {"Rhyaa",    "Father",      "of",    "Mercy",   SX_MALE,    D_RHYAA},
					   {"Solonir",  "Grandfather", "of",    "Learning",SX_MALE,    D_SOLONIR},
					   {"Enoreth",	"Deity",	   "of",	"Travel",  SX_FEMALE,  D_ENORETH}
					  };

void _PASCAL train_get_deity()
{
	char *t2="ATOeCDyMrhSn";
	char *t3="ATOECDYMRhSN";
	char letter[2];
	static int boundary[]={16,16, 294,22,
						   16,24, 294,30,
						   16,32, 294,38,
						   16,40, 294,46,
						   16,48, 294,54,
						   16,56, 294,62,
						   16,64, 294,70,
						   16,72, 294,78,
						   16,80, 294,86,
						   16,88, 294,94,
						   16,96, 294,102,
						   16,104,294,110,
						   -1,-1, -1,-1};
	GWINDOW win;
	int i,j,num;
	char temp[80];

	if (adv.nclass==DRUID)
	{
		strcpy(adv.deity_name,"Skrymyyr");
		strcpy(adv.deity_control,"Nature");
		return;
	}

	if (adv.nclass!=PRIEST   &&
		adv.nclass!=CRUSADER &&
		adv.nclass!=MONK)
	{
		strcpy(adv.deity_name,"None");
		strcpy(adv.deity_control,"N/A");
		return;
	}

	cls_scroll();
	scroll_wrap_write(14,"WHICH DEITY DOTH THEE WORSHIP?");

	win.x1=2;
	win.y1=2;
	win.x2=39;
	win.y2=16;
	win.border=4;
	win.back=0;

	make_gwindow(&win);

	for (i=0; i<SIZE(deities); i++)
	{
		_settextposition(i+3,3);
		_settextcolor(5);

		strcpy(temp,deities[i].name);

		for (j=strlen(deities[i].name)+
			   strlen(deities[i].title)+
			   strlen(deities[i].connect)+
			   strlen(deities[i].sphere)+2; j<35; j++)
					strcat(temp,"ù");

		_outtext(temp);

		sprintf(temp,"%s %s %s",deities[i].title,
								deities[i].connect,
								deities[i].sphere);
		_outtext(temp);

		for (j=0; j<(int)strlen(deities[i].name); j++)
		{
			if (deities[i].name[j]==t2[i])
			{
				letter[0]=t2[i];
				letter[1]='\0';

				_settextposition(i+3,3+j);
				_settextcolor(13);
				_outtext(letter);

				break;
			}
		}
	}

	short_prompt_sound();

	num=mouse_in_range(boundary,t3,"");

	strcpy(adv.deity_name,   deities[num].name);
	strcpy(adv.deity_control,deities[num].sphere);
	adv.ndeity              =deities[num].ndeity;
	adv.year_last_pray		=pent_data.year;
	adv.day_last_pray		=max(2,pent_data.date-(rand()%10)+4);

	switch(num)
	{
		case 0 : adv.secondary_attrib[ATTACK]+=5;
				 adv.secondary_attrib[SURVIVAL]-=5;
				 break;

		case 1 : adv.banked+=rand()%50+10;
				 adv.secondary_attrib[ATTACK]-=5;
				 break;

		case 2 : adv.secondary_attrib[PARRY]+=5;
				 adv.secondary_attrib[ATTACK]-=5;
				 break;

		case 3 : adv.secondary_attrib[MISSILE]+=5;
				 adv.secondary_attrib[IMMUNITY_DISEASE]-=5;
				 break;

		case 4 : adv.secondary_attrib[HEAL]+=5;
				 adv.secondary_attrib[ATTACK]-=5;
				 break;

		case 5 : adv.secondary_attrib[HUNT]+=5;
				 adv.secondary_attrib[SWIM]-=5;
				 break;

		case 6 : adv.secondary_attrib[SWIM]+=5;
				 adv.secondary_attrib[HUNT]-=5;
				 break;

		case 7 : adv.secondary_attrib[ATTACK]+=5;
				 adv.secondary_attrib[HEAL]-=5;
				 break;

		case 8 : adv.secondary_attrib[ATTACK]+=5;
				 adv.secondary_attrib[SURVIVAL]-=5;
				 break;

		case 9 : adv.secondary_attrib[HEAL]+=5;
				 adv.secondary_attrib[ATTACK]-=5;
				 break;

		case 10: adv.secondary_attrib[HUNT]+=5;
				 adv.secondary_attrib[PARRY]-=5;
				 break;

		case 11: adv.secondary_attrib[SURVIVAL]+=5;
				 adv.secondary_attrib[LISTEN]-=5;
				 break;
	}

	kill_gwindow(&win);
}

void _PASCAL cath_pray(PLAYER *adv)
{
	char temp[80];
	int num=get_town_num(pent_data.x,pent_data.y);
	int i,dnum;

	if (adv->nclass!=CRUSADER &&
		adv->nclass!=MONK     &&
		adv->nclass!=PRIEST)
	{
		GX("Only Priests, Monks and Crusaders may pray!",BAD);
		return;
	}

	if (adv->ndeity!=small_towns[num].ndeity)
	{
		for (i=0; i<SIZE(deities); i++)
			if (deities[i].ndeity==small_towns[num].ndeity)
				dnum=i;

		sprintf(temp,"This art a shrine to %s, not %s! Be gone!",
				   deities[dnum].name,
				   adv->deity_name);

		GX(temp,BAD);

		return;
	}

	adv->year_last_pray         =pent_data.year;
	adv->day_last_pray			=pent_data.date;

	adv->current_hp             =adv->hp;
	adv->current_divine_points  =adv->divine_points;

	sprintf(temp,"%s kneels down and meditates peacefully!",adv->name);
	GX(temp,GOOD);

	sprintf(temp,"After %s prayers, %s feels enlightened!",
					adv->his_her,
					adv->name);
	GX(temp,PRAY);
}

char *get_deity_name_in_town(int x,int y)
{
	int i,num;
	int tnum=get_town_num(x,y);

	for (i=0; i<SIZE(deities); i++)
		if (deities[i].ndeity==small_towns[tnum].ndeity)
			num=i;

	return(deities[num].name);
}

void _PASCAL deity_angry(PLAYER *adv)
{
	char temp[160];
	char *vis="At midnight %s perceives %s vision of %s.";
	static char *adj[]={"an upsetting",
						"a distressing",
						"a tormenting",
						"a worrying"};
	static char *sight[]={"a bloody battle between rival orc tribes",
						  "a ruthless witch trial",
						  "a witch swinging slowly in a noose",
						  "a witch digging up corpses in a moonlit graveyard",
						  "an angry deity executing a disloyal cleric",
						  "an angry deity creating an earthquake",
						  "a great plague-ridden landscape"};

	if (percent()>75)
		return;

	sprintf(temp,
			vis,
			adv->name,
			adj[rand()%SIZE(adj)],
			sight[rand()%SIZE(sight)]);

	SCROLL(1,0,temp);

	solemn_sound();

	pause(2);
}
