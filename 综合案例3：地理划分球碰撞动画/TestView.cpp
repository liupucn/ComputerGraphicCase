
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
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GRAPH_ANIMATION, &CTestView::OnGraphAnimation)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_ANIMATION, &CTestView::OnUpdateGraphAnimation)
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	Alpha = 0.0, Beta = 0.0, Gamma = 0.0;
	Direction.x = 10, Direction.y = 10, Direction.z = 0.0;
	ptCenter.x = 0.0, ptCenter.y = 0.0, ptCenter.z = 0.0;
	bPlay = FALSE;
	nRadius = 200;
	sphere.SetptCenter(ptCenter);
	sphere.ReadVertex();
	sphere.ReadFacet();
	transform.SetMatrix(sphere.P, (sphere.N1 - 1) * sphere.N2 + 2);
	transform.Scale(nRadius);
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
	DoubleBuffer(pDC);//����ͼ��
}

void CTestView::DoubleBuffer(CDC* pDC)//˫�����ͼ
{
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	nWidth = rect.Width(), nHeight = rect.Height();
	nHalfWidth = nWidth / 2, nHalfHeight = nHeight / 2;
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	CDC memDC;//�����ڴ�DC
	memDC.CreateCompatibleDC(pDC);//����һ������ʾDC���ݵ��ڴ�DC
	CBitmap NewBitmap, *pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//���������ڴ�λͼ 
	pOldBitmap = memDC.SelectObject(&NewBitmap);//������λͼѡ���ڴ�DC
	memDC.FillSolidRect(rect, pDC->GetBkColor());//���ÿͻ�������ɫ
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//�ڴ�DC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	DrawObject(&memDC);//����ͼ��
	CollisionDetection();
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY); //���ڴ�DC�е�λͼ��������ʾDC
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
}

void CTestView::DrawObject(CDC* pDC)//����ͼ��
{
	sphere.SetptCenter(ptCenter);
	sphere.Draw(pDC);
}

void CTestView::CollisionDetection(void)//��ײ��⺯��
{
	if (ptCenter.x - nRadius < -nHalfWidth)//�������߽緢������ײ
		Direction.x = 10;
	if (ptCenter.x + nRadius > nHalfWidth)//������ұ߽緢������ײ
		Direction.x = -10;
	if (ptCenter.y + nRadius > nHalfHeight)//������ϱ߽緢������ײ
		Direction.y = -10;
	if (ptCenter.y - nRadius < -nHalfHeight)//������±߽緢������ײ
		Direction.y = 10;
}

void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Alpha = 5;
	Beta = 5;
	Gamma = 10;
	//transform.RotateX(Alpha);
	//transform.RotateY(Beta);
	transform.RotateZ(Gamma);
	ptCenter += Direction;
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (!bPlay)
	{
		switch (nChar)
		{
		case VK_UP:
			Alpha = -5;
			transform.RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha = 5;
			transform.RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta = -5;
			transform.RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta = 5;
			transform.RotateY(Beta);
			break;
		default:
			break;
		}
		Invalidate(FALSE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
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
	if (bPlay)//���ö�ʱ��
		SetTimer(1, 150, NULL);
	else
		KillTimer(1);
}


void CTestView::OnUpdateGraphAnimation(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (bPlay)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
