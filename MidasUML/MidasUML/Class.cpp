#include "stdafx.h"
#include "Class.h"

Class::Class(CString name, POINT point, std::vector<Var> var, std::vector<Function> function, int key)
{
	m_name = name;
	m_point = point;
	m_var = var;
	m_function = function;
	m_key = key;
}


Class::~Class()
{
}

int Class::getHorizonSize()
{
	int i, max = 0, tmp;
	for (i = 0; i < m_var.size(); ++i) {
		tmp = m_var[i].getInfo().GetLength();
		if (max < tmp) {
			max = tmp;
		}
	}
	for (i = 0; i < m_function.size(); ++i) {
		tmp = m_function[i].getInfo().GetLength();
		if (max < tmp) {
			max = tmp;
		}
	}
	tmp = m_name.GetLength();
	if (max < tmp) max = tmp;
	tmp = strlen(STR_CLASS_NAME);
	if (max < tmp) max = tmp;
	tmp = strlen(STR_CLASS_ATTR);
	if (max < tmp) max = tmp;
	tmp = strlen(STR_CLASS_FUNC);
	if (max < tmp) max = tmp;

	return (max * N_FONT_WIDTH) + (N_MARGIN_X * 2);
}
int Class::getVerticalSize()
{
	int varsize = getVarSize();
	int functionsize = getFunctionSize();
	int nLineCnt = 4 + varsize + functionsize;

	return (nLineCnt * N_FONT_HEIGHT) + ((nLineCnt + 1) * N_LINE_PADDING) + (N_MARGIN_Y * 2); // 숫자 폰트 크기에 맞추기
}

POINT Class::getUpCenter() {
	POINT tmp;
	tmp.x = m_point.x + getHorizonSize() / 2;
	tmp.y = m_point.y;
	return tmp;
}
POINT Class::getDownCenter() {
	POINT tmp;
	tmp.x = m_point.x + getHorizonSize() / 2;
	tmp.y = m_point.y + getVerticalSize();
	return tmp;
}
POINT Class::getRightCenter() {
	POINT tmp;
	tmp.x = m_point.x + getHorizonSize();
	tmp.y = m_point.y + getVerticalSize() / 2;
	return tmp;
}
POINT Class::getLeftCenter() {
	POINT tmp;
	tmp.x = m_point.x;
	tmp.y = m_point.y + getVerticalSize() / 2;
	return tmp;
}

void Class::drawClass(CDC * pDC)
{
	POINT Point = getPoint();
	CFont Font, *pOldFont;

	Font.CreatePointFont(N_FONT_SIZE, _T("굴림체"));
	pOldFont = pDC->SelectObject(&Font);

	/* 사각형 그리기 */
	pDC->Rectangle(Point.x, Point.y, Point.x + getHorizonSize(), Point.y + getVerticalSize());

	/* 출력 좌표 초기화 */
	Point.x += N_MARGIN_X;
	Point.y += N_MARGIN_Y;

	/* 클래스 이름 출력 */
	pDC->TextOutW(Point.x, Point.y, CString(STR_CLASS_NAME));
	Point.y += N_HEIGHT;
	pDC->TextOutW(Point.x, Point.y, getName());
	Point.y += N_HEIGHT;

	/* 분할 선 */
	pDC->MoveTo(Point.x - N_MARGIN_X, Point.y);
	pDC->LineTo(Point.x + getHorizonSize() - N_MARGIN_X, Point.y);
	Point.y += N_LINE_PADDING;

	/* 속성 출력 */
	pDC->TextOutW(Point.x, Point.y, CString(STR_CLASS_ATTR));
	Point.y += N_HEIGHT;
	for (std::vector<Var>::iterator iter = m_var.begin(); iter != m_var.end(); iter++)
	{
		pDC->TextOutW(Point.x, Point.y, (*iter).getInfo());
		Point.y += N_HEIGHT;
	}

	/* 분할 선 */
	pDC->MoveTo(Point.x - N_MARGIN_X, Point.y);
	pDC->LineTo(Point.x + getHorizonSize() - N_MARGIN_X, Point.y);
	Point.y += N_LINE_PADDING;

	/* 오퍼레이션 출력 */
	pDC->TextOutW(Point.x, Point.y, CString(STR_CLASS_FUNC));
	Point.y += N_HEIGHT;
	for (std::vector<Function>::iterator iter = m_function.begin(); iter != m_function.end(); iter++)
	{
		pDC->TextOutW(Point.x, Point.y, (*iter).getInfo());
		Point.y += N_HEIGHT;
	}

	pDC->SelectObject(pOldFont);
}