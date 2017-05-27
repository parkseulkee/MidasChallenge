
// MidasUMLDoc.h : CMidasUMLDoc 클래스의 인터페이스
//


#pragma once

#include "Class.h"
#include "Association.h"

class CMidasUMLDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMidasUMLDoc();
	DECLARE_DYNCREATE(CMidasUMLDoc)

// 특성입니다.
private:
	std::vector<Class> classes;
	std::vector<Association> associations;
	int key;
public:
	Class getClass(int id) { return classes[id]; }
	Class getAssociationClass(int key);
	void addClass(CString name, POINT point, std::vector<Var> var, std::vector<Function> function);
	void deleteClass(int id) {
		classes.erase(classes.begin() + id);
		SetModifiedFlag();
	}
	int getSize() { return classes.size(); }

	Association getAssociation(int id) { return associations[id]; }
	void addAssociation(int mainkey, int subKey, ASSOCIATION_TYPE at);
	void deleteAssociation(int id) { 
		associations.erase(associations.begin() + id);
		SetModifiedFlag();
	}
	int getAssocSize() { return associations.size(); }
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMidasUMLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
};
