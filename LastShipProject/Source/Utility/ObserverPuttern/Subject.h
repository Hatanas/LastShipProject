#pragma once

#include <list>
#include <algorithm>
#include "Observer.h"

template<typename NotificationID>
class Observer;


template<typename NotificationID>
class Subject
{
protected:
	typedef std::list<Observer<NotificationID> *> Observers;
	Observers ObserversList;
	NotificationID notificationID;
public:
	virtual void notify()
	{
		auto update = [](Observers::value_type observer)
		{
			observer->update(this, notificationID);
		};

		std::for_each(ObserversList.begin(), ObserversList.end(), update);
	}
	virtual void registerObserver(Observer<NotificationID> *observer)
	{
		ObserverList.push_back(observer);
	}
	virtual void unregisterObserver(Observer<NotificationID> *observer)
	{
		ObserverList.remove(observer);
	}
	Subject(){}
	virtual ~Subject(){}
};

