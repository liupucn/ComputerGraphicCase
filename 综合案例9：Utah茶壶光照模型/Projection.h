#pragma once
#include "P3.h"

class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void InitialParameter(void);
	CP3 PerspectiveProjection(CP3 WorldPoint);//͸��ͶӰ
	CP3 OrthogonalProjection(CP3 WorldPoint);//����ͶӰ	
public:
	CP3 EyePoint;//�ӵ�
private:
	double k[8];//͸��ͶӰ����
	double R, Phi, Psi, d;//�ӵ�������
};

