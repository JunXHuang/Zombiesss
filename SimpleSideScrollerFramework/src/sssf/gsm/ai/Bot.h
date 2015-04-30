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
	Game* game;
	Bot(LuaPlus::LuaState* initState) { luaState = initState; }
public:
	Bot(Game* initGame, string fileName, int argc, string argk[], string argv[]);
	Bot(Game* initGame, string fileName, int argc, string argv[]);
	~Bot();

	Game* getGame() { return game; }
	void think(Game *game);
	void setVar(string var, int val);
	void setVar(string var, float val);
	void setVar(string var, string val);
	Bot* clone() { return new Bot(luaState); }
};