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
		
		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);



	protected:
		void notify(const Event& event);


	private:

		std::vector<std::shared_ptr<Observer>> m_pObservers;


	};

}
