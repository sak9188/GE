#pragma once
class GE_Ticker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// 毫秒级别的定时器
class GE_ClockTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// 秒级别的定时器
class GE_SlowTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// 分钟级别的定时器
class GE_IntervalTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// 小时级别的定时器
class GE_HourTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};

// 天级别的定时器
class GE_PeriodTicker
{
	typedef std::map<GE::Int64, _PyCallBack>		tdTickReactor;
public:
	GE_Ticker();
	~GE_Ticker();
};


