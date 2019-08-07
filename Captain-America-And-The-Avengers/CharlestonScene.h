#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "Shield.h"
#include "GunEnemy.h"
#include "MissileEnemy.h"
#include "RunEnemy.h"
#include "GunStock.h"
#include "BossCharleston.h"
#include "Camera.h"
#include "GameMap.h"
#include "Grid.h"
#include "Ground.h"
#include "DynamicGround.h"
#include "BreakGround.h"
#include "MapObjectReader.h"
#include "Capsule.h"
#include "TransportArea.h"

class CharlestonScene : public Scene
{
public:
	CharlestonScene();
	~CharlestonScene();

	void Setup();
	void Update(float deltaTime);
	void Draw();

	SoundType GetBgMusic();

	MapID GetMapID() {
		return MapID::Charleston;
	};

	void Transport();

private:
	std::unique_ptr<Player> mPlayer;

	// Inherited via Scene
	virtual void OnKeyUp(BYTE key) override;
	virtual void OnKeyDown(BYTE key) override;


};