#pragma once

class CMainDlg : public CDialogImpl<CMainDlg>, public CDialogResize<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_DLGRESIZE_MAP( CMainDlg )
		DLGRESIZE_CONTROL( IDC_IMAGE_PATH, DLSZ_SIZE_X )
		DLGRESIZE_CONTROL( IDC_CLEAR_LOG, DLSZ_MOVE_X )
		DLGRESIZE_CONTROL( IDC_OPTION, DLSZ_MOVE_X )
		DLGRESIZE_CONTROL( IDC_LOG, DLSZ_SIZE_X | DLSZ_SIZE_Y )
	END_DLGRESIZE_MAP()

	BEGIN_MSG_MAP( CMainDlg )
		MESSAGE_HANDLER( WM_LOG_EVENT, OnLogEvent )
		MESSAGE_HANDLER( WM_TIMER, OnTimer )
		COMMAND_ID_HANDLER( IDC_SELECT_PROCESS, OnSelectProcess )
		COMMAND_ID_HANDLER( IDC_CREATE_PROCESS, OnCreateProcess )
		COMMAND_ID_HANDLER( IDC_DETACH_PROCESS, OnDetachProcess )
		COMMAND_ID_HANDLER( IDC_SNAPSHOT, OnSnapshot )
		COMMAND_ID_HANDLER( IDC_CLEAR_LOG, OnClearLog )
		COMMAND_ID_HANDLER( IDC_OPTION, OnOption )
		COMMAND_ID_HANDLER( IDCANCEL, OnCancel )
		MESSAGE_HANDLER( WM_SYSCOMMAND, OnSysCommand )
		MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
		CHAIN_MSG_MAP( CDialogResize<CMainDlg> )
	END_MSG_MAP()

public:
	void UpdateUI( BOOL bDumping, DWORD dwPid, LPCTSTR szImgPath );
	void StopDump();
	BOOL DoDetach();

public:
	LRESULT OnInitDialog( UINT, WPARAM, LPARAM, BOOL& );
	LRESULT OnSysCommand( UINT, WPARAM, LPARAM, BOOL& );
	LRESULT OnTimer( UINT, WPARAM, LPARAM, BOOL& );
	LRESULT OnLogEvent( UINT, WPARAM wParam, LPARAM, BOOL& );
	LRESULT OnCancel( WORD, WORD, HWND, BOOL& );
	LRESULT OnCreateProcess( WORD, WORD, HWND, BOOL& );
	LRESULT OnSelectProcess( WORD, WORD, HWND, BOOL& );
	LRESULT OnDetachProcess( WORD, WORD, HWND, BOOL& );
	LRESULT OnSnapshot( WORD, WORD, HWND, BOOL& );
	LRESULT OnClearLog( WORD, WORD, HWND, BOOL& );
	LRESULT OnOption( WORD, WORD, HWND, BOOL& );
};
