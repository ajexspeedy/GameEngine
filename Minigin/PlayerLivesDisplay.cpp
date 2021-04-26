#include "ImposterPCH.h"
#include "PlayerLivesDisplay.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Font.h"

dae::PlayerLivesDisplay::PlayerLivesDisplay(const std::shared_ptr<Font>& font, int lives, float x, float y) :
	m_RemainingLives(lives),
	m_UpdateLives(false)
{
	std::string text = "Remaining lives: ";
	text += std::to_string(lives);
	m_pTextComponent = std::make_unique<TextComponent>(text, font);
	m_pTextComponent->SetPosition(x, y);
}

void dae::PlayerLivesDisplay::onNotify(const Event& event)
{
	if (event.Message == "PlayerDead")
	{
		m_RemainingLives = static_cast<EventData<int>*>(event.pEventData)->data;
		std::string text = "Remaining lives: ";
		text += (std::to_string(m_RemainingLives));
		m_pTextComponent->SetText(text);
		m_UpdateLives = true;
	}
}

void dae::PlayerLivesDisplay::Render() const
{
	m_pTextComponent->Render();
}

void dae::PlayerLivesDisplay::Update()
{
	if (m_UpdateLives)
	{
		m_pTextComponent->Update();
		m_UpdateLives = false;
	}
}

