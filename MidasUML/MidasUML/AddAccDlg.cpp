// AddAccDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MidasUML.h"
#include "AddAccDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MidasUMLDoc.h"
#include "MidasUMLView.h"

// CAddAccDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddAccDlg, CDialogEx)

CAddAccDlg::CAddAccDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADD_ACCOS, pParent)
{

}

CAddAccDlg::~CAddAccDlg()
{
}

void CAddAccDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_mainBox);
	DDX_Control(pDX, IDC_COMBO2, m_subBox);
	DDX_Control(pDX, IDC_COMBO3, m_accBox);
}


BEGIN_MESSAGE_MAP(CAddAccDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddAccDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddAccDlg 메시지 처리기입니다.


BOOL CAddAccDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_accBox.AddString(_T("상속"));
	m_accBox.AddString(_T("의존"));
	m_accBox.SetCurSel(0);

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMidasUMLDoc *pDoc = (CMidasUMLDoc *)pChild->GetActiveDocument();

	for (int i = 0;i < pDoc->getSize();i++) {
		CString name = pDoc->getClass(i).getName();
		m_mainBox.AddString(name);
		m_subBox.AddString(name);
	}
	m_mainBox.SetCurSel(0);
	m_subBox.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAddAccDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
	UpdateData(TRUE);
	int mainId = m_mainBox.GetCurSel();
	int subId = m_subBox.GetCurSel();

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMidasUMLDoc *pDoc = (CMidasUMLDoc *)pChild->GetActiveDocument();

	int mainKey = pDoc->getClass(mainId).getKey();
	int subKey = pDoc->getClass(subId).getKey();
	ASSOCIATION_TYPE at = (ASSOCIATION_TYPE)m_accBox.GetCurSel();

	pDoc->addAssociation(mainKey, subKey, at);
}
