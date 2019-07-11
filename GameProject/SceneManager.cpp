#include "pch.h"
#include "SceneManager.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager sceneManager;
	return sceneManager;
}

void SceneManager::SetupDefaultScene()
{
	mCurrentScene = new DemoScene();
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

void SceneManager::OnKeyDown(BYTE keyCode)
{
	if (mCurrentScene == NULL) return;
	mCurrentScene->OnKeyDown(keyCode);
}

void SceneManager::OnKeyUp(BYTE keyCode)
{
	if (mCurrentScene == NULL) return;
	mCurrentScene->OnKeyUp(keyCode);
}
