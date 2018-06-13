// cfghjView.cpp : implementation of the CCfghjView class
//

#include "stdafx.h"
#include "cfghj.h"

#include "cfghjDoc.h"
#include "cfghjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCfghjView

IMPLEMENT_DYNCREATE(CCfghjView, CView)

BEGIN_MESSAGE_MAP(CCfghjView, CView)
	//{{AFX_MSG_MAP(CCfghjView)
	ON_COMMAND(ID_CLAMP_BPP, OnClampBpp)
	ON_COMMAND(ID_SMOOTH1, OnSmooth1)
	ON_COMMAND(ID_EDGE_DET, OnEdgeDet)
	ON_COMMAND(ID_BUTTON32775, OnCreateParticule)
	ON_COMMAND(ID_BUTTON32776, OnCreateNois)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_BUTTON32777, OnFlare)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_BUTTON32778, OnNoise2)
	ON_COMMAND(ID_BUTTON32779, OnPinceau)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfghjView construction/destruction

CCfghjView::CCfghjView():x1(500), y1(10), y2(100)
{
	// TODO: add construction code here

}

CCfghjView::~CCfghjView()
{
}

BOOL CCfghjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCfghjView drawing
	int k=-1;

void CCfghjView::OnDraw(CDC* pDC)
{
	CCfghjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int j, i;
	CDC compDC; 
	RECT rec={0, 0, 500, 256};


	if(!pDoc->m_pImage) return;

	unsigned long* ptr= pDoc->m_pImage;

	++k;
	if(pDoc->m_bNoise2 == 1)
		pDoc->CreateNoise2(k);
	if(pDoc->m_bNoise2 == 2)
		pDoc->CreatePinceaux();

	ptr= &pDoc->m_pImage[(0)*(pDoc->m_h*pDoc->m_w)];
	for(j= 0; j<(signed)pDoc->m_h; ++j){
		for(i= 0; i<(signed)pDoc->m_w; ++i){
			pDC->SetPixel(i, j, *ptr++);
		}
	}

	for(j= 0; j<(y2-y1); ++j){
		int startX= 0;//(rand()%3);
		int maxX=5;//(rand()%3)+5;
		for(i= startX; i<maxX; ++i){
			unsigned char v= pDoc->m_pImage[(j%pDoc->m_h)*pDoc->m_w+(i%pDoc->m_w)];
			if(v!=255)
				pDC->SetPixel(i+(x1-4), j+y1, (0xFF<<16)|((0xFF-v)<<8)|((0xFF-v)<<0));
			else
				pDC->SetPixel(i+(x1-4), j+y1, 0x00FF0000);
		}
	}

	CString chaine;
	chaine.Format("m_nCurImage: %d", k);
	pDC->TextOut(260, 0, chaine);
	InvalidateRect(&rec, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CCfghjView printing

BOOL CCfghjView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCfghjView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCfghjView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCfghjView diagnostics

#ifdef _DEBUG
void CCfghjView::AssertValid() const
{
	CView::AssertValid();
}

void CCfghjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCfghjDoc* CCfghjView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCfghjDoc)));
	return (CCfghjDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCfghjView message handlers

void CCfghjView::OnClampBpp() 
{
	GetDocument()->m_bNoise2= 0;
	GetDocument()->ClampBpp();
	Invalidate();

}

void CCfghjView::OnSmooth1() 
{
	GetDocument()->m_bNoise2= 0;
	GetDocument()->Smooth1();
	Invalidate();
}

void CCfghjView::OnEdgeDet() 
{
	GetDocument()->m_bNoise2= 0;
	GetDocument()->Edge();
	Invalidate();
}

void CCfghjView::OnCreateParticule() 
{
	GetDocument()->CreateParticule();
	Invalidate();
	
}

void CCfghjView::OnCreateNois() 
{
	GetDocument()->m_bNoise2= 0;
	GetDocument()->CreateNoise();
	Invalidate();
	
}

void CCfghjView::OnFlare() 
{
	GetDocument()->m_bNoise2= 0;
	GetDocument()->CreateFlare();
	Invalidate();
}

void CCfghjView::OnNoise2() 
{
	GetDocument()->m_bNoise2= 1;
	GetDocument()->CreateNoise2(0);
	Invalidate();
	
}

void CCfghjView::OnPinceau() 
{
	GetDocument()->m_bNoise2= 2;
	GetDocument()->CreatePinceaux();
	Invalidate();
}

void CCfghjView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	y2= point.y;
	
	Invalidate();
	CView::OnRButtonUp(nFlags, point);
}

void CCfghjView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	x1= point.x;
	y1= point.y;

	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CCfghjView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
}

BOOL CCfghjView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{

	GetDocument()->m_coverage+= zDelta/120;

	if(GetDocument()->m_coverage<0)
		GetDocument()->m_coverage= 0;

	if(GetDocument()->m_coverage>255)
		GetDocument()->m_coverage= 255;

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

