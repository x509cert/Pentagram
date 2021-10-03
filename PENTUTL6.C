#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <string.h>

int _PASCAL show_determine_spells(PLAYER *adv)
{
	int i,num_spells;

	num_spells=0;

	memset(adv_spells,0,sizeof(adv_spells));

	for (i=0; i<LAST_WIZARD; i++)
		if (adv->wizard_spells[wiz_spell_names[i].name]!=NO_SPELL)
		{
			adv_spells[num_spells].descrip=wiz_spell_names[i].descrip;
			adv_spells[num_spells].name   =wiz_spell_names[i].name;

			num_spells++;
		}

	for (i=0; i<LAST_ILLUSIONIST; i++)
		if (adv->illusionist_spells[ill_spell_names[i].name]!=NO_SPELL)
		{
			adv_spells[num_spells].descrip=ill_spell_names[i].descrip;
			adv_spells[num_spells].name   =ill_spell_names[i].name;

			num_spells++;
		}

	for (i=0; i<LAST_DRUID; i++)
		if (adv->druid_spells[dru_spell_names[i].name]!=NO_SPELL)
		{
			adv_spells[num_spells].descrip=dru_spell_names[i].descrip;
			adv_spells[num_spells].name   =dru_spell_names[i].name;

			num_spells++;
		}

	for (i=0; i<LAST_PRIEST; i++)
		if (adv->priest_spells[pri_spell_names[i].name]!=NO_SPELL)
		{
			adv_spells[num_spells].descrip=pri_spell_names[i].descrip;
			adv_spells[num_spells].name   =pri_spell_names[i].name;

			num_spells++;
		}

	if (num_spells!=0)
		qsort(&adv_spells[0],
			  num_spells,
			  sizeof(SPELL_NAME),
			  show_determine_spells_sort);

	return(num_spells);
}

#ifndef DEV
#pragma intrinsic(strcmp)
#endif

int _CDECL show_determine_spells_sort(SPELL_NAME *s1,SPELL_NAME *s2)
{
	return(strcmp(s1->descrip,s2->descrip));
}
