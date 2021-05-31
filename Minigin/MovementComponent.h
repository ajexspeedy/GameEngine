#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	
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
		MovementComponent(Transform* pTransform);

		void Jump(MovementDirection direction);
		void Update() override;
	private:
		Transform* m_pTransform;

		

		glm::vec2 m_StartPosition;

		float m_InitJumpVelocityX, m_InitJumpVelocityY;
		float m_JumpDuration, m_JumpTimer;
		
		float m_Gravity,m_YOffset;
		bool m_IsJumping;
	};

}