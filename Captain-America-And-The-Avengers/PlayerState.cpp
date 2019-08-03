#include "pch.h"
#include "PlayerState.h"

PlayerState::PlayerState()
{
}

EPlayerState PlayerState::GetState()
{
	return EPlayerState::Running;
}
