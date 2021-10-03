#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bkeybrd.h>
#include <butil.h>
#include "mmalloc.h"

static char _FAR  *sk[NUM_ANIMATED_SKULLS];

void _PASCAL all_party_damaged_swim()
{
	GWINDOW win;
	int i,j;
	int damage;
	int mod_damage;
	int someone_damaged=FALSE;
	char temp[40];

	if (check_party_globals_in_effect(IN_EFFECT_WALK_ON_WATER)!=ERR)
		return;

	SCROLL(1,7,"Thy party goes for a swim!");

	create_damage_window(&win);

	_settextcolor(DAMAGE_WINDOW_COL);

	for (i=0,j=0; i<=P_NUM; i++)
	{
		if (player_is_dead(&TPP[i]))
				continue;

		if (percent()>effective_swim(&TPP[i]))
		{
			damage=get_dice_roll(8,1,0);
			mod_damage=modified_damage(damage);

			TPP[i].current_hp-=mod_damage;

			if (TPP[i].current_hp<=0)
				player_has_died_set(&TPP[i]);

			someone_damaged=TRUE;

			sprintf(temp,"%s suffers %d damage%s",
						 TPP[i].name,
						 mod_damage,
						 (TPP[i].current_hp==0)?" & dies":".");
		}
		else
		{
			sprintf(temp,"%s swims!",TPP[i].name);
		}

		_settextposition(win.y1+DAMAGE_WINDOW_Y+j,win.x1+1);
		_outtext(temp);

		j++;
	}

	damage_window_wait_kill(&win,someone_damaged);

	(void)is_all_party_dead();
}

void _PASCAL print_all_dead_message()
{
	char _FAR *back_image;
	int i;

	kbflush();

	print_grim_reaper();

	back_image=(char _FAR *)Mmalloc((size_t)6400);

	if (back_image==NULL)
		panic_RAM("Back Image (Death)");

	_getimage(59,20,174,124,back_image);

	load_animated_skulls();

	dead_draw_fancy_box();

	animate_skull(108,55);

	death_sound();

	for (i=0; i<2; i++)
	{
		flash(70,34);
		flash(140,44);
		flash(70,99);
		flash(130,90);
		flash(100,80);
	}

	kill_animated_skull();

	pause(1);

	dead_place_text();

	_putimage(59,20,back_image,_GPSET);

	Mfree((void *)back_image);
}

void _PASCAL dead_draw_fancy_box()
{
	generic_pic_draw(59,20,"DEATH");
}

void _PASCAL dead_place_text()
{
	int i,x;
	int freq=400;
	static char *t1[]={"THY ENTIRE",
					   "PARTY HATH",
					   "PERISHED",
					   "MISERABLY!"};

	static char *t2[]={"O, SUCH A",
					   "FRAGILE",
					   "SHELL BE",
					   "THIS WE",
					   "CALL MAN!"};

	for (i=0; i<SIZE(t1); i++)
	{
		x=116-(strlen(t1[i])*4);

		dead_print_text_scan(t1[i],x+1,106,14,&freq);
	}

	utspkr(0);

	dead_smooth_scroll_window(12);

	pause(2);

	freq=400;

	for (i=0; i<SIZE(t2); i++)
	{
		x=116-(strlen(t2[i])*4);

		dead_print_text_scan(t2[i],x+1,106,14,&freq);
	}

	utspkr(0);

	dead_smooth_scroll_window(10);

	pause(2);

	dead_smooth_scroll_window(85);
}

void _PASCAL dead_print_text_scan(char *text,int x,int y,int col,int *freq)
{
	int i,scan_line,t;
	char *start_text;
	int start_x;
	unsigned int j,k;

	strupr(text);

	start_text=text;
	start_x   =x;

	if (!NO_SOUND)
		utspkr(*freq);

	for (scan_line=0; scan_line<8; scan_line++)
	{
		text=start_text;
		x   =start_x;

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
					 case '!' : i= 0; break;
					 case '.' : i=38; break;
					 case ',' : i=39; break;
					 case  39 : i=47; break;
					 default  : i=-1; break;
				}
			}

			if (i!=ERR)
			{
				j=FONT[i*8+scan_line];

				for (k=0;k<8;k++)
				{
				   if (j & 128)
					   FFPLOT(x+k,y,(char)col);

				   j <<= 1;
				}
			}

			if (!NO_SOUND)
				utspkr((*freq)--);

			text++;
			x+=8;
		}

		Fscroll_message(1);
		delay(10);
	}

	dead_smooth_scroll_window(2);
}

void _PASCAL dead_smooth_scroll_window(int num)
{
	int i;

	for (i=0; i<num; i++)
	{
		Fscroll_message(1);
		delay(7);
	}
}

void _PASCAL reduce_hp(PLAYER *adv,int damage,int cause)
{
	adv->current_hp-=damage;

	if (adv->current_hp<=0)
	{
		adv->current_hp=0;
		adv->is_dead=TRUE;

		nullify_all_in_effect(adv);

		if (cause!=NO_DISPLAY)
			player_has_died(adv,cause);
	}
}

int _PASCAL get_dice_roll(int dice,int num_rolls,int add)
{
	int num,i;

	num=0;

	for (i=0; i<num_rolls; i++)
		num+=rand()%dice+1;

	num+=add;

	return(num);
}

int _PASCAL get_d20()
{
	return(get_dice_roll(20,1,0));
}

void _PASCAL player_has_died_set(PLAYER *adv)
{
	adv->is_dead=TRUE;
	adv->current_hp=0;

	memset((void *)&adv->in_effect,0,sizeof(IN_EFFECT));
}

void _PASCAL player_has_died(PLAYER *adv,int cause)
{
	GWINDOW win;
	char *t;
	static int boundary[]={132,84,167,96,
						   -1,-1,-1,-1};

	player_has_died_set(adv);

	win.x1=9;
	win.y1=7;
	win.x2=29;
	win.y2=14;
	win.back=0;
	win.border=4;

	make_gwindow(&win);

	_settextcolor(5);

	_settextposition(win.y1+1,win.x1+5);
	_outtext(adv->name);

	_settextposition(win.y1+2,win.x1+5);
	_outtext("hath died");

	_settextposition(win.y1+3,win.x1+5);

	switch(cause)
	{
		case FROM_POISON   : t="from poison.";   break;
		case FROM_COMBAT   : t="in melee.";      break;
		case FROM_DROWNING : t="from drowning."; break;
		case FROM_HUNGER   : t="of starvation."; break;
		case FROM_DISEASE  : t="from disease";   break;
		case FROM_FROZE    : t="Fffrroozzen!";   break;
		case FROM_BURNT    : t="from burns.";    break;
		case FROM_FRIGHT   : t="from fright";    break;
		case FROM_ELECTR   : t="Electrocuted!";  break;
		case FROM_FELL     : t="from falling.";  break;
		case FROM_TRAP     : t="from a trap!";   break;
		case FROM_HUNTING  : t="from Hunting!";  break;
		case FROM_HERBS    : t="of toxic herbs!";break;
		case FROM_CHILL    : t="from cold!";     break;
	}

	_outtext(t);

	click_box(132,84,B_OK);

	draw_gravestone(73,64);

	death_sound();

	(void)mouse_in_range(boundary,STR_ALL_DIGITS,"");

	kill_gwindow(&win);

	(void)is_all_party_dead();
}

int _PASCAL is_all_party_dead()
{
	int i;
	int all_dead=TRUE;

	for (i=0; i<=P_NUM; i++)
		if (player_is_alive(&TPP[i]))
				all_dead=FALSE;

	if (all_dead)
		the_party.all_dead=TRUE;

	return(all_dead);
}

int _PASCAL modified_damage(int damage)
{
	return(min(99,1+(modified_average_level()/2)*damage));
}

void _PASCAL load_animated_skulls()
{
	FILE *fptr;
	int i;
	char temp[30];

	for (i=0; i<NUM_ANIMATED_SKULLS; i++)
	{
		sk[i]=(char _FAR *)Mmalloc(160);

		if (sk[i]==NULL)
			panic_RAM("Anim. Skull");

		sprintf(temp,"%sANSKULL%d.PIC",PIC_DIRECTORY,i+1);

		fptr=fopen(temp,"rb");

		if (fptr==NULL)
			panic_FILE(temp);

		fread((void *)sk[i],160,1,fptr);

		fclose(fptr);
	}
}

void _PASCAL kill_animated_skull()
{
	int i;

	for (i=0; i<NUM_ANIMATED_SKULLS; i++)
		Mfree((void *)sk[i]);
}

void _PASCAL animate_skull(int x,int y)
{
	int i,j;
	int dir=1;

	for (i=0,j=1; i<60; i++)
	{
		_putimage(x,y,sk[j],_GPSET);

		if (((j+=dir)>=NUM_ANIMATED_SKULLS-1) || j<=1)
			dir=-dir;

		if (!NO_SOUND)
			utspkr(40+(j*2));

		delay(50);
	}

	utspkr(0);
}

void _PASCAL create_damage_window(GWINDOW *win)
{
	win->x1=2;
	win->y1=2;
	win->x2=40;
	win->y2=win->y1+9+MAX_PARTY;
	win->border=5;
	win->back=0;

	make_gwindow(win);

	generic_pic_draw(win->x1*8+44,win->y1*8-2,"DAMAGE");

	click_box(139,109,B_OK);
}

void _PASCAL damage_window_wait_kill(GWINDOW *win,int injured)
{
	static int bound[]={139,109,174,121,
						-1,-1,-1,-1};

	if (injured)
		solemn_sound();
	else
		good_sound();

	mouse_in_range(bound,STR_ALL_DIGITS,"");

	kill_gwindow(win);
}
