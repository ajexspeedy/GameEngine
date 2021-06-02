#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop) // This pop somehow allows the warning to not be ignored? 


namespace dae
{
	class Transform final
	{
	public:
		Transform(const float x, const float y, const float z);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
