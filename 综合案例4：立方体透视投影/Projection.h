#pragma once
#include "P3.h"
class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void InitialParameter(void);//͸��ͶӰ������ʼ��
	CP2 PerspectiveProjection(CP3 WorldPoint);//͸��ͶӰ
	CP2 OrthogonalProjection(CP3 WorldPoint);//����ͶӰ
	CP2 CavalierProjection(CP3 WorldPoint);//б�Ȳ�ͶӰ
	CP2 CabinetProjection(CP3 WorldPoint);//б����ͶӰ
public:
	CP3 EyePoint;//�ӵ�
private:
	double k[8];//͸��ͶӰ����
	double R, Psi, Phi,d;//�ӵ��������
};

