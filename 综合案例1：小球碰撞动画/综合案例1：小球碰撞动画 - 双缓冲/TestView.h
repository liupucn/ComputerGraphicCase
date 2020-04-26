
// TestView.h : interface of the CTestView class
//

#pragma once


class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument() const;

// Operations
public:
	void DoubleBuffer(CDC* pDC);//˫�����ͼ
	void DrawObject(CDC* pDC);//���ƶ���
	void CollisionDetection(void);//��ײ��⺯��
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int nWidth,nHeight;//�ͻ����Ŀ�Ⱥ͸߶�
	int nHalfWidth,nHalfHeight;//�ͻ������Ͱ��
	int R;//Բ�İ뾶
	CPoint Direction;//�˶�����
	CPoint ptCenter;//Բ������
	BOOL bPlay;//��������
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGraphAnimation();
	afx_msg void OnUpdateGraphAnimation(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

