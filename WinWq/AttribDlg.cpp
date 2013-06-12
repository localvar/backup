// AttribDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winwq.h"
#include "AttribDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttribDlg dialog


CAttribDlg::CAttribDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAttribDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAttribDlg)
	m_nGuanZi = 0;
	m_nMiddle = 0;
	m_GameDiscribe = _T("");
	m_PieceDiscribe = _T("");
	//}}AFX_DATA_INIT
	nTotalHand=999;
}


void CAttribDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttribDlg)
	DDX_Text(pDX, IDC_GUANZI, m_nGuanZi);
	DDV_MinMaxInt(pDX, m_nGuanZi, m_nMiddle,nTotalHand);
	DDX_Text(pDX, IDC_MIDDLE, m_nMiddle);
	DDV_MinMaxInt(pDX, m_nMiddle, 0,nTotalHand);
	DDX_Text(pDX, IDC_GAMEDISCRIBE, m_GameDiscribe);
	DDX_Text(pDX, IDC_PIECEDISCRIBE, m_PieceDiscribe);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttribDlg, CDialog)
	//{{AFX_MSG_MAP(CAttribDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttribDlg message handlers

BOOL CAttribDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	nTotalHand=pGi->nTotalHand;

	m_GameDiscribe.Format("����:%s\n",pGi->GameName);
	CString temp;
	temp.Format("�ڷ�:%s ��λ:%s\n�׷�:%s ��λ:%s\n",pGi->BlackName,pGi->BlackDegree,pGi->WhiteName,pGi->WhiteDegree);
	m_GameDiscribe+=temp;
	temp.Format("����%d��%d��%d��  ��%d��  %s\n",pGi->nYear,pGi->nMonth,pGi->nDay,pGi->nTotalHand,pGi->WinLost);
	m_GameDiscribe+=temp;
	int panes=(pGi->nPanes-9)/2;
	char *p[]=
	{
		"��·��",
		"ʮһ·��",
		"ʮ��·��",
		"ʮ��·��",
		"ʮ��·��",
		"ʮ��·��"
	};
	char *preput[]=
	{
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
	temp.Format("%s    %s\n",p[panes],preput[pGi->nBlackPrevPut]);
	m_GameDiscribe+=temp;
				
	m_nMiddle = pGi->nMiddle;
	m_nGuanZi = pGi->nGuanZi;	
	
	m_PieceDiscribe.Format("��:%d  ��:%d  ��ɫ:%s  ���:%d  ������:%d\n%s",
			pi->m_nCol,
			pi->m_nRow,
			pi->m_nColor==0?"":(pi->m_nColor==1?"��":"��"),
			pi->m_nSerNum,
			pi->m_nKills,
			pi->m_Discribe
			);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetRange(0,nTotalHand);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->SetRange(0,nTotalHand);
	
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAttribDlg::OnOK() 
{
	if(!UpdateData()) return;

	CDialog::OnOK();
}
