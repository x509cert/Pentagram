#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

#define xo1 	5
#define xo2 	115
#define xo3 	228
#define yo1 	93
#define yo2 	118
#define yo3 	143
#define yo4 	168
#define xoffset 23

void _PASCAL show_all_images(int sex)
{
	static struct POS  {
							int  x,y;
							char *name;
							char *hilite;
							int  hilite_off;

					   } pos[]={{xo1,yo1,"BARD",        "B",0},
								{xo1,yo2,"CRUSADER",    "C",0},
								{xo1,yo3,"DRUID",       "D",0},
								{xo1,yo4,"DUELIST",     "U",8},

								{xo2,yo1,"H",			"H",0},
								{xo2,yo2,"ILLUSIONIST", "L",8},
								{xo2,yo3,"MONK",        "M",0},
								{xo2,yo4,"P",           "P",0},

								{xo3,yo1,"RANGER",      "R",0},
								{xo3,yo2,"THIEF",       "T",0},
								{xo3,yo3,"WARRIOR",     "W",0},
								{xo3,yo4,"W",           "I",8}};
	int i;

	draw_adv_image(BARD,        xo1,yo1);
	draw_adv_image(CRUSADER,    xo1,yo2);
	draw_adv_image(DRUID,       xo1,yo3);
	draw_adv_image(DUELIST,     xo1,yo4);

	draw_adv_image(HUNTER,      xo2,yo1);
	draw_adv_image(ILLUSIONIST, xo2,yo2);
	draw_adv_image(MONK,        xo2,yo3);
	draw_adv_image(PRIEST,      xo2,yo4);

	draw_adv_image(RANGER,      xo3,yo1);
	draw_adv_image(THIEF,       xo3,yo2);
	draw_adv_image(WARRIOR,     xo3,yo3);
	draw_adv_image(WIZARD,      xo3,yo4);

	if (sex==SX_FEMALE)
	{
		pos[11].name="WITCH";
		pos[7].name ="PRIESTESS";
		pos[4].name ="HUNTRESS";
	}
	else
	{
		pos[11].name="WIZARD";
		pos[7].name ="PRIEST";
		pos[4].name ="HUNTER";
	}

	for (i=0; i<SIZE(pos); i++)
	{
		print_text(pos[i].name,
				   pos[i].x+xoffset,
				   pos[i].y+5,
				   NORMAL_HEIGHT,
				   5);

		print_text(pos[i].hilite,
				   pos[i].x+xoffset+pos[i].hilite_off,
				   pos[i].y+5,
				   NORMAL_HEIGHT,
				   13);
	}
}

void _PASCAL draw_adv_image(int class,int x,int y)
{
	switch(class)
	{
		case WARRIOR		:	_putimage(x,y,im_warrior,_GPSET);
								break;

		case PRIEST 		:	_putimage(x,y,im_priest,_GPSET);
								break;

		case RANGER 		:	_putimage(x,y,im_ranger,_GPSET);
								break;

		case DRUID			:	_putimage(x,y,im_druid,_GPSET);
								break;

		case THIEF			:	_putimage(x,y,im_thief,_GPSET);
								break;

		case WIZARD 		:	_putimage(x,y,im_wizard,_GPSET);
								break;

		case BARD			:	_putimage(x,y,im_bard,_GPSET);
								break;

		case MONK			:	_putimage(x,y,im_monk,_GPSET);
								break;

		case ILLUSIONIST	:	_putimage(x,y,im_illusionist,_GPSET);
								break;

		case HUNTER 		:	_putimage(x,y,im_hunter,_GPSET);
								break;

		case DUELIST		:	_putimage(x,y,im_duelist,_GPSET);
								break;

		case CRUSADER		:	_putimage(x,y,im_crusader,_GPSET);
								break;
	}
}
