#include "sssf/gsm/ai/Bot.h"
#include "sssf/gsm/state/GameStateManager.h"

static Bot* thisBot;

static int LPPrint(LuaPlus::LuaState* state) {
	OutputDebugStringA(state->CheckString(1));
	OutputDebugStringA("\n");

	return 0;
}

static int LPSpawn(LuaPlus::LuaState* state) {
	Game* game = thisBot->getGame();
	SpriteManager* spriteManager = game->getGSM()->getSpriteManager();
	AnimatedSprite* player = spriteManager->getPlayer();

	string keys[] = { "init"};
	string vals[] = { "1"};
	Bot *bot = new Bot(game, "data/bots/BallBot.lua", 1, keys, vals);
	bot->setSpriteType(spriteManager->getSpriteType(7));
	bot->setAlpha(255);
	bot->setCurrentState(L"IDLE");
	bot->applyPhysics(game);
	bot->setPosition(thisBot->getX(), thisBot->getY());
	bot->setGravity(false);
	spriteManager->addBot(game, bot);
	if (thisBot->getX() > player->getX()) {
		bot->setVelocity(-30, 0);
	} else {
		bot->setVelocity(30, 0);
	}

	return 0;
}

Bot::Bot(Game* initGame, string fileName, int argc, string argk[], string argv[]) {
	game = initGame;
	luaState = LuaPlus::LuaState::Create(true);

	for (int i = 0; i < argc; i++) {
		luaState->GetGlobals().SetString(argk[i].c_str(), argv[i].c_str());
	}

	init(fileName);
}

Bot::Bot(Game* initGame, string fileName, int argc, string argv[]) {
	game = initGame;
	luaState = LuaPlus::LuaState::Create(true);
	
	for (int i = 0; i < argc; i++) {
		luaState->GetGlobals().SetString(i, argv[i].c_str());
	}

	init(fileName);
}

void Bot::init(string fileName) {
	LuaPlus::LuaObject luaGlobals = luaState->GetGlobals();
	luaGlobals.Register("PrintString", LPPrint);
	luaGlobals.Register("SpawnBall", LPSpawn);

	//forward bot functions
	luaMetaTable = luaGlobals.CreateTable("MultiObjectMetaTable");
	luaMetaTable.SetObject("__index", luaMetaTable);
	//luaMetaTable.RegisterObjectDirect("changeFrame",		(AnimatedSprite*)0,		&Bot::changeFrame);
	luaMetaTable.RegisterObjectDirect("getAlpha",			(AnimatedSprite*)0,		&Bot::getAlpha);
	luaMetaTable.RegisterObjectDirect("getCurrentImageID",	(AnimatedSprite*)0,		&Bot::getCurrentImageID);
	//luaMetaTable.RegisterObjectDirect("getCurrentState",	(AnimatedSprite*)0,		&Bot::getCurrentState);
	luaMetaTable.RegisterObjectDirect("getFrameIndex",		(AnimatedSprite*)0,		&Bot::getFrameIndex);
	//luaMetaTable.RegisterObjectDirect("getSpriteType",	(AnimatedSprite*)0,		&Bot::getSpriteType);
	luaMetaTable.RegisterObjectDirect("getVelocityX",		(CollidableObject*)0,	&Bot::getVelocityX);
	luaMetaTable.RegisterObjectDirect("getVelocityY",		(CollidableObject*)0,	&Bot::getVelocityY);
	luaMetaTable.RegisterObjectDirect("getX",				(CollidableObject*)0,	&Bot::getX);
	luaMetaTable.RegisterObjectDirect("getY",				(CollidableObject*)0,	&Bot::getY);
	luaMetaTable.RegisterObjectDirect("setAlpha",			(AnimatedSprite*)0,		&Bot::setAlpha);
	//luaMetaTable.RegisterObjectDirect("setCurrentState",	(AnimatedSprite*)0,		&Bot::setCurrentState);
	//luaMetaTable.RegisterObjectDirect("setSpriteType",	(AnimatedSprite*)0,		&Bot::setSpriteType);
	luaMetaTable.RegisterObjectDirect("setVelocity",		(CollidableObject*)0,	&Bot::setVelocity);
	luaMetaTable.RegisterObjectDirect("setPosition",		(CollidableObject*)0,	&Bot::setPosition);

	LuaPlus::LuaObject luaThis = luaState->BoxPointer(this);
	luaThis.SetMetaTable(luaMetaTable);
	luaGlobals.SetObject("this", luaThis);

	if (luaState->DoFile(fileName.c_str())) {
		// error
		OutputDebugStringA("Lua Error: ");
		if (luaState->GetTop() == 1) {
			OutputDebugStringA(luaState->CheckString(1));
		}
		OutputDebugStringA("\n");
	} else {
		LuaPlus::LuaFunction<int> lInit = luaState->GetGlobal("init");
		lInit();
	}
}

Bot::~Bot() {
	if (physics)
		body->GetWorld()->DestroyBody(body);
	physics = false;
}

void Bot::setVar(string var, int val) {
	LuaPlus::LuaObject sObj = luaState->GetGlobal(var.c_str());
	sObj.AssignInteger(luaState, val);
}

void Bot::setVar(string var, float val) {
	LuaPlus::LuaObject sObj = luaState->GetGlobal(var.c_str());
	sObj.AssignNumber(luaState, val);
}

void Bot::setVar(string var, string val) {
	LuaPlus::LuaObject sObj = luaState->GetGlobal(var.c_str());
	sObj.AssignString(luaState, val.c_str());
}


void Bot::think(Game *game) {
	thisBot = this;

	LuaPlus::LuaObject luaPlayer = luaState->BoxPointer(game->getGSM()->getSpriteManager()->getPlayer());
	luaPlayer.SetMetaTable(luaMetaTable);

	LuaPlus::LuaFunction<int> lThink = luaState->GetGlobal("think");
	lThink(luaPlayer);
}