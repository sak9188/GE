#pragma once

#include "Singleton.h"
#include "GE.h"

#include <sstream>

namespace GE
{
	class IO
		: public Singleton<IO>
	{
		GE_BAN_COPY(IO)
	public:
		IO();
		~IO();

		IO& Trace();
		IO& Info();
		IO& Debug();
		IO& Warning();
		IO& Error();

		void					ShowTime(bool isShow);
		std::string				GetOutString();
		// std::string				UTF8ToGBK(const std::string& szUTF8);

		IO&					operator<<(const char* s);
		IO&					operator<<(const std::string& s);
		IO&					operator<<(GE::Int64 i64);
		IO&					operator<<(GE::Uint64 ui64);
		IO&					operator<<(GE::Int32 i32);
		IO&					operator<<(GE::Uint32 ui32);
		IO&					operator<<(GE::Int8 i8);
		IO&					operator<<(GE::Uint8 ui8);

	private:
		std::ostringstream		outBuf;
		bool					expected;

		// 是否显示时间
		bool					showTime;
	};
}


#ifdef _MSC_VER
#define GE_IO_ShowTime(BOOL) GE::IO::Instance()->ShowTime(BOOL)
#define GE_Trace GE::IO::Instance()->Trace()
#define GE_Info GE::IO::Instance()->Info()
#define GE_Debug GE::IO::Instance()->Debug()
#define GE_Warning GE::IO::Instance()->Warning()
#define GE_Error GE::IO::Instance()->Error()
#endif // _MSC_VER


