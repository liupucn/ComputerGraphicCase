
// TestView.h : interface of the CTestView class
//

#pragma once
#include "ViewPlane.h"//��ƽ��
#include "Lighting.h"//������
#include "Material.h"//������
#include "Sphere.h"//������
#include "Torus.h"//Բ����
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
	void SetScene(CDC* pDC);//���ó���
	void RenderScene(CDC* pDC,int nDepth);//��Ⱦ����
	void RenderAntiAliasingScene(CDC* pDC,int nDepth);//��Ⱦ����������
    CRGB RayTracing(CRay Ray, int nDepth);//���߸���
	CRay Reflect(CRay IncidentLight, CIntersection Hit);//����
    CRGB Shader(CRay Ray, CIntersection  Hit, int nDepth);//��ɫ    
    CRay Refract(CRay IncidentLight, CIntersection Hit);//����
	BOOL ShadowCast(CIntersection Hit);//Ͷ����Ӱ
public:
	
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
	int nClientWidth,nClientHeight;//�ͻ�����Ⱥ͸߶�
	int	nLightSourceNumber;//��Դ����
	CLighting* pLight;//���ջ���
	int nVResolution,nHResolution;//ˮƽ�봹ֱ�ֱ���
	CViewPlane ViewPlane;//��ƽ��
	CGeometricObject* pObjects[2];//���ζ���ָ��
	CMaterial Material[2];//�������
	int nObjectNumber;//��������
	CRGB bkColor;//����ɫ
	double PixelSize;//���ش�С
	CP3 EyePoint;//�ӵ�
	double zViewPlane;//��ƽ����z���ϵ�λ��
	double R,d;//�Ӿ����Ӿ�
	double nHittoLightSource;//��ײ�����Դ�ľ���
	CIntersection MiniHit;//��С��ײ�� 
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

