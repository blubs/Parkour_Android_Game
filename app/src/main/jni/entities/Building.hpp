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
	//x & y are in floor tiles, z is in windowgridtiles
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

	//Dispatches to floor's input_to_maneuver
	//	ultimately returns a maneuver if there exists a maneuver in the current floor's tileset such that:
	//	(the input required to start the maneuver is input_type) AND (the player is within the bounding box required to start the maneuver)
	//	returns NULL if no such Maneuver exists
	Maneuver* input_to_maneuver(Vec3 pos, int input_type)
	{
		return active_floor->input_to_maneuver(pos,input_type);
	}


	Vec3 get_tile_ofs_at_pos(Vec3 p)
	{
		return active_floor->get_tile_ofs_at_pos(p);
	}


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
	void generate(Vec3 player_pos)
	{
		active_floor_number = 10;

		floors = 20;

		dimensions = Vec3(10,10,floors);

		size = Vec3(dimensions.x * TILE_SIZE, dimensions.y * TILE_SIZE, dimensions.z * WINDOW_TILE_SIZE);

		pos = Vec3(0,0,GROUNDLEVEL);

		global_mins = Vec3(pos.x - 0.5f*size.x, pos.y, pos.z);
		global_maxs = Vec3(global_mins.x + size.x, pos.y + size.y, pos.z+size.z);

		active_floor->generate(pos,active_floor_number,global_mins,global_maxs,player_pos);
	}

	void regenerate_floor(Vec3 player_pos)
	{
		active_floor->clear();

		floors = 20;

		//Range from [10 -> 20]
		float size_x = 10 + floorf(Random::rand() * 11);
		float size_y = 10 + floorf(Random::rand() * 11);

		dimensions = Vec3(size_x,size_y,floors);

		size = Vec3(dimensions.x * TILE_SIZE, dimensions.y * TILE_SIZE, dimensions.z * WINDOW_TILE_SIZE);

		pos = Vec3(0,0,GROUNDLEVEL);

		global_mins = Vec3(pos.x - 0.5f*size.x, pos.y, pos.z);
		global_maxs = Vec3(global_mins.x + size.x, pos.y + size.y, pos.z+size.z);


		active_floor->generate(pos,active_floor_number,global_mins,global_maxs,player_pos);


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
		return active_floor->is_solid_at(p);
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

	int render(Vec3 player_pos, Mat4 vp)
	{
		//TODO: if this building is generated
		//TODO: render this building
		//If we are in the building, only render floor and interior glass
		//if we are out of the building, only render exterior FIXME: this needs additional checks for broken windows (culling sides of building as well)
		bool plyr_in_bldg = !is_out_of_bounds(player_pos);

		if(!plyr_in_bldg)
		{
			Global_Tiles::instance->window_mat->bind_material();

			Material* mat = Global_Tiles::instance->window_mat;
			mat->bind_value(Shader::PARAM_TEXTURE_DIFFUSE,(void*) Global_Tiles::instance->window_tex0);
			mat->bind_value(Shader::PARAM_TEXTURE_NORMAL,(void*) Global_Tiles::instance->window_tex0);

			Mat4 m;
			Mat4 world_trans = Mat4::TRANSLATE(global_mins);

			Static_Model* model = Global_Tiles::instance->window_model;

			//Quick unoptimized test for rendering

			//Only have to bind the mesh once
			model->bind_mesh_data2(mat);
			//Rendering the front wall of the building
			for(int i = 0; i < dimensions.x; i++)
			{
				for(int j = 0; j < dimensions.z; j++)
				{
					//model->bind_mesh_data2(mat);

					m = world_trans * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,0,j*WINDOW_TILE_SIZE));

					Mat4 mvp = vp * m;
					mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

					Mat3 m_it = m.inverted_then_transposed().get_mat3();
					mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

					model->render_without_bind();
				}
			}


			//Rendering the back wall of the building
			Mat4 wall_orientation = Mat4::TRANSLATE(Vec3(size.x,size.y,0)) * Mat4::ROTATE(Quat(PI,Vec3::UP()));
			for(int i = 0; i < dimensions.x; i++)
			{
				for(int j = 0; j < dimensions.z; j++)
				{
					//model->bind_mesh_data2(mat);

					m = world_trans * wall_orientation * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,0,j*WINDOW_TILE_SIZE));

					Mat4 mvp = vp * m;
					mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

					Mat3 m_it = m.inverted_then_transposed().get_mat3();
					mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

					model->render_without_bind();
				}
			}

			//Rendering the right wall of the building
			wall_orientation = Mat4::TRANSLATE(Vec3(size.x,0,0)) * Mat4::ROTATE(Quat(HALF_PI,Vec3::UP()));
			for(int i = 0; i < dimensions.y; i++)
			{
				for(int j = 0; j < dimensions.z; j++)
				{
					//model->bind_mesh_data2(mat);

					m = world_trans * wall_orientation * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,0,j*WINDOW_TILE_SIZE));

					Mat4 mvp = vp * m;
					mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

					Mat3 m_it = m.inverted_then_transposed().get_mat3();
					mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

					model->render_without_bind();
				}
			}

			//Rendering the left wall of the building
			wall_orientation = Mat4::TRANSLATE(Vec3(0,size.y,0)) * Mat4::ROTATE(Quat(HALF_PI+PI,Vec3::UP()));
			for(int i = 0; i < dimensions.y; i++)
			{
				for(int j = 0; j < dimensions.z; j++)
				{
					//model->bind_mesh_data2(mat);

					m = world_trans * wall_orientation * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,0,j*WINDOW_TILE_SIZE));

					Mat4 mvp = vp * m;
					mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

					Mat3 m_it = m.inverted_then_transposed().get_mat3();
					mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

					model->render_without_bind();
				}
			}
		}

		if(active_floor && plyr_in_bldg)
			active_floor->render(vp);
		return 1;
	}

	//Rendering method called at the end to render transparent windows and tiles
	int render_transparent_meshes(Vec3 player_pos, Mat4 vp)
	{
		//TODO: if this building is generated
		//TODO: render this building
		bool plyr_in_bldg = !is_out_of_bounds(player_pos);

		//Only render the interior windows if we are in the building
		if(plyr_in_bldg)
		{
			Global_Tiles::instance->window_int_mat->bind_material();

			Material* mat = Global_Tiles::instance->window_int_mat;
			mat->bind_value(Shader::PARAM_TEXTURE_DIFFUSE,(void*) Global_Tiles::instance->window_int_tex0);
			mat->bind_value(Shader::PARAM_TEXTURE_NORMAL,(void*) Global_Tiles::instance->window_int_tex0);
			mat->bind_value(Shader::PARAM_TEXTURE_MISC,(void*) Global_Tiles::instance->window_int_misc_tex0);

			//Drawing the interior windows only on the active floor number
			//TODO: skip drawing of broken interior windows (and draw their skeletal animations)
			Mat4 m;
			Mat4 world_trans = Mat4::TRANSLATE(global_mins + Vec3(0,0,active_floor_number*WINDOW_TILE_SIZE));

			Static_Model* model = Global_Tiles::instance->window_int_model;

			//Quick unoptimized test for rendering

			//Only have to bind the mesh once
			model->bind_mesh_data2(mat);
			//Rendering the front transparent windows
			for(int i = 0; i < dimensions.x; i++)
			{
				//model->bind_mesh_data2(mat);

				m = world_trans * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,0,0));

				Mat4 mvp = vp * m;
				mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

				Mat3 m_it = m.inverted_then_transposed().get_mat3();
				mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

				model->render_without_bind();
			}


			//Rendering the back transparent windows
			Mat4 wall_orientation = Mat4::TRANSLATE(Vec3(size.x,size.y,0)) * Mat4::ROTATE(Quat(PI,Vec3::UP()));
			for(int i = 0; i < dimensions.x; i++)
			{
				//model->bind_mesh_data2(mat);

				m = world_trans * wall_orientation * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,0,0));

				Mat4 mvp = vp * m;
				mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

				Mat3 m_it = m.inverted_then_transposed().get_mat3();
				mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

				model->render_without_bind();
			}

			//Rendering the right transparent windows
			wall_orientation = Mat4::TRANSLATE(Vec3(size.x,0,0)) * Mat4::ROTATE(Quat(HALF_PI,Vec3::UP()));
			for(int i = 0; i < dimensions.y; i++)
			{
				//model->bind_mesh_data2(mat);

				m = world_trans * wall_orientation * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,0,0));

				Mat4 mvp = vp * m;
				mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

				Mat3 m_it = m.inverted_then_transposed().get_mat3();
				mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

				model->render_without_bind();
			}

			//Rendering the left transparent windows
			wall_orientation = Mat4::TRANSLATE(Vec3(0,size.y,0)) * Mat4::ROTATE(Quat(HALF_PI+PI,Vec3::UP()));
			for(int i = 0; i < dimensions.y; i++)
			{
				//model->bind_mesh_data2(mat);

				m = world_trans * wall_orientation * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,0,0));

				Mat4 mvp = vp * m;
				mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

				Mat3 m_it = m.inverted_then_transposed().get_mat3();
				mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

				model->render_without_bind();
			}
		}
		//FIXME: if we end up using transparency in tiles, call transparent render for floor
		//if(active_floor)
		//	active_floor->render(vp);
		return 1;
	}
};
#endif //PARKOUR_BUILDING_HPP
