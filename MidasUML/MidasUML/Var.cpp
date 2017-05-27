#include "stdafx.h"
#include "Var.h"


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