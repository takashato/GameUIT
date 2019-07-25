#include "pch.h"
#include "Game.h"
#include "GameMap.h"

using namespace std;
GameMap::GameMap(int MapID, const wchar_t* filePathIMap, const wchar_t* filePathMMap, Camera* camera)
{
	isAnimation = false;
	mID = MapID;
	TileWidth = TileHeight = 32;
	mCamera = camera;
	LoadMap(filePathIMap, filePathMMap);
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
	/*mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	for (int i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset* tileset = mMap->GetTileset(i);

		std::string directoryPath = StringUtils::GetDirectoryFromFilePath(filePath);
		directoryPath += "\\" + tileset->GetImage()->GetSource();
		std::wstring wFilePath = std::wstring(directoryPath.begin(), directoryPath.end());
		Sprite* sprite = new Sprite(wFilePath.c_str());
		mTilesetMap.insert(std::pair<int, Sprite*>(i, sprite));
	}*/
}

void GameMap::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(Game::GetInstance().GetWidth() / 2 - mCamera->GetPosition().x,
		Game::GetInstance().GetHeight() / 2 - mCamera->GetPosition().y);
	//Fix camera render error
	int x, y;
	x = trans.x;
	y = trans.y;
	D3DXVECTOR2 trans2(x,y);
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
				Pos = D3DXVECTOR3(j * TileWidth, i * TileHeight, 0);//Toa do thuc cua Tile
				RECT sourceRECT;
				sourceRECT.left = Left * TileWidth;
				sourceRECT.right = sourceRECT.left + TileWidth;
				sourceRECT.top = Top * TileHeight;
				sourceRECT.bottom = sourceRECT.top + TileHeight;
				SpriteMap->SetRect(sourceRECT);
				SpriteMap->Draw(Pos, D3DXVECTOR2(), trans2);
			}
	/*for (int i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer* layer = mMap->GetTileLayer(i);
		if (!layer->IsVisible())
		{
			continue;
		}

		for (int j = 0; j < mMap->GetNumTilesets(); j++)
		{
			const Tmx::Tileset* tileSet = mMap->GetTileset(j);
			RECT sourceRECT;

			int tileWidth = mMap->GetTileWidth();
			int tileHeight = mMap->GetTileHeight();

			int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (int m = 0; m < layer->GetHeight(); m++)
			{
				for (int n = 0; n < layer->GetWidth(); n++)
				{
					if (layer->GetTileTilesetIndex(n, m) != -1)
					{
						int tileID = layer->GetTileId(n, m);

						int y = tileID / tileSetWidth;
						int x = tileID - y * tileSetWidth;

						sourceRECT.top = y * tileHeight;
						sourceRECT.bottom = sourceRECT.top + tileHeight;
						sourceRECT.left = x * tileWidth;
						sourceRECT.right = sourceRECT.left + tileWidth;

						Sprite* sprite = mTilesetMap[j];

						D3DXVECTOR3 position(1.0f * n * tileWidth, 1.0f * m * tileHeight, 0);

						sprite->SetRect(sourceRECT);

						sprite->Draw(position, D3DXVECTOR2(), trans);
					}
				}
			}
		}
	}*/
		isAnimation = !isAnimation;
}

void GameMap::SetCamera(Camera* camera)
{
	mCamera = camera;
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
	case ID_MAP_PITTSBURGH_EXTRA_1:
		break;
	case ID_MAP_PITTSBURGH_EXTRA_2:
		break;
	case ID_MAP_RED_ALERT:
		break;
	default:
		break;
	}
	return spawnPoint;
}