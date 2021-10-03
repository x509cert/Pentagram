#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _CDECL enter_ruin_windless_haven() /* Spectre */
{
	GWINDOW win;
	static boundary[]={113,127,148,139,
						-1,-1,-1,-1};

	SCROLL(1,1,"Thy party ventures slowly into "
			   "ye ruined village of Windless Haven.");

	general_low_sound();
	pause(2);

	if (pent_data.spectre_visited && pent_data.wand_given)
	{
		SCROLL(1,0,"After much searching, thy party find naught but a broken sign!");

		bad_sound();

		return;
	}

	if (pent_data.talisman_1_found &&
		pent_data.talisman_2_found &&
		pent_data.talisman_3_found &&
		pent_data.talisman_4_found)
	{
		if (!pent_data.spectre_visited)
		{
			ruin_windless_haven_draw();
		}
	}
	else
	{
		win.x1=5;
		win.y1=3;
		win.x2=30;
		win.y2=19;
		win.back=0;
		win.border=3;

		SCROLL(1,0,"Whilst searching, thy party spot a small wooden signpost...");

		general_low_sound();

		pause(2);

		make_gwindow(&win);

		generic_pic_draw(58,24,"WHAVEN");

		click_box(113,127,B_OK);

		(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

		kill_gwindow(&win);

		SCROLL(1,0,"Sensing grave danger thy party leave ye ruins!");
		solemn_sound();
		pause(1);
	}
}

void _PASCAL ruin_windless_haven_draw()
{
	FILE *fptr;
	char temp[80];
	int imx=231;
	int imy=42;
	int xstart,x,y;
	int bytes_read;
	unsigned int chunk=64;
	int i;
	char letter[3];
	GWINDOW win;
	static int boundary[]={132,164,167,176,
							-1,-1,-1,-1};

	GX("Taking thee by surprise, an apparition appears amongst ye ruins.",BAD);

	win.x1=4;
	win.y1=5;
	win.x2=36;
	win.y2=24;
	win.border=4;
	win.back=0;

	xstart=x=win.x1*8+2;
	y=win.y1*8+2;

	make_gwindow(&win);

	generic_pic_draw(imx,imy,"SPECTRE");

	draw_image_box();

	click_box(132,164,B_OK);

	sprintf(temp,"%s%s",PIC_DIRECTORY,SPECTRE_TEXT_FILE);

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

	pent_data.spectre_visited=TRUE;

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	GX("Ye Talisman of Fate emits a warm glow as ye spirit vanishes.",GOOD);

	spectre_give_rod_of_devouring();
}

void _PASCAL spectre_give_rod_of_devouring()
{
	int person=ERR;
	int i;

	for (i=0; i<=P_NUM; i++)
	{
		if (player_is_alive(&TPP[i]) &&
			number_of_items(&TPP[i])<MAX_CARRY)
		{
			person=i;
			break;
		}
	}

	if (person!=ERR)
	{
		give_rod_of_devouring(person);
	}
	else                                    /* Clear hole for Rod   */
	{                                       /* by removing a potion */
		for (i=0; i<=P_NUM; i++)
		{
			if (player_is_alive(&TPP[i]))
			{
				if (TPP[i].items_carried[i].item==POTION)
				{
					TPP[i].items_carried[i].item=NOTHING;

					give_rod_of_devouring(i);

					break;
				}
			}
		}
	}
}

void _PASCAL give_rod_of_devouring(int person)
{
	char temp[120];

	add_to_player(DEVOURING_ROD,
				  NO_PLUS,
				  ITEM_CARRIED,
				  FALSE,
				  &TPP[person]);

	sprintf(temp,"An intricately engraved black rod appears in %s%s hand "
				 "as thy party hears a weak voice from within ye ruins..",
					TPP[person].name,
					end_s(TPP[person].name));

	SCROLL(1,14,temp);

	good_sound();
	pause(4);

	SCROLL(1,1,"\"Use ye Rod of Devouring wisely, it hast great power "
			   "in mortal combat.\"");

	general_low_sound();
	pause(3);

	SCROLL(1,1,"Ye voice, fading rapidly, continues, \"Though ye "
			   "may know not of it, thy party hath set us free "
			   "from our lifeless bonds. At last we may rest "
			  "peacefully in our cold graves.\"");

	good_sound();
	pause(2);

	add_xp_to_party(10000L);

	pent_data.wand_given=TRUE;
}
