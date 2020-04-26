#include "StdAfx.h"
#include "Facet.h"


CFacet::CFacet(void)
{
}

CFacet::~CFacet(void)
{

}

void CFacet::SetVertexNumber(int vNumber)
{
	this->vNumber = vNumber;
}

void CFacet::SetFacetNormal(CP3 Vertex0, CP3 Vertex1, CP3 Vertex2)//���淨ʸ������
{
	CVector3 Vector01(Vertex0, Vertex1);//Vertex0��Vertex1���㹹�ɱ�ʸ��
	CVector3 Vector02(Vertex0, Vertex2);//Vertex0��Vertex2���㹹�ɱ�ʸ��
	fNormal = CrossProduct(Vector01, Vector02);
}

void CFacet::SetFacetNormal(CVertex Vertex0, CVertex Vertex1, CVertex Vertex2)//���淨ʸ������
{
	CVector3 Vector01(Vertex0.P, Vertex1.P);//Vertex0��Vertex1���㹹�ɱ�ʸ��
	CVector3 Vector02(Vertex0.P, Vertex2.P);//Vertex0��Vertex2���㹹�ɱ�ʸ��
	fNormal = CrossProduct(Vector01, Vector02);
}