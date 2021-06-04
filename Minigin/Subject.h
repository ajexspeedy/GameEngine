#pragma once
#include "EventStruct.h"
#include <vector>
#include "Observer.h"


namespace dae
{

	class Observer;
	class Subject
	{
	public:
		Subject() = default;
		~Subject() = default;
		
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);



	protected:
		void notify(const Event& event);


	private:

		std::vector<Observer*> m_pObservers;


	};

}
