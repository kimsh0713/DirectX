#pragma once
template<typename T>
class st
{
public:
	static T* p;
	static T* G()
	{
		if (!p)
			p = new T;
		return p;
	}
	static void D()
	{
		delete p;
		p = nullptr;
	}
};

template <typename T>
T* st<T>::p = nullptr;