#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

void _PASCAL meet_random_party()
{
	OTHER_PARTY others[MAX_PARTY];
	int num_in_other;
	int x6=35+30;
	int x5=50+30;
	int x4=65+30;
	int xstart;
	int x,y;
	int bytes_read;
	char temp[80], letter[3];
	char cl[30];
	int chunk=64;
	int person=0;
	FILE *fptr;
	int i;
	int info_bought=FALSE;
	GWINDOW win;
	static int boundary[]={138,130,173,142
							-1,-1,-1,-1};

	GX("Thy party happens upon a benign band of adventurers!",GOOD);

	num_in_other=build_meeting_party(others);

	win.x1=4;
	win.y1=4;
	win.x2=37;
	win.y2=20;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	switch(num_in_other)
	{
		case 4 : xstart=x4; break;
		case 5 : xstart=x5; break;
		default: xstart=x6; break;
	}

	for (i=0; i<num_in_other; i++)
		draw_adv_image(others[i].nclass,xstart+i*35,31);

	y=70;
	x=xstart=35;

	strcpy(cl,get_class_string(others[0].nclass,
							   percent()>70?SX_MALE:SX_FEMALE));

	sprintf(temp,"Their head, a %s %s, speaks to %s:",
		get_condx_string(others[0].condx),
		cl,
		TPP[get_random_live_person()].name);

	write_little(temp,x,y-12,6,FAST);

	sprintf(temp,"%s%s",PIC_DIRECTORY,OTHER_PARTY_TEXT_FILE);

	fptr=fopen(temp,"rb");

	if (fptr==(FILE *)NULL)
		panic_FILE(temp);

	while (!feof(fptr))
	{
		bytes_read=fread((void *)temp,sizeof(char),chunk,fptr);

		for (i=0; i<bytes_read; i++)
		{
			temp[i]^=XOR_CODE;

			if (temp[i]=='\n')
			{
				x=xstart;
				y+=7;
			}
			else
			{
				letter[0]=temp[i];
				letter[1]='\0';

				write_little(letter,x,y,5,FAST);

				x+=4;
			}
		}
	}

	fclose(fptr);

	click_box(138,130,B_OK);

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	while (person!=ERR)
	{
		person=adv_select_adventurer("Who pays","ye 1,000 GC?",TRUE);

		if (person!=ERR)
		{
			if (TPP[person].cash>=1000L)
			{
				TPP[person].cash-=1000L;

				SCROLL(1,14,"Ye leader says unto thee-");
				scroll_scroll();

				if (percent()>60)
					rumour_dungeon_info(FALSE);
				else
				{
					rumour_open_index_file();
					rumour_general_info(R_DUNGEON1);
					rumour_close_index_file();
				}

				person=ERR;

				good_sound();

				info_bought=TRUE;
			}
			else
			{
				sprintf(temp,"%s hath but %luGC!",
							TPP[person].name,
							TPP[person].cash);

				GX(temp,BAD);
			}
		}
	}

	scroll_scroll();

	if (!info_bought)
	{
		scroll_wrap_write(0,"\"If thou think ye dost not need our "
							"knowledge - so be it!\", says ye leader.");

		scroll_scroll();
	}

	scroll_wrap_write(1,"Ye adventurers leave thy party to continue their own quests.");

	if (info_bought)
		good_sound();
	else
		bad_sound();
}

int _PASCAL build_meeting_party(OTHER_PARTY other_party[MAX_PARTY])
{
	static struct t {
						int nclass1, nclass2, nclass3;

					} poss_party[MAX_PARTY]={WARRIOR, CRUSADER, RANGER,
											 WARRIOR, CRUSADER, THIEF,
											 PRIEST,  PRIEST,   WIZARD,
											 WIZARD,  THIEF,    ILLUSIONIST,
											 THIEF,   THIEF,    DRUID,
											 WARRIOR, BARD,     MONK};
	int i,per,num;

	num=MAX_PARTY;

	if (percent()>70)
	{
		if (percent()>70)
			num--;

		num--;
	}

	for (i=0; i<MAX_PARTY; i++)
		other_party[i].nclass=0;

	for (i=0; i<num; i++)
	{
		per=percent();

		if (per>=0 && per<=60)
			other_party[i].nclass=poss_party[i].nclass1;
		else
		if (per>=61 && per<=85)
			other_party[i].nclass=poss_party[i].nclass2;
		else
			other_party[i].nclass=poss_party[i].nclass3;

		other_party[i].condx=other_party_get_condx();
	}

	return(num);
}

int _PASCAL other_party_get_condx()
{
	return(rand()%OP_BLOOD_STAINED+1);
}

char *get_condx_string(int condx)
{
	static char temp[30];

	switch(condx)
	{
		 case OP_BADLY_BRUISED   : strcpy(temp,"badly bruised");    break;
		 case OP_WOUNDED         : strcpy(temp,"wounded");          break;
		 case OP_BANDAGED        : strcpy(temp,"bandaged");         break;
		 case OP_HEAVILY_BANDAGED: strcpy(temp,"heavily bandaged"); break;
		 case OP_BLOOD_STAINED   : strcpy(temp,"blood stained");    break;
		 default                 : strcpy(temp,"stout");            break;
	}

	return(temp);
}
