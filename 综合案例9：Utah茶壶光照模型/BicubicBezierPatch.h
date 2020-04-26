#pragma once
#include "Facet.h"
#include "Projection.h"
#include "ZBuffer.h"
#include"Texture.h"

class CBicubicBezierPatch
{
public:
	CBicubicBezierPatch(void);
	virtual ~CBicubicBezierPatch(void);
	void ReadControlPoint(CP3* V, int ReNumber);//����16�����Ƶ�
	void ReadTexture(CTexture* pTexture);//��������
	void SetScene(CLighting* pLight, CMaterial* pMaterial);//���ó���
	void DrawCurvedPatch(CDC* pDC, CZBuffer*pZBuffer, int nPatch);
private:
	void Recursion(CDC* pDC, CZBuffer* pZBuffer, int ReNumber, CT2* pRect,int nPatch);
	void Tessellation(CT2* pRect, CP3* P, CVector3* N, CT2* T, int nPatch);//ϸ������
	void DrawFacet(CDC* pDC, CZBuffer* pZBuffer, CP3* P, CVector3* N, CT2* T);//�����ı���
	void LeftMultiplyMatrix(double M[4][4], CP3 V[4][4]);//��˶������
	void RightMultiplyMatrix(CP3 V[4][4], double M[4][4]);//�ҳ˶������
	void TransposeMatrix(double M[4][4]);//ת�þ���
public:
	int ReNumber;//�ݹ����
	CP3 V3[16];//��ά���Ƶ�
	CProjection projection;//ͶӰ����
	CLighting* pLight;//����
	CMaterial* pMaterial;//����
	CTexture* pTexture;//����
	int TextureIndex;//����
};

