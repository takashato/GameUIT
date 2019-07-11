#pragma once
#include "Scene.h"
#include "DemoScene.h"

class SceneManager : ISingleton
{
public:
	static SceneManager& GetInstance();
	
	void SetupDefaultScene();

	void Update(float deltaTime);
	void Draw();

	void OnKeyDown(BYTE keyCode);
	void OnKeyUp(BYTE keyCode);

private:
	SceneManager() : ISingleton(NULL) {}
	Scene* mCurrentScene = NULL;
};