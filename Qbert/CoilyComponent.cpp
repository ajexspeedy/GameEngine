#include "ImposterPCH.h"
#include "GameObject.h"

#include "CoilyComponent.h"
#include "TransformComponent.h"

#include "TimeManager.h"


dae::CoilyComponent::CoilyComponent(GameObject* pParent, GameObject* pPlayer, const float spawnDuration) :
	Component{ pParent },
	m_SpawnTimer{ 0.f },
	m_SpawnDuration{ spawnDuration },
	m_FallTimer{ 0.f },
	m_FallDuration{ 3.f },
	m_FallVelocity{ 40.f },
	m_Form{ CoilyForm::egg },
	m_SpawnEnabled{ false },
	m_IsSpawned{ false },
	m_IsFalling{ false },
	m_pPlayer{ pPlayer }
{

	SetSpawnEnabled(true);

}



void dae::CoilyComponent::Update()
{
	if (m_IsSpawned && m_IsFalling)
	{
		float deltaTime = TimeManager::GetInstance().GetDeltaTime();
		m_FallTimer += deltaTime;
		if (m_FallTimer > m_FallDuration)
		{
			m_FallTimer = m_FallDuration;
			m_IsFalling = false;

		}
		auto pos = GetParent()->GetComponent<TransformComponent>()->GetPosition();
		std::cout << pos.x << " - " << pos.y << std::endl;

	}
	if (m_SpawnEnabled)
	{
		float deltaTime = TimeManager::GetInstance().GetDeltaTime();
		m_SpawnTimer += deltaTime;
		if (m_SpawnTimer >= m_SpawnDuration)
		{
			m_SpawnEnabled = false;
			SpawnEgg();
			return;
		}

	}
}

void dae::CoilyComponent::SetSpawnEnabled(bool enable)
{
	m_SpawnEnabled = enable;
}

bool dae::CoilyComponent::GetSpawnEnabled() const
{
	return m_SpawnEnabled;
}

void dae::CoilyComponent::SpawnEgg()
{
	m_IsSpawned = true;
	m_IsFalling = true;
	m_SpawnTimer = 0.f;



}



