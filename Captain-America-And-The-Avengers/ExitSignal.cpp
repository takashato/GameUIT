#include "pch.h"
#include "ExitSignal.h"

void ExitSignal::Draw() const
{
	if (isCollectKeyCrystal)
	{
		static int nRenderFrame = 0;
		if (++nRenderFrame % 50 < 25)
		{
			mAni->Draw(D3DXVECTOR3(40.0f, 20.0f, .0f), D3DXVECTOR2(.0f, .0f));
		}
	}
}

void ExitSignal::CollectKeyCrystal(bool isCollected)
{
	isCollectKeyCrystal = isCollected;
}