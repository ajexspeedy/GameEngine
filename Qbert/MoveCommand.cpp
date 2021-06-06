#include "ImposterPCH.h"
#include "MoveCommand.h"



dae::MovementCommand::MovementCommand(MovementComponent* pMovementComponent, MovementComponent::MovementDirection direction):
	m_pMovementComponent{pMovementComponent},
	m_Direction{direction}
{
}

void dae::MovementCommand::Execute()
{
	m_pMovementComponent->Jump(m_Direction);
	//TODO: Jump here
	

}
