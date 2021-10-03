#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <io.h>
#include "mmalloc.h"

void _PASCAL load_startup_data()
{
	load_map();
	load_map_icons();

	load_adv_images();
	load_adv_mask_images();

	load_day_night_icons();

	load_adventure_menu();
}

void _PASCAL load_adv_images()
{
	load_one_adv_image(im_bard, 	   "bard");
	load_one_adv_image(im_crusader,    "crusader");
	load_one_adv_image(im_druid,	   "druid");
	load_one_adv_image(im_duelist,	   "duelist");
	load_one_adv_image(im_hunter,	   "hunter");
	load_one_adv_image(im_illusionist, "illusion");
	load_one_adv_image(im_monk, 	   "monk");
	load_one_adv_image(im_priest,	   "priest");
	load_one_adv_image(im_ranger,	   "ranger");
	load_one_adv_image(im_thief,	   "thief");
	load_one_adv_image(im_warrior,	   "warrior");
	load_one_adv_image(im_wizard,	   "wizard");
}

static void _PASCAL _NEAR load_one_adv_image(char _FAR icon[MONSTER_IMAGE_SIZE],char *fname)
{
	FILE *fptr;
	char temp[80];

	sprintf(temp,"%s%s.pic",PROFESSION_DIRECTORY,fname);

	fptr=fopen(temp,"rb");

	if (fptr==(FILE *)NULL)
		panic_FILE(temp);

	fread((void *)icon,MONSTER_IMAGE_SIZE,1,fptr);

	fclose(fptr);
}

void _PASCAL load_adv_mask_images()
{
	load_one_adv_mask_image(im_bard_msk,		"bard");
	load_one_adv_mask_image(im_crusader_msk,	"crusader");
	load_one_adv_mask_image(im_druid_msk,		"druid");
	load_one_adv_mask_image(im_duelist_msk, 	"duelist");
	load_one_adv_mask_image(im_hunter_msk,		"hunter");
	load_one_adv_mask_image(im_illusionist_msk, "illusion");
	load_one_adv_mask_image(im_monk_msk,		"monk");
	load_one_adv_mask_image(im_priest_msk,		"priest");
	load_one_adv_mask_image(im_ranger_msk,		"ranger");
	load_one_adv_mask_image(im_thief_msk,		"thief");
	load_one_adv_mask_image(im_warrior_msk, 	"warrior");
	load_one_adv_mask_image(im_wizard_msk,		"wizard");
}

static void _PASCAL _NEAR load_one_adv_mask_image(char _FAR icon[MONSTER_IMAGE_SIZE],char *fname)
{
	FILE *fptr;
	char temp[80];

	sprintf(temp,"%s%s.msk",PROFESSION_DIRECTORY,fname);

	fptr=fopen(temp,"rb");

	if (fptr==(FILE *)NULL)
		panic_FILE(temp);

	fread((void *)icon,MONSTER_IMAGE_SIZE,1,fptr);

	fclose(fptr);
}

void _PASCAL load_map()
{
	char temp[80];
	FILE *fptr;
	size_t size=MAP_SIZE*(MAP_SIZE/2);

	sprintf(temp,"%s%s",PIC_DIRECTORY,MAP_FILE);

	fptr=fopen(temp,"rb");

	if (fptr==(FILE *)NULL)
		panic_FILE(temp);

	fread(MAP,size,1,fptr);

	fclose(fptr);
}

void _PASCAL load_map_icons()
{
	load_one_map_icon(map_icon_hills,		"hills.icn");
	load_one_map_icon(map_icon_forest,		"forest.icn");
	load_one_map_icon(map_icon_grass,		"grass.icn");
	load_one_map_icon(map_icon_highmts, 	"highmts.icn");
	load_one_map_icon(map_icon_marsh,		"marsh.icn");
	load_one_map_icon(map_icon_mts, 		"mts.icn");
	load_one_map_icon(map_icon_sea, 		"sea.icn");
	load_one_map_icon(map_icon_sea2,		"sea2.icn");
	load_one_map_icon(map_icon_town,		"town.icn");
	load_one_map_icon(map_icon_water,		"water.icn");
	load_one_map_icon(map_icon_water2,		"water2.icn");
	load_one_map_icon(map_icon_village, 	"village.icn");
	load_one_map_icon(map_icon_cross,		"cross.icn");
	load_one_map_icon(map_icon_party,		"party.icn");
	load_one_map_icon(map_icon_party2,		"party2.icn");
	load_one_map_icon(map_icon_party_mask,	"partymsk.icn");
	load_one_map_icon(map_icon_dungeon, 	"dungeon.icn");
	load_one_map_icon(map_icon_ruin,		"ruin.icn");
	load_one_map_icon(map_icon_br_lr,		"br_lr.icn");
	load_one_map_icon(map_icon_br_ud,		"br_ud.icn");
	load_one_map_icon(map_icon_signpost,	"signpost.icn");
	load_one_map_icon(map_icon_road01,		"rd01.icn");
	load_one_map_icon(map_icon_road02,		"rd02.icn");
	load_one_map_icon(map_icon_road03,		"rd03.icn");
	load_one_map_icon(map_icon_road04,		"rd04.icn");
	load_one_map_icon(map_icon_road05,		"rd05.icn");
	load_one_map_icon(map_icon_road06,		"rd06.icn");
	load_one_map_icon(map_icon_road07,		"rd07.icn");
	load_one_map_icon(map_icon_road08,		"rd08.icn");
	load_one_map_icon(map_icon_road09,		"rd09.icn");
	load_one_map_icon(map_icon_road10,		"rd10.icn");
	load_one_map_icon(map_icon_road11,		"rd11.icn");
}

static void _PASCAL _NEAR load_one_map_icon(char _FAR icon[MAP_ICON_SIZE],char *fname)
{
	FILE *fptr;
	char temp[80];

	sprintf(temp,"%s%s",MAP_ICON_DIRECTORY,fname);

	fptr=fopen(temp,"rb");

	if (fptr==(FILE *)NULL)
		panic_FILE(temp);

	fread((void *)icon,MAP_ICON_SIZE,1,fptr);

	fclose(fptr);
}

void _PASCAL load_adventure_menu()
{
	long size;
	FILE *fptr;
	char temp[80];

	sprintf(temp,"%sADVMENU.PIC",PIC_DIRECTORY);

	fptr=fopen(temp,"rb");

	if (fptr==NULL)
		panic_FILE(temp);

	size=filelength(fileno(fptr));

	adv_menu=(char _FAR *)Mmalloc((size_t)size);

	if (adv_menu==(char _FAR *)NULL)
		panic_RAM("ADVMENU.PIC");

	fread((void *)adv_menu,(size_t)size,1,fptr);

	fclose(fptr);

	all_menu_bkgrnd=(char _FAR *)Mmalloc((size_t)(size+50L));

	if (all_menu_bkgrnd==(char _FAR *)NULL)
		panic_RAM("AdvMenu Image");
}

void _PASCAL load_day_night_icons()
{
	load_one_day_night_icon(day_nite_icon_1, "daynte1.icn");
	load_one_day_night_icon(day_nite_icon_2, "daynte2.icn");
	load_one_day_night_icon(day_nite_icon_4, "daynte4.icn");
	load_one_day_night_icon(day_nite_icon_5, "daynte5.icn");
	load_one_day_night_icon(day_nite_icon_6, "daynte6.icn");
	load_one_day_night_icon(day_nite_icon_7, "daynte7.icn");
	load_one_day_night_icon(day_nite_icon_11,"daynte11.icn");
	load_one_day_night_icon(day_nite_icon_12,"daynte12.icn");
	load_one_day_night_icon(day_nite_icon_13,"daynte13.icn");
	load_one_day_night_icon(day_nite_icon_14,"daynte14.icn");
	load_one_day_night_icon(day_nite_icon_15,"daynte15.icn");
	load_one_day_night_icon(day_nite_icon_16,"daynte16.icn");
	load_one_day_night_icon(day_nite_icon_17,"daynte17.icn");
}

void _PASCAL load_one_day_night_icon(char _FAR icon[DAY_NITE_ICON_SIZE],char *fname)
{
	FILE *fptr;
	char temp[80];

	sprintf(temp,"%s%s",DAY_NIGHT_DIRECTORY,fname);

	fptr=fopen(temp,"rb");

	if (fptr==(FILE *)NULL)
		panic_FILE(temp);

	fread((void *)icon,DAY_NITE_ICON_SIZE,1,fptr);

	fclose(fptr);
}

void _PASCAL select_font()
{
	static int boundary[]={115,68,203,75,
						   115,85,203,92,
						   -1,-1,-1,-1};


	generic_pic_draw(69,31,"FONTS");

	switch (mouse_in_range(boundary,"GC",""))
	{
		case 0 :load_font(GOTHIC);
				break;

		default:load_font(CELTIC);
				break;
	}

	cls();
}

void _PASCAL load_font(int fnt)
{
	FILE *fptr;

	if ((fptr=fopen(fnt==CELTIC?CELTIC_FILE:GOTHIC_FILE,"rb"))==NULL)
		panic_FILE("Font file");

	fread(FONT,FONT_RAM_SIZE*sizeof(int),1,fptr);

	fclose(fptr);
}
