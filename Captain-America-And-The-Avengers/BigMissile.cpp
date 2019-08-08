#include "pch.h"
#include "BigMissile.h"
#include "SceneManager.h"

Sprite* BigMissile::mSprite = NULL;
AnimationScript* BigMissile::mAniScripts = NULL;
Animation* BigMissile::mAniTop = NULL;
Animation* BigMissile::mAniTopLeft = NULL;
Animation* BigMissile::mAniBottomLeft = NULL;
Animation* BigMissile::mAniLeft = NULL;
Animation* BigMissile::mAniBottom = NULL;


BigMissile::BigMissile(D3DXVECTOR3 position, Player* player)
{
	mPlayer = player;

	LoadAnimations();
	mPosition = position;
	orginalPos = position;
	mState = 0;

	if (GeoUtils::IsIntersect(GetBoundingBox(), SceneManager::GetInstance().GetScene()->GetCamera()->GetBound())) {
		SoundManager::GetInstance().CPlaySound(SoundType::BeAttack);
	}
}

BigMissile::~BigMissile()
{
}

void BigMissile::LoadAnimations()
{
	if (mSprite == nullptr)
	{
		mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Rocket.png");
		mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\MissileOfFlyEnemy.xml");

		mAniTop = new Animation(mSprite, mAniScripts->GetRectList("Top", "0"), 0.1F);
		mAniTopLeft = new Animation(mSprite, mAniScripts->GetRectList("TopLeft", "0"), 0.1F);
		mAniLeft = new Animation(mSprite, mAniScripts->GetRectList("Left", "0"), 0.1F);
		mAniBottomLeft = new Animation(mSprite, mAniScripts->GetRectList("BottomLeft", "0"), 0.1F);
		mAniBottom = new Animation(mSprite, mAniScripts->GetRectList("Bottom", "0"), 0.1F);
	}

	mCurrentAni = mAniTop;
}

void BigMissile::Update(float deltaTime)
{
	if (abs(orginalPos.x - mPosition.x) >= 200.0f) // Max length
	{
		mState = 1; // Pending destroy
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(new Explosion(this));
	}

	if (mState != 1)
	{
		auto grid = SceneManager::GetInstance().GetScene()->GetGrid();
		for (auto entity : grid->mTemp)
		{
			if (GeoUtils::IsIntersect(GetBoundingBox(), entity->GetBoundingBox()))
			{
				if (entity->GetCollidableObjectType() == EPlatform)
				{
					grid->Add(new Explosion(this));
					mState = 1;
				}
			}
		}
	}

	CalcVelByPlayerPos(mPlayer->GetPosition().x + mPlayer->GetWidth() / 2, mPlayer->GetPosition().y + mPlayer->GetHeight() / 2);
	SetAnimationByVel();
	Entity::Update(deltaTime);
}

void BigMissile::SetAnimationByVel()
{
	float x = mVelocityX;
	float y = mVelocityY;
	if (x >= 0 && y >= 0) {
		mDirection = (EntityDirection)1;
		if (std::abs(x) > std::abs(y) / 2 && std::abs(x) < std::abs(y) * 2)
		{
			mCurrentAni = mAniBottomLeft;
		}
		else if (std::abs(x) > std::abs(y) * 2)
		{
			mCurrentAni = mAniLeft;
		}
		else
		{
			mCurrentAni = mAniBottom;
		}
	}
	else if (x < 0 && y >= 0) {
		mDirection = (EntityDirection)-1;
		if (std::abs(x) > std::abs(y) / 2 && std::abs(x) < std::abs(y) * 2)
		{
			mCurrentAni = mAniBottomLeft;
		}
		else if (std::abs(x) > std::abs(y) * 2)
		{
			mCurrentAni = mAniLeft;
		}
		else
		{
			mCurrentAni = mAniBottom;
		}
	}
	else if (x >= 0 && y < 0) {
		mDirection = (EntityDirection)1;
		if (std::abs(x) > std::abs(y) / 2 && std::abs(x) < std::abs(y) * 2)
		{
			mCurrentAni = mAniTopLeft;
		}
		else if (std::abs(x) > std::abs(y) * 2)
		{
			mCurrentAni = mAniLeft;
		}
		else
		{
			mCurrentAni = mAniTop;
		}
	}
	else if (x < 0 && y < 0) {
		mDirection = (EntityDirection)-1;
		if (std::abs(x) > std::abs(y) / 2 && std::abs(x) < std::abs(y) * 2)
		{
			mCurrentAni = mAniTopLeft;
		}
		else if (std::abs(x) > std::abs(y) * 2)
		{
			mCurrentAni = mAniLeft;
		}
		else
		{
			mCurrentAni = mAniTop;
		}
	}
}

void BigMissile::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->SetFlippedHorizontally(mVelocityX > 0.0f);
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0, 0));
	}
}

int BigMissile::GetState()
{
	return mState;
}

void BigMissile::OnSetPosition()
{
	Bullet::OnSetPosition();
}

BulletType BigMissile::GetBulletType()
{
	return BulletType::BBigMissile;
}

void BigMissile::HitShield()
{
	mIsHitShield = true;
}

void BigMissile::CalcLineEqual(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float& a, float& b)
{
	a = (p2.y - p1.y) / (p2.x - p1.x);
	b = (p2.x * p1.y - p1.x * p2.y) / (p2.x - p1.x);
}

void BigMissile::CalcVelByPlayerPos(float x, float y)
{
	float dx = x - mPosition.x;
	float dy = y - mPosition.y;

	if (dx < 0 && dy < 0) {
		if (mVelocityX < 0 && mVelocityY < 0)
		{
			if (abs(dx) / abs(dy) < abs(mVelocityX) / abs(mVelocityY))
			{
				mVelocityX -= MIN_CHANGE_VELX_PER_FRAME;
			}
			else
			{
				mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
			}
		}
		else if (mVelocityX >= 0 && mVelocityY < 0) {
			mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
		}
		else if (mVelocityX < 0 && mVelocityY >= 0) {
			mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
		}
		else if (mVelocityX >= 0 && mVelocityY >= 0) {
			SceneManager::GetInstance().GetScene()->GetGrid()->Add(new Explosion(this));
			mState = 1;
			SetVelocityX(.0f);
			SetVelocityY(.0f);
			return;
		}
	}
	else if (dx >= 0 && dy < 0) {
		if (mVelocityX < 0 && mVelocityY < 0)
		{
			mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
		}
		else if (mVelocityX >= 0 && mVelocityY < 0) {
			if (abs(dx) / abs(dy) < abs(mVelocityX) / abs(mVelocityY))
			{
				mVelocityX -= MIN_CHANGE_VELX_PER_FRAME;
			}
			else
			{
				mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
			}
		}
		else if (mVelocityX < 0 && mVelocityY >= 0) {
			SceneManager::GetInstance().GetScene()->GetGrid()->Add(new Explosion(this));
			mState = 1;
			SetVelocityX(.0f);
			SetVelocityY(.0f);
			return;
		}
		else if (mVelocityX >= 0 && mVelocityY >= 0) {
			mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
		}
	}
	else if (dx < 0 && dy >= 0) {
		if (mVelocityX < 0 && mVelocityY < 0)
		{
			mVelocityX -= MIN_CHANGE_VELX_PER_FRAME;
		}
		else if (mVelocityX >= 0 && mVelocityY < 0) {
			SceneManager::GetInstance().GetScene()->GetGrid()->Add(new Explosion(this));
			mState = 1;
			SetVelocityX(.0f);
			SetVelocityY(.0f);
			return;
		}
		else if (mVelocityX < 0 && mVelocityY >= 0) {
			if (dy == 0 && mVelocityY == 0) { return; }
			else if (dy == 0 && mVelocityY != 0) {
				mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
			}
			else if (dy != 0 && mVelocityY == 0)
			{
				mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
			}
			else if (abs(dx) / abs(dy) < abs(mVelocityX) / abs(mVelocityY))
			{
				mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
			}
			else
			{
				mVelocityX -= MIN_CHANGE_VELX_PER_FRAME;
			}
		}
		else if (mVelocityX >= 0 && mVelocityY >= 0) {
			mVelocityX -= MIN_CHANGE_VELX_PER_FRAME;
		}
	}
	else if (dx >= 0 && dy >= 0) {
		if (mVelocityX < 0 && mVelocityY < 0)
		{
			SceneManager::GetInstance().GetScene()->GetGrid()->Add(new Explosion(this));
			mState = 1;
			SetVelocityX(.0f);
			SetVelocityY(.0f);
			return;
		}
		else if (mVelocityX >= 0 && mVelocityY < 0) {
			mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
		}
		else if (mVelocityX < 0 && mVelocityY >= 0) {
			mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
		}
		else if (mVelocityX >= 0 && mVelocityY >= 0) {
			if (dy == 0 && mVelocityY == 0) { return; }
			else if (dy == 0 && mVelocityY != 0) {
				mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
			}
			else if (dy != 0 && mVelocityY == 0)
			{
				mVelocityX -= MIN_CHANGE_VELX_PER_FRAME;
			}
			else if (abs(dx) / abs(dy) < abs(mVelocityX) / abs(mVelocityY))
			{
				mVelocityX -= MIN_CHANGE_VELX_PER_FRAME;
			}
			else
			{
				mVelocityX += MIN_CHANGE_VELX_PER_FRAME;
			}
		}
	}
	UpdateVelYbyVelX(mVelocityX);

}

void BigMissile::UpdateVelYbyVelX(float velx)
{
	if (abs(velx) > BULLET_MOVING)
	{
		mVelocityX = velx / abs(velx) * BULLET_MOVING;
		mVelocityY = 0;
	}
	else
	{
		mVelocityY = sqrt(BULLET_MOVING * BULLET_MOVING - velx * velx);
	}
}