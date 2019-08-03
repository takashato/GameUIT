#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "Shield.h"
#include "GunEnemy.h"
#include "MissileEnemy.h"
#include "RunEnemy.h"
#include "BossCharleston.h"
#include "Camera.h"
#include "GameMap.h"
#include "Grid.h"
#include "Ground.h"
#include "MapObjectReader.h"

class CharlestonScene : public Scene
{
public:
	CharlestonScene();
	~CharlestonScene();

	void Setup();
	void Update(float deltaTime);
	void Draw();

	SoundType GetBgMusic();

private:
	std::unique_ptr<Camera> mCamera;
	std::unique_ptr<GameMap> mMap;
	std::unique_ptr<Grid> mGrid;

	std::unique_ptr<Player> mPlayer;

	// Inherited via Scene
	virtual void OnKeyUp(BYTE key) override;
	virtual void OnKeyDown(BYTE key) override;
};