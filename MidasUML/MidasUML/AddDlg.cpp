// AddDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MidasUML.h"
#include "AddDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MidasUMLDoc.h"
#include "MidasUMLView.h"

// CAddDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddDlg, CDialog)

CAddDlg::CAddDlg(CWnd* pParent /*= NULL*/)
	: CDialog(IDD_ADD, pParent)
	, m_varName(_T(""))
	, m_varType(_T(""))
	, m_funcName(_T(""))
	, m_funcParam(_T(""))
	, m_funcType(_T(""))
{
	m_point = { 0,0 };
}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VAR_ACC, m_varAcc);
	DDX_Control(pDX, IDC_FUNC_ACC, m_funcAcc);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_varName);
	DDX_Text(pDX, IDC_EDIT3, m_varType);
	DDX_Text(pDX, IDC_EDIT4, m_funcName);
	DDX_Text(pDX, IDC_EDIT6, m_funcParam);
	DDX_Text(pDX, IDC_EDIT5, m_funcType);
	DDX_Control(pDX, IDC_LIST2, m_varAccessLIST);
	DDX_Control(pDX, IDC_LIST3, m_varNameList);
	DDX_Control(pDX, IDC_LIST4, m_varTypeList);
	DDX_Control(pDX, IDC_LIST5, m_funcAccList);
	DDX_Control(pDX, IDC_LIST6, m_funcNameList);
	DDX_Control(pDX, IDC_LIST7, m_funcParamList);
	DDX_Control(pDX, IDC_LIST8, m_funcTypeList);
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialog)
	ON_BN_CLICKED(IDC_VAR_BUTTON, &CAddDlg::OnBnClickedVarButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddDlg 메시지 처리기입니다.


BOOL CAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_varAcc.AddString(_T("private"));
	m_varAcc.AddString(_T("protected"));
	m_varAcc.AddString(_T("public"));

	m_funcAcc.AddString(_T("private"));
	m_funcAcc.AddString(_T("protected"));
	m_funcAcc.AddString(_T("public"));

	m_varAcc.SetCurSel(0);
	m_funcAcc.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAddDlg::OnBnClickedVarButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int acc = m_varAcc.GetCurSel();
	CString accString;
	accString.Format(_T("%d"), acc);
	CString name;
	GetDlgItemText(IDC_EDIT2, name);
	CString type;
	GetDlgItemText(IDC_EDIT3, type);

	m_varAccessLIST.InsertString(0, accString);
	m_varNameList.InsertString(0, name);
	m_varTypeList.InsertString(0, type);
}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int acc = m_funcAcc.GetCurSel();
	CString accString;
	accString.Format(_T("%d"), acc);
	CString name;
	GetDlgItemText(IDC_EDIT4, name);
	CString param;
	GetDlgItemText(IDC_EDIT6, param);
	CString type;
	GetDlgItemText(IDC_EDIT5, type);

	m_funcAccList.AddString(accString);
	m_funcNameList.AddString(name);
	m_funcParamList.AddString(param);
	m_funcTypeList.AddString(type);
}


void CAddDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
	UpdateData(TRUE);
	std::vector<Var> var;
	for (int i = 0;i < m_varAccessLIST.GetCount();i++) {
		CString acc;
		m_varAccessLIST.GetText(i, acc);
		CString name;
		m_varNameList.GetText(i, name);
		CString type;
		m_varTypeList.GetText(i, type);
		var.push_back(Var((ACCESS_TYPE)_ttoi(acc), name, type));
	}
	std::vector<Function> function;
	for (int i = 0;i < m_funcAccList.GetCount();i++) {
		CString acc;
		m_funcAccList.GetText(i, acc);
		CString name;
		m_funcNameList.GetText(i, name);
		CString param;
		m_funcParamList.GetText(i, param);
		CString type;
		m_funcTypeList.GetText(i, type);
		function.push_back(Function((ACCESS_TYPE)_ttoi(acc), type, name, param));
	}
	CString name;
	name.Format(_T("%s"), m_name);
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMidasUMLDoc *pDoc = (CMidasUMLDoc *)pChild->GetActiveDocument();
	CMidasUMLView *pView = (CMidasUMLView *)pChild->GetActiveView();
	pDoc->addClass(name, pView->m_point, var, function);
}
