#pragma once

#include <mutex>

#include "GE.h"

class GE_GUID64
{
	
public:
	~GE_GUID64(void);

// 这里使用 推特的 雪花算法 保证是唯一id
// 
public:
	GE::Uint64			AllotGUID();						//分配一个全球ID

private:
	GE::Uint64			m_uBaseID;
	GE::Uint64			m_uMaxID;

	void Init();
	GE_SINGLETON(GE_GUID64)
};
GE_SET_SINGLETON(GE_GUID64)

