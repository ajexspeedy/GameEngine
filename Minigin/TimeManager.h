#pragma once
#include <chrono>
#include "Singleton.h"

namespace dae
{

	class TimeManager : public Singleton<TimeManager>
	{
	public:

		void CalculateDeltaTime();
		
		float GetDeltaTime() const;
		float GetFPS() const;
		
	
	private:
		friend class Singleton<TimeManager>;
		TimeManager() = default;

		using clock = std::chrono::steady_clock::time_point;
		clock m_LastTime = std::chrono::high_resolution_clock::now(); // default value
		clock m_CurrentTime = {};
		float m_DeltaTime = {};
		
	};
}
