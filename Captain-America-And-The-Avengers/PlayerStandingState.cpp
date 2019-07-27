#include "pch.h"
#include "PlayerStandingState.h"

PlayerStandingState::PlayerStandingState(Player* player) : PlayerState(player)
{
	player->SetVelocityX(0.0f);
	player->SetVelocityY(0.0f);
}

EPlayerState PlayerStandingState::GetState()
{
	return Standing;
}

void PlayerStandingState::HandleKeyboard(Keyboard* keyboard)
{
	int counter = 0;
	if (keyboard->IsPressing(GAME_KEY_LEFT) || keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		mPlayer->SetState(new PlayerRunningState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_JUMP))
	{
		mPlayer->SetState(new PlayerJumpingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		mPlayer->SetState(new PlayerSittingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_UP))
	{
		mPlayer->SetState(new PlayerHighShieldingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerThrowingShieldState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_SURF))
	{
		mPlayer->SetState(new PlayerSurfingState(mPlayer));	
	}
	
	/*else
	{
		mPlayer->SetVelocityX(.0f);
	}*/
}

void PlayerStandingState::CheckCollision(std::list<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		float t, nx, ny;

		if (entity->GetCollidableType() == CollidableType::EPlatform)
		{
			RECT playerBB = mPlayer->GetBoundingBox();
			RECT entityBB = entity->GetBoundingBox();
			CollisionEvent::GetInstance().SweptAABB(
				mPlayer->GetPosition().x,
				mPlayer->GetPosition().y,
				mPlayer->GetPosition().x + playerBB.right,
				mPlayer->GetPosition().y + playerBB.bottom,
				mPlayer->GetVelocityX(),
				mPlayer->GetVelocityY(),
				entity->GetPosition().x,
				entity->GetPosition().y,
				entity->GetPosition().x + entityBB.right,
				entity->GetPosition().y + entityBB.bottom,
				t,
				nx,
				ny
			);

			//std::cout << "Stand t = " << t << "\n";

			if (t >= 0.0f && t <= 0.03f)
			{
				std::cout << "Collision with this ground!!\n";
				return;
			}
		}
	}
}
