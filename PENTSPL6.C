#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

/* Illusionist Spells non-battle magic*/

int _PASCAL cast_SLY_EARS(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[120];
	int whom;

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			whom=adv_select_adventurer("Cast Sly Ears","on whom?",TRUE);

			if (whom!=ERR)
			{
				res=TRUE;

				TPP[whom].in_effect.sly_ears+=adv->level*2;

				sprintf(temp,"%s puts %s hands over %s ears and chants "
							 "an arcane verse to %sself...",
							 adv->name,
							 adv->his_her,
							 adv->his_her,
							 adv->him_her);

				print_spell_description(temp);
			}
			else
				add_lost_spell_pts(adv,1);
		}
	}

	return(res);
}

int _PASCAL cast_CATS_EYES(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[120];
	int whom;

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,1))
		{
			whom=adv_select_adventurer("Cast Cats Eyes","on whom?",TRUE);

			if (whom!=ERR)
			{
				res=TRUE;

				TPP[whom].in_effect.cats_eyes+=adv->level*2;

				sprintf(temp,"%s puts %s hands over %s mouth and mutters "
							 "a mystic verse to %sself...",
							 adv->name,
							 adv->his_her,
							 adv->his_her,
							 adv->him_her);

				print_spell_description(temp);
			}
			else
				add_lost_spell_pts(adv,1);
		}
	}

	return(res);
}

/************************************************************************/

int _PASCAL cast_CREATE_ARTIFACTS(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	int too_much=FALSE;
	int opt;
	char *t2="DAUOQ",temp[80];
	GWINDOW win;
	static char *t[]={"Darts","Arrows","Quarrels","Oil Flasks","Quit"};
	static int qty[]={3,3,3,2};
	static int boundary[]={136,48,214,54,
						   136,56,214,62,
						   136,64,214,70,
						   136,72,214,78,
						   136,80,214,86,
						   -1,-1,-1,-1};

	if (!cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
		return(FALSE);

	SCROLL(2,0,"What artifact dost thou conjure?");
	general_low_sound();

	win.x1=17;
	win.y1=6;
	win.x2=29;
	win.y2=13;
	win.back=0;
	win.border=3;

	make_gwindow(&win);

	print_menu_options(t,
					   SIZE(t),
					   t2,
					   win.x1+1,win.y1+1,
					   7,
					   11);

	opt=mouse_in_range(boundary,t2,"");

	kill_gwindow(&win);

	if (opt!=4)
	{
		if (!enough_spell_points_to_cast(adv,2))
			return(FALSE);

		sprintf(temp,"%s rubs %s hands slowly..",adv->name,adv->his_her);
		print_spell_description(temp);

		res=TRUE;
	}

	switch(opt)
	{
		case 0 : if (adv->darts>=MAX_DARTS)
				 {
					too_much=TRUE;
				 }
				 else
				 {
					adv->darts+=qty[opt];
					adv->darts=min(adv->darts,MAX_DARTS);
				 }

				 break;

		case 1 : if (adv->arrows>=MAX_ARROWS)
				 {
					too_much=TRUE;
				 }
				 else
				 {
					adv->arrows+=qty[opt];
					adv->arrows=min(adv->arrows,MAX_ARROWS);
				 }

				 break;

		case 2 : if (adv->quarrels>=MAX_QUARRELS)
				 {
					too_much=TRUE;
				 }
				 else
				 {
					adv->quarrels+=qty[opt];
					adv->quarrels=min(adv->quarrels,MAX_QUARRELS);
				 }

				 break;

		case 3 : if (adv->oil>=MAX_OIL)
				 {
					too_much=TRUE;
				 }
				 else
				 {
					adv->oil+=qty[opt];
					adv->oil=min(adv->oil,MAX_OIL);
				 }

				 break;

		default: res=FALSE;
				 break;
	}

	if (res)
	{
		if (too_much)
		{
			sprintf(temp,"%s hath enough %s already!",adv->name,t[opt]);
			SCROLL(1,0,temp);
			bad_sound();
		}
		else
		{
			sprintf(temp,"..and %s appear in %s hands...!",t[opt],adv->his_her);
			SCROLL(1,14,temp);
			good_sound();
		}
	}

	return(res);
}

/************************************************************************/

int _PASCAL cast_MIRAGE(PLAYER *adv,SPELL_NAME *spell_name)
{
	int res=FALSE;
	char temp[120];

	if (cast_spell_correct_situation(adv,spell_name,NON_COMBAT_SPELL))
	{
		if (enough_spell_points_to_cast(adv,3))
		{
			res=TRUE;

			adv->in_effect.mirage+=adv->level*4;

			sprintf(temp,"%s wiggles an index finger at thy party "
						 "members...and one by one they fade!",
						 adv->name);

			print_spell_description(temp);
		}
	}

	return(res);
}
