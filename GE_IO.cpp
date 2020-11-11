#include "GE_IO.h"



GE_IO::GE_IO()
{
}


GE_IO::~GE_IO()
{
}

GE_IO& GE_IO::Trace()
{
	return *this;
}

GE_IO& GE_IO::Info()
{
	return *this;

}

GE_IO& GE_IO::Debug()
{
	return *this;

}

GE_IO& GE_IO::Warning()
{
	return *this;

}

GE_IO& GE_IO::Error()
{
	std::cout << "GE_EXC ";
	this->outBuf << "GE_EXC ";
	this->expected = true;
	return *this;
}

GE_IO& GE_IO::operator<<(const char* s)
{
	if (this->bHasRedirectToFile)
	{
		std::cout << s;
	}
	else
	{
		std::string sz(s);
		std::cout << this->UTF8ToGBK(sz);
	}
	this->outBuf << s;
	return *this;
}

GE_IO& GE_IO::operator<<(const std::string& s)
{
	if (this->bHasRedirectToFile)
	{
		std::cout << s;
	}
	else
	{
		std::cout << this->UTF8ToGBK(s);
	}
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

std::string GE_IO::GetOutString()
{
	std::string s = this->outBuf.str();
	this->outBuf.str("");
	this->outBuf.clear();
	return s;
}

std::string GE_IO::UTF8ToGBK(const std::string& szUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, szUTF8.c_str(), -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, szUTF8.c_str(), -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)wszGBK, -1, szGBK, len, NULL, NULL);
	std::string szTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return szTemp;
}
