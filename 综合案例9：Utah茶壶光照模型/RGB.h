#pragma once

class CRGB
{
public:
	CRGB(void);
	CRGB(double red, double green, double blue, double alpha = 0.0);
	virtual ~CRGB (void);
	friend CRGB operator + (const CRGB &c0, const CRGB &c1);//���������
	friend CRGB operator - (const CRGB &c0, const CRGB &c1);
	friend CRGB operator * (const CRGB &c0, const CRGB &c1);
	friend CRGB operator * (const CRGB &c, double scalar);
	friend CRGB operator * (double scalar,const CRGB &c);
	friend CRGB operator / (const CRGB &c, double scalar);
	friend CRGB operator += (CRGB &c1, CRGB &c2);
	friend CRGB operator -= (CRGB &c1, CRGB &c2);
	friend CRGB operator *= (CRGB &c1, CRGB &c2);
	friend CRGB operator /= (CRGB &c1, double scalar);
	void Normalize(void);//�淶����[0,1]����
public:
	double red;//��ɫ����
	double green;//��ɫ����
	double blue;//��ɫ����
	double alpha;//alpha����
};

