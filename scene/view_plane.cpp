#include "view_plane.h"

void View_Plane::get_pij(M3DVector3f point, float move_u, float move_v)
{
	M3DVector3f v, u;
	m3dCopyVector3(v, v_); 
	m3dCopyVector3(u, u_); 

	m3dScaleVector3(u, move_u);
	m3dScaleVector3(v, move_v);

	m3dAddVectors3(point, u, v);
	m3dAddVectors3(point, point, origin_);
}

void View_Plane::move(float x, float y, float z)
{
	eye_[0] += x;
	eye_[1] += y;
	eye_[2] += z;

	origin_[0] += x;
	origin_[1] += y;
	origin_[2] += z;
}

void View_Plane::rotate(float angle, float x, float y, float z)
{
	M3DMatrix33d rotate_matrix;
	m3dRotationMatrix33(rotate_matrix,angle,x,y,z);

	transfer(eye_,rotate_matrix);
	transfer(origin_,rotate_matrix);
	transfer(u_,rotate_matrix);
	transfer(v_,rotate_matrix);
}

void View_Plane::transfer(M3DVector3f vec, M3DMatrix33d tran_matrix)
{
	M3DVector3f new_vec;
	new_vec[0] = vec[0] * tran_matrix[0] + vec[1] * tran_matrix[3] + vec[2] * tran_matrix[6];
	new_vec[1] = vec[0] * tran_matrix[1] + vec[1] * tran_matrix[4] + vec[2] * tran_matrix[7];
	new_vec[2] = vec[0] * tran_matrix[2] + vec[1] * tran_matrix[5] + vec[2] * tran_matrix[8];
	m3dCopyVector3(vec,new_vec);
}

void View_Plane::get_orth_ray(M3DVector3f vector) const
{
	m3dCrossProduct(vector,u_,v_);
	m3dNormalizeVector(vector);
}

void View_Plane::get_per_ray(M3DVector3f vVector, M3DVector3f vPoint) const
{ 
	m3dSubtractVectors3(vVector, vPoint, eye_);
	m3dNormalizeVector(vVector);
}
