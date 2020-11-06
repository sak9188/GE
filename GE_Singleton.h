#pragma once

template<class T>
class GE_Singleton
{
public:
	static void		New() { instance = new T; }
	static void		Delete() { if (instance) { delete instance; instance = NULL; }; }
	static T*		Instance(void) { return instance; }

protected:
	GE_Singleton(void) {}
	~GE_Singleton(void) {}

protected:
	static T* instance;
};

template<class T>
T* GE_Singleton<T>::instance;
