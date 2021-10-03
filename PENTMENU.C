#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

int _PASCAL wolfburg_menu()
{
	static  char *opt[]={"Bank",
						 "Cathedral",
						 "Inn",
						 "Market",
						 "Gaming Hall",
						 "Training Grounds",
						 "Go Adventuring",
						 "Saga Options",
						 "Quit Pentagram"};

	char *opt_let="BCIMGTASQ";

	static int boundary[]={88,32,212,38,
						   88,40,212,46,
						   88,48,212,54,
						   88,56,212,62,
						   88,64,212,70,
						   88,72,212,78,
						   88,80,212,86,
						   88,88,212,94,
						   88,96,212,102,
						   -1,-1,-1,-1};

	char *ti="CITY OF WOLFBURG";
	int fin=FALSE;

	GWINDOW win;

	cls();
	cls_scroll();

	print_large_title(ti);

	win.x1=11;
	win.x2=win.x1+18;
	win.y1=4;
	win.y2=15;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	print_menu_options(opt,
					   SIZE(opt),
					   opt_let,
					   win.x1+1,
					   win.y1+1,
					   5,
					   13);

	fin=mouse_in_range(boundary,opt_let,"");

	kill_gwindow(&win);

	return(fin+1);
}
