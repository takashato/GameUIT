#include "pch.h"
#include "GridNode.h"

GridNode::GridNode()
{
}

void GridNode::Add(Collidable* collidable)
{
	mList.push_back(collidable);
	mList.unique();
}

void GridNode::Remove(Collidable* collidable)
{
	mList.remove(collidable);
}

std::list<Collidable*> GridNode::GetAll()
{
	return mList;
}
