// SaveBMP.cpp: implementation of the CSaveBMP class.
//
//////////////////////////////////////////////////////////////////////
// BMP파일로 저장하기
#include "stdafx.h"
#include "MidasUML.h"
#include "SaveBMP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSaveBMP::CSaveBMP()
{

}

CSaveBMP::~CSaveBMP()
{

}

void CSaveBMP::SaveBitmapToDirectFile(CDC *pDC, CRect BitmapSize, int BitCount, CString strFilePath)
{
	CBitmap bmp, *pOldBmp;
	CDC dcMem;
	BITMAP                  bm;
	BITMAPINFOHEADER        bi;
	LPBITMAPINFOHEADER      lpbi;
	DWORD                   dwLen;
	HANDLE                  handle;
	HANDLE                  hDIB;
	HPALETTE                hPal = NULL;


	/*----- CDC의 내용을 Bitmap으로 전송 ----*/

	dcMem.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, BitmapSize.Width(), BitmapSize.Height());
	pOldBmp = (CBitmap*)dcMem.SelectObject(&bmp);
	dcMem.BitBlt(0, 0, BitmapSize.Width(), BitmapSize.Height(), pDC, 0, 0, SRCCOPY);
	dcMem.SelectObject(pOldBmp);



	if (strFilePath == "")          return;

	/*------------------------- 비트멥 헤더를 기록함 -------------------------*/

	if (hPal == NULL)
		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

	GetObject(HBITMAP(bmp), sizeof(BITMAP), &bm);

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = bm.bmWidth * bm.bmHeight * 3;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	int nColors = (1 << bi.biBitCount);

	if (nColors > 256)
		nColors = 0;

	dwLen = bi.biSize + nColors * sizeof(RGBQUAD);
	hPal = SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);
	RealizePalette(pDC->GetSafeHdc());

	hDIB = GlobalAlloc(GMEM_FIXED, dwLen);
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	GetDIBits(pDC->GetSafeHdc(),
		HBITMAP(bmp),
		0,
		(DWORD)bi.biHeight,
		(LPBYTE)NULL,
		(LPBITMAPINFO)lpbi,
		(DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	if (bi.biSizeImage == 0)
	{
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8)
			* bi.biHeight;
	}


	dwLen += bi.biSizeImage;

	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	GetDIBits(pDC->GetSafeHdc(),
		HBITMAP(bmp),
		0,
		(DWORD)bi.biHeight,
		(LPBYTE)lpbi
		+ (bi.biSize + nColors * sizeof(RGBQUAD)),
		(LPBITMAPINFO)lpbi,
		(DWORD)DIB_RGB_COLORS);

	BITMAPFILEHEADER      hdr;

	hdr.bfType = ((WORD)('M' << 8) | 'B');
	hdr.bfSize = GlobalSize(hDIB) + sizeof(hdr);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD)(sizeof(hdr) + lpbi->biSize + nColors * sizeof(RGBQUAD));


	char* pBmpBuf;

	DWORD FileSize;

	FileSize = sizeof(hdr) + GlobalSize(hDIB);
	pBmpBuf = new char[FileSize];

	memcpy(pBmpBuf, &hdr, sizeof(hdr));
	memcpy(pBmpBuf + sizeof(hdr), lpbi, GlobalSize(hDIB));
	/*--------------------- 실제 파일에 기록함 --------------------------*/
	CFile file;

	file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);

	file.Write(pBmpBuf, FileSize);

	file.Close();


	/*------------------------ 임시로 할당한 메모리를 해제.. -------------*/

	delete[] pBmpBuf;

	if (hDIB)
	{
		GlobalFree(hDIB);
	}

	SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);

}