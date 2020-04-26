#include "StdAfx.h"
#include "P3.h"
#include "math.h"
#define Round(d) int(d + 0.5)


CP3::CP3(void)
{
	z = 0.0;
}

CP3::CP3(double x, double y, double z) :CP2(x, y)
{
	this->z = z;
}

CP3::~CP3(void)
{
}

CP3 operator + (const CP3 &p0, const CP3 &p1)//��
{
	CP3 p;
	p.x = p0.x + p1.x;
	p.y = p0.y + p1.y;
	p.z = p0.z + p1.z;
	return p;
}

CP3 operator - (const CP3 &p0, const CP3 &p1)//��
{
	CP3 p;
	p.x = p0.x - p1.x;
	p.y = p0.y - p1.y;
	p.z = p0.z - p1.z;
	return p;
}

CP3 operator * (const CP3 &p, double scalar)//��ͳ����Ļ�
{
	return CP3(p.x * scalar, p.y * scalar, p.z * scalar);
}

CP3 operator * (double scalar, const CP3 &p)//��ͳ����Ļ�
{
	return CP3(p.x * scalar, p.y * scalar, p.z * scalar);
}

CP3 operator / (const CP3 &p0, double scalar)//����
{
	if (fabs(scalar) < 1e-4)
		scalar = 1.0;
	CP3 p;
	p.x = p0.x / scalar;
	p.y = p0.y / scalar;
	p.z = p0.z / scalar;
	return p;
}

CP3 operator += (CP3 &p0, CP3 &p1)
{
	p0.x = p0.x + p1.x;
	p0.y = p0.y + p1.y;
	p0.z = p0.z + p1.z;
	return p0;
}

CP3 operator -= (CP3 &p0, CP3 &p1)
{
	p0.x = p0.x - p1.x;
	p0.y = p0.y - p1.y;
	p0.z = p0.z - p1.z;
	return p0;
}

CP3 operator *= (CP3 &p, double scalar)
{
	p.x = p.x * scalar;
	p.y = p.y * scalar;
	p.z = p.z * scalar;
	return p;
}

CP3 operator /= (CP3 &p, double scalar)
{
	if (fabs(scalar) < 1e-4)
		scalar = 1.0;
	p.x = p.x / scalar;
	p.y = p.y / scalar;
	p.z = p.z / scalar;
	return p;
}

BOOL operator == (CP3 &p0, CP3 &p1)
{
	if (Round(p0.x) == Round(p1.x) && Round(p0.y) == Round(p1.y) && Round(p0.z) == Round(p1.z))
		return TRUE;
	else
		return FALSE;
}

double CP3::Magnitude(void)//����
{
	return sqrt(x * x + y * y + z * z);
}