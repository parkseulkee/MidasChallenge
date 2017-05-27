
// MidasUMLView.cpp : CMidasUMLView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MidasUML.h"
#endif

#include "MidasUMLDoc.h"
#include "MidasUMLView.h"

#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidasUMLView

IMPLEMENT_DYNCREATE(CMidasUMLView, CView)

BEGIN_MESSAGE_MAP(CMidasUMLView, CView)
	// ǥ�� �μ� �����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMidasUMLView::OnFilePrintPreview)
//	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ADD_CLASS, &CMidasUMLView::OnAddClass)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CMidasUMLView ����/�Ҹ�

CMidasUMLView::CMidasUMLView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_point = { 0,0 };

}

CMidasUMLView::~CMidasUMLView()
{
}

BOOL CMidasUMLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMidasUMLView �׸���

void CMidasUMLView::OnDraw(CDC* pDC)
{
	CMidasUMLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	for (int i = 0; i < pDoc->getSize(); i++) {
		Class _class = pDoc->getClass(i);
		_class.drawClass(pDC);
	}

	/*{
		CString strName1("Hello");
		POINT Point1;
		Point1.x = 10;
		Point1.y = 10;
		std::vector<Var> var;
		std::vector<Function> function;

		Var var1(PRIVATE, CString("var1"), CString("char"));
		Var var2(PUBLIC, CString("var2"), CString("int"));
		Var var3(PROTECTED, CString("var3"), CString("long"));
		var.push_back(var1);
		var.push_back(var2);
		var.push_back(var3);

		Function func1(PRIVATE, CString("func1"), CString("int"), CString("int param1"));
		Function func2(PUBLIC, CString("func2"), CString("char *"), CString("char * param1, char * param2"));
		Function func3(PROTECTED, CString("func3"), CString("CString"), CString("CString param1"));
		function.push_back(func1);
		function.push_back(func2);
		function.push_back(func3);

		Class cls1(strName1, Point1, var, function);
		cls1.drawClass(pDC);
	}*/
}


// CMidasUMLView �μ�


void CMidasUMLView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMidasUMLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMidasUMLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMidasUMLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMidasUMLView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//void CMidasUMLView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CMidasUMLView ����

#ifdef _DEBUG
void CMidasUMLView::AssertValid() const
{
	CView::AssertValid();
}

void CMidasUMLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMidasUMLDoc* CMidasUMLView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMidasUMLDoc)));
	return (CMidasUMLDoc*)m_pDocument;
}
#endif //_DEBUG



void CMidasUMLView::OnAddClass()
{
	// TODO: ���⿡ ���� ó���� �ڵ带 �߰��մϴ�.
	CAddDlg dlg;
	if (dlg.DoModal() != IDOK) return;
}


void CMidasUMLView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CMenu menu;
	menu.LoadMenuW(IDR_MidasUMLTYPE);
	CMenu *pContextMenu = menu.GetSubMenu(5);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	GetCursorPos(&point);
	ScreenToClient(&point);
	m_point = point;
}