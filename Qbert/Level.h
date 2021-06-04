#pragma once
#include "TileComponent.h"
#include "MovementComponent.h"
#include "Transform.h"
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
		Level(const int maxRows,const int maxColumns,const std::string& filepath);
		~Level();

		void AddTile(GameObject* pTile);
		const std::vector<GameObject*>& GetTiles() const;

		bool CheckOnTiles(int& row, int& column, MovementComponent::MovementDirection direction, bool& isFalling);

		void AddEntity(GameObject* pEntity);


	private:
		bool IsOutsideLevel(const int row, const int column);
		void SetLevelRules(const std::string& filePath);
		void SetStartPosition(const std::string& data);
		void SetStartTile(const std::string& data);

		std::string RemoveWhitespace(const std::string& line);
		void CheckTag(const std::string& line);

		void NextLevel();
		void ResetLevel();

		TileComponent::TileColor ChangeTileLevel1(TileComponent::TileColor tileColor);
		TileComponent::TileColor ChangeTileLevel2(TileComponent::TileColor tileColor);
		TileComponent::TileColor ChangeTileLevel3(TileComponent::TileColor tileColor);

		TileComponent::TileColor ChangeTile(TileComponent::TileColor tileColor);
		std::vector<GameObject*> m_pTiles;

		bool m_IsFalling;
		LevelType m_LevelType;
		TileComponent::TileColor m_StartTile, m_EndTile;
		int m_MaxRows, m_MaxColumns;

		glm::vec2 m_StartPositionPlayer;
		int m_StartTilePlayerX, m_StartTilePlayerY;

		std::vector<GameObject*> m_pEntities;
	};

}