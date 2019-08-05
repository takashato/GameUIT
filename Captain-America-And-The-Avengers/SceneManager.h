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

	/*void ChangeScene();*/
private:
	SceneManager() : ISingleton(NULL) {}
	Scene* mCurrentScene = NULL;

	Keyboard* mKeyboard = NULL;
};