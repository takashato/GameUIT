#include "pch.h"
#include "DemoScene.h"

DemoScene::DemoScene() : Scene()
{
	Setup();
}

void DemoScene::Setup()
{
	Scene::Setup();
	mMap = new GameMap((char*)"Resources\\Map\\CharlestonMap.tmx");
	mPlayer = new Player();
}

void DemoScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	mPlayer->HandleKeyboard(mKeyboard);
	mPlayer->Update(deltaTime);
}

void DemoScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();
	Scene::Draw();
}

void DemoScene::OnKeyUp(BYTE keyCode)
{
	Scene::OnKeyUp(keyCode);
}

void DemoScene::OnKeyDown(BYTE keyCode)
{
	Scene::OnKeyDown(keyCode);
}
