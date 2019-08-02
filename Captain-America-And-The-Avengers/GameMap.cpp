#include "pch.h"
#include "Game.h"
#include "GameMap.h"

using namespace std;
GameMap::GameMap(int MapID, const wchar_t* filePathIMap, const wchar_t* filePathMMap, Camera* camera)
{
	mID = MapID;
	TileWidth = TileHeight = 32;
	mCamera = camera;
	LoadMap(filePathIMap, filePathMMap);
	LoadGround();
}

GameMap::~GameMap()
{
	for (int i = 0; i < InHeight; i++)
		delete[] MatrixMap[i];
	delete[] MatrixMap;
	/*delete mMap;*/
}

void GameMap::LoadMap(const wchar_t* filePathIMap, const wchar_t* filePathMMap)
{
	ifstream ReadMap(filePathMMap);
	ReadMap >> InTile >> InWidth >> InHeight;
	MatrixMap = new int*[InHeight];
	for (int i = 0; i < InHeight; i++)
		MatrixMap[i] = new int[InWidth];
	for (int i = 0; i < InHeight; i++)
		for (int j = 0; j < InWidth; j++)
		{
			ReadMap >> MatrixMap[i][j];
		}
	SpriteMap = new Sprite(filePathIMap);
}

void GameMap::Draw(D3DXVECTOR2 trans)
{
	//Fix camera render error
	int x, y;
	x = static_cast<int>(trans.x);
	y = static_cast<int>(trans.y);
	D3DXVECTOR2 trans2((float)x,(float)y);
	D3DXVECTOR3 Pos;
	//Xu li theo luoi bitmap chuan 32x32
	//Chieu ngang va chieu doc camera
	int Width, Height;
	Width = mCamera->GetWidth();
	Height = mCamera->GetHeight();
	//Camera Bound
	RECT Bound;
	Bound = mCamera->GetBound();
		//Chon hang va cot de render tile
		int RowTileStart, RowTileEnd, ColTileStart, ColTileEnd;
		ColTileStart = Bound.left / TileWidth;
		ColTileEnd = ColTileStart + Width / TileWidth;
		RowTileStart = Bound.top / TileHeight;
		RowTileEnd = RowTileStart + Height / TileHeight;
		int ID;
		if (ColTileEnd < InWidth)
			ColTileEnd++;
		if (RowTileEnd < InHeight)
			RowTileEnd++;
		//Xu li Tilset co chieu ngang khong qua 80 tile (Do quy dinh cat tileset)
		for (int i = RowTileStart; i < RowTileEnd; i++)
			for (int j = ColTileStart; j < ColTileEnd; j++)
			{
				int Left, Top;
				ID = MatrixMap[i][j];
				if (ID / 80 == 0)
				{
					Top = 0;
					Left = ID;
				}
				else
				{
					Top = ID / 80;
					Left = ID - Top * 80;
				}
				Pos = D3DXVECTOR3(1.0f * j * TileWidth, 1.0f* i * TileHeight, .0f);//Toa do thuc cua Tile
				RECT sourceRECT;
				sourceRECT.left = Left * TileWidth;
				sourceRECT.right = sourceRECT.left + TileWidth;
				sourceRECT.top = Top * TileHeight;
				sourceRECT.bottom = sourceRECT.top + TileHeight;
				SpriteMap->SetRect(sourceRECT);
				SpriteMap->Draw(Pos, D3DXVECTOR2(), trans2);
			}
}

void GameMap::SetCamera(Camera* camera)
{
	mCamera = camera;
}

RECT GameMap::GetBoundary()
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = GetWidth();
	bound.bottom = GetHeight();
	return bound;
}

int GameMap::GetWidth()
{
	return InWidth * TileWidth;
}

int GameMap::GetHeight()
{
	return InHeight * TileHeight;
}

D3DXVECTOR3 GameMap::GetPlayerSpawnPoint()
{
	D3DXVECTOR3 spawnPoint(.0f, .0f, .0f);
switch (mID)
	{
	case ID_MAP_CHARLESTON:
		spawnPoint = SPAWPOINT_CHARLESTON;
			break;
	case ID_MAP_CHARLESTON_BOSS_LIGHT:
		spawnPoint = SPAWPOINT_MiniMap;
		break;
	case ID_MAP_PITTSBURGH_DARK:
		spawnPoint = SPAWPOINT_PITTSBURGH;
		break;
	case ID_MAP_PITTSBURGH_DARK_EXTRA_1:
		break;
	case ID_MAP_PITTSBURGH_DARK_EXTRA_2:
		break;
	case ID_MAP_RED_ALERT:
		break;
	default:
		break;
	}
	return spawnPoint;
}
void GameMap::LoadGround()
{
	if (mID == ID_MAP_CHARLESTON)
	{
		
	}
	else if (mID == ID_MAP_CHARLESTON_BOSS_DARK || mID == ID_MAP_CHARLESTON_BOSS_LIGHT)
	{

	}
	else if (mID == ID_MAP_PITTSBURGH_DARK || mID == ID_MAP_PITTSBURGH_LIGHT)
	{

	}
	else if (mID == ID_MAP_PITTSBURGH_DARK_EXTRA_1 || mID == ID_MAP_PITTSBURGH_LIGHT_EXTRA_1)
	{

	}
	else if (mID == ID_MAP_PITTSBURGH_DARK_EXTRA_2 || mID == ID_MAP_PITTSBURGH_LIGHT_EXTRA_2)
	{

	}
	else if (mID==ID_MAP_RED_ALERT)
	{
		 
	}
}
