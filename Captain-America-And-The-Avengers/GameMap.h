#pragma once
#include "Sprite.h"
#include "./MapReader/Tmx.h.in"
#include "StringUtils.h"

class GameMap
{
public:
	GameMap(char* filePath);
	~GameMap();
	void LoadMap(char* filePath);
	void Draw();

protected:
	Tmx::Map* mMap;
	std::map<int, Sprite*> mTilesetMap;
};