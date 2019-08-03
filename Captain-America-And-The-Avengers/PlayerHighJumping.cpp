#include "pch.h"
#include "PlayerHighJumping.h"
#include "Player.h"

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
	else counterTimeFlip += deltaTime;

	if (timeUp < TIME_KEEP_SPIN) {
		timeUp += deltaTime;
		player.SetVelocityY(-SPIN_SPEED_VER);
	}
	else
	{
		if (timeDown < TIME_KEEP_SPIN)
		{
			timeDown += deltaTime;
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
		player.SetVelocityX(-SPIN_SPEED_HOR);
	}
	if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player.SetVelocityX(SPIN_SPEED_HOR);
	}
	if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		if (timeUp >= TIME_KEEP_SPIN && timeDown >= TIME_KEEP_SPIN)
		{
			//cap.SetState(State::Captain_CoverLow);
			return;
		}
	}
}

void PlayerHighJumping::OnKeyDown(Player& player, BYTE code)
{
	//if (!isKicked) {
	//	if (keyCode == setting.Get(KeyControls::Attack))
	//	{
	//		isKicked = true;
	//		cap.SetState(State::Captain_Kicking);
	//		return;
	//	}
	//}
}

void PlayerHighJumping::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_LEFT || code == VK_RIGHT)
		player.SetVelocityX(.0f);
}

void PlayerHighJumping::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerHighJumping::GetState()
{
	return EPlayerState::HighJumping;
}
