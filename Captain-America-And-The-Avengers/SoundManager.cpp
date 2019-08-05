#include "pch.h"
#include "SoundManager.h"
#include "Window.h"

SoundManager& SoundManager::GetInstance()
{
	static SoundManager soundManager;
	return soundManager;
}
SoundManager::SoundManager() : ISingleton(NULL) 
{
	dSound = 0;
	dSound = new CSoundManager();
	HRESULT hr;
	hr = dSound->Initialize(Window::GetInstance().GetHWnd(), DSSCL_PRIORITY);
	if (hr != DS_OK)
		return;
	// Set stereo, 22kHz, 16-bit output. 
	hr = dSound->SetPrimaryBufferFormat(2, 22050, 16);
	if (hr != DS_OK)
		return;	
	// Load the wave file into a DirectSound buffer 
	AddSound(SoundType::Ambush, L"Resources\\Sound\\Ambush.wav");
	AddSound(SoundType::BeAttack, L"Resources\\Sound\\BeAttack.wav");
	AddSound(SoundType::BossBattle, L"Resources\\Sound\\BossBattle.wav");
	AddSound(SoundType::BossShootBigBullets, L"Resources\\Sound\\BossShootBigBullets.wav");
	AddSound(SoundType::BossShootSmallBullets, L"Resources\\Sound\\BossShootSmallBullets.wav");
	AddSound(SoundType::Death, L"Resources\\Sound\\Death.wav");
	AddSound(SoundType::Explosive, L"Resources\\Sound\\Explosive.wav");
	AddSound(SoundType::FallingWater, L"Resources\\Sound\\FallingWater.wav");
	AddSound(SoundType::Hit, L"Resources\\Sound\\Hit.wav");
	AddSound(SoundType::ItemEnery, L"Resources\\Sound\\ItemEnergy.wav");
	AddSound(SoundType::ItemKeyKrystal, L"Resources\\Sound\\ItemKeyKrystal.wav");
	AddSound(SoundType::ItemNormal, L"Resources\\Sound\\ItemNormal.wav");
	AddSound(SoundType::RedAlert, L"Resources\\Sound\\RedAlert.wav");
	AddSound(SoundType::SmallBulletsHitShields, L"Resources\\Sound\\SmallBulletsHitShields.wav");
	AddSound(SoundType::SurfingSound, L"Resources\\Sound\\SurfingSound.wav");
	AddSound(SoundType::ThemeOfCaptainAmerica, L"Resources\\Sound\\ThemeOfCaptainAmerica.wav");
	AddSound(SoundType::ThrowShield, L"Resources\\Sound\\ThrowShield.wav");
	AddSound(SoundType::TouchTheGround, L"Resources\\Sound\\TouchTheGround.wav");
	AddSound(SoundType::JumpTurn, L"Resources\\Sound\\Turn.wav");
}
void SoundManager::AddSound(SoundType soundType, const wchar_t* filePath)
{
	CSound* pSound = 0;
	HRESULT hr = dSound->Create(&pSound, const_cast<LPTSTR>(filePath));
	if (hr != DS_OK)
	{
		return;
	}
	listSound[soundType] = pSound;
}
void SoundManager::CPlaySound(SoundType soundType)
{
	listSound[soundType]->Play();
}

void SoundManager::CLoopSound(SoundType soundType)
{
	listSound[soundType]->Play(0, DSBPLAY_LOOPING);
}
void SoundManager::CStopsound(SoundType soundType)
{
	listSound[soundType]->Stop();
}

void SoundManager::CResetSound(SoundType soundType)
{
	listSound[soundType]->Reset();
}
