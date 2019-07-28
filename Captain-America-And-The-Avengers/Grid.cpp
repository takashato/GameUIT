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

void Grid::Add(Entity* entity)
{
	int col = static_cast<int>(entity->GetPosition().x / mCellSize);
	int row = static_cast<int>(entity->GetPosition().y / mCellSize);
	if (col >= mColNum || row >= mRowNum) {
		std::cout << "Grid reject col " << col << " row " << row << "\n";
		return; // Do not add this
	}
	mCells[col][row]->Add(entity);
	std::cout << "An entity has been added to grid <" << col << "; " << row << "> based on position (" << entity->GetPosition().x << "; " << entity->GetPosition().y << ")\n";
}

void Grid::Move(Entity* entity, D3DXVECTOR3 oldPosition)
{
	int oldCol = static_cast<int>(oldPosition.x / mCellSize);
	int oldRow = static_cast<int>(oldPosition.y / mCellSize);
	if (oldCol >= mColNum || oldRow >= mRowNum)
		ThrowGameException("Old position is out of grid range.");
	mCells[oldCol][oldRow]->Remove(entity); // Remove from old placed grid
	Add(entity); // Add to new grid
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
