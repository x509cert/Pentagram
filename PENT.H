/*
 *    Pentagram Header
 *
 *    Started in earnest after 4 yrs on 7th April 1989!
 *
 *
 */

#define TITLE                   "Pentagram"
#define AUTHOR                  "Michael Howard"
#define COMPANY                 "Odin Software Development"
#define VERSION                 "1.01"
#define PENTAGRAM_VERSION		'à'

#if _MSC_VER >= 600
  #define _PASCAL				_pascal
  #define _CDECL				_cdecl
  #define _NEAR 				_near
  #define _FAR					_far
#endif

#define FALSE                   0
#define TRUE                    !FALSE

#define ON                      TRUE
#define OFF                     FALSE

#define SLOW                    0
#define FAST                    !SLOW

#define NO                      0
#define YES                     !NO

#define ERR                     -1

#define GLOBAL_DATA             "GLOBAL.PNT"
#define PARTYFILE               "PARTY.PNT"
#define ADV_PREFIX              "ADVN%03d.PNT"
#define GUILD_TEXT_FILE1        "GUILD1.TXT"
#define GUILD_TEXT_FILE2        "GUILD2.TXT"
#define SPECTRE_TEXT_FILE       "SPECTRE.TXT"
#define OTHER_PARTY_TEXT_FILE   "O_PARTY.TXT"
#define MAP_FILE                "REALMS5.MAP"
#define PIC_DIRECTORY           "PENTPIX\\"
#define COA_DIRECTORY           "PENTCOA\\"
#define DAY_NIGHT_DIRECTORY     "PENTDYNT\\"
#define MAP_ICON_DIRECTORY      "PENTICON\\"
#define DUNGEON_DIRECTORY       "PENTDNGN\\"
#define HOURGLASS_DIRECTORY 	"PENTHRGL\\"
#define MONSTER_DIRECTORY		"PENTMNST\\"
#define PROFESSION_DIRECTORY	"PENTPROF\\"
#define DUNGEON_SUFFIX          "DNG"
#define DUNGEON_SAVED_SUFFIX    "D@@"
#define DUNGEON_DESCRIP_SUFFIX  "DSC"
#define MONSTER_DATABASE		"FIENDS.DAT"
#define CELTIC_FILE 			PIC_DIRECTORY "CELTIC.FNT"
#define GOTHIC_FILE             PIC_DIRECTORY "GOTHIC.FNT"

#define START_YEAR              892
#define START_DATE              230

#define DOUBLE_HEIGHT           2   /* Used for printing Gothic/Celtic Text */
#define NORMAL_HEIGHT           1

#define GOTHIC                  2   /* The selectable game font */
#define CELTIC                  1

#define XOR_CODE                0x55
#define RUMOUR_SIZE             80
#define MAX_RUMOUR_INDEX        40

#define NUM_HG_IMAGES           5

#define STEPS_PER_HALF_HOUR 	8

#define ELIGIBLE_THRESHOLD		2
#define NOT_ELIGIBLE			(-4)
#define HOE_KILL_THRESHOLD		90
#define PRAYER_TIME_THRESHOLD   30
#define CRITICAL_HIT_THRESHOLD	50
#define BANK_INTEREST_THRESHOLD 28
#define CURIOUS_BOX_DEAD        50
#define FOOD_THRESHOLD          400
#define KINDNESS_THRESHOLD		3
#define ROCK_THRESHOLD			80

#define COMBAT_DURATION 		31

#define BACKSTAB_MULTIPLIER     4

#define MAX_HP                  999
#define MAX_CHANNEL             40
#define MAX_PARTY               6
#define MAX_ON_DISC             10
#define MAX_CARRY               12
#define MAX_SKILLS              15
#define MAX_LEVEL               15
#define TITLE_LEVEL             9
#define MAX_SMALLTOWNS			23
#define MAX_DEITIES 			12
#define MAX_POOL                MAX_PARTY*MAX_CARRY
#define MAX_WIZARD_SPELLS       25
#define MAX_PRIEST_SPELLS       25
#define MAX_DRUID_SPELLS        25
#define MAX_ILLUSIONIST_SPELLS  25
#define MAX_PLAYER_SPELLS       40
#define MAX_SPELLS              30
#define MAX_GOLD_SWAP           9999
#define MAX_FOOD                99
#define MAX_OIL                 10
#define MAX_QUARRELS            30
#define MAX_DARTS               30
#define MAX_ARROWS              30
#define MAX_HERBS_CARRY 		5
#define MAX_WORLD				195
#define MAX_DUNGEONS            7
#define MAX_DUNGEON_X           20
#define MAX_DUNGEON_Y           21
#define MAX_DUNGEON_Z           4
#define MAX_DUNGEON_DESCRIP     26
#define MAX_WAND_USE			3
#define MAX_DEVOURING_ROD_USE	2
#define MAX_RING_USE            4
#define MAX_PROFESSIONALISM     25
#define MAX_ATTACK				2		/* Max Number of monster attacks */
#define MAX_MONSTERS            8
#define MAX_ODIN_PAGES          3
#define MAX_ODIN_NOTE_SIZE		800
#define MAX_ABILITY 			20


#define DAMAGE_WINDOW_COL		13
#define DAMAGE_WINDOW_Y         6

#define CHANNEL_MULTIPLIER      2
#define MONSTER_IMAGE_SIZE      300

#define CMBT_AREA_X 			9		/* Size of the */
#define CMBT_AREA_Y 			9		/* Combat Arena */

#define CMBT_SIZE_X 			21		/* Size of a combat cell */
#define CMBT_SIZE_Y 			22		/* in pixels */

#define FLEE_COORDS_NOT_SET 	15

#define DNGN_STEPS_HALF_HOUR    40      /* Number of steps in Dungeon per «Hr */
#define DNGN_ENCRYPT_CODE       65

#define DUNGEON_BIT_X           7       /* Size of each dungeon square */
#define DUNGEON_BIT_Y           5
#define DUNGEON_XOFF            10      /* Used when drawing dungeon squares */
#define DUNGEON_YOFF            9

#define DICE_COLOUR             4

#define NUM_ANIMATED_SKULLS     4

#define PLUS_1_COST             20
#define PLUS_2_COST             40
#define PLUS_3_COST             75

#define NO_SPELL                255
#define SPELL_LEARNED           101

#define LEVEL_2_LEVEL           3
#define LEVEL_3_LEVEL           6

#define WINDOW_MAP_SIZE         9
#define MAP_ICON_SIZE           106
#define MAP_SIZE                200

#define DAY_NITE_ICON_SIZE		910
#define FONT_RAM_SIZE			767

#define MORALE_MIN				0
#define MORALE_MAX				10
#define MORALE_LOWER_THRESHOLD	3
#define MORALE_UPPER_THRESHOLD	8

#define POT_DURATION            (6+(rand()%4))

#define THIEVES_GUILD_CUT       10L

#define DAYS_PER_YEAR           360L

#define SURPRISE_LOW_THRESHOLD  6
#define SURPRISE_MOD            50

#define mouse(a,b,c,d)			CMOUSEL(a,b,c,d)

#define TPP                     the_party.player
#define P_NUM					the_party.num_in_party
#define IN_COMBAT               the_party.in_combat
#define IN_DUNGEON              the_party.in_dungeon
#define IN_RUIN 				the_party.in_ruin

#define SIZE(x)                 (sizeof(x)/sizeof(x[0]))

#define NO_SOUND                (!pent_data.sound)

#define TALISMAN_BIT(bit,x,y)   ((x)&1?bit[y][x>>1]&0x0F:(bit[y][x>>1]&0xF0)>>4)

#define map_bit(x,y)            ((x)&1?(*(MAP+((x)>>1)+((y)*(MAP_SIZE/2))))&0x0F \
									  :(*(MAP+((x)>>1)+((y)*(MAP_SIZE/2))))>>4)

#define BLOCKSIZE(x1,y1,x2,y2)	(2L+_imagesize(x1,y1,x2,y2))

#ifdef DEV
#define DEBUG()					DEBUG_func(__FILE__, __LINE__)
#else
#define DEBUG()
#endif

#define CMBT_X(x)				(CMBT_SIZE_X*(x)+1)
#define CMBT_Y(y)				(CMBT_SIZE_Y*(y)+1)

#define GX(a,b) 				gexclaim(a,b)

#define sgn(x)					((x)>0?1:(((x)<0)?-1:0))

#define LAST_WIZARD 			(INVOKE_FAMILIAR+1)
#define LAST_PRIEST 			(SPELL_OF_PASSAGE+1)
#define LAST_ILLUSIONIST		(SUSPEND_TIME+1)
#define LAST_DRUID				(EARTHQUAKE+1)

enum	prev_jobs		{PJ_BODYGUARD,	   PJ_LABOURER,    PJ_MERCENARY,
						 PJ_MILITIAMAN,    PJ_PIT_FIGHTER, PJ_WATCHMAN,
						 PJ_OUTLAW, 	   PJ_SOLDIER,	   PJ_STREET_FIGHTER,
						 PJ_BOUNTY_HUNTER, PJ_GAMEKEEPER,
						 PJ_PROSPECTOR,    PJ_TRAPPER,	   PJ_POACHER,
						 PJ_HYPNOTIST,	   PJ_SEER, 	   PJ_SCRIBE,
						 PJ_ALCHEMIST_APP, PJ_STUDENT,	   PJ_TRADER,
						 PJ_WIZARD_APP,    PJ_PHARMACIST,  PJ_ARTISAN_APP,
						 PJ_EXCISEMAN,	   PJ_ENGINEER,    PJ_INITIATE,
						 PJ_LIBRARIAN,	   PJ_TEACHER,	   PJ_JEWELLER,
						 PJ_HERBALIST,	   PJ_HUSBANDMAN,
						 PJ_FORESTER,	   PJ_WOODSMAN,    PJ_SQUIRE,
						 PJ_CLERIC, 	   PJ_BEGGAR,	   PJ_GAMBLER,
						 PJ_GRAVE_ROBBER,  PJ_FOOTPAD,	   PJ_JAILER,
						 PJ_PEDLAR, 	   PJ_SMUGGLER,    PJ_TOMB_ROBBER,
						 PJ_RAT_CATCHER,   PJ_OUTRIDER,    PJ_RUSTLER};

enum	cmbt_type		{WANDERING_MONSTER, SET_MONSTER,
						 MANGRETH_MONSTER,	KALDRUTHA_MONSTER};

enum    cmbt_move_opts  {MOVE_MOVE, MOVE_SNEAK};

enum    wand_modes      {WAND_MODE_SCATTER,
						 WAND_MODE_SOLITARY,
						 NORMAL_SPELL_SAVE};

enum	cmbt_magic_type {TY_FIRE,		 TY_ICE,
						 TY_ENERGY, 	 TY_ELECTRICITY,
						 TY_ANTI_UNDEAD, TY_MIND,
						 TY_QUAKE};

enum    deitie_types    {D_ATHIN,  D_TARL,    D_OLRIC,
						 D_AERDRI, D_CELANIL, D_DUMATHIN,
						 D_CYRR,   D_MAGMI,   D_MORR,
						 D_RHYAA,  D_SOLONIR, D_ENORETH};

enum	sound_types 	{VICTORY,GX_NONE,NEW_LEVEL,SPELL,
						 SOLEMN, DEATH,  BAD,	   GOOD,
						 PRAY};

enum    rumour_cats     {R_0,
						 R_CLASS,       R_HALF_OGRE,    R_HALFLING,
						 R_DWARF,       R_ELF,          R_HUMAN,
						 R_SYLVAN_ELF,  R_WARRIOR,      R_CRUSADER,
						 R_RANGER,      R_WIZARD,       R_PRIEST,
						 R_ILLUSIONIST, R_DRUID,        R_DUELIST,
						 R_HUNTER,      R_THIEF,        R_MONK,
						 R_BARD,        R_ARMOUR,       R_BANE_RUNE,
						 R_POISON,      R_WEAPON,       R_RACE,
						 R_TOWN,        R_WOMAN,        R_SEASON,
						 R_DISEASE,     R_DEATH,        R_FIRE,
						 R_MAGIC,       R_HUNTING,      R_WEATHER,
						 R_MONTH,       R_PICK_LOCK,    R_TOOLS,
						 R_ANGHARAD,    R_BACKSTAB,     R_MONSTER,
						 R_SNOTLING,    R_MIST_WARRIOR, R_UNDEAD,
						 R_DRAGON,      R_SNAKE,        R_DUNGEON1,
						 R_DUNGEON2,    R_HELLS,        R_DAMNED,
						 R_MORIBUND,    R_MISERY,       R_CRYPT,
						 R_CATHEDRAL,   R_HEALING,      R_DEMON,
						 R_POTION,      R_HERB1,        R_HERB2,
						 R_GUILD,       R_DARK_ELF,
						 R_TALISMAN,    R_FOXHOLLOW,    R_INSURANCE,
						 R_GODS,        R_GAMBLING,     R_TREASURE,
						 R_KAITLIN,     R_LOCK,         R_MORT,
						 R_MUSIC,       R_PENTAGRAM,    R_PIERCER,
						 R_PRAY,        R_RAYEK,        R_3_TRAITORS,
						 R_RIVERNECK,   R_SOUTH_RHYDE,  R_NORTH_RHYDE,
						 R_WOLFBURG,    R_SEA,          R_RUIN,
						 R_RUWK,        R_BANK,         R_LOSTSOUL,
						 R_TRAP,        R_TORCH,        R_OAK_VALE,
						 R_WAND,        R_OLD_HAG,      R_GHOST_SHIP,
						 R_EYE_OF_HELL, R_HOLY_WATER,   R_COMBAT,
						 R_FOREST,      R_REST,         R_MONEY,
						 R_DRINK,       R_GRAVE_ROT,    R_POX,
						 R_GNOME,       R_RUMOUR,       R_MOON,
						 R_CLOAK,       R_FOOD,         R_SUMMON,
						 R_ANIMAL,      R_CHEST,        R_GIANT,
						 R_SAGE,
						 R_ISLAND,		R_RIVERDAWN,	R_LANDIR,
						 R_SEA_POINT,   R_TIRAVEL,      R_ERIHN,
						 R_DUN_CIRACH,  R_DUN_TARITH,   R_FROSTHAVEN,
						 R_MINASH,      R_CAPE_DAWN,    R_TELKAR,
						 R_KANRAITH,    R_MIST_POINT,   R_BLACKLOCK,
						 R_EDRAM,       R_MIRENNA,      R_LEECHWEED,
						 R_SNOWEED,     R_WOLFPETAL,    R_ICE_NETTLE,
						 R_GYLVIR,      R_ANGELS_WING,  R_BEERBERRY,
						 R_WILD_SPRIG,  R_GLOWPETAL,    R_THORNBRIG,
						 R_ASHLEAF,     R_PIGWORT,      R_MOON_TEMPLE,
						 R_MANGRETH,	R_WYNEWEED,
						 R_ATHIN,       R_TARL,         R_OLRIC,
						 R_AERDRI,		R_CELANIL,		R_DUMATHIN,
						 R_CYRR,		R_MAGMI,		R_MORR,
						 R_RHYAA,       R_SOLONIR,      R_ENORETH,

						 R_END,     /* Mark end of Rumour Index types */

						 R_SEX,
						 R_SWEAR    /* Index response if you swear! */
						};

enum buzz_durations 	{BUZZ_SHORT,BUZZ_LONG};

enum directions 		{DIR_NORTH, DIR_SOUTH, DIR_WEST, DIR_EAST, JUST_TELEPORTED=99};

enum buttons            {B_NO,      B_OK,       B_YES,
						 B_NEXT,    B_PREV,     B_QUIT,
						 B_INFO,    B_FINISH,   B_HIGHER,
						 B_LOWER,   B_CARD_RED, B_CARD_BLACK,
						 B_PRINT,   B_SCAN};

enum sexes              {SX_MALE, SX_FEMALE, SX_BOTH};

enum classes            {WARRIOR=1, RANGER,     CRUSADER,
						 DUELIST,   PRIEST,     HUNTER,
						 THIEF,     MONK,       BARD,
						 DRUID,     ILLUSIONIST,WIZARD};

enum races				{HUMAN=1,	 HIGH_ELF, DWARF,	   HALFLING,
						 SYLVAN_ELF, GNOME,    HALF_OGRE,  DARK_ELF};

enum languages			{LAN_OLD_TONGUE=1, LAN_ORCISH=2,	 LAN_OGRISH=4,
						 LAN_DWARFISH=8,   LAN_ELVISH=16,	 LAN_GOBLIN=32,
						 LAN_UNDERWURLDE=64};

enum second_skills      {SWIM=1,            SURVIVAL,       HUNT,
						 ATTACK,            PARRY,          LISTEN,
						 FIND_TRAP,         DISARM_TRAP,    MISSILE,
						 HEAL,              HERB_LORE,      MOVE_SILENT,
						 PICK_LOCK,         IMMUNITY_POISON,IMMUNITY_DISEASE};

enum pluses             {NO_PLUS=0, PLUS_1, PLUS_2, PLUS_3, CURSED};

enum items              {LEATHER_ARMOUR=1,  SPLINT_ARMOUR=5,CHAIN_ARMOUR=10,
						 PLATE_ARMOUR=15,   ELF_ARMOUR=20,

						 DAGGER=25,         AXE=30,         SHORT_SWORD=35,
						 LONG_SWORD=40,     RAPIER=45,      CLAYMORE=50,
						 MACE=55,           FLAIL=60,       BOW=65,
						 CROSSBOW=70,       HALBERD=75,     SLING=80,

						 SMALL_SHIELD=85,   MEDIUM_SHIELD=90,
						 LARGE_SHIELD=95,   HELMET=100,

						 SACK=105,          BACK_PACK,      TINDER_BOX,
						 HEAVY_CLOAK,       HOODED_LANTERN, THIEVES_TOOLS,
						 RELIGIOUS_SYMBOL,  CURIOUS_BOX,    SEXTANT,

						 WYVERN_RING,       DRAGON_RING,    RING_OF_HEALING,
						 MIND_SHIELD_RING,  RING_OF_FIRE,   RING_OF_ICICLES,
						 RING_OF_SWIMMING,  WARMTH_RING,

						 THUNDER_WAND,      ICE_WAND,       FIRE_WAND,
						 HEALING_STAVE,     SUSTENANCE_WAND,DEVOURING_ROD,

						 ORB_TITAN,         ORB_DEXTERITY,  ORB_WISE,
						 ORB_FORTUNE,       ORB_MEDITATION, ORB_STAMINA,
						 ORB_BEAUTY,

						 RELIC,             TOME,           ELFIN_CLOAK,
						 BRACERS_POISON,    PENDANT_HEALTH, ELFIN_BOOTS,
						 GLOVES_NIMBLENESS, LUTE,           GRIMOIRE,

						 POTION=200,

						 NOTHING=255};

enum item_status        {ITEM_CARRIED=0, ITEM_HELD=1};

enum potion_types       {POT_SECRET_DOOR=15,    POT_STRENGTH,
						 POT_STRIKING,          POT_UNDEAD_TURN,
						 POT_FIRE_RESIST,       POT_COLD_RESIST,
						 POT_HEALING,           POT_REVIVING,
						 POT_POISON,            POT_HOLYWATER,
						 POT_NOTHING,           POT_CURE_DISEASE,
						 POT_ALCOHOL};

enum conditions         {OKAY=1, POISONED, DEAD,       DUST,
						 WEAK,   DISEASED, UNCONCIOUS, BLIND,
						 SLEEP,  AFRAID,   POSSESSED,  BOUND,
						 FLEE,   STUNNED};

enum handedness 		{HAND_RIGHT, HAND_LEFT, HAND_AMBIDEXTROUS};

enum diseases           {NO_DISEASE=1, GRAVE_ROT, POX, PLAGUE};

enum ethics             {LAWFUL=1, NEUTRAL, CHAOTIC};

enum hunger_levels      {NOT_HUNGRY=0, SLIGHT_HUNGER, BELLY_RUMBLE, HUNGRY,
						 VERY_HUNGRY,  DANGEROUSLY_HUNGRY};

enum terrain            {PATH=0,        SEA,        GRASS,
						 TOWN,          SIGNPOST,   HILLS,
						 BRIDGE,        MOUNTAINS,  HIGH_MOUNTAINS,
						 WATER,         FOREST,     MARSH,
						 CELTIC_CROSS,  DUNGEON,    RUIN,
						 CITY};

enum bridges            {BRIDGE_UD=20,  BRIDGE_LR};

enum precip_types       {PRECIP_NONE,   PRECIP_LIGHT,
						 PRECIP_MEDIUM, PRECIP_HEAVY};

enum rain_snow          {RAIN, SLEET, SNOW};

enum wind_types         {NO_WIND, LIGHT_WIND, WINDY, STRONG_WIND};

enum cloud_types        {CLEAR_SKY, HIGH_CLOUD, LIGHT_CLOUD, CLOUDY, DARK_CLOUDS};

enum temperatures       {DANGEROUSLY_COLD, FREEZING, COLD, COMFORTABLE, WARM, HOT, VERY_HOT, DANGEROUSLY_HOT};

enum works_status       {RESTING, LIGHT_WORK, WORKING, HARD_WORK};

enum check_bdays        {DONT_CHECK_BIRTHDAYS=0, CHECK_BIRTHDAYS=1};

enum moon_phases        {NEW_MOON,PHASE_2, PHASE_3, PHASE_4, PHASE_5, PHASE_6, FULL_MOON,
						 PHASE_8, PHASE_9, PHASE_10, PHASE_11, PHASE_12};

enum familiars          {NO_FAMILIAR,     FAMILIAR_HAWK,    FAMILIAR_CAT,
						 FAMILIAR_BAT,    FAMILIAR_TOAD,    FAMILIAR_FOX,
						 FAMILIAR_OTTER,  FAMILIAR_OWL,     FAMILIAR_RABBIT,
						 FAMILIAR_RAT,    FAMILIAR_VIPER};

enum town_types         {TWN_HAMLET, TWN_VILLAGE, TWN_TOWN, TWN_CITY};

enum seasons            {SPRING, SUMMER, AUTUMN, WINTER};

enum attack_types       {MON_NO_ATTACK,     MON_CLAW,
						 MON_KICK,          MON_WEAPON,
						 MON_BITE,          MON_FIRE,
						 MON_ICE,           MON_ELECTRICITY,
						 MON_TAIL_LASH,     MON_STING,
						 MON_MAGIC,         MON_GAZE,
						 MON_PUNCH, 		MON_BREATH,
						 MON_SPIT_FIRE,     MON_ROCK,
						 MON_ARROW};

enum monster_times      {MON_DAY, MON_NIGHT, MON_BOTH};

enum monster_weaknesses {WK_NONE, WK_ICE, WK_FIRE, WK_ELECTRICITY, WK_QUAKE};

enum opponent_dir		{O_DIR_NONE,	  O_DIR_NORTH,	   O_DIR_NORTHEAST,
						 O_DIR_NORTHWEST, O_DIR_SOUTH,	   O_DIR_SOUTHEAST,
						 O_DIR_SOUTHWEST, O_DIR_EAST,	   O_DIR_WEST};

enum treasure_types 	{TRE_NONE=0,	  TRE_LOW_MONEY=1, TRE_MED_MONEY=2,
						 TRE_LOT_MONEY=4, TRE_JEWELS=8,    TRE_MAGIC=16};

enum monster_types      {TYP_NO_RUNES=0, TYP_UNDEAD=1,    TYP_FIRE=2,
						 TYP_WATER=4,    TYP_EARTH=8,     TYP_AERIAL=16,
						 TYP_DEMONIC=32, TYP_NOCTURNAL=64,TYP_ICE=128};

enum monster_images     {IM_AIR,           IM_BANDIT,     IM_BANSHEE,
						 IM_BLACK_DEMON,   IM_BRIGAND,    IM_EARTH,
						 IM_ELITE_MIST,    IM_ELITE_SKEL, IM_ENT,
						 IM_ETTIN,         IM_EYE,        IM_FIRE,
						 IM_FIRE_BAT,      IM_GARGOYLE,   IM_GHOST,
						 IM_GHOUL,         IM_GOBLIN,     IM_GREAT_MIST,
						 IM_GREEN_VIPER,   IM_HOBGOBLIN,  IM_ICE_DEMON,
						 IM_ICE_SPIDER,    IM_ICE_VIPER,  IM_LESSER_DEVIL,
						 IM_LICHE,         IM_LIZARD,     IM_MIST_WARRIOR,
						 IM_OGRE,          IM_ORC,        IM_ORC_CHIEF,
						 IM_PIT_DEMON,     IM_RAT,        IM_RED_DRAGON,
						 IM_SCORPION,      IM_SKELETON,   IM_SPECTRE,
						 IM_TROLL,         IM_WARLOCK,    IM_WASP,
						 IM_WATER,         IM_WEREWOLF,   IM_WILLOWISP,
						 IM_WITCH,         IM_WOLF,       IM_ZOMBIE};

enum monster_speak_ty	{MSPK_NONE, MSPK_GRUNT,    MSPK_SWEAR,
						 MSPK_MOAN, MSPK_FRIENDLY, MSPK_OFF_HAND,
						 MSPK_HROOM};

enum monster_weapon_ty	{MWPN_NONE, MWPN_CLUB,	 MWPN_SHORT_SWORD,
						 MWPN_AXE,  MWPN_HALBERD,MWPN_DAGGER,
						 MWPN_LONG_SWORD};

enum combat_spells      {COMBAT_SPELL, NON_COMBAT_SPELL, BOTH_SPELL};

enum spell_types1       /* Wizard */
						{DRAGONFLAME1,			HAMMERHAND,
						 ARC_LIGHTNING1,        FIND_HIDDEN_DOOR,
						 GRAVMUR_RAGE,			FROZEN_WIND1,
						 FIRE_MIST,             MIGHTY_APPEARANCE,

						 DRAGONFLAME2,			LETHARGY,
						 SWIFTNESS,             ARC_LIGHTNING2,
						 DISPEL_TRAP,           SINK,
						 BLINDING_FLASH,		FROZEN_WIND2,

						 DRAGONFLAME3,			ARC_LIGHTNING3,
						 DEATH_CURSE,			BIND_DEMON,
						 TELEPORT,				FROZEN_WIND3,
						 INVOKE_FAMILIAR
						};

						/* Priest */
enum spell_types2       {TWILIGHT,              NEUTRALISE_POISON,
						 PROT_FROM_COLD,        PROT_FROM_FIRE,
						 CURE_LIGHT_INJURY,     CAUSE_LIGHT_INJURY,
						 HOLY_SPRAY,            DUNGEON_DIVINATION,

						 OPEN_CHEST,            REMOVE_CURSE,
						 CURE_DISEASE,          CURE_SEVERE_INJURY,
						 DISRUPTION,            CAUSE_SEVERE_INJURY,
						 BLADES,

						 PROT_FROM_TRAPS,       RESURRECT,
						 CURE_CRITICAL_INJURY,  CAUSE_CRITICAL_INJURY,
						 MISSILE_CLOAK, 		SPELL_OF_PASSAGE
						};

						/* Illusionist */
enum spell_types3       {HORRIFY,               SLY_EARS,
						 CATS_EYES,             PHANTASM1,
						 STAR_FLARE,            AXELS_BLUR,
						 ALLYS_DANCING_DAGGER,

						 JONAS_SPOOK,           KORINAS_LEAP,
						 PHANTASM2,             AXELS_SHIMMER,
						 ALLYS_DANCING_MACE,	MOON_FLARE,
						 CREATE_ARTIFACTS,

						 AXELS_SHADOW,          MIRAGE,
						 PHANTASM3,             ALLYS_DANCING_SABRE,
						 SUN_FLARE,             SUSPEND_TIME
						};

						/* Druid */
enum spell_types4       {WALK_ON_WATER,         FLAME_SHEET,
						 RAZOR_LEAVES1,         POISON_IMMUNITY,
						 PLANT_FEAST,			TRUEFLIGHT,

						 AURA_OF_PROTECTION,    RAZOR_LEAVES2,
						 TANGLE_THORNS,         MINDS_EYE,
						 ICE_HAMMER,			DR_INVOKE_FAMILIAR,

						 ASCERTAIN_POWER,		BANISH_ELEMENTAL,
						 RAZOR_LEAVES3,         CALL_HAILSTORM,
						 MAELSTROM, 			EARTHQUAKE
						};

						/* Bard */
enum spell_types5       {WINDSONG,       WAYFARERS_TUNE, ALETHRAN,
						 TALE_OF_YULDAR, PALISORS_DREAM, DAYLIGHT_FALLS,
						 HUNTERS_POEM
						};

enum things_in_effect	{IN_EFFECT_WINDSONG,		IN_EFFECT_WAYFARERS_TUNE,
						 IN_EFFECT_ALETHRAN,        IN_EFFECT_TALE_OF_YULDAR,
						 IN_EFFECT_PALISORS_DREAM,  IN_EFFECT_DAYLIGHT_FALLS,
						 IN_EFFECT_LIGHT,           IN_EFFECT_PROT_FROM_TRAPS,
						 IN_EFFECT_WALK_ON_WATER,   IN_EFFECT_TANGLE_THORNS,
						 IN_EFFECT_MIRAGE,          IN_EFFECT_AURA_OF_PROTECTION,
						 IN_EFFECT_LETHARGY,        IN_EFFECT_SWIFTNESS,
						 IN_EFFECT_HUNTERS_POEM,	IN_EFFECT_SPELL_OF_PASSAGE,
						 IN_EFFECT_MISSILE_CLOAK,	IN_EFFECT_TRUEFLIGHT
						};

enum herb_types         {HERB_NONE,         HERB_WOLFPETAL,
						 HERB_WILDSPRIG,    HERB_THORNBRIG,
						 HERB_RUWK,         HERB_SNOWEED,
						 HERB_MIRENNA,      HERB_BEERBERRY,
						 HERB_GYLVIR,       HERB_GLOWPETAL,
						 HERB_PIGWORT,      HERB_EDRAM,
						 HERB_LEECHWEED,    HERB_ASHLEAF,
						 HERB_ANGELSWING,   HERB_ICE_NETTLE,
						 HERB_WYNEWEED};

enum herb_bits          {HERB_BIT_PETAL, HERB_BIT_FLOWER, HERB_BIT_BERRY};

enum herb_effects       {HERB_EFF_HP,      HERB_EFF_DISEASE,
						 HERB_EFF_POISON,  HERB_EFF_SORC_PT,
						 HERB_EFF_DIV_PT,  HERB_EFF_DRUNK,
						 HERB_EFF_NOTHING};

enum herb_colours       {HERB_COL_RED,          HERB_COL_BLUE,
						 HERB_COL_PURPLE,       HERB_COL_YELLOW,
						 HERB_COL_WHITE,        HERB_COL_BRIGHT_GREEN,
						 HERB_COL_PINK,         HERB_COL_ORANGE,
						 HERB_COL_PASTEL_BLUE};

enum potion_options     {DRINK_POTION, TASTE_POTION};

enum card_suits         {CS_HEARTS, CS_CLUBS, CS_SPADES, CS_DIAMONDS};

enum card_values        {CV_TWO,   CV_THREE, CV_FOUR, CV_FIVE, CV_SIX,
						 CV_SEVEN, CV_EIGHT, CV_NINE, CV_TEN,  CV_JACK,
						 CV_QUEEN, CV_KING,  CV_ACE};

enum blackjack_opts     {BJ_STICK, BJ_ANOTHER, BJ_QUIT};

enum swaps              {SWAP_FOOD,     SWAP_OIL,   SWAP_ARROWS,
						 SWAP_QUARRELS, SWAP_DARTS, SWAP_GOLD};

enum cause_of_death     {NO_DISPLAY,   FROM_POISON,  FROM_COMBAT,
						 FROM_DROWNING,FROM_HUNGER,  FROM_DISEASE,
						 FROM_FROZE,   FROM_BURNT,   FROM_FRIGHT,
						 FROM_ELECTR,  FROM_FELL,    FROM_TRAP,
						 FROM_HUNTING, FROM_HERBS,   FROM_CHILL};

enum dungeon_names      {DN_LOSTSOUL, DN_DAMNED,    DN_CRYPT,
						 DN_MORT,     DN_MORIBUND,  DN_HELLS,
						 DN_MISERY};

enum dungeon_levels     {DUN_LVL_1, DUN_LVL_2, DUN_LVL_3, DUN_LVL_4};

enum dungeon_monster_ty {DM_ALL, DM_UNDEAD, DM_GOBLINOID, DM_DEMONS};

enum dungeon_set_monst	{DMON_NONE,   DMON_DRAGON, DMON_DEMON, DMON_ORC,
						 DMON_GOBLIN, DMON_GIANT,  DMON_MIST_WARRIOR,
						 DMON_TROLL,  DMON_RAT,    DMON_UNDEAD,
						 DMON_SNAKE,  DMON_SPIDER, DMON_RANDOM};

enum dungeon_artifacts  {DNG_WALL,         DNG_LOCKED_DOOR,  DNG_STAIRS_UP,
						 DNG_STAIRS_DOWN,  DNG_VOICE,        DNG_SPECIAL,
						 DNG_CORRIDOR,     DNG_TRAP,         DNG_DOOR,
						 DNG_HEAVY_DOOR,   DNG_SECRET_DOOR,  DNG_MONSTER,
						 DNG_WATER,        DNG_WHIRLPOOL,    DNG_EMPTY_CHEST,
						 DNG_CHEST,        DNG_TRAPPED_CHEST,DNG_LOCKED_CHEST,
						 DNG_TR_LOCK_CHEST,DNG_PILLAR
						};

enum dungeon_traps      {TRAP_NONE,   TRAP_SPEAR,        TRAP_ACID_SQUIRT,
						 TRAP_ARROW,  TRAP_POISON_ARROW, TRAP_GAS,
						 TRAP_PIT,    TRAP_SPIKED_PIT,   TRAP_POISON_SPIKED_PIT,
						 TRAP_ROCKS,  TRAP_ELECTRICITY,  TRAP_FIREBALL
						};

enum chest_traps        {CHEST_TRAP_POISON_DART, CHEST_TRAP_DART,
						 CHEST_TRAP_GAS,         CHEST_TRAP_ELECTRICITY};

enum dungeon_spec_lp    {LOOKING, PASSING};

enum dungeon_difficulty {DD_TOUGH, DD_DIFFICULT, DD_DANGEROUS,
						 DD_VERY_DANGEROUS,DD_SUICIDAL};

enum rarity_types       {COMMON, UNCOMMON, RARE, VERY_RARE};

enum occ_types          {IS_EMPTY, IS_MONSTER, IS_PLAYER, IS_WALL};

enum wall_positions     {CMBT_OPEN_AREA, CMBT_CORRIDOR_AREA, CMBT_LL_AREA,
						 CMBT_LR_AREA,   CMBT_X_AREA};

enum combat_attack_mode {CMBT_SLASH,   CMBT_THRUST,  CMBT_BOW, CMBT_CROSSBOW,
						 CMBT_DART,    CMBT_SLING,	 CMBT_OIL, CMBT_HOLYWATER,
						 CMBT_BACKSTAB,CMBT_BLUDGEON,CMBT_PUNCH};

enum combat_next_round	{NR_FLEE, NR_COMBAT, NR_PARLEY};

enum combat_results     {RES_PARTY_SLAIN,   RES_MONSTERS_SLAIN,
						 RES_MONSTERS_FLEE, RES_PARTY_FLEE,
						 RES_PARLEY,		RES_NO_ACTION};

enum other_party_condx  {OP_OKAY,            OP_BADLY_BRUISED,
						 OP_WOUNDED,         OP_BANDAGED,
						 OP_HEAVILY_BANDAGED,OP_BLOOD_STAINED};


enum print_types        {PRN_EPSON, PRN_IBM, PRN_LASER};

enum surprise_types     {SURPRISE_NEITHER, SURPRISE_BOTH,
						 SURPRISE_PARTY,   SURPRISE_MONSTERS};

enum combat_delays		{CSPEED_SLOW,CSPEED_MED,CSPEED_FAST};


					/**************************
					 *                        *
					 *       Structures       *
					 *                        *
					 *                        *
					 **************************/

typedef struct pool_type{
							unsigned        item;         /* Eg; Dagger        */
							unsigned        type     : 6; /* Eg; +1            */
							unsigned        status   : 2; /* Eg; HELD|CARRIED  */
							unsigned        poisoned : 2; /* Eg; TRUE|FALSE    */

						} ITEM_POOL;

typedef struct spell_nm {
							int             name;
							char			*descrip;

						} SPELL_NAME;

typedef struct use_sw   {
							ITEM_POOL       bit;
							char            desc[30];

						} USE_SWAP;

typedef struct level_det{
							unsigned long   lower;
							unsigned long   upper;

						} LEVELS;

typedef struct gwindow  {
							int             x1,y1,x2,y2;
							char _FAR		*object;
							int             back;
							int             border;

						} GWINDOW;

typedef struct in_eff {
							unsigned        windsong;           /* Bard General protection  */
							unsigned        wayfarers_tune;     /*  "   Increase Agility +1 */
							unsigned        alethran;           /*  "   Creates Light       */
							unsigned        tale_of_yuldar;     /*  "   Increase Attack +15 */
							unsigned        palisors_dream;     /*  "   Extra Damage +1/2 lv*/
							unsigned        daylight_falls;     /*  "   Heal Faster  x1.5   */
							unsigned        hunters_poem;       /*  "   Better Armour AC-1  */

							unsigned        lantern_lit;
							unsigned        twilight;
							unsigned        prot_fire;
							unsigned        prot_cold;
							unsigned        prot_traps;
							unsigned        spell_of_passage;
							unsigned		walk_on_water;
							unsigned		trueflight;
							unsigned        tangle_thorns;
							unsigned        mighty_appearance;
							unsigned        mirage;
							unsigned        sly_ears;
							unsigned        cats_eyes;
							unsigned		hammerhand;
							unsigned		missile_cloak;

							unsigned        poison_immunity;
							unsigned        aura_protection;
							unsigned        swiftness;
							unsigned        find_hidden_doors;
							unsigned        axels_blur;
							unsigned        axels_shimmer;
							unsigned        axels_shadow;
							unsigned        allys_dancing_dagger;
							unsigned        allys_dancing_mace;
							unsigned        allys_dancing_sabre;

							unsigned        pot_striking;           /* Long lasting   */
							unsigned        pot_holy_water;         /* potion effects */
							unsigned        pot_undead_turn;
							unsigned        pot_fire_resist;
							unsigned        pot_cold_resist;
							unsigned        pot_strength;

							void            *allys_opponent;

					   } IN_EFFECT;

typedef struct player_type {
							unsigned char   version;            /* Game Version */

							char            name[12];
							char            file_name[14];

							int             in_party;

							char            race[17];
							int             nrace;

							int             sex;
							char            sex_title[10];

							char            him_her[5];
							char            he_she[5];
							char            his_her[5];

							char            class[20];
							int             nclass;

							unsigned		level		: 4;
							unsigned		max_level	: 4;

							unsigned long   xp;

							int             speed;              /* 0=Slow, 20=Superfast */

							int             ethics;

							int             professionalism;    /* Used as indicators to  */
																/* aid in distributing xp */
							int 			previous_job;

							unsigned		strength	 : 5;
							unsigned		intelligence : 5;
							unsigned		piety		 : 5;
							unsigned		agility 	 : 5;
							unsigned		toughness	 : 5;
							unsigned		charisma	 : 5;
							unsigned		luck		 : 5;

							unsigned long   banked;
							unsigned long   cash;

							int             languages;

							char            age[30];
							int             nage;
							char            birthday[40];
							int             birth_date;
							char            where_born[50];

							int 			hand;

							int             current_hp;
							int             hp;

							int             insurance;
							int             guild_member;

							char			deity_name[10];
							char			deity_control[10];

							int 			ndeity;

							int 			year_last_pray;
							int             day_last_pray;

							int             familiar;

							int             bane_rune;

							int             current_sorcery_points;
							int             current_divine_points;
							int             sorcery_points;
							int             divine_points;

							int             wizard_spells[MAX_WIZARD_SPELLS];
							int             priest_spells[MAX_PRIEST_SPELLS];
							int             druid_spells[MAX_DRUID_SPELLS];
							int             illusionist_spells[MAX_ILLUSIONIST_SPELLS];

							int             points_cast;

							int             secondary_attrib[MAX_SKILLS+1];

							char            here_to_fool1;

							unsigned        is_dust         : 1;
							unsigned        is_dead         : 1;
							unsigned        is_poisoned     : 1;
							unsigned        is_diseased     : 1;
							unsigned        is_asleep       : 1;
							unsigned        is_parrying     : 1;
							unsigned        is_stunned      : 3;

							unsigned		sneaking		: 1;

							int             disease;
							int             disease_how_long;
							int             disease_onset_time;
							int             disease_symptoms_given;      /* TRUE|FALSE */
							int             disease_wear_off;

							int             nheight;
							char			height[35];
							int             nweight;
							char			weight[35];

							int             ac;

							int             hits_per_round;

							int             food;               /* Max 99 lots */
							int             oil;
							int             arrows;
							int             quarrels;
							int 			darts;
																/* Unbroken after */
							unsigned		holywater_left : 4; /* a battle!	  */
							unsigned		oil_left	   : 4;

							int             max_drunkeness;
							int             drunkeness;

							int             hungry;
							int             last_food_bias;
							int             mins_last_food;

							char            here_to_fool2;

							unsigned		thunder_wand_used	  : 3;	/* Upto 3 a day */
							unsigned		fire_wand_used		  : 3;
							unsigned		ice_wand_used		  : 3;
							unsigned		stave_healing_used	  : 3;
							unsigned		sustenance_wand_used  : 3;

							unsigned		ring_of_fire_used	  : 3;
							unsigned		ring_of_icicles_used  : 3;

							int             bard_songs_sung;       /* Songs sang by a bard */

							int             learn_wiz1_spells;     /* Number of spells learnable */
							int             learn_wiz2_spells;
							int             learn_wiz3_spells;

							int             learn_ill1_spells;
							int             learn_ill2_spells;
							int             learn_ill3_spells;

							int             learn_pri1_spells;
							int             learn_pri2_spells;
							int             learn_pri3_spells;

							int             learn_dru1_spells;
							int             learn_dru2_spells;
							int             learn_dru3_spells;

							int             num_items_carried;

							ITEM_POOL       helmet_used;        /* The helmet and shield */
							ITEM_POOL       shield_used;        /* that is being used */
							ITEM_POOL       weapon_used;        /* The weapon and armour */
							ITEM_POOL       armour_used;        /* That is being used */
							ITEM_POOL       ring_used;

							int             herbs_carried[MAX_HERBS_CARRY];
							ITEM_POOL       items_carried[MAX_CARRY];

							IN_EFFECT		in_effect;

							unsigned		x : 4;				   /* Combat location */
							unsigned		y : 4;

							char			here_to_fool3;

							unsigned		kills         : 15;
                            unsigned        member_of_HOE : 1;

					} PLAYER;

typedef struct ye_party {                                           /* The day to day */
							int             num_in_party;           /* details of the */
																	/* Adventures     */
							int 			resting;
							int 			fire_lit;

							int             all_dead;

							int             adventuring;            /* TRUE|FALSE */

							int             in_dungeon;             /* TRUE|FALSE */
							int             in_ruin;                /* TRUE|FALSE */
							int             in_town;                /* TRUE|FALSE */
							int             in_combat;              /* TRUE|FALSE */

							int             mapping_in_dungeon;     /* TRUE|FALSE */

							int             dungeon_level;
							int             dungeon_x;
							int             dungeon_y;
							int             dungeon_current_feature;

							long            xp_earned;
							long            gc_earned;

							PLAYER          player[MAX_PARTY];

						 } THE_PARTY;

typedef struct dung_bit   {
							unsigned        mapped          : 1;    /* TRUE|FALSE        */
							unsigned        trap_triggered  : 1;    /* TRUE|FALSE        */
							unsigned        reserved        : 1;
							unsigned        feature         : 6;    /* CHEST|STAIRS etc  */
							unsigned        trap_monst      : 4;    /* Trap/Monster Type */
							unsigned        descrip_no      : 5;    /* 1-32              */

						  } DUNGEON_SQUARE;

typedef struct dungeon_ty {
							char            name[50];
							char            message[80];

							char            file_name[9];
							int             nname;

							int             x_position;
							int             y_position;

							int             level;

							int             spells_work;

							int             number_of_levels;

							int             most_monster_type;

							char            descrip[MAX_DUNGEON_DESCRIP][40];

							DUNGEON_SQUARE  map[MAX_DUNGEON_Z][MAX_DUNGEON_X][MAX_DUNGEON_Y];

						 } DUNGEON_TY;

typedef struct dung_look {
							char            *name;
							char            *message;

							char            *file_name;
							int             nname;

							int             x_position;
							int             y_position;

							unsigned        number_of_levels : 3;
							unsigned        difficulty       : 3;

						 }  DUNGEON_LOOK_TY;

typedef struct s_town    {
							char            *name;

							int             coat_of_arms;

							char            *inn_name;
							int             town_type;

							int             x_position;
							int 			y_position;

							char            *descrip;

							int             ndeity;

						 } SMALL_TOWN;

typedef struct  pent_ty  {                                          /* Global data   */
							int             date;                   /* on the outcome*/
							int             day;                    /* of the game   */
							int 			year;					/* This stuff	 */
							int             time_hour;              /* is permanent  */
							int             time_minute;
							int             season;

							char            st_date[40];

							int             current_day_night_icon;

							int             rain_level;
							int             rain_type;
							int             wind_level;
							int             cloud_level;
							int             temperature;
							int             degrees_c;

							int             finished;

							int             moon_phase;

							int             visited_guild;
							int             date_since_guild_visit;

							unsigned        told_about_talisman : 1;
							unsigned        talisman_1_found    : 1;
							unsigned        talisman_2_found    : 1;
							unsigned        talisman_3_found    : 1;
							unsigned        talisman_4_found    : 1;

							unsigned        sound               : 1;

							unsigned        seer_visited        : 1;
							unsigned        spell_given         : 1;
							unsigned        spectre_visited     : 1;
							unsigned        wand_given          : 1;

							unsigned        devouring_rod_used  : 8;
							unsigned        curious_box_used    : 8;

							unsigned        kaldrutha_defeated  : 1;
							unsigned		mangreth_defeated	: 1;

							int             x;
							int             y;
							int 			current_feature;

							int 			date_visit_wolfburg;
							int 			year_visit_wolfburg;

							int 			combat_speed;

							char            order[MAX_PARTY][20];

							unsigned        checksum;

					} PENT_DATA;


typedef struct herb_type{
							char            *name;
							int             nname;
							int             rarity;
							int             effect;                    /* Poison etc */
							int             coloured_part;             /* Leaf, flower, berries*/
							int             colour;
							int             terrain1;                  /* Hills, mts           */
							int             terrain2;
							int             terrain3;
							int             damage_cure;               /* +ve and -ve          */

						} HERBS;

typedef struct animal_type
						{
							char            *name;
							int             bite_damage;
							int             ram_damage;
							int             rarity;
							int             size;

						} ANIMALS;

typedef struct signpost_type                                           /* Stores signpost data */
						{
							int             x;
							int             y;
							char            *sign_title;
							char            *message;

						} SIGNPOSTS;

typedef struct mon_type {
							char            name[25];
							char            silly_name[25];

							char            image[10];
							char            mask_image[10];

							int             ethics;                 /* Lawful - Chaotic     */

							unsigned long   xp;

							unsigned        hd;
							int 			current_hp;

							int             ac;
							unsigned		max_number			:4;
							unsigned		min_number			:4;
							int             bane_rune_type;         /* Undead, Cold etc     */

							int 			monster_type;			/* Used in selection	*/

							unsigned        poison_chance;          /* Poison %             */
							unsigned        disease_chance;         /* Diseased %           */
							unsigned        disease_type;

                            int             treasure_type;          /* NONE, GOLD, ITEMS etc*/

                            int             attack_type[MAX_ATTACK];          /* Claw, Weapon etc */
							int             attack_damage[MAX_ATTACK];        /* Eg; 10 hp        */

							char            magic_attack_string[25];

							unsigned		can_plane_travel	:1;

							unsigned        poison_immunity     :1; /* TRUE|FALSE           */
							unsigned        fire_immunity       :1; /* TRUE|FALSE           */
							unsigned        ice_immunity        :1; /* TRUE|FALSE           */
							unsigned        electricity_immunity:1; /* TRUE|FALSE           */
							unsigned		mind_spell_immunity :1; /* TRUE|FALSE			*/
							unsigned		quake_immunity		:1; /* TRUE|FALSE			*/
							unsigned        magic_weapon_to_hit :1; /* TRUE|FALSE           */

							unsigned        backstabbable       :1; /* Can be backstabbed   */
							unsigned        stunnable           :1; /* Can be stunned */

						    unsigned        wandering           :1; /* TRUE|FALSE           */
							unsigned        dungeon             :1; /* TRUE|FALSE           */
							unsigned        outdoors            :1; /* TRUE|FALSE           */
							unsigned        hills               :1; /* TRUE|FALSE           */

							unsigned        night_day           :2; /* NIGHT|DAY|BOTH       */

							unsigned        intelligence        :5; /* 0-18                 */
							unsigned        agility             :5; /* 0-18                 */
							unsigned        speed               :5; /* 0=Slow, 18=Superfast */
							unsigned        surprise            :5; /* 0=always surprised!  */

							unsigned		weapon_type		    :4;
							unsigned		speak_type		    :4;

							unsigned        humanoid            :1; /* TRUE|FALSE           */

							unsigned        weakness            :4; /* Major weakness       */

							unsigned		condition		    :4; /* SLEEP etc			*/
                            unsigned        fleeing             :1;
							unsigned        flown               :1;

							unsigned        spell_bound         :3; /* Frozen by Binding Spell */
							unsigned        time_suspended      :3; /* Subject to Suspend Time */
							unsigned        is_stunned          :3; /* Stunned                 */
							unsigned        is_lethargic        :3;

							unsigned		morale_affected     :1; /* Used in combat to see */
							int 			current_morale		:5; /* if a monster flees	 */

							int             eligible            :6; /* TRUE|FALSE for combat */

							unsigned		x				    :4; /* X & Y position */
							unsigned		y				    :4; /* in combat */

							unsigned		flee_x			    :4; /* Flee Target x & y */
							unsigned        flee_y              :4; /* Coordinates */

							unsigned        weak_msg_given      :1; /* If monster msg given */

							PLAYER			*opponent;			    /* Opp. aiming for */

					} MONSTER;

typedef struct ruin_type
						{
							int             x;
							int             y;
							char            *description;
							void            (*func)(void); /* Function for ruin */

						} RUINS;

typedef struct crds     {
							unsigned        suit  : 4;
							unsigned        value : 4;

						} CARDS;

typedef union mon_pl_ty {
							MONSTER         *monster;
							PLAYER          *player;

						} MON_PL;

typedef struct _cmbt_ty {
							MON_PL          occ;
							int             nocc;  /* IS_EMPTY   | IS_WALL   */
												   /* IS_MONSTER | IS_PLAYER */
						} CMBT_CELL;


typedef struct oth_part {
							int             nclass;
							int             condx;

						}   OTHER_PARTY;

typedef struct brd_type {
							int             x,y;
							char            *message;

						} BRIDGES;

typedef struct _rum_type {
							int             opt1;
							int             opt2;
							int             opt3;
							char            *mess;

						} RUMOUR;

typedef struct _rum_idx  {
							unsigned char   rumour_index;                  /* R_CLASS .... */
							unsigned char   rumour_number;                 /* Number of rumours */
							unsigned        rumour_pos[MAX_RUMOUR_INDEX];  /* Pos. of rumour */

						 } RUMOUR_INDEX;

typedef struct _dtype	 {
							char			*name;
							char			*title;
							char			*connect;
							char			*sphere;
							int 			sex;
							int 			ndeity;

						 } DEITY_TYPE;

typedef struct _mag_type {
							int             pts_add;
							int             lv1_add;
							int             lv2_add;
							int             lv3_add;

						 }  LVL_MAGIC_TYPE;

					/**************************
					 *                        *
					 *  Function Prototypes   *
					 *                        *
					 *                        *
					 **************************/


/*
 *  These are in the library MHEGA.LIB. The
 *  library is assembled in the Large Model
 *
 *  Built from :
 *
 *      NORTH.ASM     SOUTH.ASM   EAST.ASM
 *      EGA_ORIG.ASM  FFPLOT.ASM  SCROLLSC.ASM
 *      WEST.ASM      PAGE01.ASM  SCROLLMS.ASM
 *
 */

unsigned     int mem_left(void);
void _CDECL  Fscroll_scroll(void);
void _CDECL  Fscroll_message(int);
void _CDECL  Fscroll_combat(int);
void _CDECL  Fscroll_shield(void);
void _CDECL  scroll_north(void);
void _CDECL  scroll_south(void);
void _CDECL  scroll_east(void);
void _CDECL  scroll_west(void);
void _PASCAL FFPLOT(int,int,char);
void _CDECL  EGA_origin(int,int,int);
void _CDECL  FFpent_pan(void);
void _CDECL  move_EGA_pages(int,int);
void _CDECL  melt_EGA_pages(int,int,int);

/*
 *  Normal Pentagram Source code stuff
 */


#ifdef DEV
void _PASCAL    DEBUG_func(char *,int);
#endif

#ifdef BOMB
void _PASCAL    BOMB_check(void);
#endif

void _CDECL     main(int, char **);
void _CDECL     delay(unsigned);        /* Nicked from TurboC library! */
int  _PASCAL	shut_program_down(int);
void _PASCAL	select_font(void);
void _PASCAL	load_font(int);
void _PASCAL	cls(void);
void _PASCAL	cls_scroll(void);
void _PASCAL	_NEAR cls_show_adventurer(void);
void _PASCAL	scroll_scroll(void);
void _PASCAL	page_in_cmbt_screen(void);
void _PASCAL	page_out_cmbt_screen(void);
void _PASCAL	init_hardware(void);
void _PASCAL	write_little(char *,int,int,int,int);
void _PASCAL	print_text(char *,int,int,int,int);
void _PASCAL	print_tall_char(int,int,int,int);
void _PASCAL	_NEAR print_char(int,int,int,int);
void _PASCAL	print_rune(int,int,int,int);
void _PASCAL	print_rune_string(char *,int,int,int);
void _PASCAL	SCROLL(int,int,char *);
void _PASCAL	scroll_wrap_write(int,char *);
void _PASCAL	combat_write(int,char *,int);
void _PASCAL	draw_full_chain(void);
void _PASCAL	combat_write_mod_line(int,char *,int);
void _PASCAL	cmbt_print_spell_name(SPELL_NAME *);
void _PASCAL	draw_main_screen(int);
void _PASCAL	panic(char *);
void _PASCAL	panic_FILE(char *);
void _PASCAL	panic_RAM(char *);
int  _PASCAL	strlen_half(char *);
int  _PASCAL	plus_or_minus_one(void);
void _PASCAL	click_box(int,int,int);
void _PASCAL	make_gwindow(GWINDOW *);
void _PASCAL	kill_gwindow(GWINDOW *);
void _PASCAL	print_trap_sign(int,int);
void _PASCAL	print_small_dead(int,int,int);
void _PASCAL	show_all_images(int);
void _PASCAL	init_mouse(void);
void _PASCAL	mouse_reset(void);
void _PASCAL	mouse_on(void);
void _PASCAL	mouse_off(void);
void _PASCAL	mouse_mickey_set(int,int);
void _PASCAL	mouse_mickey_restore(void);
void _PASCAL	mouse_set_combat_move_mickey(void);
int  _PASCAL	mouse_button_r(void);
int  _PASCAL	mouse_button_l(void);
void _PASCAL	mouse_shape1(void);
void _PASCAL	mouse_shape2(void);
void _PASCAL	mouse_gotoxy(int,int);
void _PASCAL	mouse_readxy(int *,int *);
void _PASCAL	mouse_mickey(int,int);
void _PASCAL	mouse_horiz_range(int,int);
void _PASCAL	mouse_vert_range(int,int);
void _PASCAL	mouse_half_range(void);
void _PASCAL	mouse_full_range(void);
int  _PASCAL	mouse_in_range(int *, unsigned char *, unsigned char *);
void _PASCAL	mouse_define_pointer(int,int);
void _PASCAL	mouse_put_pointer(int,int);
void _PASCAL	mouse_erase_pointer(int,int);
int  _PASCAL	tick(int,int,int);
void _PASCAL	print_large_title(char *);
int  _PASCAL	wolfburg_menu(void);
void _PASCAL	load_finish_image(void);
void _PASCAL	draw_chain(int,int);
void _PASCAL	draw_HOE_coa(int,int);
void _PASCAL	draw_choose(int,int,int);
void _PASCAL	draw_x_hair(int,int,int);
void _PASCAL	draw_hit(int x,int y);
void _PASCAL	draw_wahs_w(int,int);
void _PASCAL	draw_wahs_a(int,int);
void _PASCAL	draw_wahs_h(int,int);
void _PASCAL	draw_wahs_s(int,int);
void _PASCAL	twinkle(int,int);
void _PASCAL	generic_pic_draw(int,int,char *);
void _PASCAL	draw_alter_arrow(int,int);
void _PASCAL	draw_crystal_ball(int,int);
void _PASCAL	draw_gravestone(int,int);
void _PASCAL	draw_pentagram(int,int,int,int);
void _PASCAL	_NEAR draw_evil_eyes(int,int);
void _PASCAL	_NEAR draw_evil_eyes_part(int,int,int);
void _PASCAL	draw_guild_coa(int,int);
void _PASCAL	draw_dungeon_in(int,int);
void _PASCAL	draw_ruin_image(int,int);
void _PASCAL	draw_cross_image(int,int);
void _PASCAL	draw_dungeon_out(int,int);
void _PASCAL	print_grim_reaper(void);
int  _PASCAL	distance_between_points(int,int,int,int);
void _PASCAL	make_gplease_wait(void);
void _PASCAL	kill_gplease_wait(void);
void _PASCAL	select_adv_sound(void);
void _PASCAL    wake_up_sound(void);
void _PASCAL    korinas_leap_sound(void);
void _PASCAL	spell_finished_sound(void);
void _PASCAL	game_finished_sound(void);
void _PASCAL	next_round_sound(void);
void _PASCAL	pray_sound(void);
void _PASCAL	HOE_sound(void);
void _PASCAL	victory_sound(void);
void _PASCAL	combat_death_sound(void);
void _PASCAL	player_attack_sound(void);
void _PASCAL	click_sound(void);
void _PASCAL	move_player_sound(void);
void _PASCAL	move_monster_sound(void);
void _PASCAL	miss_sound(void);
void _PASCAL	short_prompt_sound(void);
void _PASCAL	hit_sound(void);
void _PASCAL	encounter_sound(void);
void _PASCAL	flee_sound(void);
void _PASCAL	monster_move_sound(void);
void _PASCAL	all_dead_sound(void);
void _PASCAL	potion_sound(void);
void _PASCAL	symptoms_sound(void);
void _PASCAL	use_item_sound(void);
void _PASCAL	advance_level_sound(void);
void _PASCAL	lute_sound(void);
void _PASCAL	mouse_sound(void);
void _PASCAL	sink_sound(void);
void _PASCAL	snotling_sound(void);
void _PASCAL	general_low_sound(void);
void _PASCAL	teleport_up_sound(void);
void _PASCAL	teleport_down_sound(void);
void _PASCAL	incidental_sound(void);
void _PASCAL	found_talisman_bit_sound(void);
void _PASCAL	stairs_up_sound(void);
void _PASCAL	stairs_down_sound(void);
void _PASCAL	treasure_sound(void);
void _PASCAL	voice_sound(void);
void _PASCAL	wand_sound(void);
void _PASCAL	staff_sound(void);
void _PASCAL	trap_sound(void);
void _PASCAL	short_bad_sound(void);
void _PASCAL	bad_sound2(void);
void _PASCAL	solemn_sound(void);
void _PASCAL	death_sound(void);
void _PASCAL	good_sound(void);
void _PASCAL	flash(int,int);
void _PASCAL	draw_treasure_message(void);
void _PASCAL	draw_talisman_part(int,int,int);
void _PASCAL	print_little_lr(int,int);
void _PASCAL	print_big_dungeon_door(int,int);
void _PASCAL	dungeon_encounter_snotling(void);
void _PASCAL	_NEAR dungeon_snotling_sneak_up(PLAYER *);
void _PASCAL	_NEAR dungeon_snotling_has_money(PLAYER *);
unsigned long	_PASCAL _NEAR dungeon_snotling_get_money(PLAYER *);
void _PASCAL	print_up_down(int,int);
void _PASCAL	print_left_right(int,int);
void _PASCAL	draw_sex_sym(int,int,int,int);
void _PASCAL	draw_female_sym(int,int,int);
void _PASCAL	draw_male_sym(int,int,int);
void _PASCAL	draw_eddie_blood(int,int);
void _PASCAL	draw_eddie_blood_materialise(int,int);
void _PASCAL	draw_eddie(int,int);
void _PASCAL	draw_and_erase_eddie(int,int);
char *          give_date(unsigned int);
unsigned long	_PASCAL convert_date_to_half_hours(int,int,int);
void _PASCAL	pause(int);
void _PASCAL	cmbt_pause(int);
void _PASCAL	cmbt_half_pause(void);
void _PASCAL	half_pause(void);
int  _PASCAL	gget_yn(char *);
void _PASCAL	close_program(void);
void _PASCAL	_NEAR make_map_heap(void);
void _PASCAL	_NEAR kill_map_heap(void);
void _PASCAL	hall(void);
void _PASCAL	inn(char *);
void _PASCAL	cathedral(void);
void _PASCAL	cath_pray(PLAYER *);
int  _PASCAL	player_overdue_at_praying(PLAYER *);
long _PASCAL	days_since_last_pray(PLAYER *);
void _PASCAL	cath_resurrect(PLAYER *,PLAYER *, unsigned long);
void _PASCAL	cath_heal(PLAYER *,PLAYER *, unsigned long);
void _PASCAL	cath_cure_disease(PLAYER *,PLAYER *, unsigned long);
void _PASCAL	cath_exorcise(PLAYER *,PLAYER *, unsigned long);
void _PASCAL	cath_remove_poison(PLAYER *,PLAYER *, unsigned long);
void _PASCAL	cath_determine_insurance(PLAYER *,PLAYER *,unsigned long);
void _PASCAL	cath_take_1pc_for_trouble(PLAYER *, unsigned long);
int  _PASCAL	cath_who_is_paying(unsigned long, PLAYER *, PLAYER *);
int  _PASCAL	cath_will_you_pay(unsigned long,char *,PLAYER *);
void _PASCAL	market(void);
void _PASCAL	bank(void);
void _PASCAL	situation_details(void);
void _PASCAL	_NEAR situation_header(char *);
void _PASCAL	training_grounds(void);
void _PASCAL	front_options(void);
void _PASCAL	adventure(void);
void _PASCAL	save_game(int);
void _PASCAL	load_game(int);
void _PASCAL	_NEAR situation_details_page1(void);
void _PASCAL	_NEAR situation_details_page2(void);
void _PASCAL	_NEAR situation_details_page3(void);
void _PASCAL	_NEAR situation_details_page4(void);
void _PASCAL	_NEAR situation_details_page5(void);
void _PASCAL	_NEAR situation_details_page6(void);
void _PASCAL	_NEAR situation_details_page7(void);
void _PASCAL	_NEAR situation_details_page8(void);
void _PASCAL	_NEAR situation_details_page9(void);
void _PASCAL	_NEAR situation_details_cls(void);
void _PASCAL	show_cursor(int);
int  _PASCAL	isvowel(int);
static void 	_PASCAL _NEAR about_pentagram(void);
static void 	_PASCAL _NEAR about_odin(void);
static void 	_PASCAL _NEAR load_about_odin(void);
static void 	_PASCAL _NEAR kill_about_odin(void);
static void 	_PASCAL _NEAR about_odin_cls(void);
static void 	_PASCAL _NEAR about_odin_page(int);
int  _PASCAL	ready_an_adventurer_armour(PLAYER *);
int  _PASCAL	ready_an_adventurer_shield(PLAYER *);
int  _PASCAL	ready_an_adventurer_helmet(PLAYER *);
int  _PASCAL	ready_an_adventurer_weapon(PLAYER *);
int  _PASCAL	ready_an_adventurer_ring(PLAYER *);
int  _PASCAL	ready_an_adventurer(PLAYER *);
void _PASCAL	train_an_adventurer(void);
void _PASCAL	purge_an_adventurer(void);
void _PASCAL	CBOX_write(char *,int);
void _PASCAL	CBOX_please_wait(void);
void _PASCAL	CBOX_turn_on(void);
void _PASCAL	CBOX_scroll(void);
void _PASCAL	CBOX_led(int,int,int,int);
void _PASCAL	CBOX_self_test(void);
void _PASCAL	CBOX_handle_place_name(void);
void _PASCAL	CBOX_battery_low(void);
void _PASCAL	CBOX_search_database(char *);
void _PASCAL	CBOX_town_found(int);
void _PASCAL	CBOX_deity_found(int);
void _PASCAL	CBOX_dungeon_found(int);
void _PASCAL	CBOX_notfound(void);
void _PASCAL	CBOX_turn_off(void);
void _PASCAL	CBOX_print_battery_level(void);
void _PASCAL	check_for_noble_names(PLAYER *);
char *			train_get_free_slot(void);
void _PASCAL	set_default_adv(void);
int  _PASCAL	train_get_race(void);
int  _PASCAL	train_get_class(void);
char *          get_class_string(int,int);
void _PASCAL	train_generate_base_scores(void);
void _PASCAL	train_generate_scores(void);
int  _PASCAL	train_get_class(void);
void _PASCAL	train_alter_scores(void);
int  _PASCAL	train_fake_alter_scores(int *);
void _PASCAL	train_update_graph_scores(int,int,int,int,int,int,int,int);
void _PASCAL	train_get_gender(void);
void _PASCAL	train_get_languages(void);
void _PASCAL	train_update_possible_classes(void);
void _PASCAL	train_get_ethics(void);
void _PASCAL	train_get_ethics_1(void);
void _PASCAL	train_get_ethics_2(void);
void _PASCAL	train_get_ethics_3(void);
void _PASCAL	train_get_second_skills(void);
void _PASCAL	train_get_prev_job(void);
void _PASCAL	train_secondary_by_prev_job(void);
void _PASCAL	train_get_money(void);
void _PASCAL	train_get_height_weight(void);
void _PASCAL	train_get_height(void);
void _PASCAL	train_get_weight(void);
void _PASCAL	train_get_spells(void);
void _PASCAL	train_get_random_spell(void);
void _PASCAL	train_get_age(void);
void _PASCAL	train_get_age_cat(void);
void _PASCAL	train_get_place_of_birth(void);
void _PASCAL	train_get_hand(void);
void _PASCAL	train_get_hp(void);
void _PASCAL	train_get_birthday(void);
void _PASCAL	train_get_deity(void);
void _PASCAL	train_get_speed(void);
void _PASCAL	train_get_max_level(void);
void _PASCAL	check_deity_angry(void);
char *			adv_previous_job(PLAYER *);
char *			get_deity_name_in_town(int,int);
void _PASCAL	deity_angry(PLAYER *);
void _PASCAL	check_hypothermia(void);
void _PASCAL	check_hypothermia_one(PLAYER *);
void _PASCAL	inflict_hypothermia_damage(PLAYER *);
int  _PASCAL	select_a_disc_adventurer(char *,int);
static void 	_PASCAL _NEAR make_all_disc_buffer(void);
static void 	_PASCAL _NEAR kill_all_disc_buffer(void);
int  _PASCAL	change_this_adv_name(PLAYER *);
void _PASCAL	change_adv_name(void);
static void 	_PASCAL _NEAR place_one_person_in_select(PLAYER *,int);
void _PASCAL	add_to_party(void);
int  _PASCAL	party_can_carry_treasure(void);
char *			end_s(char *);
void _PASCAL	check_if_can_join_HOE(PLAYER *);
void _PASCAL	add_take_from_party(void);
int  _PASCAL	init_party_for_adventure(void);
void _PASCAL	generate_initial_party_order(void);
void _PASCAL	process_steps(int *);
void _PASCAL	update_hp_etc_whilst_walking(void);
void _PASCAL	view_an_adventurer(void);
void _PASCAL	add_an_adventurer(void);
void _PASCAL	drop_an_adventurer(void);
void _PASCAL	log_all_disc_players(void);
void _PASCAL	save_global_data(void);
void _PASCAL	load_startup_data(void);
void _PASCAL	load_adv_images(void);
static void 	_PASCAL _NEAR load_one_adv_image(char _FAR [],char *);
void _PASCAL	load_adv_mask_images(void);
static void 	_PASCAL _NEAR load_one_adv_mask_image(char _FAR [],char *);
void _PASCAL	load_global_data(void);
void _PASCAL	setup_global_data(void);
static void 	_PASCAL _NEAR check_global_data_checksum(void);
static unsigned _PASCAL _NEAR global_data_checksum(void);
void _PASCAL	oops(int);
char *          gquery(int,int,int,int,int,char *);
void _PASCAL	_NEAR  draw_moon(int,int,unsigned *);
void _PASCAL	gexclaim(char *,int);
void _PASCAL	sort_adv_items(PLAYER *);
void _PASCAL	sort_pool_items(int);
int  _PASCAL	sort_items_value(ITEM_POOL *);
int  _CDECL     sort_comp(ITEM_POOL *,ITEM_POOL *);
int  _PASCAL	bard_max_songs(PLAYER *);
int  _PASCAL	get_song_duration(PLAYER *);
int  _PASCAL	bard_is_singing(PLAYER *,char *);
int  _PASCAL	show_determine_spells(PLAYER *);
int  _CDECL     show_determine_spells_sort(SPELL_NAME *, SPELL_NAME *);
int  _PASCAL	get_full_item_descrip(ITEM_POOL *,char *);
void _PASCAL	show_adventurer(PLAYER *);
void _PASCAL	_NEAR show_adventurer_1(PLAYER *);
void _PASCAL	_NEAR show_adventurer_2(PLAYER *);
void _PASCAL	_NEAR show_adventurer_3(PLAYER *);
void _PASCAL	_NEAR show_adventurer_4(PLAYER *);
void _PASCAL	_NEAR show_adventurer_5(PLAYER *,int);
void _PASCAL	_NEAR show_adventurer_6(int);
void _PASCAL	_NEAR show_adventurer_7(PLAYER *);
char *          adv_title(PLAYER *);
int  _PASCAL	show_all_spells(int,char [][40]);
void _PASCAL	ruin_teleport_message(void);
void _PASCAL	enter_ruin_display_msg(char *);
void _PASCAL	enter_a_ruin(void);
void _PASCAL	kicked_out_of_moon_temple(int);
void _CDECL     enter_ruin_lochgrim_keep(void);
void _CDECL     enter_ruin_dreadhorn(void);
void _CDECL     enter_ruin_moon_temple(void);
void _CDECL     enter_ruin_moon_keep(void);
void _CDECL     enter_ruin_ironlode_keep(void);
void _CDECL     enter_ruin_silverglade_keep(void);
void _CDECL     enter_ruin_helmhilde_keep(void);
void _CDECL     enter_ruin_cragsclaw_keep(void);
void _CDECL     enter_ruin_helmgaard_keep(void);
void _CDECL     enter_ruin_oldhelm(void);
void _CDECL     enter_ruin_nordhausen(void);
void _CDECL     enter_ruin_castle_hilar(void);
void _CDECL     enter_ruin_castle_latus(void);
void _CDECL     enter_ruin_castle_janus(void);
void _CDECL     enter_ruin_windless_haven(void);
void _CDECL     enter_ruin_monastry(void);
void _CDECL     enter_ruin_escer_fortress(void);
void _PASCAL	ruin_oldhelm_show(void);
void _PASCAL	display_keep_runes(char *);
void _PASCAL	actually_enter_moon_keep(void);
void _PASCAL	kill_thieves_at_moon_keep(int);
void _PASCAL	ruin_windless_haven_draw(void);
void _PASCAL	spectre_give_rod_of_devouring(void);
void _PASCAL	give_rod_of_devouring(int);
static void 	_PASCAL _NEAR ruin_monastry_cleansed(void);
int  _PASCAL	enter_a_celtic_cross(void);
int  _PASCAL	evaluate_level_details(unsigned long *);
void _PASCAL	distribute_pool(void);
void _PASCAL	distribute_update_wahs(PLAYER *,int);
unsigned		long _PASCAL distribute_print_5(int,int,int,char *);
void _PASCAL	distribute_display_sell_price(unsigned long,int,int);
unsigned        long distribute_handle_an_item(int,int,int,ITEM_POOL *,char *);
void _PASCAL	distribute_arrange_draw(void);
int  _PASCAL	take_items_from_adv(PLAYER *);
void _PASCAL	distribute_all_items(int);
void _PASCAL	distribute_draw_screen(GWINDOW *);
void _PASCAL	spell_sound(void);
void _PASCAL	bad_sound(void);
int  _PASCAL	who_is_going(char *);
int  _PASCAL	who_is_going_whilst_adventuring(char *);
void _PASCAL	thank_you(void);
int  _PASCAL	market_get_quantity( char *,int,int);
void _PASCAL	market_armourer(void);
void _PASCAL	market_black_smith(void);
void _PASCAL	market_magic_shoppe(void);
void _PASCAL	_NEAR market_magic_shoppe_rings(void);
void _PASCAL	_NEAR market_magic_shoppe_orbs(void);
void _PASCAL	_NEAR market_magic_shoppe_potions(void);
void _PASCAL	_NEAR market_magic_shoppe_wands(void);
void _PASCAL	_NEAR market_magic_shoppe_misc(void);
void _PASCAL	market_spell_guild(void);
void _PASCAL	market_general_store(void);
void _PASCAL	class_cannot_use(int, char *);
void _PASCAL	not_powerful_enough(int,int);
void _PASCAL	cannot_learn_more(int,int);
void _PASCAL	too_weak_to_use(char *,char *);
void _PASCAL	race_cannot_use(int, char *);
int  _PASCAL	market_get_item_plus(int, char *, unsigned long *);
void _PASCAL	market_wizard_spells1(void);
void _PASCAL	market_wizard_spells2(void);
void _PASCAL	market_wizard_spells3(void);
void _PASCAL	market_illusionist_spells1(void);
void _PASCAL	market_illusionist_spells2(void);
void _PASCAL	market_illusionist_spells3(void);
void _PASCAL	market_priest_spells1(void);
void _PASCAL	market_priest_spells2(void);
void _PASCAL	market_priest_spells3(void);
void _PASCAL	market_druid_spells1(void);
void _PASCAL	market_druid_spells2(void);
void _PASCAL	market_druid_spells3(void);
void _PASCAL	market_put_person_details(GWINDOW *);
void _PASCAL	already_have_spell( char *);
void _PASCAL	dungeon_warfare_act( char *,int);
void _PASCAL	you_only_have(char *, unsigned long);
int  _PASCAL	got_enough_money(unsigned long,PLAYER *);
int  _PASCAL	got_enough_money_not_inv(unsigned long,PLAYER *);
int  _PASCAL	got_enough_money_for_misc(unsigned long, PLAYER *);
void _PASCAL	carry_no_more(PLAYER *);
void _PASCAL	add_to_player(int,int,int,int,PLAYER *);
void _PASCAL	add_to_adv_carry_money_thanks(PLAYER *,long,int,int);
int  _PASCAL	get_first_live_person(void);
int  _PASCAL	someone_in_guild(void);
int  _PASCAL	class_in_party(int);
int  _PASCAL	number_of_items(PLAYER *);
static void 	_PASCAL _NEAR bank_withdraw_all(void);
static void 	_PASCAL _NEAR bank_withdraw_some(void);
static void 	_PASCAL _NEAR bank_deposit_all(void);
static void 	_PASCAL _NEAR bank_deposit_some(void);
static void 	_PASCAL _NEAR bank_pool_all(void);
static void 	_PASCAL _NEAR bank_disperse(void);
static unsigned long _NEAR get_interest_earned_and_update(PLAYER *);
void _PASCAL	new_day(int,int);
void _PASCAL	set_next_day_dawn(void);
void _PASCAL	update_wands_rings_at_midnight(void);
void _PASCAL	update_one_wand_ring(PLAYER *);
void _PASCAL	check_birthdays(void);
void _PASCAL	default_cursor(void);
void _PASCAL	end_of_month(void);
void _PASCAL	evaluate_interest(void);
static void 	_PASCAL _NEAR end_of_month_interest(void);
char *			get_the_weather(void);
int  _PASCAL	effective_temperature(void);
static void 	_PASCAL _NEAR modify_temp_for_latitude(int *);
static void 	_PASCAL _NEAR modify_temp_for_terrain(int *,int);
void _PASCAL	generate_the_weather(void);
char *          stristr(char *,char *);
int  _PASCAL	learn_wiz_ill_spell( char *, long, int, PLAYER *);
int  _PASCAL	learn_pri_dru_spell( char *, long, int, PLAYER *);
int  _PASCAL	show_small_town_data(int,int);
void _PASCAL	quote_on_leaving_town(void);
int  _PASCAL	enter_town_draw_menu(char *);
char *          get_town_details(int,int);
int  _PASCAL	get_town_num(int,int);
void _PASCAL	town_inn(void);
void _PASCAL	town_cathedral(void);
void _PASCAL	town_food_market(void);
void _PASCAL	town_saga_options(void);
int  _PASCAL	town_go_adventuring(void);
void _PASCAL	town_quit_program(void);
void _PASCAL	enter_town(int,int);
void _PASCAL	entering_city_get_taxed(void);
void _PASCAL	thieves_pay_guild(unsigned long);
void _PASCAL	stay_a_night(char *);
char *          inn_rest_one_person(PLAYER *,int *);
void _PASCAL	inn_town_awaken(void);
void _PASCAL	buy_a_drink(char *);
void _PASCAL	save_adventurer(PLAYER *);
char *          rumour_get_subject(void);
char *          rumour_read_quote(int);
int  _PASCAL	rumour_parse_data(char *);
int  _PASCAL	rumour_data_has_swearing(char *);
void _PASCAL	swear_at_barman(void);
void _PASCAL	handle_rumour(void);
int  _PASCAL	rumour_data_is_about_sex(char *);
void _PASCAL	rumour_open_index_file(void);
void _PASCAL	rumour_close_index_file(void);
char *          rumour_get_quote(int);
void _PASCAL	rumour_divulge_info(int);
void _PASCAL	rumour_general_info(int);
void _PASCAL	rumour_town_info(void);
void _PASCAL	rumour_dungeon_info(int);
int  _PASCAL	player_has_dragon_wyvern_ring(PLAYER *);
void _PASCAL	player_is_drunk_so_leave(PLAYER *,char *);
int  _PASCAL	player_is_tipsy(PLAYER *);
int  _PASCAL	player_is_drunk(PLAYER *);
int  _PASCAL	player_is_alive(PLAYER *);
int  _PASCAL	player_is_dead(PLAYER *);
int  _PASCAL	average_level(void);
int  _PASCAL	modified_average_level(void);
char *          get_adv_status(PLAYER *);
char *          get_adv_status_abbr(PLAYER *);
int  _PASCAL	get_status_colour(PLAYER *);
int  _PASCAL	player_is_weak(PLAYER *);
int  _PASCAL	effective_find_herb(PLAYER *);
int  _PASCAL	effective_attacks_per_round(PLAYER *);
int  _PASCAL	effective_open_heavy_door(PLAYER *);
int  _PASCAL	effective_magic_save(PLAYER *,int);
int  _PASCAL	effective_dragon_breath_save(PLAYER *);
int  _PASCAL	effective_trap_save(PLAYER *, int);
int  _PASCAL	effective_player_initiative(PLAYER *);
int  _PASCAL	effective_monster_initiative(MONSTER *);
int  _PASCAL	effective_monster_surprise(MONSTER *);
int  _PASCAL	effective_turn_undead(PLAYER *);
int  _PASCAL	effective_surprise(PLAYER *);
int  _PASCAL	effective_strength(PLAYER *);
int  _PASCAL	effective_intelligence(PLAYER *);
int  _PASCAL	effective_piety(PLAYER *);
int  _PASCAL	effective_agility(PLAYER *);
int  _PASCAL	effective_toughness(PLAYER *);
int  _PASCAL	effective_luck(PLAYER *);
int  _PASCAL	_NEAR adjust_damage_for_spell_luck(PLAYER *);
int  _PASCAL	effective_spell_luck(PLAYER *);
int  _PASCAL	effective_charisma(PLAYER *);
int  _PASCAL	effective_speed(PLAYER *);
int  _PASCAL	get_base_ac(PLAYER *);
int  _PASCAL	effective_ac(PLAYER *);
int  _PASCAL	effective_ac_side(PLAYER *);
int  _PASCAL	effective_ac_back(PLAYER *);
int  _PASCAL	effective_attack(PLAYER *);
int  _PASCAL	effective_player_attack(MONSTER *,PLAYER *);
int  _PASCAL	effective_backstab(MONSTER *,PLAYER *);
int  _PASCAL	effective_damage(PLAYER *,MONSTER *);
int  _PASCAL	effective_missile_damage(PLAYER *,MONSTER *,int);
int  _PASCAL	effective_parry(PLAYER *);
int  _PASCAL	effective_missile(PLAYER *);
int  _PASCAL	effective_disarm_trap(PLAYER *);
int  _PASCAL	effective_find_trap(PLAYER *);
int  _PASCAL	effective_pick_lock(PLAYER *);
int  _PASCAL	effective_snap_thieves_tools(PLAYER *);
void _PASCAL	dng_actually_snap_thieves_tools(PLAYER *,int);
int  _PASCAL	dng_lock_difficulty(int,int,int);
int  _PASCAL	effective_listen(PLAYER *);
int  _PASCAL	effective_move_silently(PLAYER *);
int  _PASCAL	effective_disease_immunity(PLAYER *);
int  _PASCAL	effective_poison_immunity(PLAYER *);
int  _PASCAL	effective_heal(PLAYER *);
int  _PASCAL	effective_heal_rate(PLAYER *);
int  _PASCAL	effective_herb_lore(PLAYER *);
int  _PASCAL	effective_hunt(PLAYER *);
int  _PASCAL	effective_survival(PLAYER *);
int  _PASCAL	effective_swim(PLAYER *);
int  _PASCAL	effective_chance_spot_snotling(PLAYER *);
void _PASCAL	purge_all_in_effects(void);
int  _PASCAL	check_party_globals_in_effect(int);
int  _PASCAL	is_wearing_metal(PLAYER *);
int  _PASCAL	get_random_live_person(void);
int  _PASCAL	player_is_carrying(PLAYER *, int);
int  _PASCAL	player_is_carrying_potion(PLAYER *,int);
int  _PASCAL	player_is_wearing(PLAYER *, int);
int  _PASCAL	load_party_from_disc(void);
void _PASCAL	save_party_to_disc(void);
void _PASCAL	save_party_data_to_disc(void);
void _PASCAL	load_party_data_from_disc(void);
void _PASCAL	update_in_effects(void);
void _PASCAL	update_combat_in_effects(void);
void _PASCAL	go_up_a_level(void);
int  _PASCAL	move_adventurer_up_a_level(void);
void _PASCAL	advance_attrib(void);
void _PASCAL	advance_a_warrior(void);
void _PASCAL	advance_a_priest(int);
void _PASCAL	advance_a_wizard(int);
void _PASCAL	advance_a_druid(int);
void _PASCAL	advance_a_thief(void);
void _PASCAL	advance_a_ranger(int);
void _PASCAL	advance_a_crusader(int);
void _PASCAL	advance_a_bard(void);
void _PASCAL	advance_a_monk(int);
void _PASCAL	advance_a_illusionist(int);
void _PASCAL	advance_a_hunter(int);
void _PASCAL	advance_a_duelist(void);
void _PASCAL	advance_spells(int,int);
void _PASCAL	increase_hp(int);
void _PASCAL	draw_compass_image(int,int);
void _PASCAL	draw_image_box(void);
void _PASCAL	load_adventure_menu(void);
void _PASCAL	clear_adv_menu_heap(void);
void _PASCAL	deal_with_adventure_menu(void);
char *          get_province(int,int);
void _PASCAL	adv_search_province(int,int,int);
void _PASCAL	adv_search(void);
void _PASCAL	determine_secret_doors_nearby(void);
int  _PASCAL	effective_spot_secret_door(PLAYER *);
void _PASCAL	adv_useitem(void);
int  _PASCAL	_NEAR use_hooded_lantern(PLAYER *);
int  _PASCAL	_NEAR use_grimoire(PLAYER *);
int  _PASCAL	use_thieves_tools(PLAYER *);
int  _PASCAL	use_religious_symbol(PLAYER *);
int  _PASCAL	_NEAR use_sextant(PLAYER *);
int  _PASCAL	use_curious_box(PLAYER *);
int  _PASCAL	use_ring_of_fire(PLAYER *);
int  _PASCAL	use_ring_of_icicles(PLAYER *);
int  _PASCAL	actually_use_ring(PLAYER *,int);
int  _PASCAL	use_thunder_wand(PLAYER *);
int  _PASCAL	use_ice_wand(PLAYER *);
int  _PASCAL	use_fire_wand(PLAYER *);
int  _PASCAL	use_healing_stave(PLAYER *);
int  _PASCAL	use_sustenance_wand(PLAYER *);
int  _PASCAL	use_rod_of_devouring(PLAYER *);
int  _PASCAL	actually_use_wand_get_mode(void);
int  _PASCAL	actually_use_wand(PLAYER *,int);
void _PASCAL	wand_attack_failed(void);
void _PASCAL	wand_attack_succeeded(PLAYER *,MONSTER *,int);
int  _PASCAL	actually_use_wand_scatter(PLAYER *,int);
int  _PASCAL	actually_use_wand_solitary(PLAYER *,int);
int  _PASCAL	use_lute(PLAYER *);
void _PASCAL	nullify_combat_area(void);
void _PASCAL	nullify_allys_spells(PLAYER *);
void _PASCAL	nullify_party(void);
void _PASCAL	nullify_pool(void);
void _PASCAL	nullify_all_unbroken_flasks(void);
void _PASCAL	_NEAR nullify_one_unbroken_flasks(PLAYER *);
void _PASCAL	nullify_all_songs(PLAYER *);
void _PASCAL	nullify_all_parrying_flags(void);
void _PASCAL	nullify_all_sneaking_flags(void);
void _PASCAL	nullify_all_combat_spells(void);
void _PASCAL	nullify_all_in_effect(PLAYER *);
void _PASCAL	nullify_all_in_effect_party(void);
char *			potion_get_colour(int,int);
void _PASCAL	potion_remove_from_player(PLAYER *,int);
int  _PASCAL	number_of_hidden_doors(void);
void _PASCAL	print_potion_description(char *,int);
void _PASCAL	give_potion_to_player(PLAYER *,int);
void _PASCAL	adv_drink_potion(void);
void _PASCAL	adv_swap_item(void);
void _PASCAL	adv_equip(void);
void _PASCAL	print_spell_description(char *);
int  _PASCAL	cannot_cast_spell(PLAYER *);
void _PASCAL	adv_cast_spell(void);
void _PASCAL	adv_hunt(void);
void _PASCAL	adv_forage(void);
void _PASCAL	adv_rest(void);
void _PASCAL	attempt_to_rest(void);
void _PASCAL	rest_light_fire(void);
void _PASCAL	rest_animate_hourglass(int,int);
void _PASCAL	rest_draw_hourglass_frame(int,int);
void _PASCAL	rest_update_hourglass(int,int,int);
void _PASCAL	rest_trickle_sand(int,int,int);
void _PASCAL	rest_hg_load_all_images(void);
void _PASCAL	rest_hg_free_all_images(void);
int  _PASCAL	interrupt_rest(void);
void _PASCAL	rest_bed_down_message(void);
void _PASCAL	rest_get_up_message(void);
void _PASCAL	adv_get_rest_time(int *,int *);
void _PASCAL	actually_rest_one_adv(PLAYER *);
void _PASCAL	actually_rest(int,int);
void _PASCAL	adv_rearrange(void);
void _PASCAL	adv_arrange_draw(void);
void _PASCAL	adv_eat(void);
void _PASCAL	adv_inspect(void);
void _PASCAL	select_swap_type(int,int);
int  _PASCAL	swap_item_get_people(int *,int *);
int  _PASCAL	validate_item_use(PLAYER *,USE_SWAP *);
void _PASCAL	_NEAR actually_swap_item_single(int,int);
void _PASCAL	actually_swap_herbs(int,int);
void _PASCAL	_NEAR actually_swap_item_multiple(int,int,int);
int  _PASCAL	_NEAR get_swap_amount(char *, char *,char *,unsigned long int);
int  _PASCAL	actually_use_item(PLAYER *);
int  _PASCAL	check_wand_ring_explodes(PLAYER *,int);
int  _PASCAL	actually_cast_a_spell(PLAYER *);
void _PASCAL	actually_cast_spell_draw_cls(void);
void _PASCAL	actually_cast_spell_draw(int,GWINDOW *,int);
int  _PASCAL	_NEAR spell_dispatch(PLAYER *,SPELL_NAME *);
int  _PASCAL	enough_spell_points_to_cast(PLAYER *,int);
void _PASCAL	add_lost_spell_pts(PLAYER *,int);
void _PASCAL	cast_in_dungeon_only(char *);
void _PASCAL	inflict_spell_damage(PLAYER *,MONSTER *,int,int,int,int,int,void (_FAR *)(int,int),int,int);
void _FAR * 	get_spell_colour_and_dice(int,int *,MONSTER *,int *);
int  _PASCAL	_NEAR get_channeling_damage(PLAYER *,SPELL_NAME *,int);
int  _PASCAL	_NEAR spell_use_channeling(PLAYER *,SPELL_NAME *);
int  _PASCAL	generic_solitary_battle_magic(PLAYER *,SPELL_NAME *,int,int,int,int,int,int,int);
int  _PASCAL	generic_scatter_battle_magic(PLAYER *,SPELL_NAME *,int,int,int,int,int,int);
void _PASCAL	spell_does_naught(void);
int  _PASCAL	cast_spell_correct_situation(PLAYER *, SPELL_NAME *, int);
int  _PASCAL	cast_DRAGONFLAME1(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_HAMMERHAND(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_ARC_LIGHTNING1(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_FIND_HIDDEN_DOOR(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_GRAVMUR_RAGE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_FROZEN_WIND1(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_FIRE_MIST(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_MIGHTY_APPEARANCE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_DRAGONFLAME2(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_LETHARGY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_SWIFTNESS(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_ARC_LIGHTNING2(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_DISPEL_TRAP(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_SINK(PLAYER *, SPELL_NAME *);
int  _PASCAL	_NEAR cast_SINK_lower_xy(int *,int *);
int  _PASCAL	cast_BLINDING_FLASH(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_FROZEN_WIND2(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_DRAGONFLAME3(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_ARC_LIGHTNING3(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_DEATH_CURSE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_BIND_DEMON(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_TELEPORT(PLAYER *, SPELL_NAME *);
void _PASCAL	cast_TELEPORT_get_xy(int *,int *);
int  _PASCAL	cast_FROZEN_WIND3(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_INVOKE_FAMILIAR(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_TWILIGHT(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_NEUTRALISE_POISON(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_PROT_FROM_COLD(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_PROT_FROM_FIRE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CURE_LIGHT_INJURY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CAUSE_LIGHT_INJURY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_HOLY_SPRAY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_DUNGEON_DIVINATION(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_OPEN_CHEST(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_REMOVE_CURSE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CURE_DISEASE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CURE_SEVERE_INJURY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_DISRUPTION(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CAUSE_SEVERE_INJURY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_BLADES(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_PROTECTION_FROM_TRAPS(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_RESURRECT(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CURE_CRITICAL_INJURY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CAUSE_CRITICAL_INJURY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_priest_cure_spells(PLAYER *, int);
int  _PASCAL	cast_priest_cause_spells(PLAYER *,SPELL_NAME *);
int  _PASCAL	cast_SPELL_OF_PASSAGE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_MISSILE_CLOAK(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_HORRIFY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_SLY_EARS(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CATS_EYES(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_PHANTASM1(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_STAR_FLARE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_MOON_FLARE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CREATE_ARTIFACTS(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_SUN_FLARE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_SUSPEND_TIME(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_AXELS_BLUR(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_ALLYS_DANCING_DAGGER(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_JONAS_SPOOK(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_KORINAS_LEAP(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_PHANTASM2(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_AXELS_SHIMMER(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_ALLYS_DANCING_MACE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_AXELS_SHADOW(PLAYER *, SPELL_NAME *);
int  _PASCAL	_NEAR cast_generic_AXEL(PLAYER *, SPELL_NAME *,int);
int  _PASCAL	cast_MIRAGE(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_PHANTASM3(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_ALLYS_DANCING_SABRE(PLAYER *, SPELL_NAME *);
int  _PASCAL	_NEAR cast_generic_ALLYS_spell(PLAYER *, SPELL_NAME *,int);
void _PASCAL	ALLYS_spell_actually_hit(PLAYER *);
int  _PASCAL	_NEAR cast_HORRIFY_or_JONAS_SPOOK(PLAYER *,SPELL_NAME *,int);
int  _PASCAL	cast_TRUEFLIGHT(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_WALK_ON_WATER(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_FLAME_SHEET(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_RAZOR_LEAVES1(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_POISON_IMMUNITY(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_PLANT_FEAST(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_AURA_OF_PROTECTION(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_RAZOR_LEAVES2(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_TANGLE_THORNS(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_MINDS_EYE(PLAYER *, SPELL_NAME *);
int  _PASCAL	actually_cast_MINDS_EYE(PLAYER *, SPELL_NAME *);
void _PASCAL	cast_MINDS_EYE_make_sound(void);
void _PASCAL	cast_MINDS_EYE_display_party(int,int);
int  _PASCAL	cast_ICE_HAMMER(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_ASCERTAIN_POWER(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_BANISH_ELEMENTAL(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_RAZOR_LEAVES3(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_CALL_HAILSTORM(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_MAELSTROM(PLAYER *, SPELL_NAME *);
int  _PASCAL	cast_EARTHQUAKE(PLAYER *, SPELL_NAME *);
char *          select_swap_item(PLAYER *,PLAYER *);
void _PASCAL	select_song_to_sing(PLAYER *);
void _PASCAL	_NEAR  draw_map_square(int,int,int);
void _PASCAL	draw_night_map(void);
void _PASCAL	draw_map(int);
void _PASCAL	draw_first_map(void);
void _PASCAL	place_map(void);
void _PASCAL	kill_map(void);
static void 	_PASCAL _NEAR load_one_map_icon(char _FAR [],char *);
void _PASCAL	load_map(void);
void _PASCAL	load_map_icons(void);
void _PASCAL	_NEAR position_party_on_map(void);
int  _PASCAL	_NEAR determine_road_shape(int,int);
void _PASCAL	cannot_go_direction(char *);
int  _PASCAL	go_north(void);
int  _PASCAL	go_south(void);
int  _PASCAL	go_east(void);
int  _PASCAL	go_west(void);
void _PASCAL	_NEAR fill_northern_map(void);
void _PASCAL	_NEAR fill_southern_map(void);
void _PASCAL	_NEAR fill_eastern_map(void);
void _PASCAL	_NEAR fill_western_map(void);
int  _PASCAL	adv_select_adventurer(char *,char *,int);
void _PASCAL	draw_adv_image(int,int,int);
void _PASCAL	draw_adv_cmbt_image(int,int,int);
void _PASCAL	display_coordinates(void);
void _PASCAL	divulge_signpost_info(int,int);
void _PASCAL	divulge_bridge_info(int,int);
void _PASCAL	divulge_ruin_info(int,int);
void _PASCAL	divulge_dungeon_info(int,int);
void _PASCAL	adv_actually_eat(PLAYER *);
void _PASCAL	adv_actually_use_herbs(PLAYER *);
void _PASCAL	remove_herb_from_adv(PLAYER *,int);
void _PASCAL	adv_sort_herbs(PLAYER *);
int  _CDECL     herb_sorter(int *,int *);
char *          get_herb_name(int,int);
int  _PASCAL	adv_num_herbs(PLAYER *);
void _PASCAL	day_night(void);
int  _PASCAL	determine_day_nite_icon(void);
int  _PASCAL	is_night_time(void);
char *          get_time_string(int,int);
int  _PASCAL	check_today_is_sunday_msg(char *);
void _PASCAL	load_day_night_icons(void);
void _PASCAL	load_one_day_night_icon(char _FAR [],char *);
void _PASCAL	draw_first_day_night(void);
void _PASCAL	celtic_cross(void);
void _PASCAL	effects_at_celtic_cross(void);
int  _PASCAL	percent(void);
int  _PASCAL	combat(int);
void _PASCAL    cmbt_initial_msg(int);
void _PASCAL    cmbt_end_msg(int,int);
int  _PASCAL	build_entire_combat_arena(int);
void _PASCAL	load_cmbt_options(void);
void _PASCAL	load_cmbt_rip(void);
void _PASCAL	kill_cmbt_options(void);
void _PASCAL	load_cmbt_images(void);
void _PASCAL	kill_cmbt_rip(void);
void _PASCAL	kill_cmbt_images(void);
void _PASCAL	draw_combat_logo(void);
void _PASCAL	draw_cmbt_wall(int,int);
void _PASCAL	draw_cmbt_grass(int,int);
int  _PASCAL	get_next_round_option(void);
int  _PASCAL	next_round_flee(void);
int  _PASCAL	next_round_parley(void);
void _PASCAL	next_round_MSPK_NONE(void);
void _PASCAL	next_round_MSPK_HROOM(void);
void _PASCAL	next_round_MSPK_GRUNT(void);
void _PASCAL	next_round_MSPK_SWEAR(void);
void _PASCAL	next_round_MSPK_MOAN(void);
void _PASCAL	next_round_MSPK_FRIENDLY(void);
void _PASCAL	next_round_MSPK_OFF_HAND(void);
void _PASCAL	display_monster_speak(char *,int);
void _PASCAL	reduce_hp(PLAYER *,int,int);
int  _PASCAL	player_holding_edged_weapon(PLAYER *);
void _PASCAL	player_has_died(PLAYER *,int);
void _PASCAL	player_has_died_set(PLAYER *);
int  _PASCAL	is_all_party_dead(void);
void _PASCAL	load_animated_skulls(void);
void _PASCAL	animate_skull(int,int);
void _PASCAL	kill_animated_skull(void);
void _PASCAL	perform_death_of_party(void);
void _PASCAL	dead_print_text_scan(char *,int,int,int,int *);
void _PASCAL	dead_smooth_scroll_window(int);
void _PASCAL	dead_draw_fancy_box(void);
void _PASCAL	dead_place_text(void);
void _PASCAL	print_all_dead_message(void);
int  _PASCAL	get_dice_roll(int,int,int);
int  _PASCAL	get_d20(void);
void _PASCAL	all_party_damaged_swim(void);
void _PASCAL	all_party_damaged_trap(void);
void _PASCAL	all_party_damaged_hail(void);
void _PASCAL	all_party_damaged_electricty(void);
void _PASCAL	all_party_damaged_fire(void);
void _PASCAL	all_party_damaged_cold(void);
void _PASCAL	all_party_damaged_fall(void);
void _PASCAL	incidentals(void);
char *          incidental_daytime_adventuring(void);
void _PASCAL	incidental_special(void);
void _PASCAL	incidental_adventuring(void);
void _PASCAL	incidental_dungeon(void);
void _PASCAL	incidental_dungeon_sounds(void);
void _PASCAL	incidental_dispatcher(char *);
void _PASCAL	incidental_ghostly_figure(void);
void _PASCAL	dungeon_blow_out_light(void);
void _PASCAL    incidental_khazad_dum(void);
void _PASCAL	meet_random_party(void);
long _PASCAL	non_magic_treasure(void);
void _PASCAL	magic_treasure(void);
void _PASCAL	mt_potion(void);
void _PASCAL	mt_weapon(void);
void _PASCAL	mt_ring(void);
void _PASCAL	mt_wand(void);
void _PASCAL	_NEAR shake_side(void);
void _PASCAL	_NEAR shake_up(void);
void _PASCAL	_NEAR shake_diag(void);
void _PASCAL	shake_screen_explode(void);
void _PASCAL	shake_screen(void);
void _PASCAL	load_card_images(void);
void _PASCAL	kill_card_images(void);
void _PASCAL	hall_play_high_low(void);
void _PASCAL	hall_play_black_jack(void);
void _PASCAL	hall_play_wizard_dice(void);
void _PASCAL	hall_play_demon_marbles(void);
void _PASCAL	hall_draw_card_back(int,int);
void _PASCAL	hall_draw_card_front(int,int,int,int);
long _PASCAL	hall_get_bet(void);
void _PASCAL	hall_shuffle_cards(void);
int  _PASCAL	hall_high_low_select(void);
void _PASCAL	hall_pointing_hand(int,int);
void _PASCAL	hall_kill_pointing_hand(int,int);
void _PASCAL	hall_get_rules(void);
void _PASCAL	_NEAR hall_get_rules_high_low(int,int);
void _PASCAL	_NEAR hall_get_rules_wizard_dice(int,int);
void _PASCAL	_NEAR hall_get_rules_blackjack(int,int);
void _PASCAL	_NEAR hall_get_rules_marbles(int,int);
void _PASCAL	_NEAR hall_get_rules_cls(void);
void _PASCAL	hall_get_attacked(void);
void _PASCAL	hall_place_dice(void);
int  _PASCAL	hall_shake_dice(int);
int  _PASCAL	hall_dice_select_bet(void);
int  _PASCAL	hall_card_add(int);
int  _PASCAL	hall_another_card(void);
void _PASCAL	_NEAR marbles_startscreen(void);
void _PASCAL	_NEAR marbles_updatescreen(int,int);
void _PASCAL	_NEAR marbles_playerselect(void);
void _PASCAL	_NEAR marbles_computerselect(void);
void _PASCAL	_NEAR marbles_evaluate(void);
void _PASCAL	_NEAR marbles_won(int);
int  _PASCAL	_NEAR marbles_new(int,int);
static	void	_PASCAL _NEAR  marbles_cursor(int,int,int);
void _PASCAL	_NEAR  draw_marble(int,int,int,int);
void _PASCAL	bane_rune_acquire(void);
void _PASCAL	bane_rune_draw(int,int,int,int);
int  _PASCAL	bane_rune_yes_no(void);
int  _PASCAL	bane_rune_type(void);
void _PASCAL	bane_rune_announce(void);
int  _PASCAL	bane_rune_select_adv(void);
void _PASCAL	contract_diseases_in_combat(PLAYER *,MONSTER *);
void _PASCAL	contract_grave_rot(PLAYER *);
void _PASCAL	contract_pox(PLAYER *);
void _PASCAL	contract_plague(PLAYER *);
void _PASCAL	disease_display_symptoms(PLAYER *);
void _PASCAL	recover_from_disease(PLAYER *);
void _PASCAL	disease_inflict_damage(PLAYER *);
void _PASCAL	disease_update_all_players(void);
void _PASCAL	drink_or_taste_potion(void);
int  _PASCAL	get_potion_to_drink(PLAYER *,int);
void _PASCAL	potion_down_the_hatch_taste(PLAYER *, int, char *);
void _PASCAL	potion_down_the_hatch_drink(PLAYER *, int);
void _PASCAL	actually_hunt(PLAYER *);
char * _PASCAL	actually_hunt_ram(PLAYER *,ANIMALS *);
char * _PASCAL	actually_hunt_bite(PLAYER *,ANIMALS *);
int  _PASCAL	actually_hunt_find_chance(PLAYER *);
char * _PASCAL	actually_hunt_get_damaged(PLAYER *,ANIMALS *);
int  _PASCAL	actually_hunt_get_animal(void);
void _PASCAL	actually_forage(PLAYER *);
int  _PASCAL	get_printer_type(void);
void _PASCAL	get_printer_EPSON(void);
void _PASCAL	get_printer_IBM(void);
void _PASCAL	get_printer_LASER(void);
void _PASCAL	print_banner(void);
void _PASCAL	prn(char *);
void _PASCAL	print_adventurer(PLAYER *);
void _PASCAL	print_adventurer_1(PLAYER *);
void _PASCAL	print_adventurer_2(PLAYER *);
void _PASCAL	print_adventurer_3(PLAYER *);
void _PASCAL	print_adventurer_4(PLAYER *);
void _PASCAL	print_adventurer_5(PLAYER *);
int  _PASCAL	test_printer(void);
void _PASCAL	oops_here_comes_the_boss(void);
void _PASCAL	build_boss_screen(void);
void _PASCAL	drink_POT_SECRET_DOOR(PLAYER *, char *, char *);
void _PASCAL	drink_POT_STRENGTH(PLAYER *, char *, char *);
void _PASCAL	drink_POT_STRIKING(PLAYER *, char *, char *);
void _PASCAL	drink_POT_UNDEAD_TURN(PLAYER *, char *, char *);
void _PASCAL	drink_POT_FIRE_RESIST(PLAYER *, char *, char *);
void _PASCAL	drink_POT_COLD_RESIST(PLAYER *, char *, char *);
void _PASCAL	drink_POT_HEALING(PLAYER *, char *, char *);
void _PASCAL	drink_POT_REVIVING(PLAYER *, char *, char *);
void _PASCAL	drink_POT_POISON(PLAYER *, char *, char *);
void _PASCAL	drink_POT_HOLYWATER(PLAYER *, char *, char *);
void _PASCAL	drink_POT_NOTHING(PLAYER *, char *, char *);
void _PASCAL	drink_POT_CURE_DISEASE(PLAYER *, char *, char *);
void _PASCAL	drink_POT_ALCOHOL(PLAYER *, char *, char *);
char *          familiar_type(PLAYER *);
void _PASCAL	find_a_herb(PLAYER *);
int  _PASCAL	get_a_random_herb(void);
int  _PASCAL	get_herb_number(int);
void _PASCAL	add_herb_to_player(int,PLAYER *);
void _PASCAL	swap_add_herb_to_player(int,PLAYER *);
char *          describe_herb(int);
void _PASCAL	herb_found(int,PLAYER *);
void _PASCAL	herb_not_found(PLAYER *);
int  _PASCAL	chance_of_finding_herb(int,int);
int  _PASCAL	select_a_herb_from_list(PLAYER *);
void _PASCAL	actually_eat_herb(PLAYER *,int);
void _PASCAL	distribute_xp_gc(unsigned long);
void _PASCAL	add_xp_to_party(unsigned long);
void _PASCAL	check_for_HOE(void);
void _PASCAL	can_join_HOE(PLAYER *);
void _PASCAL	distribute_gc(void);
void _PASCAL	print_menu_options(char **,int,char *,int,int,int,int);
void _PASCAL	null_all_professionalism(void);
void _PASCAL	add_to_professionalism(PLAYER *, int);
int  _PASCAL	get_dungeon_number(int,int);
char *          get_dungeon_basename(int);
void _PASCAL	load_dungeon(char *);
void _PASCAL	save_dungeon(char *);
void _PASCAL	explore_dungeon(int *);
int  _PASCAL	handle_dungeon_up_down(char *);
int  _PASCAL	take_dungeon_level_up(void);
int  _PASCAL	take_dungeon_level_down(void);
void _PASCAL	actually_enter_dungeon(void);
void _PASCAL	draw_all_mapped_dungeon_level(int);
void _PASCAL	draw_all_dungeon_walls(void);
void _PASCAL	place_dungeon_map(void);
void _PASCAL	kill_dungeon_map(void);
void _PASCAL	draw_one_dungeon_bit(int,int,int,int);
void _PASCAL	init_dungeon_entry(void);
int  _PASCAL	dungeon_move(int);
int  _PASCAL	draw_dungeon_party(int,int,int);
void _PASCAL	dungeon_deal_with_feature(int);
void _PASCAL	dng_search(void);
void _PASCAL	dng_useitem(void);
void _PASCAL	dng_drink_potion(void);
void _PASCAL	dng_swap_item(void);
void _PASCAL	dng_equip(void);
void _PASCAL	dng_cast_spell(void);
void _PASCAL	dng_door(void);
int  _PASCAL	dng_handle_multiple_doors(int,int,int,int,int);
void _PASCAL	dng_deal_with_heavy_door(int,PLAYER *);
void _PASCAL	dng_deal_with_locked_door(int,PLAYER *);
void _PASCAL	dng_door_handled_ok(int);
void _PASCAL	dng_chest(void);
void _PASCAL	dng_rest(void);
void _PASCAL	dng_rearrange(void);
void _PASCAL	dng_eat(void);
void _PASCAL	dng_inspect(void);
void _PASCAL	deal_with_dungeon_menu(void);
void _PASCAL	load_dungeon_menu(void);
void _PASCAL	clr_dng_menu_heap(void);
void _PASCAL	bang_into_dungeon_wall(void);
void _PASCAL	bang_into_pillar(void);
void _PASCAL	bang_into_dungeon_bit(char *);
void _PASCAL	dungeon_redraw_feature(int,int,int,int);
void _PASCAL	dungeon_view_from_party(int,int,int);
int  _PASCAL	_NEAR  see_through(int,int,int);
void _PASCAL	dungeon_print_level(int);
void _PASCAL	dungeon_print_description(char *);
void _PASCAL	land_on_trap(int);
int  _PASCAL	spot_trap(PLAYER *);
void _PASCAL	disarm_trap(PLAYER *,int);
char *          get_trap_name(int);
void _PASCAL	trigger_trap(int);
void _PASCAL	trigger_TRAP_SPEAR(void);
void _PASCAL	trigger_TRAP_ACID_SQUIRT(void);
void _PASCAL	trigger_TRAP_ARROW(void);
void _PASCAL	trigger_TRAP_POISON_ARROW(void);
void _PASCAL	trigger_TRAP_GAS(void);
void _PASCAL	trigger_TRAP_PIT(void);
void _PASCAL	trigger_TRAP_SPIKED_PIT(void);
void _PASCAL	trigger_TRAP_POISON_SPIKED_PIT(void);
void _PASCAL	trigger_TRAP_ROCKS(void);
void _PASCAL	trigger_TRAP_ELECTRICITY(void);
void _PASCAL	trigger_TRAP_FIREBALL(void);
void _PASCAL	trigger_trap_message(char *);
void _PASCAL	display_trap_window(void);
int  _PASCAL	modified_damage(int);
int  _PASCAL	select_person_to_disarm_trap(void);
void _PASCAL	create_damage_window(GWINDOW *);
void _PASCAL	damage_window_wait_kill(GWINDOW *,int);
void _PASCAL	open_dungeon_door(void);
void _PASCAL	dungeon_voice(void);
void _PASCAL	open_secret_dungeon_door(void);
void _PASCAL	land_on_dungeon_chest(void);
void _PASCAL	land_on_dungeon_voice(void);
void _PASCAL	land_on_dungeon_special(int);
void _PASCAL	depict_dungeon_levels(int,int,int);
void _PASCAL	bang_into_heavy_door(void);
void _PASCAL	bang_into_locked_door(void);
void _PASCAL	remark_on_leaving_dungeon(unsigned long,unsigned long);
void _PASCAL	encrypt_dungeon_descriptions(void);
void _PASCAL	decrypt_dungeon_descriptions(void);
int  _PASCAL	town_cath_who_is_paying(unsigned long,PLAYER *, PLAYER *,int *);
void _PASCAL	dng_open_chest(PLAYER *,int,int,int,int);
void _PASCAL	dng_inspect_chest(PLAYER *,int);
void _PASCAL	dng_handle_locked_chest(PLAYER *,int,int,int,int);
int  _PASCAL	dng_chest_trap_type(int,int,int);
void _PASCAL	dng_disarm_chest(PLAYER *,int,int,int,int);
void _PASCAL	dng_pick_chest(PLAYER *,int,int,int,int);
void _PASCAL	dng_dispel_chest(PLAYER *);
void _PASCAL	dng_cast_open_chest(PLAYER *);
void _PASCAL	look_inside_chest(void);
void _PASCAL	dng_trigger_chest_trap(PLAYER *,int,int,int);
int  _PASCAL	is_a_guild_member(PLAYER *);
int  _PASCAL	determine_last_guild_visit(void);
void _PASCAL	guild_draw_face(GWINDOW *);
void _PASCAL	first_visit_to_guild(void);
void _PASCAL	more_visits_to_guild(void);
void _PASCAL	visit_guild_too_early(void);
void _PASCAL	guild_recruit_members(unsigned long);
void _PASCAL	stars_draw_line(int,int);
void _PASCAL	stars_draw_point(int,int,int);
void _PASCAL	stars_draw_kayne(int,int);
void _PASCAL	stars_draw_glamhelm(int,int);
void _PASCAL	stars_draw_gellen(int,int);
void _PASCAL	stars_draw_incuus(int,int);
void _PASCAL	special_passing_text(void);
void _PASCAL	special_lostsoul(int,int);
void _PASCAL	special_damned(int,int);
void _PASCAL	special_crypt(int,int);
void _PASCAL	special_mort(int,int);
void _PASCAL	special_moribund(int,int);
void _PASCAL	special_hells(int,int);
void _PASCAL	special_misery(int,int);
void _PASCAL	curse_a_player(PLAYER *);
void _PASCAL	_NEAR  special_lostsoul0(int);
void _PASCAL	_NEAR  special_lostsoul1(int);
void _PASCAL	_NEAR  special_lostsoul2(void);
void _PASCAL	_NEAR  special_damned0(int);
void _PASCAL	_NEAR  special_damned1(void);
void _PASCAL	_NEAR  special_damned2(void);
void _PASCAL	_NEAR  special_damned3(void);
void _PASCAL	_NEAR  special_crypt0(int);
void _PASCAL	_NEAR  special_crypt1(void);
void _PASCAL	_NEAR  special_mort0(int);
void _PASCAL	_NEAR  special_mort1(void);
void _PASCAL	_NEAR  special_mort2(int);
void _PASCAL	_NEAR  special_mort3(void);
void _PASCAL	_NEAR  special_moribund0(void);
void _PASCAL	_NEAR  special_moribund1(void);
void _PASCAL	_NEAR  special_moribund2(void);
void _PASCAL	_NEAR  special_hells0(int);
void _PASCAL	_NEAR  special_hells1(void);
void _PASCAL	_NEAR  special_hells2(int);
void _PASCAL	special_hells2_resurrect(void);
void _PASCAL	_NEAR  special_hells3(int);
void _PASCAL	_NEAR  special_misery0(void);
void _PASCAL	special_make_gwindow(void);
void _PASCAL	special_kill_gwindow(void);
void _PASCAL	special_wait(void);
void _PASCAL	special_found_talisman_bit(void);
int  _PASCAL	special_update_talisman_details(void);
void _PASCAL	set_to_corridor(void);
int  _PASCAL	display_and_solve_riddle(char **,int,char *,char **,int);
void _PASCAL	read_guild_flyer(int);
void _PASCAL	got_riddle_wrong(int);
void _PASCAL	build_combat_screen(void);
void _PASCAL	tell_talisman_story(void);
void _PASCAL	treebeard(void);
int  _PASCAL	build_meeting_party(OTHER_PARTY[MAX_PARTY]);
int  _PASCAL	other_party_get_condx(void);
char *          get_condx_string(int);
int  _PASCAL	select_random_dungeon(void);
void _PASCAL	display_part_of_dungeon_map(int);
void _PASCAL	game_finished(void);
void _PASCAL	check_if_game_finished(void);
static void 	_PASCAL _NEAR  poison_weapon(PLAYER *);
static int		_PASCAL _NEAR  player_has_poison(PLAYER *);
static void 	_PASCAL _NEAR  remove_one_poison_vial(PLAYER *);
static void 	_PASCAL _NEAR  put_poison_on_weapon(PLAYER *);
static void 	_PASCAL _NEAR  check_for_poison_cut(PLAYER *adv);
int  _PASCAL	drop_poison_for_weapon_used(PLAYER *);
char *			get_weapon_name(int);
void _PASCAL	build_and_pos_monsters(int,int);
void _PASCAL	pos_party(int);
void _PASCAL	pos_monst(int,int);
static void 	_PASCAL _NEAR  pos_monst_in_open_area(int);
static void 	_PASCAL _NEAR  pos_monst_in_corridor_area(int);
static void 	_PASCAL _NEAR  pos_monst_in_LL_area(int);
static void 	_PASCAL _NEAR  pos_monst_in_LR_area(int);
static void 	_PASCAL _NEAR  pos_monst_in_X_area(int);
void _PASCAL	_NEAR  set_monster_defaults(MONSTER *);
int  _PASCAL	_NEAR  build_monster(int,MONSTER *);
int  _PASCAL	_NEAR  load_mangreth_stats(void);
int  _PASCAL	_NEAR  load_kaldrutha_stats(void);
void _PASCAL	_NEAR  load_monster_mask(void);
void _PASCAL	build_monster_get_opponent(MONSTER *);
int  _PASCAL	build_monsters(int);
void _PASCAL	_NEAR  load_monster_database(void);
void _PASCAL	_NEAR  kill_monster_database(void);
void _PASCAL	_NEAR  load_monster_image(void);
int  _PASCAL	_NEAR  get_fuzzy_monster_type(int,int);
void _PASCAL	_NEAR  fuzzy_mask_dungeon_monsters(void);
void _PASCAL	_NEAR  fuzzy_promote_hill_monsters(void);
void _PASCAL	_NEAR  fuzzy_mask_outdoor_monsters(void);
void _PASCAL	_NEAR  fuzzy_mask_day_nite(void);
int  _PASCAL	_NEAR  get_monster_type(void);
void _PASCAL	_NEAR  nullify_monster_eligible(void);
void _PASCAL	_NEAR  fuzzy_bracket_monsters(void);
int  _PASCAL	_NEAR  fuzzy_get_num_eligible(int *);
int  _PASCAL	_NEAR  choose_monster_from_eligibles(int,int);
void _PASCAL	_NEAR  fuzzy_by_level(int);
void _PASCAL	_NEAR  fuzzy_by_type(int,int);
int  _PASCAL	determine_combat_area_size(void);
static int		_PASCAL _NEAR  solid(int);
void _PASCAL	init_cmbt_area(int);
int  _PASCAL	start_combat(void);
static void 	_PASCAL _NEAR  pos_party_in_open_area(void);
static void 	_PASCAL _NEAR  pos_party_in_LL_area(void);
static void 	_PASCAL _NEAR  pos_party_in_LR_area(void);
static void 	_PASCAL _NEAR  pos_party_in_X_area(void);
static void 	_PASCAL _NEAR  pos_party_in_corridor_area(void);
void _PASCAL	pos_party_member(PLAYER *,int,int);
void _PASCAL	pos_one_monster(MONSTER *,int,int);
void _PASCAL	handle_combat_result(int);
int  _PASCAL	cmbt_area_contents(int,int);
void _PASCAL	cmbt_area_nullify_square(int,int);
static void 	_PASCAL _NEAR  cmbt_draw_monster(int,int);
static void 	_PASCAL _NEAR  cmbt_blank_square(int,int);
void _PASCAL	cmbt_draw_rip(int,int);
void _PASCAL	cmbt_display_slaughter(int,int);
void _PASCAL	cmbt_dissolve_square(int,int);
void _PASCAL	cmbt_between_points(int,int,int,int,int *,int *,void (_FAR *)(int,int));
void _PASCAL	cmbt_player_phys_hits(PLAYER *,MONSTER *,int);
void _PASCAL	cmbt_monster_phys_hits(PLAYER *,MONSTER *,int);
void _PASCAL	cmbt_player_phys_misses(PLAYER *);
void _PASCAL	cmbt_monster_is_slain(PLAYER *,MONSTER *);
void _PASCAL	_NEAR  cmbt_check_monster_weak_msg(MONSTER *);
void _PASCAL	cmbt_player_is_slain(PLAYER *);
void _PASCAL	cmbt_player_is_weak(PLAYER *);
int  _PASCAL	determine_battle_order(void);
void _PASCAL	determine_surprise(void);
void _PASCAL	determine_battle_order_sort(int);
int  _CDECL     PLAY_MONST_compare_initiative(CMBT_CELL *, CMBT_CELL *);
int  _PASCAL	PLAY_MONST_is_alive(CMBT_CELL *);
void _PASCAL	PLAY_MONST_round(CMBT_CELL *);
static void 	_PASCAL _NEAR  init_open_area(void);
static void 	_PASCAL _NEAR  init_corridor_area(void);
static void 	_PASCAL _NEAR  init_LL_area(void);
static void 	_PASCAL _NEAR  init_LR_area(void);
static void 	_PASCAL _NEAR  init_X_area(void);
void _PASCAL	load_cmbt_wall(void);
void _PASCAL	kill_cmbt_wall(void);
void _PASCAL	cmbt_handle_options(PLAYER *);
void _PASCAL	cmbt_handle_options_draw_im(void);
int  _PASCAL	cmbt_thrust(PLAYER *);
int  _PASCAL	cmbt_slash(PLAYER *);
int  _PASCAL	cmbt_bludgeon(PLAYER *);
void _PASCAL	cmbt_DEBUG(void);
void _PASCAL	cmbt_player_does_naught(PLAYER *);
void _PASCAL	display_hit_name(PLAYER *,int);
int  _PASCAL	cmbt_missile(PLAYER *);
static int		_PASCAL _NEAR  modify_missile_for_distance(int,int,int,int);
static int		_PASCAL _NEAR  modify_missile_for_magic(PLAYER *,int);
static void 	_PASCAL _NEAR  cmbt_get_missed_missile_pos(int *,int *);
static void 	_PASCAL _NEAR  cmbt_missile_missed_msg(void);
static void 	_PASCAL _NEAR  cmbt_missile_hit_wall_msg(int,int);
void _PASCAL	cmbt_missile_hit_adv(PLAYER *,PLAYER *,int);
void _PASCAL	cmbt_player_is_missiled(PLAYER *, PLAYER *, char *,int);
int  _PASCAL	cmbt_missile_sling(PLAYER *);
int  _PASCAL	cmbt_missile_crossbow(PLAYER *);
int  _PASCAL	cmbt_missile_bow(PLAYER *);
int  _PASCAL	cmbt_missile_dart_oil_water(PLAYER *);
int  _PASCAL	cmbt_missile_dart(PLAYER *);
int  _PASCAL	cmbt_missile_oil(PLAYER *);
int  _PASCAL	cmbt_missile_water(PLAYER *);
int  _PASCAL	cmbt_missile_which_arrow(int,int,int,int);
int  _PASCAL	cmbt_generic_missile(PLAYER *,int,void (_FAR *)(int,int));
int  _PASCAL	cmbt_generic_oil_water(PLAYER *,int);
void _PASCAL	_NEAR  cmbt_hath_no_item(char *);
int  _PASCAL	cmbt_use(PLAYER *);
int  _PASCAL	_NEAR  cmbt_swap_weapon(PLAYER *);
int  _PASCAL	_NEAR  cmbt_turn(PLAYER *);
int  _PASCAL	_NEAR  cmbt_cast(PLAYER *);
int  _PASCAL	_NEAR  cmbt_potion(PLAYER *);
int  _PASCAL	_NEAR  cmbt_parry(PLAYER *);
int  _PASCAL	_NEAR  cmbt_move(PLAYER *);
int  _PASCAL	_NEAR  cmbt_sneak(PLAYER *);
int  _PASCAL	_NEAR  cmbt_move_or_sneak(PLAYER *,int);
void _PASCAL	cmbt_select_sq_around_player(int,int *,int *,int,int,int);
void _PASCAL	select_a_foe_msg(void);
int  _PASCAL	_NEAR  cmbt_move_player_in_bounds(int,int);
int  _PASCAL	cmbt_move_player_allowed(int,int,int,int,int);
int  _PASCAL	_NEAR  cmbt_inspect(PLAYER *);
int  _PASCAL	cmbt_backstab(PLAYER *);
int  _PASCAL	cmbt_punch(PLAYER *);
void _FAR       _CDECL cmbt_missile_draw_west_arrow(int,int);
void _FAR       _CDECL cmbt_missile_draw_east_arrow(int,int);
void _FAR       _CDECL cmbt_missile_draw_north_arrow(int,int);
void _FAR       _CDECL cmbt_missile_draw_south_arrow(int,int);
void _FAR       _CDECL cmbt_missile_draw_red(int,int);
void _FAR       _CDECL cmbt_missile_draw_blue(int,int);
void _FAR       _CDECL cmbt_missile_draw_magenta(int,int);
void _FAR       _CDECL cmbt_missile_draw_white(int,int);
void _FAR       _CDECL cmbt_missile_draw_sling_shot(int,int);
void _FAR       _CDECL cmbt_missile_draw_flask(int,int);
void _FAR       _CDECL cmbt_missile_draw_rock(int,int);
void _PASCAL	cmbt_bad_msg(char *,int);
int  _PASCAL	monster_is_alive(MONSTER *);
int  _PASCAL	monster_is_dead(MONSTER *);
int  _PASCAL	monster_imm_to_poison(MONSTER *);
int  _PASCAL	monster_imm_to_fire(MONSTER *);
int  _PASCAL	monster_imm_to_ice(MONSTER *);
int  _PASCAL	monster_imm_to_electricity(MONSTER *);
int  _PASCAL	monster_imm_to_mind_spells(MONSTER *);
int  _PASCAL	monster_can_fly(MONSTER *);
void _PASCAL	monster_perform_death_throes(MONSTER *);
int  _PASCAL	monster_is_weak(MONSTER *);
int  _PASCAL	effective_monster_saving_throw(MONSTER *,PLAYER *,int);
void _PASCAL	monster_reduce_hp(MONSTER *,int);
void _PASCAL	monster_has_died(MONSTER *);
int  _PASCAL	is_undead_or_demon(MONSTER *);
int  _PASCAL	is_an_elemental(MONSTER *);
void _PASCAL	make_monster_move(MONSTER *);
int  _PASCAL	move_monster_randomly(MONSTER *);
int  _PASCAL	_NEAR  monster_surrounded(MONSTER *);
void _PASCAL	_NEAR  monster_stands_firm(MONSTER *);
void _PASCAL	make_monster_decision(MONSTER *);
int  _PASCAL	analyse_players_about_monster(MONSTER *);
int  _PASCAL	get_player_to_attack(void);
int  _PASCAL	make_monster_cast_spell(MONSTER *,int);
void _PASCAL	_NEAR  monster_cast_fire(MONSTER *,PLAYER *,int);
void _PASCAL	_NEAR  monster_cast_ice(MONSTER *,PLAYER *,int);
void _PASCAL	_NEAR  monster_cast_electricity(MONSTER *,PLAYER *,int);
void _PASCAL	_NEAR  monster_cast_power_spell(MONSTER *,PLAYER *,int);
void _PASCAL	_NEAR  monster_use_breath(MONSTER *,int);
void _PASCAL	_NEAR  monster_throw_rock(MONSTER *,PLAYER *,int);
void _PASCAL	_NEAR  monster_fire_arrow(MONSTER *,PLAYER *,int);
void _PASCAL	_NEAR  monster_spit_fire(MONSTER *,int);
void _PASCAL	_NEAR  monster_use_gaze(MONSTER *,PLAYER *,int);
void _PASCAL	_NEAR  monster_generic_cast_spell(MONSTER *,PLAYER *,int,int,int,void (_FAR *)(int,int));
void _PASCAL	_NEAR  monster_spell_succeeds(PLAYER *,int);
void _PASCAL	_NEAR  monster_spell_fails(int);
void _PASCAL	_NEAR  monster_spell_hits_wall(int,int);
int  _PASCAL	_NEAR  straight_line_monster_to_player(MONSTER *,PLAYER *);
int  _PASCAL	_NEAR  monster_get_spell_victim(MONSTER *);
void _PASCAL	make_monster_flee(MONSTER *);
void _PASCAL	make_monster_fade(MONSTER *);
int  _PASCAL	monster_at_combat_edge(MONSTER *);
void _PASCAL	set_monster_flee_coords(MONSTER *);
int  _CDECL     flee_closest_wall(int *,int *);
int  _PASCAL	set_monster_flee_coordsN(MONSTER *);
int  _PASCAL	set_monster_flee_coordsS(MONSTER *);
int  _PASCAL	set_monster_flee_coordsE(MONSTER *);
int  _PASCAL	set_monster_flee_coordsW(MONSTER *);
int  _PASCAL	monster_attack_is_physical(MONSTER *,int);
int  _PASCAL	monster_attack_is_magical(MONSTER *,int);
int  _PASCAL	opponent_next_to_monster(MONSTER *);
int  _PASCAL	any_player_next_to_monster(MONSTER *);
int  _PASCAL	get_player_from_cmbt_square(int,int);
int  _PASCAL	get_monster_from_cmbt_square(int,int);
int  _PASCAL	make_monster_attack(MONSTER *,int);
int  _PASCAL	effective_monster_attack(MONSTER *,PLAYER *);
int  _PASCAL	effective_monster_damage(MONSTER *,int);
int  _PASCAL	effective_monster_dodge_splash(MONSTER *);
void _PASCAL	check_monster_poison_disease(PLAYER *,MONSTER *,int);
void _PASCAL	cmbt_monster_is_splashed(PLAYER *,MONSTER *);
void _PASCAL	cmbt_player_is_splashed(PLAYER *);
void _PASCAL	cmbt_spell_missed(int,int);
void _PASCAL	cmbt_oil_water_splash(PLAYER *,int,int,int);
char *			monster_phys_attack_string(MONSTER *,PLAYER *,int);
char *			monster_phys_miss_string(MONSTER *,PLAYER *,int);
void _PASCAL	get_party_combat_location(int *,int *);
void _PASCAL	actually_make_monster_move(MONSTER *);
void _PASCAL	get_new_monster_location(MONSTER *);
int  _PASCAL	are_all_monsters_dead_or_flown(void);
void _PASCAL	cmbt_grab_image(int,int);
void _PASCAL	cmbt_replace_image(int,int);
void _PASCAL	cmbt_buzz_a_square(int,int,int);
void _PASCAL	cmbt_hit_a_square(int,int);
void _PASCAL	spell_hit_a_square(int,int);
void _PASCAL	want_to_poison_weapon(PLAYER *);
void _PASCAL	morale_increase(MONSTER *,int);
void _PASCAL	morale_decrease(MONSTER *,int);
int  _PASCAL	effective_morale(MONSTER *);
void _PASCAL	morale_check(MONSTER *);
void _PASCAL	morale_one_monster_at_start(MONSTER *,int);
void _PASCAL	morale_all_at_start(void);
void _PASCAL	morale_all_increase(int);
void _PASCAL	morale_all_decrease(int);
void _PASCAL	pick_up_flasks_after_combat(void);
void _PASCAL	display_post_combat_stats(void);
void _PASCAL	cmbt_cannot_use_in_close_melee(int);
void _PASCAL	combat_end_determine_treasure(int);
int  _PASCAL	player_scores_critical_hit(PLAYER *,MONSTER *);
int  _PASCAL	monster_scores_critical_hit(PLAYER *,MONSTER *);
int  _PASCAL	_NEAR  modify_player_spell_damage(MONSTER *,int,int);
static long 	_PASCAL _NEAR  monsters_treasure_TRE_NONE(void);
static long 	_PASCAL _NEAR  monsters_treasure_TRE_LOW_MONEY(int);
static long 	_PASCAL _NEAR  monsters_treasure_TRE_MED_MONEY(int);
static long 	_PASCAL _NEAR  monsters_treasure_TRE_LOT_MONEY(int);
static long 	_PASCAL _NEAR  monsters_treasure_TRE_JEWELS(int);
static long 	_PASCAL _NEAR  monsters_treasure_TRE_MAGIC(void);
static long 	_PASCAL _NEAR  monsters_treasure_money(int,int);
void _PASCAL	check_wandering_monsters(void);
int  _PASCAL	party_next_to(int);
void _PASCAL	generic_pic_draw(int,int,char *);
static	 int	_PASCAL monster_is_stunnable(MONSTER *);
int  _PASCAL	is_monster_stunned_from_hit(MONSTER *,int);
void _PASCAL	actually_stun_monster(MONSTER *);
int  _PASCAL	is_player_stunned_from_hit(PLAYER *,int);
void _PASCAL	actually_stun_player(PLAYER *);
void _PASCAL	handle_wizard_mode(void);
void _PASCAL	check_fall_down_steps(void);
int  _PASCAL	effective_fall_down_steps(PLAYER *);
void _PASCAL	fall_down_steps(PLAYER *);
int  _PASCAL	max_points_cast_per_day(PLAYER *);
void _PASCAL	player_is_spell_drained(PLAYER *);
int  _PASCAL	check_player_is_spell_drained(PLAYER *);
static void 	_PASCAL _NEAR  update_all_spell_drains(void);
int  _PASCAL    good_for_dark_elf(PLAYER *);
