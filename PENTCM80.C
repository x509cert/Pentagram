#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include "mmalloc.h"

/*
 *
 *	Build Combat Graphics
 *
 */

static char _FAR *cmbt_wall_buffer;
static char _FAR *cmbt_grass_buffer;
static char _FAR *cmbt_menu_buffer;
static int		  walls_needed;

void _PASCAL draw_cmbt_wall(int x,int y)
{
	if (walls_needed)
		_putimage(x*21+1,y*22+1,cmbt_wall_buffer,_GPSET);
}

void _PASCAL draw_cmbt_grass(int x,int y)
{
	_putimage(x*21+1,y*22+1,cmbt_grass_buffer,_GPSET);
}

void _PASCAL load_cmbt_images()
{
	load_cmbt_wall();
	load_cmbt_rip();
	load_cmbt_options();
}

void _PASCAL load_cmbt_rip()
{
	FILE *fptr;
	char temp[30];

	sprintf(temp,"%s%s.PIC",PIC_DIRECTORY,IN_DUNGEON?"CMBTRIP":"CMBTRIP2");

	fptr=fopen(temp,"rb");

	if (fptr==NULL)
		panic_FILE(temp);

	cmbt_rip_buffer=(char _FAR *)Mmalloc(MONSTER_IMAGE_SIZE);

	if (cmbt_rip_buffer==(char _FAR *)NULL)
		panic_RAM("Combat RIP");

	fread((void *)cmbt_rip_buffer,MONSTER_IMAGE_SIZE,1,fptr);

	fclose(fptr);
}

void _PASCAL load_cmbt_wall()
{
	FILE *fptr;
	long size=290L;
	char temp[30];
	char *im;

	walls_needed=FALSE;

	if (IN_DUNGEON)
	{
		im="DNG_WALL";
		walls_needed=TRUE;
	}
	else
	if (pent_data.current_feature==HILLS	 ||
		pent_data.current_feature==MOUNTAINS ||
		pent_data.current_feature==HIGH_MOUNTAINS)
	{
		im="CMBTSTNE";
		walls_needed=TRUE;
	}
	else
	if (pent_data.current_feature==FOREST)
	{
		im="CMBTTREE";
		walls_needed=TRUE;
	}

	if (walls_needed)
	{
		sprintf(temp,"%s%s.PIC",PIC_DIRECTORY,im);

		fptr=fopen(temp,"rb");

		if (fptr==NULL)
			panic_FILE("Dungeon Wall");

		cmbt_wall_buffer=(char _FAR *)Mmalloc((size_t)size);

		if (cmbt_wall_buffer==(char _FAR *)NULL)
			panic_RAM("Dungeon Wall");

		fread((void *)cmbt_wall_buffer,(size_t)size,1,fptr);

		fclose(fptr);
	}

	if (!IN_DUNGEON)
	{
		sprintf(temp,"%sCMBTGRSS.PIC",PIC_DIRECTORY);

		fptr=fopen(temp,"rb");

		if (fptr==NULL)
			panic_FILE("Combat Grass");

		cmbt_grass_buffer=(char _FAR *)Mmalloc((size_t)size);

		if (cmbt_grass_buffer==(char _FAR *)NULL)
			panic_RAM("Combat Grass");

		fread((void *)cmbt_grass_buffer,(size_t)size,1,fptr);

		fclose(fptr);
	}
}

void _PASCAL load_cmbt_options()
{
	FILE *fptr;
	long size=6500L;
	char temp[30];

	sprintf(temp,"%sCMBTMENU.PIC",PIC_DIRECTORY);

	fptr=fopen(temp,"rb");

	if (fptr==NULL)
		panic_FILE("Combat Menu");

	cmbt_menu_buffer=(char _FAR *)Mmalloc((size_t)size);

	if (cmbt_menu_buffer==(char _FAR *)NULL)
		panic_RAM("Combat Menu");

	fread((void *)cmbt_menu_buffer,(size_t)size,1,fptr);

	fclose(fptr);
}

void _PASCAL kill_cmbt_images()
{
	kill_cmbt_wall();
	kill_cmbt_options();
	kill_cmbt_rip();
}

void _PASCAL kill_cmbt_wall()
{
	if (walls_needed)
		Mfree((void *)cmbt_wall_buffer);

	if (!IN_DUNGEON)
		Mfree((void *)cmbt_grass_buffer);
}

void _PASCAL kill_cmbt_rip()
{
	Mfree((void *)cmbt_rip_buffer);
}

void _PASCAL kill_cmbt_options()
{
	Mfree((void *)cmbt_menu_buffer);
}

void _PASCAL draw_combat_logo()
{
	_setactivepage(1);
	generic_pic_draw(211,0,"CMBTSWRD");
	generic_pic_draw(199,26,"CMBTBACK");
	_setactivepage(0);
}

void _PASCAL page_in_cmbt_screen()
{
	move_EGA_pages(0,2);
	melt_EGA_pages(1,0,39);
}

void _PASCAL page_out_cmbt_screen()
{
	melt_EGA_pages(2,0,41);
}

void _PASCAL build_combat_screen()
{
	int i;

	_setactivepage(1);

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,0,0,190,199);

	_setcolor(4);

	for (i=0; i<=CMBT_AREA_X; i++)
	{
		_moveto(i*CMBT_SIZE_X,0);
		_lineto(i*CMBT_SIZE_X,CMBT_SIZE_Y*CMBT_AREA_X);
	}

	for (i=0; i<=CMBT_AREA_Y; i++)
	{
		_moveto(0,i*CMBT_SIZE_Y);
		_lineto(CMBT_SIZE_X*CMBT_AREA_Y,i*CMBT_SIZE_Y);
	}

	_moveto(1,199);
	_lineto(190,199);
	_lineto(190,1);

	_setactivepage(0);
}

void _PASCAL cmbt_handle_options_draw_im()
{
	_putimage(213,30,cmbt_menu_buffer,_GPSET);
}
