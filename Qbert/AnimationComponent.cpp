#include "ImposterPCH.h"
#include "AnimationComponent.h"
#include "GameObject.h"

dae::AnimationComponent::AnimationComponent(GameObject* pParent, const int nrAnimations, const int nrFrames, const std::string& fileName, const SDL_Rect& srcRect, const int widthDestRect, const int heightDestRect) :
	RenderComponent{ pParent,fileName,srcRect,widthDestRect,heightDestRect },
	m_NrAnimations{ nrAnimations },
	m_CurrentAnimation{ 0 },
	m_NrFrames{ nrFrames },
	m_CurrentFrame{ 0 }
{
}

void dae::AnimationComponent::Update()
{

}


void dae::AnimationComponent::NextFrame()
{
	++m_CurrentFrame;
	if (m_CurrentFrame >= m_NrFrames)
	{
		m_CurrentFrame = 0;
	}
	UpdateSrcRect();
	// std::cout << m_CurrentFrame << " - " << m_NrFrames << std::endl;
}

void dae::AnimationComponent::SetFrame(int frame)
{
	if (frame >= 0 && frame < m_NrFrames)
	{
		m_CurrentFrame = frame;
		UpdateSrcRect();
	}
}

void dae::AnimationComponent::SetAnimation(int animation)
{
	if (animation >= 0 && animation < m_NrAnimations)
	{
		m_CurrentAnimation = animation;
		UpdateSrcRect();
	}
}

void dae::AnimationComponent::UpdateSrcRect()
{
	int newSrcRectX = (m_CurrentAnimation * m_NrFrames + m_CurrentFrame);
	//if (GetParent()->GetName() == "Qbert")
	//{
	//	std::cout << m_CurrentFrame << std::endl;
	//	if (newSrcRectX > m_NrFrames * m_NrAnimations)
	//		std::cout << newSrcRectX << std::endl;
	//}

	MoveSrcRectPosition(newSrcRectX, 0);
}
