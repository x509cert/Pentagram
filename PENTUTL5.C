#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bkeys.h>
#include <bkeybrd.h>
#include <bstrings.h>
#include "mmalloc.h"

void _PASCAL panic(char *mess)
{
	static char *box[]={"ษออออออออป",
						"บ        บ",
						"บ        บ",
						"บ        บ",
						"บ        บ",
						"ศออออออออผ"};

	static char *exc[]={"ÜÜ",
						"ÛÛ",
						"ÜÜ"};

	static char *oopss[]={"An error has occured in Pentagram!",
						  "Please get in touch with Odin Software",
						  "Development if this error persists and",
						  "quote the error message below:"};

	int  i;
	int  box_col=0xE;
	int  exc_col=0x1F;
	int  mess_col1=0x7;
	int  mess_col2=0xF;
	long bk=0x4L;

	if (_setvideomode(_TEXTC80)==0)
	{
		_setvideomode(_TEXTBW80);

		box_col=7;
		exc_col=0x1f;
		bk=0x0L;
	}

	_setbkcolor(bk);
	_settextcolor(box_col);

	for (i=0; i<SIZE(box); i++)
	{
		_settextposition(i+1,1);
		_outtext(box[i]);
	}

	_settextcolor(exc_col);

	for (i=0; i<SIZE(exc); i++)
	{
		_settextposition(i+2,5);
		_outtext(exc[i]);
	}

	_setbkcolor(0L);
	_settextcolor(mess_col1);

	for (i=0; i<SIZE(oopss); i++)
	{
		_settextposition(i+2,40-strlen_half(oopss[i]));
		_outtext(oopss[i]);
	}

	_settextcolor(mess_col2);
	_setbkcolor(4L);

	_settextposition(8,40-strlen_half(mess));
	_outtext(mess);

	_settextposition(10,1);

	solemn_sound();

	default_cursor();

	exit(1);
}

void _PASCAL panic_RAM(char *mess)
{
	char temp[80];

	sprintf(temp,"Out of RAM for %s",mess);

	panic(temp);
}

void _PASCAL panic_FILE(char *mess)
{
	char temp[80];

	sprintf(temp,"Can't Open/Read/Write %s",mess);

	panic(temp);
}

void _PASCAL make_gwindow(GWINDOW *w)
{
	int x1,y1,x2,y2;
	char col;

#define OFFS 2

	x1=(w->x1-1)<<3;
	x2=(w->x2-1)<<3;
	y1=(w->y1-1)<<3;
	y2=(w->y2-1)<<3;

	col=(char)w->back;

	w->object=(char _FAR *)Mmalloc((size_t)_imagesize(x1,y1,x2,y2));

	if (w->object==(char _FAR *)NULL)
		panic_RAM("Dynamic Window");

	_getimage(x1,y1,x2,y2,w->object);

	if (w->border)
	{
		_setcolor(w->back);
		_rectangle(_GFILLINTERIOR,x1+1,y1+1,x2-1,y2-1);

		_setcolor(w->border);
		_rectangle(_GBORDER,x1+OFFS,y1,x2-OFFS,y2);
		_rectangle(_GBORDER,x1,y1+OFFS,x2,y2-OFFS);

		FFPLOT(x1+OFFS,y1+OFFS+1,col);      /* Erase line crosses */
		FFPLOT(x1+OFFS,y1+OFFS-1,col);

		FFPLOT(x1+OFFS-1,y2-OFFS,col);
		FFPLOT(x1+OFFS+1,y2-OFFS,col);

		FFPLOT(x2-OFFS-1,y1+OFFS,col);
		FFPLOT(x2-OFFS+1,y1+OFFS,col);

		FFPLOT(x2-OFFS,y2-OFFS-1,col);
		FFPLOT(x2-OFFS,y2-OFFS+1,col);
	}

#undef OFFS

}

void _PASCAL kill_gwindow(GWINDOW *w)
{
	_putimage((w->x1-1)*8,(w->y1-1)*8,w->object,_GPSET);

	Mfree((void *)w->object);
}

void _PASCAL cls()
{
	short col=_getcolor();

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,2*8,3*8,38*8,14*8);
	_rectangle(_GFILLINTERIOR,0,7*8,319,14*8);

	_setcolor(col);
}

void _PASCAL cls_scroll()
{
	_setcolor(6);

	_rectangle(_GFILLINTERIOR,8,127,304,189);
}

void _PASCAL scroll_scroll()
{
	Fscroll_scroll();
}

void _PASCAL gexclaim(char *text,int type)
{
	GWINDOW win;
	char line1[80];
	char line2[80];
	int longest;
	int two_needed=FALSE;
	int i;
	static int boundary[]={137,68,172,80,
						   -1,-1,-1,-1};

	memset((void *)line1,0,sizeof(line1));
	memset((void *)line2,0,sizeof(line2));

	if (strlen(text)>35)
	{
		i=strlen_half(text);

		while (!isspace(text[i]))
			--i;

		memcpy((void *)line1,(void *)text,i);
		strcpy(line2,&text[i+1]);

		longest=max(strlen(line1),strlen(line2));

		win.x1=19-longest/2;
		win.x2=22+longest/2;

		two_needed=TRUE;
	}
	else
	if (strlen(text)<10)
	{
		win.x1=15;
		win.x2=25;

		strcpy(line1,text);

	}
	else
	{
		win.x1=19-strlen_half(text);
		win.x2=22+strlen_half(text);

		strcpy(line1,text);
	}

	win.y1=two_needed?5:6;
	win.y2=12;
	win.border=14;
	win.back=0;

	make_gwindow(&win);

	_settextposition(win.y1+1,20-strlen_half(line1));
	_settextcolor(6);
	_outtext(line1);

	if (two_needed)
	{
		_settextposition(win.y1+2,20-strlen_half(line2));
		_outtext(line2);
	}

	click_box(137,68,B_OK);

	switch(type)
	{
		case BAD        : bad_sound();           break;
		case GOOD		: good_sound(); 		 break;
		case DEATH      : death_sound();         break;
		case SOLEMN     : solemn_sound();        break;
		case SPELL      : spell_sound();         break;
		case NEW_LEVEL	: advance_level_sound(); break;
		case VICTORY	: victory_sound();		 break;
		case PRAY		: pray_sound(); 		 break;
		case GX_NONE    :                        break;
	}

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);
}

int _PASCAL gget_yn(char *text)
{
	GWINDOW win;
	int result;
	static int boundary[]={100,60,135,72,
						   175,60,250,72,
						   -1,-1,-1,-1};

	if (strlen(text)<10)
	{
		win.x1=15;
		win.x2=25;
	}
	else
	{
		win.x1=19-strlen_half(text);
		win.x2=22+strlen_half(text);
	}

	win.y1=5;
	win.y2=11;
	win.border=5;
	win.back=0;

	make_gwindow(&win);

	_settextposition(win.y1+1,win.x1+1);
	_settextcolor(4);
	_outtext(text);

	click_box(100,60,B_YES);
	click_box(175,60,B_NO);

	switch(mouse_in_range(boundary,"YN","YQ"))
	{
		case 0 : result=YES; break;
		default: result=NO ; break;
	}


	kill_gwindow(&win);

	return(result);
}

char *gquery(int x,int y,int len,int col,int type,char *init)
{
	char data[80];
	static char temp[80];
	int fin=FALSE;
	int i;
	int ch,code;
	int current_len=strlen(init);
	int cursor_col=(col>=7?col-8:col+8);

	type=(char)toupper((int)type);

	memset((void *)data,0, sizeof(data));
	strcpy(data,init);

	_settextcolor(col);
	_settextposition(y,x);
	_outtext(data);

	while (!fin)
	{
		_settextcolor(cursor_col);
		_settextposition(y,x+current_len);
		_outtext("\xFE");

		ch=kbgetkey(&code);

		if (code==KB_S_A_B && ch==KB_C_A_B)
		{
			oops_here_comes_the_boss();
		}
		else
		if (code)
		{
			switch(ch)
			{
				case '\b'   :   if (current_len)
									data[--current_len]='\0';

								break;

				case 13     :   fin=TRUE;
								break;

				default     :   if (((type=='N' && isdigit(ch))  ||
									 (type=='A' && (isalnum(ch)  || isspace(ch)))) &&
									  current_len<len)
										if (!(isspace(ch) && current_len==0))
											data[current_len++]=(char)ch;


								break;
			}
		}

		memset((void *)temp,0,sizeof(temp));
		memset((void *)temp,32,len);
		memcpy((void *)temp,(void *)data,current_len);

		temp[0]=(char)toupper((int)temp[0]);

		for (i=1; i<(int)strlen(temp); i++)
			if (isspace((int)temp[i-1]) && isprint((int)temp[i]))
				temp[i]=(char)toupper((int)temp[i]);

		_settextcolor(col);
		_settextposition(y,x);

		_outtext(temp);
		_outtext(" ");
	}

	stpcvt(temp,RTWHITE);

	return(temp);
}

void _PASCAL _NEAR shake_side()
{
	EGA_origin(rand()%8,0,40);
	EGA_origin(0,0,40);
}

void _PASCAL _NEAR shake_up()
{
	EGA_origin(0,rand()%8,40);
	EGA_origin(0,0,40);
}

void _PASCAL _NEAR shake_diag()
{
	EGA_origin(rand()%8,rand()%8,40);
	EGA_origin(0,0,40);
}

void _PASCAL shake_screen()
{
	int i;

	for (i=0; i<5; i++)
	{
		switch(rand()%3)
		{
			case 0 : shake_up();   break;
			case 1 : shake_diag(); break;
			default: shake_side(); break;
		}
	}
}

int _PASCAL percent()	  /* 0-99 */
{
	return((rand()%100));
}

#ifdef DEV

void _PASCAL DEBUG_func(char *where,int line_num)
{
	char temp[80];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath(where,drive,dir,fname,ext);

	sprintf(temp,"%s%s (%d). Abort?",fname,ext,line_num);

	if (gget_yn(temp))
		exit(99);
}

#endif

int _PASCAL strlen_half(char *string)
{
	return(strlen(string)/2);
}

int _PASCAL plus_or_minus_one()
{
	int n1=rand();
	int n2=rand();

	return(sgn(n1-n2));
}

char *stristr(char *big,char *little)
{
	static char tbig[100];
	char tlittle[30];
	char *ad;

	strcpy(tbig,big);
	strcpy(tlittle,little);

	strupr(tbig);
	strupr(tlittle);

	ad=strstr(tbig,tlittle);

	return((ad==NULL)?NULL:big+(ad-tbig));
}
