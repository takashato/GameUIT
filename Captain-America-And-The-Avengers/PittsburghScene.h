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
#include "IronBar.h"
#include "MapObjectReader.h"
#include "Capsule.h"
#include "FlyRocketEnemy.h"
#include "Bat.h"
#include "Door.h"

enum TypeExtra
{
	Type1,
	Type2
};
class PittsburghScene : public Scene
{
public:
	PittsburghScene();
	~PittsburghScene();

	void Setup();
	void Update(float deltaTime);
	void Draw();

	SoundType GetBgMusic();

	MapID GetMapID() {
		return MapID::Pittsburgh;
	};

	void Transport(/*TypeExtra type*/);

	void CheckAmbush();
	void EnterAmbush();
	void LeaveAmbush();

private:
	std::unique_ptr<Player> mPlayer;

	// Inherited via Scene
	virtual void OnKeyUp(BYTE key) override;
	virtual void OnKeyDown(BYTE key) override;

	bool enteredAmbush = false;
	bool passedAmbush = false;

	std::set<Spawner*> spawnerList, ambushSpawner;
};