#pragma once
class Association
{
private:
	ASSOCIATION_TYPE m_at;
	CString m_mainClassName;
	CString m_subClassName;
public:
	Association(ASSOCIATION_TYPE at, CString mainClassName, CString subClassName);
	~Association();
	ASSOCIATION_TYPE getAssociation() { return m_at; }
};

