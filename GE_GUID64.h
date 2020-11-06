#pragma once

#include "GE.h"
#include "GE_Singleton.h"

class GE_GUID64
	: public GE_Singleton<GE_GUID64>
{
	
public:
	~GE_GUID64(void);

// ����ʹ�� ���ص� ѩ���㷨 ��֤��Ψһid
// 
public:
	GE::Uint64			AllotGUID();						//����һ��ȫ��ID

private:
	GE::Uint64			baseID;
	GE::Uint64			maxID;
};

