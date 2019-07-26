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
<<<<<<< HEAD
=======

>>>>>>> 30065f4b9e405d273d4c4d14da9107aa49f2ba8f
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

	std::vector<Enemy*> mEnemies;

	Ground *ground1 = NULL, *ground2 = NULL, *ground3 = NULL, *ground4 = NULL, *ground5 = NULL, *ground6 = NULL, *ground7 = NULL, *ground8 = NULL, *ground9 = NULL, *ground10 = NULL;
private:
	int MapID, MapMaxID;
	
};