#pragma once
#include "Vector3.h"

class CRay//������
{
public:
	CRay(void);
	virtual ~CRay(void);
	CRay(CVector3 Origin, CVector3 Direction);//������ߺ���	
	CP3 GetPoint(double t);//���㽻�㺯��
public:
	CVector3 Origin;//���ߵ�Դ��
	CVector3 Direction;//���ߵķ���
};

