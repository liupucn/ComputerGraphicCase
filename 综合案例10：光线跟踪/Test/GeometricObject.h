#pragma once
#include "Intersection.h"
#include "Material.h"

#define Epsilon 0.001
#define HugeValue 100000

class CGeometricObject//���ζ�����
{
public:
	CGeometricObject(void);
	virtual ~CGeometricObject(void);
	virtual BOOL Hit(CRay Ray, CIntersection &Hit) = 0;//������ײ��⺯��
public:
	CMaterial Material;  //ÿ������Ĳ���
};

