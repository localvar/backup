// WqOpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinWq.h"
#include "WqOpenDlg.h"
#include <dlgs.h>
#include "CBoard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWqOpenDlg

extern void operator >>(CArchive& ar,GAMEINFO& gi);

IMPLEMENT_DYNAMIC(CWqOpenDlg, CFileDialog)

CWqOpenDlg::CWqOpenDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	SetTemplate(0,IDD_WQ_OPENDLG);
}


BEGIN_MESSAGE_MAP(CWqOpenDlg, CFileDialog)
	//{{AFX_MSG_MAP(CWqOpenDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CWqOpenDlg::OnInitDone()
{
	CFileDialog::OnInitDone();

	CRect r,rDiscribe;
	CWnd* pList=GetParent()->GetDlgItem(lst1);
	pList->GetWindowRect(r);
	GetParent()->ScreenToClient(r);
	
	CWnd* pWnd=GetDlgItem(IDC_DISCRIBE);
	pWnd->GetWindowRect(rDiscribe);

	GetParent()->ScreenToClient(rDiscribe);

	pWnd->SetWindowPos(NULL,r.left,rDiscribe.top,r.Width(),rDiscribe.Height(),
		SWP_NOACTIVATE|SWP_NOZORDER);
}

void CWqOpenDlg::OnFileNameChange()
{
	CFileDialog::OnFileNameChange();

	CString fn,msg;
	msg="���������ļ�";

	fn=GetPathName();
	if(GetFileExt()=="zbm")
	{
		CFile file;
		if(file.Open(fn,CFile::shareDenyNone|CFile::modeRead))
		{	
			CArchive ar(&file,CArchive::load);
			DWORD dwSchema;
			ar>>dwSchema;
			if(dwSchema==552931)
			{
				GAMEINFO gi;
				ar>>gi;
				msg.Format("����:%s\n",gi.GameName);
				CString temp;
				temp.Format("�ڷ�:%s ��λ:%s   �׷�:%s ��λ:%s\n",gi.BlackName,gi.BlackDegree,gi.WhiteName,gi.WhiteDegree);
				msg+=temp;
				temp.Format("����%d��%d��%d��  ��%d��  %s\n",gi.nYear,gi.nMonth,gi.nDay,gi.nTotalHand,gi.WinLost);
				msg+=temp;
				int panes=(gi.nPanes-9)/2;
				char *p[]={
					"��·��",
					"ʮһ·��",
					"ʮ��·��",
					"ʮ��·��",
					"ʮ��·��",
					"ʮ��·��"
				};
				char *preput[]={
					"",
					"������",
					"�ö�����",
					"��������",
					"��������",
					"��������",
					"��������",
					"��������",
					"�ð�����",
					"�þ�����"
				};
				temp.Format("%s    %s\n",p[panes],preput[gi.nBlackPrevPut]);
				msg+=temp;
			}
			else msg="�ļ���ʽ����,���������ļ�";
			ar.Close();
			file.Close();
		}
	}
	
	SetDlgItemText(IDC_DISCRIBE,msg);
}
