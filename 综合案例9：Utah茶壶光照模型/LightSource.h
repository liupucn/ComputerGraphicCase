#pragma once
#include "P3.h"

class CLightSource
{
public:
	CLightSource(void);
	virtual ~CLightSource(void);
	void SetDiffuse(CRGB diffuse);//���ù�Դ���������
	void SetSpecular(CRGB specular);//���ù�Դ�ľ��淴���
	void SetPosition(double x, double y, double z);//���ù�Դ��ֱ������λ��
	void SetAttenuationFactor(double c0, double c1, double c2);//���ù�ǿ��˥������
	void SetOnOff(BOOL onoff);//���ù�Դ����״̬	
public:
	CRGB L_Diffuse;//���������ɫ	
	CRGB L_Specular;//���淴�����ɫ
	CP3 L_Position;//��Դλ��
	double L_C0;//����˥������
	double L_C1;//����˥������
	double L_C2;//����˥������
	BOOL L_OnOff;//��Դ������ر�
};