// EditDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MidasUML.h"
#include "EditDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MidasUMLDoc.h"
#include "MidasUMLView.h"
// CEditDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEditDlg, CDialogEx)

CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDIT, pParent)
	, m_name(_T(""))
	, m_varName(_T(""))
	, m_varType(_T(""))
	, m_funcName(_T(""))
	, m_funcParam(_T(""))
	, m_funcType(_T(""))
{
	selectClass = -1;
}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_VAR_ACC, m_valueAcc);
	DDX_Control(pDX, IDC_FUNC_ACC, m_funcAcc);
	DDX_Text(pDX, IDC_EDIT2, m_varName);
	DDX_Text(pDX, IDC_EDIT3, m_varType);
	DDX_Text(pDX, IDC_EDIT4, m_funcName);
	DDX_Text(pDX, IDC_EDIT6, m_funcParam);
	DDX_Text(pDX, IDC_EDIT5, m_funcType);
	DDX_Control(pDX, IDC_LIST1, m_varList);
	DDX_Control(pDX, IDC_LIST5, m_funcList);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
	ON_BN_CLICKED(IDC_VAR_BUTTON, &CEditDlg::OnBnClickedVarButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CEditDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CEditDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CEditDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditDlg 메시지 처리기입니다.


void CEditDlg::OnBnClickedVarButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// var 추가
	int acc = m_valueAcc.GetCurSel();
	CString name;
	GetDlgItemText(IDC_EDIT2, name);
	CString type;
	GetDlgItemText(IDC_EDIT3, type);

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMidasUMLDoc *pDoc = (CMidasUMLDoc *)pChild->GetActiveDocument();
	pDoc->getPointClass(selectClass)->addVar(Var((ACCESS_TYPE)acc, name, type));
	std::vector<Var> var = pDoc->getPointClass(selectClass)->getVarInfo();
	CString str = var[var.size() - 1].getInfo();
	m_varList.AddString(str);
}


void CEditDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// func 추가
	int acc = m_funcAcc.GetCurSel();
	CString name;
	GetDlgItemText(IDC_EDIT4, name);
	CString type;
	GetDlgItemText(IDC_EDIT5, type);
	CString param;
	GetDlgItemText(IDC_EDIT6, param);
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMidasUMLDoc *pDoc = (CMidasUMLDoc *)pChild->GetActiveDocument();

	pDoc->getPointClass(selectClass)->addFunction(Function((ACCESS_TYPE)acc, type, name, param));
	std::vector<Function> function = pDoc->getPointClass(selectClass)->getFunctionInfo();
	CString str = function[function.size() - 1].getInfo();
	m_funcList.AddString(str);
}


void CEditDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// var 삭제
	int id = m_varList.GetCurSel();
	m_varList.DeleteString(id);
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMidasUMLDoc *pDoc = (CMidasUMLDoc *)pChild->GetActiveDocument();
	pDoc->getPointClass(selectClass)->deleteVar(id);
}


void CEditDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// func 삭제
	int id = m_funcList.GetCurSel();
	m_funcList.DeleteString(id);
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMidasUMLDoc *pDoc = (CMidasUMLDoc *)pChild->GetActiveDocument();
	pDoc->getPointClass(selectClass)->deleteFunction(id);
}


BOOL CEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_valueAcc.AddString(_T("private"));
	m_valueAcc.AddString(_T("protected"));
	m_valueAcc.AddString(_T("public"));

	m_funcAcc.AddString(_T("private"));
	m_funcAcc.AddString(_T("protected"));
	m_funcAcc.AddString(_T("public"));

	m_valueAcc.SetCurSel(0);
	m_funcAcc.SetCurSel(0);

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMidasUMLDoc *pDoc = (CMidasUMLDoc *)pChild->GetActiveDocument();

	Class _class = pDoc->getClass(selectClass);
	SetDlgItemText(IDC_EDIT1, _class.getName());
	std::vector<Var> var = _class.getVarInfo();
	for (int i = 0;i < var.size();i++) {
		CString varInfo = var[i].getInfo();
		m_varList.AddString(varInfo);
	}
	std::vector<Function> function = _class.getFunctionInfo();
	for (int i = 0;i < function.size();i++) {
		CString funcInfo = function[i].getInfo();
		m_funcList.AddString(funcInfo);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CEditDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
