#pragma once
#include "buggin_out_VS\stdafx.h"

/*
	BugginOutGame.h

	This file contains setup data for making the BugginOut game. Note that nearly
	all of this data would better serve us if loaded from files.
*/

// HERE IS THE BugginOut GAME SETUP/INIT FILE. EVERYTHING WOULD START FROM HERE

static const float		PLAYER_LEVEL1_X = 80.0f;
static const float		PLAYER_LEVEL1_Y = 100.0f;

static const float		PLAYER_LEVEL2_X = 80.0f;
static const float		PLAYER_LEVEL2_Y = 100.0f;

static const float		PLAYER_LEVEL3_X = 80.0f;
static const float		PLAYER_LEVEL3_Y = 10.0f;

static int				NumberOfBotsPerLevel = 10;

static char*			AudioStr				= "data/Sound/ah.wav";
static char*			Level1Sound				= "data/Sound/Level1.wav";
static char*			Level2Sound				= "data/Sound/Level2.wav";
static char*			Level3Sound				= "data/Sound/Level3.wav";
static char*			HitSound				= "data/Sound/hit.wav";

static const wstring	W_LEVEL_1_DIR			= L"data/levels/SideScrollerFirstLevel/";
static const wstring	W_LEVEL_1_NAME			= L"SideScrollerFirstLevel.tmx";
static const wstring	W_LEVEL_1_PATH			= W_LEVEL_1_DIR + W_LEVEL_1_NAME;

static const wstring	W_LEVEL_2_DIR			= L"data/levels/SideScrollerSecondLevel/";
static const wstring	W_LEVEL_2_NAME			= L"SideScrollerSecondLevel.tmx";
static const wstring	W_LEVEL_2_PATH			= W_LEVEL_2_DIR + W_LEVEL_2_NAME;

static const wstring	W_LEVEL_3_DIR			= L"data/levels/SideScrollerThirdLevel/";
static const wstring	W_LEVEL_3_NAME			= L"SideScrollerThirdLevel.tmx";
static const wstring	W_LEVEL_3_PATH			= W_LEVEL_3_DIR + W_LEVEL_3_NAME;

static const wstring	W_INIT_FILE				= L"data/ZombiesssInit.txt";
static const wstring	W_GUI_INIT_FILE			= L"data/BugginOutGUI.txt";
static const string		W_DEBUG_FILE			= "DebugOutput.txt";

static const string		W_JUMP_BOT_FILE			= "data/bots/RandomJumpingBot.lua";
static const string		W_BAT_BOT_FILE			= "data/bots/BatBot.lua";

// HERE ARE THE GAME PROPERTIES WE ARE LOADING FROM FROM THE SETUP FILE
static const wstring	W_TITLE					= L"TITLE";
static const wstring	W_SCREEN_WIDTH			= L"SCREEN_WIDTH";
static const wstring	W_SCREEN_HEIGHT			= L"SCREEN_HEIGHT";
static const wstring	W_USE_FULLSCREEN_MODE	= L"USE_FULLSCREEN_MODE";
static const wstring	W_TEXT_FONT_SIZE		= L"TEXT_FONT_SIZE";
static const wstring	W_VIEWPORT_OFFSET_X		= L"VIEWPORT_OFFSET_X";
static const wstring	W_VIEWPORT_OFFSET_Y		= L"VIEWPORT_OFFSET_Y";
static const wstring	W_TOGGLE_OFFSET_Y		= L"TOGGLE_OFFSET_Y";
static const wstring	W_FONT_COLOR_RED		= L"FONT_COLOR_RED";
static const wstring	W_FONT_COLOR_GREEN		= L"FONT_COLOR_GREEN";
static const wstring	W_FONT_COLOR_BLUE		= L"FONT_COLOR_BLUE";
static const wstring	W_COLOR_KEY_RED			= L"COLOR_KEY_RED";
static const wstring	W_COLOR_KEY_GREEN		= L"COLOR_KEY_GREEN";
static const wstring	W_COLOR_KEY_BLUE		= L"COLOR_KEY_BLUE";

// CONSTANTS FOR ARTWORK - NOTE, THIS SHOULD REALLY BE LOADED FROM A FILE
static const wstring	W_GO_TO_MM_COMMAND		= L"Go To Main Menu";
static const wstring	W_START_COMMAND			= L"Start";
static const wstring	W_EXIT_COMMAND			= L"Exit";
static const wstring	W_BACK_COMMAND			= L"Back";
static const wstring	W_ABOUT_COMMAND			= L"About";
static const wstring	W_CONTROLS_COMMAND		= L"Controls";
static const wstring	W_HELP_COMMAND			= L"Help";
static const wstring	W_QUIT_COMMAND			= L"Quit";
static const wstring	W_GREEN_CURSOR_PATH		= L"data/gui/cursor/green_cursor.png";
static const wstring	W_RED_CURSOR_PATH		= L"data/gui/cursor/red_cursor.png";
static const wstring	W_SPLASH_SCREEN_PATH	= L"data/gui/overlays/zombiesss_screen_overlay.png";
static const wstring	W_MAIN_MENU_PATH		= L"data/gui/overlays/zombiesss_menu_overlay.png";
static const wstring	W_ABOUT_PATH			= L"data/gui/overlays/zombiesss_about.png";
static const wstring	W_CONTROLS_PATH			= L"data/gui/overlays/zombiesss_controls.png";
static const wstring	W_HELP_PATH				= L"data/gui/overlays/zombiesss_help.png";
static const wstring	W_START_IMAGE_PATH		= L"data/gui/buttons/start_game.png";
static const wstring	W_START_IMAGE_MO_PATH	= L"data/gui/buttons/start_game_mo.png";
static const wstring	W_EXIT_IMAGE_PATH		= L"data/gui/buttons/exit_game.png";
static const wstring	W_EXIT_IMAGE_MO_PATH	= L"data/gui/buttons/exit_game_mo.png";
static const wstring	W_QUIT_IMAGE_PATH		= L"data/gui/buttons/quit.png";
static const wstring	W_QUIT_IMAGE_MO_PATH	= L"data/gui/buttons/quit_mo.png";
static const wstring	W_ABOUT_IMAGE_PATH		= L"data/gui/buttons/about.png";
static const wstring	W_ABOUT_IMAGE_MO_PATH	= L"data/gui/buttons/about_mo.png";
static const wstring	W_CONTROLS_IMAGE_PATH	= L"data/gui/buttons/controls.png";
static const wstring	W_CONTROLS_IMAGE_MO_PATH = L"data/gui/buttons/controls_mo.png";
static const wstring	W_HELP_IMAGE_PATH		= L"data/gui/buttons/help.png";
static const wstring	W_HELP_IMAGE_MO_PATH	= L"data/gui/buttons/help_mo.png";

// FOR OUR SPRITE
static const wstring	SPRITE_TYPES_DIR = L"data/sprite_types/";
static const wstring	SPRITE_TYPES_LIST = SPRITE_TYPES_DIR + L"sprite_type_list.xml";
static const wstring	JUMPING = L"JUMPING";

// FOR THE GAME WORLD
static const float		MAX_VIEWPORT_AXIS_VELOCITY = 20.0f;
static const float		W_GRAVITY = 0.8f;
static const float		JUMPING_BOT_MIN_CYCLES = 30;
static const float		JUMPING_BOT_MAX_CYCLES = 120;
static const float		JUMPING_BOT_MAX_VELOCITY = 40;
static const float		JUMP_SPEED = -128.0f;
static const float		PLAYER_SPEED = 32.0f;
static const int		MIN_FPS = 5;
static const int		MAX_FPS = 100;
static const int		FPS_INC = 1;
static const wstring	ATTACKING_RIGHT(L"ATTACKING_RIGHT");
static const wstring	ATTACKING_LEFT(L"ATTACKING_LEFT");
static const wstring	STUNNED_LEFT(L"STUNNED_LEFT");
static const wstring	STUNNED_RIGHT(L"STUNNED_RIGHT");
static const wstring	LEFT(L"LEFT");
static const wstring	RIGHT(L"RIGHT");
static const wstring	LEFT_DEAD(L"LEFT_DEAD");
static const wstring	RIGHT_DEAD(L"RIGHT_DEAD");
static const wstring	IDLE(L"IDLE");
static const wstring	DEAD(L"DEAD");

// USED FOR MOVEMENT
const unsigned int W_KEY = (unsigned int)'W';
const unsigned int A_KEY = (unsigned int)'A';
const unsigned int S_KEY = (unsigned int)'S';
const unsigned int D_KEY = (unsigned int)'D';
const unsigned int G_KEY = (unsigned int)'G';
const unsigned int P_KEY = (unsigned int)'P';
const unsigned int T_KEY = (unsigned int)'T';
const unsigned int UP_KEY = VK_UP;
const unsigned int DOWN_KEY = VK_DOWN;
const unsigned int LEFT_KEY = VK_LEFT;
const unsigned int RIGHT_KEY = VK_RIGHT;
const unsigned int SPACE_KEY = VK_SPACE;

// THIS IS JUST FOR SHOWING HOW THE CURSOR CAN BE CHANGED
const unsigned int C_KEY = (unsigned int)'C';

// SPRITE TYPES
static const int PLAYER_SPRITE_TYPE = 0;
static const int ZOMBIE_SPRITE_TYPE = 1;
static const int BAT_SPRITE_TYPE = 2;
static const int BALL_SPRITE_TYPE = 3;