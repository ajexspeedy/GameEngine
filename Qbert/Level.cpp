#include "ImposterPCH.h"
#include "Level.h"
#include "GameObject.h"
#include "TransformComponent.h"

using namespace dae;
dae::Level::Level(const int maxRows, const int maxColumns, LevelType levelType) :
	m_MaxRows{ maxRows },
	m_MaxColumns{ maxColumns },
	m_LevelType{ levelType },
	m_IsFalling{ false }
{
}
Level::~Level()
{
	for (auto tile : m_pTiles)
	{
		if (tile)
		{
			delete tile;
			tile = nullptr;
		}
	}
	m_pTiles.clear();
}

void Level::AddTile(GameObject* pTile)
{
	m_pTiles.push_back(pTile);
}

const std::vector<GameObject*>& dae::Level::GetTiles() const
{
	return m_pTiles;
}

void Level::CheckOnTiles(int& row, int& column, MovementComponent::MovementDirection direction, bool& isFalling)
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
	default:
		std::cout << "Error CheckOnTiles: Default value" << std::endl;
		break;
	}
	if (IsOutsideLevel(row, column))
	{

		isFalling = true;
		return;
	}
	for (auto tile : m_pTiles)
	{

		if (tile->GetComponent<TileComponent>()->IsOnTile(row, column))
		{
			tile->GetComponent<TileComponent>()->SetTileColor(ChangeTile(tile->GetComponent<TileComponent>()->GetTileColor()));

			std::cout << "On tile: \n";


		}
	}
}

bool dae::Level::IsOutsideLevel(const int row, const int column)
{
	
	return row < 0 || row + column> m_MaxRows || column < 0 || column > m_MaxColumns;
}

TileComponent::TileColor Level::ChangeTile(TileComponent::TileColor tileColor)
{
	switch (tileColor)
	{
	case TileComponent::TileColor::color1:
		return TileComponent::TileColor::color2;
		break;
	case TileComponent::TileColor::color2:
		return TileComponent::TileColor::defaultColor;
		break;
	case TileComponent::TileColor::defaultColor:
		return TileComponent::TileColor::color1;
		break;
	default:
		return TileComponent::TileColor::defaultColor;
	}

}
