#include "pch.h"
#include "PlayerKickingState.h"

PlayerKickingState::PlayerKickingState(Player* player) : PlayerState(player)
{
}

EPlayerState PlayerKickingState::GetState()
{
	return Kicking;
}

void PlayerKickingState::HandleKeyboard(Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
	}
}

void PlayerKickingState::OnCollision(CollisionEvent* ce)
{
	if (ce->entity->GetCollidableObjectType() == EPlatform && ce->ny == -1.0f)
	{
		Player* player = mPlayer; // Avoid null
		player->SetState(new PlayerStandingState(player));
		player->SetPositionY(ce->entity->GetPosition().y - player->GetHeight());
	}
}
