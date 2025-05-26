#include "sphere.h"
#include "../Imageio/Imageio.h"
#include <math.h>

Intersect_Cond	Sphere::intersection_check(const M3DVector3f start, const M3DVector3f dir, float& distance, M3DVector3f intersection_p)
{
	M3DVector3f ray_to_center;
	m3dSubtractVectors3(ray_to_center, _pos, start);
	float ray_center_length = m3dDotProduct(ray_to_center, ray_to_center);

	float closest_point = m3dDotProduct(ray_to_center, dir);
	if (closest_point < 0)
	{
		return _k_miss;
	}

	float halfCord2 = (_rad * _rad) - (ray_center_length - (closest_point * closest_point));
	if (halfCord2 < 0)
	{
		return _k_miss;
	}

	Intersect_Cond type;
	M3DVector3f tmp;
	m3dSubtractVectors3(tmp, start, _pos);
	float length = m3dDotProduct(tmp, tmp);
	if (length < _rad2)
	{
		type = _k_inside;
		distance = closest_point + sqrt(halfCord2);
	}
	else
	{
		type = _k_hit;
		distance = closest_point - sqrt(halfCord2);
	}

	M3DVector3f tmp_v;
	m3dCopyVector3(tmp_v, dir);
	m3dScaleVector3(tmp_v, distance);
	m3dAddVectors3(intersection_p, start, tmp_v);

	return type;
}

void Sphere::shade(M3DVector3f view, M3DVector3f intersect_p, const Light& sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow)
{
	
	M3DVector3f normal;
	m3dSubtractVectors3(normal, intersect_p, _pos);
	m3dNormalizeVector(normal);

	
	M3DVector3f light_dir, light_pos, light_color;
	sp_light.get_light(light_pos, light_color);

	
	m3dSubtractVectors3(light_dir, light_pos, intersect_p);
	m3dNormalizeVector(light_dir);

	
	float dot = m3dDotProduct(light_dir, normal);
	float diffuse_coef = dot;
	if (diffuse_coef < 0) diffuse_coef = 0;
	if (shadow) diffuse_coef = 0;

	
	float sp_coeff;
	M3DVector3f r;
	M3DVector3f  tmp;
	m3dCopyVector3(tmp, normal);
	m3dScaleVector3(tmp, (2 * dot));
	m3dSubtractVectors3(r, light_dir, tmp);

	
	sp_coeff = m3dDotProduct(view, r);
	if (sp_coeff < 0) sp_coeff = 0;
	if (shadow) sp_coeff = 0;

	
	sp_coeff = pow(sp_coeff, 11);

	for (int i = 0; i < 3; i++)
	{
		color[i] = _kd * diffuse_coef + _ks * sp_coeff * light_color[i] + _ka * am_light[i];
		color[i] *= _color[i];
	}

	//Apply texture
	M3DVector3f tex_color;
	get_color(intersect_p, tex_color);
	for (int i = 0; i < 3; i++)
	{
		color[i] *= tex_color[i];
	}
}

void Sphere::load_texture(std::string file_name)
{
	_texture = new Image;
	if (_texture == NULL)
	{
		printf("Can't allocate image for %s. Exiting\n", file_name.c_str());
		return;
	}

	ReadImage(file_name.c_str(), _texture->nx, _texture->ny, _texture->data, _texture->ncolorChannels);
}

void Sphere::texture_color(M3DVector3f pos, M3DVector3f color)
{
	//Compute 2D position on the sphere
	float x = pos[0] - _pos[0];
	float y = pos[1] - _pos[1];

	//Remap to unit range
	x /= _rad;
	y /= _rad;

	//Get the texture value
	get_texel(x, y, color);
}

void Sphere::get_texel(float x, float y, M3DVector3f color)
{
	//Remap to texture range
	int ix = int(x * _texture->nx + _texture->nx) % _texture->nx;
	int iy = int(y * _texture->ny + _texture->ny) % _texture->ny;

	//Access the texture
	int i = (ix + iy * _texture->nx) * 3;
	color[0] = _texture->data[i + 0] / 255.0;
	color[1] = _texture->data[i + 1] / 255.0;
	color[2] = _texture->data[i + 2] / 255.0;
}