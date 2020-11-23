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

		// 这里使用 推特的 雪花算法 保证是唯一id
		// 
	public:
		GE::Uint64			AllotGUID();						//分配一个全球ID
		void				ResetBaseID();

	private:
		GE::Uint16			baseID;
		const GE::Uint16	maxID = 65535;
	};

}


