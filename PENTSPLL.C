#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <ctype.h>
#include <butil.h>

extern SPELL_NAME wiz_spell_names[]={
							   {DRAGONFLAME1		 , "Dragonflame I"	   },
							   {HAMMERHAND           , "Hammerhand"        },
							   {ARC_LIGHTNING1       , "Arc Lightning I"   },
							   {FIND_HIDDEN_DOOR     , "Find Hidden Door"  },
							   {GRAVMUR_RAGE         , "Gravmur's Rage"    },
							   {FROZEN_WIND1		 , "Frozen Wind I"	   },
							   {FIRE_MIST            , "Fire Mist"         },
							   {MIGHTY_APPEARANCE    , "Mighty Appearance" },
							   {DRAGONFLAME2		 , "Dragonflame II"    },
							   {LETHARGY             , "Lethargy"          },
							   {SWIFTNESS            , "Swiftness"         },
							   {ARC_LIGHTNING2       , "Arc Lightning II"  },
							   {DISPEL_TRAP          , "Dispel Trap"       },
							   {SINK                 , "Sink"              },
							   {BLINDING_FLASH       , "Blinding Flash"    },
							   {FROZEN_WIND2		 , "Frozen Wind II"    },
							   {DRAGONFLAME3		 , "Dragonflame III"   },
							   {ARC_LIGHTNING3       , "Arc Lightning III" },
							   {DEATH_CURSE          , "Death Curse"       },
							   {BIND_DEMON           , "Bind Demon"        },
							   {TELEPORT             , "Teleport"          },
							   {FROZEN_WIND3		 , "Frozen Wind III"   },
							   {INVOKE_FAMILIAR      , "Invoke Familiar"   }
							};

extern SPELL_NAME pri_spell_names[]={
							   {TWILIGHT             , "Twilight"             },
							   {NEUTRALISE_POISON    , "Neutralise Poison"    },
							   {PROT_FROM_COLD       , "Protection from Cold" },
							   {PROT_FROM_FIRE       , "Protection from Fire" },
							   {CURE_LIGHT_INJURY    , "Cure Light Injury"    },
							   {CAUSE_LIGHT_INJURY   , "Cause Light Injury"   },
							   {HOLY_SPRAY           , "Holy Spray"           },
							   {DUNGEON_DIVINATION   , "Dungeon Divination"   },
							   {OPEN_CHEST           , "Open Chest"           },
							   {REMOVE_CURSE         , "Remove Curse"         },
							   {CURE_DISEASE         , "Cure Disease"         },
							   {CURE_SEVERE_INJURY   , "Cure Severe Injury"   },
							   {DISRUPTION           , "Disruption"           },
							   {CAUSE_SEVERE_INJURY  , "Cause Severe Injury"  },
							   {BLADES               , "Blades"               },
							   {PROT_FROM_TRAPS      , "Protection from Traps"},
							   {RESURRECT            , "Resurrect"            },
							   {CURE_CRITICAL_INJURY , "Cure Critical Injury" },
							   {CAUSE_CRITICAL_INJURY, "Cause Critical Injury"},
							   {SPELL_OF_PASSAGE	 , "Spell of Passage"	  },
							   {MISSILE_CLOAK		 , "Missile Cloak"		  }
							};

extern SPELL_NAME ill_spell_names[]={
							   {HORRIFY              , "Horrify"              },
							   {SLY_EARS             , "Sly Ears"             },
							   {CATS_EYES            , "Cat's Eyes"           },
							   {PHANTASM1            , "Phantasm I"           },
							   {STAR_FLARE           , "Star Flare"           },
							   {AXELS_BLUR           , "Axel's Blur"          },
							   {ALLYS_DANCING_DAGGER , "Ally's Dancing Dagger"},
							   {JONAS_SPOOK          , "Jonas' Spook"         },
							   {KORINAS_LEAP         , "Korina's Leap"        },
							   {MOON_FLARE           , "Moon Flare"           },
							   {CREATE_ARTIFACTS     , "Create Artifacts"     },
							   {PHANTASM2            , "Phantasm II"          },
							   {AXELS_SHIMMER        , "Axel's Shimmer"       },
							   {ALLYS_DANCING_MACE   , "Ally's Dancing Mace"  },
							   {AXELS_SHADOW         , "Axel's Shadow"        },
							   {MIRAGE               , "Mirage"               },
							   {SUN_FLARE            , "Sun Flare"            },
							   {SUSPEND_TIME         , "Suspend Time"         },
							   {PHANTASM3            , "Phantasm III"         },
							   {ALLYS_DANCING_SABRE  , "Ally's Dancing Sabre" }
							};

extern SPELL_NAME dru_spell_names[]={
							   {TRUEFLIGHT			 , "Trueflight" 		  },
							   {WALK_ON_WATER        , "Walk on Water"        },
							   {FLAME_SHEET          , "Flame Sheet"          },
							   {RAZOR_LEAVES1        , "Razor Leaves I",      },
							   {POISON_IMMUNITY      , "Poison Immunity"      },
							   {PLANT_FEAST          , "Plant Feast"          },
							   {AURA_OF_PROTECTION   , "Aura of Protection"   },
							   {RAZOR_LEAVES2        , "Razor Leaves II"      },
							   {TANGLE_THORNS		 , "Tangle Thorns"		  },
							   {MINDS_EYE            , "Minds Eye"            },
							   {ICE_HAMMER			 , "Ice Hammer" 		  },
							   {DR_INVOKE_FAMILIAR   , "InvokeÿFamiliar"      },
							   {ASCERTAIN_POWER 	 , "Ascertain Power"	  },
							   {BANISH_ELEMENTAL     , "Banish Elemental"     },
							   {RAZOR_LEAVES3        , "Razor Leaves III"     },
							   {CALL_HAILSTORM       , "Call Hailstorm"       },
							   {MAELSTROM			 , "Maelstrom"			  },
							   {EARTHQUAKE			 , "Earthquake" 		  }
							};

int _PASCAL actually_cast_a_spell(PLAYER *adv)
{
	int LONGEST=22;
	int DOWN=10;
	int i;
	GWINDOW win;
	int num_spells;
	int page;
	int num_pages;
	int fin=FALSE;
	int select;
	int ok=FALSE;
	char *title="Pick thy Spell";
	int spell_selected;
	int update_page;
	int cl=adv->nclass;
	static int boundary[]={16, 32, 212,38,
						   16, 40, 212,46,
						   16, 48, 212,54,
						   16, 56, 212,62,
						   16, 64, 212,70,
						   16, 72, 212,78,
						   16, 80, 212,86,
						   16, 88, 212,94,
						   16, 96, 212,102,
						   16, 104,212,110,
						   72, 120,82, 129,
						   84, 120,94, 129,
						   112,119,147,131,
							-1,-1,-1,-1};
	char temp[80];
	int res;

	win.x1=2;
	win.y1=3;
	win.x2=LONGEST+win.x1+4;
	win.y2=DOWN+win.y1+5;
	win.back=0;
	win.border=3;

	num_spells=show_determine_spells(adv);

	num_pages=((num_spells-1)/DOWN)+1;

	page=1;

	if (!num_spells)
	{
		sprintf(temp,"%s hath no spells!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	if ((cl==WIZARD      ||
		 cl==ILLUSIONIST ||
		 cl==MONK        ||
		 cl==RANGER)     && adv->current_sorcery_points==0)
	{
		sprintf(temp,"%s hath no sorcery points left!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	if ((cl==PRIEST      ||
		 cl==DRUID       ||
		 cl==HUNTER      ||
		 cl==CRUSADER)   && adv->current_divine_points==0)
	{
		sprintf(temp,"%s hath no divine points left!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	if ((pent_data.current_feature==SEA    ||
		 pent_data.current_feature==WATER) &&
		 check_party_globals_in_effect(IN_EFFECT_WALK_ON_WATER)==ERR)
	{
		sprintf(temp,"%s cannot swim & cast spells simultaneously!",adv->name);
		GX(temp,BAD);

		return(FALSE);
	}

	make_gwindow(&win);

	_settextcolor(14);
	_settextposition(win.y1+1,win.x1+3);
	_outtext(title);

	print_up_down(72,120);
	click_box(112,119,B_QUIT);

	_settextcolor(13);

	for (i=0; i<DOWN; i++)
	{
		sprintf(temp,"%cù",i+'A');
		_settextposition(win.y1+2+i,win.x1+1);
		_outtext(temp);
	}

	update_page=TRUE;

	while (!fin)
	{
		if (update_page)
		{
			sprintf(temp,"%d/%d",page,num_pages);

			_settextcolor(12);
			_settextposition(win.y1+1,win.x2-strlen(temp)-1);
			_outtext(temp);

			actually_cast_spell_draw(page,&win,DOWN);
		}

		ok=FALSE;

		while (!ok)
		{
			update_page=TRUE;

			select=mouse_in_range(boundary,
								  "ABCDEFGHIJ++Q",
								  "ªªªªªªªªªª\xD0\xC8Q");

			if (select<10 && (select+((page-1)*DOWN))>num_spells)
				continue;

			if (select>=10)
				ok=TRUE;

			switch(select)
			{
				case 10 :   if (++page>num_pages)
							{
								update_page=FALSE;
								page=num_pages;
							}

							spell_selected=ERR;

							break;

				case 11 :   if (--page<1)
							{
								update_page=FALSE;
								page=1;
							}

							spell_selected=ERR;

							break;

				case 12 :	spell_selected=ERR;
							ok=TRUE;
							fin=TRUE;
							kill_gwindow(&win);

							break;

				default :	spell_selected=select+((page-1)*DOWN);
							ok=TRUE;
							kill_gwindow(&win);

							break;
			}
		}

		if (spell_selected!=ERR)
		{
			res=spell_dispatch(adv,&adv_spells[spell_selected]);

			fin=TRUE;
		}
		else
			res=FALSE;
	}

	return(res);
}

void _PASCAL actually_cast_spell_draw(int page,GWINDOW *win,int DOWN)
{
	int i,j;
	int start=(page-1)*DOWN;

	actually_cast_spell_draw_cls();

	_settextcolor(5);

	for (i=0; i<DOWN; i++)
	{
		j=i+start;

		if (strlen(adv_spells[j].descrip)<4 || !isalpha(adv_spells[j].descrip[0]))
			break;

		_settextposition(win->y1+2+i,win->x1+3);
		_outtext(adv_spells[j].descrip);
	}
}

void _PASCAL actually_cast_spell_draw_cls()
{
	_setcolor(0);
	_rectangle(_GFILLINTERIOR,32,32,212,114);
}

int _PASCAL _NEAR spell_dispatch(PLAYER *adv,SPELL_NAME *spell_name)
{
	int i;
	int type=ERR;
	int res=FALSE;
	char temp[60];

	if (type==ERR)
		for (i=0; i<SIZE(wiz_spell_names); i++)
			if (strcmp(spell_name->descrip,wiz_spell_names[i].descrip)==0)
				type=WIZARD;

	if (type==ERR)
		for (i=0; i<SIZE(pri_spell_names); i++)
			if (strcmp(spell_name->descrip,pri_spell_names[i].descrip)==0)
				type=PRIEST;

	if (type==ERR)
		for (i=0; i<SIZE(ill_spell_names); i++)
			if (strcmp(spell_name->descrip,ill_spell_names[i].descrip)==0)
				type=ILLUSIONIST;

	if (type==ERR)
		for (i=0; i<SIZE(dru_spell_names); i++)
			if (strcmp(spell_name->descrip,dru_spell_names[i].descrip)==0)
				type=DRUID;

	if (type!=ERR)
	{
		if (IN_COMBAT)
			cmbt_print_spell_name(spell_name);

		switch(type)
		{
			case WIZARD:
						switch(spell_name->name)
						{
							case DRAGONFLAME1			:	res=cast_DRAGONFLAME1(adv,spell_name);		   break;
							case HAMMERHAND 			:	res=cast_HAMMERHAND(adv,spell_name);		   break;
							case ARC_LIGHTNING1 		:	res=cast_ARC_LIGHTNING1(adv,spell_name);	   break;
							case FIND_HIDDEN_DOOR		:	res=cast_FIND_HIDDEN_DOOR(adv,spell_name);	   break;
							case GRAVMUR_RAGE			:	res=cast_GRAVMUR_RAGE(adv,spell_name);		   break;
							case FROZEN_WIND1			:	res=cast_FROZEN_WIND1(adv,spell_name);		   break;
							case FIRE_MIST				:	res=cast_FIRE_MIST(adv,spell_name); 		   break;
							case MIGHTY_APPEARANCE		:	res=cast_MIGHTY_APPEARANCE(adv,spell_name);    break;
							case DRAGONFLAME2			:	res=cast_DRAGONFLAME2(adv,spell_name);		   break;
							case LETHARGY				:	res=cast_LETHARGY(adv,spell_name);			   break;
							case SWIFTNESS				:	res=cast_SWIFTNESS(adv,spell_name); 		   break;
							case ARC_LIGHTNING2 		:	res=cast_ARC_LIGHTNING2(adv,spell_name);	   break;
							case DISPEL_TRAP			:	res=cast_DISPEL_TRAP(adv,spell_name);		   break;
							case SINK					:	res=cast_SINK(adv,spell_name);				   break;
							case BLINDING_FLASH 		:	res=cast_BLINDING_FLASH(adv,spell_name);	   break;
							case FROZEN_WIND2			:	res=cast_FROZEN_WIND2(adv,spell_name);		   break;
							case DRAGONFLAME3			:	res=cast_DRAGONFLAME3(adv,spell_name);		   break;
							case ARC_LIGHTNING3 		:	res=cast_ARC_LIGHTNING3(adv,spell_name);	   break;
							case DEATH_CURSE			:	res=cast_DEATH_CURSE(adv,spell_name);		   break;
							case BIND_DEMON 			:	res=cast_BIND_DEMON(adv,spell_name);		   break;
							case TELEPORT				:	res=cast_TELEPORT(adv,spell_name);			   break;
							case FROZEN_WIND3			:	res=cast_FROZEN_WIND3(adv,spell_name);		   break;
							case INVOKE_FAMILIAR		:	res=cast_INVOKE_FAMILIAR(adv,spell_name);	   break;
						}

						break;

			case PRIEST:
						switch(spell_name->name)
						{
							case TWILIGHT               :   res=cast_TWILIGHT(adv,spell_name);             break;
							case NEUTRALISE_POISON		:	res=cast_NEUTRALISE_POISON(adv,spell_name);    break;
							case PROT_FROM_COLD 		:	res=cast_PROT_FROM_COLD(adv,spell_name);	   break;
							case PROT_FROM_FIRE 		:	res=cast_PROT_FROM_FIRE(adv,spell_name);	   break;
							case CURE_LIGHT_INJURY		:	res=cast_CURE_LIGHT_INJURY(adv,spell_name);    break;
							case CAUSE_LIGHT_INJURY 	:	res=cast_CAUSE_LIGHT_INJURY(adv,spell_name);   break;
							case HOLY_SPRAY 			:	res=cast_HOLY_SPRAY(adv,spell_name);		   break;
							case DUNGEON_DIVINATION 	:	res=cast_DUNGEON_DIVINATION(adv,spell_name);   break;
							case OPEN_CHEST 			:	res=cast_OPEN_CHEST(adv,spell_name);		   break;
							case REMOVE_CURSE			:	res=cast_REMOVE_CURSE(adv,spell_name);		   break;
							case CURE_DISEASE			:	res=cast_CURE_DISEASE(adv,spell_name);		   break;
							case CURE_SEVERE_INJURY 	:	res=cast_CURE_SEVERE_INJURY(adv,spell_name);   break;
							case DISRUPTION 			:	res=cast_DISRUPTION(adv,spell_name);		   break;
							case CAUSE_SEVERE_INJURY	:	res=cast_CAUSE_SEVERE_INJURY(adv,spell_name);  break;
							case BLADES 				:	res=cast_BLADES(adv,spell_name);			   break;
							case PROT_FROM_TRAPS		:	res=cast_PROTECTION_FROM_TRAPS(adv,spell_name);break;
							case RESURRECT				:	res=cast_RESURRECT(adv,spell_name); 		   break;
							case CURE_CRITICAL_INJURY	:	res=cast_CURE_CRITICAL_INJURY(adv,spell_name); break;
							case CAUSE_CRITICAL_INJURY	:	res=cast_CAUSE_CRITICAL_INJURY(adv,spell_name);break;
							case SPELL_OF_PASSAGE		:	res=cast_SPELL_OF_PASSAGE(adv,spell_name);	   break;
							case MISSILE_CLOAK			:	res=cast_MISSILE_CLOAK(adv,spell_name); 	   break;
						}

						break;

			case ILLUSIONIST:
						switch(spell_name->name)
						{
							case HORRIFY				:	res=cast_HORRIFY(adv,spell_name);			   break;
							case SLY_EARS				:	res=cast_SLY_EARS(adv,spell_name);			   break;
							case CATS_EYES				:	res=cast_CATS_EYES(adv,spell_name); 		   break;
							case PHANTASM1              :   res=cast_PHANTASM1(adv,spell_name);            break;
							case STAR_FLARE 			:	res=cast_STAR_FLARE(adv,spell_name);		   break;
							case AXELS_BLUR 			:	res=cast_AXELS_BLUR(adv,spell_name);		   break;
							case KORINAS_LEAP			:	res=cast_KORINAS_LEAP(adv,spell_name);		   break;
							case ALLYS_DANCING_DAGGER	:	res=cast_ALLYS_DANCING_DAGGER(adv,spell_name); break;
							case JONAS_SPOOK			:	res=cast_JONAS_SPOOK(adv,spell_name);		   break;
							case PHANTASM2              :   res=cast_PHANTASM2(adv,spell_name);            break;
							case MOON_FLARE             :   res=cast_MOON_FLARE(adv,spell_name);           break;
							case CREATE_ARTIFACTS       :   res=cast_CREATE_ARTIFACTS(adv,spell_name);     break;
							case AXELS_SHIMMER			:	res=cast_AXELS_SHIMMER(adv,spell_name); 	   break;
							case ALLYS_DANCING_MACE 	:	res=cast_ALLYS_DANCING_MACE(adv,spell_name);   break;
							case AXELS_SHADOW			:	res=cast_AXELS_SHADOW(adv,spell_name);		   break;
							case MIRAGE                 :   res=cast_MIRAGE(adv,spell_name);               break;
							case PHANTASM3              :   res=cast_PHANTASM3(adv,spell_name);            break;
							case SUN_FLARE				:	res=cast_SUN_FLARE(adv,spell_name); 		   break;
							case SUSPEND_TIME           :   res=cast_SUSPEND_TIME(adv,spell_name);         break;
							case ALLYS_DANCING_SABRE    :   res=cast_ALLYS_DANCING_SABRE(adv,spell_name);  break;
						}

						break;

			case DRUID:
						switch(spell_name->name)
						{
							case TRUEFLIGHT 			:	res=cast_TRUEFLIGHT(adv,spell_name);		   break;
							case WALK_ON_WATER			:	res=cast_WALK_ON_WATER(adv,spell_name); 	   break;
							case FLAME_SHEET			:	res=cast_FLAME_SHEET(adv,spell_name);		   break;
							case RAZOR_LEAVES1			:	res=cast_RAZOR_LEAVES1(adv,spell_name); 	   break;
							case POISON_IMMUNITY		:	res=cast_POISON_IMMUNITY(adv,spell_name);	   break;
							case PLANT_FEAST			:	res=cast_PLANT_FEAST(adv,spell_name);		   break;
							case AURA_OF_PROTECTION 	:	res=cast_AURA_OF_PROTECTION(adv,spell_name);   break;
							case RAZOR_LEAVES2			:	res=cast_RAZOR_LEAVES2(adv,spell_name); 	   break;
							case DR_INVOKE_FAMILIAR 	:	res=cast_INVOKE_FAMILIAR(adv,spell_name);	   break;
							case TANGLE_THORNS			:	res=cast_TANGLE_THORNS(adv,spell_name); 	   break;
							case MINDS_EYE				:	res=cast_MINDS_EYE(adv,spell_name); 		   break;
							case ICE_HAMMER 			:	res=cast_ICE_HAMMER(adv,spell_name);		   break;
							case ASCERTAIN_POWER		:	res=cast_ASCERTAIN_POWER(adv,spell_name);	   break;
							case BANISH_ELEMENTAL		:	res=cast_BANISH_ELEMENTAL(adv,spell_name);	   break;
							case RAZOR_LEAVES3			:	res=cast_RAZOR_LEAVES3(adv,spell_name); 	   break;
							case CALL_HAILSTORM 		:	res=cast_CALL_HAILSTORM(adv,spell_name);	   break;
							case MAELSTROM				:	res=cast_MAELSTROM(adv,spell_name); 		   break;
							case EARTHQUAKE 			:	res=cast_EARTHQUAKE(adv,spell_name);		   break;
						}

						break;
		}
	}

	if (res!=FALSE)
	{
		if (check_player_is_spell_drained(adv))
		{
			sprintf(temp,"%s art Spell Drained!",adv->name);

			if (IN_COMBAT)
			{
				cmbt_bad_msg(temp,TRUE);
			}
			else
			{
				SCROLL(1,0,temp);
				bad_sound();
			}
		}
	}

	return(res);
}

void _PASCAL add_lost_spell_pts(PLAYER *adv,int pts)
{
	switch(adv->nclass)
	{
		case WIZARD 	:
		case ILLUSIONIST:
		case RANGER 	: adv->current_sorcery_points+=pts; break;

		case DRUID		:
		case PRIEST 	:
		case CRUSADER	: adv->current_divine_points+=pts;	break;
	}

	adv->points_cast-=pts;
}

int _PASCAL enough_spell_points_to_cast(PLAYER *adv,int needed)
{
	int enough=TRUE;
	char temp[80];

	if (check_player_is_spell_drained(adv))
	{
		player_is_spell_drained(adv);
		return(FALSE);
	}

	switch(adv->nclass)
	{
		case WIZARD     :
		case ILLUSIONIST:
		case RANGER     :
		case MONK       :   if (adv->current_sorcery_points<needed)
							{
								if (adv->current_sorcery_points)
								{
									sprintf(temp,"%s hath but %d sorcery point%s",
											adv->name,
											adv->current_sorcery_points,
											adv->current_sorcery_points==1?"!":"s!");
								}
								else
								{
									sprintf(temp,"%s hath no sorcery points left!",
											adv->name);

								}

								enough=FALSE;
							}
							else
								adv->current_sorcery_points-=needed;

							break;

		case PRIEST     :
		case DRUID      :
		case CRUSADER   :
		case HUNTER     :   if (adv->current_divine_points<needed)
							{
								if (adv->current_divine_points)
								{
									sprintf(temp,"%s hath but %d divine point%s",
											adv->name,
											adv->current_divine_points,
											adv->current_divine_points==1?"!":"s!");
								}
								else
								{
									sprintf(temp,"%s hath no divine points left!",
											adv->name);
								}

								enough=FALSE;
							}
							else
								adv->current_divine_points-=needed;

							break;

	}

	if (!enough)
		GX(temp,BAD);

	if (cannot_cast_spell(adv))
		enough=FALSE;

	if (enough)
		adv->points_cast+=needed;

	return(enough);
}

int _PASCAL cast_spell_correct_situation(PLAYER *adv,SPELL_NAME *spell_name,int sit_required)
{
	char temp[120];
	int result;

	if ((IN_COMBAT	&& sit_required==COMBAT_SPELL) ||
		(!IN_COMBAT && sit_required==NON_COMBAT_SPELL))
	{
		result=TRUE;
	}
	else
	{
		if (IN_COMBAT)
		{
			sprintf(temp,"%s works not in combat!",spell_name->descrip);
			combat_write(4,temp,TRUE);
		}
		else
		{
			sprintf(temp,"%s cannot cast %s, as it is%sa combat spell!",
					adv->name,
					spell_name->descrip,
					sit_required==NON_COMBAT_SPELL?" not ":" ");

			SCROLL(1,0,temp);
		}

		solemn_sound();
		delay(400);

		result=FALSE;
	}

	return(result);
}

void _PASCAL cast_in_dungeon_only(char *spell)
{
	char temp[80];

	sprintf(temp,"%s works only in dungeons!",spell);

	GX(temp,BAD);
}

void _PASCAL print_spell_description(char *mess)
{
	if (IN_COMBAT)
		combat_write(14,mess,TRUE);
	else
		SCROLL(1,14,mess);

	spell_sound();
}

int _PASCAL cannot_cast_spell(PLAYER *adv)
{
	char temp[100];

	if (!IN_DUNGEON)
		return(FALSE);

	if (dungeon.spells_work==TRUE)
		return(FALSE);

	if (IN_COMBAT)
	{
		sprintf(temp,"Something prevents %s from casting %s spell!",
						adv->name,
						adv->his_her);

		cmbt_bad_msg(temp,TRUE);
	}
	else
	{
		sprintf(temp,"%s attempts to casting ye spell, but something prevents %s!",
					adv->name,
					adv->him_her);

		SCROLL(1,0,temp);
		pause(1);
	}

	solemn_sound();

	return(TRUE);
}

void _FAR *get_spell_colour_and_dice(int att_type,
									 int *dice_base,
									 MONSTER *mnst,
									 int *poss_save)
{
	void (_FAR *draw)(int xp,int yp);
	int base=*dice_base;
	int save=TRUE;

	switch(att_type)
	{
		case TY_FIRE   :        draw=cmbt_missile_draw_red;

								if (monster_imm_to_fire(mnst))
								   base=0;

								if (mnst->weakness==WK_FIRE)
								{
									save=FALSE;
									base=(base*3)/2;
								}

								break;

		case TY_ANTI_UNDEAD:	draw=cmbt_missile_draw_white;

								if (!is_undead_or_demon(mnst))
									base=0;

								break;

		case TY_ICE    :		draw=cmbt_missile_draw_white;

								if (monster_imm_to_ice(mnst))
								   base=0;

								if (mnst->weakness==WK_ICE)
								{
									save=FALSE;
									base=(base*3)/2;
								}

								break;

		case TY_ELECTRICITY:	draw=cmbt_missile_draw_blue;

								if (monster_imm_to_electricity(mnst))
								   base=0;

								if (mnst->weakness==WK_ELECTRICITY)
								{
									save=FALSE;
									base=(base*3)/2;
								}

								break;

		case TY_MIND	:		draw=cmbt_missile_draw_white;

								if (monster_imm_to_mind_spells(mnst))
								   base=0;

								break;

		case TY_QUAKE   :       draw=NULL;

								if (mnst->weakness==WK_QUAKE)
								{
									save=FALSE;
									base=(base*3)/2;
								}

								if (mnst->quake_immunity)
									base=0;

								break;
		case TY_ENERGY	:
		default 		:		draw=cmbt_missile_draw_magenta;
								break;
	}

	*dice_base=base;
	*poss_save=save;

	return((void _FAR *)draw);
}

void _PASCAL inflict_spell_damage(PLAYER *adv,
								  MONSTER *mnst,
								  int weak_type,
								  int poss_save,
								  int dice_base,
								  int num_rolls,
								  int add,
								  void (_FAR *draw)(int xp,int yp),
								  int x,int y)
{
	int damage;
	char temp[40];
	int endx=x,endy=y;

	if (poss_save)
		if (percent()<effective_monster_saving_throw(mnst,adv,NORMAL_SPELL_SAVE))
			dice_base=0;

	if (draw!=NULL)
	{
		if ((unsigned)x!=adv->x || (unsigned)y!=adv->y)
		{
			cmbt_between_points(adv->x,adv->y,x,y,&endx,&endy,draw);

			if (cmbt_area_contents(endx,endy)==IS_WALL)
			{
				cmbt_spell_missed(endx,endy);

				return;
			}
		}
	}

	if (dice_base)
	{
		cmbt_hit_a_square(endx,endy);

		damage=get_dice_roll(dice_base,num_rolls,add);
		damage=modify_player_spell_damage(mnst,weak_type,damage);
		damage+=adjust_damage_for_spell_luck(adv);

		sprintf(temp,"%s inflicts %d damage.",adv->name,damage);

		combat_write(14,temp,TRUE);

		monster_reduce_hp(mnst,damage);

		if (monster_is_dead(mnst))
			cmbt_monster_is_slain(adv,mnst);
		else
			half_pause();
	}
	else
	{
		cmbt_bad_msg("Thy foe appears unaffected!",TRUE);
	}
}

int _PASCAL _NEAR modify_player_spell_damage(MONSTER *mnst,int weak_type,int damage)
{
	int add_dam=damage/3;

	if (mnst->weakness!=WK_NONE)
		if (mnst->weakness==(unsigned)weak_type)
			damage+=add_dam;

	return(damage);
}

int _PASCAL _NEAR adjust_damage_for_spell_luck(PLAYER *adv)
{
	return(percent()<=effective_spell_luck(adv)?(rand()%2+1):0);
}

int _PASCAL _NEAR spell_use_channeling(PLAYER *adv,SPELL_NAME *spell_name)
{
	int max_channel=min(adv->current_hp-1,MAX_CHANNEL/CHANNEL_MULTIPLIER);

	if (player_is_weak(adv) ||
		max_channel==0      ||
		adv->current_sorcery_points==0)
	{
		combat_write(4,"Thou art too weak to Channel!",TRUE);
		return(0);
	}

	if (!NO_SOUND)
	{
		utspkr(1000);
		delay(50);
		utspkr(800);
		delay(50);
		utspkr(1000);
		delay(50);
		utspkr(0);
	}

	return(!gget_yn("Dost thou Channel thy spell?")
		   ?0:get_channeling_damage(adv,spell_name,max_channel));
}

int _PASCAL _NEAR get_channeling_damage(PLAYER *adv,
										SPELL_NAME *spell_name,
										int max_channel)
{
	GWINDOW win;
	char *letters="\xC8\xD0"" ";
	char temp[80];
	int channel=0;
	int fin=FALSE;
	int i;
	static char *t[]={"Spell   : ",
					  "Channel : ",
					  "Damage  : ",
					  "Leaving : "};

	static int boundary[]={127,112,138,122,
						   115,112,126,122,
						   165,110,200,122,
							-1,-1,-1,-1};

	win.x1=6;
	win.y1=3;
	win.x2=35;
	win.y2=17;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	generic_pic_draw(78,win.y1*8+2,"CHANNEL");

	print_up_down(115,112);

	click_box(165,110,B_FINISH);

	_settextcolor(9);

	for (i=0; i<SIZE(t); i++)
	{
		_settextposition(win.y1+6+i,win.x1+1);
		_outtext(t[i]);
	}

	_settextcolor(11);

	_settextposition(win.y1+6,win.x1+11);
	_outtext(spell_name->descrip);

	fast_mouse=ON;

	while (!fin)
	{
		sprintf(temp,"%d point%s",channel,channel==1?" ":"s ");
		_settextposition(win.y1+7,win.x1+11);
		_outtext(temp);

		sprintf(temp,"%d extra ",channel*CHANNEL_MULTIPLIER);
		_settextposition(win.y1+8,win.x1+11);
		_outtext(temp);

		sprintf(temp,"%d HP ",adv->current_hp-channel);
		_settextposition(win.y1+9,win.x1+11);
		_outtext(temp);

		switch(mouse_in_range(boundary,letters,"ªªF"))
		{
			case 0 : channel++; break;
			case 1 : channel--; break;
			default: fin=TRUE;  break;
		}

		if (channel<0)
			channel=max_channel;

		if (channel>max_channel)
			channel=0;

		delay(20);
	}

	fast_mouse=OFF;

	kill_gwindow(&win);

	if (channel)
	{
		adv->current_sorcery_points--;
		adv->current_hp-=channel;
	}

	return(channel*CHANNEL_MULTIPLIER);
}

int _PASCAL generic_solitary_battle_magic(PLAYER *adv,
										  SPELL_NAME *spell_name,
										  int sp_pts,
										  int att_type,
										  int weak_type,
										  int dice_base,
										  int num_rolls,
										  int dam_add,
										  int channel)
{
	MONSTER *mnst;
	int x,y;
	int poss_save;
	void (_FAR *draw)(int xp,int yp);
	int ch_damage=0;

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,sp_pts))
		return(FALSE);

	if (channel)
		ch_damage=spell_use_channeling(adv,spell_name);

	x=adv->x;
	y=adv->y;

	select_a_foe_msg();

	cmbt_select_sq_around_player(9,&x,&y,TRUE,FALSE,FALSE);

	if ((unsigned)x==adv->x && (unsigned)y==adv->y)
	{
		add_lost_spell_pts(adv,sp_pts);

		if (channel)
		{
			add_lost_spell_pts(adv,1);
			adv->current_hp+=(ch_damage/CHANNEL_MULTIPLIER);
		}

		return(FALSE);
	}

	mnst=cmbt_area[x][y].occ.monster;

	draw=(void (_FAR *)())get_spell_colour_and_dice(att_type,&dice_base,mnst,&poss_save);

	spell_sound();

	inflict_spell_damage(adv,mnst,weak_type,poss_save,
						 dice_base,num_rolls,dam_add+ch_damage,draw,x,y);

	return(TRUE);
}

int _PASCAL generic_scatter_battle_magic(PLAYER *adv,
										 SPELL_NAME *spell_name,
										 int sp_pts,
										 int att_type,
										 int weak_type,
										 int dice_base,
										 int num_rolls,
										 int dam_add)
{
	MONSTER *mnst;
	int i;
	int poss_save;
	void (_FAR *draw)(int xp,int yp);

	if (!cast_spell_correct_situation(adv,spell_name,COMBAT_SPELL))
		return(FALSE);

	if (!enough_spell_points_to_cast(adv,sp_pts))
		return(FALSE);

	spell_sound();

	draw=(void (_FAR *)())get_spell_colour_and_dice(att_type,&dice_base,&the_monsters[0],&poss_save);

	for (i=0; i<MAX_MONSTERS; i++)
	{
		mnst=&the_monsters[i];

		if (mnst->current_hp>0 && !mnst->flown)
		{
			inflict_spell_damage(adv,mnst,
								 weak_type,
								 poss_save,
								 dice_base,num_rolls,dam_add,
								 draw,
								 mnst->x,mnst->y);
		}
	}

	return(TRUE);
}

void _PASCAL spell_does_naught()
{
	cmbt_bad_msg("Naught appears to happen!",TRUE);
}

void _PASCAL cmbt_spell_missed(int x,int y)
{
	cmbt_hit_a_square(x,y);
	cmbt_bad_msg("Missed!",TRUE);
}
