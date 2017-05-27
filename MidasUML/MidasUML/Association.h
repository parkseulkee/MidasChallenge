#pragma once
class Association : public CObject
{
private:
	ASSOCIATION_TYPE m_at;
	int m_mainKey;
	int m_subKey;
public:
	DECLARE_SERIAL(Association);
	Association();
	Association(const Association &_assoc);
	Association(ASSOCIATION_TYPE at, int mainKey, int subKey);
	~Association();
	ASSOCIATION_TYPE getAssociation() { return m_at; }
	int getMainKey() { return m_mainKey; }
	int getSubKey() { return m_subKey; }

	Association& operator=(const Association &_assoc) {
		m_at = _assoc.m_at;
		m_mainKey = _assoc.m_mainKey;
		m_subKey = _assoc.m_subKey;
		return *this;
	}
	virtual void Serialize(CArchive& ar);
};

