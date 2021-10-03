#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bkeys.h>
#include <bkeybrd.h>

void _PASCAL train_generate_base_scores()
{
	switch(adv.nrace)
	{
		case DWARF      :  adv.strength= 12; adv.intelligence=  9; adv.piety=  8;
						   adv.agility =  7; adv.toughness   = 12; adv.luck =  9;
						   adv.charisma=  8;
						   break;

		case HIGH_ELF	:  adv.strength=  9; adv.intelligence= 10; adv.piety=  8;
						   adv.agility = 10; adv.toughness   =  8; adv.luck =  9;
						   adv.charisma= 11;
						   break;

		case GNOME		:  adv.strength=  8; adv.intelligence= 10; adv.piety= 12;
						   adv.agility =  9; adv.toughness	 =	9; adv.luck =  7;
						   adv.charisma=  7;
						   break;

		case HALF_OGRE  :  adv.strength= 12; adv.intelligence=  5; adv.piety=  5;
						   adv.agility =  8; adv.toughness   = 13; adv.luck =  5;
						   adv.charisma=  6;
						   break;

		case HALFLING   :  adv.strength=  8; adv.intelligence=  6; adv.piety=  6;
						   adv.agility = 12; adv.toughness   = 10; adv.luck = 12;
						   adv.charisma= 11;
						   break;

		case HUMAN      :  adv.strength= 11; adv.intelligence=  9; adv.piety=  9;
						   adv.agility =  9; adv.toughness   =  9; adv.luck =  9;
						   adv.charisma=  9;
						   break;

		case SYLVAN_ELF :  adv.strength= 11; adv.intelligence= 10; adv.piety=  9;
						   adv.agility = 12; adv.toughness   = 11; adv.luck = 10;
						   adv.charisma= 11;
						   break;

		case DARK_ELF   :  adv.strength= 10; adv.intelligence=  9; adv.piety=  8;
						   adv.agility = 10; adv.toughness   = 11; adv.luck =  9;
						   adv.charisma=  9;
						   break;
	}

	switch(adv.sex)
	{
		case SX_MALE    :  adv.strength++;
						   adv.toughness++;
						   break;

		case SX_FEMALE  :  adv.luck++;
						   adv.charisma++;
						   adv.piety++;
						   break;
	}
}

void _PASCAL train_generate_scores()
{

	GWINDOW win,win_im;
	static char *t[]={"Str:","Int:","Pie:","Tou:","Agi:","Cha:","Luc:"};
	int i;

	win.x1=3;
	win.y1=1;
	win.x2=37;
	win.y2=12;
	win.back=0;
	win.border=14;

	win_im.x1=1;
	win_im.y1=12;
	win_im.x2=40;
	win_im.y2=25;
	win_im.back=0;
	win_im.border=13;

	make_gwindow(&win_im);
	make_gwindow(&win);

	for (i=0; i<SIZE(t); i++)
	{
		_settextcolor(4);
		_settextposition(win.y1+i+1,win.x1+1);
		_outtext(t[i]);

		if (mouse_installed)
			print_little_lr(250,16+((i-1)*8));
	}

	_settextposition(10,4);
	_outtext("Extra:");

	click_box(230,70,B_FINISH);

	_setcolor(3);
	_rectangle(_GBORDER,55,6,208,66);

	_settextcolor(1);
	_settextposition(10,15);
	_outtext(adv.race);

	draw_sex_sym(adv.sex,102,72,9);

	show_all_images(adv.sex);

	abort_training=FALSE;

	fast_mouse=ON;
	train_alter_scores();
	fast_mouse=OFF;

	kill_gwindow(&win);

	if (!abort_training)
	{
		adv.nclass=train_get_class();
		strcpy(adv.class,get_class_string(adv.nclass,adv.sex));
	}

	kill_gwindow(&win_im);
}

void _PASCAL train_alter_scores()
{
	unsigned str,ine,pie,tou,agi,cha,luc;
	int extra;
	int fin=FALSE;
	int a_class=0;
	int key_press;
	int fy=0;
	static int boundary[]={
						   261, 8,269,14,
						   250, 8,258,14,  /* Str */

						   261,16,269,22,
						   250,16,258,22,  /* Int */

						   261,24,269,30,
						   250,24,258,30,  /* Pie */

						   261,32,269,38,
						   250,32,258,38,  /* Tou */

						   261,40,269,46,
						   250,40,258,46,  /* Agi */

						   261,48,269,54,
						   250,48,258,54,  /* Cha */

						   261,56,269,62,
						   250,56,258,62,  /* Luc */

						   230,70,265,82,
						   -1,-1,-1,-1};

	str=adv.strength;
	ine=adv.intelligence;
	pie=adv.piety;
	tou=adv.toughness;
	agi=adv.agility;
	cha=adv.charisma;
	luc=adv.luck;

	extra=12;

	if (percent()>70)
	{
		extra++;

		if (percent()>70)
		{
			extra++;

			if (percent()>70)
				extra++;
		}
	}

	train_update_graph_scores(str,ine,pie,tou,agi,cha,luc,extra);

	train_update_possible_classes();

	while (!fin)
	{
		a_class=be_warrior+be_priest+be_wizard+be_druid+be_thief+
				be_ranger+be_crusader+be_bard+be_monk+be_illusionist+
				be_hunter+be_duelist;

		key_press=(mouse_installed
				 ?mouse_in_range(boundary,"ªªªªªªªªªªªªªªQQ","")
				 :train_fake_alter_scores(&fy));

		switch (key_press)
		{
			case 0 :
				if (extra>0 && adv.strength<18)      /* Inc Str */
				{
					extra--;
					adv.strength++;
				}

				break;

			case 1 :
				if (adv.strength>str)                /* Dec Str */
				{
					extra++;
					adv.strength--;
				}

				break;

			case 2 :
				if (extra>0 && adv.intelligence<18)  /* Inc Int */
				{
					extra--;
					adv.intelligence++;
				}

				break;

			case 3 :
				if (adv.intelligence>ine)            /* Dec Int */
				{
					extra++;
					adv.intelligence--;
				}

				break;

			case 4 :
				if (extra>0 && adv.piety<18)          /* Inc Pie */
				{
					extra--;
					adv.piety++;
				}

				break;

			case 5 :
				if (adv.piety>pie)                   /* Dec Pie */
				{
					extra++;
					adv.piety--;
				}

				break;

			case 6:
				if (extra>0 && adv.toughness<18)     /* Inc Tou */
				{
					extra--;
					adv.toughness++;
				}

				break;

			case 7 :
				if (adv.toughness>tou)               /* Dec Tou */
				{
					extra++;
					adv.toughness--;
				}

				break;

			case 8 :
				if (extra>0 && adv.agility<18)       /* Inc Agi */
				{
					extra--;
					adv.agility++;
				}

				break;

			case 9 :
				if (adv.agility>agi)                 /* Dec Agi */
				{
					extra++;
					adv.agility--;
				}

				break;

			case 10 :
				if (extra>0 && adv.charisma<18)      /* Inc Cha */
				{
					extra--;
					adv.charisma++;
				}

				break;

			case 11 :
				if (adv.charisma>cha)                /* Dec Cha */
				{
					extra++;
					adv.charisma--;
				}

				break;

			case 12 :
				if (extra>0 && adv.luck<18)          /* Inc Luc */
				{
					extra--;
					adv.luck++;
				}

				break;

			case 13 :
				if (adv.luck>luc)                    /* Dec Luc */
				{
					extra++;
					adv.luck--;
				}

				break;

			default : if (!extra && a_class)
						fin=TRUE;
					  else
					  {
						if (extra)
						{
							if (gget_yn("Dost thou wish to cease training?")==TRUE)
							{
								abort_training=fin=TRUE;
							}
						}
					  }

					  break;
		}

		if (!abort_training)
		{
			train_update_graph_scores(adv.strength,
									  adv.intelligence,
									  adv.piety,
									  adv.toughness,
									  adv.agility,
									  adv.charisma,
									  adv.luck,
									  extra);

			train_update_possible_classes();
		}
	}
}

int _PASCAL train_fake_alter_scores(int *y_pos)
{
	int y_offset=8;
	int code;
	int fin=FALSE;
	int valid_key;
	int old_y;
	int new_y=*y_pos;
	int value;

	draw_alter_arrow(250,(new_y*8)+y_offset);

	while (!fin)
	{
		kbgetkey(&code);

		valid_key=TRUE;
		old_y=new_y;

		switch(code)
		{
			case KB_S_N_UP   : new_y--;

							   if (new_y<0)
								  new_y=6;

							   break;

			case KB_S_N_DOWN : new_y++;

							   if (new_y>6)
								  new_y=0;

							   break;

			case KB_S_N_LEFT : fin=TRUE;
							   value=new_y*2+1;
							   break;

			case KB_S_N_RIGHT: fin=TRUE;
							   value=new_y*2;
							   break;

			case KB_S_N_ESC  :
			case KB_S_N_Q    :
			case KB_S_N_F    : fin=TRUE;
							   value=14;
							   break;

			default          : valid_key=FALSE;
							   break;
		}

		if (valid_key)
			mouse_sound();

		if (!fin && valid_key)
		{
			_setcolor(0);
			_rectangle(_GFILLINTERIOR,
					   250,
					   (old_y*8)+y_offset,
					   260,
					   (old_y*8)+y_offset+9);

			draw_alter_arrow(250,(new_y*8)+y_offset);
		}
	}

	_setcolor(0);
	_rectangle(_GFILLINTERIOR,
			   250,
			   (new_y*8)+y_offset,
			   260,
			   (new_y*8)+y_offset+9);

	*y_pos=new_y;

	return(value);
}

void _PASCAL train_update_possible_classes()
{
#define X1 30  /* +25 */
#define X2 140
#define X3 253
#define Y1 106 /* +13 */
#define Y2 131
#define Y3 156
#define Y4 181

	be_warrior= be_priest     = be_wizard  = be_druid   =
	be_thief  = be_ranger     = be_crusader= be_bard    =
	be_monk   = be_illusionist= be_hunter  = be_duelist = FALSE;

	switch(adv.nrace)
	{
		case DWARF      :   be_warrior  = tick(X3,Y3,(adv.strength>=15 && adv.toughness>=11)?ON:OFF);
							be_priest   = tick(X2,Y4,(adv.piety>=15 && adv.charisma>=10)?ON:OFF);
							be_wizard   = tick(X3,Y4,(adv.intelligence>=15 && adv.agility>=12)?ON:OFF);
							be_druid    = tick(X1,Y3,(adv.intelligence>=15 && adv.piety>=14)?ON:OFF);
							be_thief    = tick(X3,Y2,(adv.strength>=12 && adv.agility>=15 && adv.luck>=12)?ON:OFF);
							be_ranger   = tick(X3,Y1,(adv.strength>=15 && adv.intelligence>=12 && adv.piety>=12)?ON:OFF);
							break;

		case HIGH_ELF	:	be_warrior	= tick(X3,Y3,(adv.strength>=15 && adv.toughness>=11)?ON:OFF);
							be_priest   = tick(X2,Y4,(adv.piety>=15 && adv.charisma>=10)?ON:OFF);
							be_wizard   = tick(X3,Y4,(adv.intelligence>=15 && adv.agility>=12)?ON:OFF);
							be_druid    = tick(X1,Y3,(adv.intelligence>=15 && adv.piety>=14)?ON:OFF);
							be_thief    = tick(X3,Y2,(adv.strength>=12 && adv.agility>=15 && adv.luck>=12)?ON:OFF);
							be_bard     = tick(X1,Y1,(adv.strength>=15 && adv.intelligence>=10 && adv.piety>=10 && adv.toughness>=10 && adv.agility>=10 && adv.luck>=10 && adv.charisma>=12)?ON:OFF);
							be_ranger   = tick(X3,Y1,(adv.strength>=15 && adv.intelligence>=12 && adv.piety>=12)?ON:OFF);
							be_illusionist=tick(X2,Y2,(adv.intelligence>=15 && adv.agility>=13 && adv.piety>=10)?ON:OFF);
							be_duelist  = tick(X1,Y4,(adv.strength>=15 && adv.toughness>=10 && adv.agility>=14 && adv.luck>=12)?ON:OFF);
							break;

		case GNOME      :   be_warrior  = tick(X3,Y3,(adv.strength>=15 && adv.toughness>=11)?ON:OFF);
							be_priest   = tick(X2,Y4,(adv.piety>=15 && adv.charisma>=10)?ON:OFF);
							be_thief    = tick(X3,Y2,(adv.strength>=12 && adv.agility>=15 && adv.luck>=12)?ON:OFF);
							be_ranger   = tick(X3,Y1,(adv.strength>=15 && adv.intelligence>=12 && adv.piety>=12)?ON:OFF);
							be_illusionist=tick(X2,Y2,(adv.intelligence>=15 && adv.agility>=13 && adv.piety>=10)?ON:OFF);
							break;

		case HALF_OGRE  :   be_warrior  = tick(X3,Y3,(adv.strength>=15 && adv.toughness>=11)?ON:OFF);
							be_hunter   = tick(X2,Y1,(adv.strength>=15 && adv.toughness>=14 && adv.agility>=13 && adv.luck>=10)?ON:OFF);
							break;

		case HALFLING   :   be_warrior  = tick(X3,Y3,(adv.strength>=15 && adv.toughness>=11)?ON:OFF);
							be_thief    = tick(X3,Y2,(adv.strength>=12 && adv.agility>=15 && adv.luck>=12)?ON:OFF);
							break;

		case HUMAN      :   be_warrior  = tick(X3,Y3,(adv.strength>=15 && adv.toughness>=11)?ON:OFF);
							be_priest   = tick(X2,Y4,(adv.piety>=15 && adv.charisma>=10)?ON:OFF);
							be_wizard   = tick(X3,Y4,(adv.intelligence>=15 && adv.agility>=12)?ON:OFF);
							be_druid    = tick(X1,Y3,(adv.intelligence>=15 && adv.piety>=14)?ON:OFF);
							be_thief    = tick(X3,Y2,(adv.strength>=12 && adv.agility>=15 && adv.luck>=12)?ON:OFF);
							be_ranger   = tick(X3,Y1,(adv.strength>=15 && adv.intelligence>=12 && adv.piety>=12)?ON:OFF);
							be_illusionist=tick(X2,Y2,(adv.intelligence>=15 && adv.agility>=13 && adv.piety>=10)?ON:OFF);
							be_duelist  = tick(X1,Y4,(adv.strength>=15 && adv.toughness>=10 && adv.agility>=14 && adv.luck>=12)?ON:OFF);
							be_hunter   = tick(X2,Y1,(adv.strength>=15 && adv.toughness>=14 && adv.agility>=13 && adv.luck>=10)?ON:OFF);
							be_crusader = tick(X1,Y2,(adv.piety>=12 && adv.strength>=15 && adv.charisma>=10)?ON:OFF);
							be_bard     = tick(X1,Y1,(adv.strength>=15 && adv.intelligence>=10 && adv.piety>=10 && adv.toughness>=10 && adv.agility>=10 && adv.luck>=10 && adv.charisma>=12)?ON:OFF);
							be_monk     = tick(X2,Y3,(adv.piety>=12 && adv.intelligence>=15 && adv.agility>=10 && adv.charisma>=10)?ON:OFF);
							break;

		case SYLVAN_ELF :   be_warrior  = tick(X3,Y3,(adv.strength>=15 && adv.toughness>=11)?ON:OFF);
							be_thief    = tick(X3,Y2,(adv.strength>=12 && adv.agility>=15 && adv.luck>=12)?ON:OFF);
							be_bard     = tick(X1,Y1,(adv.strength>=15 && adv.intelligence>=10 && adv.piety>=10 && adv.toughness>=10 && adv.agility>=10 && adv.luck>=10 && adv.charisma>=12)?ON:OFF);
							be_duelist  = tick(X1,Y4,(adv.strength>=15 && adv.toughness>=10 && adv.agility>=14 && adv.luck>=12)?ON:OFF);
							be_ranger   = tick(X3,Y1,(adv.strength>=15 && adv.intelligence>=12 && adv.piety>=12)?ON:OFF);
							be_druid    = tick(X1,Y3,(adv.intelligence>=15 && adv.piety>=14)?ON:OFF);
							be_hunter   = tick(X2,Y1,(adv.strength>=15 && adv.toughness>=14 && adv.agility>=13 && adv.luck>=10)?ON:OFF);
							break;

		case DARK_ELF   :   be_warrior  = tick(X3,Y3,(adv.strength>=15 && adv.toughness>=11)?ON:OFF);
							be_thief    = tick(X3,Y2,(adv.strength>=12 && adv.agility>=15 && adv.luck>=12)?ON:OFF);
							be_illusionist=tick(X2,Y2,(adv.intelligence>=15 && adv.agility>=13 && adv.piety>=10)?ON:OFF);
							be_wizard   = tick(X3,Y4,(adv.intelligence>=15 && adv.agility>=12)?ON:OFF);
							break;
	}
}

void _PASCAL train_update_graph_scores(int s,int i,int p,int t,int a,int c,int l,int x)
{
	int x_off=60;
	int y_off=10;
	int c1=11;
	int c2=0;
	int tx=29;
	int txx=10;
	char temp[6];

	_settextcolor(12);

	_settextposition(2,tx);
	sprintf(temp,"%2d",s);
	_outtext(temp);

	_settextposition(3,tx);
	sprintf(temp,"%2d",i);
	_outtext(temp);

	_settextposition(4,tx);
	sprintf(temp,"%2d",p);
	_outtext(temp);

	_settextposition(5,tx);
	sprintf(temp,"%2d",t);
	_outtext(temp);

	_settextposition(6,tx);
	sprintf(temp,"%2d",a);
	_outtext(temp);

	_settextposition(7,tx);
	sprintf(temp,"%2d",c);
	_outtext(temp);

	_settextposition(8,tx);
	sprintf(temp,"%2d",l);
	_outtext(temp);

	_settextposition(10,txx);
	sprintf(temp,"%2d",x);
	_outtext(temp);

	_setcolor(c1);
	_rectangle(_GFILLINTERIOR,x_off,y_off,s*8+x_off,y_off+4);

	_setcolor(c2);
	_rectangle(_GFILLINTERIOR,s*8+x_off+1,y_off,18*8+x_off,y_off+4);

	y_off+=8;
	_setcolor(c1);
	_rectangle(_GFILLINTERIOR,x_off,y_off,i*8+x_off,y_off+4);

	_setcolor(c2);
	_rectangle(_GFILLINTERIOR,i*8+x_off+1,y_off,18*8+x_off,y_off+4);

	y_off+=8;
	_setcolor(c1);
	_rectangle(_GFILLINTERIOR,x_off,y_off,p*8+x_off,y_off+4);

	_setcolor(c2);
	_rectangle(_GFILLINTERIOR,p*8+x_off+1,y_off,18*8+x_off,y_off+4);

	y_off+=8;
	_setcolor(c1);
	_rectangle(_GFILLINTERIOR,x_off,y_off,t*8+x_off,y_off+4);

	_setcolor(c2);
	_rectangle(_GFILLINTERIOR,t*8+x_off+1,y_off,18*8+x_off,y_off+4);

	y_off+=8;
	_setcolor(c1);
	_rectangle(_GFILLINTERIOR,x_off,y_off,a*8+x_off,y_off+4);

	_setcolor(c2);
	_rectangle(_GFILLINTERIOR,a*8+x_off+1,y_off,18*8+x_off,y_off+4);

	y_off+=8;
	_setcolor(c1);
	_rectangle(_GFILLINTERIOR,x_off,y_off,c*8+x_off,y_off+4);

	_setcolor(c2);
	_rectangle(_GFILLINTERIOR,c*8+x_off+1,y_off,18*8+x_off,y_off+4);

	y_off+=8;
	_setcolor(c1);
	_rectangle(_GFILLINTERIOR,x_off,y_off,l*8+x_off,y_off+4);

	_setcolor(c2);
	_rectangle(_GFILLINTERIOR,l*8+x_off+1,y_off,18*8+x_off,y_off+4);
}

int _PASCAL train_get_class()
{
	int a_class;
	int class;
	int fin=FALSE;
	char *t2="BCDUHLMPRTWI";
	static int boundary[]={5,92,64,109,         /* Bard         */
						   5,117,89,134,        /* Crusader     */
						   5,142,67,158,        /* Druid        */
						   5,168,83,183,        /* Duelist      */

						   115,92,185,109,      /* Hunter       */
						   115,117,222,137,     /* Illusionist  */
						   115,142,171,160,     /* Monk         */
						   115,168,185,183,     /* Priest       */

						   228,92,299,109,      /* Ranger       */
						   228,117,289,133,     /* Thief        */
						   228,142,309,159,     /* Warrior      */
						   228,168,299,188,     /* Wizard       */
						   -1,-1,-1,-1};
	GWINDOW win,win_mess;
	char *mess="Select thy Profession";

	win.x1=5;
	win.y1=1;
	win.x2=34;
	win.y2=11;
	win.border=6;
	win.back=0;

	a_class=be_warrior+be_priest+be_wizard+be_druid+be_thief+
			be_ranger+be_crusader+be_bard+be_monk+be_illusionist+
			be_hunter+be_duelist;

	if (a_class==1)
	{
		if (be_warrior)
			class=WARRIOR;

		if (be_priest)
			class=PRIEST;

		if (be_wizard)
			class=WIZARD;

		if (be_druid)
			class=DRUID;

		if (be_thief)
			class=THIEF;

		if (be_ranger)
			class=RANGER;

		if (be_crusader)
			class=CRUSADER;

		if (be_bard)
			class=BARD;

		if (be_monk)
			class=MONK;

		if (be_illusionist)
			class=ILLUSIONIST;

		if (be_hunter)
			class=HUNTER;

		if (be_duelist)
			class=DUELIST;

		return(class);
	}

	win_mess.x1=19-strlen_half(mess);
	win_mess.y1=(win.y2-win.y1)/2+1;
	win_mess.x2=21+strlen_half(mess)+1;
	win_mess.y2=win_mess.y1+5;
	win_mess.back=0;
	win_mess.border=14;

	make_gwindow(&win_mess);

	_settextcolor(1);
	_settextposition(win_mess.y1+1,21-strlen_half(adv.race));
	_outtext(adv.race);

	draw_sex_sym(adv.sex,(18-strlen_half(adv.race))*8,win_mess.y1*8,9);

	_settextcolor(3);
	_settextposition(win_mess.y1+3,20-strlen_half(mess));
	_outtext(mess);

	while (!fin)
	{
		switch(mouse_in_range(boundary,t2,""))
		{
			case 0 : if (be_bard)        {class=BARD;       fin=TRUE;} break;
			case 1 : if (be_crusader)    {class=CRUSADER;   fin=TRUE;} break;
			case 2 : if (be_druid)       {class=DRUID;      fin=TRUE;} break;
			case 3 : if (be_duelist)     {class=DUELIST;    fin=TRUE;} break;
			case 4 : if (be_hunter)      {class=HUNTER;     fin=TRUE;} break;
			case 5 : if (be_illusionist) {class=ILLUSIONIST;fin=TRUE;} break;
			case 6 : if (be_monk)        {class=MONK;       fin=TRUE;} break;
			case 7 : if (be_priest)      {class=PRIEST;     fin=TRUE;} break;
			case 8 : if (be_ranger)      {class=RANGER;     fin=TRUE;} break;
			case 9 : if (be_thief)       {class=THIEF;      fin=TRUE;} break;
			case 10: if (be_warrior)     {class=WARRIOR;    fin=TRUE;} break;
			case 11: if (be_wizard)      {class=WIZARD;     fin=TRUE;} break;
		}
	}

	kill_gwindow(&win_mess);

	return(class);
}
