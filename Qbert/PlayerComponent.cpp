#include "ImposterPCH.h"
#include "PlayerComponent.h"
#include "InputManager.h"
#include "KillCommand.h"
#include "ScoreCommand.h"
#include "GameObject.h"
#include "MenuSelectorComponent.h"


dae::PlayerComponent::PlayerComponent(GameObject* pParent, int lives) :
	Component{ pParent },
	m_Lives(lives),
	m_Score(0)
{



}



void dae::PlayerComponent::Update()
{
}



void dae::PlayerComponent::KillPlayer()
{
	m_Lives--;
	if (m_Lives <= 0)
	{
		m_Lives = 3;
		m_Score = 0;
		GetParent()->GetComponent<MenuSelectorComponent>()->LoseGame();
	}
	notify(Event("PlayerDead", new EventData<int>(m_Lives)));

}



void dae::PlayerComponent::ChangeScore(int value)
{
	if (GetParent() == nullptr)
		return;
	m_Score += value;
	notify(Event("PlayerScore", new EventData<int>(m_Score)));
}

