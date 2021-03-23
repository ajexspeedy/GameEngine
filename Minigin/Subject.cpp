#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"
#include "GameObject.h"



void dae::Subject::AddObserver(std::shared_ptr<Observer> observer)
{
	
	m_pObservers.push_back(observer);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_pObservers.erase(std::remove(begin(m_pObservers), end(m_pObservers), observer));
}

void dae::Subject::notify(const Event& event)
{
	for(auto& observer:m_pObservers)
	{
		
		observer->onNotify(event);
	}
}
