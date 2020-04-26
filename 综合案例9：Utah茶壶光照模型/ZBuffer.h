#pragma once
#include "Point3.h"
#include "Texture.h"
#include "Lighting.h"//Phongģ��

class CZBuffer  
{
public:
	CZBuffer(void);
    virtual ~CZBuffer(void);
	void SetPoint(CP3 P0, CP3 P1, CP3 P2, CVector3 N0, CVector3 N1, CVector3 N2, CT2 T0, CT2 T1, CT2 T2);// �����γ�ʼ��
	void InitialDepthBuffer(int nWidth, int nHeight, double zDepth);//��ʼ����Ȼ�����
	void PhongShader(CDC* pDC, CP3 ViewPoint, CLighting* pLight, CMaterial* pMaterial, CTexture* pTexture);//�⻬��ɫ
private:
	void DDA(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//�߱��	
	CVector3 LinearInterp(double t, double tStart, double tEnd, CVector3 vStart, CVector3 vEnd);//���������Բ�ֵ
	CT2 LinearInterp(double t, double tStart, double tEnd, CT2 uvStart, CT2 uvEnd);//�����ַ���Բ�ֵ
	void SortVertex(void);//��������
	CRGB GetTexture(int u, int v, CTexture* pTexture);//��ȡ������ɫ	
private:
	CP3 P0, P1, P2;//�����εĸ���������
	CPoint3 point0, point1, point2;//�����ε�������������
	CPoint2* SpanLeft; //��ȵ���������־
	CPoint2* SpanRight;//��ȵ��յ������־
	int nIndex;//��¼ɨ��������
	double** zBuffer;//��Ȼ�����
	int nWidth, nHeight;//�����������߶�	
};