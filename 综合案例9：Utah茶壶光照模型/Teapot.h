#pragma once
#include "Patch.h"
#include "Projection.h"
#include "BicubicBezierPatch.h"

class CTeapot
{
public:
	CTeapot(void);
	virtual~CTeapot(void);
	void ReadVertex(void);//������ƶ���ζ���
	void ReadPatch(void);//����˫��������Ƭ
	void SetReNumber(int ReNumber);//���õݹ����
	void ReadTexture(CTexture *pTexture);//��������
	void SetScene(CLighting* pLight, CMaterial* pMaterial);//���ó���
	void Draw(CDC* pDC, CZBuffer* pZBuffer);//��������
public:
	int ReNumber;
	CP3 Ver[306];//����ܿ��Ƶ�
	CPatch Pat[32];//�������Ƭ
	CP3 Ver3[16];//��ά���Ƶ�
	CBicubicBezierPatch bezier;//bezier����Ƭ
	CLighting* pLight;//����
	CMaterial* pMaterial;//����
	CTexture* Texture;//����
};


