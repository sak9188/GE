#include "GE_IO.h"

#include <iostream>

#include "boost/date_time/posix_time/posix_time.hpp"

GE_IO::GE_IO()
	: showTime(true)
{
}


GE_IO::~GE_IO()
{
}


const std::locale timeString = std::locale(std::cout.getloc(), new boost::posix_time::time_facet("<%Y-%m-%d %H:%M:%S>"));

// 这里打印的是机器上的时间，并非服务器上的时间 这里要注意
// 为什么不用服务器上的时间，因为这样可能会出现循环依赖
GE_IO& GE_IO::Trace()
{
	std::stringstream ss;
	ss << ">> Trace";
	if (showTime)
	{
		auto time = boost::posix_time::second_clock::local_time();
		ss.imbue(timeString);
		ss << time;
	}
	ss << ": ";
	std::cout << ss.str();
	this->outBuf << ss.str();
	return *this;
}

GE_IO& GE_IO::Info()
{
	std::stringstream ss;
	ss << ">> Info";
	if (showTime)
	{
		auto time = boost::posix_time::second_clock::local_time();
		ss.imbue(timeString);
		ss << time;
	}
	ss << ": ";
	std::cout << ss.str();
	this->outBuf << ss.str();
	return *this;
}

GE_IO& GE_IO::Debug()
{
	std::stringstream ss;
	ss << ">> Debug";
	if (showTime)
	{
		auto time = boost::posix_time::second_clock::local_time();
		ss.imbue(timeString);
		ss << time;
	}
	ss << ": ";
	std::cout << ss.str();
	this->outBuf << ss.str();
	return *this;
}

GE_IO& GE_IO::Warning()
{
	std::stringstream ss;
	ss << ">> Warning";
	if (showTime)
	{
		auto time = boost::posix_time::second_clock::local_time();
		ss.imbue(timeString);
		ss << time;
	}
	ss << ": ";
	std::cout << ss.str();
	this->outBuf << ss.str();
	return *this;
}

GE_IO& GE_IO::Error()
{
	std::stringstream ss;
	ss << ">> Error";
	if (showTime)
	{
		auto time = boost::posix_time::second_clock::local_time();
		ss.imbue(timeString);
		ss << time;
	}
	ss << ": ";
	std::cout << ss.str();
	this->outBuf << ss.str();
	this->expected = true;
	return *this;
}

GE_IO& GE_IO::operator<<(const char* s)
{
	//if (this->bHasRedirectToFile)
	//{
	//	std::cout << s;
	//}
	//else
	//{
	//	std::string sz(s);
	//	std::cout << this->UTF8ToGBK(sz);
	//}
	std::cout << s;
	this->outBuf << s;
	return *this;
}

GE_IO& GE_IO::operator<<(const std::string& s)
{
	//if (this->bHasRedirectToFile)
	//{
	//	std::cout << s;
	//}
	//else
	//{
	//	std::cout << this->UTF8ToGBK(s);
	//}
	std::cout << s;
	this->outBuf << s;
	return *this;
}

GE_IO& GE_IO::operator<<(GE::Int64 i64)
{
	std::cout << i64;
	this->outBuf << i64;
	return *this;
}

GE_IO& GE_IO::operator<<(GE::Uint64 ui64)
{
	std::cout << ui64;
	this->outBuf << ui64;
	return *this;
}

GE_IO& GE_IO::operator<<(GE::Int32 i32)
{
	std::cout << i32;
	this->outBuf << i32;
	return *this;
}

GE_IO& GE_IO::operator<<(GE::Uint32 ui32)
{
	std::cout << ui32;
	this->outBuf << ui32;
	return *this;
}

GE_IO& GE_IO::operator<<(GE::Int8 i8)
{
	std::cout << static_cast<GE::Int32>(i8);
	this->outBuf << static_cast<GE::Int32>(i8);
	return *this;
}

GE_IO& GE_IO::operator<<(GE::Uint8 ui8)
{
	std::cout << static_cast<GE::Uint32>(ui8);
	this->outBuf << static_cast<GE::Uint32>(ui8);
	return *this;
}

void GE_IO::ShowTime(bool isShow)
{
	showTime = isShow;
}

std::string GE_IO::GetOutString()
{
	std::string s = this->outBuf.str();
	this->outBuf.str("");
	this->outBuf.clear();
	return s;
}


// 先不管UTF-8
//std::string GE_IO::UTF8ToGBK(const std::string& szUTF8)
//{
//	int len = MultiByteToWideChar(CP_UTF8, 0, szUTF8.c_str(), -1, NULL, 0);
//	unsigned short * wszGBK = new unsigned short[len + 1];
//	memset(wszGBK, 0, len * 2 + 2);
//	MultiByteToWideChar(CP_UTF8, 0, szUTF8.c_str(), -1, (LPWSTR)wszGBK, len);
//
//	len = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)wszGBK, -1, NULL, 0, NULL, NULL);
//	char *szGBK = new char[len + 1];
//	memset(szGBK, 0, len + 1);
//	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)wszGBK, -1, szGBK, len, NULL, NULL);
//	std::string szTemp(szGBK);
//	delete[]szGBK;
//	delete[]wszGBK;
//	return szTemp;
//}
