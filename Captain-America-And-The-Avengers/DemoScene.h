#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
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

protected:
	Camera* mCamera = NULL;

	Player* mPlayer = NULL;
	GameMap* mMap = NULL;
};