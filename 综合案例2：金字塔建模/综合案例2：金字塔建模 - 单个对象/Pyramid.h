#pragma once
#include "P3.h"
#include"Facet.h"

class CPyramid
{
public:
	CPyramid(void);
	virtual ~CPyramid(void);
	void ReadVertex(void);//������
	void ReadFacet(void);//�������
	void Draw(CDC* pDC);//����ͼ��
public:
	CP3 P[5];//���
	CFacet F[5];//���
};

