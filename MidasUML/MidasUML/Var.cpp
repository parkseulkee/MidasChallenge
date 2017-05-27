#include "stdafx.h"
#include "Var.h"

IMPLEMENT_SERIAL(Var, CObject, 1);


Var::Var(const Var &_var)
{
	m_at = _var.m_at;
	m_name = _var.m_name;
	m_type = _var.m_type;
}

Var::Var()
{
	m_at = PRIVATE;
	m_name = _T("");
	m_type = _T("");
}

Var::Var(ACCESS_TYPE at, CString name, CString type)
{
	m_at = at;
	m_name = name;
	m_type = type;
}


Var::~Var()
{
}

CString Var::getInfo()
{
	CString info;
	switch (m_at) {
	case PRIVATE: info += "-"; break;
	case PROTECTED: info += "#"; break;
	case PUBLIC: info += "+"; break;
	}
	info += m_name;
	info += ":";
	info += m_type;

	return info;
}

void Var::edit(ACCESS_TYPE at, CString name, CString type)
{
	m_at = at;
	m_name = name;
	m_type = type;
}


void Var::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_at << m_name << m_type;
	}
	else
	{	// loading code
		int n;
		ar >> n >> m_name >> m_type;
		m_at = (ACCESS_TYPE)n;
	}
}
