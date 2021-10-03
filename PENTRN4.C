#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _CDECL enter_ruin_dreadhorn()
{
	int person=get_random_live_person();
	char temp[120];

	SCROLL(2,1,"Slowly, Thy party ventures across ye broken "
			   "drawbridge of ye ruins of Castle Dreadhorn.");

	general_low_sound();
	pause(3);

	SCROLL(1,1,"Time hath taken its toll greatly on ye ruins - and "
			   "naught stirs now. Exhaustive searching by thy "
			   "party proves ye folktale that Orc clans now "
			   "possess all treasures kept hidden in Dreadhorn.");

	general_low_sound();
	pause(4);

	if (person!=ERR)
	{
		if (percent()>effective_disease_immunity(&TPP[person]))
			contract_pox(&TPP[person]);

		reduce_hp(&TPP[person],1,FROM_FRIGHT);

		if (player_is_alive(&TPP[person]))
		{
			sprintf(temp,"Upon leaving, some brown slime falls from ye "
						 "castle gateway above and drops on %s!",
						 TPP[person].name);

			SCROLL(1,0,temp);

			bad_sound();
			pause(4);

			SCROLL(1,1,"Happily, ye slime falls away and seeps into "
					   "ye ground below thy party!");

			good_sound();
		}
	}
}
