#pragma once
#include "../common/common.h"
#include "../scene/Light.h"

typedef enum
{
	_k_hit	=	0,
	_k_miss ,
	_k_inside
} Intersect_Cond;

class Basic_Primitive
{
public:
	enum  Object_Type
	{
		_k_unknown = 0,
		_k_triangle,
		_k_sphere,
		_k_wall,
		_k_object
	};
public:
	Basic_Primitive(Object_Type type = _k_triangle, float delta = 1.0)
		:_type(type), _delta(delta)
	{ 	}
	virtual	~Basic_Primitive() {};
	virtual	Intersect_Cond	intersection_check(const M3DVector3f start, const M3DVector3f dir, float & distance, M3DVector3f intersection_p) = 0;
	virtual	void	shade(M3DVector3f view,M3DVector3f intersect_p,const Light & sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow) = 0;
	virtual	void	get_reflect_direct(const M3DVector3f direct,const M3DVector3f intersect_p,M3DVector3f reflect_direct) = 0;
	virtual	bool	get_refract_direct(const M3DVector3f direct,const M3DVector3f intersect_p,M3DVector3f refract_direct, float delta,bool is_in) { m3dLoadVector3(refract_direct, 0, 0, 0); return true;}
	virtual	void	get_properties(float & ks,float & kt, float & ws, float & wt) const = 0;
	virtual	float	get_delta() const  {	return _delta; };
	Object_Type	get_type()	{	return	_type; }
	
protected:
	float	_delta;	//Refraction factor for material
	Object_Type	_type;
};
