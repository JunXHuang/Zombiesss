#include "sssf/gsm/ai/Bot.h"

static int LPPrint(LuaPlus::LuaState* state) {
	OutputDebugStringA(state->CheckString(1));
	OutputDebugStringA("\n");

	return 0;
}

static int LPSetVelocity() {
	
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
	LuaPlus::LuaObject metaTableObj = luaGlobals.CreateTable("MultiObjectMetaTable");
	metaTableObj.SetObject("__index", metaTableObj);
	metaTableObj.RegisterObjectDirect("changeFrame",		(AnimatedSprite*)0,		&Bot::changeFrame);
	metaTableObj.RegisterObjectDirect("getAlpha",			(AnimatedSprite*)0,		&Bot::getAlpha);
	metaTableObj.RegisterObjectDirect("getCurrentImageID",	(AnimatedSprite*)0,		&Bot::getCurrentImageID);
	//metaTableObj.RegisterObjectDirect("getCurrentState",	(AnimatedSprite*)0,		&Bot::getCurrentState);
	metaTableObj.RegisterObjectDirect("getFrameIndex",		(AnimatedSprite*)0,		&Bot::getFrameIndex);
	//metaTableObj.RegisterObjectDirect("getSpriteType",	(AnimatedSprite*)0,		&Bot::getSpriteType);
	metaTableObj.RegisterObjectDirect("getVelocityX",		(CollidableObject*)0,	&Bot::getVelocityX);
	metaTableObj.RegisterObjectDirect("getVelocityY",		(CollidableObject*)0,	&Bot::getVelocityY);
	metaTableObj.RegisterObjectDirect("getX",				(CollidableObject*)0,	&Bot::getX);
	metaTableObj.RegisterObjectDirect("getY",				(CollidableObject*)0,	&Bot::getY);
	metaTableObj.RegisterObjectDirect("setAlpha",			(AnimatedSprite*)0,		&Bot::setAlpha);
	//metaTableObj.RegisterObjectDirect("setCurrentState",	(AnimatedSprite*)0,		&Bot::setCurrentState);
	//metaTableObj.RegisterObjectDirect("setSpriteType",	(AnimatedSprite*)0,		&Bot::setSpriteType);
	metaTableObj.RegisterObjectDirect("setVelocity",		(CollidableObject*)0,	&Bot::setVelocity);
	metaTableObj.RegisterObjectDirect("setPosition",		(CollidableObject*)0,	&Bot::setPosition);

	LuaPlus::LuaObject luaThis = luaState->BoxPointer(this);
	luaThis.SetMetaTable(metaTableObj);
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
	LuaPlus::LuaObject lGame = luaState->BoxPointer(game);
	LuaPlus::LuaFunction<int> lThink = luaState->GetGlobal("think");
	lThink(lGame);
}