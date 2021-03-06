﻿#include "ImposterPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TransformComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Font.h"

dae::TextComponent::TextComponent(GameObject* pParent, const std::string& text, const std::shared_ptr<Font>& font) :
	Component{ pParent },
	m_NeedsUpdate(true),
	m_Text{ text },
	m_Font{ font }
{
	UpdateTexture();
}





void dae::TextComponent::Update()
{

	UpdateTexture();
}

void dae::TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = GetParent()->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	if (text != m_Text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}
}

void dae::TextComponent::SetPosition(float x, float y)
{
	GetParent()->GetComponent<TransformComponent>()->SetPosition(x, y, 0.0f);
}

void dae::TextComponent::UpdateTexture()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}
