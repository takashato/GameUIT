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
	mList.push_back(entity);
	mList.unique();
}

void GridNode::Remove(Entity* entity)
{
	mList.remove(entity);
}

std::list<Entity*> GridNode::GetAll()
{
	return mList;
}
