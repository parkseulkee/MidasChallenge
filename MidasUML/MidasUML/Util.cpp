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
	AdjustableArrowCap CapSRL(5, 5, 0);
	//AdjustableArrowCap CapRLT(5, 5, 0);
	switch (eAssc)
	{
	case INHERITANCE:
		Pen.SetCustomEndCap(&CapInh);
		break;
	case DEPENDENCY:
		Pen.SetCustomEndCap(&CapDpd);
		Pen.SetDashStyle(DashStyleDash);
		break;
	case RELATION:
		break;
	case SIDE_RELATION:
		Pen.SetCustomEndCap(&CapSRL);
		break;
	}

	Graphics.DrawLine(&Pen, Cls1Pnt.x, Cls1Pnt.y, Cls2Pnt.x, Cls2Pnt.y);

	return;
}

long double calSlope(POINT Pnt1, POINT Pnt2)
{
	long double ldSlope;
	int	nDstX = (Pnt2.y - Pnt1.y);
	int nDstY = (Pnt2.x - Pnt1.x);

	if (nDstX == 0)
		ldSlope = 99999;
	else
		ldSlope = (long double)(nDstY / nDstX);


	return ldSlope;
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

bool chkOnClass(Class Cls, POINT Cur)
{
	POINT ClsPnt1 = Cls.getPoint();
	POINT ClsPnt2;
	ClsPnt2.x = ClsPnt1.x + Cls.getHorizonSize();
	ClsPnt2.y = ClsPnt1.y + Cls.getVerticalSize();

	return chkBoundary(ClsPnt1, ClsPnt2, Cur);
}

bool chkOnAssociation(POINT Strt, POINT End, POINT Cur)
{
	bool bRes = false;
	long double ldSlope = calSlope(Strt, End);

	if (chkBoundary(Strt, End, Cur))
	{
		double dHeight = abs((Strt.x * End.y + End.x * Cur.y + Cur.x * Strt.y - Strt.x * Cur.y - Cur.x * End.y - End.x * Strt.y) / sqrt((End.x - Strt.x) * (End.x - Strt.x) + (End.y - Strt.y) * (End.y - Strt.y)));
		if( dHeight <= 5 )
			bRes = true;
	}

	return bRes;
}