#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "GunEnemy.h"
#include "MissileEnemy.h"
#include "RunEnemy.h"
#include "Camera.h"
#include "GameMap.h"

class DemoScene : public Scene
{
public:
	DemoScene();
	~DemoScene();

	void Setup();

	void Update(float deltaTime);
	void Draw();

	void CheckCamera();

	void SetMapId(int ID) { MapID = ID; }

	void ChangeMap(int ID);
protected:
	Camera* mCamera = NULL;
	Player* mPlayer = NULL;
	GameMap* mMap = NULL;
	GunEnemy* gunEnemy1 = NULL, *gunEnemy2 = NULL, *gunEnemy3 = NULL, *gunEnemy4 = NULL;
	MissileEnemy *missileEnemy1 = NULL, *missileEnemy2 = NULL;
private:
	int MapID, MapMaxID;
	RunEnemy *runEnemy1 = NULL;
};