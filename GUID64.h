#pragma once

#include "GE.h"
#include "Singleton.h"

namespace GE
{
	class GUID64
		: public Singleton<GUID64>
	{
		GE_BAN_COPY(GUID64)
	public:
		GUID64(void);
		~GUID64(void);

		// ����ʹ�� ���ص� ѩ���㷨 ��֤��Ψһid
		// 
	public:
		GE::Uint64			AllotGUID();						//����һ��ȫ��ID
		void				ResetBaseID();

	private:
		GE::Uint16			baseID;
		const GE::Uint16	maxID = 65535;
	};

}


