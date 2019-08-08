#include "pch.h"
#include "AnimationScript.h"
#include "SceneManager.h"
#include "Item.h"
#include "Capsule.h"

AnimationScript* Capsule::mAniScript = nullptr;
Sprite* Capsule::mSprite = nullptr;
Animation* Capsule::mAniNormal = nullptr;
Animation* Capsule::mAniInvoked = nullptr;

Capsule::Capsule(D3DXVECTOR3 position, std::vector<ItemType>& itemList)
{
	if (itemList.size() < 2)
	{
		ThrowGameException("Item List size must be larger than 2.");
	}
	mItemPrimary = itemList[0];
	mITemSecondary = itemList[1];
	mDroppedPrimary = false;

	mPosition = position;
	mWidth = 16;
	mHeight = 16;
	mCurrentAni = mAniNormal;
}

void Capsule::Update(float deltaTime)
{
	if (mIsJustDrop)
	{
		mCounter += deltaTime;
		if (mCounter >= DROP_INTERVAL)
		{
			mIsJustDrop = false;
			mCurrentAni = mAniNormal;
			mCounter = .0f;
		}
	}
}

void Capsule::Draw(D3DXVECTOR2 trans)
{
	if (auto scene = dynamic_cast<PittsburghScene*>(SceneManager::GetInstance().GetScene()))
	{
		if (!scene->isLightOn)
		{
			mCurrentAni->Draw(GetPosition(), trans, D3DCOLOR_RGBA(0, 0, 0, 255));
			this->RenderBoundingBox(trans);
		}
		else
		{
			mCurrentAni->Draw(mPosition, trans);
			this->RenderBoundingBox(trans);
		}
	}
	else if (auto scene = dynamic_cast<PittsburghExtra1Scene*>(SceneManager::GetInstance().GetScene()))
	{
		if (!scene->isLightOn)
		{
			mCurrentAni->Draw(GetPosition(), trans, D3DCOLOR_RGBA(0, 0, 0, 255));
			this->RenderBoundingBox(trans);
		}
		else
		{
			mCurrentAni->Draw(mPosition, trans);
			this->RenderBoundingBox(trans);
		}
	}
	else if (auto scene = dynamic_cast<PittsburghExtra2Scene*>(SceneManager::GetInstance().GetScene()))
	{
		if (!scene->isLightOn)
		{
			mCurrentAni->Draw(GetPosition(), trans, D3DCOLOR_RGBA(0, 0, 0, 255));
			this->RenderBoundingBox(trans);
		}
		else
		{
			mCurrentAni->Draw(mPosition, trans);
			this->RenderBoundingBox(trans);
		}
	}
	else
	{
		mCurrentAni->Draw(mPosition, trans);
		this->RenderBoundingBox(trans);
	}
}

void Capsule::Drop()
{
	if (!mIsJustDrop)
	{
		if (SceneManager::GetInstance().GetScene() != nullptr
			&& SceneManager::GetInstance().GetScene()->GetGrid() != nullptr)
		{ 
			Item* item;
			if (!mDroppedPrimary)
			{
				mDroppedPrimary = true;
				item = new Item(mItemPrimary, mPosition);
			}
			else
				item = new Item(mITemSecondary, mPosition);
			SceneManager::GetInstance().GetScene()->GetGrid()->Add(item);
		}
		mIsJustDrop = true;
		mCurrentAni = mAniInvoked;
	}
}

RECT Capsule::GetBoundingBox()
{
	RECT rect;
	rect.left = mPosition.x;
	rect.top = mPosition.y;
	rect.right = rect.left + mWidth;
	rect.bottom = rect.top + mHeight;
	return rect;
}

CollidableObjectType Capsule::GetCollidableObjectType()
{
	return CollidableObjectType::ECapsule;
}

void Capsule::LoadAnimation()
{
	mAniScript = new AnimationScript("Resources\\Sprites\\Item\\Capsule.xml");
	mSprite = new Sprite(L"Resources\\Sprites\\Item\\Capsule.png");
	mAniNormal = new Animation(mSprite, mAniScript->GetRectList("Capsule", "0"));
	mAniInvoked = new Animation(mSprite, mAniScript->GetRectList("Capsule", "1"));
}
