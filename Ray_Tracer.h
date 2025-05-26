#pragma once
#include "scene/Scene.h"
#include "scene/view_plane.h"
#include "common/image_volume.h"

class Ray_Tracer
{
public:
	Ray_Tracer(void);
public:
	~Ray_Tracer(void);
public:
	void	run(Image & image);
	void	ray_tracing(M3DVector3f start, M3DVector3f direct, float weight, M3DVector3f color, unsigned int depth,Basic_Primitive * prim);
private:
	bool	check_shadow(M3DVector3f intersect_point);
private:
	Scene		_scene;
	View_Plane	_view_plane;
	M3DVector3f	_dim;
	float		_min_weight;
	float		_max_depth;
};
