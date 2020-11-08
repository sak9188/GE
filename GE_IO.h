#pragma once

#include "GE_Singleton.h"

class GE_IO
	: public GE_Singleton<GE_IO>
{
public:
	GE_IO();
	~GE_IO();

	void Trace();
	void Info();
	void Debug();
	void Warning();
	void Error();
};

