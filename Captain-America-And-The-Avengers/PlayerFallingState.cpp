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

void PlayerFallingState::CheckCollision(std::list<Entity*> entities)
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

			std::cout << "t = " << t << "\n";

			if (t >= 0.0f && t <= 0.03f)
			{
				std::cout << "Collision with this ground!!\n";
				//mPlayer->AddPositionY(t * mPlayer->GetVelocityX());
				mPlayer->SetPositionY(entity->GetPosition().y - mPlayer->GetBoundingBox().bottom);
				mPlayer->SetState(new PlayerStandingState(mPlayer));
				return;
			}
		}
	}
}
