#include "pch.h"
#include "GridNode.h"

GridNode::GridNode()
{
}

GridNode::~GridNode()
{
	for (Entity* entity : mList)
	{
		delete entity;
	}
}

void GridNode::Add(Entity* entity)
{
	entity->SetGridNode(this);
	mList.push_back(entity);
	mList.unique();
}

void GridNode::Remove(Entity* entity)
{
	entity->SetGridNode(nullptr);
	mList.remove(entity);
}

bool GridNode::Has(Entity* entity)
{
	return (std::find(mList.begin(), mList.end(), entity) != mList.end());
}

std::list<Entity*> GridNode::GetAll()
{
	return mList;
}
