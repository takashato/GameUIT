#pragma once
#include "Entity.h"
#include "SceneData.h"
#include "Enemy.h"

class Spawner: public Entity
{
public:
	Spawner(D3DXVECTOR3 position, DataEnemy enemyData, float spawnInterval = 5.0f);
	~Spawner();
	virtual RECT GetBoundingBox() override;
	virtual CollidableObjectType GetCollidableObjectType() override;

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 trans);
	void Spawn();

	Enemy* GetEnemy() { return mEnemy; }

	void OnDelete();
	
private:
	bool spawnFirstTime = false;
	float spawnInterval;

	DataEnemy dataEnemy;

	Enemy* mEnemy = nullptr;

	float mCounter = 0.0f;
};