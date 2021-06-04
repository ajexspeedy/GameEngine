#include "ImposterPCH.h"
#include "Subject.h"
#include "Observer.h"
#include "GameObject.h"



void dae::Subject::AddObserver(Observer* pObserver)
{
	
	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(Observer* pObserver)
{
	m_pObservers.erase(std::remove(begin(m_pObservers), end(m_pObservers), pObserver));
}

void dae::Subject::notify(const Event& event)
{
	for(auto& observer:m_pObservers)
	{
		
		observer->onNotify(event);
	}
}
