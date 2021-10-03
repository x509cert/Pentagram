#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <ctype.h>
#include <bkeybrd.h>

static SIGNPOSTS signdata[]=
{
		41,121,
		"",
		"\"Ignore this misleading Sign, but don't forget to worship regularly!\"",

		146, 78,
		"",
		"\"Northwards lie ye Teardrop Mts, so called due to their distinctive tear shape. Ancient Lore says they were formed from ye tears of laughter shed by Morr, Lady of Death, upon witnessing bloodshed in Ye Realms.\"",

		70, 82,
		"",
		"\"Northwards lie ye Fang Mountains, named by Lord Gallum, first mayor of Wolfburg, upon sighting ye two snow-capped peaks.\"",

		90,194,
		"",
		"\"Welcome to Lizards Point, ye most Southerly tip of Ye Realms.\"",

		105,7,
		"",
		"\"Welcome to Ice Point, ye most Northerly point of Ye Realms.\"",

		62,92,
		"Wolfsway and Northwest Rd.",
		"\"NE to Wolfburg and ye Fang Mts. W to Sea Pt. S to Riverdawn, Tiravel and Riverneck. SE to Kaitlin and Kanraith. E to Mist Pt.\"",

		70,112,
		"Great East-West Rd and Traitors Rd.",
		"\"N to Wolfburg and ye Fang Mts. NW to Sea Pt. S to Riverdawn. E to Riverneck, Tiravel, Kaitlin, Kanraith and Mist Pt.\"",

		115,113,
		"Great East-West Rd and Southernway",
		"\"W to Wolfburg, Riverdawn, Sea Pt and ye Fang Mts. S to Riverneck, Tiravel, Kaitlin, and Kanraith. E to Mist Pt.\"",

		113,131,
		"Old North-South Rd",
		"\"N to Wolfburg, Mist Pt., Riverdawn and ye Fang Mts. NW to Sea Pt. W to Riverneck, Tiravel and Kaitlin.\"",

		58,150,
		"Old South lane",
		"\"E to Wolfburg, Sea Pt., Riverdawn, Kaitlin, Kanraith, Mist Pt and ye Fang Mts. W to Riverneck. S to Tiravel.\"",

		140,163,
		"",
		"\"Murder Crossroads. Here ye deranged necromancer, Kaldrutha, acquired cadavers for her demented rituals by slitting ye throats of tired travellers!\"",

		73,13,
		"Old Greatwood Lane",
		"\"SW to Greatwood and NW to Frosthaven.\"",

		122,22,
		"Ye Old Forsaken Road",
		"\"S to ye tranquil village of Erihn.\"",

		172,35,
		"Ye Old Man Road",
		"\"S to Rayek. N to Angharad.\"",

		127,78,
		"Ye One Stride Lane.",
		"\"N to North Rhyde and S to South Rhyde.\"",

		167,153,
		"Chillfrost Road.",
		"\"SE to Minash and N to Dun Cirach.\"",

		170,48,
		"",
		"\"Beware: Thou art venturing into Fools Valley, gateway to ye Encircling Mts. N art Hells Vault.\"",

		107,90,
		"",
		"\"Korina's Leap: At this cliff edge, ye famed illusionist, Korina, met her death after a squabble with her lover!\""
};

void _PASCAL divulge_signpost_info(int x,int y)
{
	int i;
	int sign_num=ERR;

	for (i=0; i<SIZE(signdata); i++)
		if (x==signdata[i].x && y==signdata[i].y)
			sign_num=i;

	kbflush();

	SCROLL(2,14,"Ye wooden signpost reads..");
	scroll_scroll();

	if (strlen(signdata[sign_num].sign_title))
		scroll_wrap_write(1,signdata[sign_num].sign_title);

	if (strlen(signdata[sign_num].message))
		scroll_wrap_write(14,signdata[sign_num].message);

	general_low_sound();
}
