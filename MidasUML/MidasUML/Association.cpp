#include "stdafx.h"
#include "Association.h"

IMPLEMENT_SERIAL(Association, CObject, 1);

Association::Association()
{

}

Association::Association(const Association &_assoc)
{
	m_at = _assoc.m_at;
	m_mainKey = _assoc.m_mainKey;
	m_subKey = _assoc.m_subKey;
}

Association::Association(ASSOCIATION_TYPE at, int mainKey, int subKey)
{
	m_at = at;
	m_mainKey = mainKey;
	m_subKey = subKey;
}


Association::~Association()
{
}


void Association::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_at << m_mainKey << m_subKey;
	}
	else
	{	// loading code
		int n;
		ar >> n >> m_mainKey >> m_subKey;
		m_at = (ASSOCIATION_TYPE)n;
	}
}
