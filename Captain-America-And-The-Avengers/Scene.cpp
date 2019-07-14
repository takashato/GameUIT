#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
}

void Scene::Setup()
{
}

void Scene::Update(float deltaTime)
{
}

void Scene::Draw()
{
}

void Scene::OnKeyDown(BYTE keyCode)
{
	mKeyboard.OnKeyDown(keyCode);
}

void Scene::OnKeyUp(BYTE keyCode)
{
	mKeyboard.OnKeyUp(keyCode);
}

Keyboard& Scene::GetKeyboard()
{
	return mKeyboard;
}
