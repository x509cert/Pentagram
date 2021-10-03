#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

static BRIDGES bridges[]={21 ,103,"Crescent River",
						  23 , 97,"Crescent River",
						  45 , 94,"Needle Gulf",
						  46 , 94,"Needle Gulf",
						  47 , 94,"Needle Gulf",
						  64 ,104,"Wolfsway River",
						  64 ,103,"Wolfsway River",
						  101, 89,"Upper Reaches of Wolf Bay",
						  70 , 39,"Lindale River",
						  139,124,"Ring Finger River",
						  143,124,"Middle Finger River",
						  148,125,"Index Finger River",
						  167,136,"Oromos River",
						  177,138,"Keremis River",
						  139,177,"Entrance to Lake Gelswith",
						  126, 36,"River Iceway",
						  143,174,"River Gelswith",
						  155,166,"River Gelswith",
						  159,169,"River Gelness",
						  158,169,"River Gelness"};

void _PASCAL divulge_bridge_info(int x,int y)
{
	char temp[80];
	int i;
	int num=ERR;
	static char *t[]={"old stone","creaky wooden"};

	for (i=0; i<SIZE(bridges); i++)
	{
		if (x==bridges[i].x && y==bridges[i].y)
		{
			num=i;
			break;
		}
	}

	if (num!=ERR)
	{
		sprintf(temp,"A sign on ye %s bridge reads:\n\"Ye %s.\"",
					t[x%(SIZE(t))],
					bridges[x>89?0:1].message);

		SCROLL(1,14,temp);

		general_low_sound();
	}
}
