#include "ImposterPCH.h"
#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
using namespace dae;



RenderComponent::RenderComponent(const std::string& filename, const float x, const float y) :
	m_UseSrcRect{ false },
	m_Width{ -1.f },
	m_Height{ -1.f }
{
	m_pTransform = new Transform{};
	SetTexture(filename);
	SetPosition(x, y);
}

dae::RenderComponent::RenderComponent(const std::string& filename, const float width, const float height, const float x, const float y) :
	m_UseSrcRect{ false },
	m_Width{ width },
	m_Height{ height }
{
	m_pTransform = new Transform{};
	SetTexture(filename);
	SetPosition(x, y);

}


void RenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		
		const auto pos = m_pTransform->GetPosition();
		if (m_Width != -1.f && m_Height != -1.f)
		{
			SDL_Rect destRect;
			destRect.x = static_cast<int>(pos.x);
			destRect.y = static_cast<int>(pos.y);
			destRect.w = static_cast<int>(m_Width);
			destRect.h = static_cast<int>(m_Height);
			if (m_UseSrcRect)
			{

				Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, destRect);
			}
			else
			{


				Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Width, m_Height);

			}
		}
		else
		{
			if (m_UseSrcRect)
			{
				Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, pos.x, pos.y);
			}
			else
			{
				Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
			}
		}



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
	m_pTransform->SetPosition(x, y, 0.0f);

}

void dae::RenderComponent::Translate(float x, float y)
{
	auto newPos = m_pTransform->GetPosition();
	newPos.x += x;
	newPos.y += y;
	m_pTransform->SetPosition(newPos.x, newPos.y, 0.f);
}

void dae::RenderComponent::SetSrcRect(float x, float y, float width, float height)
{

	m_SrcRect.x = static_cast<int>(x);
	m_SrcRect.y = static_cast<int>(y);
	m_SrcRect.w = static_cast<int>(width);
	m_SrcRect.h = static_cast<int>(height);
	m_UseSrcRect = true;
}

void dae::RenderComponent::SetSrcRect(const SDL_Rect& srcRect)
{
	m_SrcRect = srcRect;
	m_UseSrcRect = true;
}

void dae::RenderComponent::SetSrcRectPosition(int x, int y)
{
	m_SrcRect.x = x;
	m_SrcRect.y = y;
}

void dae::RenderComponent::MoveSrcRectPosition(int x, int y)
{
	int newX = x * m_SrcRect.w;
	int newY = y * m_SrcRect.h;
	SetSrcRectPosition(newX, newY);
}

Transform* dae::RenderComponent::GetTransform() const
{

	return m_pTransform;
}

