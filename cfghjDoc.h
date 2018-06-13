// cfghjDoc.h : interface of the CCfghjDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGHJDOC_H__F79CCDE3_0301_4C1B_9A2E_D8F8D5F7FA1B__INCLUDED_)
#define AFX_CFGHJDOC_H__F79CCDE3_0301_4C1B_9A2E_D8F8D5F7FA1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCfghjDoc : public CDocument
{
protected: // create from serialization only
	CCfghjDoc();
	DECLARE_DYNCREATE(CCfghjDoc)

// Attributes
public:
	int m_bNoise2;
	unsigned long *m_pImage;
	unsigned long m_nbText;
	unsigned long m_w;
	unsigned long m_h;
	long m_coverage;
	float m_sharpeness;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfghjDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreatePinceaux();
	void CreateFlare();
	void CreateNoise();
	void CreateNoise2(int k);
	void CreateParticule();
	void Edge();
	void Smooth2();
	void Smooth1();
	void ClampBpp();
	virtual ~CCfghjDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCfghjDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGHJDOC_H__F79CCDE3_0301_4C1B_9A2E_D8F8D5F7FA1B__INCLUDED_)
