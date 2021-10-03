#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *	Player Missile Options #2
 *
 */

void _FAR _CDECL cmbt_missile_draw_red(int x,int y)
{
	int rx=CMBT_X(x)+4;
	int ry=CMBT_Y(y)+5;
	int i,j;
	char c;

	for (i=0; i<12; i++)
		for (j=0; j<12; j++)
			if (c=missile_red[i][j])
				FFPLOT(rx+j,ry+i,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_white(int x,int y)
{
	int rx=CMBT_X(x)+4;
	int ry=CMBT_Y(y)+5;
	int i,j;
	char c;

	for (i=0; i<12; i++)
		for (j=0; j<12; j++)
			if (c=missile_white[i][j])
				FFPLOT(rx+j,ry+i,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_magenta(int x,int y)
{
	int rx=CMBT_X(x)+4;
	int ry=CMBT_Y(y)+5;
	int i,j;
	char c;

	for (i=0; i<12; i++)
		for (j=0; j<12; j++)
			if (c=missile_magenta[i][j])
				FFPLOT(rx+j,ry+i,(char)((c==0x4)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_blue(int x,int y)
{
	int rx=CMBT_X(x)+4;
	int ry=CMBT_Y(y)+5;
	int i,j;
	char c;

	for (i=0; i<12; i++)
		for (j=0; j<12; j++)
			if (c=missile_blue[i][j])
				FFPLOT(rx+j,ry+i,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_west_arrow(int x,int y)
{
	int rx=CMBT_X(x)+2;
	int ry=CMBT_Y(y)+8;
	int i,j;
	char c;

	for (i=0; i<15; i++)
		for (j=0; j<5; j++)
			if (c=missile_arr_west[j][i])
				FFPLOT(rx+i,ry+j,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_east_arrow(int x,int y)
{
	int rx=CMBT_X(x)+3;
	int ry=CMBT_Y(y)+8;
	int i,j;
	char c;

	for (i=0; i<15; i++)
		for (j=0; j<5; j++)
			if (c=missile_arr_east[j][i])
				FFPLOT(rx+i,ry+j,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_north_arrow(int x,int y)
{
	int rx=CMBT_X(x)+8;
	int ry=CMBT_Y(y)+3;
	int i,j;
	char c;

	for (i=0; i<5; i++)
		for (j=0; j<14; j++)
			if (c=missile_arr_nrth[j][i])
				FFPLOT(rx+i,ry+j,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_south_arrow(int x,int y)
{
	int rx=CMBT_X(x)+8;
	int ry=CMBT_Y(y)+3;
	int i,j;
	char c;

	for (i=0; i<5; i++)
		for (j=0; j<14; j++)
			if (c=missile_arr_sth[j][i])
				FFPLOT(rx+i,ry+j,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_sling_shot(int x,int y)
{
	int rx=CMBT_X(x)+7;
	int ry=CMBT_Y(y)+8;
	int i,j;
	char c;

	for (i=0; i<6; i++)
		for (j=0; j<6; j++)
			if (c=missile_sling_shot[i][j])
				FFPLOT(rx+j,ry+i,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_rock(int x,int y)
{
	int rx=CMBT_X(x)+5;
	int ry=CMBT_Y(y)+5;
	int i,j;
	char c;

	for (i=0; i<8; i++)
		for (j=0; j<10; j++)
			if (c=missile_rock[i][j])
				FFPLOT(rx+j,ry+i,(char)((c==0xD)?0:c));
}

void _FAR _CDECL cmbt_missile_draw_flask(int x,int y)
{
	int rx=CMBT_X(x)+6;
	int ry=CMBT_Y(y)+7;
	int i,j;
	char c;

	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
			if (c=missile_flask[i][j])
				FFPLOT(rx+j,ry+i,(char)((c==0xD)?0:c));
}
