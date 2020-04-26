#pragma once
#include"Vector3.h"

class CFacet
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void SetVertexNumber(int vNumber);
	void SetFacetNormal(CP3 Vertex0, CP3 Vertex1, CP3 Vertex2, CP3 Vertex3);
public:
	int vNumber;//��Ķ�����
	int vIndex[4];//��Ķ���������
	CVector3 fNormal;//��ķ�����
};

