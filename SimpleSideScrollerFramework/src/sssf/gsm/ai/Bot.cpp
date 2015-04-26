#include "sssf/gsm/ai/Bot.h"
#include "sssf/gsm/state/GameStateManager.h"

static int LPPrint(LuaPlus::LuaState* state) {
	OutputDebugStringA(state->CheckString(1));
	OutputDebugStringA("\n");

	return 0;
}

Bot::Bot(string fileName, int argc, string argk[], string argv[]) {
	luaState = LuaPlus::LuaState::Create(true);

	for (int i = 0; i < argc; i++) {
		luaState->GetGlobals().SetString(argk[i].c_str(), argv[i].c_str());
	}

	init(fileName);
}

Bot::Bot(string fileName, int argc, string argv[]) {
	luaState = LuaPlus::LuaState::Create(true);
	
	for (int i = 0; i < argc; i++) {
		luaState->GetGlobals().SetString(i, argv[i].c_str());
	}

	init(fileName);
}

void Bot::init(string fileName) {
	LuaPlus::LuaObject luaGlobals = luaState->GetGlobals();
	luaGlobals.Register("PrintString", LPPrint);

	//forward bot functions
	luaMetaTable = luaGlobals.CreateTable("MultiObjectMetaTable");
	luaMetaTable.SetObject("__index", luaMetaTable);
	luaMetaTable.RegisterObjectDirect("changeFrame",		(AnimatedSprite*)0,		&Bot::changeFrame);
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
	LuaPlus::LuaState::Destroy(luaState);
}


void Bot::think(Game *game) {
	LuaPlus::LuaObject luaPlayer = luaState->BoxPointer(game->getGSM()->getSpriteManager()->getPlayer());
	luaPlayer.SetMetaTable(luaMetaTable);

	LuaPlus::LuaFunction<int> lThink = luaState->GetGlobal("think");
	lThink(luaPlayer);
}