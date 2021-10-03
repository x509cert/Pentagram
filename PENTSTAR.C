#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL stars_draw_line(int x,int y)
{
	_setcolor(4);
	_moveto(x,y);
	_lineto(x+210,y);
	_moveto(x,y+2);
	_lineto(x+210,y+2);

	_setcolor(12);
	_moveto(x-1,y+1);
	_lineto(x+211,y+1);
}

void _PASCAL stars_draw_point(int x,int y,int size)
{
	FFPLOT(x,y,15);

	if (size)
	{
		FFPLOT(x+1,y,15);
		FFPLOT(x,y+1,15);
		FFPLOT(x+1,y+1,15);
	}
}

void _PASCAL stars_draw_kayne(int x,int y)
{
	static int stars[]={10,22,1,
						47,14,1,
						31,41,0,
						38,39,0,
						46,37,0,
						38,48,0,
						40,52,0,
						42,57,0,
						30,67,1,
						59,60,1};
	int i;

	for (i=0; i<SIZE(stars); i+=3)
		stars_draw_point(x+stars[i],y+stars[i+1],stars[i+2]);
}

void _PASCAL stars_draw_glamhelm(int x,int y)
{
	static int stars[]={8,  22,0,
						34, 23,1,
						51, 34,1,
						70, 44,0,
						78, 63,0,
						115,66,0,
						125,46,1};
	int i;

	for (i=0; i<SIZE(stars); i+=3)
		stars_draw_point(x+stars[i],y+stars[i+1],stars[i+2]);
}

void _PASCAL stars_draw_gellen(int x,int y)
{
	static int stars[]={41,19,0,
						39,27,0,
						45,35,0,
						39,50,0,
						45,53,0,
						22,71,0,
						25,69,0,
						61,73,0,
						40,75,1,
						40,91,1,
						42,81,1};
	int i;

	for (i=0; i<SIZE(stars); i+=3)
		stars_draw_point(x+stars[i],y+stars[i+1],stars[i+2]);
}

void _PASCAL stars_draw_incuus(int x,int y)
{
	static int stars[]={4, 6, 0,
						26,6, 0,
						55,5, 0,
						74,6, 0,
						76,14,0,
						53,16,0,
						56,34,1,
						19,36,0,
						28,20,1,
						22,14,0};
	int i;

	for (i=0; i<SIZE(stars); i+=3)
		stars_draw_point(x+stars[i],y+stars[i+1],stars[i+2]);
}
