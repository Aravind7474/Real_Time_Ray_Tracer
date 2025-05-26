#include "Wall.h"
#include <math.h>
#include "../Imageio/Imageio.h"

Intersect_Cond Wall::intersection_check(const M3DVector3f start, const M3DVector3f dir, float& distance, M3DVector3f intersection_p)
{
	if (_tr1.intersection_check(start, dir, distance, intersection_p) == _k_hit)
	{
		return _k_hit;
	}
	else
	{
		return _tr2.intersection_check(start, dir, distance, intersection_p);
	}
}


void	Wall::shade(M3DVector3f view, M3DVector3f intersect_p, const Light& sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow)
{
	//For Wall shading, get normal for the wall face from one of its triangles 	
	M3DVector3f normal;
	_tr1.normal(normal);
	m3dNormalizeVector(normal);
	M3DVector3f light_dir, light_pos, light_color;
	//Get the location and color of the light source	
	sp_light.get_light(light_pos, light_color);
	//Compute the vector pointing to the light source	
	m3dSubtractVectors3(light_dir, light_pos, intersect_p);
	m3dNormalizeVector(light_dir);
	//Compute diffusion with dot product	
	float dot = m3dDotProduct(light_dir, normal);
	float diffuse_coef = dot;
	if (diffuse_coef < 0) diffuse_coef = 0;
	if (shadow) diffuse_coef = 0;
	//Use original Phong model to compute r	
	float sp_coeff;
	M3DVector3f r;
	M3DVector3f  tmp;
	m3dCopyVector3(tmp, normal);
	m3dScaleVector3(tmp, (2 * dot));
	m3dSubtractVectors3(r, light_dir, tmp);
	//Compute specular dot product	
	sp_coeff = m3dDotProduct(view, r);
	if (sp_coeff < 0) sp_coeff = 0;
	if (shadow) sp_coeff = 0;
	//Compute specular with shineness coefficient	
	sp_coeff = pow(sp_coeff, 11);
	//Generate color with Phong model	
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


void	Wall::get_reflect_direct(const M3DVector3f direct0, const M3DVector3f intersect_p, M3DVector3f reflect_direct)
{
	M3DVector3f normal;
	_tr1.normal(normal);
	//Reflection vector	
	float dot = m3dDotProduct(direct0, normal);
	m3dScaleVector3(normal, 2 * dot);
	m3dSubtractVectors3(reflect_direct, direct0, normal);
}


void Wall::load_texture(std::string file_name)
{
	_texture = new Image;
	if (_texture == NULL)
	{
		printf("Can't allocate image for %s. Exiting\n", file_name.c_str());
		return;
	}
	ReadImage(file_name.c_str(), _texture->nx, _texture->ny, _texture->data, _texture->ncolorChannels);
}

void Wall::texture_color(M3DVector3f pos, M3DVector3f color)
{
	float x = _is_yz ? pos[2] - _left_down[2] : pos[0] - _left_down[0];
	float y = _is_xz ? pos[2] - _left_down[2] : pos[1] - _left_down[1];
	//Remap to unit range	
	x /= _width;
	y /= _height;
	//Get the texture value	
	get_texel(x, y, color);
}

void	Wall::get_texel(float x, float y, M3DVector3f color)
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