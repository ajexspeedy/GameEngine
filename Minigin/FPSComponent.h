#pragma once
#include "TextComponent.h"

namespace dae
{
	class FPSComponent :
		public TextComponent
	{
	public:
		FPSComponent(const std::string& text, const std::shared_ptr<Font>& font);
		void Update() override;


		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	private:
		float m_FPSCooldown{ 0.f };
	};

}