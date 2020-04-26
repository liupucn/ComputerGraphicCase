#include "StdAfx.h"
#include "BicubicBezierPatch.h"
#include <math.h>
#define ROUND(d) int(d + 0.5)

CBicubicBezierPatch::CBicubicBezierPatch(void)
{
	ReNumber = 0;
}


CBicubicBezierPatch::~CBicubicBezierPatch(void)
{
}

void CBicubicBezierPatch::ReadControlPoint(CP3* V, int ReNumber)
{
	for(int i = 0; i< 16; i++)
		V3[i] = V[i];
	this->ReNumber = ReNumber;
}

void CBicubicBezierPatch::ReadTexture(CTexture* pTexture)//��������
{
	this->pTexture = pTexture;
}

void CBicubicBezierPatch::SetScene(CLighting *pLight, CMaterial *pMaterial)//���ù�Դ������
{
	this->pLight = pLight;
	this->pMaterial = pMaterial;
}

void CBicubicBezierPatch::DrawCurvedPatch(CDC* pDC, CZBuffer*pZBuffer, int nPatch)
{
	CT2 Rect[4];
	Rect[0] = CT2(0,0); Rect[1] = CT2(1, 0);//��ʼ��uv
	Rect[2] = CT2(1, 1);Rect[3] = CT2(0, 1);
	Recursion(pDC, pZBuffer, ReNumber, Rect, nPatch);//�ݹ麯��
}

void CBicubicBezierPatch::Recursion(CDC* pDC, CZBuffer* pZBuffer, int ReNumber, CT2* pRect, int nPatch)
{
	if(ReNumber == 0)
	{
		CP3 P[4];
		CT2 T[4];
		CVector3 N[4];
		Tessellation(pRect, P, N, T, nPatch);
		DrawFacet(pDC, pZBuffer, P, N, T);//����Facet
		return;
	}
	else
	{
		double HalfU = (pRect[0].u + pRect[1].u)/2.0;
		double HalfV = (pRect[0].v + pRect[3].v)/2.0;
		CT2 SubRect[4][4];//һ��Ϊ�ĸ�
		//�����ӳ�����
		SubRect[0][0] = pRect[0];
		SubRect[0][1].u = HalfU;     SubRect[0][1].v = pRect[0].v;
		SubRect[0][2].u = HalfU;     SubRect[0][2].v = HalfV;
		SubRect[0][3].u = pRect[0].u;SubRect[0][3].v = HalfV;
		//�����ӳ�����
		SubRect[1][0] = SubRect[0][1];
		SubRect[1][1] = pRect[1];
		SubRect[1][2].u = pRect[1].u;SubRect[1][2].v = HalfV;
		SubRect[1][3] = SubRect[0][2];
		//�����ӳ�����
		SubRect[2][0] = SubRect[1][3];
		SubRect[2][1] = SubRect[1][2];
		SubRect[2][2] = pRect[2];
		SubRect[2][3].u = HalfU; SubRect[2][3].v = pRect[2].v;
		//�����ӳ�����
		SubRect[3][0] = SubRect[0][3];
		SubRect[3][1] = SubRect[2][0];
		SubRect[3][2] = SubRect[2][3];
		SubRect[3][3] = pRect[3];

		Recursion(pDC, pZBuffer, ReNumber - 1, SubRect[0], nPatch);
		Recursion(pDC, pZBuffer, ReNumber - 1, SubRect[1], nPatch);
		Recursion(pDC, pZBuffer, ReNumber - 1, SubRect[2], nPatch);
		Recursion(pDC, pZBuffer, ReNumber - 1, SubRect[3], nPatch);
	}
}

void CBicubicBezierPatch::Tessellation(CT2* pRect, CP3* P, CVector3* N, CT2* T, int nPatch)
{
	double M[4][4];//ϵ������Mbe
	M[0][0] = -1; M[0][1] = 3; M[0][2] = -3; M[0][3] = 1;
	M[1][0] = 3; M[1][1] = -6; M[1][2] = 3; M[1][3] = 0;
	M[2][0] = -3; M[2][1] = 3; M[2][2] = 0; M[2][3] = 0;
	M[3][0] = 1; M[3][1] = 0; M[3][2] = 0; M[3][3] = 0;
	CP3 VC[4][4];//���߼����ÿ��Ƶ�����
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			VC[i][j] = V3[i * 4 + j];
	LeftMultiplyMatrix(M, VC);//ϵ�����������ά�����
	TransposeMatrix(M);//����ת�þ���
	RightMultiplyMatrix(VC, M);//ϵ�������ҳ���ά�����
	double u0, u1, u2, u3, v0, v1, v2, v3;//u��v��������
	for (int i = 0;i < 4;i++)
	{
		u3 = pow(pRect[i].u, 3.0), u2 = pow(pRect[i].u, 2.0), u1 = pow(pRect[i].u, 1.0), u0 = 1;
		v3 = pow(pRect[i].v, 3.0), v2 = pow(pRect[i].v, 2.0), v1 = pow(pRect[i].v, 1.0), v0 = 1;
		P[i] =  (v3 * VC[0][0] + v2 * VC[1][0] + v1 * VC[2][0] + v0 * VC[3][0]) * u3
			  + (v3 * VC[0][1] + v2 * VC[1][1] + v1 * VC[2][1] + v0 * VC[3][1]) * u2
			  + (v3 * VC[0][2] + v2 * VC[1][2] + v1 * VC[2][2] + v0 * VC[3][2]) * u1
			  + (v3 * VC[0][3] + v2 * VC[1][3] + v1 * VC[2][3] + v0 * VC[3][3]) * u0;

		//���㶥�㷨����
		CP3 P0, P1;
		u3 = pow(pRect[i].u, 3.0), u2 = pow(pRect[i].u, 2.0), u1 = pow(pRect[i].u, 1.0), u0 = 1.0;
		v3 = 3.0 * pow(pRect[i].v, 2.0), v2 = 2.0 * pow(pRect[i].v, 1.0), v1 = 1.0, v0 = 0.0;
		P0 = (v3 * VC[0][0] + v2 * VC[1][0] + v1 * VC[2][0] + v0 * VC[3][0]) * u3
			+ (v3 * VC[0][1] + v2 * VC[1][1] + v1 * VC[2][1] + v0 * VC[3][1]) * u2
			+ (v3 * VC[0][2] + v2 * VC[1][2] + v1 * VC[2][2] + v0 * VC[3][2]) * u1
			+ (v3 * VC[0][3] + v2 * VC[1][3] + v1 * VC[2][3] + v0 * VC[3][3]) * u0;

		u3 = 3.0*pow(pRect[i].u, 2.0), u2 = 2.0*pow(pRect[i].u, 1.0), u1 = 1.0, u0 = 0.0;
		v3 = pow(pRect[i].v, 3.0), v2 = pow(pRect[i].v, 2.0), v1 = pow(pRect[i].v, 1.0), v0 = 1.0;
		P1 = (v3 * VC[0][0] + v2 * VC[1][0] + v1 * VC[2][0] + v0 * VC[3][0]) * u3
			+ (v3 * VC[0][1] + v2 * VC[1][1] + v1 * VC[2][1] + v0 * VC[3][1]) * u2
			+ (v3 * VC[0][2] + v2 * VC[1][2] + v1 * VC[2][2] + v0 * VC[3][2]) * u1
			+ (v3 * VC[0][3] + v2 * VC[1][3] + v1 * VC[2][3] + v0 * VC[3][3]) * u0;

		N[i] = CrossProduct(CVector3(P0), CVector3(P1)).Normalize();//���㷨����

		/*���������*/
		if (nPatch == 6 || nPatch == 7 || nPatch == 10 || nPatch == 11)
		{
			int Index = nPatch - 6;
			TextureIndex = 0;
			T[i].u = (pTexture[TextureIndex].bmp.bmWidth - 1) / 2 * (pRect[i].u + (Index % 4));
			T[i].v = (pTexture[TextureIndex].bmp.bmHeight - 1) / 2 * (pRect[i].v + int(Index / 4));
		}
		else if (nPatch == 4 || nPatch == 5 || nPatch == 8 || nPatch == 9)
		{
			int Index = nPatch - 4;
			TextureIndex = 1;
			T[i].u = (pTexture[TextureIndex].bmp.bmWidth - 1) / 2 * (pRect[i].u + (Index % 4));
			T[i].v = (pTexture[TextureIndex].bmp.bmHeight - 1) / 2 * (pRect[i].v + int(Index / 4));
		}
		else
		{
			TextureIndex = 0;
			T[i].u = pTexture[TextureIndex].bmp.bmWidth - 1;
			T[i].v = pTexture[TextureIndex].bmp.bmHeight - 1;
		}
	}

	if (fabs(P[0].x - P[1].x) < 1e-6)//��������������
		N[0] = N[1] = CVector3(P[0]).Normalize();
	if (fabs(P[2].x - P[3].x) < 1e-6)
		N[2] = N[3] = CVector3(P[2]).Normalize();
}

void CBicubicBezierPatch::DrawFacet(CDC* pDC, CZBuffer* pZBuffer, CP3* P, CVector3* N, CT2* T)
{
	CP3 ViewPoint = projection.EyePoint;
	CP3 Point4[4];//ͶӰ���ƽ���ı��ζ�������
	for (int nVertex = 0; nVertex < 4; nVertex++)//��ѭ��
		Point4[nVertex] = projection.PerspectiveProjection(P[nVertex]);

	pZBuffer->SetPoint(Point4[0], Point4[1], Point4[2], N[0], N[1], N[2], T[0], T[1], T[2]);
	pZBuffer->PhongShader(pDC, ViewPoint, pLight, pMaterial, &pTexture[TextureIndex]);
	pZBuffer->SetPoint(Point4[0], Point4[2], Point4[3], N[0], N[2], N[3], T[0], T[2], T[3]);
	pZBuffer->PhongShader(pDC, ViewPoint, pLight, pMaterial, &pTexture[TextureIndex]);
}

void CBicubicBezierPatch::LeftMultiplyMatrix(double M[4][4], CP3 V[4][4])//��˾���M*V
{
	CP3 VT[4][4];//��ʱ����
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			VT[i][j] = M[i][0] * V[0][j] + M[i][1] * V[1][j] + M[i][2] * V[2][j] + M[i][3] * V[3][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			V[i][j] = VT[i][j];
}

void CBicubicBezierPatch::RightMultiplyMatrix(CP3 V[4][4], double M[4][4])//�ҳ˾���V*M
{
	CP3 VT[4][4];//��ʱ����
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			VT[i][j] = V[i][0] * M[0][j] + V[i][1] * M[1][j] + V[i][2] * M[2][j] + V[i][3] * M[3][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			V[i][j] = VT[i][j];
}

void CBicubicBezierPatch::TransposeMatrix(double M[4][4])//ת�þ���
{
	double VT[4][4];//��ʱ����
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			VT[j][i] = M[i][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			M[i][j] = VT[i][j];
}