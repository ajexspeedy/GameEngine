#include "ImposterPCH.h"
#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "../Qbert/MovementComponent.h"
#include "GameObject.h"






dae::RenderComponent::RenderComponent(GameObject* pParent, const std::string& filename) :
	Component{ pParent },
	m_UseSrcRect{ false }
{

	SetTexture(filename);

}


dae::RenderComponent::RenderComponent(GameObject* pParent, const std::string& filename, const SDL_Rect& srcRect) :
	Component{ pParent },
	m_UseSrcRect{ true },
	m_SrcRect{ srcRect }

{
	SetTexture(filename);
}


void dae::RenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{

		const auto pos = GetParent()->GetComponent<TransformComponent>()->GetPosition();
		const auto size = GetParent()->GetComponent<TransformComponent>()->GetSize();
		if (size.x != -1.f && size.y != -1.f)
		{
			SDL_Rect destRect;
			destRect.x = static_cast<int>(pos.x);
			destRect.y = static_cast<int>(pos.y);
			destRect.w = static_cast<int>(size.x);
			destRect.h = static_cast<int>(size.y);
			if (m_UseSrcRect)
			{

				Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, destRect);
			}
			else
			{


				Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, destRect.w, destRect.h);

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

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetEnableSrcRect(bool enable)
{
	m_UseSrcRect = enable;
}

void dae::RenderComponent::SetPosition(float x, float y)
{
	GetParent()->GetComponent<TransformComponent>()->SetPosition(x, y);


}

void dae::RenderComponent::Translate(float x, float y)
{
	auto newPos = GetParent()->GetComponent<TransformComponent>()->GetPosition();
	newPos.x += x;
	newPos.y += y;
	GetParent()->GetComponent<TransformComponent>()->SetPosition(newPos.x, newPos.y, 0.f);
}

void dae::RenderComponent::SetSrcRect(const int x, const int y, const int width, const int height)
{
	m_SrcRect = { x,y,width,height };
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

void dae::RenderComponent::SetSrcRectSize(const int width, const int height)
{
	m_SrcRect.w = width;
	m_SrcRect.h = height;
}




