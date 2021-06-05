#include "ImposterPCH.h"
#include "GameObject.h"

#include "TimeManager.h"

#include "UggWrongwayComponent.h"
#include "MovementComponent.h"

dae::UggWrongwayComponent::UggWrongwayComponent(GameObject* pParent, UggWrongwayForm form, const float startPosX, const float startPosY) :
	Component{ pParent },
	m_SpawnEnabled{ true },
	m_StartPosX{ startPosX },
	m_StartPosY{ startPosY },
	m_JumpTimer{ 0.f },
	m_JumpDuration{ 0.5f },
	m_Form{ form }
{
	
	if (m_Form == UggWrongwayForm::wrongway)
	{
		GetParent()->GetComponent<MovementComponent>()->SetTileOffset(0, +1);
	}
	else
	{
		GetParent()->GetComponent<MovementComponent>()->SetTileOffset(-1, +1);
	}
}

void dae::UggWrongwayComponent::Update()
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
			if (m_Form == UggWrongwayComponent::UggWrongwayForm::wrongway)
			{
				if (rando <= 5)
				{
					direction = MovementComponent::MovementDirection::up_right;
				}
				else
				{
					direction = MovementComponent::MovementDirection::right;
				}
				GetParent()->GetComponent<MovementComponent>()->WrongwayJump(direction);
			}
			else
			{
				if (rando <= 5)
				{
					direction = MovementComponent::MovementDirection::up_left;
				}
				else
				{
					direction = MovementComponent::MovementDirection::left;
				}
				GetParent()->GetComponent<MovementComponent>()->UggJump(direction);
			}

			
		}
	}
}
