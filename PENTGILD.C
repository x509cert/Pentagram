#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

static char *muttering="Muttering to himself, Bjarn opens ye "
					   "secret door and disappears into ye gloomy corridor..";

int _PASCAL determine_last_guild_visit()	 /* Days since last visit */
{
	int diff;

	if (!pent_data.visited_guild)
		diff=100;                   /* Dummy value */
	else
		diff=pent_data.date-pent_data.date_since_guild_visit;

	return(diff);
}

void _PASCAL visit_guild_too_early()
{
	SCROLL(1,14,"Thy party sees many footprints, "
				"made by many pairs of leather boots..");
}

void _PASCAL guild_draw_face(GWINDOW *win)
{
	FILE *fptr;
	char temp[80];
	int xstart,x,y;
	int bytes_read;
	unsigned int chunk=64;
	int i;
	char letter[3];
	static int boundary[]={132,164,167,176,
							-1,-1,-1,-1};

	GX("Caught unawares, a stocky, bearded warrior blocks thy path!",BAD);

	win->x1=4;
	win->y1=5;
	win->x2=36;
	win->y2=24;
	win->border=4;
	win->back=0;

	xstart=x=(win->x1)*8+2;
	y=(win->y1)*8+2;

	make_gwindow(win);

	generic_pic_draw(221,44,"GUARD");

	draw_image_box();

	click_box(132,164,B_OK);

	sprintf(temp,"%s%s",
			PIC_DIRECTORY,
			pent_data.visited_guild?GUILD_TEXT_FILE2:GUILD_TEXT_FILE1);

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

	pent_data.date_since_guild_visit=pent_data.date;

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(win);
}

void _PASCAL guild_recruit_members(unsigned long price)
{
	int fin=FALSE;
	int select;
	char temp[80];

	while (!fin)
	{
		select=adv_select_adventurer("Who joins","ye Guild?",TRUE);

		if (select!=ERR)
		{
			if (TPP[select].guild_member)
			{
				sprintf(temp,"%s art already a member!",
						TPP[select].name);

				GX(temp,BAD);
			}
			else
			{
				if (TPP[select].cash<price)
				{
					sprintf(temp,"%s hath but %lu GC!",
							TPP[select].name,
							TPP[select].cash);

					GX(temp,BAD);
				}
				else
				{
					TPP[select].cash-=price;
					TPP[select].guild_member=TRUE;

					sprintf(temp,"%s art now a Guild Member!",
							TPP[select].name);

					GX(temp,GOOD);
				}
			}
		}
		else
			fin=TRUE;
	}
}

void _PASCAL first_visit_to_guild()
{
	GWINDOW win;

	guild_draw_face(&win);
	guild_recruit_members(250L);

	SCROLL(1,0,muttering);

	good_sound();
}

void _PASCAL more_visits_to_guild()
{
	GWINDOW win;

	guild_draw_face(&win);
	guild_recruit_members(300L);

	SCROLL(1,0,muttering);

	good_sound();
}
