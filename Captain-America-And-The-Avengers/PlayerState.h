#pragma once
#include "Keyboard.h"

class Player;

enum EPlayerState {
	Standing,
	Running,
	Jumping
};

class PlayerState
{
public:
	PlayerState(Player* player);
	Player* GetPlayer();

	virtual EPlayerState GetState();
	virtual void HandleKeyboard(Keyboard &keyboard);

protected:
	Player* mPlayer = nullptr;
};