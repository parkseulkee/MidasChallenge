#include "stdafx.h"
#include "Function.h"

IMPLEMENT_SERIAL(Function, CObject, 1);

Function::Function(const Function &_function)
{
	m_at = _function.m_at;
	m_return_type = _function.m_return_type;
	m_name = _function.m_name;
	m_parameter = _function.m_parameter;
}

Function::Function()
{
	m_at = PRIVATE;
	m_return_type = _T("");
	m_name = _T("");
	m_parameter = _T("");
}

Function::Function(ACCESS_TYPE at, CString return_type, CString name, CString parameter)
{
	m_at = at;
	m_return_type = return_type;
	m_name = name;
	m_parameter = parameter;
}


Function::~Function()
{
}

CString Function::getInfo()
{
	CString info;
	switch (m_at) {
	case PRIVATE: info += "-"; break;
	case PROTECTED: info += "#"; break;
	case PUBLIC: info += "+"; break;
	}
	info += m_name;
	info += "(";
	info += m_parameter;
	info += "):";
	info += m_return_type;

	return info;
}

void Function::edit(ACCESS_TYPE at, CString return_type, CString name, CString parameter)
{
	m_at = at;
	m_return_type = return_type;
	m_name = name;
	m_parameter = parameter;
}


void Function::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_at << m_return_type << m_name << m_parameter;
	}
	else
	{	// loading code
		int n;
		ar >> n >> m_return_type >> m_name >> m_parameter;
		m_at = (ACCESS_TYPE)n;
	}
}
