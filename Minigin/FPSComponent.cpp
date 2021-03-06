#include "ImposterPCH.h"
#include "FPSComponent.h"
#include "TimeManager.h"


dae::FPSComponent::FPSComponent(GameObject* pParent, const std::string& text, const std::shared_ptr<Font>& font):
	TextComponent(pParent,text,font)
{
	
}


void dae::FPSComponent::Update()
{
	if (m_FPSCooldown <= 0.f)
	{
		SetText("FPS: " + std::to_string(int(TimeManager::GetInstance().GetFPS())));
		m_FPSCooldown = 1.f;
	}
	m_FPSCooldown -= TimeManager::GetInstance().GetDeltaTime();
	UpdateTexture();
}
