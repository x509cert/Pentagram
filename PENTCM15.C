#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/*
 *
 *  Place Monster/Players in combat arena
 *  Combat Arena Utilities
 */

typedef struct pos_party_type {
								int x,y;

							  } POS_TYPE;

int _PASCAL build_entire_combat_arena(int encounter)
{
	int combat_area_size,hd;

	make_gplease_wait();

	load_cmbt_images();
	build_combat_screen();

	combat_area_size=determine_combat_area_size();
	init_cmbt_area(combat_area_size);

	hd=build_monsters(encounter);

	kill_gplease_wait();

	_setactivepage(1);

	pos_party(combat_area_size);
	pos_monst(combat_area_size,num_monsters);

	_setactivepage(0);

	page_in_cmbt_screen();

	return(hd);
}

void _PASCAL pos_monst(int combat_area, int num)
{
	switch(combat_area)
	{
		case CMBT_OPEN_AREA     : pos_monst_in_open_area(num);      break;
		case CMBT_CORRIDOR_AREA : pos_monst_in_corridor_area(num);  break;
		case CMBT_LL_AREA       : pos_monst_in_LL_area(num);        break;
		case CMBT_LR_AREA       : pos_monst_in_LR_area(num);        break;
		case CMBT_X_AREA        : pos_monst_in_X_area(num);         break;
	}
}

static void _PASCAL _NEAR pos_monst_in_open_area(int num)
{
	int i;
	int x,y;
	int dealt_with;

	for (i=0; i<num; i++)
	{
		dealt_with=FALSE;

		while (!dealt_with)
		{
			x=rand()%CMBT_SIZE_X;
			y=rand()%6;

			if (cmbt_area_contents(x,y)==IS_EMPTY)
			{
				dealt_with=TRUE;
				pos_one_monster(&the_monsters[i],x,y);
			}
		}
	}
}

static void _PASCAL _NEAR pos_monst_in_corridor_area(int num)
{
	pos_monst_in_open_area(num);
}

static void _PASCAL _NEAR pos_monst_in_LL_area(int num)
{
	int i;
	int x,y;
	int dealt_with;

	for (i=0; i<num; i++)
	{
		dealt_with=FALSE;

		while (!dealt_with)
		{
			x=rand()%6;
			y=rand()%3;

			y+=2;

			if (cmbt_area_contents(x,y)==IS_EMPTY)
			{
				dealt_with=TRUE;
				pos_one_monster(&the_monsters[i],x,y);
			}
		}
	}
}

static void _PASCAL _NEAR pos_monst_in_LR_area(int num)
{
	int i;
	int x,y;
	int dealt_with;

	for (i=0; i<num; i++)
	{
		dealt_with=FALSE;

		while (!dealt_with)
		{
			x=rand()%6;
			y=rand()%3;

			x+=5;
			y+=2;

			if (cmbt_area_contents(x,y)==IS_EMPTY)
			{
				dealt_with=TRUE;
				pos_one_monster(&the_monsters[i],x,y);
			}
		}
	}
}

static void _PASCAL _NEAR pos_monst_in_X_area(int num)
{
	switch(rand()%3)
	{
		case 0 : pos_monst_in_LR_area(num);   break;
		case 1 : pos_monst_in_LL_area(num);   break;
		default: pos_monst_in_open_area(num); break;
	}
}

void _PASCAL pos_party(int combat_area)
{
	switch(combat_area)
	{
		case CMBT_OPEN_AREA     : pos_party_in_open_area();     break;
		case CMBT_CORRIDOR_AREA : pos_party_in_corridor_area(); break;
		case CMBT_LL_AREA       : pos_party_in_LL_area();       break;
		case CMBT_LR_AREA       : pos_party_in_LR_area();       break;
		case CMBT_X_AREA        : pos_party_in_X_area();        break;
	}
}

static void _PASCAL _NEAR pos_party_in_LL_area()
{
	int i;
	static POS_TYPE pos[]={{4,6},
						   {5,6},
						   {4,7},
						   {5,7},
						   {5,8},
						   {6,8}};

	for (i=0; i<SIZE(pos); i++)
		if (player_is_alive(&TPP[i]))
			pos_party_member(&TPP[i],pos[i].x,pos[i].y);
}

static void _PASCAL _NEAR pos_party_in_LR_area()
{
	int i;
	static POS_TYPE pos[]={{2,6},
						   {3,6},
						   {2,7},
						   {3,7},
						   {3,8},
						   {4,8}};

	for (i=0; i<SIZE(pos); i++)
		if (player_is_alive(&TPP[i]))
			pos_party_member(&TPP[i],pos[i].x,pos[i].y);
}

static void _PASCAL _NEAR pos_party_in_X_area()
{
	int i;
	static POS_TYPE pos[]={{3,7},
						   {4,7},
						   {5,7},
						   {3,8},
						   {4,8},
						   {5,8}};

	for (i=0; i<SIZE(pos); i++)
		if (player_is_alive(&TPP[i]))
		{
			if (!IN_DUNGEON)
				draw_cmbt_grass(pos[i].x,pos[i].y);

			pos_party_member(&TPP[i],pos[i].x,pos[i].y);
		}
}

static void _PASCAL _NEAR pos_party_in_corridor_area()
{
	int i;
	static POS_TYPE pos[]={{4,6},
						   {5,6},
						   {3,7},
						   {4,7},
						   {4,8},
						   {5,8}};

	for (i=0; i<SIZE(pos); i++)
		if (player_is_alive(&TPP[i]))
			pos_party_member(&TPP[i],pos[i].x,pos[i].y);
}

static void _PASCAL _NEAR pos_party_in_open_area()
{
	pos_party_in_X_area();
}

void _PASCAL init_cmbt_area(int combat_area)
{
	_setactivepage(1);
	_setvisualpage(0);

	switch(combat_area)
	{
		case CMBT_OPEN_AREA     : init_open_area();     break;
		case CMBT_CORRIDOR_AREA : init_corridor_area(); break;
		case CMBT_LL_AREA       : init_LL_area();       break;
		case CMBT_LR_AREA       : init_LR_area();       break;
		case CMBT_X_AREA        : init_X_area();        break;
	}

	_setactivepage(0);
	_setvisualpage(0);
}

static void _PASCAL _NEAR init_open_area()
{
	int i,j;
	int draw_walls=FALSE;
	static char t[]={0, 		   0,
					 1, 		   0,
					 0, 		   1,
					 0, 		   CMBT_AREA_Y-1,
					 1, 		   CMBT_AREA_Y-1,
					 0, 		   CMBT_AREA_Y-2,
					 CMBT_AREA_X-1,0,
					 CMBT_AREA_X-1,1,
					 CMBT_AREA_X-2,0,
					 CMBT_AREA_X-1,CMBT_AREA_Y-1,
					 CMBT_AREA_X-1,CMBT_AREA_Y-2,
					 CMBT_AREA_X-2,CMBT_AREA_Y-1};

	if (pent_data.current_feature==FOREST		  ||
		pent_data.current_feature==HILLS		  ||
		pent_data.current_feature==MOUNTAINS	  ||
		pent_data.current_feature==HIGH_MOUNTAINS)
		draw_walls=TRUE;

	for (i=0; i<CMBT_AREA_X; i++)
	{
		for (j=0; j<CMBT_AREA_Y; j++)
		{
			cmbt_area[i][j].occ.monster =NULL;
			cmbt_area[i][j].nocc        =IS_EMPTY;

			if (!IN_DUNGEON)
			{
				draw_cmbt_grass(i,j);

				if (i<CMBT_AREA_X)
				{
					if (percent()>ROCK_THRESHOLD && draw_walls)
					{
						cmbt_area[i][j].nocc=IS_WALL;
						draw_cmbt_wall(i,j);
					}
				}
			}
		}
	}

	if (IN_DUNGEON) 				/* Special 'corners' */
	{
		for (i=0; i<SIZE(t); i+=2)
		{
			cmbt_area[t[i]][t[i+1]].nocc=IS_WALL;
			draw_cmbt_wall(t[i],t[i+1]);
		}
	}
}

static void _PASCAL _NEAR init_corridor_area()
{
	int i,j;

	init_open_area();

	for (i=0; i<CMBT_AREA_Y; i++)
	{
		for (j=0; j<3; j++)
		{
			cmbt_area[j][i].nocc			  =IS_WALL;
			cmbt_area[CMBT_AREA_X-j-1][i].nocc=IS_WALL;

			draw_cmbt_wall(j,i);
			draw_cmbt_wall(CMBT_AREA_X-j-1,i);
		}
	}
}

static void _PASCAL _NEAR init_LL_area()
{
	int i,j;

	init_open_area();

	for (i=0; i<CMBT_AREA_X; i++)
	{
		cmbt_area[i][0].nocc =IS_WALL;
		cmbt_area[i][1].nocc =IS_WALL;

		draw_cmbt_wall(i,0);
		draw_cmbt_wall(i,1);
	}

	for (i=2; i<CMBT_AREA_Y; i++)
	{
		cmbt_area[CMBT_AREA_X-1][i].nocc =IS_WALL;
		cmbt_area[CMBT_AREA_X-2][i].nocc =IS_WALL;

		draw_cmbt_wall(CMBT_AREA_X-1,i);
		draw_cmbt_wall(CMBT_AREA_X-2,i);
	}

	for (i=0; i<4; i++)
	{
		for (j=5; j<CMBT_AREA_Y; j++)
		{
			cmbt_area[i][j].nocc =IS_WALL;
			draw_cmbt_wall(i,j);
		}
	}
}

static void _PASCAL _NEAR init_LR_area()
{
	int i,j;

	init_open_area();

	for (i=0; i<CMBT_AREA_X; i++)
	{
		cmbt_area[i][0].nocc =IS_WALL;
		cmbt_area[i][1].nocc =IS_WALL;

		draw_cmbt_wall(i,0);
		draw_cmbt_wall(i,1);
	}

	for (i=2; i<CMBT_AREA_Y; i++)
	{
		cmbt_area[0][i].nocc =IS_WALL;
		cmbt_area[1][i].nocc =IS_WALL;

		draw_cmbt_wall(0,i);
		draw_cmbt_wall(1,i);
	}

	for (i=5; i<9; i++)
	{
		for (j=5; j<CMBT_AREA_Y; j++)
		{
			cmbt_area[i][j].nocc =IS_WALL;
			draw_cmbt_wall(i,j);
		}
	}
}

static void _PASCAL _NEAR init_X_area()
{
	int i,j;

	init_open_area();

	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			cmbt_area[i][j].nocc =IS_WALL;
			draw_cmbt_wall(i,j);

			cmbt_area[CMBT_AREA_Y-i-1][j].nocc =IS_WALL;
			draw_cmbt_wall(CMBT_AREA_Y-i-1,j);


			cmbt_area[i][CMBT_AREA_Y-(j+1)].nocc =IS_WALL;
			draw_cmbt_wall(i,CMBT_AREA_Y-(j+1));

			cmbt_area[CMBT_AREA_X-i-1][CMBT_AREA_Y-(j+1)].nocc =IS_WALL;
			draw_cmbt_wall(CMBT_AREA_X-i-1,CMBT_AREA_Y-(j+1));
		}
	}
}

int _PASCAL determine_combat_area_size()		/* position of walls etc */
{
	int x,y,z;
	int nw,n,ne,w,e,sw,s,se;

	if (!IN_DUNGEON)
		return(CMBT_OPEN_AREA);

	x=the_party.dungeon_x;
	y=the_party.dungeon_y;
	z=the_party.dungeon_level;

	nw=dungeon.map[z][x-1][y-1].feature;
	n =dungeon.map[z][x  ][y-1].feature;
	ne=dungeon.map[z][x+1][y-1].feature;
	w =dungeon.map[z][x-1][y  ].feature;
	e =dungeon.map[z][x+1][y  ].feature;
	sw=dungeon.map[z][x-1][y+1].feature;
	s =dungeon.map[z][x  ][y+1].feature;
	se=dungeon.map[z][x+1][y+1].feature;

	if (!solid(nw) && !solid(n) && !solid(ne) &&
		!solid(w)  && !solid(e) &&
		!solid(sw) && !solid(s) && !solid(se))
		return(CMBT_OPEN_AREA);

	if (!solid(nw) && !solid(ne) && !solid(sw) && !solid(se))
		return(CMBT_X_AREA);

	if (!solid(n) && !solid(s) && !solid(w) && !solid(e))
		return(CMBT_X_AREA);

	if (!solid(n) && !solid(s) && !solid(ne))
		return(CMBT_LR_AREA);

	if (!solid(n) && !solid(s) && !solid(nw))
		return(CMBT_LL_AREA);

	if (!solid(n) && !solid(s) && !solid(sw))
		return(CMBT_LR_AREA);

	if (!solid(n) && !solid(s) && !solid(se))
		return(CMBT_LL_AREA);

	if (!solid(n) && !solid(e))
		return(CMBT_LL_AREA);

	if (!solid(n) && !solid(w))
		return(CMBT_LR_AREA);

	if (!solid(s) && !solid(w))
		return(CMBT_LL_AREA);

	if (!solid(s) && !solid(e))
		return(CMBT_LR_AREA);

	return(CMBT_CORRIDOR_AREA);
}

static int _PASCAL _NEAR solid(int dir)
{
	if (dir==DNG_WALL           ||
		dir==DNG_HEAVY_DOOR     ||
		dir==DNG_LOCKED_DOOR    ||
		dir==DNG_SECRET_DOOR    ||
		dir==DNG_DOOR)
		return(TRUE);
	else
		return(FALSE);
}
