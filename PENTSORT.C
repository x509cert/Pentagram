#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

void _PASCAL sort_adv_items(PLAYER *adv)
{
	qsort(adv->items_carried,MAX_CARRY,sizeof(ITEM_POOL),sort_comp);
}

void _PASCAL sort_pool_items(int num_items)
{
	qsort(&pool[0],num_items,sizeof(ITEM_POOL),sort_comp);
}

int _PASCAL sort_items_value(ITEM_POOL *item)
{
	int value=NOTHING;

	if (item->item==NOTHING || item->item==-1)
	{
		return(NOTHING);
	}
	else
	if (item->item==POTION)             /* Allows potions to come  */
	{                                   /* after other magic items */
		value=item->item+item->type;    /* As they use the same    */
	}                                   /* numbers as +1,+2 etc    */
	else
	{
		switch(item->type)
		{
			case PLUS_1 : value=item->item+1; break;
			case PLUS_2 : value=item->item+2; break;
			case PLUS_3 : value=item->item+3; break;
			default     : value=item->item;   break;
		}
	}

	return(value);
}

int _CDECL sort_comp(ITEM_POOL *c1,ITEM_POOL *c2)
{
	int v1=sort_items_value(c1);
	int v2=sort_items_value(c2);

	if (v1<v2)
		return(-1);
	else
	if (v1==v2)
		return(0);
	else
		return(1);
}
