#pragma once
#include "MapReader/tinyxml2.h"

struct DataGround {
	GroundType type;
	int x, y, w, h;
	DataGround(GroundType type, int x, int y, int w, int h) {
		this->type = type;
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
	std::list<DataEnemy>& GetDataEnemy() { return mDataEnemies; };

private:
	tinyxml2::XMLNode* pRoot = nullptr;

	std::string mTilemapIPath;
	std::string mTilemapMPath;
	std::unordered_map<std::string, D3DXVECTOR3> mSpawnPoints;
	std::list<DataGround> mDataGrounds;
	std::list<DataEnemy> mDataEnemies;
};