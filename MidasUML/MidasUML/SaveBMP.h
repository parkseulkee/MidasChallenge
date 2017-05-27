// SaveBMP.h: interface for the CSaveBMP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVEBMP_H__0A7207D1_3C7C_4B6B_B90E_91D225A5006A__INCLUDED_)
#define AFX_SAVEBMP_H__0A7207D1_3C7C_4B6B_B90E_91D225A5006A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSaveBMP
{
public:
	void SaveBitmapToDirectFile(CDC *pDC, CRect BitmapSize, int BitCount, CString strFilePath);
	CSaveBMP();
	virtual ~CSaveBMP();

};

#endif // !defined(AFX_SAVEBMP_H__0A7207D1_3C7C_4B6B_B90E_91D225A5006A__INCLUDED_)