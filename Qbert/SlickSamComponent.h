#pragma once
#include "Component.h"
#include "Subject.h"
#include "PlayerLivesDisplay.h"
#include "Observer.h"


namespace dae
{
	class TextComponent;
	class GameObject;
	class SlickSamComponent : public Component
	{
	public:
		enum class SlickSamForm
		{
			slick,
			sam
		};
		SlickSamComponent(GameObject* pParent, GameObject* pPlayer, const float startPosX = 0.f, const float startPosY = 0.f);
		~SlickSamComponent() = default;


		virtual void Update() override;

	

		SlickSamComponent(const SlickSamComponent& other) = delete;
		SlickSamComponent(SlickSamComponent&& other) = delete;
		SlickSamComponent& operator=(const SlickSamComponent& other) = delete;
		SlickSamComponent& operator=(SlickSamComponent&& other) = delete;

	protected:
		

		
		GameObject* m_pPlayer;
	};

}