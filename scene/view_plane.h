#ifndef __VIEW_PLANE_H
#define __VIEW_PLANE_H
#include "../common/common.h"
class View_Plane
{
public:
	View_Plane()
	{
		M3DVector3f zero;
		zero[0] = zero[1] = zero[2] = 0;
		m3dCopyVector3(origin_,zero);
		m3dCopyVector3(eye_,zero);
		m3dCopyVector3(u_,zero);
		m3dCopyVector3(v_,zero);

		m3dCopyVector3(origin_backup_,zero);
		m3dCopyVector3(eye_backup_,zero);
		m3dCopyVector3(u_backup_,zero);
		m3dCopyVector3(v_backup_,zero);
	}

public:
	inline void set_origin(float x, float y, float z) 
	{	
		origin_[0] = x; origin_backup_[0] = x;
		origin_[1] = y; origin_backup_[1] = x;
		origin_[2] = z; origin_backup_[2] = x;
	}

	inline void set_origin(const M3DVector3f vector)  { 	m3dCopyVector3(origin_,vector); m3dCopyVector3(origin_backup_,vector);	}
	inline void get_origin(M3DVector3f vector) const  { 	m3dCopyVector3(vector,origin_);	}
	
	inline void set_eye(float x, float y, float z) 
	{	
		eye_[0] = x;	eye_backup_[0] = x;
		eye_[1] = y;	eye_backup_[1] = y;
		eye_[2] = z;	eye_backup_[2] = z;
	}
	inline void set_eye(const M3DVector3f vector) { m3dCopyVector3(eye_,vector); m3dCopyVector3(eye_backup_,vector); }
	inline void get_eye(M3DVector3f vector) const {	m3dCopyVector3(vector,eye_); }

	inline void set_u(float x, float y, float z) 
	{	
		u_[0] = x; u_backup_[0] = x;
		u_[1] = y; u_backup_[1] = y;
		u_[2] = z; u_backup_[2] = z;
	}
	inline void set_u(const M3DVector3f vector) { m3dCopyVector3(u_,vector); m3dCopyVector3(u_backup_,vector);}
	inline void get_u(M3DVector3f vector) const { m3dCopyVector3(vector,u_);}
	
	inline void set_v(float x, float y, float z) 
	{	
		v_[0] = x; v_backup_[0] = x;
		v_[1] = y; v_backup_[1] = y;
		v_[2] = z; v_backup_[2] = z;
	}
	inline void set_v(const M3DVector3f vector) { m3dCopyVector3(v_,vector);m3dCopyVector3(v_backup_,vector); }
	inline void get_v(M3DVector3f vector) const { m3dCopyVector3(vector,v_); }

	inline void reset_coord()
	{
		m3dCopyVector3(origin_,origin_backup_);
		m3dCopyVector3(eye_,eye_backup_);
		m3dCopyVector3(u_,u_backup_);
		m3dCopyVector3(v_,v_backup_);
	}

public:
	void get_pij(M3DVector3f point, float move_u, float move_v);

	void move(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void transfer(M3DVector3f vec, M3DMatrix33d tran_matrix);

	void get_orth_ray(M3DVector3f vector) const;
	void get_per_ray(M3DVector3f vVector, M3DVector3f vPoint) const;
private:
	M3DVector3f origin_;
	M3DVector3f eye_;
	M3DVector3f u_;
	M3DVector3f v_;

	M3DVector3f origin_backup_;
	M3DVector3f eye_backup_;
	M3DVector3f u_backup_;
	M3DVector3f v_backup_;

};
#endif