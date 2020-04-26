
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
#include <math.h>
#define  PI 3.1415926
#define ROUND(d) int(d + 0.5)

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
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	nLightSourceNumber = 1;//��Դ����
	bkColor = CRGB(0.0, 0.0, 0.0);//������Ļ����ɫ
	pLight = new CLighting(nLightSourceNumber);//һά��Դ��̬����
	pLight->LightSource[nLightSourceNumber - 1].SetPosition(300, 500, 100);//���ù�Դλ��
	for (int i = 0; i < nLightSourceNumber; i++)
	{
		pLight->LightSource[i].L_Diffuse = CRGB(1.0, 1.0, 1.0); //��Դ����������ɫ	
		pLight->LightSource[i].L_Specular = CRGB(1.0, 1.0, 1.0);//��Դ����߹���ɫ
		pLight->LightSource[i].L_C0 = 1.0;//����˥��ϵ��
		pLight->LightSource[i].L_C1 = 0.0000001;//����˥��ϵ��
		pLight->LightSource[i].L_C2 = 0.00000001;//����˥��ϵ��
		pLight->LightSource[i].L_OnOff = TRUE;//��Դ����	
	}
	//������ɫ��͸���������
	Material[0].SetAmbient(CRGB(0.5, 0.0, 0.0));//�����ⷴ����
	Material[0].SetDiffuse(CRGB(0.5, 0.0, 0.0));//��������
	Material[0].SetSpecular(CRGB(1.0, 1.0, 1.0));//���淴����
	Material[0].SetEmission(CRGB(0.0, 0.0, 0.0));//��������ɢ����ɫ
	Material[0].M_n = 30.0;//�߹�ָ��
	Material[0].M_eta = 0.0;//�����ʵ������ʾ��͸��
	//���ò�͸��Բ������
	Material[1].SetAmbient(CRGB(0.0, 0.5, 0.0));//����������
	Material[1].SetDiffuse(CRGB(0.0, 0.5, 0.0));//��������
	Material[1].SetSpecular(CRGB(1.0, 1.0, 1.0));//���淴����
	Material[1].SetEmission(CRGB(0.0, 0.0, 0.0));//��������ɢ����ɫ
	Material[1].M_n = 30.0;//�߹�ָ��
	Material[1].M_eta = 1.0;//������
}

CTestView::~CTestView()
{
	delete pLight;
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
	CRect rect;//����ͻ�������
	GetClientRect(&rect);//��ÿͻ�������Ϣ
	nClientWidth = rect.Width();//��ÿͻ����Ŀ��
	nClientHeight = rect.Height();//��ÿͻ����ĸ߶�
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(), rect.Height());//���ô��ڷ�Χ
	pDC->SetViewportExt(rect.Width(), -rect.Height());//x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//�ͻ�������Ϊԭ��
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	pDC->FillSolidRect(rect, RGB(bkColor.red * 255, bkColor.green * 255, bkColor.blue * 255));
	nObjectNumber = 2;//��������
	int RecursionTimes = 5;//�ݹ����
	SetScene(pDC);//���ó���
	//RenderScene(pDC, RecursionTimes);//��Ⱦ����
	RenderAntiAliasingScene(pDC, RecursionTimes);
	for (int i = 0; i < nObjectNumber; i++)
		delete pObjects[i];
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

void CTestView::OnInitialUpdate(void)
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
}

void CTestView::SetScene(CDC* pDC)//���ó�������
{
	pObjects[0] = new CSphere(100, CP3(0, 0, 20), Material[0]);//���첻͸�����棨�뾶������λ�ã����ʣ�
	pObjects[1] = new CTorus(CP3(0, 0, 0), 200, 80, Material[1]);//���첻͸��Բ���棨����λ�ã����뾶�����뾶�����ʣ�
	PixelSize = 1;//�����ش�С
	ViewPlane.SetResolution(ROUND(nClientWidth / PixelSize), ROUND(nClientHeight / PixelSize));
	R = 600;//�Ӿ�
	zViewPlane = -200;//��ƽ����zw���ϵ�λ��
	d = R - zViewPlane;//�Ӿ�
	EyePoint = CP3(0, 0, R);//�����ӵ�
}

void CTestView::RenderScene(CDC* pDC, int nDepth)//��Ⱦ��������
{
	for (int nRow = 0; nRow < ViewPlane.VerRes; nRow++)//��ɨ��
	{
		for (int nCol = 0; nCol < ViewPlane.HorRes; nCol++)//��ɨ��
		{
			CP2 Pixel(PixelSize*(nCol - ViewPlane.HorRes / 2 + 0.5), PixelSize*(nRow - ViewPlane.VerRes / 2 + 0.5));//��Ļ��������
			CVector3 Direction(EyePoint, CP3(Pixel.x, Pixel.y, zViewPlane));//���ӵ㵽��Ļĳһ���ص�����Ϊ���ߵķ�������
			Direction = Direction.Normalize();//�淶����������
			CVector3 Origin = CVector3(EyePoint);//���ӵ���Ϊ���ߵ����
			CRay Ray(Origin, Direction);//�������
			CRGB PixelColor = RayTracing(Ray, nDepth);
			PixelColor.Normalize();//��ɫ�淶������
			CPoint LBPoint(ROUND(Pixel.x - PixelSize / 2.0), ROUND(Pixel.y - PixelSize / 2.0));
			CPoint RTPoint(ROUND(Pixel.x + PixelSize / 2.0), ROUND(Pixel.y + PixelSize / 2.0));
			CRect PixelRect(LBPoint, RTPoint);
			pDC->FillSolidRect(PixelRect, RGB(PixelColor.red * 255, PixelColor.green * 255, PixelColor.blue * 255));
		}
	}
}

void CTestView::RenderAntiAliasingScene(CDC* pDC, int nDepth)//��Ⱦ��������������
{
	ViewPlane.SetSampleNumber(25);//���ز���������Ϊƽ������
	int n = (int)sqrt((double)ViewPlane.SampleNumber);
	for (int nRow = 0; nRow < ViewPlane.VerRes; nRow++)//��ɨ��
	{
		for (int nCol = 0; nCol < ViewPlane.HorRes; nCol++)//��ɨ��
		{
			CP2 SPoint;
			CRGB SPointColor = bkColor;
			for (int p = 0; p < n; p++)//ɨ��������
			{
				for (int q = 0; q < n; q++)
				{
					SPoint.x = PixelSize * (nCol - ViewPlane.HorRes / 2 + (q + 0.5) / n);//����������
					SPoint.y = PixelSize * (nRow - ViewPlane.VerRes / 2 + (p + 0.5) / n);
					CVector3 Direction(EyePoint, CP3(SPoint.x, SPoint.y, zViewPlane));//���ӵ㵽��Ļĳһ���ص�����Ϊ���ߵķ�������
					Direction = Direction.Normalize();//�淶����������
					CVector3 Origin = CVector3(EyePoint);//���ӵ���Ϊ���ߵ����
					CRay Ray(Origin, Direction);//�������
					SPointColor += RayTracing(Ray, nDepth);
				}
			}
			CPoint LBPoint(ROUND(SPoint.x - PixelSize / 2), ROUND(SPoint.y - PixelSize / 2));
			CPoint RTPoint(ROUND(SPoint.x + PixelSize / 2), ROUND(SPoint.y + PixelSize / 2));
			CRect PixelRect(LBPoint, RTPoint);
			CRGB PixelRectColor = SPointColor / ViewPlane.SampleNumber;//ƽ��������ɫ
			PixelRectColor.Normalize();//��ɫ�淶������
			pDC->FillSolidRect(PixelRect, RGB(PixelRectColor.red * 255, PixelRectColor.green * 255, PixelRectColor.blue * 255));
		}
	}
}

CRGB CTestView::RayTracing(CRay Ray, int nDepth)//���߸��ٺ���
{
	if (!nDepth)//��Ⱦ���ΪnDepth
		return bkColor;
	CIntersection MiniHit;//��С��ײ��
	MiniHit.t = HugeValue;
	for (int i = 0; i < nObjectNumber; i++)//������������
	{
		CIntersection hit;
		if (pObjects[i]->Hit(Ray, hit) && hit.t < MiniHit.t)
			MiniHit = hit;//������С��ײ��
	}
	if (MiniHit.t == HugeValue)//����������û����ײ��
		return bkColor;
	else
		return Shader(Ray, MiniHit, nDepth);//����С��ײ�������ɫ	
}

CRGB CTestView::Shader(CRay Ray, CIntersection  Hit, int nDepth)//��ɫ����
{
	CRGB LocalI(0.0, 0.0, 0.0), TotalI;//�ֲ���ǿ���ܹ�ǿ
	BOOL bShowShadow = FALSE;//��Ӱ����
	if (ShadowCast(Hit) && bShowShadow)
		LocalI += pLight->Ambient * Hit.Material.M_Ambient;//ֻ�л�����
	else
		LocalI += pLight->Illuminate(EyePoint, Hit.Point, Hit.Normal, &Hit.Material);//�ֲ���ǿ
	double ks = 0.4, kt = 0.9;//ksΪ����ϵ����ktΪ����ϵ��
	CRGB ReflectionI = RayTracing(Reflect(Ray, Hit), nDepth - 1); //�����ǿ
	CRGB RefractionI = RayTracing(Refract(Ray, Hit), nDepth - 1); //�����ǿ
	if (Hit.Material.M_eta)//����͸��
		TotalI = LocalI + ks * ReflectionI + kt * RefractionI;//��������
	else
		TotalI = LocalI + ks * ReflectionI;//����������
	return TotalI;
}

CRay CTestView::Reflect(CRay IncidentLight, CIntersection Hit)//���亯��
{
	CRay ReflectionRay;//�������
	ReflectionRay.Origin = Hit.Point;//������ߵ�Դ��
	CVector3 V(-IncidentLight.Direction);//�����������
	CVector3 N = Hit.Normal.Normalize();//��ײ�㷨����
	CVector3 R = 2.0 * N * fabs(DotProduct(N, V)) - V;//���䷽��λ����
	ReflectionRay.Direction = R;//������ߵĵ�λ��������
	return ReflectionRay;
}

CRay CTestView::Refract(CRay IncidentLight, CIntersection Hit)//���亯��
{
	CRay RefractionRay;//�������
	RefractionRay.Origin = Hit.Point;//������ߵ�Դ��
	Hit.Normal = Hit.Normal.Normalize();//�淶����ײ��ķ�����
	CVector3 V(-IncidentLight.Direction);//�����������
	double NdotV = DotProduct(Hit.Normal, V);//���㷨�������������ĵ��
	double Eta = Hit.Material.M_eta;//���������
	if (NdotV < 0.0)
	{
		NdotV = -NdotV;
		Hit.Normal = -Hit.Normal;
		Eta = 1.0 / Eta;
	}
	double costheta2 = sqrt(1 - (1 - NdotV * NdotV) / (Eta * Eta));
	CVector3 T = IncidentLight.Direction / Eta - (costheta2 - NdotV / Eta) * Hit.Normal;//���䷽��λ����
	RefractionRay.Direction = T;//������ߵĵ�λ��������	
	return RefractionRay;
}

BOOL CTestView::ShadowCast(CIntersection Hit)//��Ӱ����
{
	for (int i = 0; i < nLightSourceNumber; i++)
	{
		CVector3 SL(Hit.Point, pLight->LightSource[i].L_Position);// LΪ���������
		nHittoLightSource = SL.Magnitude();//��ײ�㵽��Դ�ľ���
		SL = SL.Normalize();//�淶����Ӱ���ߵķ�������
		CRay ShadowRay(Hit.Point, SL);//��Ӱ����
		CIntersection ShadowHit;
		for (int j = 0; j < nObjectNumber; j++)//���������еĸ�������
			pObjects[j]->Hit(ShadowRay, ShadowHit);
		if (ShadowHit.t < nHittoLightSource)
			return TRUE;
	}
	return FALSE;
}

