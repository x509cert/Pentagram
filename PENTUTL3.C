#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>
#include <io.h>
#include "mmalloc.h"

void _PASCAL print_trap_sign(int x,int y)
{
	generic_pic_draw(x,y,"TRAP!");
}

void _PASCAL print_grim_reaper()
{
	GWINDOW win;
	static int boundary[]={140,124,175,136,-1,-1,-1,-1};

	win.x1=11;
	win.y1=2;
	win.x2=30;
	win.y2=19;
	win.back=0;
	win.border=7;

	make_gwindow(&win);

	generic_pic_draw(win.x1*8+4,win.y1*8+2,"GRIMRPR");

	click_box(140,124,B_OK);

	all_dead_sound();

	solemn_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

int _PASCAL tick(int x,int y,int on_off)
{
	static char da[][8]={        /*  */
						  {0x4,0x4,0x4,0x4,0x4,0x4,0xE,0x4},
						  {0x4,0x0,0x0,0x0,0x0,0xE,0x0,0x4},
						  {0x4,0x0,0x0,0x0,0x0,0xE,0x0,0x4},
						  {0x4,0xE,0x0,0x0,0xE,0x0,0x0,0x4},
						  {0x4,0x0,0xE,0x0,0xE,0x0,0x0,0x4},
						  {0x4,0x0,0x0,0xE,0x0,0x0,0x0,0x4},
						  {0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4},
					  };

	int i,j;

	if (on_off==ON)
	{
		for (i=0; i<7; i++)
			for (j=0; j<8; j++)
				if (da[i][j])
					FFPLOT(x+j,y+i,(char)da[i][j]);
	}
	else
	{
		_setcolor(0);
		_rectangle(_GFILLINTERIOR,x,y,x+8,y+7);
	}

	return(on_off==ON?TRUE:FALSE);
}

void _PASCAL draw_treasure_message()
{
	int y1=72;
	int y2=88;
	char *t="Treasure!";
	int xpos=160-((strlen(t)*8)/2);
	int ypos=y1+((y2-y1)/2)-14;
	GWINDOW win;

	win.x1=14;
	win.y1=8;
	win.x2=28;
	win.y2=14;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	generic_pic_draw(145,78,"TREASURE");

	print_text(t,xpos,  ypos,  NORMAL_HEIGHT,12);
	print_text(t,xpos-1,ypos-1,NORMAL_HEIGHT,4);

	treasure_sound();

	pause(2);

	kill_gwindow(&win);
}

void _PASCAL draw_gravestone(int x,int y)
{
	generic_pic_draw(x,y,"GRAVE");
}

void _PASCAL draw_image_box()
{
	_setcolor(6);
	_rectangle(_GBORDER,215,40,265,73);
	_rectangle(_GBORDER,214,39,266,74);

	_setpixel(216,41);
	_setpixel(216,72);
	_setpixel(264,41);
	_setpixel(264,72);

	_setcolor(0);
	_setpixel(214,39);
	_setpixel(214,74);
	_setpixel(266,39);
	_setpixel(266,74);
}

void _PASCAL load_finish_image()
{
	_setactivepage(5);
	generic_pic_draw(24,20,"LEFIN");
	_setactivepage(0);
}

void _PASCAL generic_pic_draw(int x,int y,char *filename)
{
	char temp[80];
	FILE *fptr;
	char _FAR *buffer;
	size_t buffer_sz;            /* COA is fulled PATH'ed */

	if (strstr(filename,".ICN")!=NULL &&
		strstr(filename,"COA")!=NULL)
		strcpy(temp,filename);
	else
		sprintf(temp,"%s%s.PIC",PIC_DIRECTORY,filename);

	fptr=fopen(temp,"rb");

	if (fptr==(FILE *)NULL)
		panic_FILE(temp);

	buffer_sz=(unsigned)filelength(fileno(fptr));
	buffer_sz+=16;

	buffer=(char _FAR *)Mmalloc(buffer_sz);

	if (buffer==(char _FAR *)NULL)
		panic_RAM("Generic Image buffer");

	fread((void *)buffer,buffer_sz,1,fptr);

	fclose(fptr);

	_putimage(x,y,buffer,_GPSET);

	Mfree((void *)buffer);
}
