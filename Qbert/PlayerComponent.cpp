#include "ImposterPCH.h"
#include "PlayerComponent.h"
#include "InputManager.h"
#include "KillCommand.h"
#include "ScoreCommand.h"
#include "GameObject.h"



dae::PlayerComponent::PlayerComponent(GameObject* pParent, int health, int lives) :
	Component{ pParent },
	m_Health(health),
	m_Lives(lives),
	m_Score(0)
{



}



void dae::PlayerComponent::Update()
{
}



void dae::PlayerComponent::ChangeHealth(int value)
{
	m_Health += value;
	if (m_Health <= 0)
	{
		if (m_Lives == 0)
		{
			m_Health = 0;
		}
		else
		{
			m_Lives--;
			notify(Event("PlayerDead", new EventData<int>(m_Lives)));
			m_Health = 1;
		}
	}
}

void dae::PlayerComponent::ChangeScore(int value)
{
	m_Score += value;
	notify(Event("PlayerScore", new EventData<int>(m_Score)));
}

