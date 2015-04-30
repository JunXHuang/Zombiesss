#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\ai\Bot.h"
#include "buggin_out\BugginOutCollisionListener.h"
#include "tmxmi\TMXMapImporter.h"
#include "Box2D\Dynamics\Contacts\b2Contact.h"
#include "Box2D\Dynamics\b2Fixture.h"
#include "buggin_out\BugginOut.h"
#include "buggin_out\BugginOutKeyEventHandler.h"
#include "sssf\XAudio2\XAudio2.h"
void BugginOutCollisionListener::BeginContact(b2Contact* contact) {

	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	AnimatedSprite *Obj1=NULL,*Obj2=NULL;
	if (bodyUserData)
		Obj1 = static_cast<AnimatedSprite*>(bodyUserData);
	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		Obj2 = static_cast<AnimatedSprite*>(bodyUserData);

	if (Obj1 && Obj2){
		int obj1ID = Obj1->getSpriteType()->getSpriteTypeID();
		int obj2ID = Obj2->getSpriteType()->getSpriteTypeID();
		if ((obj1ID == 0 || obj2ID == 0) && (obj1ID != 6 && obj2ID != 6)) {
			//player vs zombie
			AnimatedSprite* player;
			Bot* bot;
			if (obj1ID == 0) {
				player = Obj1;
				bot = static_cast<Bot*>(Obj2);
			} else {
				player = Obj2;
				bot = static_cast<Bot*>(Obj1);
			}
			if (player->getY() + (3 * (player->getSpriteType()->getTextureHeight() / 4)) < bot->getY())
				bot->getGame()->getGSM()->getSpriteManager()->removeBot(bot);
			else 
				bot->getGame()->getGSM()->finishGame();
		}
		if ((obj1ID == 6 || obj2ID == 6) && (obj1ID != 0 && obj2ID != 0)) {
			//bat vs zombie
			Bot* bat;
			Bot* bot;
			if (obj1ID == 6) {
				bat = static_cast<Bot*>(Obj1);
				bot = static_cast<Bot*>(Obj2);
			} else {
				bat = static_cast<Bot*>(Obj2);
				bot = static_cast<Bot*>(Obj1);
			}
			bot->getGame()->getGSM()->getSpriteManager()->removeBot(bot);
		}
	}
}

void BugginOutCollisionListener::EndContact(b2Contact* contact) {

	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<AnimatedSprite*>(bodyUserData);

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<AnimatedSprite*>(bodyUserData);

}

void BugginOutCollisionListener::OutOfBounds(Game* game) {
	//player out of bounds
	AnimatedSprite *player= game->getGSM()->getSpriteManager()->getPlayer();
	XAudio2 *xAudio2 = game->getGSM()->getXAudio2();
	if (player->getLevelCheck() != 3){
		if (player->getX() > game->getGSM()->getWorld()->getWorldWidth() || player->getY() > game->getGSM()->getWorld()->getWorldHeight()){
			TMXMapImporter tmxMapImporter;
			BugginOutKeyEventHandler temp;
			game->getGSM()->getSpriteManager()->unloadSprites();
			game->getGSM()->getWorld()->unloadWorld();
			player->setLevelCheck((player->getLevelCheck() + 1) % 3);
			switch (player->getLevelCheck()){
			case 2:
				tmxMapImporter.loadWorld(game, W_LEVEL_2_DIR, W_LEVEL_2_NAME);
				player->setPosition(PLAYER_LEVEL2_X, PLAYER_LEVEL2_Y);
				xAudio2->FreeAudioEngine();
				xAudio2->initXAudio();
				xAudio2->loadWavFile(Level2Sound);
				xAudio2->createSource();
				xAudio2->getSource()->SetVolume(0.1);
				xAudio2->playAudio();
				temp.loadSprites(game);
				break;
			case 0:
				player->setLevelCheck(3);
				tmxMapImporter.loadWorld(game, W_LEVEL_3_DIR, W_LEVEL_3_NAME);
				player->setPosition(PLAYER_LEVEL3_X, PLAYER_LEVEL3_Y);
				xAudio2->FreeAudioEngine();
				xAudio2->initXAudio();
				xAudio2->loadWavFile(Level3Sound);
				xAudio2->createSource();
				xAudio2->getSource()->SetVolume(0.1);
				xAudio2->playAudio();
				temp.loadSprites(game);
				break;
			default: break;
			}
		}
	}
}

