#pragma once
#include "Patch.h"
#include "BicubicBezierPatch.h"

class CTeapot
{
public:
	CTeapot(void);
	virtual~CTeapot(void);
	void ReadVertex(void);//������ƶ���ζ���
	void ReadPatch(void);//����˫��������Ƭ
	void SetRecursiveNumber(int Renumber);//���õݹ����
	void Draw(CDC* pDC);//��������
public:
	int ReNumber;//�ݹ����
	CP3 Ver[306];//����ܿ��Ƶ�
private:
	CPatch Pat[32];//�������Ƭ
	CP3 Ver3[16];//��ά���Ƶ�
	CBicubicBezierPatch bezier;//bezier����Ƭ
};


