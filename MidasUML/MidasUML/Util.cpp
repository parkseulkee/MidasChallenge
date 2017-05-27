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

/*
void drawRelation(CDC * pDC, Class Cls1, Class Cls2)
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

	pDC->MoveTo(Cls1Pnt[iCls1Min]);
	pDC->LineTo(Cls2Pnt[iCls2Min]);

	return;
}
*/