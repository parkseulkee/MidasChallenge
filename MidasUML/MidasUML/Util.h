#pragma once
#include "stdafx.h"
#include "Class.h"

double calDistance(POINT Point1, POINT Point2);
void getShortPoint(Class Cls1, Class Cls2, POINT * pPnt1, POINT * pPnt2);
void drawAssociation(CDC * pDC, Class Cls1, Class Cls2, ASSOCIATION_TYPE eAssc);