#pragma once
#define print(x) std::cout << x << std::endl

// 整数取值范围
#define GE_INT8_MIN		(-127 - 1)
#define	GE_INT8_MAX		127
#define GE_UINT_MAX		0xff
#define GE_INT16_MIN		 (-32768)        /* minimum (signed) short value */
#define GE_INT16_MAX      32767         /* maximum (signed) short value */
#define GE_UINT16_MAX     0xffff        /* maximum unsigned short value */
#define GE_INT32_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define GE_INT32_MAX       2147483647    /* maximum (signed) int value */
#define GE_UINT32_MAX      0xffffffff    /* maximum unsigned int value */
#define GE_INT64_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#define GE_INT64_MAX      2147483647L   /* maximum (signed) long value */
#define GE_UINT64_MAX     0xffffffffUL  /* maximum unsigned long value */

// 断言
#define GE_ASSERT(exp) if(!(exp)){abort();}
#define GE_STATIC_ASSERT BOOST_STATIC_ASSERT

// 安全删除
#define GE_SAFE_DELETE(_ptr)	\
	if((_ptr)) { \
	delete (_ptr);	\
	(_ptr) = 0;	\
		};

// 禁止拷贝
#define GE_BAN_COPY(CLASS)\
	CLASS& operator = (const CLASS& t) = delete; \
	CLASS(const CLASS &) = delete;

// 常用返回
#define Py_RETURN_NONE return Py_INCREF(Py_None), Py_None

// 单例设计模式
#define GE_SINGLETON(CLASS) \
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

#define GE_SET_SINGLETON(CLASS) \
		CLASS CLASS::m_pInstance;\
		std::mutex CLASS::m_Mutex;

// 跨平台整数
namespace GE
{
#ifdef _MSC_VER 
	typedef signed char			Int8;
	typedef signed short		Int16;
	typedef signed int			Int32;
	typedef signed __int64		Int64;
	typedef unsigned char		Uint8;
	typedef unsigned short		Uint16;
	typedef unsigned int		Uint32;
	typedef unsigned __int64	Uint64;
#elif __GNUC__
	typedef signed char			Int8;
	typedef signed short		Int16;
	typedef signed int			Int32;
	typedef signed long long	Int64;
	typedef unsigned char		Uint8;
	typedef unsigned short		Uint16;
	typedef unsigned int		Uint32;
	typedef unsigned long long	Uint64;
#endif
}