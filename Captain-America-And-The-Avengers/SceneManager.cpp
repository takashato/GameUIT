#include "pch.h"
#include "SceneManager.h"
#include "Item.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager sceneManager;
	return sceneManager;
}

void SceneManager::Setup()
{
	Capsule::LoadAnimation();
	Item::LoadAnimation();
	mKeyboard = new Keyboard();
	//mCurrentScene = new CharlestonBossScene();
	ChangeScene(MapID::Charleston);
	//mCurrentScene = new CharlestonScene();
}

void SceneManager::Update(float deltaTime)
{
	if (mCurrentScene == NULL) return;
	mCurrentScene->Update(deltaTime);
}

void SceneManager::Draw()
{
	if (mCurrentScene == NULL) return;
	mCurrentScene->Draw();
}

Keyboard* SceneManager::GetKeyboard()
{
	return mKeyboard;
}

void SceneManager::OnKeyUp(BYTE key)
{
	mCurrentScene->OnKeyUp(key);
}

void SceneManager::OnKeyDown(BYTE key)
{
	switch (key)
	{
	case KEY_TOGGLE_DEBUG: // KEY D for debug
		Entity::shouldRenderBoundingBox = !Entity::shouldRenderBoundingBox;
		break;
	case (BYTE)'Q':
		mCurrentScene->Transport();
		break;
	}
	mCurrentScene->OnKeyDown(key);
}

Scene* SceneManager::GetScene()
{
	return mCurrentScene;
}


void SceneManager::ChangeScene(MapID mapID)
{
	if (mCurrentScene != nullptr && mCurrentScene->GetMapID() == mapID) return;
	
	if (mCurrentScene != nullptr)
	{
		if ((mapID == MapID::Pittsburgh &&
			(mCurrentScene->GetMapID() == MapID::PittsburghExtra1 || mCurrentScene->GetMapID() == MapID::PittsburghExtra2))
			||
			(mCurrentScene->GetMapID() == MapID::Pittsburgh &&
			(mapID == MapID::PittsburghExtra1 || mapID == MapID::PittsburghExtra2)))
		{
			std::cout << "Switch between extra map.\n";
		}
		else
		{
			delete mCurrentScene;
		}
	}

	switch (mapID)
	{
	case MapID::Charleston:		mCurrentScene = new CharlestonScene(); break;
	case MapID::CharlestonBoss:	mCurrentScene = new CharlestonBossScene(); break;
	case MapID::Pittsburgh:
		if (mScenePittsburg == nullptr) mScenePittsburg = new PittsburghScene();
		mCurrentScene = mScenePittsburg;
		if (mSceneExtra1 == nullptr) mSceneExtra1 = new PittsburghExtra1Scene();
		if (mSceneExtra2 == nullptr) mSceneExtra2 = new PittsburghExtra2Scene();
		break;
	case MapID::PittsburghExtra1:
		mCurrentScene = mSceneExtra1; 
		break;
	case MapID::PittsburghExtra2:
		mCurrentScene = mSceneExtra2; 
		break;
	case MapID::RedAlertBoss:	mCurrentScene = new RedAlertBossScene(); break;
	}
}

