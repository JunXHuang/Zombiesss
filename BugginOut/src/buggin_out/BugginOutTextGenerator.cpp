/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugginOutTextGenerator.cpp

	See BugginOutTextGenerator.h for a class description.
*/

#include "buggin_out_VS\stdafx.h"
#include "buggin_out\BugginOut.h"
#include "buggin_out\BugginOutTextGenerator.h"
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\text\GameText.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

static const wstring	W_MOUSE_COORDS_TEXT = L"Mouse: (";
static const wstring	W_PLAYER_POSITION_TEXT = L"Player Position: (";
static const wstring	W_PLAYER_VELOCITY_TEXT = L"Player Velocity: (";
static const int		W_TEXT_X = 200;
static const int		W_TEXT_Y = 10;

void BugginOutTextGenerator::appendMouseCoords(Game *game)
{
	wstringstream wss;
	WindowsInput *input = (WindowsInput*)game->getInput();
	textToGenerate.append(W_MOUSE_COORDS_TEXT);
	wss << input->getMousePoint()->x;
	wss << L", ";
	wss << input->getMousePoint()->y;
	wss << L")";
	wss << L"\n";
	textToGenerate.append(wss.str());
}

void BugginOutTextGenerator::appendPlayerInfo(Game *game)
{
	wstringstream wss1;
	wstringstream wss2;
	CollidableObject* player = game->getGSM()->getSpriteManager()->getPlayer();
	if (!player->isPhysicsSet()) return;
	textToGenerate.append(W_PLAYER_POSITION_TEXT);
	wss1 << (int)player->getX();
	wss1 << L", ";
	wss1 << (int)player->getY();
	wss1 << L")";
	wss1 << L"\n";
	textToGenerate.append(wss1.str());
	textToGenerate.append(W_PLAYER_VELOCITY_TEXT);
	wss2 << (int)player->getVelocityX();
	wss2 << L", ";
	wss2 << (int)player->getVelocityY();
	wss2 << L")";
	wss2 << L"\n";
	wss2 <<game->getGSM()->getSpriteManager()->getPlayer()->getLevelCheck() << "\n";
	textToGenerate.append(wss2.str());
}

/*
	initText - Provides an example of how to render text to our screen every frame,
	allowing for the text to continually change. This method adds a text object
	to the text manager (GameText), which allows it to be updated each frame. This
	method should be called only once for each object.
*/
void BugginOutTextGenerator::initText(Game *game)
{
	// FIRST UPDATE THE TEXT THIS GENERATOR IS USING
	appendMouseCoords(game);
	appendPlayerInfo(game);

	// AND THEN HAND IT TO THE TEXT MANAGER, SPECIFYING WHERE IT SHOULD BE RENDERED
	GameText *text = game->getText();
	text->addText(&textToGenerate, W_TEXT_X, W_TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
}

/*
	updateText - updates the text. Note that the text must already have been added
	to the text manager via the initText method. Also not that there should be a
	separate TextGenerator for each line of text we wish to render.
*/
void BugginOutTextGenerator::updateText(Game *game)
{
	// THE TEXT MANAGER (GameText) HAS A POINTER TO OUR TEXT, SO WE CAN
	// SIMPLY CLEAR IT OUT OF OLD CHARACTER DATA AND FILL IT IN WITH
	// WHAT WE WANT.
	textToGenerate.clear();
	appendMouseCoords(game);
	appendPlayerInfo(game);
}