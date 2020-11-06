#pragma once

#include "GE.h"
#include "GE_Singleton.h"

class GE_GUID64
	: public GE_Singleton<GE_GUID64>
{
	
public:
	~GE_GUID64(void);

// 这里使用 推特的 雪花算法 保证是唯一id
// 
public:
	GE::Uint64			AllotGUID();						//分配一个全球ID

private:
	GE::Uint64			baseID;
	GE::Uint64			maxID;
};

