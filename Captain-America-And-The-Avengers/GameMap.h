#pragma once
#include "Sprite.h"
#include "Camera.h"
#include "./MapReader/Tmx.h.in"
#include "StringUtils.h"
#include "fstream"
class GameMap
{
public:
	GameMap(int MapID, const wchar_t* filePathIMap, const wchar_t* filePathMMap, Camera* camera = NULL);//Imagepath vs MatrixMap
	~GameMap();
	void LoadMap(const wchar_t* filePathIMap, const wchar_t* filePathMMap);
	void Draw();

	void SetCamera(Camera* camera);

	int GetWidth();
	int GetHeight();

	D3DXVECTOR3 GetPlayerSpawnPoint();
protected:

	int TileWidth, TileHeight;
	int InTile, InWidth, InHeight;//InWidth = tile tren hang , InHeight = tile tren cot 
	int **MatrixMap;
	Sprite* SpriteMap = NULL;
	Camera* mCamera;
private:
	int mID;
};