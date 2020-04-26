#pragma once
#include"T2.h"
#include "Projection.h"

class CBicubicBezierPatch
{
public:
	CBicubicBezierPatch(void);
	virtual ~CBicubicBezierPatch(void);
	void ReadControlPoint(CP3* V, int ReNumber);//����16�����Ƶ�͵ݹ����
	void DrawCurvedPatch(CDC* pDC);//��������
	void DrawControlGrid(CDC* pDC);//���ƿ�������
private:
	void Recursion(CDC* pDC, int ReNumber, CT2* pRect);//�ݹ麯��
	void Tessellation(CT2* pRect, CP2* P);
	void DrawFacet(CDC* pDC, CP2* P);//�����ı���
	void LeftMultiplyMatrix(double M[4][4], CP3 V[4][4]);//��˶������
	void RightMultiplyMatrix(CP3 V[4][4], double M[4][4]);//�ҳ˶������
	void TransposeMatrix(double M[4][4]);//ת�þ���
public:
	int ReNumber;//�ݹ����
	CP3 V3[16];//��ά���Ƶ�
	CProjection projection;//ͶӰ����
};

