#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

/* Priest Spells non-battle magic*/

int _PASCAL cast_TWILIGHT(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[120];

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			res=TRUE;

			sprintf(temp,"Streams of red, yellow and white flames emerge from %s%s "
						 "hands, illuminating ye %s.",
						 adv->name,
						 end_s(adv->name),
						 IN_DUNGEON?"dark dungeon":"area about thy party");

			print_spell_description(temp);

			adv->in_effect.twilight+=8+effective_spell_luck(adv)+adv->level;
		}
	}

	return(res);
}

int _PASCAL cast_NEUTRALISE_POISON(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	PLAYER *on;
	char temp[120];
	int whom;

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			whom=adv_select_adventurer("Cast Neutral.","Poison on?",TRUE);

			if (whom!=ERR)
			{
				res=TRUE;

				on=&TPP[whom];

				if (on->is_poisoned)
				{
					on->is_poisoned=FALSE;

					sprintf(temp,"A yellow iridescent spray washes over %s, "
								 "improving %s health.",
								  on->name,
								  on->his_her);

					print_spell_description(temp);
				}
				else
				{
					sprintf(temp,"%s is not poisoned! Thy spell art wasted.",on->name);

					SCROLL(1,0,temp);
					bad_sound();
				}
			}
			else
				add_lost_spell_pts(adv,1);
		}
	}

	return(res);
}

int _PASCAL cast_PROT_FROM_COLD(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	PLAYER *on;
	char temp[120];
	int whom;

	if (enough_spell_points_to_cast(adv,1))
	{
		whom=adv_select_adventurer("Cast Prot.","from Cold on?",TRUE);

		if (whom!=ERR)
		{
			res=TRUE;

			on=&TPP[whom];

			on->in_effect.prot_cold+=adv->level*2;

			sprintf(temp,"An aquamarine light engulfs %s.",on->name);

			print_spell_description(temp);
		}
		else
			add_lost_spell_pts(adv,1);
	}

	return(res);
}

int _PASCAL cast_PROT_FROM_FIRE(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	PLAYER *on;
	char temp[120];
	int whom;

	if (enough_spell_points_to_cast(adv,1))
	{
		whom=adv_select_adventurer("Cast Prot.","from Fire on?",TRUE);

		if (whom!=ERR)
		{
			res=TRUE;

			on=&TPP[whom];

			on->in_effect.prot_fire+=adv->level*2;

			sprintf(temp,"An orange-red light engulfs %s.",on->name);

			print_spell_description(temp);
		}
		else
			add_lost_spell_pts(adv,1);
	}

	return(res);
}

int _PASCAL cast_CURE_LIGHT_INJURY(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_priest_cure_spells(adv,CURE_LIGHT_INJURY));
}

int _PASCAL cast_DUNGEON_DIVINATION(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[120];
	char desc[120];
	int dungeon_number;
	char *diff;
	int i;

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			if (!IN_DUNGEON && pent_data.current_feature!=DUNGEON)
			{
				SCROLL(1,0,"Ye must be in or near a dungeon to cast Dungeon Divination!");

				bad_sound();
			}
			else
			{
				res=TRUE;

				dungeon_number=get_dungeon_number(pent_data.x, pent_data.y);

				for (i=0; i<MAX_DUNGEONS; i++)
				{
					if (dungeon_number==look_dungeons[i].nname)
					{
						switch(look_dungeons[i].difficulty)
						{
						   case DD_TOUGH         : diff="tough";          break;
						   case DD_DIFFICULT     : diff="difficult";      break;
						   case DD_DANGEROUS     : diff="dangerous";      break;
						   case DD_VERY_DANGEROUS: diff="very dangerous"; break;
						   case DD_SUICIDAL      : diff="suicidal";       break;
						}

						break;
					}
				}

				sprintf(desc,"\"%s hath %d %s level%sto explore!\"",
							look_dungeons[i].name,
							look_dungeons[i].number_of_levels,
							diff,
							look_dungeons[i].number_of_levels!=1?"s ":" ");

				sprintf(temp,"%s prays to %s deity, %s...",
						adv->name,
						adv->his_her,
						adv->deity_name);

				print_spell_description(temp);

				pause(2);

				sprintf(temp,"An authorative voice in %s%s mind whispers..",
						adv->name,
						end_s(adv->name));

				SCROLL(1,14,temp);
				pause(2);

				SCROLL(1,14,desc);
			}
		}
	}

	return(res);
}

int _PASCAL cast_OPEN_CHEST(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	int x,y,l;
	int feature;
	char temp[120];

	x=the_party.dungeon_x;
	y=the_party.dungeon_y;
	l=the_party.dungeon_level;

	feature=dungeon.map[l][x][y].feature;

	if (!IN_DUNGEON)
	{
		cast_in_dungeon_only(spell_name->descrip);
		return(FALSE);
	}

	if (feature!=DNG_CHEST          &&
		feature!=DNG_TRAPPED_CHEST  &&
		feature!=DNG_TR_LOCK_CHEST  &&
		feature!=DNG_LOCKED_CHEST   &&
		feature!=DNG_EMPTY_CHEST)
	{
		GX("Thou art not by a chest!",BAD);
		return(FALSE);
	}

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,2))
		{
			sprintf(temp,"A ball of soft white light forms at the end of %s%s fingers...",
						adv->name,
						end_s(adv->name));

			print_spell_description(temp);

			pause(2);

			SCROLL(1,14,"Instantly ye chest lid bursts open!");

			if (feature==DNG_TRAPPED_CHEST || feature==DNG_TR_LOCK_CHEST)
				dng_trigger_chest_trap(adv,l,x,y);

			if (feature==DNG_EMPTY_CHEST)
			{
				SCROLL(1,0,"Ye chest is empty!");

				bad_sound();
			}
			else
			{
				res=TRUE;

				look_inside_chest();
				dungeon.map[l][x][y].feature=DNG_EMPTY_CHEST;
			}
		}
	}

	return(res);
}

int _PASCAL cast_REMOVE_CURSE(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	PLAYER *on;
	char temp[120];
	int whom;
	int i;
	int curse_found=FALSE;

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,2))
		{
			whom=adv_select_adventurer("Remove Curse","from whom?",TRUE);

			if (whom!=ERR)
			{
				on=&TPP[whom];

				sprintf(temp,"%s lays %s hands, tinged with an ice blue haze, on %s.",
							  adv->name,
							  adv->his_her,
							  on->name);

				for (i=0; i<MAX_CARRY; i++)
				{
					if (on->items_carried[i].type==CURSED)
					{
						on->items_carried[i].type=NO_PLUS;
						curse_found++;
					}
				}

				print_spell_description(temp);

				if (curse_found)
				{
					res=TRUE;

					sprintf(temp,"a black shadow issues forth from %s%s body!",
								 on->name,
								 end_s(on->name));

					SCROLL(2,0,temp);
					solemn_sound();
				}
				else
				{
					SCROLL(1,0,"But naught seems to happen!");
					bad_sound();
				}
			}
			else
				add_lost_spell_pts(adv,2);
		}
	}

	return(res);
}

int _PASCAL cast_CURE_DISEASE(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	PLAYER *on;
	char temp[120];
	int whom;

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,2))
		{
			whom=adv_select_adventurer("Cast Cure","Disease on?",TRUE);

			if (whom!=ERR)
			{
				on=&TPP[whom];

				if (on->disease!=NO_DISEASE)
				{
					res=TRUE;

					recover_from_disease(on);

					sprintf(temp,"A magenta spray washes over %s, improving %s health!",
								  on->name,
								  on->his_her);

					print_spell_description(temp);
				}
				else
				{
					sprintf(temp,"%s is not diseased! Thy spell art wasted.",on->name);

					SCROLL(1,0,temp);
					bad_sound();
				}
			}
			else
				add_lost_spell_pts(adv,2);
		}
	}

	return(res);
}

int _PASCAL cast_CURE_SEVERE_INJURY(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_priest_cure_spells(adv,CURE_SEVERE_INJURY));
}

int _PASCAL cast_PROTECTION_FROM_TRAPS(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[120];

	if (enough_spell_points_to_cast(adv,2))
	{
		res=TRUE;

		adv->in_effect.prot_traps+=((adv->level*2)+(effective_spell_luck(adv)/2));

		sprintf(temp,"%s claps %s hands and invokes a shimmering "
					 "shield engulfing thy party.",
					 adv->name,
					 adv->his_her);

		print_spell_description(temp);
	}

	return(res);
}

int _PASCAL cast_RESURRECT(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	PLAYER *on;
	char temp[120];
	int whom;
	int i;
	static char *moves[]={"hands start to twitch",
						  "feet start to twitch",
						  "head starts to move",
						  "eyes begin to open",
						  "mouth moves",
						  "heart starts beating"};

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,3))
		{
			if (IN_DUNGEON                                         &&
				the_party.dungeon_level==2                     &&
				the_party.dungeon_current_feature==DNG_SPECIAL &&
				dungeon.nname==DN_HELLS)
			{
				special_hells2_resurrect();
				res=TRUE;
			}
			else
			{
				whom=adv_select_adventurer("Cast Resurrect","on whom?",FALSE);

				if (whom!=ERR)
				{
					on=&TPP[whom];

					if (on->is_dead)
					{
						res=TRUE;

						on->is_dead=FALSE;
						on->current_hp=1;

						i=rand()%SIZE(moves);

						sprintf(temp,"%s lays %s hands on %s and utters great incantations.",
									  adv->name,
									  adv->his_her,
									  on->name);

						print_spell_description(temp);

						pause(1);

						sprintf(temp,"%s%s %s!\n\n%s hath bestowed life to a lifeless corpse!",
									  on->name,
									  end_s(on->name),
									  moves[i],
									  adv->name);

						SCROLL(1,14,temp);
						good_sound();
					}
					else
					{
						if (on->is_dust)
							sprintf(temp,"%s art dust, only divine intervention can bestow life on %s!",
									on->name,
									on->him_her);
						else
							sprintf(temp,"%s is not dead! Thy spell art wasted.",on->name);

						SCROLL(1,0,temp);
						bad_sound();
					}

					adv->current_hp=1;

					pause(2);

					sprintf(temp,"%s feels weak!",adv->name);

					SCROLL(1,0,temp);
					bad_sound();
				}
				else
					add_lost_spell_pts(adv,3);
			}
		}
	}

	return(res);
}

int _PASCAL cast_CURE_CRITICAL_INJURY(PLAYER *adv,SPELL_NAME *spell_name)
{
	return(cast_priest_cure_spells(adv,CURE_CRITICAL_INJURY));
}

int _PASCAL cast_SPELL_OF_PASSAGE(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[80];

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,3))
		{
			res=TRUE;

			adv->in_effect.spell_of_passage+=(adv->level*5);

			sprintf(temp,"%s looks up to ye sky whilst praying...",adv->name);

			print_spell_description(temp);
		}
	}

	return(res);
}

int _PASCAL cast_priest_cure_spells(PLAYER *adv,int spell_type)
{
	int res=FALSE;
	PLAYER *on;
	char temp[120];
	int whom;
	int hp;
	int sp_pts;
	char *spell_name;
	int dice_base;
	int rolls;

	switch(spell_type)
	{
		case CURE_LIGHT_INJURY    : dice_base=8;
									sp_pts=1;
									rolls=1;
									spell_name="Light";
									break;

		case CURE_SEVERE_INJURY   : dice_base=8;
									rolls=2;
									sp_pts=2;
									spell_name="Severe";
									break;

		case CURE_CRITICAL_INJURY : dice_base=8;
									rolls=3;
									sp_pts=3;
									spell_name="Critical";
									break;
	}

	if (enough_spell_points_to_cast(adv,sp_pts))
	{
		sprintf(temp,"Cast %s",spell_name);

		whom=adv_select_adventurer(temp,"Injury on?",TRUE);

		if (whom!=ERR)
		{
			on=&TPP[whom];

			hp=adv->level+get_dice_roll(dice_base,rolls,sp_pts);

			if (on->hp==on->current_hp)
			{
				if (IN_COMBAT)
				{
					cmbt_bad_msg("Naught appears to happen!",TRUE);
				}
				else
				{
					if (strcmp(on->file_name,adv->file_name))
					{
						sprintf(temp,"%s casts cure %s injury on %s, "
									 "but %s art uninjured!",
									 adv->name,
									 spell_name,
									 on->name,
									 on->he_she);
					}
					else
					{
						sprintf(temp,"%s casts cure %s injury on %sself, "
									 "but %s art unscathed!",
									 adv->name,
									 spell_name,
									 on->him_her,
									 on->he_she);
					}

					SCROLL(1,0,temp);
					bad_sound();
				}
			}
			else
			{
				res=TRUE;

				on->current_hp+=hp;

				if (on->current_hp>=on->hp)
				{
					on->current_hp=on->hp;

					sprintf(temp,"%s hath all %s hps restored.",
								 on->name,
								 on->his_her);
				}
				else
				{
					sprintf(temp,"%s gains %d hp, %s now hath %d left from %d.",
								  on->name,
								  hp,
								  on->he_she,
								  on->current_hp,
								  on->hp);
				}

				if (IN_COMBAT)
				{
					combat_write(14,temp,TRUE);
					spell_sound();
					twinkle(CMBT_X(on->x),CMBT_Y(on->y));
				}
				else
				{
					SCROLL(1,14,temp);
					spell_sound();
				}
			}
		}
		else
			add_lost_spell_pts(adv,sp_pts);
	}

	return(res);
}
