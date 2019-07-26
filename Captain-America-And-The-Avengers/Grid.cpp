#include "pch.h"
#include "Grid.h"

Grid::Grid(int colNum, int rowNum, int cellSize)
{
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

void Grid::Add(Collidable* collidable)
{
	int col = collidable->GetPositionX() / mCellSize;
	int row = collidable->GetPositionY() / mCellSize;
	if (col >= mColNum || row >= mRowNum) return; // Do not add this
<<<<<<< HEAD
	mCells[col][row]->Add(entity);
	std::cout << "An entity has been added to grid <" << col << "; " << row << "> based on position (" << entity->GetPosition().x << "; " << entity->GetPosition().y << ")\n";
=======
	mCells[col][row]->Add(collidable);
>>>>>>> 30065f4b9e405d273d4c4d14da9107aa49f2ba8f
}

void Grid::Move(Collidable* collidable, D3DXVECTOR3 oldPosition)
{
	int oldCol = static_cast<int>(oldPosition.x / mCellSize);
	int oldRow = static_cast<int>(oldPosition.y / mCellSize);
	if (oldCol >= mColNum || oldRow >= mRowNum)
		ThrowGameException("Old position is out of grid range.");
	mCells[oldCol][oldRow]->Remove(collidable); // Remove from old placed grid
	Add(collidable); // Add to new grid
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
			res.push_back(mCells[i][j]);
		}
	}
	return res;
}
