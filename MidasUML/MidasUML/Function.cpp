#include "stdafx.h"
#include "Function.h"


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