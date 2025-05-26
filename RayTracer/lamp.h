#pragma once
#pragma once
#include "../primitives/Basic_Primitive.h"
#include "../primitives/Triangle.h"
#include "../common/image_volume.h"
#include <string>
#include <map>
#include <list>

typedef std::list<Triangle*> Triangle_List;

class Object :public Basic_Primitive
{
public:
	Object(const char* fn, M3DVector3f pos, float size, M3DVector3f color)
		:Basic_Primitive(_k_object)
		, _tr(NULL)
		, _texture(NULL)
	{
		float x, y, z;
		int a, b, c, t;
		char str[100];
		FILE* in_file = fopen(fn, "rt");

		if (in_file == NULL) {
			printf("Can't open input file %s. Exiting.\n", fn);
			exit(1);
		}

		// mapping from vertex indices to coordinates
		std::map<int, float> vx, vy, vz;

		// get object data
		while (fgets(str, 100, in_file))
		{
			// get vertices
			if (sscanf(str, "v %f %f %f", &x, &y, &z))
			{
				
				vx[vx.size() + 1] = x * size + pos[0];
				vy[vy.size() + 1] = y * size + pos[1];
				vz[vz.size() + 1] = z * size + pos[2];
			}

			// get faces
			if (sscanf(str, "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t, &t, &b, &t, &t, &c, &t, &t))
			{
				
				M3DVector3f v0 = { vx[a], vy[a], vz[a] };
				M3DVector3f v1 = { vx[b], vy[b], vz[b] };
				M3DVector3f v2 = { vx[c], vy[c], vz[c] };
				_triangle_list.push_back(new Triangle(v0, v1, v2));
			}
		}

		fclose(in_file);

		m3dCopyVector3(_color, color);
		_kd = 1.0;
		_ka = 1.0;
		_ks = 1.0;

		_ks2 = _ks;
		_kt = 0.0;

		_ws = 0.0;
		_wt = 0.0;	//No Refraction
	}

public:
	~Object(void)
	{
		if (_texture != NULL)
		{
			delete[] _texture->data;
			delete _texture;
		}

		Triangle* triangle = NULL;
		for (Triangle_List::iterator it = _triangle_list.begin(); it != _triangle_list.end();)
		{
			triangle = *it;
			_triangle_list.erase(it++);
			delete triangle;
		}
	}

public:
	Intersect_Cond	intersection_check(const M3DVector3f start, const M3DVector3f dir, float& distance, M3DVector3f intersection_p);
	void	shade(M3DVector3f view, M3DVector3f intersect_p, const Light& sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow);
	//void	get_reflect_direction(M3DVector3f dir);
	void	get_reflect_direct(const M3DVector3f direct, const M3DVector3f intersect_p, M3DVector3f reflect_direct);
	bool	get_refract_direct(const M3DVector3f direct, const M3DVector3f intersect_p, M3DVector3f refract_direct, float delta, bool is_in);

	void	get_properties(float& ks, float& kt, float& ws, float& wt) const { ks = _ks2; kt = _kt; ws = _ws; wt = _wt; }
	void	set_properties(float ks, float  kt, float  ws, float  wt) { _ks2 = _ks = ks; _kt = kt; _ws = ws; _wt = wt; }
public:
	void load_texture(std::string file_name);
private:
	inline void	get_color(M3DVector3f pos, M3DVector3f color) { if (_texture == NULL) m3dCopyVector3(color, _color); else texture_color(pos, color); }
	void	texture_color(M3DVector3f pos, M3DVector3f color);
	void	get_texel(float x, float y, M3DVector3f color);
private:
	Triangle* _tr;
	Triangle_List _triangle_list;
	M3DVector3f _color;
	float		_kd;
	float		_ks;
	float		_ka;

	float		_ws;
	float		_wt;
	float		_kt;
	float		_ks2;

private:
	Image* _texture;
};


