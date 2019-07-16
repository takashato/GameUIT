#pragma once
#include "Sprite.h"
#include "Camera.h"
#include "./MapReader/Tmx.h.in"
#include "StringUtils.h"

class GameMap
{
public:
	GameMap(char* filePath, Camera* camera = NULL);
	~GameMap();
	void LoadMap(char* filePath);
	void Draw();

	void SetCamera(Camera* camera);

	int GetWidth();
	int GetHeight();

	D3DXVECTOR3 GetPlayerSpawnPoint();

protected:
	Tmx::Map* mMap;
	std::map<int, Sprite*> mTilesetMap;

	Camera* mCamera;
};