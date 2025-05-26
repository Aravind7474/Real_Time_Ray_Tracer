#pragma once
#include "../common/common.h"
#include "Basic_Primitive.h"
#include "../common/image_volume.h"
#include <string>

class Sphere : public Basic_Primitive
{
public:
	Sphere(M3DVector3f pos, float rad, M3DVector3f color)
		:Basic_Primitive(_k_sphere, 0.35)
		, _rad(rad)
		, _texture(NULL)
	{
		_rad2 = rad * rad;
		m3dCopyVector3(_pos, pos);
		m3dCopyVector3(_color, color);
		_kd = 1.0;
		_ka = 0.2;
		_ks = 1.0;

		_ks2 = _ks;
		_kt = 0.5;

		_ws = 0.2;
		_wt = 0.5;
	}

	~Sphere()
	{

	}

public:
	void	get_param(M3DVector3f pos, float& rad) const
	{
		m3dCopyVector3(pos, _pos);
		rad = _rad;
	}
public:
	Intersect_Cond	intersection_check(const M3DVector3f start, const M3DVector3f dir, float& distance, M3DVector3f intersection_p);
	void	shade(M3DVector3f view, M3DVector3f intersect_p, const Light& sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow);
	void	get_properties(float& ks, float& kt, float& ws, float& wt) const { ks = _ks2; kt = _kt; ws = _ws; wt = _wt; }
	void	set_properties(float ks, float  kt, float  ws, float  wt) { _ks2 = _ks = ks; _kt = kt; _ws = ws; _wt = wt; }
	virtual	void	get_reflect_direct(const M3DVector3f direct, const M3DVector3f intersect_p, M3DVector3f reflect_direct) {};
	virtual	bool	get_refract_direct(const M3DVector3f direct, const M3DVector3f intersect_p, M3DVector3f refract_direct, float delta, bool is_in) { return true; }
public:
	void load_texture(std::string file_name);
private:
	inline void	get_color(M3DVector3f pos, M3DVector3f color) { if (_texture == NULL) m3dCopyVector3(color, _color); else texture_color(pos, color); }
	void	texture_color(M3DVector3f pos, M3DVector3f color);
	void	get_texel(float x, float y, M3DVector3f color);
private:
	M3DVector3f	_pos;
	M3DVector3f	_color;
	float		_rad;
	float		_rad2;
	float		_ws;
	float		_wt;
	float		_kt;
	float		_ks2;

	float		_kd;
	float		_ks;
	float		_ka;
private:
	Image* _texture;
};
