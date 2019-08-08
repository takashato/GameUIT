#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "Grid.h"

Grid::Grid(int totalWidth, int totalHeight)
{
	Grid::instance = this;

	mCellSize = Game::GetInstance().GetWidth() > Game::GetInstance().GetHeight() ?
		Game::GetInstance().GetWidth() / 2
		: Game::GetInstance().GetHeight() / 2;

	mColNum = (int)ceil(1.0f * totalWidth / mCellSize);
	mRowNum = (int)ceil(1.0f * totalHeight / mCellSize);
	InitNodes();
}

Grid::Grid(int colNum, int rowNum, int cellSize)
{
	Grid::instance = this;
	mColNum = colNum;
	mRowNum = rowNum;
	mCellSize = cellSize;
	InitNodes();
}

Grid::~Grid()
{
	for (int i = 0; i < mColNum; ++i)
	{
		for (int j = 0; j < mRowNum; ++j)
		{
			delete mCells[i][j];
		}
		delete mCells[i];
	}
	delete mCells;
}

void Grid::Update(float deltaTime, RECT rect, Player* player)
{
	mTemp.clear();
	GetEntities(rect, mTemp);
	std::vector<Entity*> toDelete;
	for (Entity* entity : mTemp)
	{
		auto type = entity->GetCollidableObjectType();
		if (type == EEnemy)
		{
			((Enemy*)entity)->Update(deltaTime, player);
		}
		else
		{
			entity->Update(deltaTime);
		}

		// Check destroy
		if (type == EBullet)
		{
			auto bullet = (Bullet*)entity;
			if (bullet->GetBulletType() == BulletType::BNormalBullet
				|| bullet->GetBulletType() == BulletType::BLittleMissile
				|| bullet->GetBulletType() == BulletType::BBigMissile
				|| bullet->GetBulletType() == BulletType::BBossNormalBullet
				|| bullet->GetBulletType() == BulletType::BBossVipBullet
				|| bullet->GetBulletType() == BulletType::BDefaultBullet
				|| bullet->GetBulletType() == BulletType::BRedAlertBullet
				|| bullet->GetBulletType() == BulletType::BBarrel)
			{
				if (bullet->mState == 1) // is pending delete
				{
					toDelete.emplace_back(entity);
				}
			}
		}
		else if (type == EItem)
		{
			if (((Item*)entity)->mState == 1)
			{
				toDelete.emplace_back(entity);
			}
		}
		else if (type == EEnemy)
		{
			if (((Enemy*)entity)->pendingDelete)
			{
				toDelete.emplace_back(entity);
			}
		}
	}

	for (auto entity : toDelete)
	{
		if (auto enemy = dynamic_cast<Enemy*>(entity)) // Tell spawner they will be delete
		{
			if (enemy->GetSpawner() != nullptr) enemy->GetSpawner()->OnDelete();
		}
		entity->GetGridNode()->Remove(entity);
		mTemp.erase(entity);
		delete entity;
	}
}

void Grid::Draw(D3DXVECTOR2 trans)
{
	std::set<Entity*> layer1, layer2;

	for (Entity* entity : mTemp)
	{
		if (entity->GetCollidableObjectType() == CollidableObjectType::ECapsule)
		{
			layer1.emplace(entity);
		}
		else
		{
			layer2.emplace(entity);
		}
	}

	for (Entity* entity : layer1)
	{
		entity->Draw(trans);
	}

	for (Entity* entity : layer2)
	{
		entity->Draw(trans);
	}
}

void Grid::InitNodes()
{
	mCells = new GridNode**[mColNum];
	for (int i = 0; i < mColNum; ++i)
	{
		mCells[i] = new GridNode*[mRowNum];
		for (int j = 0; j < mRowNum; ++j)
		{
			mCells[i][j] = new GridNode();
		}
	}
}

GridNode* Grid::GetNode(int col, int row)
{
	if (col >= mColNum || row >= mRowNum)
		ThrowGameException("Out of grid range.");
	return mCells[col][row];
}

void Grid::Add(Entity* entity)
{
	if (entity->GetCollidableObjectType() != CollidableObjectType::EPlatform)
	{
		int col = static_cast<int>(entity->GetPosition().x / mCellSize);
		int row = static_cast<int>(entity->GetPosition().y / mCellSize);
		if (col >= mColNum || row >= mRowNum || col < 0 || row < 0) {
			std::cout << "Grid reject col " << col << " row " << row << "\n";
			return; // Do not add this
		}
		mCells[col][row]->Add(entity);
	}
	else
	{
		RECT bb = entity->GetBoundingBox();
		int xs = bb.left / mCellSize;
		int ys = bb.top / mCellSize;
		int xe = bb.right / mCellSize;
		int ye = bb.bottom / mCellSize;
		for (int i = xs; i <= xe; ++i)
		{
			for (int j = ys; j <= ye; ++j)
			{
				if (i >= mColNum || j >= mRowNum || i < 0 || j < 0) continue;
				mCells[i][j]->Add(entity);
			}
		}
	}
}

void Grid::Move(Entity* entity)
{
	if (entity->GetCollidableObjectType() == EPlatform) return; // Not need to move???

	int col = static_cast<int>(entity->GetPosition().x / mCellSize);
	if (col >= mColNum) col = mColNum - 1;
	if (col < 0) col = 0;
	int row = static_cast<int>(entity->GetPosition().y / mCellSize);
	if (row >= mRowNum) row = mRowNum - 1;
	if (row < 0) row = 0;

	if (entity->GetGridNode() == nullptr)
	{
		mCells[col][row]->Add(entity);
		return;
	}

	if (entity->GetGridNode() == mCells[col][row]) return;

	entity->GetGridNode()->Remove(entity);
	mCells[col][row]->Add(entity);
}

std::vector<GridNode*> Grid::GetByViewPort(RECT bound)
{
	std::vector<GridNode*> res;
	int xs = bound.left / mCellSize;
	int ys = bound.top / mCellSize;
	int xe = bound.right / mCellSize;
	int ye = bound.bottom / mCellSize;
	for (int i = xs; i <= xe; ++i)
	{
		for (int j = ys; j <= ye; ++j)
		{
			if (i >= mColNum || j >= mRowNum) continue;
			res.push_back(mCells[i][j]);
		}
	}
	return res;
}

void Grid::GetEntities(RECT rect, std::set<Entity*>& entities)
{
	entities.clear();
	std::vector<GridNode*> nodes = GetByViewPort(rect);
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		for (Entity* entity : nodes[i]->GetAll())
		{
			entities.emplace(entity);
		}
	}
}

Grid* Grid::instance = nullptr;