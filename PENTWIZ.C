#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include "butil.h"
#include "bkeybrd.h"
#include "turbo.h"

void _PASCAL handle_wizard_mode()
{
	GWINDOW win;
	int i;
	KEYSTATUS kstat;

	(void)kbstatus(&kstat);

	if (kstat.num_state &&
		 !IN_COMBAT &&
		 (party_next_to(SEA) || party_next_to(WATER)))
	{
		win.x1=4;
		win.y1=4;
		win.x2=26;
		win.y2=19;
		win.back=0;
		win.border=9;

		make_gwindow(&win);

		wizard_mode=(wizard_mode?FALSE:TRUE);

		generic_pic_draw(win.x1*8+2,win.y1*8,wizard_mode?"WM_N":"WM_F");

		if (!NO_SOUND)
		{
			for (i=0; i<10; i++)
			{
				utspkr(150+(wizard_mode*20));
				delay(50);
				utspkr(120+(wizard_mode*20));
				delay(50);
			}
		}

		utspkr(0);

		pause(2);

		kill_gwindow(&win);
	}
}
