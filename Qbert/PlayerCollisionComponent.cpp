#include "ImposterPCH.h"
#include "PlayerCollisionComponent.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "MovementComponent.h"
#include "SlickSamComponent.h"

#include "GameObject.h"


dae::PlayerCollisionComponent::PlayerCollisionComponent(GameObject* pParent):
	Component{pParent},
	m_pEnemies{}
{
}

dae::PlayerCollisionComponent::~PlayerCollisionComponent()
{
	m_pEnemies.clear();
}

void dae::PlayerCollisionComponent::Update()
{

	for (auto enemy : m_pEnemies)
	{
		if (IsColliding(enemy))
		{
			if (enemy->HasComponent<SlickSamComponent>())
			{
				
				std::cout << "Slick n sam" << std::endl;
				break;
			}
			GetParent()->GetComponent<PlayerComponent>()->KillPlayer();
			GetParent()->GetComponent<MovementComponent>()->ResetPosition();
		}
	}
}

void dae::PlayerCollisionComponent::AddEnemy(GameObject* pEnemy)
{
	m_pEnemies.push_back(pEnemy);
}

bool dae::PlayerCollisionComponent::IsColliding(GameObject* pEnemy)
{
	int enemyColumn{ pEnemy->GetComponent<MovementComponent>()->GetColumn() }, playerColumn{ GetParent()->GetComponent<MovementComponent>()->GetColumn() };

	
	
	// Z = width, W = height
	auto enemyRect = pEnemy->GetComponent<TransformComponent>()->GetRect();
	auto playerRect = GetParent()->GetComponent<TransformComponent>()->GetRect();

	// 1 rect left to the other
	if (enemyRect.x + enemyRect.z < playerRect.x || playerRect.x + playerRect.z < enemyRect.x)
	{
		return false;
	}
	// 1 rect under the other
	if (enemyRect.y > playerRect.y + playerRect.w || playerRect.y > enemyRect.y + enemyRect.w)
	{
		return false;
	}
	if (enemyColumn != playerColumn)
	{
		//std::cout << enemyColumn << " - " << playerColumn << std::endl;
		return false;
	}
	
	return true;
}
