#pragma once
#include "Basic_Primitive.h"

class Triangle:public Basic_Primitive
{
public:
	Triangle(M3DVector3f v0, M3DVector3f v1, M3DVector3f v2)
	{
		m3dCopyVector3(_v0,v0);
		m3dCopyVector3(_v1,v1);
		m3dCopyVector3(_v2,v2);
	}
public:
	~Triangle(void){}
	inline	void	get_vertex(M3DVector3f v0, M3DVector3f v1, M3DVector3f v2) const
	{
		m3dCopyVector3(v0,_v0);
		m3dCopyVector3(v1,_v1);
		m3dCopyVector3(v2,_v2);
	}

public:
	Intersect_Cond	intersection_check(const M3DVector3f start, const M3DVector3f dir, float & distance, M3DVector3f intersection_p);
	void	normal(M3DVector3f normal);
private:
	void	shade(M3DVector3f view,M3DVector3f intersect_p,const Light & sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow){}
	void	get_reflect_direct(const M3DVector3f direct,const M3DVector3f intersect_p,M3DVector3f reflect_direct) {}
	void	get_properties(float & ks,float & kt, float & ws, float & wt) const {}
public:
	M3DVector3f	_v0;
	M3DVector3f	_v1;
	M3DVector3f	_v2;
};
