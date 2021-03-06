#include "pch.h"
#include "SceneManager.h"
#include "Item.h"

AnimationScript* Item::mAniScript = nullptr;
Sprite* Item::mSprite = nullptr;
Animation* Item::mAniFivePoint = nullptr;
Animation* Item::mAniHeartEnergy = nullptr;
Animation* Item::mAniKeyCrystal = nullptr;
Animation* Item::mAniOneUp = nullptr;
Animation* Item::mAniPowerStone = nullptr;

Item::Item(ItemType type, D3DXVECTOR3 position)
{
	SetVelocityY(100.0f);
	mPosition = position;
	SetType(type);
	mPosition.x += 8 - mWidth / 2;
}

void Item::Update(float deltaTime)
{
	if (!isOnGround)
	{
		this->deltaTime = deltaTime;

		std::vector<CollisionEvent*> cEvent;
		std::set<Entity*> entities;
		SceneManager::GetInstance().GetScene()->GetGrid()->GetEntities(
			SceneManager::GetInstance().GetScene()->GetCamera()->GetBound(),
			entities);
		this->CalcCollision(
			&entities,
			cEvent);
		for (CollisionEvent* ce : cEvent)
		{
			if (ce->entity->GetCollidableObjectType() == EPlatform
				|| ce->entity->GetCollidableObjectType() == EWater
				)
			{
				if (ce->ny == -1.0f)
				{
					isOnGround = true;
					SetPositionY(ce->entity->GetPosition().y - mHeight);
					SetVelocityY(.0f);
					break;
				}
			}
		}
	}
	AddPositionY(mVelocityY * deltaTime);
	mCurrentAni->Update(deltaTime);
}

void Item::Draw(D3DXVECTOR2 trans)
{
	mCurrentAni->Draw(mPosition, trans);
	this->RenderBoundingBox(trans);
}

void Item::Consume(Player& player)
{
	SoundType sound = SoundType::ItemNormal;
	if (mType == ItemType::KeyCrystal) 
	{
		sound = SoundType::ItemKeyKrystal;
		player.canTransport = true;
	}
	else if (mType == ItemType::HeartEnergy)
	{
		sound = SoundType::ItemEnery;
		player.GetHealth().Add(1);
	}
	SoundManager::GetInstance().CPlaySound(sound);

	mState = 1; // Set to pending delete
}

RECT Item::GetBoundingBox()
{
	RECT rect;
	rect.left = mPosition.x;
	rect.top = mPosition.y;
	rect.bottom = rect.top + mHeight;
	rect.right = rect.left + mWidth;
	return rect;
}

CollidableObjectType Item::GetCollidableObjectType()
{
	return CollidableObjectType::EItem;
}

void Item::SetType(ItemType type)
{
	mType = type;
	switch (mType)
	{
	case PowerStone:	mCurrentAni = mAniPowerStone; break;
	case KeyCrystal:	mCurrentAni = mAniKeyCrystal; break;
	case FivePoint:		mCurrentAni = mAniFivePoint; break;
	case HeartEnergy:	mCurrentAni = mAniHeartEnergy; break;
	case OneUp:			mCurrentAni = mAniOneUp; break;
	}
	mHeight = mCurrentAni->GetHeight();
	mWidth = mCurrentAni->GetWidth();
}

ItemType Item::GetType()
{
	return mType;
}

void Item::LoadAnimation()
{
	mAniScript = new AnimationScript("Resources\\Sprites\\Item\\Item.xml");
	mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\Captain America.png");
	mAniFivePoint = new Animation(Item::mSprite, Item::mAniScript->GetRectList("FivePoint", "0"));
	mAniHeartEnergy = new Animation(Item::mSprite, Item::mAniScript->GetRectList("HeartEnergy", "0"));
	mAniKeyCrystal = new Animation(Item::mSprite, Item::mAniScript->GetRectList("KeyCrystal", "0"), 0.1f);
	mAniOneUp = new Animation(Item::mSprite, Item::mAniScript->GetRectList("OneUp", "0"));
	mAniPowerStone = new Animation(Item::mSprite, Item::mAniScript->GetRectList("PowerStone", "0"), 0.1f);

}
