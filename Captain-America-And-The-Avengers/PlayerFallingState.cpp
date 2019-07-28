#include "pch.h"
#include "PlayerFallingState.h"

PlayerFallingState::PlayerFallingState(Player* player) : PlayerState(player)
{
	mPlayer->SetVelocityY(0);
}

void PlayerFallingState::HandleKeyboard(Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerKickingState(mPlayer));
	}
}

void PlayerFallingState::Update(float deltaTime)
{
	mPlayer->AddVelocityY(PLAYER_GRAVITY * deltaTime);
}

EPlayerState PlayerFallingState::GetState()
{
	return EPlayerState::Falling;
}

void PlayerFallingState::OnCollision(CollisionEvent* ce)
{
	if (ce->entity->GetCollidableObjectType() == EPlatform && ce->ny == -1.0f)
	{
		Player* player = mPlayer; // Avoid null
		player->SetState(new PlayerSittingState(player));
		player->SetPositionY(ce->entity->GetPosition().y - player->GetHeight());
	}
}
