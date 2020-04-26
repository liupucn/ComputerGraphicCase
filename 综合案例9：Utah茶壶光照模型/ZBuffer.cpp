#include "stdafx.h"
#include "Test.h"
#include "ZBuffer.h"
#include <math.h>
#define ROUND(d) int(d + 0.5)//��������궨��


CZBuffer::CZBuffer(void)
{
	zBuffer = NULL;
}

CZBuffer::~CZBuffer(void)
{
	for(int i = 0;i < nWidth;i++)
	{
		delete[] zBuffer[i];
		zBuffer[i] = NULL;
	}
	if(zBuffer != NULL)
	{
		delete zBuffer;
		zBuffer = NULL;
	}	
}

void CZBuffer::SetPoint(CP3 P0, CP3 P1, CP3 P2, CVector3 N0, CVector3 N1, CVector3 N2, CT2 T0, CT2 T1, CT2 T2)
{
	this->P0 = P0, this->P1 = P1, this->P2 = P2;
	point0.x = ROUND(P0.x);
	point0.y = ROUND(P0.y);
	point0.z = P0.z;
	point0.c = P0.c;
	point0.n = N0;
	point0.t = T0;
	point1.x = ROUND(P1.x);
	point1.y = ROUND(P1.y);
	point1.z = P1.z;
	point1.c = P1.c;
	point1.n = N1;
	point1.t = T1;
	point2.x = ROUND(P2.x);
	point2.y = ROUND(P2.y);
	point2.z = P2.z;
	point2.c = P2.c;
	point2.n = N2;
	point2.t = T2;
}

void CZBuffer::PhongShader(CDC* pDC, CP3 ViewPoint, CLighting* pLight, CMaterial* pMaterial, CTexture* pTexture)
{
	double	CurrentDepth = 0.0;//��ǰɨ���ߵ����
	CVector3 Vector01(P0, P1), Vector02(P0, P2);
	CVector3 fNormal = CrossProduct(Vector01, Vector02);
	double A = fNormal.x, B = fNormal.y, C = fNormal.z;//ƽ�淽��Ax+By+Cz��D=0��ϵ��
	double D = -A * P0.x - B * P0.y - C * P0.z;//��ǰɨ��������x��������Ȳ���
	if(fabs(C) < 1e-4)
		C = 1.0;
	double DepthStep = -A / C;//����ɨ������Ȳ�������
	SortVertex();//�����ζ�������
	//���������θ��ǵ�ɨ��������
	int nTotalLine = point1.y - point0.y + 1;
	//����span��������յ�����
	SpanLeft = new CPoint2[nTotalLine];
	SpanRight = new CPoint2[nTotalLine];
	//�ж���������P0P1�ߵ�λ�ù�ϵ��0-1-2Ϊ����ϵ
	int nDeltz = (point1.x - point0.x) * (point2.y - point1.y) - (point1.y - point0.y) * (point2.x - point1.x);//�����������z����
	if (nDeltz > 0)//������λ��P0P1�ߵ����
	{
		nIndex = 0;
		DDA(point0, point2, TRUE);
		DDA(point2, point1, TRUE);
		nIndex = 0;
		DDA(point0, point1, FALSE);
	}
	else//������λ��P0P1�ߵ��Ҳ�
	{
		nIndex = 0;
		DDA(point0, point1, TRUE);
		nIndex = 0;
		DDA(point0, point2, FALSE);
		DDA(point2, point1, FALSE);
	}
	for (int y = point0.y; y < point1.y; y++)//�±��Ͽ�
	{
		int n = y - point0.y;
		BOOL bInFlag = FALSE;//���������Ա�־����ʼֵΪ�ٱ�ʾ�������ⲿ
		for (int x = SpanLeft[n].x; x < SpanRight[n].x; x++)//����ҿ�
		{
			if (bInFlag == FALSE)
			{
				CurrentDepth = -(A * x + B * y + D) / C;//z=-(Ax+By+D)/C
				bInFlag = TRUE;
				x -= 1;
			}
			else
			{
				CVector3 Normal = LinearInterp(x, SpanLeft[n].x, SpanRight[n].x, SpanLeft[n].n, SpanRight[n].n);
				CT2 Texture = LinearInterp(x, SpanLeft[n].x, SpanRight[n].x, SpanLeft[n].t, SpanRight[n].t);
				Texture.c = GetTexture(ROUND(Texture.u), ROUND(Texture.v), pTexture);//��ȡ����ռ��Ӧ��ɫֵ
				pMaterial->SetDiffuse(Texture.c);//������ɫ��Ϊ���ʵ���������
				CRGB Intensity = pLight->Illuminate(ViewPoint, CP3(x, y, CurrentDepth), Normal, pMaterial);
				if (CurrentDepth <= zBuffer[x + nWidth/2][y + nHeight/2])//��Ȼ������㷨
				{
					zBuffer[x + nWidth/2][y + nHeight/2] = CurrentDepth;
					pDC->SetPixelV(x, y, RGB(Intensity.red * 255, Intensity.green * 255, Intensity.blue * 255));
				}
				CurrentDepth += DepthStep;
			}
		}
	}
	if(SpanLeft)
	{
		delete[]SpanLeft;
		SpanLeft = NULL;
	}
	if(SpanRight)
	{
		delete[]SpanRight;
		SpanRight = NULL;
	}
}

CRGB CZBuffer::GetTexture(int u, int v, CTexture* pTexture)
{
	/*���ͼƬ�ı߽磬��ֹԽ��*/
	if (u < 0) u = 0; if (v < 0) v = 0;
	if (u > pTexture->bmp.bmWidth - 1) u = pTexture->bmp.bmWidth - 1;
	if (v > pTexture->bmp.bmHeight - 1)	v = pTexture->bmp.bmHeight - 1;
	/*���Ҷ�Ӧ����ռ����ɫֵ*/
	int position = v * pTexture->bmp.bmWidthBytes + 4 * u;//��ɫ����λ��
	return  CRGB(pTexture->image[position + 2]/255.0, pTexture->image[position + 1]/255.0, pTexture->image[position]/255.0);//��ȡ��ɫֵ
}

void CZBuffer::DDA(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature)
{
	int dx = PEnd.x - PStart.x;
	int dy = PEnd.y - PStart.y;
	double m = double(dx)/dy;
	double x =  PStart.x;
	for(int y = PStart.y; y < PEnd.y; y++)
	{
		CVector3 Normal = LinearInterp(y, PStart.y, PEnd.y, PStart.n, PEnd.n);
		CT2 Texture = LinearInterp(y, PStart.y, PEnd.y, PStart.t, PEnd.t);
		if(bFeature)
			SpanLeft[nIndex++] = CPoint2(ROUND(x), y, Normal, Texture);
		else
			SpanRight[nIndex++] = CPoint2(ROUND(x), y, Normal, Texture);
		x += m;
	}
}

void CZBuffer::SortVertex(void)
{
	CPoint3 pt[3];
	pt[0] = point0;
	pt[1] = point1;
	pt[2] = point2;
	for(int i = 0; i < 2; i++)
	{
		int min = i;
		for(int j = i + 1; j < 3; j++)
			if(pt[j].y < pt[min].y)
				min = j;
		CPoint3 pTemp = pt[i];
		pt[i] = pt[min];
		pt[min] = pTemp;
	}
	point0 = pt[0];
	point1 = pt[2];
	point2 = pt[1];
}

CVector3 CZBuffer::LinearInterp(double t, double tStart, double tEnd, CVector3 vStart, CVector3 vEnd)//���������Բ�ֵ
{
	CVector3 vector;
	vector = (tEnd - t) / (tEnd - tStart) * vStart + (t - tStart) / (tEnd - tStart) * vEnd;
	return vector;
}

CT2 CZBuffer::LinearInterp(double t, double tStart, double tEnd, CT2 uvStart, CT2 uvEnd)//�����ַ���Բ�ֵ
{
	CT2 uvCoordinate;
	uvCoordinate = (tEnd - t) / (tEnd - tStart) * uvStart + (t - tStart) / (tEnd - tStart) * uvEnd;
	return uvCoordinate;
}

void CZBuffer::InitialDepthBuffer(int nWidth, int nHeight, double zDepth)//��ʼ����Ȼ���
{
	this->nWidth = nWidth, this->nHeight = nHeight;
	zBuffer = new double *[nWidth];
	for (int i = 0; i < nWidth; i++)
		zBuffer[i] = new double[nHeight];
	for (int i = 0; i < nWidth; i++)//��ʼ����Ȼ���
		for (int j = 0; j < nHeight; j++)
			zBuffer[i][j] = zDepth;
}