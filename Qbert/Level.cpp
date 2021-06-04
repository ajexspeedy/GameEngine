#include "ImposterPCH.h"
#include "Level.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <fstream>
#include <sstream>
#include <cwctype>
using namespace dae;
dae::Level::Level(const int maxRows, const int maxColumns, const std::string& filePath) :
	m_MaxRows{ maxRows },
	m_MaxColumns{ maxColumns },
	m_IsFalling{ false }
{
	SetLevelRules(filePath);
	ResetLevel();
}
Level::~Level()
{
	m_pTiles.clear();
}

void Level::AddTile(GameObject* pTile)
{
	pTile->GetComponent<TileComponent>()->SetTileColor(m_StartTile);
	m_pTiles.push_back(pTile);
}

const std::vector<GameObject*>& dae::Level::GetTiles() const
{
	return m_pTiles;
}

bool Level::CheckOnTiles(int& row, int& column, MovementComponent::MovementDirection direction, bool& isFalling)
{
	
	//ResetLevel();
	switch (direction)
	{
	case dae::MovementComponent::MovementDirection::up_right:
		column++;
		break;
	case dae::MovementComponent::MovementDirection::up_left:
		column++;
		row--;
		break;
	case dae::MovementComponent::MovementDirection::down_right:
		column--;
		row++;
		break;
	case dae::MovementComponent::MovementDirection::down_left:
		column--;
		break;
	default:
		std::cout << "Error CheckOnTiles: Default value" << std::endl;
		break;
	}
	if (IsOutsideLevel(row, column))
	{

		isFalling = true;
		return false;
	}
	bool isVictory = true;
	for (auto tile : m_pTiles)
	{

		if (tile->GetComponent<TileComponent>()->IsOnTile(row, column))
		{

			tile->GetComponent<TileComponent>()->SetTileColor(ChangeTile(tile->GetComponent<TileComponent>()->GetTileColor()));



		}
		if (isVictory)
		{
			if (tile->GetComponent<TileComponent>()->GetTileColor() != m_EndTile)
			{
				isVictory = false;
			}
		}
	}
	if (isVictory)
	{
		NextLevel();

	}
	return true;
}

void dae::Level::AddEntity(GameObject* pEntity)
{
	m_pEntities.push_back(pEntity);
}

bool dae::Level::IsOutsideLevel(const int row, const int column)
{

	return row < 0 || row + column> m_MaxRows || column < 0 || column > m_MaxColumns;
}

void dae::Level::SetLevelRules(const std::string& filePath)
{
	filePath;
	std::string line;

	std::ifstream myfile(filePath);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			CheckTag(RemoveWhitespace(line));
		}
		std::cout << "File opened successfully" << std::endl;
	}
	myfile.close();
}

void dae::Level::SetStartPosition(const std::string& data)
{
	auto frontIt = data.find(',');
	float startPosX = std::stof(data.substr(0, frontIt));
	auto backIt = data.substr(frontIt).find('}');
	float startPosY = std::stof(data.substr(frontIt + 1, backIt));

	m_StartPositionPlayer = { startPosX,startPosY };
}

void dae::Level::SetStartTile(const std::string& data)
{
	auto frontIt = data.find(',');
	m_StartTilePlayerX = std::stoi(data.substr(0, frontIt));
	auto backIt = data.substr(frontIt).find('}');
	m_StartTilePlayerY = std::stoi(data.substr(frontIt + 1, backIt));

}

std::string dae::Level::RemoveWhitespace(const std::string& line)
{
	std::string newString;
	for (auto character : line)
	{
		if (!std::iswspace(character))
		{
			newString += character;
		}
	}
	return newString;
}

void dae::Level::CheckTag(const std::string& line)
{
	if (line.substr(0, 1) == "<")
	{

		std::string tag{};
		for (size_t i{ 1 }; i < line.size(); i++)
		{
			if (line.substr(i, 1) == ">")
			{
				if (tag == "StartTileType")
				{
					m_StartTile = static_cast<TileComponent::TileColor>(std::stoi(line.substr(i + 1, 1)));

				}
				if (tag == "LevelType")
				{
					m_LevelType = static_cast<LevelType>(std::stoi(line.substr(i + 1, 1)));
					switch (m_LevelType)
					{
					case LevelType::Level1:
					case LevelType::Level3:
						m_EndTile = TileComponent::TileColor::color1;
						break;
					case LevelType::Level2:
						m_EndTile = TileComponent::TileColor::color2;
						break;
					}

				}
				if (tag == "StartPosition")
				{


					SetStartPosition(line.substr(i + 2));


				}
				if (tag == "StartTile")
				{
					SetStartTile(line.substr(i + 2));
				}
				break;
			}

			tag += line.substr(i, 1);
		}
		//	std::cout << tag << std::endl;
	}
}

void dae::Level::NextLevel()
{

	switch (m_LevelType)
	{
	case LevelType::Level1:
		SetLevelRules("../Data/Levels/Level2.xml");
		ResetLevel();
		break;
	case LevelType::Level2:
		SetLevelRules("../Data/Levels/Level3.xml");
		ResetLevel();
		break;
	case LevelType::Level3:
		std::cout << "Victory " << std::endl;
		break;
	}
}

void dae::Level::ResetLevel()
{
	for (auto entity : m_pEntities)
	{
		if (entity->HasComponent<MovementComponent>())
		{
			entity->GetComponent<MovementComponent>()->ResetPlayerPosition();
		}
	}
	for (auto tile : m_pTiles)
	{
		tile->GetComponent<TileComponent>()->SetTileColor(m_StartTile);
	}
}

TileComponent::TileColor dae::Level::ChangeTileLevel1(TileComponent::TileColor tileColor)
{
	switch (tileColor)
	{
	case TileComponent::TileColor::defaultColor:
		return TileComponent::TileColor::color1;
		break;
	case TileComponent::TileColor::color1:
		return TileComponent::TileColor::color1;
		break;
	case TileComponent::TileColor::color2:
		return TileComponent::TileColor::color1;
		break;
	default:
		return TileComponent::TileColor::defaultColor;
	}
}

TileComponent::TileColor dae::Level::ChangeTileLevel2(TileComponent::TileColor tileColor)
{
	switch (tileColor)
	{
	case TileComponent::TileColor::defaultColor:
		return TileComponent::TileColor::color1;
		break;
	case TileComponent::TileColor::color1:
		return TileComponent::TileColor::color2;
		break;
	case TileComponent::TileColor::color2:
		return TileComponent::TileColor::color2;
		break;
	default:
		return TileComponent::TileColor::defaultColor;
	}
}

TileComponent::TileColor dae::Level::ChangeTileLevel3(TileComponent::TileColor tileColor)
{
	switch (tileColor)
	{
	case TileComponent::TileColor::defaultColor:
		return TileComponent::TileColor::color1;
		break;
	case TileComponent::TileColor::color1:
		return TileComponent::TileColor::defaultColor;
		break;
	default:
		return TileComponent::TileColor::defaultColor;
	}
}

TileComponent::TileColor Level::ChangeTile(TileComponent::TileColor tileColor)
{
	switch (m_LevelType)
	{
	case LevelType::Level1:
		return ChangeTileLevel1(tileColor);
		break;
	case LevelType::Level2:
		return ChangeTileLevel2(tileColor);
		break;
	case LevelType::Level3:
		return ChangeTileLevel3(tileColor);
		break;
	default:

		std::cout << "Error Level::ChangeTile: default leveltype value \n";
		return TileComponent::TileColor::defaultColor;
	}


}
