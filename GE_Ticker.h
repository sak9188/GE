#pragma once
class GE_Ticker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// ���뼶��Ķ�ʱ��
class GE_ClockTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// �뼶��Ķ�ʱ��
class GE_SlowTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// ���Ӽ���Ķ�ʱ��
class GE_IntervalTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// Сʱ����Ķ�ʱ��
class GE_HourTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// �켶��Ķ�ʱ��
class GE_PeriodTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};


