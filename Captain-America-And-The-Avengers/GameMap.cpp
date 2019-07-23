#include "pch.h"
#include "Game.h"
#include "GameMap.h"

using namespace std;
GameMap::GameMap(const wchar_t* filePathIMap, const wchar_t* filePathMMap, Camera* camera)
{
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
				Pos = D3DXVECTOR3(1.0f * j * TileWidth, 1.0f * i * TileHeight, 0);//Toa do thuc cua Tile
				RECT sourceRECT;
				sourceRECT.left = Left * TileWidth;
				sourceRECT.right = sourceRECT.left + TileWidth;
				sourceRECT.top = Top * TileHeight;
				sourceRECT.bottom = sourceRECT.top + TileHeight;
				SpriteMap->SetRect(sourceRECT);
				SpriteMap->Draw(Pos, D3DXVECTOR2(), trans);
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
//	bool shouldContinue = true;
//	for (int i = 0; i < mMap->GetNumObjectGroups(); ++i)
//	{
//		const Tmx::ObjectGroup* objectGroup = mMap->GetObjectGroup(i);
//		if (objectGroup->GetName().compare("Location") == 0)
//		{
//			for (int j = 0; j < objectGroup->GetNumObjects(); ++j)
//			{
//				auto obj = objectGroup->GetObjectW(j);
//				if (obj->GetName().compare("PlayerSpawn") == 0)
//				{
//					spawnPoint.x = (float)obj->GetX();
//					spawnPoint.y = (float)obj->GetY();
//					shouldContinue = false;
//					break;
//				}
//			}
//		}
//		if (!shouldContinue) break;
//	}
	return spawnPoint;
}