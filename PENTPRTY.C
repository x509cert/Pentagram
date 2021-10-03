#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <ctype.h>
#include <butil.h>

#ifndef DEV
#pragma optimize("z",on)
#endif

int _PASCAL check_party_globals_in_effect(int eff)	/* Checks all the people in */
{													/* the party. An effect is	*/
													/* is passed, and if one of */
	int res=ERR;									/* the people has a the eff-*/
	int i;											/* in effect, then that 	*/
	IN_EFFECT *in;									/* players number is retured*/
													/* Otherwise ERR returned	*/
	for (i=0; i<MAX_PARTY; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			in=&TPP[i].in_effect;

			switch(eff)
			{
				case IN_EFFECT_WINDSONG 			 : if (in->windsong)		 res=i; break;
				case IN_EFFECT_WAYFARERS_TUNE		 : if (in->wayfarers_tune)	 res=i; break;
				case IN_EFFECT_TALE_OF_YULDAR		 : if (in->tale_of_yuldar)	 res=i; break;
				case IN_EFFECT_PALISORS_DREAM		 : if (in->palisors_dream)	 res=i; break;
				case IN_EFFECT_DAYLIGHT_FALLS		 : if (in->daylight_falls)	 res=i; break;
				case IN_EFFECT_HUNTERS_POEM 		 : if (in->hunters_poem)	 res=i; break;
				case IN_EFFECT_LIGHT                 : if (in->twilight      ||
														   in->lantern_lit	 ||
														   in->alethran)		 res=i; break;
				case IN_EFFECT_PROT_FROM_TRAPS		 : if (in->prot_traps)		 res=i; break;
				case IN_EFFECT_WALK_ON_WATER		 : if (in->walk_on_water)	 res=i; break;
				case IN_EFFECT_TANGLE_THORNS		 : if (in->tangle_thorns)	 res=i; break;
				case IN_EFFECT_MIRAGE                : if (in->mirage)           res=i; break;
				case IN_EFFECT_AURA_OF_PROTECTION	 : if (in->aura_protection)  res=i; break;
				case IN_EFFECT_SWIFTNESS			 : if (in->swiftness)		 res=i; break;
				case IN_EFFECT_SPELL_OF_PASSAGE 	 : if (in->spell_of_passage) res=i; break;
				case IN_EFFECT_TRUEFLIGHT			 : if (in->trueflight)		 res=i; break;
				case IN_EFFECT_MISSILE_CLOAK		 : if (in->missile_cloak)	 res=i; break;

				default 							 : res=ERR; break;
			}
		}

		if (res!=ERR)
			break;
	}

	return(res);
}

void _PASCAL update_in_effects()	 /* Called each turn */
{
	int i;
	IN_EFFECT *effect;
	char *spell, *potion, *song;
	static char temp[200];
	char *verb;

	if (IN_COMBAT)		  /* If called accidently pass to combat */
	{
		update_combat_in_effects();
		return;
	}

	for (i=0; i<=P_NUM; i++)
	{
		spell=potion=song="~";

		if (player_is_dead(&TPP[i]))
			continue;

		effect=&TPP[i].in_effect;

		if (effect->prot_traps)
			if (!--effect->prot_traps)
				spell=STR_PROT_FROM_TRAPS;

		if (effect->mirage)
			if (!--effect->mirage)
				spell=STR_MIRAGE;

		if (effect->sly_ears)
			if (!--effect->sly_ears)
				spell=STR_SLY_EARS;

		if (effect->cats_eyes)
			if (!--effect->cats_eyes)
				spell=STR_CATS_EYES;

		if (effect->poison_immunity)
			if (!--effect->poison_immunity)
				spell=STR_POISON_IMMUNITY;

		if (effect->find_hidden_doors)
			if (!--effect->find_hidden_doors)
				spell=STR_FIND_HIDDEN_DOOR;

		if (effect->spell_of_passage)
			if (!--effect->spell_of_passage)
				spell=STR_SPELL_OF_PASSAGE;

		if (effect->missile_cloak)
			if (!--effect->missile_cloak)
				spell=STR_MISSILE_CLOAK;

											/* All purpose Spells */
		if (effect->lantern_lit)
		{
			if (!--effect->lantern_lit)
			{
				sprintf(temp,"%s%s lantern goes out...",
						TPP[i].name,
						end_s(TPP[i].name));

				SCROLL(1,0,temp);

				if (!NO_SOUND)
				{
					utspkr(100);
					delay(30);
					utspkr(0);
				}
			}
		}

		if (effect->twilight)
			if (!--effect->twilight)
				spell=STR_TWILIGHT;

		if (effect->prot_fire)
			if (!--effect->prot_fire)
				spell=STR_PROT_FROM_FIRE;

		if (effect->prot_cold)
			if (!--effect->prot_cold)
				spell=STR_PROT_FROM_COLD;

		if (effect->trueflight)
			if (!--effect->trueflight)
				spell=STR_TRUEFLIGHT;

		if (effect->walk_on_water)
			if (!--effect->walk_on_water)
				spell=STR_WALK_ON_WATER;


											/* Potions */
		if (effect->pot_holy_water)
			if (!--effect->pot_holy_water)
				potion="Holy Water";

		if (effect->pot_striking)
			if (!--effect->pot_striking)
				potion="Striking";

		if (effect->pot_undead_turn)
			if (!--effect->pot_undead_turn)
				potion="Undead Turning";

		if (effect->pot_fire_resist)
			if (!--effect->pot_fire_resist)
				potion="Fire Resistance";

		if (effect->pot_cold_resist)
			if (!--effect->pot_cold_resist)
				potion="Cold Resistance";

		if (effect->pot_strength)
			if (!--effect->pot_strength)
				potion="Strength";

											/* Bard Songs */
		if (effect->windsong)
			if (!--effect->windsong)
				song="Windsong";

		if (effect->wayfarers_tune)
			if (!--effect->wayfarers_tune)
				song="Wayfarers Tune";

		if (effect->alethran)
			if (!--effect->alethran)
				song="Alethran";

		if (effect->tale_of_yuldar)
			if (!--effect->tale_of_yuldar)
				song="Tale of Yuldar";

		if (effect->palisors_dream)
			if (!--effect->palisors_dream)
				song="Palisors Dream";

		if (effect->daylight_falls)
			if (!--effect->daylight_falls)
				song="Daylight Falls";

		if (effect->hunters_poem)
			if (!--effect->hunters_poem)
				song="Hunters Poem";

		if (!IN_COMBAT)
		{
			if (*potion!='~')
			{
				sprintf(temp,"%s%s potion of %s finishes!",
						 TPP[i].name,
						 end_s(TPP[i].name),
						 potion);

				SCROLL(1,0,temp);

				spell_finished_sound();
			}

			if (*song!='~')
			{
				sprintf(temp,"%s finishes singing %s.",TPP[i].name,song);

				SCROLL(1,0,temp);

				spell_finished_sound();
			}

			if (*spell!='~')
			{
				switch(rand()%4)
				{
					case 0  : verb="fades out...";       break;
					case 1  : verb="fizzles out...";     break;
					case 2  : verb="runs out...";        break;
					default : verb="comes to an end..."; break;
				}

				sprintf(temp,"%s%s %s spell %s",
						TPP[i].name,
						end_s(TPP[i].name),
						spell,
						verb);

				SCROLL(1,0,temp);

				spell_finished_sound();
			}
		}
	}
}

void _PASCAL update_combat_in_effects() 	/* Called each combat round */
{
	int i;
	IN_EFFECT *effect;

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_dead(&TPP[i]))
			continue;

		effect=&TPP[i].in_effect;

		if (effect->trueflight)
			--effect->trueflight;

		if (effect->tangle_thorns)
			--effect->tangle_thorns;

		if (effect->mighty_appearance)
			--effect->mighty_appearance;

		if (effect->axels_shadow)
			--effect->axels_shadow;

		if (effect->aura_protection)
			--effect->aura_protection;

		if (effect->swiftness)
			--effect->swiftness;

		if (effect->hammerhand)
			--effect->hammerhand;

		if (effect->axels_blur)
			--effect->axels_blur;

		if (effect->axels_shimmer)
			--effect->axels_shimmer;

		if (effect->allys_dancing_dagger)
			--effect->allys_dancing_dagger;

		if (effect->allys_dancing_mace)
			--effect->allys_dancing_mace;

		if (effect->allys_dancing_sabre)
			--effect->allys_dancing_sabre;
	}
}

void _PASCAL update_hp_etc_whilst_walking()
{
	int i;
	char temp[80];

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			if (TPP[i].is_poisoned)
			{
				reduce_hp(&TPP[i],rand()%2,FROM_POISON);

				if (TPP[i].current_hp>0)
				{
					if (percent()>(50-effective_luck(&TPP[i])))
					{
						if (TPP[i].current_hp<=TPP[i].hp/3)
							sprintf(temp,"%s feels quite weak...",TPP[i].name);
						else
							sprintf(temp,"%s feels weaker.....",TPP[i].name);

						SCROLL(1,0,temp);

						short_bad_sound();
					}
				}
			}
		}
	}
}

#ifndef DEV
#pragma optimize("",on)
#endif

int _PASCAL init_party_for_adventure()
{
	int i;
	int some_alive=FALSE;

	if (!load_party_from_disc())
		return(FALSE);

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
			some_alive=TRUE;

		TPP[i].mins_last_food=TPP[i].last_food_bias;
	}

	if (!some_alive)
	{
		GX("Thine entire party art dead!",SOLEMN);
		return(FALSE);
	}

	the_party.adventuring=TRUE;
	IN_COMBAT=FALSE;
	the_party.all_dead=FALSE;

	generate_initial_party_order();

	null_all_professionalism();

	return(TRUE);
}

void _PASCAL generate_initial_party_order()
{
	int i,j,c;
	static PLAYER t;

	for (i=0; i<=P_NUM-1; i++)
	{
		c=i;
		t=TPP[i];

		for (j=i+1; j<=P_NUM; j++)
		{
			if (TPP[j].nclass < t.nclass)
			{
				c=j;
				t=TPP[j];
			}
		}

		TPP[c]=TPP[i];
		TPP[i]=t;
	}

	for (i=0; i<=P_NUM-1; i++)
	{
		if (TPP[i].nclass==TPP[i+1].nclass)
		{
			if (TPP[i].current_hp<TPP[i+1].current_hp)
			{
				t=TPP[i];
				TPP[i]=TPP[i+1];
				TPP[i+1]=t;
			}
		}
	}

	if (TPP[0].current_hp==0)         /* If leader has 0 HP */
	{
		for (i=0; i<=P_NUM; i++)
		{
			if (TPP[i].current_hp>0)
			{
				t=TPP[i];
				TPP[i]=TPP[0];
				TPP[0]=t;

				break;
			}
		}
	}

	for (i=0; i<=P_NUM; i++)
		strcpy(pent_data.order[i],TPP[i].file_name);
}

int _PASCAL adv_select_adventurer(char *title1,char *title2,int check_if_dead)
{
	GWINDOW win;
	char temp[80];
	static int boundary[]={132, 38,176, 66,
						   198, 38,232, 66,
						   132, 78,176,106,
						   198, 78,232,106,
						   132,120,176,146,
						   198,120,232,146,
						   170,162,205,174,
						   -1,-1,-1,-1};
	int selected;
	int fin=FALSE;
	int cntr;

	win.x1=16;
	win.y1=2;
	win.x2=32;
	win.y2=24;
	win.back=0;
	win.border=4;

	cntr=win.x1+((win.x2-win.x1)/2);

	make_gwindow(&win);

	_settextcolor(14);
	_settextposition(win.y1+1,cntr-strlen_half(title1));
	_outtext(title1);

	_settextposition(win.y1+2,cntr-strlen_half(title2));
	_outtext(title2);

	adv_arrange_draw();
	click_box(170,162,B_FINISH);

	while (!fin)
	{
		selected=mouse_in_range(boundary,"123456F","123456Q");

		if ((selected>P_NUM) && selected!=6)
		{
			bad_sound2();
			continue;
		}

		fin=TRUE;
	}

	kill_gwindow(&win);

	if (selected!=6)
	{
		memcpy((void *)&adv,&TPP[selected],sizeof(adv));

		if (check_if_dead)
		{
			if (player_is_dead(&TPP[selected]))
			{
				sprintf(temp,"%s ye %s art dead!",adv.name,adv.class);
				GX(temp,BAD);

				selected=6;
			}
		}
	}

	return(selected==6?ERR:selected);
}

void _PASCAL adv_arrange_draw()
{
	int i,j,xpos,ypos;
	char temp[80];

	for (i=0; i<=P_NUM; i++)
	{
		switch(i)
		{
			case 0 : xpos=145; ypos=40;  break;
			case 1 : xpos=205; ypos=40;  break;
			case 2 : xpos=145; ypos=80;  break;
			case 3 : xpos=205; ypos=80;  break;
			case 4 : xpos=145; ypos=120; break;
			case 5 : xpos=205; ypos=120; break;
		}

		draw_adv_image(TPP[i].nclass,xpos,ypos);

		if (player_is_dead(&TPP[i]))
				print_small_dead(xpos-1,
								 ypos+5,
								 14);

		sprintf(temp,"  %s",TPP[i].name);

		j=(xpos+8)-(strlen(temp)*4)/2;

		write_little(temp,
					 j,
					 ypos+22,
					 12,
					 FAST);

		sprintf(temp,"%d",i+1);

		write_little(temp,
					 j,
					 ypos+22,
					 14,
					 FAST);
	}
}

int _PASCAL get_random_live_person()
{
	int res;
	int found=ERR;
	int i;

	for (i=0; i<100; i++)
	{
		res=rand()%(P_NUM+1);

		if (player_is_alive(&TPP[res]))
		{
			found=res;
			break;
		}
	}

	if (found==ERR)
	{
		for (i=0; i<=P_NUM; i++)
		{
			if (player_is_alive(&TPP[i]))
			{
				found=res;
				break;
			}
		}
	}

	return(found);
}

void _PASCAL perform_death_of_party()
{
	int res;
	GWINDOW win;
	static int boundary[]={38,57,236,78,
						   38,85,250,104,
						   -1,-1,-1,-1};

	win.x1=4;
	win.y1=3;
	win.x2=34;
	win.y2=16;
	win.back=0;
	win.border=8;

	all_dead_sound();

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+3,win.y1*8,"DEADQUIT");

	short_prompt_sound();

	res=mouse_in_range(boundary,"QR","");

	kill_gwindow(&win);

	if (res)
	{
		nullify_all_in_effect_party();
		save_game(FALSE);
	}
	else
	{
		shut_program_down(FALSE);
	}
}

void _PASCAL add_to_player(int item,int type,int poisoned,int status,PLAYER *player)
{
	int i;

	if (number_of_items(player)>=MAX_CARRY)
		panic("add_to_player");

	for (i=0; player->items_carried[i].item!=NOTHING; i++)
		;

	player->items_carried[i].item     = item;
	player->items_carried[i].type     = type;
	player->items_carried[i].status   = status;
	player->items_carried[i].poisoned = poisoned;

	(void)number_of_items(player);
}

int _PASCAL get_first_live_person()
{
	int i;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
			return(i);

	return(ERR);
}

int _PASCAL someone_in_guild()
{
	int i;

	int res=FALSE;

	for (i=0; i<=P_NUM; i++)
		if (TPP[i].guild_member)
			res=TRUE;

	return(res);
}

int _PASCAL class_in_party(int class)		 /* Returns number of class in party */
{
	int i;
	int num=0;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]) &&
			TPP[i].nclass==class)
			num++;

	return(num);
}

void _PASCAL process_steps(int *steps)
{
	int i;
	char temp[80];
	char hunger[80];
	PLAYER *adv;

	update_in_effects();

	if (*steps>=STEPS_PER_HALF_HOUR)
	{
		for (i=0; i<=P_NUM; i++)
		{
			adv=&TPP[i];

			adv->mins_last_food+=30;

			if (player_is_dead(adv))
				continue;

			if (adv->mins_last_food>=FOOD_THRESHOLD)
			{
				adv->hungry++;
				adv->mins_last_food=0;

				if (adv->hungry!=NOT_HUNGRY)
				{
					if (adv->food!=0)
					{
						adv->hungry=NOT_HUNGRY;
						adv->food--;
					}
					else
					{
						switch(adv->hungry)
						{
							case  SLIGHT_HUNGER :   strcpy(hunger," art slightly hungry");   break;
							case  BELLY_RUMBLE  :   strcpy(hunger," hath a rumbling belly"); break;
							case  HUNGRY        :   strcpy(hunger," art hungry");            break;
							case  VERY_HUNGRY   :   strcpy(hunger," art very hungry");       break;
							default             :   strcpy(hunger," needs food quickly");    break;
						}

						sprintf(temp,"%s%s, and %s hath no food!",
									 adv->name,
									 hunger,
									 adv->he_she);

						SCROLL(1,14,temp);

						short_bad_sound();

						if (adv->hungry>=DANGEROUSLY_HUNGRY)
						{
							adv->hungry=DANGEROUSLY_HUNGRY;

							reduce_hp(&TPP[i],1,FROM_HUNGER);
						}
					}
				}
			}
		}

		*steps%=STEPS_PER_HALF_HOUR;
		pent_data.time_minute+=30;

		day_night();

		update_hp_etc_whilst_walking();
	}
}

int _PASCAL number_of_items(PLAYER *player)
{
	int i,j;

	for (i=0,j=0; i<MAX_CARRY; i++)
		if (player->items_carried[i].item!=NOTHING)
			j++;

	player->num_items_carried=j;

	return(j);
}

void _PASCAL get_party_combat_location(int *x,int *y)
{
	int i;
	int num_alive=0;
	int nx=0,ny=0;

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			nx+=TPP[i].x;
			ny+=TPP[i].y;
			num_alive++;
		}
	}

	if (num_alive)
	{
		nx/=num_alive;
		ny/=num_alive;
	}
	else
	{
		nx=CMBT_AREA_X/2;	/* Centre of combat area */
		ny=CMBT_AREA_Y/2;
	}

	*x=nx;
	*y=ny;
}

int _PASCAL average_level()
{
	int i;
	int total=0;
	int num_alive=0;

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]))
		{
			num_alive++;
			total+=TPP[i].level;
		}
	}

	return(num_alive?total/num_alive:1);
}

int _PASCAL modified_average_level()
{
	int av=average_level();

	if (IN_DUNGEON)
		av+=the_party.dungeon_level;

	return(av);
}

int _PASCAL party_can_carry_treasure()
{
	int i;
	int res=FALSE;

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_carrying(&TPP[i],SACK) ||
			player_is_carrying(&TPP[i],BACK_PACK))
		{
			res=TRUE;
			break;
		}
	}

	if (!res)
	{
		SCROLL(1,0,"Thy party hath naught to carry ye treasure in!");
		solemn_sound();
	}

	return(res);
}

char *end_s(char *word)
{
	return(toupper((int)word[strlen(word)-1])==(int)'S'?"'":"'s");
}

void _PASCAL curse_a_player(PLAYER *adv)
{
	int i,j,which;
	char temp[80];
	char weap[40];
	int something_cursed=FALSE;
	static int poss[]={
						 DAGGER,     AXE,    SHORT_SWORD,
						 LONG_SWORD, RAPIER, CLAYMORE,
						 MACE,       FLAIL,  BOW,
						 CROSSBOW,   HALBERD
					  };


	for (i=0; i<MAX_CARRY; i++)
	{
		for (j=0; j<SIZE(poss); j++)
		{
			if (adv->items_carried[i].item==poss[j] &&
				adv->items_carried[i].type!=CURSED)
			{
				if (memcmp(&adv->items_carried[i],&adv->weapon_used,sizeof(ITEM_POOL)==0))
					adv->weapon_used.type=CURSED;

				adv->items_carried[i].type=CURSED;

				something_cursed=TRUE;
				which=i;

				break;
			}
		}
	}

	if (something_cursed)
	{
		get_full_item_descrip(&adv->items_carried[which],weap);

		sprintf(temp,"%s shivers while clutching %s %s!",
				adv->name,
				adv->his_her,
				weap);
	}
	else
	{
		sprintf(temp,"A shiver runs through %s!",adv->name);
	}

	if (IN_COMBAT)
	{
		cmbt_bad_msg(temp,TRUE);
	}
	else
	{
		SCROLL(1,0,temp);
		bad_sound();
		pause(1);
	}
}
