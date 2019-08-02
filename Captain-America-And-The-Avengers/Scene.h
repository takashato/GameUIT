#pragma once
#include "Keyboard.h"
#include "SceneData.h"
#include "SoundManager.h"

class Scene {
public:
	Scene(LPCSTR filePath);
	~Scene() = default;

	virtual void Setup() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	virtual SoundType GetBgMusic() 
	{
		return SoundType::Invalid;
	};

	virtual bool HasBgMusic() 
	{
		return GetBgMusic() != SoundType::Invalid;
	}

protected:
	SceneData mData;
};