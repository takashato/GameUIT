#pragma once

enum GroundType
{
	EGroundNormal,
	EGroundHard
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
	EItem
};

enum ItemType
{
	PowerStone,
	KeyCrystal,
	FivePoint,
	HeartEnergy,
	OneUp
};