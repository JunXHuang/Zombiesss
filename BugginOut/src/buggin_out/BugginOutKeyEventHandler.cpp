/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugginOutKeyEventHandler.cpp

	See BugginOutKeyEventHandler.h for a class description.
*/

#include "buggin_out_VS\stdafx.h"
#include "buggin_out\BugginOut.h"
#include "buggin_out\BugginOutKeyEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\game\WStringTable.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\timer\GameTimer.h"
#include "tmxmi\TMXMapImporter.h"
#include "sssf\platforms\Windows\WindowsTimer.h"
#include "sssf\XAudio2\XAudio2.h"
/*
	handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
	gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
	key states since the last frame, which can allow us to respond to key presses, including when keys
	are held down for multiple frames.
*/
void BugginOutKeyEventHandler::handleKeyEvents(Game *game)
{
	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	Viewport *viewport = game->getGUI()->getViewport();
	TMXMapImporter tmxMapImporter;
	World *unload = game->getGSM()->getWorld();
	SpriteManager *spriteManager = gsm->getSpriteManager();
	XAudio2 *xAudio2 = game->getGSM()->getXAudio2();
	
	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		// WASD KEY PRESSES WILL CONTROL THE PLAYER
		// SO WE'LL UPDATE THE PLAYER VELOCITY WHEN THESE KEYS ARE
		// PRESSED, THAT WAY PHYSICS CAN CORRECT AS NEEDED
		float vX = player->getVelocityX();
		float vY = player->getVelocityY();

		// YOU MIGHT WANT TO UNCOMMENT THIS FOR SOME TESTING,
		// BUT IN THIS ASSIGNMENT, THE USER MOVES VIA MOUSE BUTTON PRESSES
		if (input->isKeyDown(A_KEY))
		{
			vX = -PLAYER_SPEED;
			player->setCurrentState(ATTACKING_LEFT);
		}
		else if (input->isKeyDown(D_KEY))
		{
			vX = PLAYER_SPEED;
			player->setCurrentState(ATTACKING_RIGHT);
		}
		else if (input->isKeyDownForFirstTime(G_KEY))
		{
			viewport->toggleDebugView();
			game->getGraphics()->toggleDebugTextShouldBeRendered();
		}
		else
		{
			vX = 0.0f;
			player->setCurrentState(IDLE);
		}
		if (input->isKeyDownForFirstTime(SPACE_KEY))
		{
			if ((int)player->getVelocityY() == 0)
			{
				vY = JUMP_SPEED;
			}
			else
			{
				cout << "WHAT HAPPENED?";
			}
		}
		if (input->isKeyDownForFirstTime(P_KEY))
		{
			//gsm->getPhysics()->togglePhysics();
			xAudio2->initXAudio();
			xAudio2->loadWavFile(AudioStr);
			xAudio2->createSource();
			xAudio2->playAudio();
		}
		if (input->isKeyDownForFirstTime(T_KEY))
		{
			xAudio2->TurnOffAudio();
			//gsm->getPhysics()->activateForSingleUpdate();
		}
		/*load level 1 cheat CTRL +1*/
		if (input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(49u)){
			if (LevelCheck != 1){
				spriteManager->unloadSprites();
				unload->unloadWorld();
				tmxMapImporter.loadWorld(game, W_LEVEL_1_DIR, W_LEVEL_1_NAME);
				player->setPosition(PLAYER_LEVEL1_X, PLAYER_LEVEL1_Y);
				LevelCheck = 1;
				NumberOfBotsPerLevel = 10;
				loadSprites(game);
			}
		}
		/*load level 2 cheat CTRL + 2*/
		if (input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(50u)){
			if (LevelCheck != 2){
				spriteManager->unloadSprites();
				unload->unloadWorld();
				tmxMapImporter.loadWorld(game, W_LEVEL_2_DIR, W_LEVEL_2_NAME);
				player->setPosition(PLAYER_LEVEL2_X, PLAYER_LEVEL2_Y);
				LevelCheck = 2;
				NumberOfBotsPerLevel = 10;
				loadSprites(game);
			}
		}
		/*load level 3 cheat CTRL +3*/
		if (input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(51u)){
			if (LevelCheck != 3){
				spriteManager->unloadSprites();
				unload->unloadWorld();
				tmxMapImporter.loadWorld(game, W_LEVEL_3_DIR, W_LEVEL_3_NAME);
				player->setPosition(PLAYER_LEVEL3_X, PLAYER_LEVEL3_Y);
				LevelCheck = 3;
				NumberOfBotsPerLevel = 10;
				loadSprites(game);
			}
		}
		// NOW SET THE ACTUAL PLAYER VELOCITY
 		player->setVelocity(vX, vY);

		bool viewportMoved = false;
		float viewportVx = 0.0f;
		float viewportVy = 0.0f;
		if (input->isKeyDown(UP_KEY))
		{
			viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(DOWN_KEY))
		{
			viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(LEFT_KEY))
		{
			viewportVx -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(RIGHT_KEY))
		{
			viewportVx += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		Viewport *viewport = game->getGUI()->getViewport();

		if (!viewportMoved) {
			//check if viewport is not on player
			float pX = player->getX() + (player->getSpriteType()->getTextureWidth() / 2);
			float pY = player->getY() + (player->getSpriteType()->getTextureHeight() / 2);
			float centerX = (float)viewport->getViewportX() + (viewport->getViewportWidth() / 2);
			float centerY = (float)viewport->getViewportY() + (viewport->getViewportHeight() / 2);
			if (pX != centerX || pY != centerY) {
				//viewport not on player, move to player.
				if (centerY > pY)
					viewportVy -= min(MAX_VIEWPORT_AXIS_VELOCITY, fabs(centerY - pY));
				if (centerY < pY)
					viewportVy += min(MAX_VIEWPORT_AXIS_VELOCITY, fabs(centerY - pY));
				if (centerX > pX)
					viewportVx -= min(MAX_VIEWPORT_AXIS_VELOCITY, fabs(centerX - pX));
				if (centerX < pX)
					viewportVx += min(MAX_VIEWPORT_AXIS_VELOCITY, fabs(centerX - pX));
				viewportMoved = true;
			}
		}
		if (viewportMoved)
			viewport->moveViewport((int)floor(viewportVx+0.5f), (int)floor(viewportVy+0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());
		
	}

	// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
	// THIS CHANGES THE CURSOR IMAGE
	if ((input->isKeyDownForFirstTime(C_KEY))
		&& input->isKeyDown(VK_SHIFT))
	{
		Cursor *cursor = game->getGUI()->getCursor();
		unsigned int id = cursor->getActiveCursorID();
		id++;
		if (id == cursor->getNumCursorIDs())
			id = 0;		
		cursor->setActiveCursorID(id);
	}

	// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
	WindowsTimer *timer = (WindowsTimer*)game->getTimer();
	int fps = timer->getTargetFPS();

	// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
	// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
	// A BETTER PLAYER EXPERIENCE
	if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
		timer->setTargetFPS(fps + FPS_INC);

	// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
	else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
		timer->setTargetFPS(fps - FPS_INC);
}

void BugginOutKeyEventHandler::loadSprites(Game *game){
	AnimatedSpriteType *botSpriteType;
	int BotPosX, worldWidth = game->getGSM()->getWorld()->getWorldWidth()-500,worldHeight=game->getGSM()->getWorld()->getWorldHeight()/10;
	for (int i = 0; i < NumberOfBotsPerLevel; i++){
		botSpriteType = game->getGSM()->getSpriteManager()->getSpriteType(rand() % 4 + 1);
		BotPosX = rand() % worldWidth+500;
		makeRandomJumpingBot(game, botSpriteType, (float)BotPosX,(float)worldHeight);
	}
}
void BugginOutKeyEventHandler::makeRandomJumpingBot(Game *game, AnimatedSpriteType *randomJumpingBotType, float initX, float initY)
{
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	string keys[] = { "initMin", "initMax", "initVel" };
	string vals[] = { "30", "120", "128" };
	Bot *bot = new Bot(W_JUMP_BOT_FILE, 3, keys, vals);
	bot->setSpriteType(randomJumpingBotType);
	bot->setAlpha(255);
	bot->setCurrentState(L"JUMPING");
	bot->applyPhysics(game);
	bot->setPosition(initX, initY);
	spriteManager->addBot(game, bot);
}