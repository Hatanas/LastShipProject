#pragma once

#include <set>
#include <algorithm>


template<typename M>
class Observer
{
public:
	virtual void update(M message) = 0; 
	Observer(){}
	virtual ~Observer(){}
};


class BaseSubject
{
private:
	bool hasChanged_m;
protected:
	bool hasChanged() const;
	void setChanged();
	void clearChanged();
public:
	BaseSubject() {}
	virtual ~BaseSubject() {}
};

inline bool BaseSubject::hasChanged() const { return hasChanged_m; }

inline void BaseSubject::setChanged() { hasChanged_m = true; }

inline void BaseSubject::clearChanged() { hasChanged_m = false; }


template<typename M>
class Subject : public BaseSubject
{
protected:
	std::set<Observer<M>*> observers;
public:
	void attach(Observer<M>*observer);
	void dettach(Observer<M>*observer);
	void notify(M message);
	Subject() {}
	virtual ~Subject() {}
};

template<typename M>
inline void Subject<M>::notify(M message)
{
	if(hasChanged()) {
		auto update = [message](Observer<M>*observer)
		{
			if(observer != nullptr) {
				observer->update(message);
			}
		};
		std::for_each(observers.begin(), observers.end(), update);
	}
	clearChanged();
}

template<typename M>
inline void Subject<M>::attach(Observer<M>*observer)
{
	if(observer != nullptr) {
		observers.insert(observer);
	}
}

template<typename M>
inline void Subject<M>::dettach(Observer<M>*observer)
{
	observers.erase(observer);
}
