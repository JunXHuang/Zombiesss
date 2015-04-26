#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "LuaPlus.h"

class Bot : public AnimatedSprite {
protected:
	LuaPlus::LuaStateAuto luaState;
	LuaPlus::LuaObject luaMetaTable;
	void init(string fileName);
private:
	Bot(LuaPlus::LuaState* initState) { luaState = initState; }
public:
	Bot(string fileName, int argc, string argk[], string argv[]);
	Bot(string fileName, int argc, string argv[]);
	~Bot();

	void think(Game *game);
	Bot* clone() { return new Bot(luaState); }
};