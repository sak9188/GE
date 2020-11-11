#pragma once

#include "GE.h"
#include "GE_Singleton.h"

class GE_GUID64
	: public GE_Singleton<GE_GUID64>
{
	GE_BAN_COPY(GE_GUID64)
public:
	GE_GUID64(void);
	~GE_GUID64(void);

// ����ʹ�� ���ص� ѩ���㷨 ��֤��Ψһid
// 
public:
	GE::Uint64			AllotGUID();						//����һ��ȫ��ID
	void				ResetBaseID();

private:
	GE::Uint16			baseID;
	const GE::Uint16	maxID = 65535;
};

