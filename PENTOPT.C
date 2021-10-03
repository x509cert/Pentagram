#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include "mmalloc.h"

static char *note_buffer[MAX_ODIN_PAGES];

void _PASCAL front_options()
{
	static char *t[]={"Save Adventure",
					  "Sound is On",
					  "Combat Speed",
					  "About Pentagram",
					  "Leave Options"};
	char *t2="SOCAL";
	int fin=FALSE;
	GWINDOW win;
	int opt;
	static int boundary[]={86,48,230,54,
						   86,56,230,62,
						   86,64,230,70,
						   86,72,230,78,
						   86,80,230,86,
						  -1,-1,-1,-1};


	win.x1		= 11;
	win.y1      = 6;
	win.x2		= 30;
	win.y2		= 13;
	win.back    = 0;
	win.border  = 4;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,
					   win.y1+1,
					   5,
					   13);

	while (!fin)
	{
		_settextcolor(5);
		_settextposition(win.y1+2,win.x1+10);
		_outtext(pent_data.sound?"On ":"Off");

		_settextposition(win.y1+3,win.x1+14);

		switch(pent_data.combat_speed)
		{
			case CSPEED_SLOW : _outtext("Slow"); break;
			case CSPEED_MED  : _outtext("Med "); break;
			case CSPEED_FAST : _outtext("Fast"); break;
		}

		opt=mouse_in_range(boundary,t2,"SOCAQ");

		switch(opt)
		{
			case 0 : save_game(FALSE);
					 break;

			case 1 : pent_data.sound=(pent_data.sound==ON?OFF:ON);
					 delay(100);
					 break;

			case 2 : switch(pent_data.combat_speed)
					 {
						case CSPEED_SLOW : pent_data.combat_speed=CSPEED_MED;
										   break;

						case CSPEED_MED  : pent_data.combat_speed=CSPEED_FAST;
										   break;

						case CSPEED_FAST : pent_data.combat_speed=CSPEED_SLOW;
										   break;
					 }

					 delay(100);
					 break;

			case 3 : about_odin();
					 break;

			default: fin=TRUE;
					 break;
		}
	}

	kill_gwindow(&win);
}

static void _PASCAL _NEAR load_about_odin()
{
	int i;
	char temp[30];
	FILE *fptr;

	for (i=0; i<MAX_ODIN_PAGES; i++)
	{
		note_buffer[i]=(char *)Mmalloc(MAX_ODIN_NOTE_SIZE);

		if (note_buffer[i]==NULL)
			panic_RAM("Odin Pages");

		sprintf(temp,"%sODIN%d.TXT",PIC_DIRECTORY,i+1);

		fptr=fopen(temp,"r");

		if (fptr==NULL)
			panic_FILE(temp);

		fread((void *)note_buffer[i],MAX_ODIN_NOTE_SIZE,1,fptr);

		fclose(fptr);
	}
}

static void _PASCAL _NEAR kill_about_odin()
{
	int i;

	for (i=0; i<MAX_ODIN_PAGES; i++)
		Mfree((void *)note_buffer[i]);
}

static void _PASCAL _NEAR about_odin()
{
	GWINDOW win;
	int fin,page,oldpage;
	static boundary[]={50, 111,85, 123,
					   115,111,150,123,
					   180,111,215,123,
						-1,-1,-1,-1};

	load_about_odin();

	win.x1=2;
	win.y1=1;
	win.x2=34;
	win.y2=17;
	win.back=1;
	win.border=14;

	make_gwindow(&win);

	click_box(50, 111,B_PREV);
	click_box(115,111,B_NEXT);
	click_box(180,111,B_FINISH);

	fin=FALSE;
	page=0;
	oldpage=ERR;

	while (!fin)
	{
		if (oldpage!=page)
		{
			about_odin_cls();

			switch(page)
			{
				case 0 : about_pentagram();
						 break;

				default: about_odin_page(page-1);
						 break;
			}
		}

		oldpage=page;

		switch(mouse_in_range(boundary,"PNF","PNQ"))
		{
			case 0 : page--;
					 if (page<0)
						page=0;
					 break;

			case 1 : page++;
					 if (page>3)
						page=3;
					 break;

			default: fin=TRUE;
		}
	}

	kill_about_odin();
	kill_gwindow(&win);
}

static void _PASCAL _NEAR about_pentagram()
{
	int i;
	static char *t[]={"_Written and Designed",
					  "__by Michael Howard",
					  "",
					  "Copyright 1989-91 Odin",
					  "_Software Development"};

	draw_pentagram(117,79,15,13);

	generic_pic_draw(75,11,"INFOPENT");

	for (i=0; i<SIZE(t); i++)
		print_text(t[i],47,34+(i*9),NORMAL_HEIGHT,13);
}

static void _PASCAL _NEAR about_odin_cls()
{
	_setcolor(1);
	_rectangle(_GFILLINTERIOR,20,7,256,110);
}

static void _PASCAL _NEAR about_odin_page(int page)
{
	int i,j;
	int yoff=7;
	int xoff=20;
	int line;
	int finish=FALSE;
	int col;
	char temp[90];
	char ch;

	line=0;

	for (i=0; finish==FALSE; i++)
	{
		for (j=0; ;j++,i++)
		{
			ch=note_buffer[page][i];

			if (ch!='\n' && ch!='~')
				temp[j]=note_buffer[page][i];
			else
				break;
		}

		temp[j]='\0';

		switch(page)
		{
			case 0 : col=line?13:15;
					 break;

			case 1 : col=13;
					 break;

			case 2 : col=(line>=5 && line<=14)?14:13;

					 if (!line)
						col=15;

					 break;
		}

		write_little(temp,xoff,yoff+line*6,col,FAST);

		line++;

		if (ch=='~')
			finish=TRUE;
	}
}
