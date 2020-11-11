#pragma once

#include "GE_Singleton.h"
#include "GE.h"

#include <sstream>

class GE_IO
	: public GE_Singleton<GE_IO>
{
	GE_BAN_COPY(GE_IO)
public:
	GE_IO();
	~GE_IO();

	GE_IO& Trace();
	GE_IO& Info();
	GE_IO& Debug();
	GE_IO& Warning();
	GE_IO& Error();

	std::string				GetOutString();
	std::string				UTF8ToGBK(const std::string& szUTF8);

	GE_IO&					operator<<(const char* s);
	GE_IO&					operator<<(const std::string& s);
	GE_IO&					operator<<(GE::Int64 i64);
	GE_IO&					operator<<(GE::Uint64 ui64);
	GE_IO&					operator<<(GE::Int32 i32);
	GE_IO&					operator<<(GE::Uint32 ui32);
	GE_IO&					operator<<(GE::Int8 i8);
	GE_IO&					operator<<(GE::Uint8 ui8);

private:
	std::ostringstream		outBuf;

	bool					expected;
};

