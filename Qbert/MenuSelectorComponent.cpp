#include "ImposterPCH.h"
#include "MenuSelectorComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Level.h"

dae::MenuSelectorComponent::MenuSelectorComponent(GameObject* pParent, Level* pLevel) :
	Component{ pParent },
	m_ButtonLocations{},
	m_CurrentButton{ 0 },
	m_pLevel{ pLevel }
{

}

void dae::MenuSelectorComponent::Update()
{
}

void dae::MenuSelectorComponent::AddButtonLocation(const glm::vec2& button)
{
	m_ButtonLocations.push_back(button);
}

glm::vec2  dae::MenuSelectorComponent::NextButton()
{
	m_CurrentButton++;
	if (m_CurrentButton >= (int)m_ButtonLocations.size())
	{
		m_CurrentButton = 0;
	}
	return m_ButtonLocations[m_CurrentButton];
}

glm::vec2 dae::MenuSelectorComponent::PreviousButton()
{
	m_CurrentButton--;
	if (m_CurrentButton < 0)
	{
		m_CurrentButton = (int)m_ButtonLocations.size() - 1;
	}
	
	return m_ButtonLocations[m_CurrentButton];
}

glm::vec2 dae::MenuSelectorComponent::GetCurrentButtonLocation() const
{
	return m_ButtonLocations[m_CurrentButton];
}

int dae::MenuSelectorComponent::GetCurrentSelection() const
{
	return m_CurrentButton;
}

void dae::MenuSelectorComponent::StartGame()
{
	m_pLevel->SetLevelMode(m_CurrentButton);

	SceneManager::GetInstance().SetCurrentScene(SceneManager::GetInstance().GetSceneByName("Game"));
}


void dae::MenuSelectorComponent::LoseGame()
{


	SceneManager::GetInstance().SetCurrentScene(SceneManager::GetInstance().GetSceneByName("Fail"));
}

void dae::MenuSelectorComponent::ResetGame()
{
	
	
	SceneManager::GetInstance().SetCurrentScene(SceneManager::GetInstance().GetSceneByName("Menu"));
}