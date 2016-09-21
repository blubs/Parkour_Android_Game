//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_BUILDING_HPP
#define PARKOUR_BUILDING_HPP

#include "../engine/math/math.hpp"
#include "Floor.hpp"

class Building : Entity
{
public:
	//Pos of the building is going to be defined as (center,smallest(closest to 0),bottom of building)
	//Where the bottom of the buildings go in world space
	static const int GROUNDLEVEL = -50;

	static const int MAX_WIDTH = BUILDING_MAX_WIDTH;
	static const int MAX_LENGTH = BUILDING_MAX_LENGTH;

	//pos is center near bottom of building

	//Size of the building in meters
	Vec3 size;
	//Size of the building in tiles (ints)
	Vec3 dimensions;
	//Global left near bottom of building
	Vec3 global_mins;
	//Global right far top of building
	Vec3 global_maxs;
	//Number of floors this building has
	int floors = 0;

	//TODO: this array will hold variant index of a tile
	char tiles[MAX_WIDTH][MAX_LENGTH];

	//char tile_types[MAX_WIDTH][MAX_LENGTH];

	Floor *active_floor = NULL;
	int active_floor_number = 0;



	Building()
	{
		active_floor = new Floor();
		clear();
	}
	~Building()
	{
		if(active_floor)
			delete active_floor;
	}

	//Creates the building
	void generate()
	{
		active_floor_number = 10;

		floors = 20;

		dimensions = Vec3(10,10,floors);

		size = GRIDSIZE*dimensions;//FIXME: how tall in meters are floors? currently they are assumed to be 3 m, which is tiny

		pos = Vec3(0,0,GROUNDLEVEL);

		global_mins = Vec3(pos.x - 0.5f*size.x, pos.y, pos.z);
		global_maxs = Vec3(global_mins.x + size.x, pos.y + size.y, pos.z+size.z);

		active_floor->generate(pos,active_floor_number,global_mins,global_maxs);

		//TODO: generate building mesh and floor
	}
	//Clears the created building, zeroes everything out
	void clear()
	{
		active_floor_number = 0;
		floors = 0;
		dimensions = Vec3(0,0,0);
		size = Vec3(0,0,0);
		pos = Vec3(0,0,0);
		global_mins = Vec3(0,0,0);
		global_maxs = Vec3(0,0,0);

		//TODO: destroy building and floor model
	}

	char is_solid_at(Vec3 p)
	{
		return active_floor->is_solid_at(p-pos);
	}

	bool is_out_of_bounds(Vec3 p)
	{
		if(p.x < global_mins.x || p.x > global_maxs.x)
			return true;
		if(p.y < global_mins.y || p.y > global_maxs.y)
			return true;
		//Z bounds are not handled here
		return false;
	}

	bool is_box_out_of_bounds(Vec3 p, float half_width)
	{
		if(p.x-half_width < global_mins.x || p.x+half_width > global_maxs.x)
			return true;
		if(p.y-half_width < global_mins.y || p.y+half_width > global_maxs.y)
			return true;
		//Z bounds are not handled here
		return false;
	}

	int render(Mat4 vp)
	{
		//TODO: if this building is generated
		//TODO: render this building

		Global_Tiles::instance->window_mat->bind_material();

		Material* mat = Global_Tiles::instance->window_mat;
		mat->bind_value(Shader::PARAM_TEXTURE_DIFFUSE,(void*) Global_Tiles::instance->window_tex0);
		mat->bind_value(Shader::PARAM_TEXTURE_NORMAL,(void*) Global_Tiles::instance->window_tex0);

		Mat4 m;
		Mat4 world_trans = Mat4::TRANSLATE(global_mins);

		Static_Model* model = Global_Tiles::instance->window_model;

		//Quick unoptimized test for rendering


		//Rendering the front wall of the building
		for(int i = 0; i < dimensions.x; i++)
		{
			for(int j = 0; j < dimensions.z; j++)
			{
				model->bind_mesh_data2(mat);

				m = world_trans * Mat4::TRANSLATE(Vec3(i*GRIDSIZE,j*GRIDSIZE,0));

				Mat4 mvp = vp * m;
				mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

				Mat3 m_it = m.inverted_then_transposed().get_mat3();
				mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

				model->render_without_bind();
			}
		}

		Mat4 wall_orientation = Mat4::ROTATE(Quat(PI,Vec3::UP())) * ;

		//Rendering the back wall of the building
		for(int i = 0; i < dimensions.x; i++)
		{
			for(int j = 0; j < dimensions.z; j++)
			{
				model->bind_mesh_data2(mat);

				m = world_trans * Mat4::TRANSLATE(Vec3(i*GRIDSIZE,size.y,j*GRIDSIZE));
				//TODO: rotate the window tiles

				Mat4 mvp = vp * m;
				mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

				Mat3 m_it = m.inverted_then_transposed().get_mat3();
				mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

				model->render_without_bind();
			}
		}


		if(active_floor)
			active_floor->render(vp);
	}
};

#endif //PARKOUR_BUILDING_HPP
