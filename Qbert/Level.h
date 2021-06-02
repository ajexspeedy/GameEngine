#pragma once
#include "TileComponent.h"
#include "MovementComponent.h"
namespace dae
{
	class GameObject;
	class Level
	{
	public:
		enum class LevelType
		{
			Level1,
			Level2,
			Level3
		};
		Level(const int maxRows,const int maxColumns,LevelType type = LevelType::Level1);
		~Level();

		void AddTile(GameObject* pTile);
		const std::vector<GameObject*>& GetTiles() const;

		void CheckOnTiles(int& row, int& column, MovementComponent::MovementDirection direction, bool& isFalling);

	private:
		bool IsOutsideLevel(const int row, const int column);
		TileComponent::TileColor ChangeTile(TileComponent::TileColor tileColor);
		std::vector<GameObject*> m_pTiles;

		bool m_IsFalling;
		LevelType m_LevelType;
		int m_MaxRows, m_MaxColumns;
	};

}