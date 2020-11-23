#pragma once

namespace GE
{
	template<class T>
	class Singleton
	{
	public:
		static void		New() { instance = new T; }
		static void		Delete() { if (instance) { delete instance; instance = NULL; }; }
		static T*		Instance(void) { return instance; }

	protected:
		Singleton(void) {}
		~Singleton(void) {}

	protected:
		static T* instance;
	};

	template<class T>
	T* Singleton<T>::instance;
}
