#pragma once
#include "GeometricObject.h"

class CSphere:public CGeometricObject//����
{
public:
	CSphere(void);
	virtual ~CSphere(void);
	CSphere(double Radius, CP3 Center, CMaterial Material);//���幹�캯��
    BOOL Hit(CRay Ray,CIntersection &Hit);//������ײ��⺯��
public:
	double Radius;//����뾶
	CP3 Center;//��������
};