#pragma once
#include "Component.h"

class RenderComponent;
class Transform;
namespace dae
{
	class TileComponent : public Component
	{
	public:


	private:
		Transform* m_pTransform;
	};
}