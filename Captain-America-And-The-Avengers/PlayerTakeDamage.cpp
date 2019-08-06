#include "pch.h"
#include "Player.h"
#include "Ground.h"
#include "PlayerTakeDamage.h"

void PlayerTakeDamage::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	SoundManager::GetInstance().CPlaySound(SoundType::BeAttack);
	maxTimeHold = 0;
	pendingSwitchState = EPlayerState::NA;
	DistanceLeftToClimb = 0.0f;
	player.SetVelocityX(INJURE_FALL_SPEED * player.mDirection * -1.0f);
	player.SetVelocityY(FALL_SPEED_VER);
	posxWhenGotInjure = player.mPosition.x;
	posyWhenGotInjure = player.mPosition.y;
	holdingDistance = 0.0f;
	mCounter = .0f;
}

Data PlayerTakeDamage::Exit(Player& player, EPlayerState toState)
{
	return std::move(data);
}

void PlayerTakeDamage::Update(Player& player, float deltaTime)
{
	if (player.mHealth.Get() <= 0)
	{
		player.SetState(EPlayerState::TakeDown);
		return;
	}

	mCounter += deltaTime;
	if (mCounter >= INJURE_STATE_HOLD_TIME)
	{
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerTakeDamage::HandleKeyboard(Player& player, Keyboard* keyboard)
{
}

void PlayerTakeDamage::OnKeyDown(Player& player, BYTE code)
{
}

void PlayerTakeDamage::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerTakeDamage::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	bool collisionWithGround = false;
	CollisionEvent* groundCe = nullptr;
	for (auto ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EPlatform)
		{
			if (ce->ny == -1.0f)
			{
				if (!player.jumpThrough)
				{
					if (player.skipGround != ce->entity)
					{
						collisionWithGround = true;
						groundCe = ce;
					}
				}
				else
				{
					player.jumpThrough = false;
					if (((Ground*)ce->entity)->GetGroundType() == EGroundNormal)
					{
						player.skipGround = ce->entity;
					}
				}
			}

			if (((Ground*)ce->entity)->GetGroundType() == EGroundHard)
			{
				if (ce->nx == -1.0f)
				{
					player.mIsCollisionLeftRightSide = true;
					player.mDirectionUnblock = Left;
					player.SetPositionX(ce->entity->GetPosition().x - player.GetWidth());
				}
				else if (ce->nx == 1.0f)
				{
					player.mIsCollisionLeftRightSide = true;
					player.mDirectionUnblock = Right;
					player.SetPositionX(ce->entity->GetBoundingBox().right);
				}
			}
		}
	}
	if (collisionWithGround)
	{
		if (player.skipGround != nullptr) player.skipGround = nullptr;
		if (((Ground*)groundCe->entity)->GetGroundType() == EGroundWater)
		{
			SoundManager::GetInstance().CPlaySound(SoundType::FallingWater);
			player.SetState(EPlayerState::Swimming);
		}
		else
		{
			player.SetVelocityY(.0f);
		}
		player.SetPositionY(groundCe->entity->GetPosition().y - player.GetHeight());
	}
}
