#pragma once

enum GroundType
{
	EGroundNormal,
	EGroundHard,
	EGroundWater
};

enum EnemyType
{
	EBatEnemy,
	EFlyEnemy,
	ERunEnemy,
	EGunEnemy,
	EGunStockEnemy,
	EMissileEnemy,
	EDefaultEnemy,
	EBossCharleston
};

enum EntityDirection
{
	Left = -1,
	Right = 1
};

enum CollidableObjectType
{
	EPlayer,
	EEnemy,
	EWeapon,
	EPlatform,
	EWater,
	EDefault,
	EBullet,
	ECapsule,
	EItem,
	EExplosion,
	ETransportArea,
	EDoor,
	EButton
};

enum ItemType
{
	PowerStone,
	KeyCrystal,
	FivePoint,
	HeartEnergy,
	OneUp
};

enum MapID
{
	Charleston,
	CharlestonBoss,
	Pittsburgh,
	PittsburghExtra1,
	PittsburghExtra2,
	RedAlertBoss
};