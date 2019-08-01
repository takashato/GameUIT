#include "pch.h"
#include "PlayerFallingState.h"

PlayerFallingState::PlayerFallingState(Player* player) : PlayerState(player)
{
	mPlayer->SetVelocityY(0);
}

void PlayerFallingState::HandleKeyboard(Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		mRunState = -1;
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		mRunState = 1;
	}
	else
	{
		mRunState = 0;
	}

	if (keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerKickingState(mPlayer));
	}
	if (keyboard->IsPressing(DIK_A))
	{
		mPlayer->SetPositionY(0.f);
		if (mPlayer->GetPosition().x < 0)
			mPlayer->SetPositionX(50.f);
	}
}

void PlayerFallingState::Update(float deltaTime)
{
	mPlayer->AddVelocityY(PLAYER_GRAVITY * deltaTime);
	if (mRunState == -1)
	{
		if (mPlayer->GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
		{
			mPlayer->AddVelocityX(-PLAYER_ACC_X * deltaTime);
			if (mPlayer->GetVelocityX() < -PLAYER_VELOCITY_X_MAX)
				mPlayer->SetVelocityX(-PLAYER_VELOCITY_X_MAX);
		}
	}
	else if (mRunState == 1)
	{
		if (mPlayer->GetVelocityX() < PLAYER_VELOCITY_X_MAX)
		{
			mPlayer->AddVelocityX(PLAYER_ACC_X * deltaTime);
			if (mPlayer->GetVelocityX() > PLAYER_VELOCITY_X_MAX)
				mPlayer->SetVelocityX(PLAYER_VELOCITY_X_MAX);
		}
	}
	else
	{
		if (mPlayer->GetVelocityX() > .0f)
		{
			mPlayer->AddVelocityX(-PLAYER_ACC_X * deltaTime);
		}
		else
		{
			mPlayer->AddVelocityX(PLAYER_ACC_X * deltaTime);
		}
	}

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
		player->SetState(new PlayerStandingState(player));
		player->SetPositionY(ce->entity->GetPosition().y - player->GetHeight());
	}
}
