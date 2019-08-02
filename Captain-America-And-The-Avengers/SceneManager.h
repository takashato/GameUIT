#pragma once
#include "Scene.h"
#include "DemoScene.h"
#include "CharlestonScene.h"

class SceneManager : ISingleton
{
public:
	static SceneManager& GetInstance();
	
	void Setup();

	void Update(float deltaTime);
	void Draw();

	Keyboard* GetKeyboard();

private:
	SceneManager() : ISingleton(NULL) {}
	Scene* mCurrentScene = NULL;

	Keyboard* mKeyboard = NULL;
};