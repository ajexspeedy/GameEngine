#include "ImposterPCH.h"
#include "MovementComponent.h"
#include "TimeManager.h"


dae::MovementComponent::MovementComponent(Transform* pTransform) :
	m_pTransform{ pTransform },
	m_StartPosition{0.f,0.f},
	m_InitJumpVelocityX{ 0.f },
	m_InitJumpVelocityY{ 0.f },
	m_JumpDuration{ 0.1f },
	m_JumpTimer{ 0.f },
	m_Gravity{ 9.81f },
	m_YOffset{ 1.f },
	m_IsJumping{ false }
{
}

void dae::MovementComponent::Jump(MovementDirection direction)
{
	auto position = m_pTransform->GetPosition();
	auto newPos = position;
	float xTranslate{ 32.f }, yTranslate{ 48.f };

	switch (direction)
	{
	case MovementComponent::MovementDirection::up_right:
		//Move(xTranslate, -yTranslate);
		newPos.x += xTranslate;
		newPos.y -= yTranslate;

		break;
	case MovementComponent::MovementDirection::up_left:
		newPos.x -= xTranslate;
		newPos.y -= yTranslate;
		//Move(-xTranslate, -yTranslate);
		break;
	case MovementComponent::MovementDirection::down_right:
		newPos.x += xTranslate;
		newPos.y += yTranslate;
		break;
	case MovementComponent::MovementDirection::down_left:
		newPos.x -= xTranslate;
		newPos.y += yTranslate;
		break;
	}

	m_InitJumpVelocityX = (newPos.x - position.x) / m_JumpDuration;
	m_InitJumpVelocityY = -(-(newPos.y - position.y) + 0.5f * m_Gravity * m_JumpDuration * m_JumpDuration) / m_JumpDuration;
	m_JumpTimer = 0.f;
	m_StartPosition = {position.x,position.y};
	m_IsJumping = true;
}

void dae::MovementComponent::Update()
{
	std::cout << m_IsJumping << std::endl;
	if (m_IsJumping)
	{
		float deltaTime = TimeManager::GetInstance().GetDeltaTime();
		m_JumpTimer += deltaTime;
		std::cout << m_JumpTimer << "- " << m_JumpDuration << std::endl;
		if (m_JumpTimer > m_JumpDuration)
		{
			m_JumpTimer = m_JumpDuration;
			m_IsJumping = false;
		}
		
		float newPosX = m_StartPosition.x + m_JumpTimer * m_InitJumpVelocityX;
		float newPosY = m_StartPosition.y + m_JumpTimer * m_InitJumpVelocityY + 0.5f * m_Gravity * m_JumpTimer * m_JumpTimer;

		m_pTransform->SetPosition(newPosX, newPosY, 0.f);

	}
}
