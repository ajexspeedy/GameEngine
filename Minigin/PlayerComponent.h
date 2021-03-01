#pragma once
#include "Component.h"
#include "Subject.h"
#include "PlayerLivesDisplay.h"
#include "Observer.h"
#include "Subject.h"

namespace dae
{
	class TextComponent;
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent(int health = 0,int lives = 3);
		~PlayerComponent() = default;
		virtual void Update() override;
	

		void ChangeHealth(int value);
		void ChangeScore(int value);

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

	protected:
		int m_Health;
		int m_Lives;
		int m_Score;
	};

}