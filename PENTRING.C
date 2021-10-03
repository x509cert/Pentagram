#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

int _PASCAL use_ring_of_fire(PLAYER *adv)
{
	if (bard_is_singing(adv,"use a ring"))
		return(FALSE);

	if (!IN_COMBAT)
	{
		SCROLL(1,0,"Ye canst use a Ring of Fire only in combat!");
		bad_sound();

		return(FALSE);
	}

	return(actually_use_ring(adv,RING_OF_FIRE));
}

int _PASCAL use_ring_of_icicles(PLAYER *adv)
{
	if (bard_is_singing(adv,"use a ring"))
		return(FALSE);

	if (!IN_COMBAT)
	{
		SCROLL(1,0,"Ye canst use a Ring of Icicles only in combat!");
		bad_sound();

		return(FALSE);
	}

	return(actually_use_ring(adv,RING_OF_ICICLES));
}
