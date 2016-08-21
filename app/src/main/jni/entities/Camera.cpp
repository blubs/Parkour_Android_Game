//
// Created by F1 on 4/29/2016.
//

#include "Camera.hpp"

//Update the view attributes
void Camera::set_persp_view(float field_of_view, int width, int height, float near_clipping_plane, float far_clipping_plane)
{
	fov = field_of_view;
	float aspect_ratio = ((float) width )/ ((float) height);
	aspect = aspect_ratio;
	near_plane = near_clipping_plane;
	far_plane = far_clipping_plane;

	//Calculate the projection matrix
	persp_proj_m = Mat4::PROJECT_PERSPECTIVE(near_plane,far_plane,aspect,fov);
	//Calculate the infinite projection matrix
	inf_proj_m = Mat4::PROJECT_INFINITE(near_plane,aspect,fov);
}
void Camera::set_ortho_view(int width, int height, float near_clipping_plane, float far_clipping_plane)
{
	//Calculate the projection matrix
	ortho_proj_m = Mat4::PROJECT_ORTHO(near_clipping_plane,far_clipping_plane,(float)width,(float)height);
}


//Converts angles to forward,right,and up vectors, and sets the view matrix
void Camera::update_view_matrix()
{
	Quat flip_y_and_z(HALF_PI,Vec3::RIGHT());

	if(use_quaternion)
		transform = Mat4::ROT_TRANS(rot,pos,&right,&up,&forward) * Mat4::ROTATE(flip_y_and_z);
	else
		transform = Mat4::ROT_TRANS(angles,pos,&right,&up,&forward) * Mat4::ROTATE(flip_y_and_z);

	if(parent)
	{
		Mat4 parent_trans = parent->get_world_transform(true);
		world_transform = parent_trans * transform;

		//Getting the camera direction vectors in world-space
		//Only rotating right up and forward vectors
		Mat3 parent_rot = parent_trans.get_mat3();
		right = parent_rot * right;
		up = parent_rot * up;
		forward = parent_rot * forward;
	}
	else
		world_transform = transform;

	view_m = world_transform.inverted();
}

void Camera::set_viewbob (int type)
{
	viewbob = type;
}

void Camera::viewbob_run_footstep (float pitch_v,float yaw_v, float roll_v)
{
	viewbob_vel.x += pitch_v;
	viewbob_vel.y += yaw_v;
	viewbob_vel.z += roll_v;
}

void Camera::update_viewbob ()
{
	switch(viewbob)
	{
		case VIEWBOB_RUNNING:
		{
			//Going to simulate a spring, make the camera accelerate towards neutral
			Vec3 force(-angles.x,-angles.y,-angles.z);
			//Adding resistance to the spring
			float spring_constant = 100.0;
			float resistance = 0.9;
			force = spring_constant*force - resistance*viewbob_vel;
			viewbob_vel = viewbob_vel + Time::delta_time * force;
			angles = angles + Time::delta_time * viewbob_vel;
			break;
		}
		case VIEWBOB_SLIDING:
			break;
		default:
		case VIEWBOB_NONE:
			break;
	}
}