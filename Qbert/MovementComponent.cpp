#include "ImposterPCH.h"
#include "Level.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Locator.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "AnimationComponent.h"
#include "SlickSamComponent.h"

dae::MovementComponent::MovementComponent(GameObject* pParent, Level* level, const int row, const int column, EntityType type, bool triggersTiles) :
	Component{ pParent },
	m_pLevel{ level },
	m_StartPosition{ 0.f,0.f },
	m_InitPosition{ 0.f,0.f },
	m_InitJumpVelocityX{ 0.f },
	m_InitJumpVelocityY{ 0.f },
	m_FallVelocity{ 50.f },
	m_JumpDuration{ 0.15f },
	m_JumpTimer{ 0.f },
	m_FallDuration{ 0.3f },
	m_FallTimer{ 0.f },
	m_Gravity{ 9.81f },
	m_IsJumping{ false },
	m_IsFalling{ false },
	m_TriggersTiles{ triggersTiles },
	m_CurrentRow{ row },
	m_StartRow{ row },
	m_CurrentColumn{ column },
	m_StartColumn{ column },
	m_Direction{},
	m_RowOffset{ 0 },
	m_ColumnOffset{ 0 },
	m_EntityType{ type }

{

	m_HasAnimations = GetParent()->HasComponent<AnimationComponent>();
	if (m_HasAnimations)
	{
		GetParent()->GetComponent<AnimationComponent>()->SetAnimation(0);
		GetParent()->GetComponent<AnimationComponent>()->SetFrame(0);
	}
	if (GetParent()->HasComponent<PlayerComponent>())
	{
		m_EntityType = EntityType::Qbert;
	}
	m_InitPosition = GetParent()->GetComponent<TransformComponent>()->GetPosition();
}

void dae::MovementComponent::Jump(MovementDirection direction)
{
	if (m_IsJumping || GetParent()->HasComponent<TransformComponent>() == false)
		return;
	auto position = GetParent()->GetComponent<TransformComponent>()->GetPosition();
	auto newPos = position;
	float xTranslate{ 32.f }, yTranslate{ 48.f };
	m_StartPosition = { position.x,position.y };
	m_Direction = direction;

	switch (m_Direction)
	{
	case MovementComponent::MovementDirection::up_right:
		newPos.x += xTranslate;
		newPos.y -= yTranslate;

		break;
	case MovementComponent::MovementDirection::up_left:
		newPos.x -= xTranslate;
		newPos.y -= yTranslate;

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
	if (m_HasAnimations)
	{
		GetParent()->GetComponent<AnimationComponent>()->SetAnimation(static_cast<int>(m_Direction));
		GetParent()->GetComponent<AnimationComponent>()->NextFrame();
	}
	m_InitJumpVelocityX = (newPos.x - position.x) / m_JumpDuration;
	m_InitJumpVelocityY = -(-(newPos.y - position.y) + 0.5f * m_Gravity * m_JumpDuration * m_JumpDuration) / m_JumpDuration;
	m_JumpTimer = 0.f;
	if (m_IsJumping == false)
	{
		Audio* audio = &Locator::GetAudio();
		switch (m_EntityType)
		{
		case EntityType::Qbert:
			audio->PlaySound(Audio::AudioStruct{ 0,0.2f,{} });
			break;
		case EntityType::Coily:
			audio->PlaySound(Audio::AudioStruct{ 1,0.2f,{} });
			break;
		}


	}
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
			m_IsJumping = false;
			glm::vec2 targetPos;
			targetPos.x = m_StartPosition.x + m_JumpDuration * m_InitJumpVelocityX;
			targetPos.y = m_StartPosition.y + m_JumpDuration * m_InitJumpVelocityY;
			GetParent()->GetComponent<TransformComponent>()->SetPosition(targetPos.x, targetPos.y);
			if (m_HasAnimations)
			{
				GetParent()->GetComponent<AnimationComponent>()->NextFrame();

			}
			bool undoTiles = GetParent()->HasComponent<SlickSamComponent>();

			if (!m_pLevel->CheckOnTiles(m_CurrentRow, m_CurrentColumn, m_Direction, m_TriggersTiles, undoTiles, m_RowOffset, m_ColumnOffset))
			{
				m_IsFalling = true;
				GetParent()->SetPushToFront(true);
				if (m_EntityType == EntityType::Qbert)
				{
					GetParent()->GetComponent<PlayerComponent>()->KillPlayer();
				}
			}
			else
			{
				if (m_EntityType == EntityType::Qbert)
				{
					GetParent()->GetComponent<PlayerComponent>()->ChangeScore(25);
				}
			}
			return;
		}

		float newPosX = m_StartPosition.x + m_JumpTimer * m_InitJumpVelocityX;
		float newPosY = m_StartPosition.y + m_JumpTimer * m_InitJumpVelocityY + 0.5f * m_Gravity * m_JumpTimer * m_JumpTimer;

		GetParent()->GetComponent<TransformComponent>()->SetPosition(newPosX, newPosY);

	}
	if (m_IsFalling)
	{

		float deltaTime = TimeManager::GetInstance().GetDeltaTime();

		m_FallTimer += deltaTime;
		if (m_FallTimer > m_FallDuration)
		{
			m_FallTimer = m_FallDuration;
			m_IsFalling = false;

			GetParent()->SetPushToBack(true);
			ResetPosition();

		}

		auto pos = GetParent()->GetComponent<TransformComponent>()->GetPosition();
		if (m_EntityType == EntityType::Wrongway)
		{
			pos.x += m_Gravity * m_FallVelocity * deltaTime;
			pos.y -= m_Gravity * m_FallVelocity * deltaTime;
		}
		else if (m_EntityType == EntityType::Ugg)
		{
			pos.x -= m_Gravity * m_FallVelocity * deltaTime;
			pos.y -= m_Gravity * m_FallVelocity * deltaTime;
		}
		else
		{
			pos.y += m_Gravity * m_FallVelocity * deltaTime;

		}

		GetParent()->GetComponent<TransformComponent>()->SetPosition(pos.x, pos.y);
	}
}



void dae::MovementComponent::SetCurrentTile(const int row, const int column)
{
	m_CurrentRow = row;
	m_CurrentColumn = column;
}
void dae::MovementComponent::WrongwayJump(MovementDirection direction)
{

	m_EntityType = EntityType::Wrongway;
	if (m_IsJumping || GetParent()->HasComponent<TransformComponent>() == false || m_IsFalling)
		return;
	auto position = GetParent()->GetComponent<TransformComponent>()->GetPosition();
	auto newPos = position;
	float xTranslate{ 32.f }, yTranslate{ 48.f };
	m_StartPosition = { position.x,position.y };
	m_Direction = direction;


	switch (m_Direction)
	{
	case MovementComponent::MovementDirection::up_right:
		newPos.x += xTranslate;
		newPos.y -= yTranslate;
		break;
	case MovementComponent::MovementDirection::right:
		newPos.x += xTranslate * 2.f;

		break;
	}
	if (m_HasAnimations)
	{
		GetParent()->GetComponent<AnimationComponent>()->SetAnimation(static_cast<int>(m_Direction));
		GetParent()->GetComponent<AnimationComponent>()->NextFrame();
	}
	m_InitJumpVelocityX = (newPos.x - position.x) / m_JumpDuration;
	m_InitJumpVelocityY = -(-(newPos.y - position.y) + 0.5f * m_Gravity * m_JumpDuration * m_JumpDuration) / m_JumpDuration;
	m_JumpTimer = 0.f;
	m_IsJumping = true;
	//std::cout << m_InitJumpVelocityX << " - " << m_InitJumpVelocityY << std::endl;

}

void dae::MovementComponent::UggJump(MovementDirection direction)
{

	m_EntityType = EntityType::Ugg;
	if (m_IsJumping || GetParent()->HasComponent<TransformComponent>() == false || m_IsFalling)
		return;
	auto position = GetParent()->GetComponent<TransformComponent>()->GetPosition();
	auto newPos = position;
	float xTranslate{ 32.f }, yTranslate{ 48.f };
	m_StartPosition = { position.x,position.y };
	m_Direction = direction;


	switch (m_Direction)
	{
	case MovementComponent::MovementDirection::up_left:
		newPos.x -= xTranslate;
		newPos.y -= yTranslate;
		break;
	case MovementComponent::MovementDirection::left:
		newPos.x -= xTranslate * 2.f;

		break;
	}
	if (m_HasAnimations)
	{
		GetParent()->GetComponent<AnimationComponent>()->SetAnimation(static_cast<int>(m_Direction));
		GetParent()->GetComponent<AnimationComponent>()->NextFrame();
	}
	m_InitJumpVelocityX = (newPos.x - position.x) / m_JumpDuration;
	m_InitJumpVelocityY = -(-(newPos.y - position.y) + 0.5f * m_Gravity * m_JumpDuration * m_JumpDuration) / m_JumpDuration;
	m_JumpTimer = 0.f;
	m_IsJumping = true;
	//std::cout << m_InitJumpVelocityX << " - " << m_InitJumpVelocityY << std::endl;

}


void dae::MovementComponent::SetStartTile(const int row, const int column)
{
	m_StartRow = row;
	m_StartColumn = column;
}

void dae::MovementComponent::ResetPosition()
{
	ResetPosition(m_InitPosition.x, m_InitPosition.y);
}


void dae::MovementComponent::ResetPosition(const float x, const float y)
{
	GetParent()->GetComponent<TransformComponent>()->SetPosition(x, y);
	//std::cout << GetParent()->GetComponent<TransformComponent>()->GetPosition().x << " - " << GetParent()->GetComponent<TransformComponent>()->GetPosition().y << std::endl;
	m_CurrentRow = m_StartRow;
	m_CurrentColumn = m_StartColumn;
	m_IsJumping = false;
	m_IsFalling = false;
}

bool dae::MovementComponent::IsJumping() const
{
	return m_IsJumping;
}

void dae::MovementComponent::SetTileOffset(const int row, const int colum)
{
	m_RowOffset = row;
	m_ColumnOffset = colum;
}

bool dae::MovementComponent::IsOnTile(const int row, const int column)
{
	//std::cout << m_CurrentRow << " - " << m_CurrentColumn << std::endl;
	return m_CurrentRow == row && m_CurrentColumn == column;
}

int dae::MovementComponent::GetRow() const
{

	return m_CurrentRow;
}

int dae::MovementComponent::GetColumn() const
{
	return m_CurrentColumn;
}
