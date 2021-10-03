#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bscreens.h>
#include <bkeybrd.h>
#include <time.h>
#include <dos.h>
#include <io.h>
#include "sprite.h"
#include "mmalloc.h"

void main(int argc,char **argv)
{
	int fin=FALSE;
	int quick_load=FALSE;
	int first=TRUE;

	Minit();

	if (argc!=1)
	{
		strupr(argv[1]);

		switch(*argv[1])
		{
			case 'C' :  quick_load=TRUE;
						load_font(CELTIC);

						break;

			case 'G' :  quick_load=TRUE;
						load_font(GOTHIC);

						break;

			case 'V' :	_setvideomode(_TEXTC80);

						printf("%s v%s%s(c) %s 1989-%s\nCreated and written by %s, %s\n",
							TITLE,
							VERSION,
#ifdef DEV
							" [Development] ",
#else
							" ",
#endif
							COMPANY,

							__DATE__+7,
							AUTHOR,
							__DATE__);

						exit(10);

						break;

			default  :  break;
		}
	}

	kbflush();

	delay(0);       /* Calibrate delay routine */

	srand((unsigned)time(NULL));

	init_hardware();

	setup_global_data();

	no_monsters=(access("MH.MH",0)==0)?TRUE:FALSE;

	make_map_heap();
	load_startup_data();

	night_flagged=FALSE;
	game_loaded=FALSE;

	situation_status=OFF;
	fast_mouse=OFF;

	generate_the_weather();

	draw_main_screen(quick_load);

	cls();
	cls_scroll();

	init_mouse();

	draw_combat_logo();
	build_boss_screen();
	load_finish_image();

	select_win.x1=1;
	select_win.y1=3;
	select_win.x2=40;
	select_win.y2=select_win.y1+MAX_ON_DISC+6;
	select_win.back=0;
	select_win.border=7;

	please_wait_win.x1=13;
	please_wait_win.y1=9;
	please_wait_win.x2=28;
	please_wait_win.y2=please_wait_win.y1+3;
	please_wait_win.back=4;
	please_wait_win.border=14;

	if (!quick_load)
		select_font();

	make_gplease_wait();

	load_global_data();
	nullify_party();
	load_party_data_from_disc();
	load_party_from_disc();

	kill_gplease_wait();

	if (P_NUM!=ERR && pent_data.current_feature!=CITY)
	{
		game_loaded=TRUE;
		first=FALSE;

		adventure();
	}

	while (!fin)
	{
		kbflush();

		if (first)
		{
			short_prompt_sound();
			first=FALSE;
		}

		switch(wolfburg_menu())
		{
			case 1 : bank();
					 break;

			case 2 : cathedral();
					 break;

			case 3 : inn("Pentagram");
					 break;

			case 4 : market();
					 break;

			case 5 : hall();
					 break;

			case 6 : training_grounds();
					 break;

			case 7 : adventure();
					 break;

			case 8 : front_options();
					 break;

			default: fin=TRUE;
					 break;
		}

		if (fin)
			fin=shut_program_down(TRUE);
	}
}

void _PASCAL default_cursor()
{
	scpgcur(0,12,13,CUR_ADJUST);
}

int _PASCAL shut_program_down(int ask)
{
	int res;
	GWINDOW win;
	static int boundary[]={90 ,106,125,118,
						   170,106,205,118,
						   -1,-1,-1,-1};

	if (in_exit)
		return(FALSE);

	in_exit=TRUE;

	if (ask)
	{
		win.x1=7;
		win.y1=4;
		win.x2=32;
		win.y2=17;
		win.back=0;
		win.border=8;

		make_gwindow(&win);

		generic_pic_draw(win.x1*8+4,win.y1*8,"QUIKQUIT");

		click_box(90, 106,B_YES);
		click_box(170,106,B_NO);

		short_prompt_sound();

		res=(mouse_in_range(boundary,"YN","YQ")!=0?FALSE:TRUE);

		kill_gwindow(&win);
	}
	else
		res=TRUE;

#ifndef DEV
	if (res==TRUE && !quick_exit && pent_data.current_feature!=CITY)
		if (ask)
			if (gget_yn("Save Adventure First?"))
				save_game(FALSE);
#endif

	if (res)
	{
		close_program();

		_setvideomode(_TEXTC80);

		default_cursor();

		exit(0);
	}

	in_exit=FALSE;

	return(FALSE);
}

void _PASCAL close_program()
{
	kill_map_heap();

	if (!quick_exit)
	{
		cls_scroll();
		generic_pic_draw(33,133,"CHAPTER");
	}

	clear_adv_menu_heap();

#ifndef DEV

	general_low_sound();

	if (!quick_exit)
		pause(2);

#endif
}

void _PASCAL init_hardware()
{
	struct videoconfig vc;

	if (!_setvideomode(_MRES16COLOR))
		panic("No EGA/VGA Adaptor Found!");

	_getvideoconfig(&vc);

	if (vc.memory<256)
		panic("Pentagram requires 256k of Video RAM!");
}

void _PASCAL _NEAR make_map_heap()
{
	size_t size=MAP_SIZE*(MAP_SIZE/2);

	if ((MAP=(unsigned char _FAR *)Mmalloc(size))==NULL)
		panic_RAM("MAP Image");
}

void _PASCAL _NEAR kill_map_heap()
{
	Mfree(MAP);
}
