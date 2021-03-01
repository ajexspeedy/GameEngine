#include "MiniginPCH.h"
#include "PlayerScoreDisplay.h"
#include "TextComponent.h"
#include "Font.h"

dae::PlayerScoreDisplay::PlayerScoreDisplay(const std::shared_ptr<Font>& font, float x, float y)
{
	m_pTextComponent = new TextComponent("Score: 0", font);
	m_pTextComponent->SetPosition(x, y);
}

void dae::PlayerScoreDisplay::onNotify(const Event& event)
{
	if (event.Message == "PlayerScore")
	{
		ColorScore color = static_cast<EventData<ColorScore>*>(event.pEventData)->data;
		m_Score = static_cast<int>(color);
		std::string scoreText{ "Score: " };
		scoreText += std::to_string(m_Score);
		m_pTextComponent->SetText(scoreText);
		m_UpdateScore = true;
	}
}

void dae::PlayerScoreDisplay::Render() const
{
	m_pTextComponent->Render();
}

void dae::PlayerScoreDisplay::Update()
{
	if(m_UpdateScore)
	{
		m_pTextComponent->Update();
		m_UpdateScore = false;
	}
}
