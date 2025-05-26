#pragma once
#include "../common/common.h"

class Light
{
public:
	Light(M3DVector3f pos, M3DVector3f color)
	{
		m3dCopyVector3(_pos,pos);
		m3dCopyVector3(_color,color);
	}

	Light()
	{
		_color[0] =_color[1] =_color[2] = 0;
		_pos[0] = _pos[1] = _pos[2] = 0;
	}
public:
	~Light(void){}
	void get_light(M3DVector3f pos, M3DVector3f color) const
	{
		m3dCopyVector3(pos,_pos);
		m3dCopyVector3(color,_color);
	}

	void get_light_pos(M3DVector3f pos) const
	{
		m3dCopyVector3(pos,_pos);
	}

	inline	void set_light(const M3DVector3f pos, const M3DVector3f color)
	{
		m3dCopyVector3(_pos,pos);
		m3dCopyVector3(_color,color);
	}
private:
	M3DVector3f	_pos;
	//M3DVector3f	_direct;
	M3DVector3f	_color;
};
