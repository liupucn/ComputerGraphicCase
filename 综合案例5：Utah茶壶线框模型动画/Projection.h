#pragma once
#include "P3.h"

class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void InitialParameter(void);
	void SetEye(double R, double Phi, double Psi);//�����ӵ�
	CP3 GetEye(void);//����ӵ�
	CP2 PerspectiveProjection(CP3 WorldPoint);//͸��ͶӰ
	CP2 OrthogonalProjection(CP3 WorldPoint);//����ͶӰ
private:
	CP3 Eye;//�ӵ�
	double k[8];//͸��ͶӰ����
	double R, Phi, Psi, d;//�ӵ����û�����ϵ�е�������
};

