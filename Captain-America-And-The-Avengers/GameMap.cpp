#include "pch.h"
#include "Game.h"
#include "GameMap.h"

GameMap::GameMap(char* filePath, Camera* camera)
{
	mCamera = camera;
	LoadMap(filePath);
}

GameMap::~GameMap()
{
	delete mMap;
}

void GameMap::LoadMap(char* filePath)
{
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	for (int i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset* tileset = mMap->GetTileset(i);

		std::string directoryPath = StringUtils::GetDirectoryFromFilePath(filePath);
		directoryPath += "\\" + tileset->GetImage()->GetSource();
		std::wstring wFilePath = std::wstring(directoryPath.begin(), directoryPath.end());
		Sprite* sprite = new Sprite(wFilePath.c_str());
		mTilesetMap.insert(std::pair<int, Sprite*>(i, sprite));
	}
}

void GameMap::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(Game::GetInstance().GetWidth() / 2 - mCamera->GetPosition().x,
		Game::GetInstance().GetHeight() / 2 - mCamera->GetPosition().y);

	for (int i = 0; i < mMap->GetNumTileLayers(); i++)
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
	}
}

void GameMap::SetCamera(Camera* camera)
{
	mCamera = camera;
}


int GameMap::GetWidth()
{
	return mMap->GetWidth()* mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
	return mMap->GetHeight()* mMap->GetTileHeight();
}
