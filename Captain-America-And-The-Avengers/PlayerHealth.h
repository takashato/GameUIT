#pragma once
#include "Animation.h"

class PlayerHealth
{
	friend class Player;

private:
	int health = 12;

	PlayerHealth() = default;
	PlayerHealth(const PlayerHealth&) = delete;

public:
	int Subtract(int dh);
	int Add(int dh);
	void Set(int h);
	void Draw() const;
	int Get() const { return health; }

	Animation* mAni = NULL;
};