#pragma once
#include "P3.h"

class CVector3
{
public:
	CVector3(void);
	virtual ~CVector3(void);
	CVector3(double x, double y, double z);//��������
	CVector3(const CP3 &vertex);
	CVector3(const CP3 &Vertex0, const CP3 &Vertex1);//�������
	double Magnitude(void);//����������ģ
	CVector3 Normalize(void);//�淶������
	friend CVector3 operator + (const CVector3 &v0, const CVector3 &v1);//���������
	friend CVector3 operator - (const CVector3 &v0, const CVector3 &v1);
	friend CVector3 operator - (const CVector3 &v);
	friend CVector3 operator * (const CVector3 &v, double scalar);
	friend CVector3 operator * (double scalar, const CVector3 &v);
	friend CVector3 operator / (const CVector3 &v,double scalar);
	friend double DotProduct(const CVector3 &v0, const CVector3 &v1);//���������ĵ��
	friend CVector3 CrossProduct(const CVector3 &v0, const CVector3 &v1);//���������Ĳ��
public:
	double x,y,z;
};

