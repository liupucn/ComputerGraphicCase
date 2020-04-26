#pragma once
#include "LightSource.h"
#include "Material.h"
#include "Vector3.h"

class CLighting
{
public:
	CLighting(void);
	CLighting(int nLightNumber);
	virtual ~CLighting(void);
	void SetLightNumber(int nLightNumber);//���ù�Դ����
	CRGB Illuminate(CP3 ViewPoint, CP3 Point, CVector3 ptNormal, CMaterial* pMaterial);//�������	
public:
	int nLightNumber;//��Դ����
	CLightSource* LightSource;//��Դ����
	CRGB Ambient;//������
};