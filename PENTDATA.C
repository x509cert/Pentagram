#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <pent.h>
#include <pentextn.h>
#pragma hdrstop("PENT.PCH")

GWINDOW         select_win;
GWINDOW         please_wait_win;
PENT_DATA       pent_data;
THE_PARTY       the_party;
PLAYER          adv;
SMALL_TOWN		town;
int             FONT[FONT_RAM_SIZE];
ITEM_POOL		pool[MAX_POOL];
int 			mouse_x,mouse_y;
int 			fast_mouse;
int             night_flagged;
int             game_loaded;
int             mouse_installed;
int             situation_status;
int 			abort_training;
int 			in_spell_section;
int 			same_people;
int 			cath_error;
MONSTER         the_monsters[MAX_MONSTERS];
CMBT_CELL       cmbt_area[CMBT_AREA_X][CMBT_AREA_Y];
CMBT_CELL       battle_order[MAX_PARTY+MAX_MONSTERS];
int             party_is_hostile;
int             num_database_monsters;
int             num_monsters;
int             num_monsters_killed;
int             num_adv_killed;
char _FAR       monster_image[MONSTER_IMAGE_SIZE];
char _FAR       monster_mask_image[MONSTER_IMAGE_SIZE];
char _FAR       underneath_image[MONSTER_IMAGE_SIZE];
long int        cmbt_xp_gained;
long int        cmbt_gold_gained;
PLAYER          *about_monsters[MAX_PARTY];
int             num_players_about_monster;
int             wizard_mode;
int             no_monsters;
int             first_round;
int             surprise_mod;
int             surprise_nstring;
int             quick_exit;
int 			in_exit;
DUNGEON_TY		dungeon;
int 			killed_by_barman=FALSE;
int 			rumr_person;
SPELL_NAME		adv_spells[MAX_PLAYER_SPELLS];
int 			be_warrior,be_priest,be_wizard;
int 			be_druid,be_thief,be_hunter;
int 			be_ranger,be_crusader,be_bard;
int 			be_monk,be_illusionist,be_duelist;


char            _FAR *cmbt_rip_buffer;
unsigned char   _FAR *MAP;

char _FAR       *all_menu_bkgrnd;
char _FAR       *adv_menu;

char _FAR       map_icon_hills[MAP_ICON_SIZE];
char _FAR       map_icon_forest[MAP_ICON_SIZE];
char _FAR       map_icon_grass[MAP_ICON_SIZE];
char _FAR       map_icon_highmts[MAP_ICON_SIZE];
char _FAR       map_icon_marsh[MAP_ICON_SIZE];
char _FAR       map_icon_mts[MAP_ICON_SIZE];
char _FAR       map_icon_sea[MAP_ICON_SIZE];
char _FAR       map_icon_sea2[MAP_ICON_SIZE];
char _FAR       map_icon_town[MAP_ICON_SIZE];
char _FAR       map_icon_water[MAP_ICON_SIZE];
char _FAR       map_icon_water2[MAP_ICON_SIZE];
char _FAR       map_icon_village[MAP_ICON_SIZE];
char _FAR       map_icon_cross[MAP_ICON_SIZE];
char _FAR       map_icon_party[MAP_ICON_SIZE];
char _FAR       map_icon_party2[MAP_ICON_SIZE];
char _FAR       map_icon_party_mask[MAP_ICON_SIZE];
char _FAR       map_icon_dungeon[MAP_ICON_SIZE];
char _FAR       map_icon_ruin[MAP_ICON_SIZE];
char _FAR       map_icon_br_lr[MAP_ICON_SIZE];
char _FAR       map_icon_br_ud[MAP_ICON_SIZE];
char _FAR       map_icon_signpost[MAP_ICON_SIZE];
char _FAR       map_icon_road01[MAP_ICON_SIZE];
char _FAR       map_icon_road02[MAP_ICON_SIZE];
char _FAR       map_icon_road03[MAP_ICON_SIZE];
char _FAR       map_icon_road04[MAP_ICON_SIZE];
char _FAR       map_icon_road05[MAP_ICON_SIZE];
char _FAR       map_icon_road06[MAP_ICON_SIZE];
char _FAR       map_icon_road07[MAP_ICON_SIZE];
char _FAR       map_icon_road08[MAP_ICON_SIZE];
char _FAR       map_icon_road09[MAP_ICON_SIZE];
char _FAR       map_icon_road10[MAP_ICON_SIZE];
char _FAR       map_icon_road11[MAP_ICON_SIZE];

char _FAR       day_nite_icon_1[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_2[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_4[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_5[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_6[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_7[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_11[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_12[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_13[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_14[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_15[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_16[DAY_NITE_ICON_SIZE];
char _FAR       day_nite_icon_17[DAY_NITE_ICON_SIZE];

char _FAR       im_bard[MONSTER_IMAGE_SIZE];
char _FAR       im_crusader[MONSTER_IMAGE_SIZE];
char _FAR       im_druid[MONSTER_IMAGE_SIZE];
char _FAR       im_duelist[MONSTER_IMAGE_SIZE];
char _FAR       im_hunter[MONSTER_IMAGE_SIZE];
char _FAR       im_illusionist[MONSTER_IMAGE_SIZE];
char _FAR       im_monk[MONSTER_IMAGE_SIZE];
char _FAR       im_priest[MONSTER_IMAGE_SIZE];
char _FAR       im_ranger[MONSTER_IMAGE_SIZE];
char _FAR       im_thief[MONSTER_IMAGE_SIZE];
char _FAR       im_warrior[MONSTER_IMAGE_SIZE];
char _FAR       im_wizard[MONSTER_IMAGE_SIZE];

char _FAR       im_bard_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_crusader_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_druid_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_duelist_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_hunter_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_illusionist_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_monk_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_priest_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_ranger_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_thief_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_warrior_msk[MONSTER_IMAGE_SIZE];
char _FAR       im_wizard_msk[MONSTER_IMAGE_SIZE];

char			next_button[][19];
char			prev_button[][20];

