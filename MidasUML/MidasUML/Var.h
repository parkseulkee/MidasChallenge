#pragma once
class Var : public CObject
{
private:
	ACCESS_TYPE m_at;
	CString m_name;
	CString m_type;
public:
	DECLARE_SERIAL(Var);
	Var(const Var &_var);
	Var();
	Var(ACCESS_TYPE at, CString name, CString type);
	~Var();
	CString getInfo();
	void edit(ACCESS_TYPE at, CString name, CString type);
	virtual void Serialize(CArchive& ar);

	Var& operator=(const Var &_var) {
		m_at = _var.m_at;
		m_name = _var.m_name;
		m_type = _var.m_type;
		return *this;
	}
};

