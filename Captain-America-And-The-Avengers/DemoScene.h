#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "Shield.h"
#include "GunEnemy.h"
#include "MissileEnemy.h"
#include "RunEnemy.h"
#include "BossCharleston.h"
#include "Camera.h"
#include "GameMap.h"
#include "Grid.h"
#include "Ground.h"
#include "MapObjectReader.h"

class DemoScene : public Scene
{
public:
	DemoScene();
	~DemoScene();

	void Setup();

	void Update(float deltaTime);
	void Draw();

	void CheckCamera(float deltaTime);

	void SetMapId(int ID) { MapID = ID; }

	void CheckChageMap();
	void ChangeMap(int ID);

protected:
	Camera* mCamera = NULL;
	GameMap* mMap = NULL;
	Grid* mGrid = NULL;

	Player* mPlayer = NULL;

	std::vector<Enemy*> mEnemies;
	std::vector<Ground*> mGrounds;

	std::vector<Entity*> mEntities;

private:
	int MapID, MapMaxID;
	
};