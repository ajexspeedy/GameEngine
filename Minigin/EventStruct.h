#pragma once
#include <string>

struct IEventData
{
};

struct Event
{
	Event(const std::string& message) :Message(message), pEventData(nullptr) {};
	Event(const std::string& message, IEventData* eventData) :Message(message), pEventData(eventData) {};
	~Event()
	{
		delete pEventData;
		pEventData = nullptr;
	};

	std::string Message;
	IEventData* pEventData;
};

template<typename T>
struct EventData :public IEventData
{
	explicit EventData(T data) :
		data(data)
	{
	}
	T data;
};