#include "stdafx.h"
#include "Sphere.h"
#include <math.h>

CSphere::CSphere(void)
{
}

CSphere::~CSphere(void)
{
}

CSphere::CSphere(double Radius, CP3 Center, CMaterial Material)
{
	this->Radius = Radius;
	this->Center = Center;
	this->Material = Material;
} 

BOOL CSphere::Hit(CRay Ray, CIntersection &Hit) //��ȡ����������Ľ���
{
	CVector3 VectorC(Center);//��������λ������
	CVector3 VectorCO = Ray.Origin - VectorC;// VectorCOΪ������ָ�������������
	double A = DotProduct(Ray.Direction,Ray.Direction); 
	double B = 2 * DotProduct(VectorCO , Ray.Direction); 
	double C = DotProduct(VectorCO , VectorCO) - Radius * Radius;
	double D = B * B - 4 * A * C;
	if (D >= 0)
	{
		double t0 = (-B - sqrt(D)) / (2 * A);
		double t1 = (-B + sqrt(D)) / (2 * A);
		if (t0 > Epsilon)
		{
			Hit.t = t0;
			Hit.Point = Ray.GetPoint(Hit.t);//��������
            Hit.Normal = CVector3(Center, Hit.Point);//����ķ�����
		}
		else if (fabs(t0) < Epsilon && t1 > Epsilon)
		{
			Hit.t = t1;
			Hit.Point = Ray.GetPoint(Hit.t);
            Hit.Normal = CVector3(Hit.Point, Center);//����ķ�����		
		}
		else
			return FALSE;
	    Hit.Material = Material;
		return TRUE;
	}
	return FALSE;
}