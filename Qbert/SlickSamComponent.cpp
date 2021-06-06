#include "ImposterPCH.h"
#include "GameObject.h"
#include "TimeManager.h"

#include "SlickSamComponent.h"
#include "MovementComponent.h"

dae::SlickSamComponent::SlickSamComponent(GameObject* pParent, const float spawnDuration, const float startPosX, const float startPosY) :
	Component{ pParent },
	m_SpawnEnabled{ true },
	m_JumpTimer{ 0.f },
	m_JumpDuration{ 0.3f },
	m_SpawnDuration{ spawnDuration },
	m_StartPosX{ startPosX },
	m_StartPosY{ startPosY }
{
}

void dae::SlickSamComponent::Update()
{


	if (m_SpawnEnabled)
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

		}
	}
	else
	{
		auto deltaTime = TimeManager::GetInstance().GetDeltaTime();
		m_SpawnTimer += deltaTime;
		if (m_SpawnTimer >= m_SpawnDuration)
		{
			m_SpawnEnabled = true;
		}
	}
}
