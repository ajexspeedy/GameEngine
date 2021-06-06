#pragma once
#include "Component.h"
#include "Transform.h"


namespace dae
{
	class RenderComponent;
	class TileComponent;
	class Level;
	class MovementComponent : public Component
	{
	public:
		enum class MovementDirection : int
		{
			up_right = 0,
			up_left = 1,
			down_right = 2,
			down_left = 3,
			right,
			left
		};
		enum class EntityType
		{
			Qbert,
			Coily,
			Wrongway,
			Ugg,
			Slick,
			Sam
		};

		MovementComponent(GameObject* pParent, Level* level, const int row, const int column,EntityType type, bool TriggersTile = true);

		void Jump(MovementDirection direction);
		void Update() override;

		void WrongwayJump(MovementDirection direction);
		void UggJump(MovementDirection direction);


		void SetCurrentTile(const int row, const int column);
		void SetStartTile(const int row, const int column);
		void SetTileOffset(const int row, const int colum);

		void ResetPosition(const float x, const float y);
		void ResetPosition();

		bool IsJumping() const;
		bool IsOnTile(const int row, const int column);

		int GetRow() const;
		int GetColumn() const;

		int GetLevelMode() const;

	private:



		Level* m_pLevel;

		glm::vec2 m_StartPosition, m_InitPosition;

		float m_InitJumpVelocityX, m_InitJumpVelocityY, m_FallVelocity;
		float m_JumpDuration, m_JumpTimer, m_FallDuration, m_FallTimer;

		float m_Gravity;
		bool m_IsJumping, m_IsFalling, m_HasAnimations, m_TriggersTiles;

		int m_CurrentRow, m_CurrentColumn, m_StartRow, m_StartColumn;
		MovementDirection m_Direction;

		int m_RowOffset, m_ColumnOffset;
		EntityType m_EntityType;

	};

}