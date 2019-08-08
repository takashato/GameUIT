#pragma once
#include "Scene.h"
#include "CharlestonScene.h"
#include "CharlestonBossScene.h"
#include "PittsburghScene.h"
#include "PittsburghExtra1Scene.h"
#include "PittsburghExtra2Scene.h"
#include "RedAlertBossScene.h"

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

	Scene* mSceneExtra1 = NULL;
	Scene* mSceneExtra2 = NULL;
	Scene* mScenePittsburg = NULL;

	Keyboard* mKeyboard = NULL;
};