#pragma once
#include "afxwin.h"


// CAddAccDlg 대화 상자입니다.

class CAddAccDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddAccDlg)

public:
	CAddAccDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddAccDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_ACCOS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_mainBox;
	CComboBox m_subBox;
	CComboBox m_accBox;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
