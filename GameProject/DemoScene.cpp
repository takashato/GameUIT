#include "pch.h"
#include "DemoScene.h"

DemoScene::DemoScene() : Scene()
{
	Setup();
}

void DemoScene::Setup()
{
	Scene::Setup();
	mEntities.push_back(new Player());
}

void DemoScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	for (std::size_t i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->Update(deltaTime);
	}
}

void DemoScene::Draw()
{
	for (std::size_t i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->Draw();
	}
	Scene::Draw();
}

void DemoScene::OnKeyUp(BYTE keyCode)
{
	Scene::OnKeyUp(keyCode);
	((Player*)mEntities[0])->SetState(PLAYER_STATE_NORMAL);
}

void DemoScene::OnKeyDown(BYTE keyCode)
{
	Scene::OnKeyDown(keyCode);
	((Player*)mEntities[0])->SetState(PLAYER_STATE_RUNNING);
}
