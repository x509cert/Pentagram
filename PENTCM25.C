#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>

/*
 *
 *	Non Dungeon Place draw Players
 *
 */

void _PASCAL draw_adv_cmbt_image(int class,int x,int y)
{
	switch(class)
	{
		case WARRIOR        :   _putimage(x,y,im_warrior_msk,_GAND);
								_putimage(x,y,im_warrior,_GOR);
								break;

		case PRIEST         :   _putimage(x,y,im_priest_msk,_GAND);
								_putimage(x,y,im_priest,_GOR);
								break;

		case RANGER         :   _putimage(x,y,im_ranger_msk,_GAND);
								_putimage(x,y,im_ranger,_GOR);
								break;

		case DRUID          :   _putimage(x,y,im_druid_msk,_GAND);
								_putimage(x,y,im_druid,_GOR);
								break;

		case THIEF          :   _putimage(x,y,im_thief_msk,_GAND);
								_putimage(x,y,im_thief,_GOR);
								break;

		case WIZARD         :   _putimage(x,y,im_wizard_msk,_GAND);
								_putimage(x,y,im_wizard,_GOR);
								break;

		case BARD           :   _putimage(x,y,im_bard_msk,_GAND);
								_putimage(x,y,im_bard,_GOR);
								break;

		case MONK           :   _putimage(x,y,im_monk_msk,_GAND);
								_putimage(x,y,im_monk,_GOR);
								break;

		case ILLUSIONIST    :   _putimage(x,y,im_illusionist_msk,_GAND);
								_putimage(x,y,im_illusionist,_GOR);
								break;

		case HUNTER         :   _putimage(x,y,im_hunter_msk,_GAND);
								_putimage(x,y,im_hunter,_GOR);
								break;

		case DUELIST        :   _putimage(x,y,im_duelist_msk,_GAND);
								_putimage(x,y,im_duelist,_GOR);
								break;

		case CRUSADER       :   _putimage(x,y,im_crusader_msk,_GAND);
								_putimage(x,y,im_crusader,_GOR);
								break;
	}
}
