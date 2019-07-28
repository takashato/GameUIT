#include "pch.h"
#include "AnimationScript.h"

AnimationScript::AnimationScript(const char* filePath)
{
	tinyxml2::XMLError eRes = xmlDoc.LoadFile(filePath);
	if (eRes != tinyxml2::XML_SUCCESS)
	{
		ThrowGameException("Error when loading animation scripts");
		return;
	}
	pRoot = xmlDoc.FirstChildElement();
	if (pRoot == nullptr || pRoot->FirstChildElement() == nullptr)
	{
		ThrowGameException("Error when loading animation scripts");
		return;
	}
}

std::vector<RECT> AnimationScript::GetRectList(const char* animationName, const char* type)
{
	tinyxml2::XMLElement* element = pRoot->FirstChildElement();
	while (element != nullptr)
	{
		if (!element->Attribute("name", animationName))
		{
			element = element->NextSiblingElement();
		}
		else // Found element
		{
			tinyxml2::XMLElement* subElement = element->FirstChildElement();
			if (!subElement)
			{
				ThrowGameException("Empty animation detected.");
				return std::vector<RECT>();
			}

			if (subElement->Attribute("type", type))
			{
				return GetSpriteRects(subElement);
			}

			subElement = subElement->NextSiblingElement();
			if (!subElement)
			{
				ThrowGameException("Invalid sprites type.");
				return std::vector<RECT>();
			}
			return GetSpriteRects(subElement);
		}
	}

	ThrowGameException("Can't find animation.");
	return std::vector<RECT>();
}

std::vector<RECT> AnimationScript::GetSpriteRects(tinyxml2::XMLElement* ele)
{
	std::vector<RECT> list;
	tinyxml2::XMLElement* subElement = ele->FirstChildElement();
	while (subElement != nullptr)
	{
		int x = subElement->IntAttribute("x");
		int y = subElement->IntAttribute("y");
		int w = subElement->IntAttribute("w");
		int h = subElement->IntAttribute("h");
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + w;
		rect.bottom = y + h;
		list.push_back(rect);

		subElement = subElement->NextSiblingElement();
	}
	if (list.size() == 0)
	{
		ThrowGameException("Empty sprite set!");
	}
	return list;
}
