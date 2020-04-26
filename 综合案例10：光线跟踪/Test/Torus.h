#pragma once
#include "GeometricObject.h"
#include "Equation.h"  //�������һԪ�Ĵη�����

class CTorus:public CGeometricObject//Բ������
{
public:
	CTorus(void);
	virtual ~CTorus(void);
	CTorus(CP3 Center,double R, double r, CMaterial Material);
	BOOL Hit(CRay Ray, CIntersection &Hit);//������ײ��⺯��
	CVector3 ComputeNormal(const CP3& p) const;//���㷨��������
public:
	double R;//ɨ�Ӱ뾶
	double r;//��״�뾶
	CEquation equation;//���һԪ�Ĵη��̶���
	CP3 Center;//Բ���廷������
};

