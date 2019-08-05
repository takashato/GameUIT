#pragma once
#include "Scene.h"
#include "CharlestonScene.h"
#include "CharlestonBossScene.h"

class SceneManager : ISingleton
{
public:
	static SceneManager& GetInstance();
	
	void Setup();

	void Update(float deltaTime);
	void Draw();

	Keyboard* GetKeyboard();

	void OnKeyUp(BYTE key);
	void OnKeyDown(BYTE key);

	Scene* GetScene();
	void ChangeScene(MapID mapID);

private:
	SceneManager() : ISingleton(NULL) {}
	Scene* mCurrentScene = NULL;

	Keyboard* mKeyboard = NULL;
};