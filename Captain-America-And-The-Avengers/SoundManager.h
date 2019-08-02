#pragma once
#include "dsutil.h"
#include "dxutil.h"
//Sound 
enum SoundType
{
	Invalid = -1,
	Ambush = 0,
	BeAttack = 1,
	BossShootSmallBullets = 2,
	BossShootBigBullets = 3,
	BossBattle = 4,
	Hit = 5,
	SmallBulletsHitShields = 6,
	Death = 7,
	ItemEnery = 8,
	ItemNormal = 9,
	ItemKeyKrystal = 10,
	SurfingSound = 11,
	ThrowShield = 12,
	Explosive = 13,
	FallingWater = 14,
	RedAlert = 15,
	ThemeOfCaptainAmerica = 16,
	TouchTheGround = 17,
	JumpTurn = 18
};

class SoundManager : ISingleton
{
public:
	static SoundManager& GetInstance();

	void CPlaySound(SoundType soundType);
	void CLoopSound(SoundType soundType);
	void CStopsound(SoundType soundType);
	void CResetSound(SoundType soundType);

	void AddSound(SoundType soundType, const wchar_t* filePath);
private:
	CSoundManager *dSound;
	map <SoundType, CSound*> listSound;
	SoundManager();
};
