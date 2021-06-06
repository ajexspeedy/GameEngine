#include "ImposterPCH.h"
#include "MenuSelectCommand.h"
#include "MenuSelectorComponent.h"
#include "SceneManager.h"

dae::MenuSelectCommand::MenuSelectCommand(MenuSelectorComponent* menuSelector, MenuMovement movement) :
	m_MenuSelector{ menuSelector },
	m_Movement{ movement }
{
}

void dae::MenuSelectCommand::Execute()
{
	if (SceneManager::GetInstance().GetSceneByName("Game") == SceneManager::GetInstance().GetCurrentSceneIndex())
	{
		return;
	}
	switch (m_Movement)
	{
	case dae::MenuSelectCommand::MenuMovement::down:
		
		m_MenuSelector->GetParent()->GetComponent<TransformComponent>()->SetPosition(m_MenuSelector->NextButton()); ;
		break;
	case dae::MenuSelectCommand::MenuMovement::up:
		m_MenuSelector->GetParent()->GetComponent<TransformComponent>()->SetPosition(m_MenuSelector->PreviousButton()); ;
		break;
	case dae::MenuSelectCommand::MenuMovement::select:
		if (SceneManager::GetInstance().GetSceneByName("Fail") == SceneManager::GetInstance().GetCurrentSceneIndex())
		{
			m_MenuSelector->ResetGame();
		}
		else 
		{
			m_MenuSelector->StartGame(); 
		}
		break;
	default:
		break;
	}
}
