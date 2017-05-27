#pragma once

class Function
{
private:
	ACCESS_TYPE m_at;
	CString m_return_type;
	CString m_name;
	CString m_parameter;
public:
	Function(ACCESS_TYPE at, CString return_type, CString name, CString parameter);
	~Function();
	CString getInfo();
	void edit(ACCESS_TYPE at, CString return_type, CString name, CString parameter);
};

