#include "DateTime.h"

#include <time.h>

#include <boost/thread/thread.hpp>
#include <boost/timer/timer.hpp>

#include "IO.h"

// 东八区
const GE::Int32 timezone = 8 * 3600;

GE::DateTime::DateTime()
	: accumulation(0), timeSpeed(1000)
{
	tzset();
	// 缓存当前时间
	unixTime = static_cast<GE::Int64>(time(0));
	
	// printf("unixtme %ld \n", unixTime);
	GE_Trace << "unixtme " << unixTime << "\n";

	CasheClock();
	CasheTime();
	// 计算时区
	timeZoneSecond = timezone;
}

GE::DateTime::~DateTime()
{

}

void GE::DateTime::SleepMsec(GE::Int32 uMsec)
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(uMsec));
}

bool GE::DateTime::Refresh()
{
	GE::Uint64 tmpClock = this->cpuCLock;
	this->CasheClock();
	if (this->cpuCLock < tmpClock)
	{
		std::cout << "Time Cycle." << std::endl;
		return false;
	}
	// 注意在上面已经能够确保m_uCPUCLock >= uTmpClock了
	this->accumulation += (this->cpuCLock - tmpClock);
	return true;
}

bool GE::DateTime::Update()
{
	/*
	如果过了1秒以上,则计算时间
	这样1秒1秒的的计算，可以让服务器能够追帧
	*/
	if (this->accumulation > this->timeSpeed)
	{
		this->unixTime += 1;
		this->accumulation -= this->timeSpeed;
		this->CasheTime();
		bool b = this->accumulation < this->timeSpeed;
#ifdef _MSC_VER
		// 检查加速的目标，停止加速
		//if (this->m_uTimeSpeed != 1000 && this->m_nUnixTime >= this->m_nTimeTarget)
		//{
		//	this->m_uTimeSpeed = 1000;
		//	this->m_nTimeTarget = 0;
		//}
#endif
		return b;
	}
	else
	{
		return true;
	}
	return false;
}

GE::Uint64 GE::DateTime::GetSystemMSeconds()
{
#ifdef _MSC_VER
	return static_cast<GE::Uint64>(clock());
#elif __GNUC__
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
#endif
}

void GE::DateTime::SetUnixTime(GE::Int32 nUnixTime)
{
	// 设置的时间必须大于当前的时间，不可能出现时间回流
	assert(this->unixTime < nUnixTime);
	this->unixTime = nUnixTime;
}

bool GE::DateTime::IsDay0(GE::Int32 uUnixTime)
{
	return false;
}

void GE::DateTime::CasheClock()
{
	this->cpuCLock = this->GetSystemMSeconds();
}

void GE::DateTime::CasheTime()
{
	// 缓存C++时间
	time_t _tt = static_cast<time_t>(unixTime);
	tm* _tm = localtime(&_tt);
	this->year = _tm->tm_year + 1900;
	this->month = _tm->tm_mon + 1;
	this->day = _tm->tm_mday;
	this->hour = _tm->tm_hour;
	this->minute = _tm->tm_min;
	this->second = _tm->tm_sec;
	this->weekDay = _tm->tm_wday;
	this->yearDay = _tm->tm_yday;
	if (_tm->tm_isdst > 0)
	{
		this->dstSecond = 3600;
	}
	else
	{
		this->dstSecond = 0;
	}
	/*
	Return value: New reference.
	缓存Python时间

	这一段是设置Python的缓存时间
	*/
	pyNow.SetPythonObject(GE::PyObjFromDatetime(this->Year(), this->Month(), this->Day(), this->Hour(), this->Minute(), this->Second()));
}