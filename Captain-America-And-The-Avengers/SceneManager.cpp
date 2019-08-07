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
	ChangeScene(MapID::Pittsburgh);
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
		delete mCurrentScene;
	switch (mapID)
	{
	case MapID::Charleston:		mCurrentScene = new CharlestonScene(); break;
	case MapID::CharlestonBoss:	mCurrentScene = new CharlestonBossScene(); break;
	case MapID::Pittsburgh:		mCurrentScene = new PittsburghScene(); break;
	case MapID::PittsburghExtra1:mCurrentScene = new PittsburghExtra1Scene(); break;
	case MapID::PittsburghExtra2:mCurrentScene = new PittsburghExtra2Scene(); break;
	}
}

