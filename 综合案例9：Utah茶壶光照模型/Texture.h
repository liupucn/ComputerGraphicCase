#pragma once
#include"resource.h"

class CTexture
{
public:
	CTexture(void);
	virtual~CTexture(void);
	void GetImage(UINT nIDResource);//׼��λͼ
	void DeleteObject(void);//�ͷ�λͼ
public:
	BYTE* image;
	BITMAP bmp;//BITMAP�ṹ�����
};

