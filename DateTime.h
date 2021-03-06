#pragma once
#include "GE.h"
#include "GEPyObject.h"
#include "Singleton.h"

#include "PythonEngine.h"

namespace GE
{
	class DateTime
		: public GE::Singleton<DateTime>
	{
	public:
		DateTime();
		~DateTime();

	public:
		static void			SleepMsec(GE::Int32 uMsec);													//休眠
		bool				Refresh();																	//刷新时间，并缓存之【返回服务器时间是否顺畅】
		bool				Update();																	//更新时间
		GE::Uint64			GetSystemMSeconds();														//获取系统启动的毫秒数
																										// 获取当前时间的函数簇
		GE::Int32			Year() { return year; }														//年（年份，如2011）
		GE::Int32			Month() { return month; }													//月（月份，1 -- 12）
		GE::Int32			Day() { return day; }														//日（日期，1 -- 31）
		GE::Int32			Hour() { return hour; }														//时（小时，0 -- 23）
		GE::Int32			Minute() { return minute; }													//分（分钟，0 -- 59）
		GE::Int32			Second() { return second; }													//秒（秒钟，0 -- 59）
		GE::Int32			WeekDay() { return weekDay; }												//星期几（0，星期天；1，星期1 ...）
		GE::Int32			YeayDay() { return yearDay; }												//今年的第几天
																										// 防范未然，假定这个程序可以运行100年
																										// 假定这个程序可以运行100年
		GE::Int64			Seconds() { return unixTime; }												//从1970元到现在的秒数

		GE::Int32			Minutes() { return static_cast<GE::Int32>(unixTime / 60); }											//从1970元到现在的分钟数

		GE::Int32			Hours() { return static_cast<GE::Int32>((unixTime + timeZoneSecond + dstSecond) / 3600); }			//从1970元到现在的小时数
		GE::Int32			Days() { return static_cast<GE::Int32>((unixTime + timeZoneSecond + dstSecond) / 86400); }	        //从1970元到现在的天数（注意这里修正了时区的影响）
		GE::Int32			Weeks() { return (Days() + 3) / 7; }										//从1970元到现在的周数（注意这里修正了时区的影响）
		GE::Int32			Months() { return (year - 1970) * 12 + month - 1; }					    //从1970元到现在的月数（注意这里修正了时区的影响）
		GE::Uint64			MSeconds() { return cpuCLock; }											    //进程启动到现在的毫秒数
		GE::Int32			TimeZoneSeconds() { return timeZoneSecond; }								//服务端当前进程所在计算机的时区
		GE::Int32			DSTSeconds() { return dstSecond; }										    //服务端当前进程所在计算机的夏令时
		GEPyObject&			Now() { return pyNow; }														//现在的时间（Python）
																										// 修正时间的函数
		void				SetUnixTime(GE::Int32 nUnixTime);											//设置内部时间
																										// 外部测试函数
		bool				IsDay0(GE::Int32 uUnixTime);												//是否是一天的第0秒

																										// 先不管时间加速的问题
																										// GE::Int32			GetFastTimeSpeed();															//时间加速几倍
																										// void				SetFastTimeSpeed(GE::Int32 nFastSpeed, GE::Int32 nTimeTarget);				//设置时间加速

	private:
		void				CasheClock();
		void				CasheTime();

	private:
		GE::Int32			timeSpeed;
		GE::Int32			year;
		GE::Int32			month;
		GE::Int32			day;
		GE::Int32			hour;
		GE::Int32			minute;
		GE::Int32			second;
		GE::Int32			weekDay;
		GE::Int32			yearDay;
		// 这里实际上只取5个字节，这样可以记录1000年以上的时间
		GE::Int64			unixTime;

		GE::Int32			timeZoneSecond;
		GE::Int32			dstSecond;
		GE::Uint64			cpuCLock;
		GE::Int64			accumulation;

		GEPyObject			pyNow;
	};
}