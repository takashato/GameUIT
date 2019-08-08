#include "pch.h"
#include "PlayerFalling.h"
#include "Player.h"
#include "Ground.h"
#include "BreakGround.h"

void PlayerFalling::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.SetVelocityY(FALL_SPEED_VER_MIN);
	/*if (fromState == State::Captain_Tackle)
		cap.vel.x = 0.0f;
	key = KeyControls::Default;*/
	if (fromState == EPlayerState::HighJumping || fromState == EPlayerState::Jumping || fromState == EPlayerState::Kicking) {
		isKicked = data.Get<bool>(IS_KICKED);
	}
}

Data PlayerFalling::Exit(Player& player, EPlayerState toState)
{
	isKicked = false;
	data.Add(IS_KICKED, isKicked);
	return std::move(data);
}

void PlayerFalling::Update(Player& player, float deltaTime)
{
	if (player.GetVelocityY() < FALL_SPEED_VER_MAX)
	{
		player.AddVelocityY(GRAVITY * 2.5 * deltaTime);
	}
}

void PlayerFalling::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		if (player.mIsCollisionLeftRightSide && player.mDirectionUnblock == Left)
		{
			player.mIsCollisionLeftRightSide = false;
		}

		if (player.GetVelocityX() >= 0)
		{
			player.SetVelocityX(-MOVING_HOR);
			player.SetDirection((EntityDirection)-1);
		}
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		if (player.mIsCollisionLeftRightSide && player.mDirectionUnblock == Right)
		{
			player.mIsCollisionLeftRightSide = false;
		}

		if (player.GetVelocityX() >= 0)
		{
			player.SetVelocityX(MOVING_HOR);
			player.SetDirection((EntityDirection)1);
		}
	}

	//case KeyControls::Attack:
	//	isKicked = true;
	//	cap.SetState(State::Captain_Kicking);
	//	return;
}

void PlayerFalling::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_KEY_ATTACK)
	{
		if (!isKicked)
		{
			isKicked = true;
			player.SetState(EPlayerState::Kicking);
		}
	}
}

void PlayerFalling::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_RIGHT || code == VK_LEFT)
	player.SetVelocityX(.0f);
}

void PlayerFalling::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	player.mIsCollisionLeftRightSide = false;
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
					if (((Ground*)ce->entity)->GetGroundType() == EGroundNormal || (((Ground*)ce->entity)->GetGroundType() == EGroundDynamic)
						|| (((Ground*)ce->entity)->GetGroundType() == EGroundBreak))
					{
						player.skipGround = ce->entity;
					}
				}
			}

			if (((Ground*)ce->entity)->GetGroundType() == EGroundBreak)
			{
				((BreakGround*)ce->entity)->isCollidedWithPlayer = true;
			}

			if (((Ground*)ce->entity)->GetGroundType() == EGroundHard)
			{
				if (ce->nx == -1.0f)
				{
					player.mIsCollisionLeftRightSide = true;
					//player.mDirectionUnblock = Left;
					player.SetVelocityX(.0f);
					player.SetPositionX(ce->entity->GetPosition().x - (player.GetWidth() / 2 + Player::PLAYER_HITBOX_HALF));
				}
				else if (ce->nx == 1.0f)
				{
					player.mIsCollisionLeftRightSide = true;
					//player.mDirectionUnblock = Right;
					player.SetVelocityX(.0f);
					player.SetPositionX(ce->entity->GetBoundingBox().right - (player.GetWidth() / 2 - Player::PLAYER_HITBOX_HALF));
				}
			}
		}
		if (ce->entity->GetCollidableObjectType() == EIronBar)
		{
			player.SetState(EPlayerState::Cling);
			player.SetPositionY(ce->entity->GetPosition().y);
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
		else if (((Ground*)groundCe->entity)->GetGroundType() == EGroundThorns && player.mState->GetState() != EPlayerState::SittingOnShield)
		{
			player.TakeDamage(1);
		}
		else if (((Ground*)groundCe->entity)->GetGroundType() == GroundType::EGroundDynamic)
		{
			player.SetState(EPlayerState::Standing);
		}
		else
		{
			player.SetState(EPlayerState::Sitting);
		}
		player.SetPositionY(groundCe->entity->GetPosition().y - player.GetHeight());
	}
}

EPlayerState PlayerFalling::GetState()
{
	return EPlayerState::Falling;
}
