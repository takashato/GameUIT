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
#include "Grid.h"
#include "Ground.h"

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

	void CheckChageMap();
	void ChangeMap(int ID);
protected:
	Camera* mCamera = NULL;
	GameMap* mMap = NULL;
	Grid* mGrid = NULL;

	Player* mPlayer = NULL;
	GunEnemy* gunEnemy1 = NULL, *gunEnemy2 = NULL, *gunEnemy3 = NULL, *gunEnemy4 = NULL;
	MissileEnemy *missileEnemy1 = NULL, *missileEnemy2 = NULL;
	RunEnemy *runEnemy1 = NULL;
	Ground *ground1 = NULL, *ground2 = NULL, *ground3 = NULL, *ground4 = NULL, *ground5 = NULL, *ground6 = NULL, *ground7 = NULL, *ground8 = NULL, *ground9 = NULL, *ground10 = NULL;
private:
	int MapID, MapMaxID;
	
};