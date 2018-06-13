// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__05FA289B_DE28_4976_A9DD_B6287571C2A9__INCLUDED_)
#define AFX_STDAFX_H__05FA289B_DE28_4976_A9DD_B6287571C2A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma pack( push, forTGA, 1)
typedef struct tagTGA_HDR
{
	unsigned char	nbCharId;
	unsigned char	cmType;
	unsigned char	imgType;
	unsigned short	idxCMFirstEntry;
	unsigned short	idxCMLenght;
	unsigned char	idxCMEntryLenght;
	unsigned short	imgXOrigin;
	unsigned short	imgYOrigin;
	unsigned short	imgWidth;
	unsigned short	imgHeight;
	unsigned char	imgPxSize;
	unsigned char	imgDesc;
}TGA_HDR;
typedef struct _BIT888
{
	unsigned char b,g,r;
}BIT888;
#pragma pack( pop, forTGA )


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__05FA289B_DE28_4976_A9DD_B6287571C2A9__INCLUDED_)
