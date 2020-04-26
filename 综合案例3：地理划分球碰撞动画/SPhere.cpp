#include "StdAfx.h"
#include "Sphere.h"
#include <math.h>//������ѧͷ�ļ�
#define  PI 3.1415926//PI�ĺ궨��
#define ROUND(d) int(d + 0.5)//��������궨��

CSphere::CSphere(void)
{
	P = NULL;
	F = NULL;
}

CSphere::~CSphere(void)
{
	if (NULL != P)
	{
		delete[]P;
		P = NULL;
	}
	if (NULL != F)
	{
		for (int n = 0; n < N1; n++)
		{
			delete[]F[n];
			F[n] = NULL;
		}
		delete[]F;
		F = NULL;
	}
}

void CSphere::SetptCenter(CP3 ptCenter)
{
	this->ptCenter = ptCenter;
}

void CSphere::ReadVertex(void)//���
{
	int Alpha = 5, Beta = 5;//��Ƭ�н�
	N1 = 180 / Alpha, N2 = 360 / Beta;
	P = new CP3[(N1 - 1) * N2 + 2];//��Ķ���
	double Alpha1, Beta1;//�н�����
	//���㱱��������
	P[0].x = 0, P[0].y = 1, P[0].z = 0;
	//����ѭ�����������ϵĵ������
	for (int i = 0; i < N1 - 1; i++)
	{
		Alpha1 = (i + 1) * Alpha * PI / 180;
		for (int j = 0; j < N2; j++)
		{
			Beta1 = j * Beta * PI / 180;
			P[i * N2 + j + 1].x = sin(Alpha1) * sin(Beta1);
			P[i * N2 + j + 1].y = cos(Alpha1);
			P[i * N2 + j + 1].z = sin(Alpha1) * cos(Beta1);
		}
	}
	//�����ϼ�������
	P[(N1 - 1) * N2 + 1].x = 0, P[(N1 - 1) * N2 + 1].y = -1, P[(N1 - 1) * N2 + 1].z = 0;
}

void CSphere::ReadFacet(void)//���
{
	//���ö�ά��̬����
	F = new CFacet *[N1];//������
	for (int n = 0; n < N1; n++)
		F[n] = new CFacet[N2];//������
	for (int j = 0; j < N2; j++)//���챱����������Ƭ
	{
		int tempj = j + 1;
		if (N2 == tempj)
			tempj = 0;//��Ƭ����β����
		int NorthIndex[3];//������������Ƭ����������
		NorthIndex[0] = 0;
		NorthIndex[1] = j + 1;
		NorthIndex[2] = tempj + 1;
		F[0][j].SetPtNumber(3);
		for (int k = 0; k < F[0][j].Number; k++)
			F[0][j].Index[k] = NorthIndex[k];
	}
	for (int i = 1; i < N1 - 1; i++)//���������ı�����Ƭ
	{
		for (int j = 0; j < N2; j++)
		{
			int tempi = i + 1;
			int tempj = j + 1;
			if (N2 == tempj)
				tempj = 0;//��Ƭ����β����
			int BodyIndex[4];//�����ı�����Ƭ����������
			BodyIndex[0] = (i - 1) * N2 + j + 1;
			BodyIndex[1] = (tempi - 1) * N2 + j + 1;
			BodyIndex[2] = (tempi - 1) * N2 + tempj + 1;
			BodyIndex[3] = (i - 1) * N2 + tempj + 1;
			F[i][j].SetPtNumber(4);
			for (int k = 0; k < F[i][j].Number; k++)
				F[i][j].Index[k] = BodyIndex[k];
		}
	}
	for (int j = 0; j < N2; j++)//�����ϼ���������Ƭ
	{
		int tempj = j + 1;
		if (N2 == tempj)
			tempj = 0;//��Ƭ����β����
		int SouthIndex[3];//�ϼ���������Ƭ����������
		SouthIndex[0] = (N1 - 2) * N2 + j + 1;
		SouthIndex[1] = (N1 - 1) * N2 + 1;
		SouthIndex[2] = (N1 - 2) * N2 + tempj + 1;
		F[N1 - 1][j].SetPtNumber(3);
		for (int k = 0; k < F[N1 - 1][j].Number; k++)
			F[N1 - 1][j].Index[k] = SouthIndex[k];
	}
}

void CSphere::Draw(CDC* pDC)
{
	for (int i = 0; i < N1; i++)//����ѭ��
	{
		for (int j = 0; j < N2; j++)
		{
			CP2 ScreenPoint, temp;
			for (int nPoint = 0; nPoint < F[i][j].Number; nPoint++)//����ѭ��
			{
				ScreenPoint.x = ptCenter.x + P[F[i][j].Index[nPoint]].x;
				ScreenPoint.y = ptCenter.y + P[F[i][j].Index[nPoint]].y;
				if (0 == nPoint)
				{
					pDC->MoveTo(ROUND(ScreenPoint.x), ROUND(ScreenPoint.y));
					temp = ScreenPoint;
				}
				else
				{
					pDC->LineTo(ROUND(ScreenPoint.x), ROUND(ScreenPoint.y));
				}
			}
			pDC->LineTo(ROUND(temp.x), ROUND(temp.y));//�պ϶����
		}
	}
}
