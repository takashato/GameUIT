#pragma once
#include "MapReader/tinyxml2.h"

struct DataGround {
	GroundType type;
	int x, y, w, h, subType;
	DataGround(GroundType type, int x, int y, int w, int h, int subType) {
		this->type = type;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->subType = subType;
	};
};

struct DataIronBar {
	int x, y, w, h;
	DataIronBar(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	};
};

struct DataEnemy {
	EnemyType type;
	int x, y, subType;
	DataEnemy(EnemyType type, int x, int y, int subType) {
		this->type = type;
		this->x = x;
		this->y = y;
		this->subType = subType;
	}
};

struct DataCapsule {
	int x, y;
	std::vector<ItemType> itemList;
	DataCapsule(int x, int y, std::vector<ItemType> itemList)
	{
		this->x = x;
		this->y = y;
		this->itemList = std::move(itemList);
	}
};

class SceneData
{
public:
	SceneData();
	SceneData(LPCSTR filePath);
	~SceneData();

	void ReadData(LPCSTR filePath);

	const char* GetTilemapImagePath() { return mTilemapIPath.c_str(); };
	const char* GetTilemapMatrixPath() { return mTilemapMPath.c_str(); };

	D3DXVECTOR3 GetSpawnPoint(LPCSTR name);
	std::list<DataGround>& GetDataGround() { return mDataGrounds; };
	std::list<DataIronBar>& GetDataIronBar() { return mDataIronBars; };
	std::list<DataEnemy>& GetDataEnemy() { return mDataEnemies; };
	std::list<DataCapsule>& GetDataCapsule() { return mDataCapsules; };

private:
	tinyxml2::XMLNode* pRoot = nullptr;

	std::string mTilemapIPath;
	std::string mTilemapMPath;
	std::unordered_map<std::string, D3DXVECTOR3> mSpawnPoints;
	std::list<DataGround> mDataGrounds;
	std::list<DataEnemy> mDataEnemies;
	std::list<DataCapsule> mDataCapsules;
	std::list<DataIronBar> mDataIronBars;
};