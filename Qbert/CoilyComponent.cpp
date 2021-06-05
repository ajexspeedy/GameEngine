#include "ImposterPCH.h"
#include "GameObject.h"

#include "CoilyComponent.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

#include "TimeManager.h"


dae::CoilyComponent::CoilyComponent(GameObject* pParent,GameObject* pPlayer , const float spawnDuration, const float startPosX, const float startPosY) :
	Component{ pParent },
	m_SpawnTimer{ 0.f },
	m_SpawnDuration{ spawnDuration },
	m_FallVelocity{ 500.f },
	m_StartPositionX{ startPosX },
	m_StartPositionY{ startPosY },
	m_JumpTimer{ 0.f },
	m_JumpDuration{ 0.5f },
	m_SnakeWidth{ 16 },
	m_SnakeHeight{ 32 },
	m_Form{ CoilyForm::egg },
	m_SpawnEnabled{ false },
	m_IsSpawned{ false },
	m_IsFalling{ false },
	m_IsActive{ false },
	m_EggJumpCounter{ 0 },
	m_MaxEggJumps{ 7 },
	m_pPlayer{pPlayer}
{

	SetSpawnEnabled(true);

}



void dae::CoilyComponent::Update()
{

	if (m_EggJumpCounter >= m_MaxEggJumps && m_Form == CoilyForm::egg)
	{
		float snakeHeightDif = 35.f;
		m_StartPositionY -= snakeHeightDif;
		m_Form = CoilyForm::snake;
		auto pos = GetParent()->GetComponent<TransformComponent>()->GetPosition();
		GetParent()->GetComponent<MovementComponent>()->ResetPosition(m_StartPositionX, m_StartPositionY);
		GetParent()->GetComponent<AnimationComponent>()->SetTexture("Textures/Coily_Snake.png");
		GetParent()->GetComponent<AnimationComponent>()->SetSrcRectSize(m_SnakeWidth, m_SnakeHeight);
		GetParent()->GetComponent<TransformComponent>()->SetSize(m_SnakeWidth * 2.f, m_SnakeHeight * 2.f);
		GetParent()->GetComponent<AnimationComponent>()->SetFrame(0);

	}
	CheckSpawnEgg();
	CheckEggFalling();
	CheckCoilyMovement();

}

void dae::CoilyComponent::SetSpawnEnabled(bool enable)
{
	m_SpawnEnabled = enable;
}

bool dae::CoilyComponent::GetSpawnEnabled() const
{
	return m_SpawnEnabled;
}

void dae::CoilyComponent::CheckSpawnEgg()
{
	if (m_SpawnEnabled)
	{
		float deltaTime = TimeManager::GetInstance().GetDeltaTime();
		m_SpawnTimer += deltaTime;
		if (m_SpawnTimer >= m_SpawnDuration)
		{
			m_SpawnEnabled = false;
			SpawnEgg();

		}

	}

}

void dae::CoilyComponent::CheckEggFalling()
{
	if (m_IsSpawned && m_IsFalling)
	{
		float deltaTime = TimeManager::GetInstance().GetDeltaTime();
		GetParent()->GetComponent<TransformComponent>()->Translate(0.f, m_FallVelocity * deltaTime);
		auto pos = GetParent()->GetComponent<TransformComponent>()->GetPosition();
		if (pos.y > m_StartPositionY)
		{
			GetParent()->GetComponent<TransformComponent>()->SetPosition(pos.x, m_StartPositionY, pos.y);
			m_IsFalling = false;
			m_IsActive = true;
		}
	}
}

void dae::CoilyComponent::CheckCoilyMovement()
{
	if (m_IsActive)
	{
		switch (m_Form)
		{
		case dae::CoilyComponent::CoilyForm::egg:
			JumpEgg();
			break;
		case dae::CoilyComponent::CoilyForm::snake:
			JumpSnake();
			break;
		default:
			std::cout << "Error Coily: undefined coily form!" << std::endl;
			break;
		}


	}

}

void dae::CoilyComponent::SpawnEgg()
{
	m_IsSpawned = true;
	m_IsFalling = true;
	m_SpawnTimer = 0.f;



}

void dae::CoilyComponent::JumpEgg()
{
	
	auto deltaTime = TimeManager::GetInstance().GetDeltaTime();
	m_JumpTimer += deltaTime;
	if (m_JumpTimer > m_JumpDuration)
	{
		MovementComponent::MovementDirection direction;
		m_JumpTimer = 0.f;
		int rando = rand() % 10 + 1;
		if (rando <= 5)
		{
			direction = MovementComponent::MovementDirection::down_left;
		}
		else
		{
			direction = MovementComponent::MovementDirection::down_right;
		}
		GetParent()->GetComponent<MovementComponent>()->Jump(direction);
		m_EggJumpCounter++;
	}
}

void dae::CoilyComponent::JumpSnake()
{

	auto deltaTime = TimeManager::GetInstance().GetDeltaTime();
	m_JumpTimer += deltaTime;
	if (m_JumpTimer > m_JumpDuration)
	{
		m_JumpTimer = 0.f;
		auto posPlayer = m_pPlayer->GetComponent<TransformComponent>()->GetPosition();
		auto posCoily = GetParent()->GetComponent<TransformComponent>()->GetPosition();
		auto diff = posPlayer - posCoily;
		MovementComponent::MovementDirection direction;
		if (diff.x <= 0.f) // also when on the same xValue
		{
			if (diff.y <= 0.f)
			{
				direction = MovementComponent::MovementDirection::up_left;
			}
			else
			{
				direction = MovementComponent::MovementDirection::down_left;
			}
		}
		else
		{
			if (diff.y <= 0.f)
			{
				direction = MovementComponent::MovementDirection::up_right;
			}
			else
			{
				direction = MovementComponent::MovementDirection::down_right;
			}
		}
		GetParent()->GetComponent<MovementComponent>()->Jump(direction);
		//std::cout << GetParent()->GetComponent<MovementComponent>()->GetColumn() << std::endl;
		return;
		
	}
}



