#include "stdafx.h"
#include "Association.h"


Association::Association(ASSOCIATION_TYPE at, CString mainClassName, CString subClassName)
{
	m_at = at;
	m_mainClassName = mainClassName;
	m_subClassName = subClassName;
}


Association::~Association()
{
}
