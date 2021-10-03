#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL celtic_cross()
{
	if (enter_a_celtic_cross())
		effects_at_celtic_cross();
}

int _PASCAL enter_a_celtic_cross()
{
	GWINDOW win;
	int res;
	char *l1="Doth ye approach";
	char *l2="ye Celtic Cross?";
	static int boundary[]={120,65,155,77,
						   175,65,210,77,
						   -1,-1,-1,-1};

	win.x1=5;
	win.x2=33;
	win.y1=5;
	win.y2=12;
	win.back=0;
	win.border=14;

	make_gwindow(&win);

	draw_cross_image(43,47);

	_settextcolor(6);
	_settextposition(6,14);
	_outtext(l1);

	_settextposition(7,14);
	_outtext(l2);

	click_box(120,65,B_YES);
	click_box(175,65,B_NO);

	switch(mouse_in_range(boundary,"YN",""))
	{
		case 0 : res=TRUE; break;
		default: res=FALSE; break;
	}

	kill_gwindow(&win);

	return(res);
}

void _PASCAL effects_at_celtic_cross()
{
	int i;
	int total_div;
	int curr_div;
	int affected;
	int a_lot;
	char temp[60];

	SCROLL(1,14,"A mystic aura of well being envelops thy party!");
	good_sound();

	for (i=0; i<=P_NUM; i++)
	{
		total_div= TPP[i].divine_points;
		curr_div = TPP[i].current_divine_points;

		affected=FALSE;
		a_lot=FALSE;

		if (player_is_alive(&TPP[i]))
		{
			switch(TPP[i].nclass)
			{
				case DRUID  :   if (curr_div<total_div)
								{
									if (curr_div<=total_div/2)
										a_lot=TRUE;

									TPP[i].current_divine_points=total_div;
									affected=TRUE;
								}

								break;

				case RANGER :	if (curr_div<total_div && ((unsigned)rand()%20<=TPP[i].luck))
								{

									if (curr_div<=total_div/2)
										a_lot=TRUE;

									TPP[i].current_divine_points=total_div;
									affected=TRUE;
								}

								break;

				default     :   break;
			}

			if (affected)
			{
				sprintf(temp,"%s%s magic increases%s",
							  TPP[i].name,
							  end_s(TPP[i].name),
							  a_lot?" considerably!":"!");

				GX(temp,GOOD);
			}
		}
	}
}

void _PASCAL draw_cross_image(int x,int y)
{
	generic_pic_draw(x,y,"CCIMAGE");
}
