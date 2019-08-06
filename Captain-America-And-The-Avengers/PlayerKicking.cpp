#include "pch.h"
#include "Player.h"
#include "PlayerKicking.h"

void PlayerKicking::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.SetVelocityY(FALL_SPEED_VER_MIN);
	firstTimeUpdate = true;
	SetAnotherState = false;
	assert(fromState == EPlayerState::Jumping || fromState == EPlayerState::HighJumping
		|| fromState == EPlayerState::Falling || fromState == EPlayerState::SittingOnShield);
	lastState = fromState;
	if (fromState == EPlayerState::Jumping)
	{
		isJumpReleased = data.Get<bool>(IS_JUMP_RELEASED);
		JumpHeightRealCounter = data.Get<float>(JUMP_HEIGHT_RealCounter);
		JumpHeightNeedCounter = data.Get<float>(JUMP_HEIGHT_NeedCounter);
	}
	if (fromState == EPlayerState::HighJumping)
	{
		timeUp = data.Get<float>(SPIN_TIME_UP);
		timeDown = data.Get<float>(SPIN_TIME_DOWN);
	}
}

Data PlayerKicking::Exit(Player& player, EPlayerState toState)
{
	SoundManager::GetInstance().CPlaySound(SoundType::Hit);
	isKicked = true;
	switch (toState)
	{
	case EPlayerState::Jumping:
		data.Add(JUMP_HEIGHT_RealCounter, JumpHeightRealCounter);
		data.Add(JUMP_HEIGHT_NeedCounter, JumpHeightNeedCounter);
		break;
	case EPlayerState::HighJumping:
		data.Add(SPIN_TIME_DOWN, timeDown);
		data.Add(SPIN_TIME_UP, timeUp);
		break;
	}
	data.Add(IS_JUMP_RELEASED, isJumpReleased);
	data.Add(IS_KICKED, isKicked);
	return std::move(data);
}

void PlayerKicking::Update(Player& player, float deltaTime)
{
	if (player.GetVelocityY() < FALL_SPEED_VER_MAX)
	{
		player.AddVelocityY(GRAVITY * 2.5 * deltaTime);
	}

	if (lastState == EPlayerState::Jumping) 
	{
		if (JumpHeightNeedCounter < MAX_JUMP_HEIGHT) 
		{
			if (!isJumpReleased) {
				JumpHeightNeedCounter += JUMP_SPEED_VER * deltaTime;
				player.SetVelocityY(-JUMP_SPEED_VER);
				JumpHeightRealCounter += JUMP_SPEED_VER * deltaTime;
			}
			else 
			{
				if (JumpHeightRealCounter < JumpHeightNeedCounter)
				{
					player.SetVelocityY(-JUMP_SPEED_VER);
					JumpHeightRealCounter += JUMP_SPEED_VER * deltaTime;
				}
				else
				{

				}
			}
		}
		else 
		{
			if (JumpHeightRealCounter < JumpHeightNeedCounter)
			{
				player.SetVelocityY(-JUMP_SPEED_VER);
				JumpHeightRealCounter += JUMP_SPEED_VER * deltaTime;
			}
			else
			{
				timeUp += Timer::Dt();
				player.SetVelocityY(-SPIN_SPEED_HOR);
				if (player.GetCurrentAnimation()->IsDoneCycle())
				{
					player.SetState(EPlayerState::HighJumping);
					return;
				}
			}
		}
		if (player.GetCurrentAnimation()->IsDoneCycle())
		{
			player.SetState(EPlayerState::Falling);
			return;
		}
	}
	else if (lastState == EPlayerState::HighJumping)
	{
		if (timeUp < TIME_KEEP_SPIN) {
			timeUp += Timer::Dt();
			player.SetVelocityY(-SPIN_SPEED_HOR);
		}
		else
		{
			isKicked = false;
			if (timeDown < TIME_KEEP_SPIN)
			{
				timeDown += Timer::Dt();
				player.SetVelocityY(SPIN_SPEED_HOR);
			}
			else
			{
				if (player.GetCurrentAnimation()->IsDoneCycle())
				{
					player.SetState(EPlayerState::Falling);
					return;
				}
			}
		}
		if (player.GetCurrentAnimation()->IsDoneCycle())
		{
			player.SetState(EPlayerState::HighJumping);
			return;
		}
	}
	else if (lastState == EPlayerState::Falling)
	{
		if (player.GetCurrentAnimation()->IsDoneCycle())
		{
			player.SetState(EPlayerState::Falling);
			return;
		}
	}
	else if (lastState == EPlayerState::SittingOnShield)
	{
		if (player.GetCurrentAnimation()->IsDoneCycle())
		{
			player.SetState(EPlayerState::Falling);
			return;
		}
	}
}

void PlayerKicking::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		player.SetDirection(EntityDirection::Left);
		player.SetVelocityX(-MOVING_HOR);
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player.SetDirection(EntityDirection::Right);
		player.SetVelocityX(MOVING_HOR);
	}
}

void PlayerKicking::OnKeyDown(Player& player, BYTE code)
{

}

void PlayerKicking::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_KEY_JUMP)
		isJumpReleased = true;
	else if (code == VK_RIGHT || code == VK_LEFT)
		player.SetVelocityX(.0f);
}

void PlayerKicking::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerKicking::GetState()
{
	return EPlayerState::Kicking;
}