#include "ImposterPCH.h"
#include "Level.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
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

bool Level::CheckOnTiles(int& row, int& column, MovementComponent::MovementDirection direction, bool triggersTile, bool undoTile, const int rowOffset, const int columnOffset)
{


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
	case dae::MovementComponent::MovementDirection::right:
		row++;
		break;
	case dae::MovementComponent::MovementDirection::left:
		row--;
		break;
	default:
		std::cout << "Error CheckOnTiles: Default value" << std::endl;
		break;
	}
	if (IsOutsideLevel(row + rowOffset, column + columnOffset))
	{

		return false;
	}

	if (!triggersTile)
	{
		return true;
	}
	bool isVictory = true;
	for (auto tile : m_pTiles)
	{

		if (tile->GetComponent<TileComponent>()->IsOnTile(row, column))
		{
			if (undoTile)
			{
				tile->GetComponent<TileComponent>()->SetTileColor(TileComponent::TileColor::defaultColor);
				return true;
			}

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

glm::vec2 dae::Level::GetStartpositionPlayer() const
{
	return m_StartPositionPlayer;
}

glm::vec2 dae::Level::GetStartTilePlayer() const
{
	return glm::vec2{ float(m_StartTilePlayerX),float(m_StartTilePlayerY) };
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

void dae::Level::SetLevelMode(const int mode)
{
	ResetLevel();
	m_Levelmode = static_cast<LevelMode>(mode);
	switch (m_Levelmode)
	{
	case LevelMode::singleplayer:
		m_Player2->SetActive(false);


		m_Player1->GetComponent<MovementComponent>()->ResetPosition(320.f, 85.f);
		m_Player1->GetComponent<MovementComponent>()->SetStartTile(0, 6);
		m_Player1->GetComponent<MovementComponent>()->SetCurrentTile(0, 6);
		break;
	case LevelMode::coop:
		m_Player2->SetActive(true);
		m_Player2->GetComponent<AnimationComponent>()->SetTexture("Textures/Qbert.png");
		m_Player2->GetComponent<AnimationComponent>()->SetSrcRectSize(16, 16);

		m_Player1->GetComponent<MovementComponent>()->ResetPosition(125.f, 370.f);
		m_Player1->GetComponent<MovementComponent>()->SetCurrentTile(0, 0);
		m_Player1->GetComponent<MovementComponent>()->SetStartTile(0, 0);
		break;
	case LevelMode::versus: // Versus doesnt really work properly
		m_Player2->SetActive(true);
		m_Player2->GetComponent<AnimationComponent>()->SetTexture("Textures/Coily_Snake.png");
		m_Player2->GetComponent<AnimationComponent>()->SetSrcRectSize(16, 32);

		m_Player1->GetComponent<MovementComponent>()->ResetPosition(125.f, 370.f);
		m_Player1->GetComponent<MovementComponent>()->SetCurrentTile(0, 0);
		m_Player1->GetComponent<MovementComponent>()->SetStartTile(0, 0);

		break;
	}
}

void dae::Level::SetPlayer1(GameObject* player1)
{
	m_Player1 = player1;
}

void dae::Level::SetPlayer2(GameObject* player2)
{
	m_Player2 = player2;
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
		entity->SwapIfActive(static_cast<int>(m_LevelType));
		if (entity->HasComponent<MovementComponent>())
		{
			entity->GetComponent<MovementComponent>()->ResetPosition();
		}
	}
	for (auto tile : m_pTiles)
	{
		tile->GetComponent<TileComponent>()->SetTileColor(m_StartTile);
	}
}

Level::LevelMode dae::Level::GetLevelMode() const
{
	return m_Levelmode;
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
