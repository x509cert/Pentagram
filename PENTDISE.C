#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")


void _PASCAL contract_diseases_in_combat(PLAYER *adv,MONSTER *mon)
{
	if (adv->disease!=NO_DISEASE)
		return;

	if (effective_disease_immunity(adv)>=percent())
		return;

	switch(mon->disease_type)
	{
		case GRAVE_ROT  : contract_grave_rot(adv);break;
		case PLAGUE     : contract_plague(adv);   break;
		case POX        : contract_pox(adv);      break;
		default         :                         break;
	}
}

void _PASCAL contract_grave_rot(PLAYER *adv)
{
	adv->disease                =GRAVE_ROT;
	adv->disease_how_long       =0;
	adv->disease_onset_time     =rand()%7+7;    /* 7-14 days */
	adv->disease_symptoms_given =FALSE;
	adv->disease_wear_off       =rand()%7-7;    /* 7-14 days */
}

void _PASCAL contract_pox(PLAYER *adv)
{
	adv->disease                =POX;
	adv->disease_how_long       =0;
	adv->disease_onset_time     =rand()%3+14;    /* 3-17 days */
	adv->disease_symptoms_given =FALSE;
	adv->disease_wear_off       =9999;           /* Never Recover! */
}

void _PASCAL contract_plague(PLAYER *adv)
{
	adv->disease                =PLAGUE;
	adv->disease_how_long       =0;
	adv->disease_onset_time     =rand()%3+14;    /* 3-17 days */
	adv->disease_symptoms_given =FALSE;
	adv->disease_wear_off       =9999;           /* Never Recover! */
}

void _PASCAL disease_update_all_players()
{
	int i;

	if (P_NUM)
	{
		for (i=0; i<=P_NUM; i++)
		{
			if (TPP[i].disease!=NO_DISEASE)
			{
				if (player_is_alive(&TPP[i]))
				{
					TPP[i].disease_how_long++;

					if (TPP[i].disease_how_long >= TPP[i].disease_onset_time)
					{
						disease_display_symptoms(&TPP[i]);
						disease_inflict_damage(&TPP[i]);
					}

					if (TPP[i].disease_how_long >= TPP[i].disease_wear_off)
						recover_from_disease(&TPP[i]);
				}
			}
		}
	}
}

void _PASCAL disease_inflict_damage(PLAYER *adv)
{
	int damage;

	switch(adv->disease)
	{
		case GRAVE_ROT  :  damage=1+(adv->level*2); break;
		case PLAGUE     :  damage=1+(adv->hp/10);   break;
		case POX        :  damage=1+(adv->hp/5);    break;
		default         :  damage=0;                break;
	}

	if (damage)
	{
		damage+=(adv->disease_how_long-adv->disease_onset_time);
		reduce_hp(adv,damage,FROM_DISEASE);
	}
}

void _PASCAL disease_display_symptoms(PLAYER *adv)
{
	static char temp[150];

	if (adv->disease!=NO_DISEASE)
	{
		if (adv->disease_symptoms_given)
			if (percent()>=effective_luck(adv)*2)
				return;

		if (adv->disease_symptoms_given)
		{
			switch(adv->disease)
			{
				case GRAVE_ROT	: sprintf(temp,"%s%s skin art quite death-like!",
											adv->name,
											end_s(adv->name));
								  break;

				case PLAGUE 	: sprintf(temp,"%s art feeling very nauseous!",
											adv->name);
								  break;

				case POX        : sprintf(temp,"More sores appear on %s%s body!",
											adv->name,
											end_s(adv->name));
								  break;

				default         : break;
			}
		}
		else
		{
			switch(adv->disease)
			{
				case GRAVE_ROT  : sprintf(temp,"%s noticies %s skin art going pale and flakey!",
											adv->name,
											adv->his_her);
								  break;

				case PLAGUE 	: sprintf(temp,"%s feels weak and nauseous!",
											adv->name);
								  break;

				case POX        : sprintf(temp,"%s noticies red sores appearing on %s face and hands!",
											adv->name,
											adv->his_her);
								  break;

				default         : break;
			}
		}

		SCROLL(2,0,temp);

		symptoms_sound();

		adv->disease_symptoms_given =TRUE;
	}
}

void _PASCAL recover_from_disease(PLAYER *adv)
{
	adv->disease                =NO_DISEASE;
	adv->disease_onset_time     =0;
	adv->disease_symptoms_given =FALSE;
	adv->disease_wear_off       =0;
}
