#include "StdAfx.h"
#include "ViewPlane.h"


CViewPlane::CViewPlane(void)
{	 
}

CViewPlane::~CViewPlane(void)
{
}

void CViewPlane::SetResolution(int HorRes, int VerRes)
{
	this->HorRes = HorRes;//��Ļ��ˮƽ�ֱ���
	this->VerRes = VerRes;//��Ļ�´�ֱ�ֱ���
}

void CViewPlane::SetSampleNumber(int SampleNumber)
{
	this->SampleNumber = SampleNumber;//������
}


