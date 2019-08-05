#pragma once
#include "Keyboard.h"
#include "SceneData.h"
#include "SoundManager.h"
#include "Grid.h"
#include "Camera.h"
#include "GameMap.h"

class Scene {
public:
	Scene(LPCSTR filePath);
	~Scene() = default;

	virtual void Setup() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	virtual void OnKeyUp(BYTE key) = 0;
	virtual void OnKeyDown(BYTE key) = 0;

	virtual SoundType GetBgMusic() 
	{
		return SoundType::Invalid;
	};

	virtual bool HasBgMusic() 
	{
		return GetBgMusic() != SoundType::Invalid;
	}


	Grid* GetGrid() { return mGrid.get(); }
	Camera* GetCamera() { return mCamera.get(); }
	GameMap* GetMap() { return mMap.get(); }

	bool mCanTransport = false;

protected:
	std::unique_ptr<Camera> mCamera;
	std::unique_ptr<GameMap> mMap;
	std::unique_ptr<Grid> mGrid;

	SceneData mData;
};