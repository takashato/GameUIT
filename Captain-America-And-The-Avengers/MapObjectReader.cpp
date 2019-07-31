#include "pch.h"
#include "MapObjectReader.h"

void MapObjectReader::LoadFromFile(const char* filePath, Grid* grid)
{
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLElement* pRoot = NULL;
	tinyxml2::XMLError eRes = xmlDoc.LoadFile(filePath);
	if (eRes != tinyxml2::XML_SUCCESS)
	{
		ThrowGameException("Error when loading map object data.");
		return;
	}
	pRoot = xmlDoc.FirstChildElement();
	if (pRoot == nullptr || pRoot->FirstChildElement() == nullptr)
	{
		ThrowGameException("Error when loading map object data.");
		return;
	}
	tinyxml2::XMLElement* element = pRoot->FirstChildElement();
	while (element != nullptr)
	{
		if (element->Attribute("type", "NormalGround") || element->Attribute("type", "HardGround"))
		{
			tinyxml2::XMLElement* subElement = element->FirstChildElement();
			while (subElement != nullptr)
			{
				int x = subElement->IntAttribute("x");
				int y = subElement->IntAttribute("y");
				int wcells = subElement->IntAttribute("wcells");
				int hcells = subElement->IntAttribute("hcells");

				for (int i = 0; i < wcells; ++i)
				{
					for (int j = 0; j < hcells; ++j)
					{
						grid->Add(new Ground(D3DXVECTOR3(x + 16.0f * i, y + 16.0f * j, .0f)));
					}
				}
				subElement = subElement->NextSiblingElement();
			}
		}
		element = element->NextSiblingElement();
	}
}
