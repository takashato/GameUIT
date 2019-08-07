#pragma once
#include "Animation.h"
class ExitSignal
{
public:
	friend class Player;

private:
	bool isCollectKeyCrystal = false;
	ExitSignal() = default;
	ExitSignal(const ExitSignal&) = delete;

public:
	void CollectKeyCrystal(bool isCollected);
	void Draw() const;
	Animation* mAni = NULL;
};

