#include "Triangle.h"

Intersect_Cond	Triangle::intersection_check(const M3DVector3f start, const M3DVector3f dir, float & distance, M3DVector3f intersection_p)
{
	float u, v;
	M3DVector3f edge1, edge2, tvec, pvec, qvec;
	float det, invDet;

	m3dSubtractVectors3(edge1,_v1, _v0);
	m3dSubtractVectors3(edge2,_v2, _v0);
	m3dCrossProduct(pvec,dir, edge2);

	det = m3dDotProduct(edge1, pvec);

	if(det > -.00000001 && det < .00000001)
	{
		return _k_miss;
	}
	invDet = 1/det;
	
	m3dSubtractVectors3(tvec, start, _v0);

	u = m3dDotProduct(tvec, pvec) * invDet;
	if(u < -0.00001 || u > 1.00001)
	{
		return _k_miss;
	}

	m3dCrossProduct(qvec, tvec, edge1);
	v = m3dDotProduct(dir, qvec) * invDet;
	if(v < -0.000001 || (u + v) > 1.00001)
	{
		return _k_miss;
	}

	distance = m3dDotProduct(edge2, qvec) * invDet;
	if( distance < 0)
	{
		return _k_miss;
	}
	M3DVector3f tmp_v;
	m3dCopyVector3(tmp_v, dir);
	m3dScaleVector3(tmp_v,distance);
	m3dAddVectors3(intersection_p,start,tmp_v);
	return _k_hit;
}

void	Triangle::normal(M3DVector3f normal)
{
	M3DVector3f edge1, edge2;
	m3dSubtractVectors3(edge1,_v1,_v0);
	m3dSubtractVectors3(edge2,_v2,_v0);

	m3dCrossProduct(normal,edge1,edge2);
	m3dNormalizeVector(normal);
}