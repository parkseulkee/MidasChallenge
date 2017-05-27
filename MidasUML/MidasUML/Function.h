#pragma once

class Function : public CObject
{
private:
	ACCESS_TYPE m_at;
	CString m_return_type;
	CString m_name;
	CString m_parameter;
public:
	DECLARE_SERIAL(Function);
	Function(const Function &_function);
	Function();
	Function(ACCESS_TYPE at, CString return_type, CString name, CString parameter);
	~Function();
	CString getInfo();
	void edit(ACCESS_TYPE at, CString return_type, CString name, CString parameter);

	Function& operator=(const Function& _function) {
		m_at = _function.m_at;
		m_return_type = _function.m_return_type;
		m_name = _function.m_name;
		m_parameter = _function.m_parameter;
		return *this;
	}
	virtual void Serialize(CArchive& ar);
};

