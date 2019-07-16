#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "GameMap.h"

class DemoScene : public Scene
{
public:
	DemoScene();
	
	void Setup();

	void Update(float deltaTime);
	void Draw();

	void OnKeyUp(BYTE keyCode);
	void OnKeyDown(BYTE keyCode);

protected:
	Player* mPlayer;
	GameMap* mMap;
};