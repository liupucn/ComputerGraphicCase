#pragma once
#include "Ray.h"
#include "Material.h"

class CIntersection: public CRay//��ײ����
{
public:
	CIntersection(void);
	virtual ~CIntersection(void);	
public:
	double t;//���㴦���ߵĲ���t
	CP3 Point; //��ײ������
    CVector3  Normal;//��ײ��ķ�����
	CMaterial Material;//��ײ��Ĳ��� 
};

