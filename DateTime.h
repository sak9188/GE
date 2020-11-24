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
		static void			SleepMsec(GE::Int32 uMsec);													//����
		bool				Refresh();																	//ˢ��ʱ�䣬������֮�����ط�����ʱ���Ƿ�˳����
		bool				Update();																	//����ʱ��
		GE::Uint64			GetSystemMSeconds();														//��ȡϵͳ�����ĺ�����
																										// ��ȡ��ǰʱ��ĺ�����
		GE::Int32			Year() { return year; }														//�꣨��ݣ���2011��
		GE::Int32			Month() { return month; }													//�£��·ݣ�1 -- 12��
		GE::Int32			Day() { return day; }														//�գ����ڣ�1 -- 31��
		GE::Int32			Hour() { return hour; }														//ʱ��Сʱ��0 -- 23��
		GE::Int32			Minute() { return minute; }													//�֣����ӣ�0 -- 59��
		GE::Int32			Second() { return second; }													//�루���ӣ�0 -- 59��
		GE::Int32			WeekDay() { return weekDay; }												//���ڼ���0�������죻1������1 ...��
		GE::Int32			YeayDay() { return yearDay; }												//����ĵڼ���
																										// ����δȻ���ٶ���������������100��
																										// �ٶ���������������100��
		GE::Int64			Seconds() { return unixTime; }												//��1970Ԫ�����ڵ�����

		GE::Int32			Minutes() { return static_cast<GE::Int32>(unixTime / 60); }											//��1970Ԫ�����ڵķ�����

		GE::Int32			Hours() { return static_cast<GE::Int32>((unixTime + timeZoneSecond + dstSecond) / 3600); }			//��1970Ԫ�����ڵ�Сʱ��
		GE::Int32			Days() { return static_cast<GE::Int32>((unixTime + timeZoneSecond + dstSecond) / 86400); }	        //��1970Ԫ�����ڵ�������ע������������ʱ����Ӱ�죩
		GE::Int32			Weeks() { return (Days() + 3) / 7; }										//��1970Ԫ�����ڵ�������ע������������ʱ����Ӱ�죩
		GE::Int32			Months() { return (year - 1970) * 12 + month - 1; }					    //��1970Ԫ�����ڵ�������ע������������ʱ����Ӱ�죩
		GE::Uint64			MSeconds() { return cpuCLock; }											    //�������������ڵĺ�����
		GE::Int32			TimeZoneSeconds() { return timeZoneSecond; }								//����˵�ǰ�������ڼ������ʱ��
		GE::Int32			DSTSeconds() { return dstSecond; }										    //����˵�ǰ�������ڼ����������ʱ
		GEPyObject&			Now() { return pyNow; }														//���ڵ�ʱ�䣨Python��
																										// ����ʱ��ĺ���
		void				SetUnixTime(GE::Int32 nUnixTime);											//�����ڲ�ʱ��
																										// �ⲿ���Ժ���
		bool				IsDay0(GE::Int32 uUnixTime);												//�Ƿ���һ��ĵ�0��

																										// �Ȳ���ʱ����ٵ�����
																										// GE::Int32			GetFastTimeSpeed();															//ʱ����ټ���
																										// void				SetFastTimeSpeed(GE::Int32 nFastSpeed, GE::Int32 nTimeTarget);				//����ʱ�����

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
		// ����ʵ����ֻȡ5���ֽڣ��������Լ�¼1000�����ϵ�ʱ��
		GE::Int64			unixTime;

		GE::Int32			timeZoneSecond;
		GE::Int32			dstSecond;
		GE::Uint64			cpuCLock;
		GE::Int64			accumulation;

		GEPyObject			pyNow;
	};
}