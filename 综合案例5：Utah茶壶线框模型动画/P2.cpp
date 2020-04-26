#include "StdAfx.h"
#include "P2.h"
#include<math.h>

CP2::CP2(void)
{
	x = 0.0, y = 0.0, w = 1.0;
}

CP2::CP2(double x, double y)
{
	this->x = x;
	this->y = y;
	this->w = 1.0;
}

CP2::~CP2(void)
{

}

CP2 operator + (const CP2 &p0, const CP2 &p1)//��
{
	CP2 result;
	result.x = p0.x + p1.x;
	result.y = p0.y + p1.y;
	return result;
}

CP2 operator - (const CP2 &p0, const CP2 &p1)//��
{
	CP2 result;
	result.x = p0.x - p1.x;
	result.y = p0.y - p1.y;
	return result;
}

CP2 operator * (const CP2 &p, double scalar)//��ͳ����Ļ�
{
	return CP2(p.x * scalar, p.y * scalar);
}

CP2 operator * (double scalar, const CP2 &p)//�����͵�Ļ�
{
	return CP2(p.x * scalar, p.y * scalar);
}

CP2 operator / (const CP2 &p, double scalar)//����
{
	if (fabs(scalar) < 1e-4)
		scalar = 1.0;
	CP2 result;
	result.x = p.x / scalar;
	result.y = p.y / scalar;
	return result;
}

CP2 operator += (CP2 &p0, CP2 &p1)
{
	p0.x += p1.x;
	p0.y += p1.y;
	return p0;
}

CP2 operator -= (CP2 &p0, CP2 &p1)
{
	p0.x -= p1.x;
	p0.y -= p1.y;
	return p0;
}

CP2 operator *= (CP2 &p, double scalar)
{
	p.x *= scalar;
	p.y *= scalar;
	return p;
}

CP2 operator /= (CP2 &p, double scalar)
{
	if(fabs(scalar) < 1e-4)
		scalar = 1.0;
	p.x /= scalar;
	p.y /= scalar;
	return p;
}

BOOL operator != (CP2 &p0, CP2 &p1)
{
	if (p0.x != p1.x || p0.y != p1.y)
		return TRUE;
	else
		return FALSE;
}