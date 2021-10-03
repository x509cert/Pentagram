#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <butil.h>
#include <bstrings.h>
#include "mmalloc.h"
#include "sprite.h"

#define PENT_DECODE(p,x,y)   (x%2?(p[y][x/2])&0xF:(p[y][x/2]>>4))

#ifndef DEV
#pragma optimize("az",on)
#pragma optimize("b2",on)
#endif

void _PASCAL print_text(char *text,int x,int y,int height,int col)
{
	int i,t;
	int number_of_quotes=0;

	stpcvt(text,RLWHITE|RTWHITE|TOUP);

	for ( ;t=*text; )
	{
		if (isalpha(t))
		{
			i=t-53;
		}
		else
		if (isdigit(t))
		{
			i=(t-48)+1;
		}
		else
		{
			switch(t)
			{
				 case '?' : i=11; break;
				 case '!' : i= 0; break;
				 case '.' : i=38; break;
				 case ',' : i=39; break;

				 case '{' : i=40; break; /* Special codes for combat_write */
				 case '}' : i=41; break;

				 case '"' : if (++number_of_quotes&1)
								i=40;
							else
								i=41;
							break;

				 case '(' : i=42; break;
				 case ')' : i=43; break;
				 case ':' : i=44; break;
				 case '-' : i=45; break;
				 case '~' : i=46; break;
				 case  39 : i=47; break;
				 default  : i=ERR;break;
			}
		}

		if (i!=ERR)
		{
			if (height==DOUBLE_HEIGHT)
			{
				print_tall_char(i,x,y,col);
			}
			else
			{
				print_char(i,x,y,col);
			}
		}

		text++;
		x+=8;
	}
}

void _PASCAL _NEAR print_char(int in,int x,int y,int col)
{
	unsigned j,k,i;

	for (i=0; i< 8; i++)
	{
		j=FONT[in*8+i];

		for (k=0;k<8;k++)
		{
		   if (j & 128)
			  FFPLOT(x+k,y+i,(char)col);

		   j <<= 1;
		}
	}
}

#ifndef DEV
#pragma optimize("",on)
#endif

void _PASCAL print_tall_char(int in,int x,int y,int col)
{
	unsigned j,k,i,z;

	for (i=0; i< 8; i++)
	{
		j=FONT[in*8+i];

		z=y+(i<<1);

		for (k=0;k<8;k++)
		{
		   if (j & 128)
		   {
			  FFPLOT(x+k,z,(char)col);
			  FFPLOT(x+k,z+1,(char)col);
		   }

		   j <<= 1;
		}
	}
}

void _PASCAL print_rune_string(char *str,int x,int y,int col)
{
	int i;
	int letter;

	strupr(str);

	for (i=0; i<(int)strlen(str); i++)
	{
		if (!isspace((int)str[i]))
		{
			if (str[i]==':')
				letter=26;
			else
				letter=str[i]-'A';

			print_rune(letter,x+i*8,y,col);
		}
	}
}

void _PASCAL print_rune(int in,int x,int y,int col)
{
	unsigned i,j,k;

	for (i=0; i<8; i++)
	{
		j=runes[in][i];

		for (k=0;k<8;k++)
		{
		   if (j & 128)
			  FFPLOT(x+k,y+i,(char)col);

		   j <<= 1;
		}
	}
}

void _PASCAL print_small_dead(int x,int y,int c)
{
	int i,j;

	for (i=0; i<6; i++)
		for (j=0; j<17; j++)
			if (dead_text[i][j])
				FFPLOT(x+j,i+y,(char)c);
}

void _PASCAL SCROLL(int scroll_num,int colour,char *text)
{
	int i;

	for (i=0; i<scroll_num; i++)
		Fscroll_scroll();

	scroll_wrap_write(colour,text);
}

void _PASCAL scroll_wrap_write(int colour,char *text)
{
	int i,j;
	int k,l,p,t;
	static char temp[500];
	int width_of_scroll=38;
	int pos_y=23*8-2;
	int number_of_quotes;

	memset((void *)temp,0,sizeof(temp));

	strupr(text);

	stpcvt(text,RLWHITE|RTWHITE);

	Fscroll_scroll();

	number_of_quotes=0;

	for (i=0,j=0,k=0; i<(int)strlen(text); i++)
	{
		temp[k++]=text[i];

		if (text[i]=='\n')
			j=0;

		if (++j>=width_of_scroll)
		{
			j=0;

			if (!isspace((int)temp[k]))
			{
				for (l=k; ; l--, j++)
				{
					if (isspace((int)temp[l]))
					{
						temp[l]='\n';
						break;
					}
				}
			}
			else
				temp[k++]='\n';
		}
	}

	for (i=0,j=1; i<(int)strlen(temp); i++)
	{
		t=(int)temp[i];

		if (t!='\n')
		{
			if (isalpha(t))
			{
				p=t-53;
			}
			else
			if (isdigit(t))
			{
				p=(t-48)+1;
			}
			else
			{
				switch(t)
				{
					 case ' ' :
					 case '\n':
					 case '\t':
					 case '\0': p=ERR;break;
					 case '?' : p=11; break;
					 case '!' : p= 0; break;
					 case '.' : p=38; break;
					 case ',' : p=39; break;
					 case '"' : if (++number_of_quotes&1)
									p=40;
								else
									p=41;
								break;

					 case '(' : p=42; break;
					 case ')' : p=43; break;
					 case ':' : p=44; break;
					 case '-' : p=45; break;
					 case '~' : p=46; break;
					 case  39 : p=47; break;
					 default  : p=ERR;break;
				}
			}

			if (p!=ERR)
				print_char(p,j*8,pos_y,colour);

			j++;
		}
		else
		{
			j=1;
			Fscroll_scroll();
		}
	}
}

void _PASCAL click_box(int x,int y,int button)
{
	int i,j;
	int xoff=35;
	int yoff=12;

	_setcolor(7);
	_rectangle(_GFILLINTERIOR,x,y,x+xoff,y+yoff);

	_setcolor(8);
	_moveto(x+xoff,y);
	_lineto(x,y);
	_lineto(x,y+yoff);

	_moveto(x+xoff,y+1);
	_lineto(x+1,y+1);
	_lineto(x+1,y+yoff);

	_setcolor(15);
	_moveto(x,y+yoff);
	_lineto(x+xoff,y+yoff);
	_lineto(x+xoff,y+1);

	_moveto(x+1,y+yoff-1);
	_lineto(x+xoff-1,y+yoff-1);
	_lineto(x+xoff-1,y+2);

	switch(button)
	{
		case B_FINISH :
					for (i=0; i<20; i++)
						for (j=0; j<7; j++)
							if (finish_button[j][i]!=0)
								FFPLOT(x+i+8,y+j+3,(char)0);

					 break;

		case B_SCAN   :
					for (i=0; i<26; i++)
						for (j=0; j<7; j++)
							if (scan_button[j][i]!=0)
								FFPLOT(x+i+5,y+j+3,(char)0);

					 break;

		case B_NO     :
					for (i=0; i<12; i++)
						for (j=0; j<7; j++)
							if (no_button[j][i]!=0)
								FFPLOT(x+i+12,y+j+3,(char)0);

					 break;

		case B_OK     :
					for (i=0; i<12; i++)
						for (j=0; j<7; j++)
							if (ok_button[j][i]!=0)
								FFPLOT(x+i+12,y+j+3,(char)0);

					 break;

		case B_YES    :
					for (i=0; i<15; i++)
						for (j=0; j<7; j++)
							if (yes_button[j][i]!=0)
								FFPLOT(x+i+10,y+j+3,(char)0);

					 break;

		case B_NEXT   :
					for (i=0; i<19; i++)
						for (j=0; j<7; j++)
							if (next_button[j][i]!=0)
								FFPLOT(x+i+8,y+j+3,(char)0);

					 break;

		case B_PREV   :
					for (i=0; i<20; i++)
						for (j=0; j<7; j++)
							if (prev_button[j][i]!=0)
								FFPLOT(x+i+8,y+j+3,(char)0);

					 break;

		case B_QUIT   :
					for (i=0; i<20; i++)
						for (j=0; j<7; j++)
							if (quit_button[j][i]!=0)
								FFPLOT(x+i+8,y+j+3,(char)0);

					 break;

		case B_CARD_RED:
					 for (i=0; i<15; i++)
						for (j=0; j<7; j++)
							if (red_button[j][i]!=0)
								FFPLOT(x+i+11,y+j+3,(char)0);

					 break;

		case B_CARD_BLACK:
					 for (i=0; i<19; i++)
						for (j=0; j<7; j++)
							if (black_button[j][i]!=0)
								FFPLOT(x+i+8,y+j+3,(char)0);

					 break;

		case B_HIGHER: for (i=0; i<20; i++)
						for (j=0; j<7; j++)
							if (higher_button[j][i]!=0)
								FFPLOT(x+i+8,y+j+3,(char)0);

					 break;

		case B_LOWER:  for (i=0; i<16; i++)
						for (j=0; j<7; j++)
							if (lower_button[j][i]!=0)
								FFPLOT(x+i+10,y+j+3,(char)0);

					 break;

		case B_PRINT:  for (i=0; i<13; i++)
						for (j=0; j<7; j++)
							if (print_button[j][i]!=0)
								FFPLOT(x+i+11,y+j+3,(char)0);

					 break;

		default:     break;
	}
}

void _PASCAL draw_pentagram(int x,int y,int c1,int c2)
{
	int i,j,c;

	for (i=0; i<28; i++)
		for (j=0; j<31; j++)
			if (c=PENT_DECODE(pentagram,j,i))
				FFPLOT(x+j,y+i,(char)(c==0x8?(char)c1:(char)c2));
}

void _PASCAL print_big_dungeon_door(int x,int y)
{
	int i,j;

	for (i=0; i<13; i++)
		for (j=0; j<12; j++)
			if (big_dungeon_door[i][j])
				FFPLOT(x+j,y+i,(char)big_dungeon_door[i][j]);
}

void _PASCAL print_large_title(char *ti)
{
	cls_scroll();

	print_text(ti,160-(strlen_half(ti)*8),150,DOUBLE_HEIGHT,0);
	print_text(ti,161-(strlen_half(ti)*8),149,DOUBLE_HEIGHT,8);
}

void _PASCAL print_little_lr(int x,int y)
{
	int i,j;

	for (i=0; i<8; i++)
		for (j=0; j<20; j++)
			if (little_lr[i][j])
				FFPLOT(x+j,y+i,(char)little_lr[i][j]);
}

void _PASCAL print_up_down(int x,int y)
{
	int i,j;

	for (i=0; i<10; i++)
		for (j=0; j<22; j++)
			if (up_down[i][j])
				FFPLOT(x+j,y+i,(char)up_down[i][j]);
}

void _PASCAL print_left_right(int x,int y)
{
	int i,j;

	for (i=0; i<11; i++)
		for (j=0; j<22; j++)
			if (left_right[i][j])
				FFPLOT(x+j,y+i,(char)left_right[i][j]);
}

void _PASCAL draw_sex_sym(int sex,int x,int y,int c)
{
	if (sex==SX_MALE)
		draw_male_sym(x,y,c);
	else
		draw_female_sym(x,y,c);
}

void _PASCAL draw_female_sym(int x,int y,int c)
{
	int i,j;

	for (i=0; i<7; i++)
		for (j=0; j<5; j++)
			if (female_sym[i][j])
				FFPLOT(x+j,y+i,(char)c);
}

void _PASCAL draw_male_sym(int x,int y,int c)
{
	int i,j;

	for (i=0; i<7; i++)
		for (j=0; j<7; j++)
			if (male_sym[i][j])
				FFPLOT(x+j,y+i,(char)c);
}

void _PASCAL draw_eddie_blood(int x,int y)
{
	int i,j;

	for (i=0; i<21; i++)
		for (j=0; j<17; j++)
			FFPLOT(x+j,y+i,(char)eddie_blood[i][j]);
}

void _PASCAL draw_eddie_blood_materialise(int x,int y)
{
	int i,j,k;

	for (k=0;k<650;k++)
	{
		i=rand()%21;
		j=rand()%17;

		if (eddie_blood[i][j])
			FFPLOT(x+j,y+i,(char)eddie_blood[i][j]);

		delay(5);
	}

	draw_eddie_blood(x,y);
}

#define del 15

void _PASCAL flash(int x,int y)
{
	char image[150];
	int i,j;

	_getimage(x,y,x+12,y+12,image);

	for (i=0; i<6; i++)
		for (j=0; j<5; j++)
			FFPLOT(j+x,i+y,(char)fla1[i][j]);

	delay(del);

	for (i=0; i<7; i++)
		for (j=0; j<6; j++)
			FFPLOT(j+x,i+y,(char)fla2[i][j]);

	delay(del);

	for (i=0; i<8; i++)
		for (j=0; j<7; j++)
			FFPLOT(j+x,i+y,(char)fla3[i][j]);

	delay(del);

	for (i=0; i<9; i++)
		for (j=0; j<8; j++)
			FFPLOT(j+x,i+y,(char)fla4[i][j]);

	delay(del);

	for (i=0; i<11; i++)
	{
		for (j=0; j<9; j++)
		{
			FFPLOT(j+x,i+y,(char)fla5[i][j]);

			if (!NO_SOUND)
				utspkr(3000+i*16);
		}
	}

	utspkr(0);

	delay(del);

	for (i=0; i<11; i++)
		for (j=0; j<9; j++)
			FFPLOT(j+x,i+y,(char)fla6[i][j]);

	delay(del);

	for (i=0; i<11; i++)
		for (j=0; j<9; j++)
			FFPLOT(j+x,i+y,(char)fla7[i][j]);

	delay(del);

	_putimage(x,y,image,_GPSET);
}

#undef del

void _PASCAL draw_guild_coa(int x,int y)
{
	int i,j;
	int c;

	for (i=0; i<23; i++)
		for (j=0; j<21; j++)
			if (c=PENT_DECODE(guild_coa,j,i))
				FFPLOT(j+x,i+y,(char)c);
}

void _PASCAL bane_rune_draw(int rune,int x,int y,int first_letter)
{
	int i,j,c;
	int xpos,ypos;
	int r;
	char *type;
	int r_off;
	char letter[4];

	for (i=0; i<15; i++)
		for (j=0; j<14; j++)
			if (c=rune_stone_image[i][j])
				FFPLOT(x+j,i+y,(char)c);

	switch(rune)
	{
		case TYP_NO_RUNES  : r_off=0; r= 1; type="None";       break;
		case TYP_UNDEAD    : r_off=0; r= 3; type="Undead";     break;
		case TYP_FIRE      : r_off=0; r= 7; type="Fire";       break;
		case TYP_WATER     : r_off=2; r=11; type="Water";      break;
		case TYP_EARTH     : r_off=0; r=12; type="Earth";      break;
		case TYP_AERIAL    : r_off=1; r=15; type="Aerial";     break;
		case TYP_DEMONIC   : r_off=1; r=18; type="Demonic";    break;
		case TYP_NOCTURNAL : r_off=0; r=19; type="Nocturnal";  break;
		case TYP_ICE       : r_off=1; r=22; type="Ice";        break;
		default 		   : r=ERR; 						   break;
	}

	if (r==ERR)
		return;

	xpos=(x+7)-((strlen_half(type))*4);
	ypos=y+18;

	write_little(type,xpos,ypos,9,FAST);

	if (first_letter)
	{
		letter[0]=type[0];
		letter[1]='\0';
		write_little(letter,xpos,ypos,11,FAST);
	}

	print_rune(r,x+2+r_off,y+4,4);
}

void _PASCAL draw_alter_arrow(int x,int y)
{
	int i,j;

	for (i=0; i<7; i++)
		for (j=0; j<10; j++)
			if (alter_ar[i][j])
				FFPLOT(j+x,i+y,alter_ar[i][j]);
}

void _PASCAL draw_chain(int x,int y)
{
	int i,j;
	char c;

	for (i=0; i<5; i++)
		for (j=0; j<38; j++)
			if (c=chain_pic[i][j])
				FFPLOT(x+j,y+i,c);
}

void _PASCAL draw_choose(int x,int y,int c)
{
	int i,j;

	for (i=0; i<19; i++)
		for (j=0; j<17; j++)
			if (choose_pic[i][j])
				FFPLOT(CMBT_X(x)+j,CMBT_Y(y)+i,(char)c);
}

void _PASCAL draw_x_hair(int x,int y,int c)
{
	int i,j;

	for (i=0; i<16; i++)
		for (j=0; j<15; j++)
			if (x_hair_pic[i][j])
				FFPLOT(CMBT_X(x)+j,CMBT_Y(y)+i,(char)c);
}

void _PASCAL draw_hit(int x,int y)
{
	int i,j;
	char c;

	for (i=0; i<16; i++)
		for (j=0; j<15; j++)
			if (c=hit_pic[i][j])
				FFPLOT(CMBT_X(x)+j,CMBT_Y(y)+i,c);
}

void _PASCAL draw_wahs_a(int x,int y)
{
	int i,j;

	for (i=0; i<7; i++)
		for (j=0; j<9; j++)
			FFPLOT(x+j,y+i,im_wahs_a[i][j]);
}

void _PASCAL draw_wahs_h(int x,int y)
{
	int i,j;

	for (i=0; i<4; i++)
		for (j=0; j<5; j++)
			FFPLOT(x+j,y+i,im_wahs_h[i][j]);
}

void _PASCAL draw_wahs_s(int x,int y)
{
	int i,j;

	for (i=0; i<5; i++)
		for (j=0; j<5; j++)
			FFPLOT(x+j,y+i,im_wahs_s[i][j]);
}

void _PASCAL draw_wahs_w(int x,int y)
{
	int i,j;

	for (i=0; i<7; i++)
		for (j=0; j<4; j++)
			FFPLOT(x+j,y+i,im_wahs_w[i][j]);
}

void _PASCAL draw_HOE_coa(int x ,int y)
{
	int i,j;
	int c;

	for (i=0; i<23; i++)
		for (j=0; j<21; j++)
			if (c=PENT_DECODE(hoe_coa,j,i))
				FFPLOT(j+x,i+y,(char)c);
}

#define MAX_TWINKLE 3

void _PASCAL twinkle(int x,int y)
{
	int i,j;
	int col;
	int x1[MAX_TWINKLE],y1[MAX_TWINKLE];
	char *block[MAX_TWINKLE];

	for (i=0; i<MAX_TWINKLE; i++)
		block[i]=Mmalloc(100*sizeof(char));

	for (i=0; i<20; i++)
	{
		if (!NO_SOUND)
			utspkr(1000+((i*50)%500));

		for (j=0; j<MAX_TWINKLE; j++)
		{
			x1[j]=x+(rand()%19);
			y1[j]=y+(rand()%20);
			col=rand()%6+1;

			GETBLOCK(x1[j],y1[j],x1[j]+4,y1[j]+4,block[j]);

			FFPLOT(x1[j]+1,y1[j]+1,(char)(col+8));

			FFPLOT(x1[j],  y1[j]+1,(char)col);
			FFPLOT(x1[j]+1,y1[j],  (char)col);
			FFPLOT(x1[j]+2,y1[j]+1,(char)col);
			FFPLOT(x1[j]+1,y1[j]+2,(char)col);
		}

		delay(60);

		for (j=MAX_TWINKLE-1; j>=0; j--)
			PUTBLOCK(x1[j],y1[j],block[j]);
	}

	utspkr(0);

	for (i=0; i<MAX_TWINKLE; i++)
		Mfree(block[i]);
}
