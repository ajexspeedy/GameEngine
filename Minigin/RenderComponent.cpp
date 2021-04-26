#include "ImposterPCH.h"
#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
using namespace dae;

RenderComponent::RenderComponent(const std::string& filename, const float x, const float y)
{
	SetTexture(filename);
	SetPosition(x, y);
}


void RenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{

		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::RenderComponent::Update()
{
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
