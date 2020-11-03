#pragma once

#include <mutex>

#include "GE.h"

class GE_Process
{
public:
	~GE_Process();

private:
	void Init();

	GE_SINGLETON(GE_Process)
};
GE_SET_SINGLETON(GE_Process)

