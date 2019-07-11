#include "pch.h"
#include "DemoScene.h"

SceneDemo::SceneDemo() : Scene()
{
	Setup();
}

void SceneDemo::Setup()
{
	Scene::Setup();
	aladdin = new Animation(L"Resources\\Sprites\\Aladdin_run.png", 38, 55, 12, 1, 0.8F / 12);
}

void SceneDemo::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	aladdin->Update(deltaTime);
}

void SceneDemo::Draw()
{
	aladdin->Draw(D3DXVECTOR3(0, 0, 0));
	Scene::Draw();
}

void SceneDemo::OnKeyUp(BYTE keyCode)
{
	std::cout << "Keyup!\n";
	Scene::OnKeyUp(keyCode);
	aladdin->SetTimePerFrame(0.8F / 12);
}

void SceneDemo::OnKeyDown(BYTE keyCode)
{
	std::cout << "Keydown!\n";
	Scene::OnKeyDown(keyCode);
	aladdin->SetTimePerFrame(0.1F / 12);
}
