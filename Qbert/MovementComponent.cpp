#include "ImposterPCH.h"
#include "MovementComponent.h"
#include "TimeManager.h"
#include "RenderComponent.h"
#include "Level.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::MovementComponent::MovementComponent(GameObject* pParent, RenderComponent* pRenderComponent, Level* level) :
	Component{ pParent },
	m_pRenderComponent{ pRenderComponent },
	m_pLevel{ level },
	m_StartPosition{ 0.f,0.f },
	m_InitJumpVelocityX{ 0.f },
	m_InitJumpVelocityY{ 0.f },
	m_FallVelocity{ 50.f },
	m_JumpDuration{ 0.15f },
	m_JumpTimer{ 0.f },
	m_FallTimer{ 0.f },
	m_Gravity{ 9.81f },
	m_YOffset{ 1.f },
	m_IsJumping{ false },
	m_IsFalling{ false },
	m_SrcRectX{ 5 },
	m_CurrentRow{},
	m_CurrentColumn{},
	m_Direction{}

{
	m_pRenderComponent->MoveSrcRectPosition(m_SrcRectX, 0);
}

void dae::MovementComponent::Jump(MovementDirection direction)
{
	if (m_IsJumping)
		return;
	auto position = GetParent()->GetComponent<TransformComponent>()->GetPosition();
	auto newPos = position;
	float xTranslate{ 32.f }, yTranslate{ 48.f };
	m_StartPosition = { position.x,position.y };
	m_Direction = direction;
	switch (m_Direction)
	{
	case MovementComponent::MovementDirection::up_right:
		m_pRenderComponent->MoveSrcRectPosition(0, 0);
		m_SrcRectX = 1;
		newPos.x += xTranslate;
		newPos.y -= yTranslate;

		break;
	case MovementComponent::MovementDirection::up_left:
		m_pRenderComponent->MoveSrcRectPosition(2, 0);
		m_SrcRectX = 3;
		newPos.x -= xTranslate;
		newPos.y -= yTranslate;

		break;
	case MovementComponent::MovementDirection::down_right:
		m_pRenderComponent->MoveSrcRectPosition(4, 0);
		m_SrcRectX = 5;
		newPos.x += xTranslate;
		newPos.y += yTranslate;
		break;
	case MovementComponent::MovementDirection::down_left:
		m_pRenderComponent->MoveSrcRectPosition(6, 0);
		m_SrcRectX = 7;
		newPos.x -= xTranslate;
		newPos.y += yTranslate;
		break;
	}

	m_InitJumpVelocityX = (newPos.x - position.x) / m_JumpDuration;
	m_InitJumpVelocityY = -(-(newPos.y - position.y) + 0.5f * m_Gravity * m_JumpDuration * m_JumpDuration) / m_JumpDuration;
	m_JumpTimer = 0.f;

	m_IsJumping = true;
}

void dae::MovementComponent::Update()
{

	if (m_IsJumping)
	{
		float deltaTime = TimeManager::GetInstance().GetDeltaTime();
		m_JumpTimer += deltaTime;

		if (m_JumpTimer > m_JumpDuration)
		{
			m_JumpTimer = m_JumpDuration;
			m_pRenderComponent->MoveSrcRectPosition(m_SrcRectX, 0);
			m_IsJumping = false;
			glm::vec2 targetPos;
			targetPos.x = m_StartPosition.x + m_JumpDuration * m_InitJumpVelocityX;
			targetPos.y = m_StartPosition.y + m_JumpDuration * m_InitJumpVelocityY;
			GetParent()->GetComponent<TransformComponent>()->SetPosition(targetPos.x, targetPos.y, 0.f);
			m_pLevel->CheckOnTiles(m_CurrentRow, m_CurrentColumn, m_Direction, m_IsFalling);

		}

		float newPosX = m_StartPosition.x + m_JumpTimer * m_InitJumpVelocityX;
		float newPosY = m_StartPosition.y + m_JumpTimer * m_InitJumpVelocityY + 0.5f * m_Gravity * m_JumpTimer * m_JumpTimer;

		GetParent()->GetComponent<TransformComponent>()->SetPosition(newPosX, newPosY, 0.f);

	}
	if (m_IsFalling)
	{
		float deltaTime = TimeManager::GetInstance().GetDeltaTime();

		m_FallTimer += deltaTime;


		auto pos = GetParent()->GetComponent<TransformComponent>()->GetPosition();
		pos.y += m_Gravity * m_FallVelocity * deltaTime;

		GetParent()->GetComponent<TransformComponent>()->SetPosition(pos.x, pos.y, 0.f);
	}
}

void dae::MovementComponent::SetCurrentTile(const int row, const int column)
{
	m_CurrentRow = row;
	m_CurrentColumn = column;
}
