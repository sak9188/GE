#include "GUID64.h"

#include "DateTime.h"
#include "Process.h"

GE::GUID64::GUID64()
	: baseID(0)
{

}

GE::GUID64::~GUID64()
{

}

GE::Uint64 GE::GUID64::AllotGUID()
{
	// 8���ֽڵ��ڴ�ֲ�
	// 5���ֽ� �� 40 bits ��Ϊʱ���е���ֲ�
	// 1 ���ֽ� �� 8 bits ��Ϊ������������̵� id (4 bits for machine, 4 bits for processes)
	//     ������֧�� 2^4 16̨������ ÿ̨����16������ (����е�����ݳ��ˣ�1���ֽ��е��˷�)
	// 2 ���ֽ� �� 16 bits ����ʾһ���� ����� 65536 �� id
	// �൱�� 1���� ���� ������65�� GUID ������

	if (baseID > maxID)
	{
		// �������ʧ���򷵻�0����������������ǲ����ܷ���0��
		return 0;
	}

	GE::Uint64 guid_secs = GE::DateTime::Instance()->Seconds();
	// printf("guid_secs %d \n", guid_secs);
	// printf("MachineID %d \n", (GE_Process::Instance()->MachineID() << 4));
	// printf("ProcessUID %d \n", ((GE_Process::Instance()->ProcessUID() << 4) >> 4));
	GE::Uint8 guid_macid = (GE::Process::Instance()->MachineID() << 4) + ((GE::Process::Instance()->ProcessUID() << 4) >> 4);
	guid_secs = (((guid_secs << 8) + guid_macid) << 16) + baseID++;
	return guid_secs;
}

void GE::GUID64::ResetBaseID()
{
	baseID = 0;
}
