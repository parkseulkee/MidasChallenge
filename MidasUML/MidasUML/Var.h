#pragma once
class Var
{
private:
	ACCESS_TYPE m_at;
	CString m_name;
	CString m_type;
public:
	Var(ACCESS_TYPE at, CString name, CString type);
	~Var();
	CString getInfo();
	void edit(ACCESS_TYPE at, CString name, CString type);
};

