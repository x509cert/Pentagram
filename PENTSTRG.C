#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

char  *STR_LEATHER_ARMOUR		 ="Leather Armour";
char  *STR_SPLINT_ARMOUR		 ="Splint Armour";
char  *STR_CHAIN_ARMOUR 		 ="Chain Armour";
char  *STR_PLATE_ARMOUR 		 ="Plate Armour";
char  *STR_ELF_ARMOUR			 ="Elven Armour";

char  *STR_DAGGER				 ="Dagger";
char  *STR_AXE					 ="Battle Axe";
char  *STR_SHORT_SWORD			 ="Short Sword";
char  *STR_LONG_SWORD			 ="Long Sword";
char  *STR_RAPIER				 ="Rapier";
char  *STR_CLAYMORE 			 ="Claymore";
char  *STR_MACE 				 ="Footman's Mace";
char  *STR_FLAIL				 ="Footman's Flail";
char  *STR_BOW					 ="Long Bow";
char  *STR_CROSSBOW 			 ="Crossbow";
char  *STR_HALBERD				 ="Halberd";
char  *STR_SLING				 ="Sling";
char  *STR_DARTS				 ="Darts";
char  *STR_ARROWS				 ="Arrows";
char  *STR_QUARRELS 			 ="Quarrels";

char  *STR_SACK 				 ="Hessian Sack";
char  *STR_BACK_PACK			 ="Backpack";
char  *STR_TINDER_BOX			 ="Tinder-box";
char  *STR_HEAVY_CLOAK			 ="Heavy Cloak";
char  *STR_HOODED_LANTERN		 ="Hooded Lantern";
char  *STR_THIEVES_TOOLS		 ="Thieves Tools";
char  *STR_RELIGIOUS_SYMBOL 	 ="Religious Symbol";
char  *STR_SEXTANT				 ="Sextant";
char  *STR_SMALL_SHIELD 		 ="Small Shield";
char  *STR_MEDIUM_SHIELD		 ="Medium Shield";
char  *STR_LARGE_SHIELD 		 ="Large Shield";
char  *STR_HELMET				 ="Metal Helmet";

char  *STR_WYVERN_RING			 ="Wyvern Ring";
char  *STR_DRAGON_RING			 ="Dragon Ring";
char  *STR_RING_OF_HEALING		 ="Ring of Healing";
char  *STR_MIND_SHIELD_RING 	 ="Mind Shield Ring";
char  *STR_RING_OF_FIRE 		 ="Ring of Fire";
char  *STR_RING_OF_ICICLES		 ="Ring of Icicles";
char  *STR_RING_OF_SWIMMING 	 ="Ring of Swimming";
char  *STR_WARMTH_RING			 ="Warmth Ring";

char  *STR_THUNDER_WAND 		 ="Thunder Wand";
char  *STR_ICE_WAND 			 ="Ice Wand";
char  *STR_FIRE_WAND			 ="Fire Wand";
char  *STR_HEALING_STAVE		 ="Healing Stave";
char  *STR_SUSTENANCE_WAND		 ="Sustenance Wand";
char  *STR_DEVOURING_ROD		 ="Rod of Devouring";
char  *STR_CURIOUS_BOX			 ="Curious Metal Box";

char  *STR_ORB_TITAN			 ="Orb of Titan";
char  *STR_ORB_DEXTERITY		 ="Orb of Dexterity";
char  *STR_ORB_WISE 			 ="Orb of ye Wise";
char  *STR_ORB_FORTUNE			 ="Orb of Fortune";
char  *STR_ORB_MEDITATION		 ="Orb of Meditation";
char  *STR_ORB_STAMINA			 ="Orb of Stamina";
char  *STR_ORB_BEAUTY			 ="Orb of Beauty";

char  *STR_RELIC				 ="Ancient Relic";
char  *STR_TOME 				 ="Ancient Tome";
char  *STR_ELFIN_CLOAK			 ="Elven Cloak";
char  *STR_BRACERS_POISON		 ="Bracers of Poison";
char  *STR_PENDANT_HEALTH		 ="Pendant of Health";
char  *STR_ELFIN_BOOTS			 ="Elven Boots";
char  *STR_GLOVES_NIMBLENESS	 ="Gloves of Nimbleness";
char  *STR_LUTE 				 ="Bard's Lute";
char  *STR_GRIMOIRE 			 ="Dusty Grimoire";

char  *STR_DRAGONFLAME1 		 ="Dragonflame I";
char  *STR_HAMMERHAND			 ="Hammerhand";
char  *STR_ARC_LIGHTNING1		 ="Arc Lightning I";
char  *STR_FIND_HIDDEN_DOOR 	 ="Find Hidden Door";
char  *STR_GRAVMUR_RAGE 		 ="Gravmur's Rage";
char  *STR_FROZEN_WIND1 		 ="Frozen Wind I";
char  *STR_FIRE_MIST			 ="Fire Mist";
char  *STR_MIGHTY_APPEARANCE	 ="Mighty Appearance";
char  *STR_DRAGONFLAME2 		 ="Dragonflame II";
char  *STR_LETHARGY 			 ="Lethargy";
char  *STR_SWIFTNESS			 ="Swiftness";
char  *STR_ARC_LIGHTNING2		 ="Arc Lightning II";
char  *STR_DISPEL_TRAP			 ="Dispel Trap";
char  *STR_SINK 				 ="Sink";
char  *STR_BLINDING_FLASH		 ="Blinding Flash";
char  *STR_FROZEN_WIND2 		 ="Frozen Wind II";
char  *STR_DRAGONFLAME3 		 ="Dragonflame III";
char  *STR_ARC_LIGHTNING3		 ="Arc Lightning III";
char  *STR_DEATH_CURSE			 ="Death Curse";
char  *STR_BIND_DEMON			 ="Bind Demon";
char  *STR_TELEPORT 			 ="Teleport";
char  *STR_FROZEN_WIND3 		 ="Frozen Wind III";
char  *STR_INVOKE_FAMILIAR		 ="Invoke Familiar";

char  *STR_TWILIGHT              ="Twilight";
char  *STR_NEUTRALISE_POISON	 ="Neutralise Poison";
char  *STR_PROT_FROM_COLD		 ="Protection from Cold";
char  *STR_PROT_FROM_FIRE		 ="Protection from Fire";
char  *STR_CURE_LIGHT_INJURY	 ="Cure Light Injury";
char  *STR_CAUSE_LIGHT_INJURY	 ="Cause Light Injury";
char  *STR_HOLY_SPRAY			 ="Holy Spray";
char  *STR_DUNGEON_DIVINATION	 ="Dungeon Divination";
char  *STR_OPEN_CHEST			 ="Open Chest";
char  *STR_REMOVE_CURSE 		 ="Remove Curse";
char  *STR_CURE_DISEASE 		 ="Cure Disease";
char  *STR_CURE_SEVERE_INJURY	 ="Cure Severe Injury";
char  *STR_DISRUPTION			 ="Disruption";
char  *STR_CAUSE_SEVERE_INJURY	 ="Cause Severe Injury";
char  *STR_BLADES				 ="Blades";
char  *STR_PROT_FROM_TRAPS		 ="Protection from Traps";
char  *STR_RESURRECT			 ="Resurrect";
char  *STR_CURE_CRITICAL_INJURY  ="Cure Critical Injury";
char  *STR_CAUSE_CRITICAL_INJURY ="Cause Critical Injury";
char  *STR_SPELL_OF_PASSAGE 	 ="Spell of Passage";
char  *STR_MISSILE_CLOAK		 ="Missile Cloak";

char  *STR_HORRIFY				 ="Horrify";
char  *STR_SLY_EARS 			 ="Sly Ears";
char  *STR_CATS_EYES			 ="Cat's Eyes";
char  *STR_PHANTASM1             ="Phantasm I";
char  *STR_STAR_FLARE			 ="Star Flare";
char  *STR_AXELS_BLUR			 ="Axel's Blur";
char  *STR_ALLYS_DANCING_DAGGER  ="Ally's Dancing Dagger";
char  *STR_JONAS_SPOOK			 ="Jonas' Spook";
char  *STR_KORINAS_LEAP 		 ="Korina's Leap";
char  *STR_PHANTASM2             ="Phantasm II";
char  *STR_MOON_FLARE			 ="Moon Flare";
char  *STR_CREATE_ARTIFACTS 	 ="Create Artifacts";
char  *STR_AXELS_SHIMMER		 ="Axel's Shimmer";
char  *STR_ALLYS_DANCING_MACE	 ="Ally's Dancing Mace";
char  *STR_AXELS_SHADOW 		 ="Axel's Shadow";
char  *STR_MIRAGE                ="Mirage";
char  *STR_PHANTASM3             ="Phantasm III";
char  *STR_SUN_FLARE			 ="Sun Flare";
char  *STR_SUSPEND_TIME 		 ="Suspend Time";
char  *STR_ALLYS_DANCING_SABRE	 ="Ally's Dancing Sabre";

char  *STR_TRUEFLIGHT			 ="Trueflight";
char  *STR_WALK_ON_WATER		 ="Walk on Water";
char  *STR_FLAME_SHEET			 ="Flame Sheet";
char  *STR_RAZOR_LEAVES1		 ="Razor Leaves I";
char  *STR_POISON_IMMUNITY		 ="Poison Immunity";
char  *STR_PLANT_FEAST			 ="Plant Feast";
char  *STR_AURA_OF_PROTECTION	 ="Aura of Protection";
char  *STR_RAZOR_LEAVES2		 ="Razor Leaves II";
char  *STR_TANGLE_THORNS		 ="Tangle Thorns";
char  *STR_MINDS_EYE			 ="Minds Eye";
char  *STR_ICE_HAMMER			 ="Ice Hammer";
char  *STR_ASCERTAIN_POWER		 ="Ascertain Power";
char  *STR_BANISH_ELEMENTAL 	 ="Banish Elemental";
char  *STR_RAZOR_LEAVES3		 ="Razor Leaves III";
char  *STR_CALL_HAILSTORM		 ="Call Hailstorm";
char  *STR_MAELSTROM			 ="Maelstrom";
char  *STR_EARTHQUAKE			 ="Earthquake";

char  *STR_ALL_DIGITS			 =";-)";

char  *STR_TRAP_SPEAR			 ="A Spear lurches from a hole in ye dungeon wall..";
char  *STR_TRAP_ACID			 ="A jet of blue acid spews from ye dungeon roof..";
char  *STR_TRAP_ARROW			 ="An Arrow fires from a slit in ye dungeon roof.";
char  *STR_TRAP_POISON_ARROW	 ="A Poison Arrow lunges from a slit in ye dungeon roof.";
char  *STR_TRAP_GAS 			 ="Thy party is engulfed by a green gas emitted from a vent above.";
char  *STR_TRAP_PIT 			 ="A great trap door, hiding a black pit, opens beneath thy party.";
char  *STR_TRAP_SPIKED_PIT		 ="A great trap door, concealing a black pit filled with spikes, opens beneath thy party!";
char  *STR_TRAP_SPIKED_POISON_PIT="An oaken trap door, hiding a dark pit filled with poisoned spikes, opens beneath thy party!";
char  *STR_TRAP_ROCKS			 ="An avalanche of boulders and rocks falls from above thy party.";
char  *STR_TRAP_ELECTRICITY 	 ="A bolt of electricity arcs across thy party.";
char  *STR_TRAP_FIREBALL         ="A large ball of raging fire bursts from a cavity in ye floor, engulfing thy party..";

char *get_weapon_name(int item)
{
	static char *name;

	switch(item)
	{
		case DAGGER 	 :	name=STR_DAGGER 	 ; break;
		case AXE		 :	name=STR_AXE		 ; break;
		case SHORT_SWORD :	name=STR_SHORT_SWORD ; break;
		case LONG_SWORD  :	name=STR_LONG_SWORD  ; break;
		case RAPIER 	 :	name=STR_RAPIER 	 ; break;
		case CLAYMORE	 :	name=STR_CLAYMORE	 ; break;
		case MACE		 :	name=STR_MACE		 ; break;
		case FLAIL		 :	name=STR_FLAIL		 ; break;
		case BOW		 :	name=STR_BOW		 ; break;
		case CROSSBOW	 :	name=STR_CROSSBOW	 ; break;
		case HALBERD	 :	name=STR_HALBERD	 ; break;
		case SLING		 :	name=STR_SLING		 ; break;
		default          :  name=""              ; break;
	}

	return(name);
}
