#include "stdafx.h"
#include "Association.h"


Association::Association(ASSOCIATION_TYPE at, int mainKey, int subKey)
{
	m_at = at;
	m_mainKey = mainKey;
	m_subKey = subKey;
}


Association::~Association()
{
}
