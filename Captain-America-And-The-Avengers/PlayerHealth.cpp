#include "pch.h"
#include "PlayerHealth.h"

int PlayerHealth::Subtract(int dh)
{
	assert(dh > 0);
	Set(max(0, health - dh));
	return health;
}

int PlayerHealth::Add(int dh)
{
	assert(dh > 0);
	Set(min(12, health + dh));
	return health;
}

void PlayerHealth::Set(int h)
{
	assert(h >= 0 && h <= 12);
	health = h;
}

void PlayerHealth::Draw() const
{
	if (health < 0 || health > 12) ThrowGameException("Player health is exceed");

	if (health > 0)
	{
		if (health <= 2) {
			static int nRenderFrame = 0;
			if (++nRenderFrame % 4)
			{
				mAni->Draw(D3DXVECTOR3(15.0f, 20.0f, .0f), D3DXVECTOR2(.0f, .0f));
			}
		}
		else
		{
			mAni->Draw(D3DXVECTOR3(15.0f, 20.0f, .0f), D3DXVECTOR2(.0f, .0f));
		}
	}
	if (health > 4)
	{
		mAni->Draw(D3DXVECTOR3(15.0f, 28.0f, .0f), D3DXVECTOR2(.0f, .0f));
	}
	if (health > 8)
	{
		mAni->Draw(D3DXVECTOR3(15.0f, 36.0f, .0f), D3DXVECTOR2(.0f, .0f));
	}
}