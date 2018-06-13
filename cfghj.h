// cfghj.h : main header file for the CFGHJ application
//

#if !defined(AFX_CFGHJ_H__73EF146D_071B_43DC_93E2_006FB3CC9E1B__INCLUDED_)
#define AFX_CFGHJ_H__73EF146D_071B_43DC_93E2_006FB3CC9E1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCfghjApp:
// See cfghj.cpp for the implementation of this class
//

class CCfghjApp : public CWinApp
{
public:
	CCfghjApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfghjApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCfghjApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGHJ_H__73EF146D_071B_43DC_93E2_006FB3CC9E1B__INCLUDED_)
