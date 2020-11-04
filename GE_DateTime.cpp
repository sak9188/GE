#include "GE_DateTime.h"

#include <time.h>
#include <boost/thread/thread.hpp>
#include <boost/timer/timer.hpp>

#include "GE_Python.h"

// ������
const GE::Int32 timezone = 8 * 3600;

GE_SET_SINGLETON(GE_DateTime)

GE_DateTime::~GE_DateTime()
{

}

void GE_DateTime::Init()
{
	this->accumulation = 0;
}

void GE_DateTime::Start()
{
	tzset();
	// ���浱ǰʱ��
	m_pInstance.unixTime = static_cast<GE::Int32>(time(0));
	m_pInstance.CasheClock();
	m_pInstance.CasheTime();
	// ����ʱ��
	m_pInstance.timeZoneSecond = timezone;
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
	// ע���������Ѿ��ܹ�ȷ��m_uCPUCLock >= uTmpClock��
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
	// ���õ�ʱ�������ڵ�ǰ��ʱ�䣬�����ܳ���ʱ�����
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
	// ����C++ʱ��
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
	����Pythonʱ��

	��һ��������Python�Ļ���ʱ��
	*/
	m_PyNow.SetPythonObject(GE::PyObjFromDatetime(this->Year(), this->Month(), this->Day(), this->Hour(), this->Minute(), this->Second()));
}