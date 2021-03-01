#pragma once
#include "EventStruct.h"

namespace dae
{
	class Observer abstract
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		virtual void onNotify(const Event& event) = 0;
	

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
		
	};
}
