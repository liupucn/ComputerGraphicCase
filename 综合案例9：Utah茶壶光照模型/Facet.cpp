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

void CFacet::SetFacetNormal(CP3 Vertex0, CP3 Vertex1, CP3 Vertex2, CP3 Vertex3)//���淨��������
{
	CVector3 Vector01(Vertex0, Vertex1);       // Vertex0��Vertex1���㹹�ɱ�����
	CVector3 Vector02(Vertex0, Vertex2);       // Vertex0��Vertex2���㹹�ɱ�����
	CVector3 Vector03(Vertex0, Vertex3);       // Vertex0��Vertex3���㹹�ɱ�����
	CVector3 fNormal1 = CrossProduct(Vector01, Vector02);
	CVector3 fNormal2 = CrossProduct(Vector01, Vector03);
	fNormal = (fNormal1 + fNormal2);

}