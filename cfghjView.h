// cfghjView.h : interface of the CCfghjView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGHJVIEW_H__6336BF1E_AA6B_4E79_88B3_8DF5C26F7105__INCLUDED_)
#define AFX_CFGHJVIEW_H__6336BF1E_AA6B_4E79_88B3_8DF5C26F7105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCfghjView : public CView
{
protected: // create from serialization only
	CCfghjView();
	DECLARE_DYNCREATE(CCfghjView)

// Attributes
public:
	CCfghjDoc* GetDocument();

	int x1, y1, x2, y2;
	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfghjView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCfghjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCfghjView)
	afx_msg void OnClampBpp();
	afx_msg void OnSmooth1();
	afx_msg void OnEdgeDet();
	afx_msg void OnCreateParticule();
	afx_msg void OnCreateNois();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFlare();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnNoise2();
	afx_msg void OnPinceau();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in cfghjView.cpp
inline CCfghjDoc* CCfghjView::GetDocument()
   { return (CCfghjDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGHJVIEW_H__6336BF1E_AA6B_4E79_88B3_8DF5C26F7105__INCLUDED_)
