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
	mCurrentScene = new CharlestonScene();
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
