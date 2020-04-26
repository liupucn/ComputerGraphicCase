#pragma once
#include"Facet.h"
#include "P3.h"

class CSphere
{
public:
	CSphere(void);
	virtual ~CSphere(void);
	void SetptCenter(CP3 ptCenter);
	void ReadVertex(void);	//������
	void ReadFacet(void);	//�������
	void Draw(CDC* pDC);	//����ͼ��
public:
	CP3* P;			//���
	int N1, N2;		//N1Ϊγ������,N2Ϊ��������
	CFacet** F;		//���
	CP3 ptCenter;	//���ĵ�
};

