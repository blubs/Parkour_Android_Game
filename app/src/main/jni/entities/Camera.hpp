//
// Created by F1 on 4/29/2016.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "../engine/common.hpp"
#include "../engine/misc.hpp"
#include "../engine/Game_Object.hpp"

class Camera : public Entity
{
public:
	float fov;
	float aspect;
	float near_plane;
	float far_plane;


	Vec3 up;
	Vec3 forward;
	Vec3 right;

	//How are we going to reference the parent of the camera?

	Mat4 persp_proj_m;
	Mat4 ortho_proj_m;
	Mat4 inf_proj_m;
	Mat4 view_m;

	//Update the view attributes
	void set_persp_view(float field_of_view, int width, int height, float near_clipping_plane, float far_clipping_plane);
	void set_ortho_view(int width, int height, float near_clipping_plane, float far_clipping_plane);


	//Converts angles to forward,right,and up vectors, and sets the view matrix
	void update_view_matrix();


	static const int VIEWBOB_NONE = 0;
	static const int VIEWBOB_RUNNING = 1;
	static const int VIEWBOB_SLIDING = 2;
	int viewbob;
	Vec3 viewbob_vel;
	void set_viewbob(int type);
	void viewbob_run_footstep(float pitch_v,float yaw_v, float roll_v);
	void update_viewbob();
};

#endif //ENGINE_CAMERA_H

