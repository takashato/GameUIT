#pragma once

class ExtraDrawer: ISingleton
{
public:
	static ExtraDrawer& GetInstance();
	
	void DrawTransform(std::vector<D3DXVECTOR2> &vertexList, 
		D3DXVECTOR2 trans = D3DXVECTOR2(.0f, .0f), 
		D3DXCOLOR color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f), 
		float width = 1.0f);

private:
	ExtraDrawer() : ISingleton(NULL) {};
};