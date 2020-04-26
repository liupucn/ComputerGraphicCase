#include "StdAfx.h"
#include "Lighting.h"
#include <math.h>
#define  PI 3.14159265


CLighting::CLighting(void)
{
	nLightNumber = 1;
	LightSource = new CLightSource[nLightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);//�������ǳ���
}

CLighting::~CLighting(void)
{
	if (LightSource)
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

CLighting::CLighting(int nLightNumber)
{
	this->nLightNumber = nLightNumber;
	LightSource = new CLightSource[nLightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);
}

CRGB CLighting::Illuminate(CP3 ViewPoint, CP3 Point, CVector3 ptNormal, CMaterial* pMaterial)
{	
	CRGB ResultI = CRGB(0.0,0.0,0.0);// ��ʼ�������ա���ǿ
	for(int loop = 0; loop < nLightNumber; loop++)//����Դ����״̬
	{	
		if(LightSource[loop].L_OnOff)//��Դ��
		{		
			CRGB I = CRGB(0.0, 0.0, 0.0);// I�������䡱��ǿ
			CVector3 L(Point, LightSource[loop].L_Position);// LΪ���������
			double d = L.Magnitude();// dΪ����⴫���ľ��� 
			L = L.Normalize();//�淶�����������
			CVector3 N = ptNormal;
			N = N.Normalize();//�淶��������
			//��1���������������
			double NdotL = max(DotProduct(N, L), 0);
			I += LightSource[loop].L_Diffuse * pMaterial->M_Diffuse * NdotL;
			//��2�������뾵�淴���,Cook-Torranceģ��
			CVector3 V(Point, ViewPoint);//VΪ������
			V = V.Normalize();//�淶��������
			CVector3 H = (L + V).Normalize();//HΪ�з�����
			double NdotH = max(DotProduct(N, H), 0);//N��H�ĵ��
			double NdotV = max(DotProduct(N, V), 0);//N��V�ĵ��
			double VdotH = max(DotProduct(V, H), 0);//V��H�ĵ��
			if(NdotL > 0.0 && NdotV > 0.0)
			{
				double F = pMaterial->M_f + (1.0 - pMaterial->M_f) * pow(1 - VdotH, 5.0);//fresnel��
				double r1 = 1.0 / (pMaterial->M_k * pMaterial->M_k * pow(NdotH, 4.0));
				double r2 = (NdotH * NdotH - 1.0) / (pMaterial->M_k * pMaterial->M_k * NdotH * NdotH);
				double D = r1 * exp(r2);//beckmann�ֲ�����
				double Gm = (2.0 * NdotH * NdotV) / VdotH;//����˥��
				double Gs = (2.0 * NdotH * NdotL) / VdotH;
				double G = min(min(1.0, Gm), Gs);
				double Rs = (F * D * G) / (NdotL * NdotV * PI);
				I += LightSource[loop].L_Specular * pMaterial->M_Specular * Rs;
			}
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
