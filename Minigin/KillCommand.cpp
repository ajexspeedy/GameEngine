#include "MiniginPCH.h"
#include "KillCommand.h"


dae::KillCommand::KillCommand(std::shared_ptr<PlayerComponent> component) :
	m_pPlayerComponent(component)
{

}

void dae::KillCommand::Execute()
{
	m_pPlayerComponent->ChangeHealth(-1);
	
	
}
