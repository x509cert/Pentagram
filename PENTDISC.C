#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <io.h>
#include <bstrings.h>

static char      *ROSTER_EMPTY="No Adventurers in Roster!";
static PLAYER    all_disc[MAX_ON_DISC];
static int       num_on_disc;

int _PASCAL select_a_disc_adventurer(char *what,int read_disc)	 /* Returns -1 on error 	*/
{                                                                /* Otherwise index into    */
																 /* all_disc_players [0..9] */
	int you_sure;
	int i;
	char temp[80];
	char *top1="    Name        Race Cls Lv Stat HP";
	char head[40];
	int selected;
	int fin=FALSE;
	static int boundary[]={ 8,  40, 300, 46,
							8,  48, 300, 54,
							8,  56, 300, 62,
							8,  64, 300, 70,
							8,  72, 300, 78,
							8,  80, 300, 86,
							8,  88, 300, 94,
							8,  96, 300,102,
							8,  104,300,110,
							8,  112,300,118,
							265,125,300,137,
							-1,-1,-1,-1};

	if (read_disc)
	{
		log_all_disc_players();

		click_box(265,125,B_QUIT);

		strcpy(head,what);

		_settextposition(select_win.y1+1,select_win.x1+(((select_win.x2-select_win.x1)/2)-strlen_half(head)));
		_settextcolor(14);
		_outtext(head);

		_settextposition(select_win.y1+2,select_win.x1+1);
		_settextcolor(9);
		_outtext(top1);

		for (i=0; i<=num_on_disc; i++)
			place_one_person_in_select(&all_disc[i],i);
	}

	while (!fin)
	{
		selected=mouse_in_range(boundary,"ABCDEFGHIJQ","");

		if ((selected<=num_on_disc) || (selected==10))
		{
			switch(selected)
			{
				case 0  :
				case 1  :
				case 2  :
				case 3  :
				case 4  :
				case 5  :
				case 6  :
				case 7  :
				case 8  :
				case 9  :  if (strnicmp("kill",head,4)==0)
						   {
								stpcvt(all_disc[selected].name,RTWHITE);

								sprintf(temp,"Kill %s. Art thou sure?",
											  all_disc[selected].name);

								you_sure=gget_yn(temp);

								fin=(you_sure==YES)?TRUE:FALSE;
						   }
						   else
								fin=TRUE;

						   break;

				default :  fin=TRUE; break;
			}
		}
	}

	if (selected==10)
		return(ERR);
	else
	{
		memcpy((void *)&adv,(void *)&all_disc[selected],sizeof(adv));
		return(selected);
	}
}

static void _PASCAL _NEAR place_one_person_in_select(PLAYER *adv,int pos)
{
	char temp[60];
	char *ra,*cl,st[10];

	switch(adv->nrace)
	{
		case HUMAN       : ra="Hmn";     break;
		case DWARF       : ra="Dwf";     break;
		case HIGH_ELF    : ra="Elf";     break;
		case GNOME       : ra="Gnm";     break;
		case HALF_OGRE   : ra="\xABOg";  break;       /* PC */
		case HALFLING    : ra="\xAB  ";  break;       /* PC */
		case SYLVAN_ELF  : ra="Syl";     break;
		case DARK_ELF    : ra="Drk";     break;
	}

	switch(adv->nclass)
	{
		case WARRIOR	 : cl="War"; break;
		case PRIEST 	 : cl="Pri"; break;
		case WIZARD 	 : cl="Wiz"; break;
		case DRUID		 : cl="Dru"; break;
		case THIEF		 : cl="Thi"; break;
		case RANGER 	 : cl="Ran"; break;
		case CRUSADER	 : cl="Cru"; break;
		case BARD		 : cl="Brd"; break;
		case MONK		 : cl="Mnk"; break;
		case ILLUSIONIST : cl="Ill"; break;
		case HUNTER 	 : cl="Hun"; break;
		case DUELIST	 : cl="Due"; break;
	}

	strcpy(st,get_adv_status_abbr(adv));

	sprintf(temp,"    %-12s%-5s%-4s%-3d%-5s%-3d",
							adv->name,
							ra,
							cl,
							adv->level,
							st,
							adv->current_hp);


	_settextcolor(5);
	_settextposition(select_win.y1+3+pos,select_win.x1+1);
	_outtext(temp);

	sprintf(temp,"%cù",pos+'A');

	_settextcolor(13);
	_settextposition(select_win.y1+3+pos,select_win.x1+1);
	_outtext(temp);

	tick(28,40+pos*8,(adv->in_party?ON:OFF));
}

char *train_get_free_slot()
{
	int i;
	static char temp[30];

	for (i=0; i<MAX_ON_DISC; i++)
	{
		sprintf(temp,ADV_PREFIX,i);

		if (access(temp,0))
			return(temp);
	}

	return("~");
}

void _PASCAL purge_an_adventurer()
{
	int sel;

	if (num_on_disc==ERR)
	{
		GX(ROSTER_EMPTY,BAD);
		return;
	}

	make_gwindow(&select_win);

	if ((sel=select_a_disc_adventurer("Kill an Adventurer",TRUE))!=ERR)
	{
		if (all_disc[sel].in_party)
		{
			GX("Ye cannot purge a party member!",BAD);
		}
		else
		{
			unlink(all_disc[sel].file_name);
			log_all_disc_players();
		}
	}

	kill_gwindow(&select_win);
}

void _PASCAL view_an_adventurer()
{
	int sel;
	FILE *fptr;
	int read_disc=TRUE;

	if (num_on_disc==ERR)
	{
		GX(ROSTER_EMPTY,BAD);
		return;
	}

	make_gwindow(&select_win);

	do
	{
		if ((sel=select_a_disc_adventurer("View an Adventurer",read_disc))!=ERR)
		{
			fptr=fopen(all_disc[sel].file_name,"rb");

			if (fptr==(FILE *)NULL)
				panic_FILE("Adventurer file");

			fread((void *)&adv,sizeof(PLAYER),1,fptr);

			fclose(fptr);

			show_adventurer(&adv);

			read_disc=FALSE;
		}

	} while (sel!=ERR);

	kill_gwindow(&select_win);
}

int _PASCAL load_party_from_disc()
{
	int res;

	log_all_disc_players();

	if (num_on_disc==ERR)
	{
		GX(ROSTER_EMPTY,BAD);
		res=FALSE;
	}
	else
	if (P_NUM==ERR)
	{
		GX("No Adventurers in ye party!",BAD);
		res=FALSE;
	}
	else
	{
		generate_initial_party_order();
		res=TRUE;
	}

	return(res);
}

void _PASCAL save_party_to_disc()
{
	int i;
	FILE *fptr;

	for (i=0; i<=P_NUM; i++)
	{
		fptr=fopen(TPP[i].file_name,"wb");

		fwrite((void *)&TPP[i],
			   (size_t)sizeof(TPP[i]),
			   (size_t)1,
			   fptr);

		fclose(fptr);
	}
}

void _PASCAL save_party_data_to_disc()		 /* Saves THE_PARTY data, except adventurers */
{
	FILE *fptr;
	size_t size=sizeof(the_party.num_in_party)+
				sizeof(the_party.resting)+
				sizeof(the_party.fire_lit)+
				sizeof(the_party.all_dead)+
				sizeof(the_party.adventuring)+
				sizeof(the_party.in_dungeon)+
				sizeof(the_party.in_ruin)+
				sizeof(the_party.in_town)+
				sizeof(the_party.in_combat)+
				sizeof(the_party.mapping_in_dungeon)+
				sizeof(the_party.dungeon_level)+
				sizeof(the_party.dungeon_x)+
				sizeof(the_party.dungeon_y)+
				sizeof(the_party.dungeon_current_feature)+
				sizeof(the_party.xp_earned)+
				sizeof(the_party.gc_earned);

	fptr=fopen(PARTYFILE,"wb");

	fwrite((void *)&the_party,size,(size_t)1,fptr);

	fclose(fptr);
}

void _PASCAL load_party_data_from_disc()	   /* Loads THE_PARTY data, except adventurers */
{
	FILE *fptr;
	size_t size=sizeof(the_party.num_in_party)+
				sizeof(the_party.resting)+
				sizeof(the_party.fire_lit)+
				sizeof(the_party.all_dead)+
				sizeof(the_party.adventuring)+
				sizeof(the_party.in_dungeon)+
				sizeof(the_party.in_ruin)+
				sizeof(the_party.in_town)+
				sizeof(the_party.in_combat)+
				sizeof(the_party.mapping_in_dungeon)+
				sizeof(the_party.dungeon_level)+
				sizeof(the_party.dungeon_x)+
				sizeof(the_party.dungeon_y)+
				sizeof(the_party.dungeon_current_feature)+
				sizeof(the_party.xp_earned)+
				sizeof(the_party.gc_earned);

	fptr=fopen(PARTYFILE,"rb");

	if (fptr==NULL)
	{
		memset((void *)&the_party,0,sizeof(the_party));
		fptr=fopen(PARTYFILE,"wb");

		fwrite((void *)&the_party,size,1,fptr);

		fclose(fptr);
	}
	else
	{
		fread((void *)&the_party,size,1,fptr);

		fclose(fptr);
	}
}

void _PASCAL log_all_disc_players()
{
	int i;
	char temp[30];
	FILE *fptr;

	num_on_disc=P_NUM=ERR;

	for (i=0; i<MAX_ON_DISC; i++)
	{
		sprintf(temp,ADV_PREFIX,i);

		fptr=fopen(temp,"rb");

		if (fptr==(FILE *)NULL)
			continue;

		fread((void *)&adv,sizeof(adv),1,fptr);

		num_on_disc++;

		memcpy((void *)&all_disc[num_on_disc],(void *)&adv,sizeof(adv));

		if (adv.in_party)
		{
			P_NUM++;

			memcpy((void *)&TPP[P_NUM],(void *)&adv,sizeof(adv));
		}

		fclose(fptr);
	}
}

int _PASCAL who_is_going(char *mess)
{
	int sel;
	FILE *fptr;
	int read_disc=TRUE;

	log_all_disc_players();

	if (num_on_disc==ERR)
	{
		GX(ROSTER_EMPTY,BAD);
		sel=ERR;
	}
	else
	{
		make_gwindow(&select_win);

		if ((sel=select_a_disc_adventurer(mess,read_disc))!=ERR)
		{
			fptr=fopen(all_disc[sel].file_name,"rb");

			if (fptr==(FILE *)NULL)
				panic_FILE("Adventurer file");

			fread((void *)&adv,sizeof(PLAYER),1,fptr);

			fclose(fptr);

			read_disc=FALSE;
		}

		kill_gwindow(&select_win);
	}

	return(sel);
}

void _PASCAL save_adventurer(PLAYER *player)
{
	FILE *fptr;
	char temp[50];

	player->here_to_fool1=(char)(rand()%20);
	player->here_to_fool2=(char)(40+rand()%20);
	player->here_to_fool3=(char)(80+rand()%20);

	fptr=fopen(player->file_name,"wb");

	if (fptr==(FILE *)NULL)
	{
		sprintf(temp,"Adventurer file %s",player->file_name);
		panic_FILE(temp);
	}

	fwrite((void *)player,sizeof(PLAYER),1,fptr);

	fclose(fptr);
}

void _PASCAL add_take_from_party()
{
	int sel;
	FILE *fptr;
	int read_disc=TRUE;

	if (num_on_disc==ERR)
	{
		GX(ROSTER_EMPTY,BAD);
		return;
	}

	make_gwindow(&select_win);

	do
	{
		if ((sel=select_a_disc_adventurer("Add or Drop an Adventurer",read_disc))!=ERR)
		{
			fptr=fopen(all_disc[sel].file_name,"rb");

			if (fptr==(FILE *)NULL)
				panic_FILE("Adventurer file");

			fread((void *)&adv,sizeof(PLAYER),1,fptr);

			fclose(fptr);

			if (adv.in_party)
			{
				if (--P_NUM<=ERR)
				{
					GX("Ye must have at least one adventurer in thy party!!",BAD);
					P_NUM++;
				}
				else
				{
					adv.in_party=FALSE;
					tick(28,40+sel*8,OFF);

					save_adventurer(&adv);
				}
			}
			else
			if (!adv.in_party)
			{
				if (++P_NUM>MAX_PARTY-1)
				{
					GX("Thy party of hardy adventurers art full!",BAD);
					P_NUM--;
				}
				else
				{
					adv.in_party=TRUE;
					tick(28,40+sel*8,ON);

					save_adventurer(&adv);
				}
			}

			read_disc=FALSE;
		}

	} while (sel!=ERR);

	kill_gwindow(&select_win);
}

void _PASCAL change_adv_name()
{
	int sel;
	FILE *fptr;
	int read_disc=TRUE;

	if (num_on_disc==ERR)
	{
		GX(ROSTER_EMPTY,BAD);
		return;
	}

	make_gwindow(&select_win);

	do
	{
		if ((sel=select_a_disc_adventurer("Who shalt be Renamed?",read_disc))!=ERR)
		{
			fptr=fopen(all_disc[sel].file_name,"rb");

			if (fptr==(FILE *)NULL)
				panic_FILE("Adventurer file");

			fread((void *)&adv,sizeof(PLAYER),1,fptr);

			fclose(fptr);

			read_disc=change_this_adv_name(&adv);
		}

	} while (sel!=ERR);

	kill_gwindow(&select_win);
}

int _PASCAL change_this_adv_name(PLAYER *adv)
{
	GWINDOW win;
	char temp[80];
	int fin=FALSE;
	char *border="[            ]";

	win.x1=7;
	win.y1=5;
	win.x2=33;
	win.y2=12;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(12);

	sprintf(temp,"Rename %s ye",adv->name);
	_settextposition(win.y1+1,20-strlen_half(temp));
	_outtext(temp);

	sprintf(temp,"%s to?",adv_title(adv));
	_settextposition(win.y1+2,20-strlen_half(temp));
	_outtext(temp);

	_settextcolor(10);
	_settextposition(win.y2-2,13);
	_outtext(border);

	while (!fin)
	{
		strcpy(temp,gquery(14,win.y2-2,11,2,'A',adv->name));

		if (strlen(temp))
			fin=TRUE;
		else
			GX("How wouldst thou like to be known as _____?",BAD);
	}

	kill_gwindow(&win);

	if (strcmp(adv->name,temp))
	{
		strcpy(adv->name,temp);
		save_adventurer(adv);

		return(TRUE);
	}

	return(FALSE);
}

void _PASCAL save_global_data()
{
	FILE *fptr;

	pent_data.checksum=global_data_checksum();

	fptr=fopen(GLOBAL_DATA,"wb");
	fwrite((void *)&pent_data,sizeof(pent_data),1,fptr);
	fclose(fptr);
}

void _PASCAL load_global_data()
{
	FILE *fptr;

	fptr=fopen(GLOBAL_DATA,"rb");

	if (fptr==NULL)
	{
		setup_global_data();
	}
	else
	{
		fread((void *)&pent_data,sizeof(pent_data),1,fptr);
		fclose(fptr);

		check_global_data_checksum();
	}
}

static void _PASCAL _NEAR check_global_data_checksum()
{
	if (global_data_checksum()!=pent_data.checksum)
		panic("GLOBAL.PNT is corrupt");
}

static unsigned _PASCAL _NEAR global_data_checksum()
{
	int i;
	char *p;
	unsigned int chksum=0;

	p=(char *)&pent_data;

	for (i=0; i<sizeof(pent_data)-20; i++)
	{
		chksum+=*p;
		p++;
	}

	return(chksum);
}

void _PASCAL setup_global_data()
{
	int i;
	char temp1[80];
	char temp2[80];

	pent_data.date                      = START_DATE;
	pent_data.day                       = 7;
	pent_data.year                      = START_YEAR;
	pent_data.time_hour                 = 7;
	pent_data.time_minute               = 0;
	pent_data.current_day_night_icon    = 0;
	pent_data.season                    = AUTUMN;
	pent_data.moon_phase                = PHASE_2;

	pent_data.rain_level                = PRECIP_LIGHT;
	pent_data.rain_type                 = SLEET;
	pent_data.wind_level                = LIGHT_WIND;
	pent_data.cloud_level               = CLOUDY;
	pent_data.temperature               = COLD;
	pent_data.degrees_c                 = 5;

	pent_data.finished                  = FALSE;

	pent_data.talisman_1_found          = FALSE;
	pent_data.talisman_2_found          = FALSE;
	pent_data.talisman_3_found          = FALSE;
	pent_data.talisman_4_found          = FALSE;
	pent_data.told_about_talisman       = FALSE;

	pent_data.x                         = 89;
	pent_data.y                         = 86;
	pent_data.current_feature           = CITY;

	pent_data.sound                     = ON;

	pent_data.visited_guild             = FALSE;
	pent_data.date_since_guild_visit    = 0;
	pent_data.seer_visited              = FALSE;
	pent_data.spell_given               = FALSE;
	pent_data.spectre_visited           = FALSE;
	pent_data.wand_given                = FALSE;
	pent_data.kaldrutha_defeated		= FALSE;
	pent_data.mangreth_defeated 		= FALSE;
	pent_data.date_visit_wolfburg		= START_DATE;
	pent_data.year_visit_wolfburg		= START_YEAR;

	pent_data.devouring_rod_used        = 0;
	pent_data.curious_box_used			= 0;

	pent_data.combat_speed				= CSPEED_MED;

	pent_data.checksum                  = global_data_checksum();

	for (i=0; i<MAX_PARTY; i++)
		strcpy(pent_data.order[i],"~");

	strcpy(temp1,give_date(pent_data.date));

	sprintf(temp2,"%s, %u",temp1,pent_data.year);

	strcpy(pent_data.st_date,temp2);

	new_day(DONT_CHECK_BIRTHDAYS,FALSE);

	wizard_mode=quick_exit=in_exit=FALSE;
}

void _PASCAL load_game(int confirm)
{
	if (confirm)
		if (!gget_yn("Load Adventure. Sure?"))
			return;

	make_gplease_wait();

	load_global_data();
	load_party_data_from_disc();
	load_party_from_disc();

	game_loaded=TRUE;

	generate_initial_party_order();

	kill_gplease_wait();
}

void _PASCAL save_game(int confirm)
{
	if (confirm)
		if (!gget_yn("Save Adventure. Sure?"))
			return;

	make_gplease_wait();

	save_global_data();
	save_party_data_to_disc();
	save_party_to_disc();

	kill_gplease_wait();
}
