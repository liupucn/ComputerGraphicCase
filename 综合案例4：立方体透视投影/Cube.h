#pragma once
#include"Projection.h"
#include"Facet.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	void ReadVertex(void);//������
	void ReadFacet(void);//�������
	void Draw(CDC* pDC);//����ͼ��	
public:	
	CP3 P[8];//���
private:
	CFacet F[6];//���
	CProjection projection;//ͶӰ
};

