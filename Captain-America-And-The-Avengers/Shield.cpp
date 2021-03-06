#include "pch.h"
#include "Shield.h"
#include "GunStock.h"
#include "CharlestonBossScene.h"
#include "SceneManager.h"

Shield::Shield(Player* player) : Weapon()
{
	mPlayer = player;
	LoadAnimations();
	SetState(EShieldIdle);
}

Shield::~Shield()
{
}

void Shield::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\Captain America.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Players\\Cap\\Shield.xml");

	mAniIdle = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.1F);
	mAniHighShield = new Animation(mSprite, mAniScripts->GetRectList("HighShield", "0"), 0.1F);
	mAniRunShield = new Animation(mSprite, mAniScripts->GetRectList("RunShield", "0"), 0.1F);
	mAniSitShield = new Animation(mSprite, mAniScripts->GetRectList("SitShield", "0"), 0.1F);
}

void Shield::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	D3DXVECTOR3 playerPosition = mPlayer->GetPosition();
	D3DXVECTOR3 shieldPosition;
	shieldPosition.z = 0.f;

	if (mPlayer->GetState()->GetState() == Kicking)
		SetDirection(mPlayer->GetDirection() == Left ? Right : Left);
	else
		SetDirection(mPlayer->GetDirection());

	mCurrentAni->SetFlippedHorizontally(mDirection == Right);

	mCounter += deltaTime;

	D3DXVECTOR3 returnPos = GetReturnPoint();

	if (!isThrown)
	{
		SetState(GetStateByPlayerState());
		SetPosition(returnPos);
	}
	else
	{
		//float acc = 2222.2125f;
		float velocity = 300.0f;

		if (mState != EShieldHigh) SetState(EShieldHigh);

		D3DXVECTOR3 oldPosition = mPosition;

		if (isReturning)
		{
			SetVelocityX((flyDirection ? -1 : 1) * velocity);
		}
		else
		{
			if (abs(throwPos.x - mPosition.x) >= 100.0f && !isReturning)
			{
				isReturning = true;
				SetVelocityX((flyDirection ? -1 : 1) * velocity);
			}
			else
			{
				SetVelocityX(-(flyDirection ? -1 : 1) * velocity);
			}
		}


		Entity::Update(deltaTime); // Update velocity

		if (flyDirection && GetVelocityX() <= 0.0f || !flyDirection && GetVelocityX() >= 0.0f)
		{
			SetPositionY(CalYOfLinearEquation(oldPosition.x, oldPosition.y, returnPos.x, returnPos.y, mPosition.x));
		}

		if (flyDirection && mPosition.x <= mPlayer->GetPosition().x || !flyDirection && mPosition.x >= mPlayer->GetPosition().x)
		{
			isThrown = false;
			isReturning = false;
			SetPosition(returnPos);
			SetVelocityX(0.0f);
			SetVelocityY(0.0f);
		}
	}
}

float Shield::CalYOfLinearEquation(float x1, float y1, float x2, float y2, float posX)
{
	float a = (y1 - y2) / (x1 - x2);
	float b = y1 - a * x1;

	return a*posX + b;
}

float Shield::GetWidth()
{
	return mWidth;
}

float Shield::GetHeight()
{
	return mHeight;
}

D3DXVECTOR3 Shield::GetReturnPoint()
{
	D3DXVECTOR3 shieldPosition(.0f, .0f, .0f);
	D3DXVECTOR3 playerPosition = mPlayer->GetPosition();
	bool isFacedRight = mPlayer->GetDirection() == Right;

#pragma region SET_RETURN_POINT_BY_PLAYER_POS_AND_STATE
	switch (mPlayer->GetState()->GetState())
	{
	default:
	case InvincibleStand:
	case Standing:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x + mPlayer->GetWidth() - 4;
			shieldPosition.y = playerPosition.y + 8;
		}
		else
		{
			shieldPosition.x = playerPosition.x - 3;
			shieldPosition.y = playerPosition.y + 8;
		}
		break;
	case Running:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x + mPlayer->GetWidth() - 4;
			shieldPosition.y = playerPosition.y + 4;
		}
		else
		{
			shieldPosition.x = playerPosition.x - 3;
			shieldPosition.y = playerPosition.y + 4;
		}
		break;
	case Falling:
	case Jumping:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x + 2;
			shieldPosition.y = playerPosition.y + 2;
		}
		else
		{
			shieldPosition.x = playerPosition.x + 5;
			shieldPosition.y = playerPosition.y + 2;
		}
		break;
	case HighShielding:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x + 6;
			shieldPosition.y = playerPosition.y - 1;
		}
		else
		{
			shieldPosition.x = playerPosition.x;
			shieldPosition.y = playerPosition.y - 1;
		}
		break;
	case Cling:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x - 4;
			shieldPosition.y = playerPosition.y + 20;
		}
		else
		{
			shieldPosition.x = playerPosition.x + 8;
			shieldPosition.y = playerPosition.y + 20;
		}
		break;
	case Kicking:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x - 2;
			shieldPosition.y = playerPosition.y + 5;
		}
		else
		{
			shieldPosition.x = playerPosition.x + mPlayer->GetWidth() - 5;
			shieldPosition.y = playerPosition.y + 5;
		}
		break;
	case Sitting:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x + mPlayer->GetWidth() - 4;
			shieldPosition.y = playerPosition.y + 8;
		}
		else
		{
			shieldPosition.x = playerPosition.x - 3;
			shieldPosition.y = playerPosition.y + 8;
		}
		break;
	case LowPunching:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x + 8;
			shieldPosition.y = playerPosition.y + 6;
		}
		else
		{
			shieldPosition.x = playerPosition.x + 14;
			shieldPosition.y = playerPosition.y + 6;
		}
		break;
	case SittingOnShield:
		if (isFacedRight)
		{
			shieldPosition.x = playerPosition.x - 2;
			shieldPosition.y = playerPosition.y + mPlayer->GetHeight() - 2;
		}
		else
		{
			shieldPosition.x = playerPosition.x;
			shieldPosition.y = playerPosition.y + mPlayer->GetHeight() - 2;
		}
		break;
	case Surfing:
		if (isFacedRight)
		{
			if (mPlayer->mAniSurfing->GetCurrentFrame() == 0)
			{
				shieldPosition.x = playerPosition.x + mPlayer->GetWidth() - 8;
				shieldPosition.y = playerPosition.y;
			}
			else
			{
				shieldPosition.x = playerPosition.x + mPlayer->GetWidth() - 3;
				shieldPosition.y = playerPosition.y;
			}
		}
		else
		{
			if (mPlayer->mAniSurfing->GetCurrentFrame() == 0)
			{
				shieldPosition.x = playerPosition.x + 1;
				shieldPosition.y = playerPosition.y;
			}
			else
			{
				shieldPosition.x = playerPosition.x - 4;
				shieldPosition.y = playerPosition.y;
			}
		}
		break;
	case ThrowingShield:
		if (isFacedRight)
		{
			if (mPlayer->mAniThrowingShield->GetCurrentFrame() == 0)
			{
				shieldPosition.x = playerPosition.x - 14;
				shieldPosition.y = playerPosition.y - 2;
			}
			else
			{
				shieldPosition.x = playerPosition.x + mPlayer->GetWidth() - 8;
				shieldPosition.y = playerPosition.y + 9;
			}
		}
		else
		{
			if (mPlayer->mAniThrowingShield->GetCurrentFrame() == 0)
			{
				shieldPosition.x = playerPosition.x + mPlayer->GetWidth() - 6;
				shieldPosition.y = playerPosition.y - 2;
			}
			else
			{
				shieldPosition.x = playerPosition.x - 16;
				shieldPosition.y = playerPosition.y + 9;
			}
		}
		break;
	}
#pragma endregion
	
	return shieldPosition;
}

ShieldState Shield::GetStateByPlayerState()
{
	switch (mPlayer->GetState()->GetState())
	{
	case LowPunching:
	case Falling:
	case Jumping:
	case Cling:
		return EShieldIdle;
	case HighShielding:
	case ThrowingShield:
		return EShieldHigh;
	case SittingOnShield:
		return EShieldSit;
	default:
		return EShieldRun;
	}
}

bool Shield::IsThrown()
{
	return isThrown;
}

bool Shield::OnCollision(std::vector<CollisionEvent*>& cEvent)
{
	for (CollisionEvent* ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EEnemy)
		{
			auto enemy = ((Enemy*)ce->entity);
			if (enemy->GetEnemyType() == EGunStockEnemy)
			{
				if(((GunStock*)enemy)->GetState() != GUNSTOCK_ROTATING_STATE)
					((GunStock*)enemy)->BeAttacked();
			}
			else if (enemy->GetCollidableObjectType() == EBatEnemy)
			{
				if (((Bat*)enemy)->GetState() != BAT_FLYWITHSHOCK_STATE)
					((Bat*)enemy)->TakeDamage(this, 2);
			}
			else if (enemy->GetEnemyType() == EnemyType::EBossCharleston)
				enemy->TakeDamage(mPlayer, 1);
			else
				enemy->TakeDamage(mPlayer, 2);
		}
		else if (ce->entity->GetCollidableObjectType() == EBullet)
		{
			if (mState == ShieldState::EShieldRun && (
				( ((Bullet*)ce->entity)->GetBulletType() == BNormalBullet)
				|| ((Bullet*)ce->entity)->GetBulletType() == BulletType::BBossNormalBullet))
			{
				if (GetDirection() == Right && ce->nx == -1.0f || GetDirection() == Left && ce->nx == 1.0f)
				{
					((Bullet*)ce->entity)->HitShield();
					SoundManager::GetInstance().CResetSound(SmallBulletsHitShields);
					SoundManager::GetInstance().CPlaySound(SmallBulletsHitShields);
				}
			}
		}
		else if (ce->entity->GetCollidableObjectType() == ECapsule)
		{
			((Capsule*)ce->entity)->Drop();
		}
		else if (mState == ShieldState::EShieldSit && ce->entity->GetCollidableObjectType() == EPlatform)
		{
			SoundManager::GetInstance().CResetSound(SmallBulletsHitShields);
			SoundManager::GetInstance().CPlaySound(SmallBulletsHitShields);
		}
		else if (ce->entity->GetCollidableObjectType() == EButton)
		{
			if (auto scene = dynamic_cast<CharlestonBossScene*>(SceneManager::GetInstance().GetScene()))
			{
				scene->ToggleLight();
			}
			if (auto scene = dynamic_cast<PittsburghScene*>(SceneManager::GetInstance().GetScene()))
			{
				scene->ToggleLight();
			}
		}
		else if (ce->entity->GetCollidableObjectType() == EDynamite)
		{
			auto dynamite = (Dynamite*)ce->entity;
			if (!dynamite->isThrown) {
				dynamite->boss->TakeDamageBossRedAlertNotCrazy(this);
				dynamite->pendingDelete = true;
				SceneManager::GetInstance().GetScene()->GetGrid()->Add(
					new Explosion(dynamite)
				);
			}
		}
		delete ce;
	}
	return true;
}

bool Shield::CheckAABB(std::set<Entity*> &entities)
{
	auto pbb = GetBoundingBox();
	for (auto entity : entities)
	{
		auto ebb = entity->GetBoundingBox();
		if (GeoUtils::IsIntersect(pbb, ebb))
		{
			//if (auto enemy = dynamic_cast<Enemy*>(entity))
			//{
			//	EnemyType type = enemy->GetEnemyType();
			//	if(mState == ShieldState::EShieldHigh || mState == ShieldState::EShieldSit)
			//		enemy->TakeDamage(this, 2);
			//	else
			//		enemy->TakeDamage(this, 1);
			//}
		}
	}
	return true;
}

void Shield::Draw(D3DXVECTOR2 transform)
{
	if ((mPlayer->GetState()->GetState() == EPlayerState::HighJumping
		|| mPlayer->GetState()->GetState() == EPlayerState::Swimming) && !IsThrown())
	{
		this->RenderBoundingBox(transform);
		return;
	}

	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0, 0));
	}

	if (!isThrown) SoundManager::GetInstance().CStopsound(ThrowShield);
}

ShieldState Shield::GetState()
{
	return mState;
}

void Shield::SetState(ShieldState state)
{
	mState = state;
	ChangeAnimationByState(mState);
	mHeight = mCurrentAni->GetHeight();
	mWidth = mCurrentAni->GetWidth();
}

void Shield::Throw()
{
	isThrown = true;
	isReturning = false;
	flyDirection = mPlayer->GetDirection() == Right;
	maxLengthFly = 100.0f;
	//SetVelocityX((flyDirection ? 1 : -1) * 666.66f);
	SetVelocityY(.0f);
	throwPos = GetReturnPoint();
	SoundManager::GetInstance().CResetSound(ThrowShield);
	SoundManager::GetInstance().CPlaySound(ThrowShield);
}

void Shield::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case EShieldIdle:
		mCurrentAni = mAniIdle;
		break;
	case EShieldHigh:
		mCurrentAni = mAniHighShield;
		break;
	case EShieldRun:
		mCurrentAni = mAniRunShield;
		break;
	case EShieldSit:
		mCurrentAni = mAniSitShield;
		break;
	}
}

void Shield::OnSetPosition()
{

}

RECT Shield::GetBoundingBox()
{
	if (mCurrentAni == nullptr) return RECT();

	RECT rect;
	rect.left = (long)mPosition.x;
	rect.top = (long)mPosition.y;
	rect.right = (long)(rect.left + GetWidth());
	rect.bottom = (long)(rect.top + GetHeight());

	return rect;
}