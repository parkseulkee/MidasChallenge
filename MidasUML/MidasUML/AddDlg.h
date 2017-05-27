#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "Class.h"
// CAddDlg 대화 상자입니다.

class CAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDlg)

public:
	CAddDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_varAcc;
	CComboBox m_funcAcc;
	virtual BOOL OnInitDialog();
	CString m_name;
	CString m_varName;
	CString m_varType;
	CString m_funcName;
	CString m_funcParam;
	CString m_funcType;
	CListBox m_varAccessLIST;
	CListBox m_varNameList;
	CListBox m_varTypeList;
	afx_msg void OnBnClickedVarButton();
	afx_msg void OnBnClickedButton2();
	CListBox m_funcAccList;
	CListBox m_funcNameList;
	CListBox m_funcParamList;
	CListBox m_funcTypeList;
	afx_msg void OnBnClickedOk();

	POINT m_point;
};
