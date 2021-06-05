#include "ImposterPCH.h"
#include "GameObject.h"

#include "SlickSamComponent.h"

dae::SlickSamComponent::SlickSamComponent(GameObject* pParent, GameObject* pPlayer, const float startPosX, const float startPosY):
	Component{pParent},
	m_pPlayer{pPlayer}
{
}

void dae::SlickSamComponent::Update()
{
}
