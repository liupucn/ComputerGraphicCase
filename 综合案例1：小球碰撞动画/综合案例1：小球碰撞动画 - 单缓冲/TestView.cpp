
// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_GRAPH_ANIMATION, &CTestView::OnGraphAnimation)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_ANIMATION, &CTestView::OnUpdateGraphAnimation)
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	bPlay = FALSE;
	ptCenter.x = 200, ptCenter.y = 200;
	Direction.x = 1, Direction.y = 1;
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	SingleBuffer(pDC);
}

void CTestView::SingleBuffer(CDC* pDC)//˫�����ͼ
{
	CRect rect;
	GetClientRect(&rect);
	nWidth = rect.Width(), nHeight = rect.Height();
	nHalfWidth = nWidth/2, nHalfHeight = nHeight/2;
	pDC->FillSolidRect(rect, RGB(0.0, 0.0, 0.0));//���ÿͻ�������ɫ
	DrawObject(pDC);//����С��
	CollisionDetection();//��ײ���	
}

void CTestView::DrawObject(CDC* pDC)//����ͼ��
{
	R = nHalfWidth / 5;
	CPoint TopLet(ptCenter.x - R, ptCenter.y - R);
	CPoint BottomRight(ptCenter.x + R, ptCenter.y + R);
	CRect Square(TopLet, BottomRight);
	CBrush NewBrush, *pOldBrush;
	NewBrush.CreateSolidBrush(RGB(255.0, 255.0, 255.0));
	pOldBrush = pDC->SelectObject(&NewBrush);
	pDC->Ellipse(Square);
	pDC->SelectObject(pOldBrush);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	ptCenter.x += Direction.x;
	ptCenter.y += Direction.y;
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

void CTestView::CollisionDetection(void)
{
	if(ptCenter.x - R < 0)//�������߽緢������ײ
		Direction.x = 1;
	if(ptCenter.x + R > nWidth)//������ұ߽緢������ײ
		Direction.x = -1;
	if(ptCenter.y - R < 0)//������ϱ߽緢������ײ
		Direction.y = 1;
	if(ptCenter.y + R > nHeight)//������±߽緢������ײ
		Direction.y = -1;
}

// CTestView printing


void CTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView message handlers
void CTestView::OnGraphAnimation()
{
	// TODO: Add your command handler code here
	bPlay = !bPlay;
	if(bPlay)//���ö�ʱ��
		SetTimer(1, 1, NULL);
	else
		KillTimer(1);
}


void CTestView::OnUpdateGraphAnimation(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(bPlay)
 		pCmdUI->SetCheck(TRUE);
 	else
 		pCmdUI->SetCheck(FALSE);
}
