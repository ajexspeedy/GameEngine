#pragma once
#include "RenderComponent.h"


namespace dae
{

	class GameObject;
	class AnimationComponent : public RenderComponent
	{
	public:
		AnimationComponent(GameObject* pParent, const int nrAnimations, const int nrFrames, const std::string& fileName, const SDL_Rect& srcRect);
		~AnimationComponent() = default;


		virtual void Update() override;
	

		void NextFrame();
		void SetFrame(int frame);
		void SetAnimation(int animation);


		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;

	protected:
		void UpdateSrcRect();
		int m_NrAnimations, m_CurrentAnimation;
		int m_NrFrames, m_CurrentFrame;


	};

}