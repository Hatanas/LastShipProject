#pragma once

#include "Subject.h"

template<typename NotificationID>
class Subject;

template<typename NotificationID>
class Observer
{
public:
	virtual void update(Subject<NotificationID> *subject, NotificationID id) = 0;
	Observer(){}
	virtual ~Observer(){}
};

