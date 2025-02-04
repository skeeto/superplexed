#ifndef SP_CONSTANTS_H
#define SP_CONSTANTS_H

namespace c {
	// application constants
	constexpr char APP_TITLE[]{ "Superplexed v0.1" };
	constexpr char APP_VERSION[]{ "0.1" };
	constexpr int APP_WIN_W_INITIAL{ 1024 };
	constexpr int APP_WIN_H_INITIAL{ 768 };
	constexpr char FILE_SIGNATURE[]{ "kaimitai@github " };
	constexpr std::size_t UNDO_HISTORY_COUNT{ 200 };

	// filenames
	constexpr char SPCONFIG_XML_FILENAME[]{ "spconfig.xml" };
	constexpr char SP_IMGUI_INI_FILENAME[]{ "spwindows.ini" };
	constexpr char DEFAULT_PROJECT_FOLDER[]{ "." };

	// folders and file extensions
	constexpr char SUFFIX_DAT[]{ "DAT" };
	constexpr char SUFFIX_BMP[]{ "bmp" };
	constexpr char SUFFIX_LST[]{ "LST" };
	constexpr char SUFFIX_SP[]{ "SP" };
	constexpr char SUFFIX_XML[]{ "xml" };

	// output messages
	constexpr unsigned int MESSAGES_MAX_SIZE{ 25 };

	// ui texts
	constexpr char SAVE_BMP[]{ "Save bmp" };
	constexpr char SAVE_DAT[]{ "Save DAT" };
	constexpr char SAVE_LST[]{ "Save LST" };
	constexpr char SAVE_SP[]{ "Save SP" };
	constexpr char SAVE_XML[]{ "Save xml" };
	constexpr char LOAD_BMP[]{ "Load bmp" };
	constexpr char LOAD_DAT[]{ "Load DAT" };
	constexpr char LOAD_LST[]{ "Load LST" };
	constexpr char LOAD_SP[]{ "Load SP" };
	constexpr char LOAD_XML[]{ "Load xml" };

	// assorted texts used in the applications for labels or parts of strings
	constexpr char TXT_FILE_OPERATIONS[]{ "File Operations" };
	constexpr char TXT_HOLD_CTRL_TO_USE[]{ "Hold Ctrl to use this button" };

	// xml tags, attributes and values
	// configuration XML
	constexpr char XML_ATTR_PROJECT_FOLDER[]{ "project_folder" };

	// level file XMLs
	constexpr char XML_COMMENTS[]{ " Supaplex Level created by Superplexed (https://github.com/kaimitai/superplexed) " };
	constexpr char XML_COMMENTS_IMAGE[]{ " Supaplex Image created by Superplexed (https://github.com/kaimitai/superplexed) " };
	constexpr char XML_COMMENTS_PALETTE[]{ " Supaplex Palettes created by Superplexed (https://github.com/kaimitai/superplexed) " };
	constexpr char XML_TAG_META[]{ "superplexed" };
	constexpr char XML_TAG_LEVEL[]{ "level" };
	constexpr char XML_TAG_TILE_ROWS[]{ "tile_rows" };
	constexpr char XML_TAG_TILE_ROW[]{ "tile_row" };
	constexpr char XML_TAG_GPS[]{ "special_ports" };
	constexpr char XML_TAG_GP[]{ "special_port" };
	constexpr char XML_TAG_SOLUTION[]{ "speedfix_solution" };

	constexpr char XML_ATTR_APP_VERSION[]{ "app_version" };
	constexpr char XML_ATTR_TITLE[]{ "title" };
	constexpr char XML_ATTR_PLAYER_X[]{ "player_x" };
	constexpr char XML_ATTR_PLAYER_Y[]{ "player_y" };
	constexpr char XML_ATTR_INFOTRONS[]{ "infotrons_needed" };
	constexpr char XML_ATTR_GRAV[]{ "gravity" };
	constexpr char XML_ATTR_FZ[]{ "freeze_zonks" };
	constexpr char XML_ATTR_NO[]{ "no" };
	constexpr char XML_ATTR_VALUE[]{ "value" };
	constexpr char XML_ATTR_SF_V[]{ "speedfix_version" };
	constexpr char XML_ATTR_SF_DB[]{ "speedfix_demo_bytes" };
	constexpr char XML_ATTR_UNKNOWN[]{ "unknown_bytes" };

	constexpr char XML_ATTR_POS_X[]{ "pos_x" };
	constexpr char XML_ATTR_POS_Y[]{ "pos_y" };
	constexpr char XML_ATTR_FE[]{ "freeze_enemies" };

	constexpr char XML_VAL_TRUE[]{ "true" };
	constexpr char XML_VAL_FALSE[]{ "false" };

	// image file xmls
	constexpr char XML_TAG_IMAGE[]{ "image" };
	constexpr char XML_ATTR_WIDTH[]{ "width" };
	constexpr char XML_ATTR_HEIGHT[]{ "height" };
	constexpr char XML_ATTR_IMGTYPE[]{ "image_type" };
	constexpr char XML_VAL_BINARY[]{ "binary" };
	constexpr char XML_VAL_PLANAR[]{ "planar" };
	constexpr char XML_TAG_PIXEL_ROWS[]{ "pixel_rows" };
	constexpr char XML_TAG_PIXEL_ROW[]{ "pixel_row" };

	// palette file xmls
	constexpr char XML_TAG_PALETTES[]{ "palettes" };
	constexpr char XML_TAG_PALETTE[]{ "palette" };
	constexpr char XML_TAG_COLOR[]{ "color" };
	constexpr char XML_ATTR_R[]{ "r" };
	constexpr char XML_ATTR_G[]{ "g" };
	constexpr char XML_ATTR_B[]{ "b" };
	constexpr char XML_ATTR_A[]{ "a" };

	// gfx constants
	constexpr unsigned int TILE_W{ 16 };
	constexpr unsigned int PALETTE_COUNT{ 4 };

	// level file constants
	constexpr unsigned int LEVEL_W{ 60 }, LEVEL_H{ 24 },
		OFFSET_TILES{ 0 }, OFFSET_GRAVITY{ 1444 }, OFFSET_UNUSED_BYTES{ 1440 },
		OFFSET_SF_VERSION{ 1445 },
		OFFSET_TITLE{ 1446 }, OFFSET_FREEZE_ZONKS{ 1469 }, OFFSET_IT_COUNT{ 1470 },
		OFFSET_GP_COUNT{ 1471 }, OFFSET_GP{ 1472 }, OFFSET_SF_DEMO_BYTES{ 1532 },
		LENGTH_TITLE{ 23 }, LENGTH_GP{ 6 }, LENGTH_SF_DEMO_BYTES{ 4 },
		LENGTH_UNUSED_BYTES{ 4 },
		LVL_DATA_BYTE_SIZE{ 1536 };
	constexpr int MAX_GP_COUNT{ 10 };

	// tile descriptions
	constexpr char TILE_DESC_EMPTY[]{ "Empty Space" };
	constexpr char TILE_DESC_ZONK[]{ "Zonk" };
	constexpr char TILE_DESC_BASE[]{ "Base" };
	constexpr char TILE_DESC_MURPHY[]{ "Murphy" };
	constexpr char TILE_DESC_INFOTRON[]{ "Infotron" };
	constexpr char TILE_DESC_RAMCHIP[]{ "RAM Chip - Chip" };
	constexpr char TILE_DESC_WALL[]{ "Wall" };
	constexpr char TILE_DESC_EXIT[]{ "Exit" };
	constexpr char TILE_DESC_FLOPPY_O[]{ "Floppy - Orange" };
	constexpr char TILE_DESC_PORT_RIGHT[]{ "Port - Right" };
	constexpr char TILE_DESC_PORT_DOWN[]{ "Port - Down" };
	constexpr char TILE_DESC_PORT_LEFT[]{ "Port - Left" };
	constexpr char TILE_DESC_PORT_UP[]{ "Port - Up" };
	constexpr char TILE_DESC_GP_RIGHT[]{ "Special Port - Right" };
	constexpr char TILE_DESC_FP_DOWN[]{ "Special Port - Down" };
	constexpr char TILE_DESC_GP_LEFT[]{ "Special Port - Left" };
	constexpr char TILE_DESC_GP_UP[]{ "Special Port - Up" };
	constexpr char TILE_DESC_SNIKSNAK[]{ "Snik Snak" };
	constexpr char TILE_DESC_FLOPPY_Y[]{ "Floppy - Yellow" };
	constexpr char TILE_DESC_TERMINAL[]{ "Terminal" };
	constexpr char TILE_DESC_FLOPPY_R[]{ "Floppy - Red" };
	constexpr char TILE_DESC_PORT2WAY_V[]{ "Port - Two-Way Vertical" };
	constexpr char TILE_DESC_PORT2WAY_H[]{ "Port - Two-Way Horizontal" };
	constexpr char TILE_DESC_PORT4WAY[]{ "Port - Four-Way" };
	constexpr char TILE_DESC_ELECTRON[]{ "Electron" };
	constexpr char TILE_DESC_BUG[]{ "Bug" };
	constexpr char TILE_DESC_RAM_LEFT[]{ "RAM Chip - Left" };
	constexpr char TILE_DESC_RAM_RIGHT[]{ "RAM Chip - Right" };
	constexpr char TILE_DESC_HW01[]{ "Hardware 01" };
	constexpr char TILE_DESC_HW02[]{ "Hardware 02" };
	constexpr char TILE_DESC_HW03[]{ "Hardware 03" };
	constexpr char TILE_DESC_HW04[]{ "Hardware 04" };
	constexpr char TILE_DESC_HW05[]{ "Hardware 05" };
	constexpr char TILE_DESC_HW06[]{ "Hardware 06" };
	constexpr char TILE_DESC_HW07[]{ "Hardware 07" };
	constexpr char TILE_DESC_HW08[]{ "Hardware 08" };
	constexpr char TILE_DESC_HW09[]{ "Hardware 09" };
	constexpr char TILE_DESC_HW10[]{ "Hardware 10" };
	constexpr char TILE_DESC_RAM_TOP[]{ "RAM Chip - Top" };
	constexpr char TILE_DESC_RAM_BOTTOM[]{ "RAM Chip - Bottom" };
	constexpr char TILE_DESC_INVISIBLE_TILE[]{ "Invisible Tile" };
	constexpr char TILE_DESC_PLAYER_START[]{ "Player Start" };

	// tile numbers
	constexpr int TILE_COUNT{ 41 }; // non-virtual gametiles
	constexpr unsigned char TILE_NO_EMPTY{ 0 };
	constexpr unsigned char TILE_NO_ZONK{ 1 };
	constexpr unsigned char TILE_NO_BASE{ 2 };
	constexpr unsigned char TILE_NO_MURPHY{ 3 };
	constexpr unsigned char TILE_NO_INFOTRON{ 4 };
	constexpr unsigned char TILE_NO_RAMCHIP{ 5 };
	constexpr unsigned char TILE_NO_WALL{ 6 };
	constexpr unsigned char TILE_NO_EXIT{ 7 };
	constexpr unsigned char TILE_NO_FLOPPY_O{ 8 };
	constexpr unsigned char TILE_NO_PORT_RIGHT{ 9 };
	constexpr unsigned char TILE_NO_PORT_DOWN{ 10 };
	constexpr unsigned char TILE_NO_PORT_LEFT{ 11 };
	constexpr unsigned char TILE_NO_PORT_UP{ 12 };
	constexpr unsigned char TILE_NO_GP_RIGHT{ 13 };
	constexpr unsigned char TILE_NO_GP_DOWN{ 14 };
	constexpr unsigned char TILE_NO_GP_LEFT{ 15 };
	constexpr unsigned char TILE_NO_GP_UP{ 16 };
	constexpr unsigned char TILE_NO_SNIKSNAK{ 17 };
	constexpr unsigned char TILE_NO_FLOPPY_Y{ 18 };
	constexpr unsigned char TILE_NO_TERMINAL{ 19 };
	constexpr unsigned char TILE_NO_FLOPPY_R{ 20 };
	constexpr unsigned char TILE_NO_PORT2WAY_V{ 21 };
	constexpr unsigned char TILE_NO_PORT2WAY_H{ 22 };
	constexpr unsigned char TILE_NO_PORT4WAY{ 23 };
	constexpr unsigned char TILE_NO_ELECTRON{ 24 };
	constexpr unsigned char TILE_NO_BUG{ 25 };
	constexpr unsigned char TILE_NO_RAM_LEFT{ 26 };
	constexpr unsigned char TILE_NO_RAM_RIGHT{ 27 };
	constexpr unsigned char TILE_NO_HW01{ 28 };
	constexpr unsigned char TILE_NO_HW02{ 29 };
	constexpr unsigned char TILE_NO_HW03{ 30 };
	constexpr unsigned char TILE_NO_HW04{ 31 };
	constexpr unsigned char TILE_NO_HW05{ 32 };
	constexpr unsigned char TILE_NO_HW06{ 33 };
	constexpr unsigned char TILE_NO_HW07{ 34 };
	constexpr unsigned char TILE_NO_HW08{ 35 };
	constexpr unsigned char TILE_NO_HW09{ 36 };
	constexpr unsigned char TILE_NO_HW10{ 37 };
	constexpr unsigned char TILE_NO_RAM_TOP{ 38 };
	constexpr unsigned char TILE_NO_RAM_BOTTOM{ 39 };
	constexpr unsigned char TILE_NO_INVISIBLE{ 40 };
	constexpr unsigned char TILE_NO_PLAYER_START{ 41 };

	// supaplex dat filenames
	// leves and level list
	constexpr char FILENAME_LEVELS[]{ "LEVELS" };
	constexpr char FILENAME_LEVEL[]{ "LEVEL" };
	// palettes
	constexpr char FILENAME_PALETTES[]{ "PALETTES" };
	// graphics files
	constexpr char FILENAME_BACK[]{ "BACK" };
	constexpr char FILENAME_CHARS6[]{ "CHARS6" };
	constexpr char FILENAME_CHARS8[]{ "CHARS8" };
	constexpr char FILENAME_CONTROLS[]{ "CONTROLS" };
	constexpr char FILENAME_FIXED[]{ "FIXED" };
	constexpr char FILENAME_GFX[]{ "GFX" };
	constexpr char FILENAME_MENU[]{ "MENU" };
	constexpr char FILENAME_MOVING[]{ "MOVING" };
	constexpr char FILENAME_PANEL[]{ "PANEL" };
	constexpr char FILENAME_TITLE[]{ "TITLE" };
	constexpr char FILENAME_TITLE1[]{ "TITLE1" };
	constexpr char FILENAME_TITLE2[]{ "TITLE2" };
	// savefiles LST-files
	constexpr char FILENAME_HALLFAME[]{ "HALLFAME" };
	constexpr char FILENAME_PLAYER[]{ "PLAYER" };

	// default savefile constants
	constexpr int PLAYER_COUNT{ 20 };
	constexpr char EMPTY_PLAYER_NAME[]{ "--------" };
	constexpr int HALLFAME_ENTRY_COUNT{ 3 };
	constexpr int HALLFAME_ENTRY_SIZE{ 12 };
	constexpr int PLAYER_NAME_SIZE{ 8 };
	constexpr int PLAYER_ENTRY_SIZE{ 128 };
	constexpr int DEFAULT_LEVEL_COUNT{ 111 };

	// default level constants
	constexpr char DEFAULT_LVL_TITLE[]{ "----- SUPERPLEXED -----" };
	constexpr unsigned char DEFAULT_LVL_SF_VERSION{ 32 };

	// color constants
	struct SP_Color {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	constexpr SP_Color COL_RED{ 0xff, 0x00, 0x00 };
	constexpr SP_Color COL_RED_DARK{ 0x80, 0x00, 0x00 };
	constexpr SP_Color COL_ORANGE{ 255,165, 0 };
	constexpr SP_Color COL_ORANGE_LIGHT{ 255,213, 128 };
	constexpr SP_Color COL_BLACK{ 0x00, 0x00, 0x00 };
	constexpr SP_Color COL_WHITE{ 0xff, 0xff, 0xff };
	constexpr SP_Color COL_YELLOW{ 0xff,0xff,0x00 };
	constexpr SP_Color COL_YELLOW_DARK{ 200,220,0 };

	constexpr SP_Color COL_BLUE{ 0x00,0x00,0xff };
	constexpr SP_Color COL_BLUE_LIGHT{ 0x00,0x80,0xff };
	constexpr SP_Color COL_BLUE_DARK{ 0x00,0x00,0x80 };

	constexpr SP_Color COL_GREEN_LIGHT{ 0xbf,0xff,0xb4 };
	constexpr SP_Color COL_GREEN{ 0x00,0xe0,0x00 };
	constexpr SP_Color COL_GREEN_DARK{ 0x32,0xcd,0x32 };

	// dear imgui window constants
	constexpr int WIN_MAIN_X{ 10 }, WIN_MAIN_Y{ 5 }, WIN_MAIN_W{ 400 }, WIN_MAIN_H{ 255 };

	constexpr int WIN_LVL_X{ 10 }, WIN_LVL_Y{ 265 }, WIN_LVL_W{ 400 }, WIN_LVL_H{ 255 };
	constexpr int WIN_SP_X{ 10 }, WIN_SP_Y{ 600 }, WIN_SP_W{ 400 }, WIN_SP_H{ 130 };
	constexpr int WIN_TP_X{ 630 }, WIN_TP_Y{ 5 }, WIN_TP_W{ 390 }, WIN_TP_H{ 430 };
	constexpr int WIN_STATS_X{ 415 }, WIN_STATS_Y{ 5 }, WIN_STATS_W{ 230 }, WIN_STATS_H{ 675 };

	constexpr int WIN_GFX_X{ 10 }, WIN_GFX_Y{ 265 }, WIN_GFX_W{ 400 }, WIN_GFX_H{ 235 };
	constexpr int WIN_PAL_X{ 415 }, WIN_PAL_Y{ 415 }, WIN_PAL_W{ 400 }, WIN_PAL_H{ 270 };
	constexpr int WIN_IMGPV_X{ 410 }, WIN_IMGPV_Y{ 5 }, WIN_IMGPV_W{ 610 }, WIN_IMGPV_H{ 405 };

	constexpr int WIN_HF_X{ 10 }, WIN_HF_Y{ 265 }, WIN_HF_W{ 400 }, WIN_HF_H{ 205 };
	constexpr int WIN_PL_X{ 415 }, WIN_PL_Y{ 5 }, WIN_PL_W{ 380 }, WIN_PL_H{ 580 };
}

#endif
