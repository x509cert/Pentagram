#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

static char _FAR *provinces[]={ /* A */ "IN YE DISTRICT OF ICE MOOR",
								/* B */ "IN YE COUNTY OF FROSTMOOR",
								/* C */ "IN YE PROVINCE OF SANKRIST",
								/* D */ "IN YE DISTRICT OF MITHLAND",
								/* E */ "IN YE PROVINCE OF FELGEDDEN",
								/* F */ "IN YE COUNTY OF WILDERLAND",
								/* G */ "IN YE DISTRICT OF HARTLAND",
								/* H */ "IN YE COUNTY OF STONELAND",
								/* I */ "IN YE PROVINCE OF WHITEMOOR",
								/* J */ "IN YE DISTRICT OF CUMHAIL",
								/* K */ "IN YE PROVINCE OF WESTERLANT",
								/* L */ "IN YE COUNTY OF EAGLECREST",
								/* M */ "IN YE DISTRICT OF MIDLANT",
								/* N */ "IN YE COUNTY OF ESROTH",
								/* O */ "IN YE PROVINCE OF EASTERLANT",
								/* P */ "IN YE DISTRICT OF ANDIR",
								/* Q */ "IN YE PROVINCE OF THORNBARREN",
								/* R */ "IN YE COUNTY OF REDMOOR",
								/* S */ "IN YE DISTRICT OF ELFWALD",
								/* T */ "IN YE COUNTY OF KUNOTH",
								/* U */ "ON YE THREE TRAITORS ISLANDS",
								/* V */ "IN YE DISTRICT OF SOUTHERLANT",
								/* W */ "IN YE PROVINCE OF LOWERHEATH",
								/* X */ "IN YE COUNTY OF BEOHELM",
								/* Y */ "IN YE DISTRICT OF MAERWULF"
							  };

char *get_province(int x,int y)
{
	int xoff,yoff;

	xoff=x/40;
	yoff=y/40;

	return(provinces[xoff+(yoff*5)]);
}
