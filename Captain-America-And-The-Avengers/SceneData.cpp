#include "pch.h"
#include "SceneData.h"

SceneData::SceneData()
{

}

SceneData::SceneData(LPCSTR filePath)
{
	ReadData(filePath);
}

SceneData::~SceneData()
{
}


void SceneData::ReadData(LPCSTR filePath)
{
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eRes = xmlDoc.LoadFile(filePath);
	if (eRes != tinyxml2::XML_SUCCESS)
	{
		ThrowGameException("Error when loading data from xml.");
		return;
	}
	pRoot = xmlDoc.FirstChildElement();

	// Start read data
	auto childNode = pRoot->FirstChildElement();
	while (childNode != nullptr)
	{
		std::string name(childNode->Name());
		if (name == "Tilemap")
		{
			mTilemapIPath = childNode->Attribute("imagePath");
			mTilemapMPath = childNode->Attribute("matrixPath");
		}
		else if (name == "SpawnPoints")
		{
			auto subNode = childNode->FirstChildElement();
			while (subNode != nullptr)
			{
				std::string key(subNode->Attribute("name"));
				float x = subNode->FloatAttribute("x");
				float y = subNode->FloatAttribute("y");
				mSpawnPoints.emplace(key, D3DXVECTOR3(x, y, .0f));

				subNode = subNode->NextSiblingElement();
			}
		}
		else if (name == "MapObjects")
		{
			auto subNode = childNode->FirstChildElement();
			while (subNode != nullptr)
			{
				std::string subName(subNode->Name());
				if (subName == "Grounds")
				{
					auto groundNode = subNode->FirstChildElement();
					while (groundNode != nullptr)
					{
						std::string type(groundNode->Attribute("type"));
						GroundType gType = GroundType::EGroundHard;
						if (type == "Normal") 
						{
							gType = GroundType::EGroundNormal;
						}
						else if (type == "Water")
						{
							gType = GroundType::EGroundWater;
						}
						mDataGrounds.push_back(DataGround(
							gType, 
							groundNode->IntAttribute("x"),
							groundNode->IntAttribute("y"),
							groundNode->IntAttribute("w"),
							groundNode->IntAttribute("h")
						));
						groundNode = groundNode->NextSiblingElement();
					}
				}
				else if (subName == "Enemies")
				{
					auto enemyNode = subNode->FirstChildElement();
					while (enemyNode != nullptr)
					{
						std::string type(enemyNode->Attribute("type"));
						EnemyType eType = EnemyType::EDefaultEnemy;
						if (type == "RunEnemy")
							eType = EnemyType::ERunEnemy;
						else if (type == "MissileEnemy")
							eType = EnemyType::EMissileEnemy;
						else if (type == "GunEnemy")
							eType = EnemyType::EGunEnemy;
						else if (type == "GunStock")
							eType = EnemyType::EGunStockEnemy;
						if (eType != EnemyType::EDefaultEnemy)
						{
							mDataEnemies.push_back(DataEnemy(
								eType,
								enemyNode->IntAttribute("x"),
								enemyNode->IntAttribute("y"),
								enemyNode->IntAttribute("subType")
							));
						}
						enemyNode = enemyNode->NextSiblingElement();
					}
				}
				else if (subName == "Capsules")
				{
					auto capsuleNode = subNode->FirstChildElement();
					while (capsuleNode != nullptr)
					{
						int x = capsuleNode->IntAttribute("x");
						int y = capsuleNode->IntAttribute("y");
						std::vector<ItemType> itemList;
						auto itemNode = capsuleNode->FirstChildElement();
						while (itemNode != nullptr)
						{
							std::string type(itemNode->Attribute("type"));
							ItemType iType;
							if (type == "PowerStone")
								iType = ItemType::PowerStone;
							else if (type == "FivePointItem")
								iType = ItemType::FivePoint;
							else if (type == "HeartEnergy")
								iType = ItemType::HeartEnergy;
							else if (type == "KeyCrystal")
								iType = ItemType::KeyCrystal;
							else 
								iType = ItemType::OneUp;
							itemList.push_back(iType);
							itemNode = itemNode->NextSiblingElement();
						}
						mDataCapsules.push_back(DataCapsule(x, y, std::move(itemList)));
						capsuleNode = capsuleNode->NextSiblingElement();
					}
				}
				subNode = subNode->NextSiblingElement();
			}
		}
		childNode = childNode->NextSiblingElement();
	}
}

D3DXVECTOR3 SceneData::GetSpawnPoint(LPCSTR name)
{
	std::string key(name);
	if (mSpawnPoints.find(name) == mSpawnPoints.end()) // Not have that spawnpoint
	{
		if (mSpawnPoints.size() == 0)
		{
			return D3DXVECTOR3(.0f, .0f, .0f);
		}
		else
		{
			return mSpawnPoints.begin()->second;
		}
	}
	else
	{
		return mSpawnPoints.at(name);
	}
}