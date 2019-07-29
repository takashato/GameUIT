#include "pch.h"
#include "ExtraDrawer.h"
#include "Game.h"

ExtraDrawer& ExtraDrawer::GetInstance()
{
	static ExtraDrawer instance;
	return instance;
}

void ExtraDrawer::DrawTransform(std::vector<D3DXVECTOR2> &vertexList, D3DXVECTOR2 trans, D3DXCOLOR color, float width)
{
	float oldWidth = Game::GetInstance().GetLineHandler()->GetWidth();

	for (size_t i = 0; i < vertexList.size(); ++i)
	{
		vertexList[i].x += trans.x;
		vertexList[i].y += trans.y;
	}

	Game::GetInstance().GetLineHandler()->SetWidth(width);
	Game::GetInstance().GetLineHandler()->SetAntialias(TRUE);
	Game::GetInstance().GetLineHandler()->Begin();

	D3DXVECTOR2* vertexData = vertexList.data();
	Game::GetInstance().GetLineHandler()->Draw(vertexData, vertexList.size(), color);

	Game::GetInstance().GetLineHandler()->End();
	Game::GetInstance().GetLineHandler()->SetWidth(oldWidth);

}
