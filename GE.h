#pragma once

// 单例设计模式
#define SINGLETON(CLASS) \
private: \
	CLASS(){Init();}; \
	CLASS& operator = (const CLASS& t) = delete; \
	CLASS(const CLASS &) = delete; \
	static CLASS m_pInstance;\
	static std::mutex m_Mutex;\
public: \
	static CLASS* GetInstance() \
	{ \
		return &m_pInstance;\
	};

#define SET_SINGLETON(CLASS) \
CLASS CLASS::m_pInstance;\
std::mutex CLASS::m_Mutex;

#define Py_RETURN_NONE return Py_INCREF(Py_None), Py_None

#define print(x) std::cout << x << std::endl

#define BAN_COPY(CLASS)\
	CLASS& operator = (const CLASS& t) = delete; \
	CLASS(const CLASS &) = delete; \



