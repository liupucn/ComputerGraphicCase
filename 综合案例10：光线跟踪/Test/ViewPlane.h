#pragma once

class CViewPlane
{
public:
	CViewPlane(void);
	virtual ~CViewPlane(void);
	void SetResolution(int HorRes, int VerRes);
	void SetSampleNumber(int SampleNumber);
public:
	int HorRes;//ˮƽ�ֱ���
	int VerRes;//��ֱ�ֱ���
	int SampleNumber;//��������
};

