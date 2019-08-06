#include "pch.h"
#include "PlayerHighJumping.h"
#include "Player.h"
#include "Ground.h"

void PlayerHighJumping::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	SetAnotherState = false;
	player.SetVelocityY(-SPIN_SPEED_VER);
	beginnx = player.GetDirection();

	isKicked = data.Get<bool>(IS_KICKED);
	if (isKicked)
	{
		if (fromState == EPlayerState::Kicking || fromState == EPlayerState::Jumping) {
			timeUp = data.Get<float>(SPIN_TIME_UP);
			timeDown = data.Get<float>(SPIN_TIME_DOWN);
		}
	}
	else
	{
		timeUp = 0;
		timeDown = 0;
	}

	SoundManager::GetInstance().CPlaySound(SoundType::JumpTurn);
}

Data PlayerHighJumping::Exit(Player& player, EPlayerState toState)
{
	player.SetDirection((EntityDirection)beginnx);
	data.Add(IS_KICKED, isKicked);
	data.Add(SPIN_TIME_DOWN, timeDown);
	data.Add(SPIN_TIME_UP, timeUp);
	return std::move(data);
}

void PlayerHighJumping::Update(Player& player, float deltaTime)
{
	if (counterTimeFlip >= 0.15f)
	{
		counterTimeFlip = 0;
		player.SetDirection((EntityDirection)(-player.GetDirection()));
	}
	else counterTimeFlip += Timer::Dt();
	player.GetCurrentAnimation()->Update(deltaTime);
	if (timeUp < TIME_KEEP_SPIN) {
		timeUp += Timer::Dt();
		player.SetVelocityY(-SPIN_SPEED_VER);
	}
	else
	{
		if (timeDown < TIME_KEEP_SPIN)
		{
			timeDown += Timer::Dt();
			player.SetVelocityY(SPIN_SPEED_VER);
		}
		else
		{
			isKicked = false;
			player.SetState(EPlayerState::Falling);
			return;
		}
	}
}

void PlayerHighJumping::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		if (player.mIsCollisionLeftRightSide && player.mDirectionUnblock == Left)
		{
			player.mIsCollisionLeftRightSide = false;
		}
		player.SetVelocityX(-SPIN_SPEED_HOR);
	}
	if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		if (player.mIsCollisionLeftRightSide && player.mDirectionUnblock == Right)
		{
			player.mIsCollisionLeftRightSide = false;
		}
		player.SetVelocityX(SPIN_SPEED_HOR);
	}
	if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		if (timeUp >= TIME_KEEP_SPIN && timeDown >= TIME_KEEP_SPIN)
		{
			player.SetState(EPlayerState::SittingOnShield);
			return;
		}
	}
}

void PlayerHighJumping::OnKeyDown(Player& player, BYTE code)
{
	if (!isKicked) {
		if (code == VK_KEY_ATTACK)
		{
			isKicked = true;
			player.SetState(EPlayerState::Kicking);
			return;
		}
	}
}

void PlayerHighJumping::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_LEFT || code == VK_RIGHT)
		player.SetVelocityX(.0f);
}

void PlayerHighJumping::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	bool collisionWithGroundTop = false;
	bool collisionWithGroundBottom = false;

	CollisionEvent* groundCe = nullptr;
	for (auto ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EPlatform)
		{
			if (ce->ny == -1.0f)
			{
				collisionWithGroundBottom = true;
				groundCe = ce;
			}

			if (((Ground*)ce->entity)->GetGroundType() == EGroundHard)
			{
				if (ce->ny == 1.0f)
				{
					collisionWithGroundTop = true;
					groundCe = ce;
				}

				if (ce->nx == -1.0f)
				{
					player.mIsCollisionLeftRightSide = true;
					player.mDirectionUnblock = Left;
					player.SetVelocityX(.0f);
					player.SetPositionX(ce->entity->GetPosition().x - player.GetWidth());
				}
				else if (ce->nx == 1.0f)
				{
					player.mIsCollisionLeftRightSide = true;
					player.mDirectionUnblock = Right;
					player.SetVelocityX(.0f);
					player.SetPositionX(ce->entity->GetBoundingBox().right);
				}
			}
		}
	}
	if (collisionWithGroundTop)
	{
		player.SetState(EPlayerState::Falling);
		player.SetPositionY(groundCe->entity->GetBoundingBox().bottom);
	}
	else if (collisionWithGroundBottom)
	{
		player.SetState(EPlayerState::Sitting);
		player.SetPositionY(groundCe->entity->GetPosition().y - player.GetHeight());
	}
}

EPlayerState PlayerHighJumping::GetState()
{
	return EPlayerState::HighJumping;
}
