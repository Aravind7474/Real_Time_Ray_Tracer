#include "lamp.h"
#include <math.h>
#include "../Imageio/Imageio.h"
#include "../common/math3d.h"

Intersect_Cond Object::intersection_check(const M3DVector3f start, const M3DVector3f dir, float& length, M3DVector3f intersection_p)
{
	Intersect_Cond cond = _k_miss;
	_tr = NULL;
	length = 1e+6;
	float distance;
	M3DVector3f p;

	
	for (Triangle_List::iterator it = _triangle_list.begin(); it != _triangle_list.end(); it++)
	{
		Triangle* tr = *it;

		
		if (tr->intersection_check(start, dir, distance, p) != _k_hit)
			continue;

		
		if (distance < length)
		{
			cond = _k_hit;
			_tr = tr;
			m3dCopyVector3(intersection_p, p);
			length = distance;
		}
	}

	return cond;
}


void Object::shade(M3DVector3f view, M3DVector3f intersect_p, const Light& sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow)
{
	//For Object shading, get the surface normal
	M3DVector3f normal;
	_tr->normal(normal);
	m3dScaleVector3(normal, -1);

	M3DVector3f light_direction, light_position, light_color;

	//Get the light location and color
	sp_light.get_light(light_position, light_color);

	//Compute the light direction vector
	m3dSubtractVectors3(light_direction, light_position, intersect_p);
	m3dNormalizeVector(light_direction);

	
	float dot = m3dDotProduct(light_direction, normal);
	float diffuse_coef = dot;
	if (diffuse_coef < 0) diffuse_coef = 0;
	if (shadow) diffuse_coef = 0;


	float sp_coeff;
	M3DVector3f r;
	M3DVector3f  _tmp_;
	m3dCopyVector3(_tmp_, normal);
	m3dScaleVector3(_tmp_, (2 * dot));
	m3dSubtractVectors3(r, light_direction, _tmp_);

	
	sp_coeff = m3dDotProduct(view, r);
	if (sp_coeff < 0) sp_coeff = 0;
	if (shadow) sp_coeff = 0;

	
	sp_coeff = pow(sp_coeff, 11);


	//Generate color with Phong model
	for (int i = 0; i < 3; i++)
	{
		color[i] = _kd * diffuse_coef + _ks * sp_coeff * light_color[i] + _ka * am_light[i];
		color[i] *= _color[i];
	}

}


void Object::get_reflect_direct(const M3DVector3f direct0, const M3DVector3f intersect_p, M3DVector3f reflect_direct)
{
	//Normal vector
	M3DVector3f normal;
	_tr->normal(normal);
	m3dScaleVector3(normal, -1);

	//Reflection vector
	float dot = m3dDotProduct(direct0, normal);
	m3dScaleVector3(normal, 2 * dot);
	m3dSubtractVectors3(reflect_direct, direct0, normal);
}

bool Object::get_refract_direct(const M3DVector3f direct, const M3DVector3f intersect_p, M3DVector3f refract_direct, float delta, bool is_in)
{
	//Normal vector
	M3DVector3f normal;
	_tr->normal(normal);
	m3dScaleVector3(normal, -1);

	//Choose appropriate refraction index and normal vector for inside/outside hits
	float r = is_in ? 1 / delta : delta;
	m3dScaleVector3(normal, is_in ? -1.0 : 1.0);

	//Refraction vector
	float dot = m3dDotProduct(direct, normal) * r;
	float _tmp_ = r * r - dot * dot;
	if (_tmp_ < 1)
	{
		m3dCopyVector3(refract_direct, direct);
		m3dScaleVector3(refract_direct, r);
		m3dScaleVector3(normal, dot + sqrtf(1 - _tmp_));
		m3dSubtractVectors3(refract_direct, refract_direct, normal);
		return true;
	}

	return false;
}


void Object::load_texture(std::string file_name)
{

}

void Object::texture_color(M3DVector3f pos, M3DVector3f color)
{
}

void Object::get_texel(float x, float y, M3DVector3f color)
{
	return;
}