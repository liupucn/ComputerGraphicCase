#pragma once

class CEquation//������
{
public:
	CEquation(void);
	virtual ~CEquation(void);
	int SolveQuadric(double c[3], double s[2]);//���һԪ���η���
	int SolveCubic(double c[4], double s[3]);//���һԪ���η���
	int SolveQuartic(double c[5], double s[4]);//���һԪ�Ĵη���
};

