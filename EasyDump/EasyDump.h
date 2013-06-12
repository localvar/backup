#pragma once

#include "resource.h"
#include "version.h"

////////////////////////////////////////////////////////////////////////////////
// ��������

// ת������
#define ED_DONT_DUMP			0
#define ED_MINI_DUMP			(MiniDumpNormal | MiniDumpWithHandleData)
#define ED_FULL_DUMP			(MiniDumpNormal | MiniDumpWithFullMemory \
	| MiniDumpWithHandleData | MiniDumpWithUnloadedModules \
	| MiniDumpWithThreadInfo | MiniDumpWithFullMemoryInfo)

// ��������ʱ, �����в�������󳤶�
#define MAX_ARGUMENT_LEN		1024

// ��¼��־���õ���Ϣ
#define WM_LOG_EVENT			(WM_USER + 200)


////////////////////////////////////////////////////////////////////////////////
// �쳣��Ϣ

struct CExceptionInfo
{
	DWORD dwCode;		// �쳣����
	bool bUser;			// �Ƿ����û������
	bool bFiltered;		// �Ƿ񱻹��˵���
	WORD Reserved;
	TCHAR szName[32];	// �쳣����
};


////////////////////////////////////////////////////////////////////////////////
// ϵͳ����ѡ��

struct CSettings
{
	LONG volatile lVersion;		// ���ڶ��߳�ͬ��
	bool volatile bKillOnExit;	// �˳�ʱ�Ƿ�ɱ������
	bool bAutoDelete;
	WORD Reserved;
	DWORD dwSnapshot;
	DWORD dwFirstChance;
	DWORD dwSecondChance;
	TCHAR szDumpPath[MAX_PATH];
};

extern CSettings Settings;


////////////////////////////////////////////////////////////////////////////////
// ���ߺ���

BOOL GetImageNameByPid( DWORD dwPid, LPTSTR szBuf, DWORD cbBuf );
BOOL GetImagePathByPid( DWORD dwPid, LPTSTR szBuf, DWORD cbBuf );
void LogEvent( UINT uEventId, ... );
int MessageBoxV( HWND hWnd, UINT uTextFmt, UINT uType, ... );
LPTSTR GetDumpPath( LPTSTR szBuf, DWORD cbBuf );
BOOL FilterException( DWORD dwExceptionCode );
const CAtlArray<CExceptionInfo>& GetExceptionList();
void UpdateExceptionList( CAtlArray<CExceptionInfo>& aException );


////////////////////////////////////////////////////////////////////////////////
// ʵ��ת���������

BOOL DumpInit();
void DumpUninit();
BOOL DumpAeDebug( DWORD dwPid, HANDLE hEvent );
DWORD DumpStart( DWORD dwPid, LPCTSTR szImgPath );
DWORD DumpStart( LPCTSTR szImgPath, LPCTSTR szArg, LPCTSTR szWorkDir );
void DumpSnapshot();
void DumpStop();
BOOL IsDumping();
BOOL IsDetachSupported();


////////////////////////////////////////////////////////////////////////////////