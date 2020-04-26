
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
	Alpha = 0.0, Beta = 0.0;
	bPlay = FALSE;
	pyramid[0].ReadVertex();
	pyramid[0].ReadFacet();
	transform[0].SetMatrix(pyramid[0].P, 5);
	transform[0].Scale(200);
	transform[0].Translate(-160, -100, 100);	
	transform[0].RotateY(-30);

	pyramid[1].ReadVertex();
	pyramid[1].ReadFacet();
	transform[1].SetMatrix(pyramid[1].P, 5);
	transform[1].Scale(150);
	transform[1].Translate(100, -80, 100);
	transform[1].RotateY(-26);

	pyramid[2].ReadVertex();
	pyramid[2].ReadFacet();
	transform[2].SetMatrix(pyramid[2].P, 5);
	transform[2].Scale(80);
	transform[2].Translate(250, -50, 100);	
	transform[2].RotateY(-20);
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
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width()/2, rect.Height()/2);
	CDC memDC;//�����ڴ�DC
	memDC.CreateCompatibleDC(pDC);//����һ������ʾDC���ݵ��ڴ�DC
	CBitmap NewBitmap, *pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(), rect.Height());//���������ڴ�λͼ 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//������λͼѡ���ڴ�DC
	memDC.FillSolidRect(rect,pDC->GetBkColor());//���ÿͻ�������ɫ
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//�ڴ�DC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	DrawObject(&memDC);//����ͼ��
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width()/2, -rect.Height()/2, SRCCOPY); //���ڴ�DC�е�λͼ��������ʾDC
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
}

void CTestView::DrawObject(CDC* pDC)//����ͼ��
{
	pyramid[0].Draw(pDC);
	pyramid[1].Draw(pDC);
	pyramid[2].Draw(pDC);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Beta = 5;
	transform[0].RotateY(Beta);
	transform[1].RotateY(Beta);
	transform[2].RotateY(Beta);
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(!bPlay)
	{
		switch(nChar)
		{
		case VK_UP:
			Alpha = -5;
			transform[0].RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha = 5;
			transform[0].RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta = -5;
			transform[0].RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta = 5;
			transform[0].RotateY(Beta);
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
	if(bPlay)//���ö�ʱ��
		SetTimer(1,150,NULL);	
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
