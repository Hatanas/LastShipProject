#pragma once
#include <mutex>
#include <memory>

template<class T>
class Singleton
{
private:
	static std::unique_ptr<T> instance_m;
	static std::once_flag flag_m;
protected:
	Singleton() {}
public:
	~Singleton() {}
private:
	Singleton(const Singleton &) = delete;
	Singleton& operator=(const Singleton &) = delete;
	Singleton(Singleton &&) = delete;
	Singleton& operator=(Singleton &&) = delete;
public:
	static T &instance()
	{
		auto create = []() { instance_m = std::make_unique<T>(); };
		std::call_once(flag_m, create);
		return *instance_m;
	}
};

template<class T>
std::unique_ptr<T> Singleton<T>::instance_m;

template<class T>
std::once_flag Singleton<T>::flag_m;

/*
class SingletonHolder
{
public:
	struct t
	{
		std::string data;
	};
public:
	typedef Singleton<t> T;
};

typedef SingletonHolder::T T;
*/