#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")
#include <butil.h>
#include <turbo.h>

void _PASCAL general_low_sound()
{
	if (NO_SOUND)
		return;

	utspkr(100);
	delay(50);
	utspkr(0);
}

void _PASCAL short_prompt_sound()
{
	if (NO_SOUND)
		return;

	utspkr(200);
	delay(25);
	utspkr(150);
	delay(20);
	utspkr(0);
}

void _PASCAL wake_up_sound()
{
	if (NO_SOUND)
		return;

	utspkr(200);
	delay(25);
	utspkr(150);
	delay(20);

	utspkr(300);
	delay(25);
	utspkr(250);
	delay(20);

	utspkr(0);
}

void _PASCAL cast_MINDS_EYE_make_sound()
{
	if (NO_SOUND)
		return;

	utspkr(700);
	delay(10);
	utspkr(1000);
	delay(10);
	utspkr(0);
}

void _PASCAL found_talisman_bit_sound()
{
	int i;
	int t;
	int diff;
	static int music[]={179,239,319,
						239,319,358,
						319,358,426,
						239,319,358,
						179,239,319};
	if (NO_SOUND)
		return;

	delay(1);

	for (i=0; i<SIZE(music); i++)
	{
		t=music[i];
		diff=(t/5);
		t+=diff;

		utspkr(t);
		delay(170);
		utspkr(0);
		delay(10);
	}

	utspkr(0);
}

void _PASCAL HOE_sound()
{
	int i;
	static int music[]={
							1, 1760, 120,
							1, 1396, 120,
							1, 1174, 120,
							1, 1760, 120,
							1, 1567, 120,
							1, 1318, 120,
							1, 1760, 120,
							1, 1318, 120,
							1, 1760, 120,
							1, 1396, 120,
							1, 1174, 120,
							1, 1760, 120,
							1, 1567, 120,
							1, 1318, 120,
							1, 1760, 120,
							1, 1318, 120,
							1, 1760, 240,
							1, 1396, 240,
							1, 1174, 240,
							1, 1760, 240,
							1, 1567, 240,
							1, 1318, 240,
							1, 1046, 240,
							1, 1567, 240,
							1, 1396, 240,
							1, 1174, 240,
							1, 987,  240,
							1, 783,  240,
							1, 659,  240,
					   };

	if (NO_SOUND)
		return;

	for (i=0; i<sizeof(music)/sizeof(music[0]); i+=3)
	{
		utspkr(music[i+1]);
		delay(music[i+2]);
		utspkr(0);
		delay(10);
	}
}

void _PASCAL stairs_up_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=100; i<=400; i+=100)
	{
		utspkr(i);
		delay(150);
		utspkr(0);
		delay(50);
	}

	utspkr(0);
}

void _PASCAL sink_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=7500; i>=100; i-=50)
	{
		utspkr(i);
		delay(4);
	}

	utspkr(0);
}

void _PASCAL stairs_down_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=400; i>=100; i-=100)
	{
		utspkr(i);
		delay(150);
		utspkr(0);
		delay(50);
	}

	utspkr(0);
}

void _PASCAL voice_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=0; i<2; i++)
	{
		utspkr(500);
		delay(30);
		utspkr(1000);
		delay(50);
	}

	utspkr(0);
}

void _PASCAL incidental_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=0; i<2; i++)
	{
		utspkr(200);
		delay(30);
		utspkr(800);
		delay(50);
	}

	utspkr(0);
}

void _PASCAL treasure_sound()
{
	int i,j;

	delay(1);

	if (NO_SOUND)
		return;

	for (j=5; j<35; j+=3)
		for (i=500; i<=1800; i+=j)
		{
			utspkr(i);
			delay(2);
		}

	utspkr(0);
}

void _PASCAL trap_sound()
{
	int i;

	delay(0);

	if (NO_SOUND)
		return;

	for (i=160; i>25; i-=2)
	{
		utspkr(i);
		delay(20);
	}

	delay(40);

	utspkr(0);
}

void _PASCAL spell_sound()
{
	int i;

	delay(0);

	if (NO_SOUND)
		return;

	for (i=1500; i>40; i-=35)
	{
		utspkr(i);
		delay(7);
		utspkr(0);
	}
}

void _PASCAL staff_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=0; i<55; i++)
	{
		utspkr(400+(i*5));
		delay(4);
		utspkr(400-(i*5));
		delay(4);
	}

	utspkr(0);
}

void _PASCAL wand_sound()
{
	int i,j;

	if (NO_SOUND)
		return;

	for (j=0; j<3; j++)
	{
		for (i=1500; i>40; i-=35)
		{
			utspkr(i);
			delay(3);
			utspkr(0);
		}
	}
}

void _PASCAL short_bad_sound()
{
	if (NO_SOUND)
		return;

	utspkr(50);
	delay(35);
	utspkr(35);
	delay(75);
	utspkr(0);
}

void _PASCAL bad_sound()
{
	if (NO_SOUND)
		return;

	utspkr(50);
	delay(75);
	utspkr(35);
	delay(150);
	utspkr(0);
}

void _PASCAL bad_sound2()
{
	if (NO_SOUND)
		return;

	utspkr(200);
	delay(70);
	utspkr(100);
	delay(70);
	utspkr(0);
}

void _PASCAL good_sound()
{
	if (NO_SOUND)
		return;

	utspkr(800);
	delay(70);
	utspkr(1100);
	delay(70);
	utspkr(0);
}

void _PASCAL death_sound()
{
	if (NO_SOUND)
		return;

	utspkr(60);
	delay(175);
	utspkr(40);
	delay(175);
	utspkr(20);
	delay(200);
	utspkr(0);
}

void _PASCAL solemn_sound()
{
	if (NO_SOUND)
		return;

	utspkr(20);
	delay(500);
	utspkr(0);
}

void _PASCAL snotling_sound()
{
	if (NO_SOUND)
		return;

	utspkr(35);
	delay(150);
	utspkr(20);
	delay(250);

	utspkr(0);
}

void _PASCAL use_item_sound()
{
	if (NO_SOUND)
		return;

	utspkr(500);
	delay(20);
	utspkr(700);
	delay(20);
	utspkr(1000);
	delay(20);

	utspkr(0);
}

void _PASCAL lute_sound()
{
	use_item_sound();
}

void _PASCAL advance_level_sound()
{
	int i,j;

	if (NO_SOUND)
		return;

	for (j=0; j<2; j++)
	{
		for (i=0; i<3; i++)
		{
			utspkr(600+(i*50));
			delay(90);
		}

		utspkr(0);
		delay(100);
	}

	utspkr(0);
}

void _PASCAL teleport_up_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=10; i<=5000; i+=6)
	{
		utspkr(i);
		delay(2);
	}

	utspkr(0);
}

void _PASCAL teleport_down_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=5000; i>10; i-=6)
	{
		utspkr(i);
		delay(2);
	}

	utspkr(0);
}

void _PASCAL symptoms_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=0; i<3; i++)
	{
		utspkr(99-(i*40));
		delay(200+(i+1)*90);
	}

	utspkr(0);
}

void _PASCAL potion_sound()
{
	if (NO_SOUND)
		return;

	utspkr(200);
	delay(80);
	utspkr(400);
	delay(90);
	utspkr(500);
	delay(111);

	utspkr(0);
}

void _PASCAL all_dead_sound()
{
	if (NO_SOUND)
		return;

	utspkr(50);
	delay(400);
	utspkr(30);
	delay(450);
	utspkr(10);
	delay(550);

	utspkr(0);
}

void _PASCAL spell_finished_sound()
{
	if (NO_SOUND)
		return;

	utspkr(100);
	delay(30);
	utspkr(0);
}

void _PASCAL mouse_sound()
{
	if (NO_SOUND)
		return;

	utspkr(1000);
	delay(20);
	utspkr(1600);
	delay(20);
	utspkr(0);
}

void _PASCAL flee_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=1000; i<13000; i+=750)
	{
		utspkr(i);
		delay(10);
	}

	utspkr(0);
}

void _PASCAL encounter_sound()
{
	if (NO_SOUND)
		return;

	utspkr(300);
	delay(150);

	utspkr(300);
	delay(150);

	utspkr(300);
	delay(150);

	utspkr(400);
	delay(333);

	utspkr(0);
}

void _PASCAL hit_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=0; i<27; i++)
	{
		utspkr(rand()%580+20);
		delay(3);
	}

	utspkr(0);
}

void _PASCAL move_monster_sound()
{
	if (NO_SOUND)
		return;

	utspkr(1000);
	delay(30);
	utspkr(0);
}

void _PASCAL move_player_sound()
{
	if (NO_SOUND)
		return;

	utspkr(1200);
	delay(30);
	utspkr(0);
}

void _PASCAL click_sound()
{
	if (NO_SOUND)
		return;

	utspkr(500);
	delay(20);
	utspkr(0);
}

void _PASCAL combat_death_sound()
{
	int i;

	if (NO_SOUND)
		return;

	for (i=0; i<100; i++)
	{
		utspkr(rand()%(580-i*5)+20);
		delay(4);
	}

	utspkr(0);
}

void _PASCAL victory_sound()
{
	int i,j,t,diff;
	static int notes[]={239,338,284,451};

	if (NO_SOUND)
		return;

	for (j=0; j<2; j++)
	{
		for (i=0; i<SIZE(notes); i++)
		{
			t=notes[i];
			diff=(t/5);
			t+=diff;

			utspkr(t);
			delay(170);
			utspkr(0);
			delay(10);
		}
	}

	utspkr(338+338/5);
	delay(100);
	utspkr(0);
}

void _PASCAL pray_sound()
{
	int i,t;
	int diff;
	static int music[]={319,239,319,
						239,319,358,
						319,358,319};

	if (NO_SOUND)
		return;

	for (i=0; i<sizeof(music)/sizeof(music[0]); i++)
	{
		t=music[i]*2;
		diff=(t/5);
		t+=diff;
		
 		utspkr(t);
		delay(60);
		utspkr(t*2);
		delay(60);

		utspkr(0);
		delay(10);
	}

	utspkr(0);
}

void _PASCAL next_round_sound()
{
	if (NO_SOUND)
		return;

	utspkr(100);
	delay(100);
	utspkr(200);
	delay(80);
	utspkr(300);
	delay(60);
	utspkr(0);
}

void _PASCAL game_finished_sound()
{
	int i;
	static int notes[]={174,4, 196,2, 220,2,
						220,2, 196,2, 174,2, 164,2,
						146,2, 146,2, 164,2, 174,2,
						174,1, 164,1, 164,4,

						174,2, 174,2, 196,2,  220,2,
						220,2, 196,2, 174,2, 164,2,
						146,2, 146,2, 164,2, 174,2,

						164,1, 146,1, 146,4,
						164,4, 174,2, 146,2,
						164,2, 174,1, 196,1, 174,2, 146,2,

						164,2, 174,1, 196,1, 174,2, 164,2,
						146,2, 164,2, 110,2, 174,2,

						174,2, 174,2, 196,2, 220,2,
						220,2, 196,2, 174,2, 164,2,
						146,2, 146,2, 164,2, 174,2,
						164,1, 146,1, 146,4,

						349,4, 392,2, 440,2,
						440,2, 392,2, 349,2, 329,2,
						293,2, 293,2, 329,2, 349,2,
						349,1, 329,1, 329,4,

						349,4, 392,2, 440,2,
						440,2, 392,2, 349,2, 329,2,
						293,2, 293,2, 329,2, 349,2,
						349,1, 329,1, 329,4,

						329,4, 349,2, 293,2,
						329,2, 349,1, 392,1, 349,2, 293,2,
						329,2, 349,1, 392,1, 349,2, 329,2,
						293,2, 329,2, 220,2, 349,2,

						349,2, 349,2, 392,2, 440,2,
						440,2, 392,2, 349,2, 329,2,
						293,2, 293,2, 329,2, 349,2,
						329,1, 293,1, 293,1, 440,1, 392,1, 349,1,

						329,4, 349,2, 293,2,
						329,2, 349,1, 392,1, 349,2, 293,2,
						329,2, 349,1, 392,1, 349,2,329,2,
						293,2, 329,2, 220,2, 349,2,

						349,2, 349,2, 392,2, 440,2,
						440,2, 392,2, 349,2, 329,2,
						293,2, 293,2, 329,2, 349,2,
						329,1, 293,1, 293,2,
						};

	if (NO_SOUND)
		return;

	for (i=0; i<sizeof(notes)/sizeof(notes[0]); i+=2)
	{
		utspkr(notes[i]*4);
		delay(notes[i+1]*200);
		utspkr(0);
		delay(10);
	}
}

void _PASCAL korinas_leap_sound()
{
	int i;

	if (!NO_SOUND)
	{
		for (i=0; i<2; i++)
		{
			utspkr(900);
			delay(50);
			utspkr(0);
			delay(30);
		}
	}

}
