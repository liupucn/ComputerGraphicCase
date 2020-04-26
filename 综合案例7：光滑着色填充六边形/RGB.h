#pragma once
class CRGB
{
public:
	CRGB(void);
	CRGB(double red, double green, double blue, double alpha = 0.0);
	virtual ~CRGB(void);	
	friend CRGB operator + (const CRGB &clr0, const CRGB &clr1);//���������
	friend CRGB operator - (const CRGB &clr0, const CRGB &clr1);
	friend CRGB operator * (const CRGB &clr0, const CRGB &clr1);
	friend CRGB operator * (const CRGB &clr, double scalar);
	friend CRGB operator * (double scalar, const CRGB &clr);
	friend CRGB operator / (const CRGB &clr, double scalar);
	friend CRGB operator += (CRGB &clr0, CRGB &clr1);
	friend CRGB operator -= (CRGB &clr0, CRGB &clr1);
	friend CRGB operator *= (CRGB &clr0, CRGB &clr1);
	friend CRGB operator /= (CRGB &clr, double scalar);
	void   Normalize();	//��һ����[0,1]����
public:
	double red;//��ɫ����
	double green;//��ɫ����
	double blue;//��ɫ����
	double alpha;//alpha����	
};

