#pragma once
class Association
{
private:
	ASSOCIATION_TYPE m_at;
	int m_mainKey;
	int m_subKey;
public:
	Association(ASSOCIATION_TYPE at, int mainKey, int subKey);
	~Association();
	ASSOCIATION_TYPE getAssociation() { return m_at; }
	int getMainKey() { return m_mainKey; }
	int getSubKey() { return m_subKey; }
};

