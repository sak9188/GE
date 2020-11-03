#pragma once

#include <mutex>

#include "GE.h"

class GE_GUID64
{
	
public:
	~GE_GUID64(void);

// ����ʹ�� ���ص� ѩ���㷨 ��֤��Ψһid
// 
public:
	GE::Uint64			AllotGUID();						//����һ��ȫ��ID

private:
	GE::Uint64			m_uBaseID;
	GE::Uint64			m_uMaxID;

	void Init();
	GE_SINGLETON(GE_GUID64)
};
GE_SET_SINGLETON(GE_GUID64)

