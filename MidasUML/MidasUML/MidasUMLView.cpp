
// MidasUMLView.cpp : CMidasUMLView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MidasUML.h"
#include "Util.h"
#endif

#include "MidasUMLDoc.h"
#include "MidasUMLView.h"
#include "SaveBMP.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidasUMLView

IMPLEMENT_DYNCREATE(CMidasUMLView, CView)

BEGIN_MESSAGE_MAP(CMidasUMLView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMidasUMLView::OnFilePrintPreview)
//	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ADD_CLASS, &CMidasUMLView::OnAddClass)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ADD_ACCOS, &CMidasUMLView::OnAddAccos)
	ON_COMMAND(ID_BUTTON_BMP_SAVE, &CMidasUMLView::OnButtonBmpSave)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_DELETE_ASSOC, &CMidasUMLView::OnDeleteAssoc)
END_MESSAGE_MAP()

// CMidasUMLView 생성/소멸

CMidasUMLView::CMidasUMLView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_point = { 0,0 };
	selectAssoc = -1;
}

CMidasUMLView::~CMidasUMLView()
{
}

BOOL CMidasUMLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMidasUMLView 그리기

void CMidasUMLView::OnDraw(CDC* pDC)
{
	CMidasUMLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (int i = 0; i < pDoc->getSize(); i++) {
		Class _class = pDoc->getClass(i);
		_class.drawClass(pDC);
	}

	for (int i = 0;i < pDoc->getAssocSize();i++) {
		Association _association = pDoc->getAssociation(i);
		Class main = pDoc->getAssociationClass(_association.getMainKey());
		Class sub = pDoc->getAssociationClass(_association.getSubKey());
		ASSOCIATION_TYPE eAssc = _association.getAssociation();
		/*CString str;
		str.Format(_T("%d %s %s"), (int)_association.getAssociation(), main.getName(), sub.getName());
		pDC->TextOutW(0, i * 30, str);*/
		drawAssociation(pDC, main, sub, eAssc);
	}
	/*
	Graphics Graphics(pDC->m_hDC);
	Graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	Color Clr(0, 0, 0);
	Pen Pen(Clr, 2.0);
	AdjustableArrowCap CapInh(5, 5);
	AdjustableArrowCap CapDpd(5, 5, 0);
	switch (0)
	{
	case INHERITANCE:
		Pen.SetCustomEndCap(&CapInh);
		break;
	case DEPENDENCY:
		Pen.SetCustomEndCap(&CapDpd);
		Pen.SetDashStyle(DashStyleDash);
		break;
	}
	Graphics.DrawLine(&Pen, 10, 200, 200, 300);
	Pen.SetCustomEndCap(&CapDpd);
	Pen.SetDashStyle(DashStyleDash);
	Graphics.DrawLine(&Pen, 20, 220, 220, 320);
	*/

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

		POINT Point2;
		Point2.x = 300;
		Point2.y = 10;

		Class cls2(strName1, Point2, var, function);
		cls2.drawClass(pDC);

		POINT Point3, Point4;
		getShortPoint(cls1, cls2, &Point3, &Point4);
		pDC->MoveTo(Point3);
		pDC->LineTo(Point4);
	}*/
}


// CMidasUMLView 인쇄


void CMidasUMLView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMidasUMLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMidasUMLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMidasUMLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CMidasUMLView 진단

#ifdef _DEBUG
void CMidasUMLView::AssertValid() const
{
	CView::AssertValid();
}

void CMidasUMLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMidasUMLDoc* CMidasUMLView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMidasUMLDoc)));
	return (CMidasUMLDoc*)m_pDocument;
}
#endif //_DEBUG



void CMidasUMLView::OnAddClass()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAddDlg dlg;
	if (dlg.DoModal() != IDOK) return;
}


void CMidasUMLView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMenu menu;
	menu.LoadMenuW(IDR_MidasUMLTYPE);
	CMenu *pContextMenu = menu.GetSubMenu(5);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	GetCursorPos(&point);
	ScreenToClient(&point);
	m_point = point;
	

	CMidasUMLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < pDoc->getAssocSize(); i++) {
		Association _association = pDoc->getAssociation(i);
		Class main = pDoc->getAssociationClass(_association.getMainKey());
		Class sub = pDoc->getAssociationClass(_association.getSubKey());

		POINT Pnt1, Pnt2;
		getShortPoint(main, sub, &Pnt1, &Pnt2);
		if (chkOnAssociation(Pnt1, Pnt2, point))
		{
			selectAssoc = i;
		}
	}
}


void CMidasUMLView::OnAddAccos()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAddAccDlg dlg;
	if (dlg.DoModal() != IDOK) return;
}


void CMidasUMLView::OnButtonBmpSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: Add your command handler code here
	CSaveBMP *sBmp = new CSaveBMP();
	CDC *pDC = GetDC();
	CRect rt;
	GetClientRect(rt);

	/*	CDC BufferDC;
	BufferDC.CreateCompatibleDC(pDC);

	// 화면 DC와 호환성 있는 메모리 비트맵을 만듦
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(pDC, rt.right, rt.bottom);

	// 메모리 DC에 메모리 비트맵을 선택
	CBitmap *pOldBitmap = (CBitmap *)BufferDC.SelectObject(&bmpBuffer);

	BufferDC.BitBlt(0, 0, rt.right, rt.bottom, pDC, 0, 0, SRCCOPY);

	// DC 복원
	BufferDC.SelectObject(pOldBitmap);
	*/


	// Save Dialog
	LPCTSTR lpszFilter = (LPCTSTR)"BMP File(*.bmp)|*.bmp|All Files|*.*||";
	CString strPath;
	bool m_bDraw = FALSE;

	/// TRUE : Read,  FALSE : Save
	CFileDialog dlg(FALSE);

	if (dlg.DoModal() == IDOK)
	{
		//strPath.Format("%s", dlg.GetFileName());
		strPath = dlg.GetPathName();
		//AfxMessageBox(strPath);
		m_bDraw = TRUE;
	}

	RedrawWindow();

	if (m_bDraw) {
		sBmp->SaveBitmapToDirectFile(pDC, rt, 0, strPath);
	}
}


void CMidasUMLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	
	//CString str1;
	//str1.Format(_T("(%d,%d)      "), point.x, point.y);
	//CDC *pDC = GetDC();
	//pDC->TextOutW(0, 0, str1);

	//CMidasUMLDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//for (int i = 0; i < pDoc->getAssocSize(); i++) {
	//	Association _association = pDoc->getAssociation(i);
	//	Class main = pDoc->getAssociationClass(_association.getMainKey());
	//	Class sub = pDoc->getAssociationClass(_association.getSubKey());

	//	POINT Pnt1, Pnt2;
	//	getShortPoint(main, sub, &Pnt1, &Pnt2);
	//	if (chkOnAssociation(Pnt1, Pnt2, point))
	//	{
	//		CString str;
	//		str.Format(_T("%d (%d,%d) (%d, %d)"), i, Pnt1.x, Pnt1.y, Pnt2.x, Pnt2.y);
	//		MessageBox(str);
	//	}
	//}
	//

	CView::OnLButtonDown(nFlags, point);
}


void CMidasUMLView::OnDeleteAssoc()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMidasUMLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (selectAssoc == -1)return;
	pDoc->deleteAssociation(selectAssoc);
	Invalidate();
	selectAssoc = -1;
}
