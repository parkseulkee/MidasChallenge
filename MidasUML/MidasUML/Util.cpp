#include "stdafx.h"
#include "Util.h"
#include "Class.h"

double calDistance(POINT Pnt1, POINT Pnt2)
{
	int nDstX = Pnt1.x - Pnt2.x;
	int nDstY = Pnt1.y - Pnt2.y;

	return sqrt((nDstX * nDstX) + (nDstY * nDstY));
}

void getShortPoint(Class Cls1, Class Cls2, POINT * pPnt1, POINT * pPnt2)
{
	POINT Cls1Pnt[4] = { Cls1.getUpCenter(), Cls1.getDownCenter(), Cls1.getRightCenter(), Cls1.getLeftCenter() };
	POINT Cls2Pnt[4] = { Cls2.getUpCenter(), Cls2.getDownCenter(), Cls2.getRightCenter(), Cls2.getLeftCenter() };
	double dMin = DBL_MAX;
	double dTmp;
	int iCls1Min, iCls2Min;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dTmp = calDistance(Cls1Pnt[i], Cls2Pnt[j]);
			if (dTmp < dMin)
			{
				dMin = dTmp;
				iCls1Min = i;
				iCls2Min = j;
			}
		}
	}

	*pPnt1 = Cls1Pnt[iCls1Min];
	*pPnt2 = Cls2Pnt[iCls2Min];

	return;
}

void drawAssociation(CDC * pDC, Class Cls1, Class Cls2, ASSOCIATION_TYPE eAssc)
{
	POINT Cls1Pnt, Cls2Pnt;
	getShortPoint(Cls1, Cls2, &Cls1Pnt, &Cls2Pnt);

	Graphics Graphics(pDC->m_hDC);
	Graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	Color Clr(0, 0, 0);
	Pen Pen(Clr, 2.0);
	AdjustableArrowCap CapInh(5, 5);
	AdjustableArrowCap CapDpd(5, 5, 0);
	switch (eAssc)
	{
	case INHERITANCE:
		Pen.SetCustomEndCap(&CapInh);
		break;
	case DEPENDENCY:
		Pen.SetCustomEndCap(&CapDpd);
		Pen.SetDashStyle(DashStyleDash);
		break;
	}

	Graphics.DrawLine(&Pen, Cls1Pnt.x, Cls1Pnt.y, Cls2Pnt.x, Cls2Pnt.y);

	return;
}

long double calSlope(POINT Pnt1, POINT Pnt2)
{
	return (long double)((Pnt2.y - Pnt1.y) / (Pnt2.x - Pnt1.x));
}

bool chkMiddle(int nStrt, int nEnd, int nCur)
{
	bool bRes = false;

	if ((min(nStrt, nEnd) <= nCur &&
		max(nStrt, nEnd) >= nCur))
		bRes = true;

	return bRes;
}

bool chkBoundary(POINT Strt, POINT End, POINT Cur)
{
	bool bRes = false;

	/*
	if ((min(Strt.x, End.x) <= Cur.x && max(Strt.x, End.x) >= Cur.x) &&
		(min(Strt.y, End.y) <= Cur.y && max(Strt.y, End.y) >= Cur.y))
		*/
	if (chkMiddle(Strt.x, End.x, Cur.x) &&
		chkMiddle(Strt.y, End.y, Cur.y) )
		bRes = true;

	return bRes;
}

bool chkOnAssociation(POINT Strt, POINT End, POINT Cur)
{
	bool bRes = false;
	long double ldSlope = calSlope(Strt, End);

	if (abs(ldSlope) >= 99999 && abs(Cur.x - Strt.x) <= 10 && chkMiddle(Strt.y, End.y, Cur.y))
		bRes = true;
	else if (ldSlope == 0 && abs(Cur.y - Strt.y) <= 10 && chkMiddle(Strt.x, End.x, Cur.x))
		bRes = true;
	else if (chkBoundary(Strt, End, Cur))
	{
		int nX = Cur.x - Strt.x;
		int nY = Cur.y - Strt.y;
		long double ldCurSlope = (long double)nY / nX;
		long double ldEftArea = abs(ldSlope*nX - ldSlope*nX);

		if (ldEftArea >= 0 && ldEftArea <= 0)
			bRes = true;
	}

	return bRes;
}