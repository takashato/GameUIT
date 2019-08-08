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
#include "MapObjectReader.h"
#include "Capsule.h"
#include "BossRedAlert.h"

class RedAlertBossScene : public Scene
{
public:
	RedAlertBossScene();
	~RedAlertBossScene();

	void Setup();
	void Update(float deltaTime);
	void Draw();

	SoundType GetBgMusic();
	MapID GetMapID() { return MapID::RedAlertBoss; }

	void Transport() {/*Khong co*/}

private:
	std::unique_ptr<Player> mPlayer;

	// Inherited via Scene
	virtual void OnKeyUp(BYTE key) override;
	virtual void OnKeyDown(BYTE key) override;

	};