#include "pch.h"
#include "Entity.h"

Entity::Entity()
{

	mDirection = Right;
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	this->AddPositionX(deltaTime * mVelocityX);
	this->AddPositionY(deltaTime * mVelocityY);
}

void Entity::Draw(D3DXVECTOR2 trans)
{
}

D3DXVECTOR3 Entity::GetPosition()
{
	return mPosition;
}

void Entity::SetPosition(D3DXVECTOR3 position)
{
	mPosition = position;
	OnSetPosition();
}

void Entity::SetPositionX(float value)
{
	mPosition.x = value;
	SetPosition(mPosition);
}

void Entity::SetPositionY(float value)
{
	mPosition.y = value;
	SetPosition(mPosition);
}

void Entity::AddPosition(D3DXVECTOR2 vector)
{
	SetPosition(mPosition + D3DXVECTOR3(vector.x, vector.y, 0.0F));
}

void Entity::AddPositionX(float value)
{
	mPosition.x += value;
	SetPosition(mPosition);
}

void Entity::AddPositionY(float value)
{
	mPosition.y += value;
	SetPosition(mPosition);
}

float Entity::GetVelocityX()
{
	return mVelocityX;
}

float Entity::GetVelocityY()
{
	return mVelocityY;
}

void Entity::SetVelocityX(float velocity)
{
	mVelocityX = velocity;
}

void Entity::SetVelocityY(float velocity)
{
	mVelocityY = velocity;
}

void Entity::AddVelocityX(float deltaVelocity)
{
	mVelocityX += deltaVelocity;
}

void Entity::AddVelocityY(float deltaVelocity)
{
	mVelocityY += deltaVelocity;
}

float Entity::GetWidth()
{
	return mWidth;
}

void Entity::SetWidth(float width)
{
	mWidth = width;
}

float Entity::GetHeight()
{
	return mHeight;
}

void Entity::SetHeight(float height)
{
	mHeight = height;
}

EntityDirection Entity::GetDirection()
{
	return mDirection;
}

void Entity::SetDirection(EntityDirection direction)
{
	mDirection = direction;
}

void Entity::OnSetPosition()
{

}

D3DXVECTOR3 Entity::GetCenterPoint()
{
	return GeoUtils::GetRectCenter(GetBoundingBox());
}

CollisionEvent* Entity::SweptAABBEx(Entity* other)
{
	float t, nx, ny;

	RECT otherBB = other->GetBoundingBox(); // static
	RECT thisBB = this->GetBoundingBox();

	float dx = (this->GetVelocityX() - other->GetVelocityX()) * deltaTime;
	float dy = (this->GetVelocityY() - other->GetVelocityY()) * deltaTime;

	CollisionEvent::SweptAABB(
		(float)thisBB.left, (float)thisBB.top, (float)thisBB.right, (float)thisBB.bottom,
		dx, dy,
		(float)otherBB.left, (float)otherBB.top, (float)otherBB.right, (float)otherBB.bottom,
		t, nx, ny
	);

	CollisionEvent* e = new CollisionEvent(t, nx, ny, other);
	return e;
}

void Entity::CalcCollision(std::set<Entity*> *entities, std::vector<CollisionEvent*>& cEvent)
{
	cEvent.clear();

	for (Entity* entity: *entities)
	{
		if (entity == this) continue;

		CollisionEvent* e = SweptAABBEx(entity);

		if (e->t >= 0 && e->t <= 1.0f)
			cEvent.push_back(e);
		else
			delete e;
	}

	std::sort(cEvent.begin(), cEvent.end(), CollisionEvent::compare);
}

bool Entity::OnCollision(std::vector<CollisionEvent*>& cEvent)
{
	return true;
}

void Entity::RenderBoundingBox(D3DXVECTOR2 transform)
{
	if (!shouldRenderBoundingBox) return;

	RECT bb = GetBoundingBox();
	std::vector<D3DXVECTOR2> vertexList;
	vertexList.push_back(D3DXVECTOR2(bb.left, bb.top));
	vertexList.push_back(D3DXVECTOR2(bb.right, bb.top));
	vertexList.push_back(D3DXVECTOR2(bb.right, bb.bottom));
	vertexList.push_back(D3DXVECTOR2(bb.left, bb.bottom));
	vertexList.push_back(D3DXVECTOR2(bb.left, bb.top));

	ExtraDrawer::GetInstance().DrawTransform(vertexList, transform);
}

void Entity::SetGridNode(GridNode* gridNode)
{
	mGridNode = gridNode;
}

GridNode* Entity::GetGridNode()
{
	return mGridNode;
}

Sprite* Entity::mSpriteBB = NULL;
bool Entity::shouldRenderBoundingBox = false;