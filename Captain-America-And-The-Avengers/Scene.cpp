#include "pch.h"
#include "Scene.h"

Scene::Scene(LPCSTR filePath)
{
	mData.ReadData(filePath);
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
