#pragma once


class CLine
{
public:
	CLine(void);
	virtual ~CLine(void);
	void MoveTo(CDC* pDC, int x0, int y0, COLORREF c0);
	void LineTo(CDC* pDC, int x1, int y1, COLORREF c1);
private:
	int x0, y0;//�������
	COLORREF c0;//�����ɫ
	int x1, y1;//�յ�����
	COLORREF c1;//�յ���ɫ	
};

