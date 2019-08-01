#include "pch.h"
#include "Grid.h"

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
	int col = static_cast<int>(entity->GetPosition().x / mCellSize);
	int row = static_cast<int>(entity->GetPosition().y / mCellSize);
	if (col >= mColNum || row >= mRowNum) {
		std::cout << "Grid reject col " << col << " row " << row << "\n";
		return; // Do not add this
	}
	mCells[col][row]->Add(entity);
}

void Grid::Move(Entity* entity)
{
	int col = static_cast<int>(entity->GetPosition().x / mCellSize);
	if (col >= mColNum) col = mColNum - 1;
	int row = static_cast<int>(entity->GetPosition().y / mCellSize);
	if (row >= mRowNum) row = mRowNum - 1;
	//std::cout << "Change (" << oldCol << "; " << oldRow << ") to " << "(" << col << "; " << row << ")\n";

	if (entity->GetGridNode() == nullptr)
	{
		mCells[col][row]->Add(entity);
		return;
	}

	if (entity->GetGridNode() == mCells[col][row]) return;

	entity->GetGridNode()->Remove(entity);
	mCells[col][row]->Add(entity);

	std::cout << "Changed to " << "(" << col << "; " << row << ")\n";
}

std::vector<GridNode*> Grid::GetByViewPort(Camera* camera)
{
	std::vector<GridNode*> res;
	RECT bound = camera->GetBound();
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

void Grid::GetEntities(Camera* camera, std::vector<Entity*>& entities)
{
	entities.clear();
	std::vector<GridNode*> nodes = GetByViewPort(camera);
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		for (Entity* entity : nodes[i]->GetAll())
		{
			entities.push_back(entity);
		}
	}
}

Grid* Grid::instance = nullptr;