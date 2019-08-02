#include "pch.h"
#include "SceneManager.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager sceneManager;
	return sceneManager;
}

void SceneManager::Setup()
{
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
