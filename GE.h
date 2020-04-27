#pragma once

// 单例设计模式
#define SINGLETON(CLASS) \
private: \
	CLASS(){Init();}; \
	~CLASS(){}; \
	CLASS& operator = (const CLASS& t) = delete; \
	CLASS(const CLASS &) = delete; \
	static std::shared_ptr<CLASS> m_pInstance;\
	static std::mutex m_Mutex;\
public: \
	static std::shared_ptr<CLASS> GetInstance() \
	{ \
		if (!m_pInstance) \
		{ \
			std::lock_guard<std::mutex> gLock(m_Mutex); \
			if (nullptr == m_pInstance) \
			{\
				m_pInstance = std::make_shared<CLASS>();\
			}\
		}\
		return m_pInstance;\
	}; \
private:

#define SET_SINGLETON(CLASS) \
std::shared_ptr<CLASS> CLASS::m_pInstance = nullptr;\
template<typename T>\
std::mutex CLASS::m_Mutex;

#define Py_RETURN_NONE return Py_INCREF(Py_None), Py_None

#define print(x) std::cout << x << std::endl



