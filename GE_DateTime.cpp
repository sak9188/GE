#include "GE_DateTime.h"

#include <time.h>
#include <boost/thread/thread.hpp>
#include <boost/timer/timer.hpp>

#include "GE_Python.h"

// 东八区
const GE::Int32 timezone = 8 * 3600;

GE_DateTime::GE_DateTime(void) : accumulation(0)
{
	tzset();
	// 缓存当前时间
	unixTime = static_cast<GE::Int32>(time(0));
	CasheClock();
	CasheTime();
	// 计算时区
	timeZoneSecond = timezone;
}

GE_DateTime::~GE_DateTime()
{

}

void GE_DateTime::SleepMsec(GE::Int32 uMsec)
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(uMsec));
}

bool GE_DateTime::Refresh()
{
	GE::Uint64 uTmpClock = this->cpuCLock;
	this->CasheClock();
	if (this->cpuCLock < uTmpClock)
	{
		std::cout << "Time Cycle." << std::endl;
		return false;
	}
	// 注意在上面已经能够确保m_uCPUCLock >= uTmpClock了
	this->accumulation += (this->cpuCLock - uTmpClock);
	return true;
}

bool GE_DateTime::Update()
{
	return false;
}

GE::Uint64 GE_DateTime::GetSystemMSeconds()
{
#ifdef _MSC_VER
	return static_cast<GE::Uint64>(clock());
#elif __GNUC__
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
#endif
}

void GE_DateTime::SetUnixTime(GE::Int32 nUnixTime)
{
	// 设置的时间必须大于当前的时间，不可能出现时间回流
	assert(this->unixTime < nUnixTime);
	this->unixTime = nUnixTime;
}

bool GE_DateTime::IsDay0(GE::Int32 uUnixTime)
{
	return false;
}

void GE_DateTime::CasheClock()
{
	this->cpuCLock = this->GetSystemMSeconds();
}

void GE_DateTime::CasheTime()
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