/*
Author: Richard McKenna
Stony Brook University
Computer Science Department

SpriteManager.cpp

See SpriteManager.h for a class description.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\XAudio2\XAudio2.h"

/*
addSpriteToRenderList - This method checks to see if the sprite
parameter is inside the viewport. If it is, a RenderItem is generated
for that sprite and it is added to the render list.
*/
void SpriteManager::addSpriteToRenderList(AnimatedSprite *sprite,
	RenderList *renderList,
	Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();

	// IS THE SPRITE VIEWABLE?
	if (viewport->areWorldCoordinatesInViewport(
		sprite->getX(),
		sprite->getY(),
		sprite->getSpriteType()->getTextureWidth(),
		sprite->getSpriteType()->getTextureHeight()))
	{
		// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
		RenderItem itemToAdd;
		itemToAdd.id = sprite->getFrameIndex();
		renderList->addRenderItem(sprite->getCurrentImageID(),
			(int)(sprite->getX() - viewport->getViewportX() + 0.5),
			(int)(sprite->getY() - viewport->getViewportY() + 0.5),
			0,
			sprite->getAlpha(),
			sprite->getSpriteType()->getTextureWidth(),
			sprite->getSpriteType()->getTextureHeight());
	}
}

/*
addSpriteItemsToRenderList - This method goes through all of the sprites,
including the player sprite, and adds the visible ones to the render list.
This method should be called each frame.
*/
void SpriteManager::addSpriteItemsToRenderList(Game *game)
{
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{
		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&player, renderList, viewport);

		// NOW ADD THE REST OF THE SPRITES
		list<Bot*>::iterator botIterator;
		/*	botIterator = bots.begin();
		while (botIterator != bots.end())
		{
		Bot *bot = (*botIterator);
		addSpriteToRenderList(bot, renderList, viewport);
		botIterator++;
		}
		*/
		Btree *temp = bots;
		botIterator = temp->bots.begin();
		while (botIterator != temp->bots.end())
		{
			Bot *bot = (*botIterator);
			addSpriteToRenderList(bot, renderList, viewport);
			botIterator++;
		}
		for (int i = 0; i < 2; i++) {
			botIterator = temp->next[i]->bots.begin();
			while (botIterator != temp->next[i]->bots.end())
			{
				Bot *bot = (*botIterator);
				addSpriteToRenderList(bot, renderList, viewport);
				botIterator++;
			}
			for (int j = 0; j < 2; j++) {
				botIterator = temp->next[i]->next[j]->bots.begin();
				while (botIterator != temp->next[i]->next[j]->bots.end())
				{
					Bot *bot = (*botIterator);
					addSpriteToRenderList(bot, renderList, viewport);
					botIterator++;
				}
			}
		}
	}
}

/*
addSprite - This method is for adding a new sprite to
this sprite manager. Once a sprite is added it can be
scheduled for rendering.
*/
void SpriteManager::addBot(Game *game, Bot *botToAdd)
{
	//bots.push_back(botToAdd);
	Btree *temp = bots;
	bool ran = false;
	int x =(int)botToAdd->getX(), num;
	int WorldX = game->getGSM()->getWorld()->getWorldWidth();
	//Adding bot to 3/4 to 1 of the map
	num = WorldX;
	num = num * 3;
	num = num / 4;
	if (x >= num){
		temp = temp->next[1];
		if (x != num)
			temp = temp->next[1];
		ran = true;
	}
	//Adding bot to 1/2 to 3/4 of the map
	num = WorldX;
	num = num / 2;
	if (x >= num&&!ran){
		temp = temp->next[1];
		if (x != num)
			temp = temp->next[0];
		ran = true;
	}
	//Adding bot to 1/4 to 1/2 of the map
	num = WorldX;
	num = num / 4;
	if (x >= num&&!ran){
		temp = temp->next[0];
		if (x != num)
			temp = temp->next[1];
		ran = true;
	}
	//Adding bot to 0 to 1/4 of the map
	if (x > 0 && !ran){
		temp = temp->next[0]->next[0];
	}
	//add bot
	temp->bots.push_back(botToAdd);
}

/*
addSpriteType - This method is for adding a new sprite
type. Note that one sprite type can have many sprites. For
example, we may say that there may be a "Bunny" type of
sprite, and specify properties for that type. Then there might
be 100 different Bunnies each with their own properties, but that
share many things in common according to what is defined in
the shared sprite type object.
*/
unsigned int SpriteManager::addSpriteType(AnimatedSpriteType *spriteTypeToAdd)
{
	spriteTypes.push_back(spriteTypeToAdd);
	return spriteTypes.size() - 1;
}

/*
clearSprites - This empties all of the sprites and sprite types.
*/
void SpriteManager::clearSprites()
{
	spriteTypes.clear();

}

/*
getSpriteType - This gets the sprite type object that corresponds
to the index argument.
*/
AnimatedSpriteType* SpriteManager::getSpriteType(unsigned int typeIndex)
{
	if (typeIndex < spriteTypes.size())
		return spriteTypes.at(typeIndex);
	else
		return NULL;
}

/*
unloadSprites - This method removes all artwork from memory that
has been allocated for game sprites.
*/
void SpriteManager::unloadSprites()
{
	//Clear all bots
	list<Bot*>::iterator it = bots->bots.begin();
	while (it != bots->bots.end()) {
		Bot* bot = *(it);
		it++;
		delete bot;
	}
	bots->bots.clear();
	for (int i = 0; i < 2; i++) {
		list<Bot*>::iterator it = bots->next[i]->bots.begin();
		while (it != bots->next[i]->bots.end()) {
			Bot* bot = *(it);
			it++;
			delete bot;
		}
		bots->next[i]->bots.clear();
		for (int j = 0; j < 2; j++) {
			list<Bot*>::iterator it = bots->next[i]->next[j]->bots.begin();
			while (it != bots->next[i]->next[j]->bots.end()) {
				Bot* bot = *(it);
				it++;
				delete bot;
			}
			bots->next[i]->next[j]->bots.clear();
		}
	}
}

Bot* SpriteManager::removeBot(Bot *botToRemove)
{
	//make sure there are no duplicates
	if (std::find(botsToRemove.begin(), botsToRemove.end(), botToRemove) == botsToRemove.end())
		botsToRemove.push_back(botToRemove); //remove bot
	return NULL;
}

/*
update - This method should be called once per frame. It
goes through all of the sprites, including the player, and calls their
update method such that they may update themselves.
*/
void SpriteManager::update(Game *game)
{
	for (list<Bot*>::iterator itr = botsToRemove.begin(); itr != botsToRemove.end(); itr++) {
		Bot* bot = (*itr);

		bots->bots.remove(bot);
		for (int i = 0; i < 2; i++) {
			bots->next[i]->bots.remove(bot);
			for (int j = 0; j < 2; j++)
				bots->next[i]->next[j]->bots.remove(bot);
		}
		if (bot)
			delete bot;
	}
	botsToRemove.clear();

	//walking sound effect
	if (player.getWalk()){
		if (player.getFC() >= 15){
			player.setFC(0);
			XAudio2 *xAudio2=game->getGSM()->getXAudio2();
			xAudio2->loadWavFile("data/Sound/walking.wav");
			xAudio2->createSource();
			xAudio2->playAudio();
			player.setWalk(false);
		}
		else
			player.setFC(player.getFC()+1);
	}
	// UPDATE THE PLAYER SPRITE
	player.updateSprite(game);

	World* world = game->getGSM()->getWorld();
	if (player.getX() < 0 || player.getY() < 0 ||
		player.getX() + player.getSpriteType()->getTextureWidth() > world->getWorldWidth() ||
		player.getY() + player.getSpriteType()->getTextureHeight() > world->getWorldHeight()) {
		world->getListener()->OutOfBounds(game);
	}

	
	// NOW UPDATE THE REST OF THE SPRITES
	Btree *temp = bots;
	int counter = temp->bots.size();
	while (counter--)
	{
		ProcessBot(game, temp->bots.front());
		temp->bots.pop_front();
	}
	for (int i = 0; i < 2; i++){
		temp = bots->next[i];
		counter = temp->bots.size();
		while (counter--)
		{
			ProcessBot(game, temp->bots.front());
			temp->bots.pop_front();
		}
		for (int j = 0; j < 2; j++){
			temp = bots->next[i]->next[j];
			counter = temp->bots.size();
			while (counter--)
			{
				ProcessBot(game, temp->bots.front());
				temp->bots.pop_front();
			}
		}
	}
}

void SpriteManager::ProcessBot(Game *game, Bot *bot){
	bot->think(game);
	bot->updateSprite(game);
	addBot(game, bot);

	/*World* world = game->getGSM()->getWorld();
	if (bot->getX() < 0 || bot->getY() < 0 ||
		bot->getX() + bot->getSpriteType()->getTextureWidth() > world->getWorldWidth() ||
		bot->getY() + bot->getSpriteType()->getTextureHeight() > world->getWorldHeight()) {
		world->getListener()->OutOfBounds(game, bot);
	}*/
}

SpriteManager::SpriteManager(){
	//Setting up Binary Tree into 4 different parts.
	bots = new Btree();
	for (int i = 0; i < 2; i++){
		Btree *botTemp = new Btree();
		bots->next[i] = botTemp;
		for (int j = 0; j < 2; j++){
			Btree *botTemp1 = new Btree();
			bots->next[i]->next[j] = botTemp1;
		}
	}

}
SpriteManager::~SpriteManager(){
	//Removing the Binary tree
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
			delete[] bots->next[i]->next[j];
		delete[] bots->next[i];
	}
	delete[] bots;
}