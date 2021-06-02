#include "ImposterPCH.h"
#include "Component.h"
#include "GameObject.h"

dae::Component::Component(GameObject* pParent):
	m_pParent{pParent}
{
}

dae::GameObject* dae::Component::GetParent() const
{
	return m_pParent;
}
