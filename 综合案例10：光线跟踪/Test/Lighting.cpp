#include "StdAfx.h"
#include "Lighting.h"
#include <math.h>
#define  PI  3.14159265

CLighting::CLighting(void)
{
	nLightNumber = 1;
	LightSource = new CLightSource[nLightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);//�������ǳ���
}

CLighting::CLighting(int nLightNumber)
{
	this->nLightNumber = nLightNumber;
	LightSource = new CLightSource[nLightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);
}

CLighting::~CLighting(void)
{
	if(LightSource)
	{
		delete []LightSource;
		LightSource = NULL;
	}
}

void CLighting::SetLightNumber(int nLightNumber)
{
	if(LightSource)
		delete []LightSource;
	this->nLightNumber = nLightNumber;
	LightSource = new CLightSource[nLightNumber];
}

CRGB CLighting::Illuminate(CP3 ViewPoint, CP3 Point, CVector3 ptNormal, CMaterial* pMaterial)
{	
	CRGB ResultI = pMaterial->M_Emission;//����������Ϊ��ʼֵ
	for(int loop = 0; loop < nLightNumber; loop++)//����Դ����״̬
	{
		if(LightSource[loop].L_OnOff)//��Դ��
		{
			CRGB I = CRGB(0.0, 0.0, 0.0);// I�������䡱��ǿ
			CVector3 L(Point, LightSource[loop].L_Position);// LΪ������
			double d = L.Magnitude();// dΪ�⴫���ľ��� 
			L = L.Normalize();//�淶��������
			CVector3 N = ptNormal;
			N = N.Normalize();//�淶��������
			//��1���������������
			double NdotL = max(DotProduct(N, L), 0);
			I += LightSource[loop].L_Diffuse * pMaterial->M_Diffuse * NdotL;
			//��2�������뾵�淴���
			CVector3 V(Point, ViewPoint);//VΪ�۲�����
			V = V.Normalize();//�淶���۲�����
			CVector3 H = (L + V) / (L + V).Magnitude();//HΪ��ֵ����
			double NdotH = max(DotProduct(N, H), 0);
			double Rs = pow(NdotH, pMaterial->M_n);
			I += LightSource[loop].L_Specular * pMaterial->M_Specular * Rs;
			//��3������ǿ˥��
			double c0 = LightSource[loop].L_C0;//c0Ϊ����˥������
			double c1 = LightSource[loop].L_C1;//c1Ϊ����˥������
			double c2 = LightSource[loop].L_C2;//c2Ϊ����˥������
			double f = (1.0/(c0 + c1 * d + c2 * d * d));//��ǿ˥������
			f = min(1.0, f);
			ResultI += I * f;
		}
		else
			ResultI += Point.c;//����������ɫ
	}
	//��4�������뻷����
	ResultI += Ambient * pMaterial->M_Ambient;
	//��5������ǿ�淶����[0,1]����
	ResultI.Normalize();
	//��6�������������㶥������յĹ�ǿ��ɫ
	return ResultI;
}
