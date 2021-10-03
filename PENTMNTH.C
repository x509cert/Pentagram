#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL evaluate_interest()
{
	long ltoday,lvisit;

	ltoday=(long)((long)pent_data.year*DAYS_PER_YEAR
				+ (long)pent_data.date);

	lvisit=(long)((long)pent_data.year_visit_wolfburg*DAYS_PER_YEAR
				+ (long)pent_data.date_visit_wolfburg);

	if (ltoday-lvisit >= BANK_INTEREST_THRESHOLD)
		end_of_month_interest();
}

static void _PASCAL _NEAR end_of_month_interest()
{
	int i;
	char file_name[30];
	FILE *fptr;
	unsigned long total=0L;
	char temp[90];

	for (i=0; i<MAX_ON_DISC; i++)
	{
		sprintf(file_name,ADV_PREFIX,i);

		if ((fptr=fopen(file_name,"rb"))!=NULL)
		{
			fread(&adv,sizeof(PLAYER),1,fptr);
			fclose(fptr);

			total+=get_interest_earned_and_update(&adv);

			save_adventurer(&adv);
		}
	}

	if (total!=0L)
	{
		sprintf(temp,"Thy party members earn %lu gc interest during ye past month!",total);
		SCROLL(1,14,temp);
		good_sound();

		pause(3);
	}
}

static unsigned long _NEAR get_interest_earned_and_update(PLAYER *adv)
{
	unsigned long interest,amount;

	if (adv->banked==0L)
		return(0L);

	if (adv->banked<999L)
		interest=10L;
	else
	if (adv->banked<9999L)
		interest=11L;
	else
	if (adv->banked<99999L)
		interest=12L;
	else
		interest=13L;

	amount=((adv->banked*interest)/100L)/12L;
	adv->banked+=amount;

	if (amount==0L)
		amount=1L;

	return(amount);
}
