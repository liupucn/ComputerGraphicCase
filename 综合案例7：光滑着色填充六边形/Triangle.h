#pragma once
#include "P2.h"//����ɫ�ĸ�������ά����
#include "Point2.h"//����ɫ��������ά����

class CTriangle//�����������
{
public:
	CTriangle(void);
	CTriangle(CP2 P0, CP2 P1, CP2 P2);//���������㹹��������
	virtual ~CTriangle(void);
	void GouraudShader(CDC* pDC);//���������
private:
	void DDA(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//�߱��
	CRGB LinearInterp(double t, double tStart, double tEnd, CRGB cStart, CRGB cEnd);//��ɫ���Բ�ֵ
	void SortVertex(void);//�����ζ�������
private:
	CPoint2 point0, point1, point2;//�����ε���������
	CPoint2* SpanLeft; //��ȵ���������־
	CPoint2* SpanRight;//��ȵ��յ������־
	int nIndex;//ɨ��������
};

