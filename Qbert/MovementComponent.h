#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class RenderComponent;
	class Level;
	class TileComponent;
	class MovementComponent : public Component
	{
	public:
		enum class MovementDirection
		{
			up_right,
			up_left,
			down_right,
			down_left
		};
		MovementComponent(GameObject* pParent, RenderComponent* pRenderComponent, Level* level, const int row, const int column);

		void Jump(MovementDirection direction);
		void Update() override;
		void SetCurrentTile(const int row, const int column);
		void ResetPlayerPosition();
	private:

		RenderComponent* m_pRenderComponent;

		Level* m_pLevel;

		glm::vec2 m_StartPosition, m_InitPosition;

		float m_InitJumpVelocityX, m_InitJumpVelocityY, m_FallVelocity;
		float m_JumpDuration, m_JumpTimer, m_FallDuration, m_FallTimer;

		float m_Gravity;
		bool m_IsJumping, m_IsFalling;

		int m_CurrentRow, m_CurrentColumn, m_StartRow, m_StartColumn;
		MovementDirection m_Direction;

		int m_SrcRectX;
	};

}