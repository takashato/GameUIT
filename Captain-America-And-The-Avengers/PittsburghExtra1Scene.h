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

class PittsburghExtra1Scene : public Scene
{
public:
	PittsburghExtra1Scene();
	~PittsburghExtra1Scene();

	void Setup();
	void Update(float deltaTime);
	void Draw();

	SoundType GetBgMusic();
	MapID GetMapID() {
		return MapID::PittsburghExtra1;
	};

	void Transport();

	bool isLightOn = false;
	void ToggleLight();

private:
	std::unique_ptr<Player> mPlayer;
	std::unique_ptr<GameMap> mMapLight;

	// Inherited via Scene
	virtual void OnKeyUp(BYTE key) override;
	virtual void OnKeyDown(BYTE key) override;

	float lightInterval = .0f;

};