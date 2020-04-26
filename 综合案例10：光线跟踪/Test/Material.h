#pragma once
#include "RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual~CMaterial(void);
	void SetAmbient(CRGB c);//���û�����ķ�����	
	void SetDiffuse(CRGB c);//�����������ķ�����
	void SetSpecular(CRGB c);//���þ��淴���ķ�����
	void SetEmission(CRGB c);//��������������ɫ
	void SetExponent(double n);//���ø߹�ָ��
public:
	CRGB M_Ambient;//������ķ�����
	CRGB M_Diffuse;//�������ķ�����
	CRGB M_Specular;//���淴���ķ�����
	CRGB M_Emission;//����������ɫ
	double M_n;//�߹�ָ��
	double M_eta;//���ʵ�������
};