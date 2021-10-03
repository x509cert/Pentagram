#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <dos.h>
#include <ctype.h>
#include "bkeybrd.h"
#include "bkeys.h"
#include "sprite.h"

static char  _FAR screen_image[100];
static int	 old_mouse_x,old_mouse_y;

extern int	 CMOUSEL(int *, int *, int *, int *);

static int  mouse_pointer[][9]={        /* New Mouse Pointer */
								{0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x2,0x2},
								{0x0,0xF,0xF,0xF,0xF,0xF,0x0,0x2,0x2},
								{0x0,0x8,0x7,0x7,0x7,0x7,0x0,0x2,0x2},
								{0x0,0x8,0x7,0x7,0x7,0x0,0x2,0x2,0x2},
								{0x0,0x8,0x7,0x8,0x7,0xF,0x0,0x2,0x2},
								{0x0,0x8,0x8,0x0,0x8,0x7,0xF,0x0,0x2},
								{0x2,0x0,0x0,0x2,0x0,0x8,0x7,0xF,0x0},
								{0x2,0x2,0x2,0x2,0x2,0x0,0x8,0x7,0x0},
								{0x2,0x2,0x2,0x2,0x2,0x2,0x0,0x0,0x2},
							   };

void _PASCAL init_mouse()
{
	mouse_reset();

	if (mouse_installed)
	{
		mouse_off();

		mouse_horiz_range(0,640-(9*2));
		mouse_vert_range(0,200-9);

		mouse_x=160;
		mouse_y=80;
	}
}

void _PASCAL mouse_reset()
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    long address;
	unsigned char first_byte;
	int fnum=0,a2,a3,a4;

	mouse_installed=FALSE;

    inregs.x.ax = 0x3533;
    intdosx ( &inregs, &outregs, &segregs );
    
    address = (((long) segregs.es) << 16) + (long) outregs.x.bx;
	first_byte = (unsigned char) * (long _FAR *) address;

	if ((address == 0) || (first_byte == 0xcf))
	{
		mouse_installed=FALSE;
	}
	else
	{
		mouse(&fnum, &a2, &a3, &a4);
		mouse_installed=TRUE;
	}
}

void _PASCAL mouse_mickey_set(int hm, int vm)
{
	int fnum=15,a2,a3,a4;

	a3=hm;
	a4=vm;

	mouse(&fnum,&a2,&a3,&a4);
}

void _PASCAL mouse_mickey_restore()
{
	mouse_mickey_set(8,16);

	mouse_x=old_mouse_x;
	mouse_y=old_mouse_y;
}

void _PASCAL mouse_set_combat_move_mickey()
{
	mouse_mickey_set(210,210);

	mouse_readxy(&old_mouse_x,&old_mouse_y);
}

void _PASCAL mouse_horiz_range(int left,int right)
{
	int fnum=7,a2,a3,a4;

	a3=left;
	a4=right;

	if (mouse_installed)
		mouse(&fnum,&a2,&a3,&a4);
}

void _PASCAL mouse_vert_range(int top,int bottom)
{
	int fnum=8,a2,a3,a4;

	a3=top;
	a4=bottom;

	if (mouse_installed)
		mouse(&fnum,&a2,&a3,&a4);
}

void _PASCAL mouse_off()
{
	int fnum=2;

	if (mouse_installed)
		mouse(&fnum, &fnum, &fnum, &fnum);
}

int _PASCAL mouse_button_r()
{
	int fnum=3, a2, a3, a4;

	if (mouse_installed)
		mouse(&fnum, &a2, &a3, &a4);

	return(mouse_installed?a2&2:0);
}

int _PASCAL mouse_button_l()
{
	int fnum=3, a2, a3, a4;

	if (mouse_installed)
		mouse(&fnum, &a2, &a3, &a4);

	return(mouse_installed?a2&1:0);
}

void _PASCAL mouse_gotoxy(int x,int y)
{
	int fnum=4,a2,a3,a4;

	if (mouse_installed)
	{
		a3=x*2;
		a4=y;

		mouse(&fnum,&a2,&a3,&a4);
	}
}

void _PASCAL mouse_readxy(int *x,int *y)
{
	int fnum=3,a2,a3,a4;

#ifdef DEV
	char temp[12];
	KEYSTATUS kstat;
#endif

	if (mouse_installed)
	{
		mouse(&fnum,&a2,&a3,&a4);
		*x=a3/2;
		*y=a4;

#ifdef DEV

		(void)kbstatus(&kstat);

		if (kstat.caps_state)
		{
			sprintf(temp,"%-3d,%-3d",*x,*y);
			_settextposition(25,33);
			_outtext(temp);
		}

#endif
	}
	else
	{
		*x=ERR;
		*y=ERR;
	}
}

int _PASCAL mouse_in_range(int *list, unsigned char *keys1, unsigned char *keys2)
{
	int x,y;
	int i;
	char keyc;
	int key;
	int code;
	unsigned int temp_int;

#ifdef DEV

	if (strlen(keys1) && strlen(keys2))
		if (strlen(keys1) != strlen(keys2))
			panic("Keys1 != Keys2");

#endif

	kbflush();

	mouse_put_pointer(mouse_x,mouse_y);

	if (!fast_mouse)
		while (mouse_button_l())
			;

	for (;;)
	{
		if (mouse_installed)
		{
			mouse_readxy(&x,&y);

			if (x!=mouse_x || y!=mouse_y)
			{
				mouse_erase_pointer(mouse_x,mouse_y);

				mouse_x=x;
				mouse_y=y;

				mouse_put_pointer(x,y);
			}

			if (mouse_button_r() && situation_status==OFF)
			{
				mouse_sound();

				mouse_erase_pointer(x,y);
				situation_details();

				if (x!=mouse_x || y!=mouse_y)
				{
					mouse_x=x;
					mouse_y=y;
				}

				mouse_put_pointer(x,y);
			}

			if (mouse_button_l())
			{
				for (i=0; list[i]!=ERR; i+=4)
				{
					if (x>=list[i] && x<=list[i+2] && y>=list[i+1] && y<=list[i+3])
					{
						mouse_sound();

						mouse_erase_pointer(mouse_x,mouse_y);

						return(i/4);
					}
				}
			}
		}

		if (kbready(&keyc,&code))
		{
			key=kbgetkey(&code);

			if (key==KB_C_N_ESC)          /* Translate Esc -> Q */
			{
				code=KB_C_N_Q;
				key=(int)'Q';
			}

			if (key==0)
			{
				key=code+0x80;
			}
			else
			{
				i=toupper(key);
				key=i;
			}


			if (code==KB_S_A_Q && key&0x80)
			{
				quick_exit=TRUE;

				mouse_erase_pointer(x,y);
				shut_program_down(TRUE);

				if (x!=mouse_x || y!=mouse_y)
				{
					mouse_x=x;
					mouse_y=y;
				}

				mouse_put_pointer(x,y);

				quick_exit=FALSE;
			}
			else

#ifdef DEV
			if (code==KB_S_A_C && key&0x80)
			{
				mouse_sound();

				mouse_erase_pointer(x,y);
				cmbt_DEBUG();

				if (x!=mouse_x || y!=mouse_y)
				{
					mouse_x=x;
					mouse_y=y;
				}

				mouse_put_pointer(x,y);
			}
			else
#endif

			if (code==KB_S_A_W && key&0x80)
			{
				handle_wizard_mode();
			}
			else
			if (code==KB_S_A_B && key&0x80)
			{
				oops_here_comes_the_boss();
			}
			else
			if (code==KB_S_N_F1 && situation_status==OFF)
			{
				mouse_sound();

				mouse_erase_pointer(x,y);
				situation_details();

				if (x!=mouse_x || y!=mouse_y)
				{
					mouse_x=x;
					mouse_y=y;
				}

				mouse_put_pointer(x,y);
			}
			else
			{
				if (strcmp(keys1,STR_ALL_DIGITS)==0 ||
					strcmp(keys2,STR_ALL_DIGITS)==0)
				{
					mouse_sound();
					kbflush();
					mouse_erase_pointer(mouse_x,mouse_y);
					return(0);
				}

				for (i=0; i<(int)strlen(keys1); i++)
				{
					if ((unsigned int )key==(unsigned int)keys1[i])
					{
						mouse_sound();
						kbflush();
						mouse_erase_pointer(mouse_x,mouse_y);
						return(i);
					}
				}

				for (i=0; i<(int)strlen(keys2); i++)
				{
					temp_int=(unsigned int)keys2[i]&0xFF;

					if ((unsigned int)key==(unsigned int)temp_int)
					{
						mouse_sound();
						kbflush();
						mouse_erase_pointer(mouse_x,mouse_y);
						return(i);
					}
				}
			}
		}
	}
}

void _PASCAL mouse_put_pointer(int x,int y)
{
	int k,j,i;

	if (mouse_installed)
	{
		GETBLOCK(x,y,x+8,y+8,screen_image);

		for (i=0; i<9; i++)
			for (j=0; j<9; j++)
				if ((k=mouse_pointer[i][j])!=2)
					FFPLOT(j+x,i+y,(char)k);
	}
}

void _PASCAL mouse_erase_pointer(int x,int y)
{
	if (mouse_installed)
		PUTBLOCK(x,y,screen_image);
}
