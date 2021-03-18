#pragma once
#include "Observer.h"
#include "Component.h"

namespace dae
{
	class Font;
	class TextComponent;
	class PlayerLivesDisplay :
		public Observer, public Component
	{
	public:
		PlayerLivesDisplay(const std::shared_ptr<Font>& font, int lives, float x = 0.f, float y = 0.f);
		~PlayerLivesDisplay() = default;

		virtual void onNotify(const Event& event) override;
		virtual void Render() const override;
		void Update() override;

		PlayerLivesDisplay(const PlayerLivesDisplay& other) = delete;
		PlayerLivesDisplay(PlayerLivesDisplay&& other) = delete;
		PlayerLivesDisplay& operator=(const PlayerLivesDisplay& other) = delete;
		PlayerLivesDisplay& operator=(PlayerLivesDisplay&& other) = delete;
	private:
		int m_RemainingLives;
		bool m_UpdateLives{ false };
		std::unique_ptr<TextComponent> m_pTextComponent;

	};

}