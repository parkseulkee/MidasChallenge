#pragma once
#include "afxwin.h"

#include "Class.h"
// CEditDlg 대화 상자입니다.

class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	CEditDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEditDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CComboBox m_valueAcc;
	CComboBox m_funcAcc;
	CString m_varName;
	CString m_varType;
	CString m_funcName;
	CString m_funcParam;
	CString m_funcType;
	CListBox m_varList;
	CListBox m_funcList;
	afx_msg void OnBnClickedVarButton();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();

	int selectClass;
	afx_msg void OnBnClickedOk();
};
