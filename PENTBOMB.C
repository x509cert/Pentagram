#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#ifdef BOMB

#include <string.h>
#include <time.h>

#pragma optimize("",off)

static char *bumf="pqrstadcbeth'!klsf~@o";

void _PASCAL BOMB_check()
{
	struct tm *t;
	time_t timer=time(NULL);
	int month=3+2;
	int year=(45*2)+1;
	static char temp[30];

	t=localtime(&timer);

	if (t->tm_mon>=month && t->tm_year>=year)
	{
		memset(temp,0,sizeof(temp));

		temp[0] =bumf[10];  /* T */
		temp[1] =bumf[11];  /* h */
		temp[2] =bumf[5];   /* a */
		temp[3] =bumf[10];  /* t */
		temp[4] =bumf[16];  /* s */
		temp[5] =' ';       /*   */
		temp[6] =bumf[5];   /* a */
		temp[7] =bumf[15];  /* l */
		temp[8] =bumf[15];  /* l */
		temp[9] =' ';       /*   */
		temp[10]=bumf[17];  /* f */
		temp[11]=bumf[20];  /* o */
		temp[12]=bumf[15];  /* l */
		temp[13]=bumf[14];  /* k */
		temp[14]=bumf[16];  /* s */
		temp[15]=bumf[13];  /* ! */

		strupr(temp);

		panic(temp);
	}
}

#endif
