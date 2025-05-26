#pragma once

#include <list>
#include "Light.h"
#include "../primitives/Sphere.h"
#include "../primitives/Wall.h"

typedef std::list<Basic_Primitive*> Prim_List;

class Scene
{
public:
	Scene();
	inline void	set_dim(const M3DVector3f dim) { m3dCopyVector3(_dim, dim); }
public:
	~Scene(void);
public:
	void	assemble();
	Intersect_Cond	intersection_check(const M3DVector3f start, const M3DVector3f dir, Basic_Primitive** prim_intersect, M3DVector3f closest_point);

public:
	const	Prim_List& get_prim_list() const { return _prim_list; }
	inline  const Light	get_sp_light() { return _sp_light; }
	inline	void	get_amb_light(M3DVector3f amb_light) { m3dCopyVector3(amb_light, _amb_light); }
private:
	Prim_List	_prim_list;
	Light		_sp_light;
	M3DVector3f	_amb_light;
	M3DVector3f	_dim;
};
