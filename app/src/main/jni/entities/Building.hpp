//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_BUILDING_HPP
#define PARKOUR_BUILDING_HPP

#include "../engine/math/math.hpp"
#include "../game/game_defs.hpp"
#include "Floor.hpp"

class Building : public Entity
{
public:
	//Pos of the building is going to be defined as (center,smallest(closest to 0),bottom of building)
	//Where the bottom of the buildings go in world space
	static const int GROUNDLEVEL = -50;

	static const int MAX_WIDTH = BUILDING_MAX_WIDTH;
	static const int MAX_LENGTH = BUILDING_MAX_LENGTH;
	static const int MAX_HEIGHT = BUILDING_MAX_HEIGHT;

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

	//Index of the window broken out of the building
	int broken_owindow_index_x = 0;
	int broken_owindow_index_y = 0;

	//Index of the window broken into the building
	int broken_iwindow_index_x = 0;
	int broken_iwindow_index_y = 0;

	//char tile_types[MAX_WIDTH][MAX_LENGTH];

	bool generated = false;
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

	//Dispatches to floor's input_to_traversal
	//	ultimately returns a traversal if we are at the last tile of the building and:
	//	(input_type is the input required to start the traversal) AND (the player is within the bounding box required to start the traversal)
	//	returns NULL if no such traversal exists
	Traversal* input_to_traversal(Vec3 pos, int input_type)
	{
		return active_floor->input_to_traversal(pos,input_type);
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
	void generate(Building* prev_bldg,Vec3 bldg_ofs)
	{
		if(generated)
			return;
		active_floor_number = 10;

		floors = 20;

		dimensions = Vec3(11,11,floors);

		size = Vec3(dimensions.x * TILE_SIZE, dimensions.y * TILE_SIZE, dimensions.z * WINDOW_TILE_SIZE);


		Vec3 prev_bldg_ofs = Vec3(0,0,0);
		if(prev_bldg != NULL)
		{
			prev_bldg_ofs = Vec3(prev_bldg->pos.x,prev_bldg->global_maxs.y,0);
			//TODO: calculate building offset based on size and previous building's position and size
		}
		pos = prev_bldg_ofs + bldg_ofs + Vec3(0,0,GROUNDLEVEL);

		global_mins = Vec3(pos.x - 0.5f*size.x, pos.y, pos.z);
		global_maxs = Vec3(global_mins.x + size.x, pos.y + size.y, pos.z+size.z);

		generate_exterior_model_list();
		generated = true;
	}

	//TODO: pass in the next building from which to get the goal range for the floor
	void generate_floor(Vec3 player_pos, Building* next_bldg)
	{
		if(!generated)
			return;

		//Finding our goal column range
		//(what tiles of this building line up with tiles of next_bldg)
		//Finding tile dimensions of next_bldg in terms of this building's tile dimensions
		int other_left_endpnt = (int)((next_bldg->pos.x - pos.x)/TILE_SIZE);
		int other_right_endpnt = ((int)next_bldg->dimensions.x) + other_left_endpnt;

		int goal_min = clamp(0,other_left_endpnt,other_right_endpnt);
		int goal_max = clamp((int)dimensions.x,other_left_endpnt,other_right_endpnt);

		LOGE("This Building: (x-pos:%.2f, x-dim:%.1f), Next Building: (x-pos:%.2f, x-dim:%.1f), goal range:[%d,%d]",pos.x,dimensions.x,next_bldg->pos.x,next_bldg->dimensions.x,goal_min,goal_max);

		active_floor->generate(pos,active_floor_number,global_mins,global_maxs,player_pos,goal_min,goal_max);
		generate_interior_model_list();
	}

	//Currently regenerates the building using a different rng numbers
	void regenerate_floor(Vec3 player_pos, Building* next_bldg)
	{
		int temp = active_floor_number;
		clear();
		active_floor_number = temp;
		active_floor->clear();

		floors = 20;

		//Range from [6 -> 14] in width
		float size_x = Random::rand_int_in_range(6,BUILDING_MAX_WIDTH+1);
		//Range from [10 -> 20] in length
		float size_y = Random::rand_int_in_range(10,BUILDING_MAX_LENGTH+1);

		dimensions = Vec3(size_x,size_y,floors);

		size = Vec3(dimensions.x * TILE_SIZE, dimensions.y * TILE_SIZE, dimensions.z * WINDOW_TILE_SIZE);

		pos = Vec3(0,0,GROUNDLEVEL);

		global_mins = Vec3(pos.x - 0.5f*size.x, pos.y, pos.z);
		global_maxs = Vec3(global_mins.x + size.x, pos.y + size.y, pos.z+size.z);

		generate_exterior_model_list();
		generated = true;
		generate_interior_model_list();

		//Finding our goal column range
		//(what tiles of this building line up with tiles of next_bldg)
		//Finding tile dimensions of next_bldg in terms of this building's tile dimensions
		int other_left_endpnt = (int)((next_bldg->pos.x - pos.x)/TILE_SIZE);
		int other_right_endpnt = ((int)next_bldg->dimensions.x) + other_left_endpnt;
		int goal_min = clamp(0,other_left_endpnt,other_right_endpnt);
		int goal_max = clamp((int)dimensions.x,other_left_endpnt,other_right_endpnt);
		LOGE("This Building: (x-pos:%.2f, x-dim:%.1f), Next Building: (x-pos:%.2f, x-dim:%.1f), goal range:[%d,%d]",pos.x,dimensions.x,next_bldg->pos.x,next_bldg->dimensions.x,goal_min,goal_max);


		active_floor->generate(pos,active_floor_number,global_mins,global_maxs,player_pos,goal_min,goal_max);
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
		exterior_model_count = 0;
		interior_model_count = 0;
		active_floor->clear();
		generated = false;
	}

	//Returns the floor's voxel at point p
	Voxel get_voxel_at(Vec3 p)
	{
		return active_floor->get_voxel_at(p);
	}
	//Returns if the floor has a voxel that is solid at the point p
	char is_solid_at(Vec3 p)
	{
		return active_floor->is_solid_at(p);
	}

	//Returns true if the point p is out of the building's inner bounds, false if not
	bool is_out_of_bounds(Vec3 p)
	{
		if(p.x < global_mins.x || p.x > global_maxs.x)
			return true;
		if(p.y < global_mins.y || p.y > global_maxs.y)
			return true;
		//Z bounds are not handled here
		return false;
	}

	//Returns true if any corner of the bounding box 2*half_width x 2*half_width located at point p is out of bounds
	bool is_box_out_of_bounds(Vec3 p, float half_width)
	{
		if(p.x-half_width < global_mins.x || p.x+half_width > global_maxs.x)
			return true;
		if(p.y-half_width < global_mins.y || p.y+half_width > global_maxs.y)
			return true;
		//Z bounds are not handled here
		return false;
	}


	//Holds a list of shell models for the building exterior
	Static_Model* exterior_models[BUILDING_MAX_EXTERIOR_MODELS];
	Mat4 exterior_model_transforms[BUILDING_MAX_EXTERIOR_MODELS];
	int exterior_model_count = 0;

	//Holds a list of shell models for the building interior
	Static_Model* interior_models[BUILDING_MAX_INTERIOR_MODELS];
	Mat4 interior_model_transforms[BUILDING_MAX_INTERIOR_MODELS];
	int interior_model_count = 0;

//#define DEBUG_SUBDIVIDE_WALL

	//Recursively 2d partitions a wall into the largest (nxn) (n being 2^i for all integers i in [0,5]) tiles that fit
	//Then we draw these tiles, drastically reducing the draw call counts for the buildings
	void subdivide_wall(Mat4 trans, int wall_width, int wall_height)
	{
		Static_Model* models[6];
		models[0] = Global_Tiles::instance->window_models->tile_model;
		models[1] = Global_Tiles::instance->window_models->m2x2_model;
		models[2] = Global_Tiles::instance->window_models->m4x4_model;
		models[3] = Global_Tiles::instance->window_models->m8x8_model;
		models[4] = Global_Tiles::instance->window_models->m16x16_model;
		models[5] = Global_Tiles::instance->window_models->m32x32_model;

		Static_Model* hor_models[6];
		hor_models[0] = Global_Tiles::instance->window_models->tile_model;
		hor_models[1] = Global_Tiles::instance->window_models->m1x2_model;
		hor_models[2] = Global_Tiles::instance->window_models->m1x4_model;
		hor_models[3] = Global_Tiles::instance->window_models->m1x8_model;
		hor_models[4] = Global_Tiles::instance->window_models->m1x16_model;
		hor_models[5] = Global_Tiles::instance->window_models->m1x32_model;

		Static_Model* vert_models[6];
		vert_models[0] = Global_Tiles::instance->window_models->tile_model;
		vert_models[1] = Global_Tiles::instance->window_models->m2x1_model;
		vert_models[2] = Global_Tiles::instance->window_models->m4x1_model;
		vert_models[3] = Global_Tiles::instance->window_models->m8x1_model;
		vert_models[4] = Global_Tiles::instance->window_models->m16x1_model;
		vert_models[5] = Global_Tiles::instance->window_models->m32x1_model;

		Mat4 m;

		for(int i = BUILDING_WINDOW_MAX_TILE_MATRIX; i >= 0; i--)
		{
			int exp = 1 << i;
			if(wall_width == 1 && wall_height >= exp)
			{
				int num_y = wall_height / exp;
				Static_Model* model = vert_models[i];
#ifdef DEBUG_SUBDIVIDE_WALL
				LOGI("Generated 1x%d 1x%d models. bounds:(%d,%d)",num_y,exp,wall_width,wall_height);
#endif
				//Generate 1 by num_y
				for(int k = 0; k < num_y; k++)
				{
					if(exterior_model_count >= BUILDING_MAX_EXTERIOR_MODELS)
					{
						LOGW("Warning, exceeded max exterior model count of %d",exterior_model_count);
						return;
					}
					exterior_models[exterior_model_count] = model;
					exterior_model_transforms[exterior_model_count++] = trans * Mat4::TRANSLATE(Vec3(0,0,k*exp*WINDOW_TILE_SIZE));
				}

				//Getting the end point that we filled to:
				Vec3 ofs = Vec3(1, 0, num_y * exp);
				//If we did not fill the wall vertically
				if(wall_height - (num_y * exp) > 0)
				{
#ifdef DEBUG_SUBDIVIDE_WALL
					LOGI("Calling subdivide at top on:  %dx%d area at (0,0,%d)",wall_width, wall_height-(int)ofs.z,(int)ofs.z);
#endif
					//Generate from the left all the way to the right
					subdivide_wall(trans * Mat4::TRANSLATE(Vec3(0,0,ofs.z * WINDOW_TILE_SIZE)),1, wall_height-(int)ofs.z);
				}
				return;
			}
			if(wall_height == 1 && wall_width >= exp)
			{
				int num_x = wall_width / exp;
				Static_Model* model = hor_models[i];
#ifdef DEBUG_SUBDIVIDE_WALL
				LOGI("Generated %dx1 %dx1 models. bounds:(%d,%d)",num_x,exp,wall_width,wall_height);
#endif
				//Generate num_x by 1 wall
				for(int j = 0; j < num_x; j++)
				{
					if(exterior_model_count >= BUILDING_MAX_EXTERIOR_MODELS)
					{
						LOGW("Warning, exceeded max exterior model count of %d",exterior_model_count);
						return;
					}
					exterior_models[exterior_model_count] = model;
					exterior_model_transforms[exterior_model_count++] = trans * Mat4::TRANSLATE(Vec3(j*exp*TILE_SIZE,0,0));
				}

				//Getting the end point that we filled to:
				Vec3 ofs = Vec3(num_x * exp, 0, 1);
				//If we did not fill the wall horizontally
				if(wall_width - (num_x * exp) > 0)
				{
#ifdef DEBUG_SUBDIVIDE_WALL
					LOGI("Calling subdivide on right on:  %dx%d area at (%d,0,0)",wall_width-(int)ofs.x, (int)ofs.z,(int)ofs.x);
#endif
					//Generate from bottom to the top of the tiles that we placed
					subdivide_wall(trans * Mat4::TRANSLATE(Vec3(ofs.x * TILE_SIZE,0,0)),wall_width-(int)ofs.x, 1);
				}
				return;
			}
			if(wall_width >= exp && wall_height >= exp && (wall_width > 1 && wall_height > 1))
			{
				int num_x = wall_width / exp;
				int num_y = wall_height / exp;

				Static_Model* model = models[i];
#ifdef DEBUG_SUBDIVIDE_WALL
				LOGI("Generated %dx%d %dx%d models. bounds:(%d,%d)",num_x,num_y,exp,exp,wall_width,wall_height);
#endif
				//Generate num_x by num_y wall
				for(int j = 0; j < num_x; j++)
				{
					for(int k = 0; k < num_y; k++)
					{
						if(exterior_model_count >= BUILDING_MAX_EXTERIOR_MODELS)
						{
							LOGW("Warning, exceeded max exterior model count of %d",exterior_model_count);
							return;
						}
						exterior_models[exterior_model_count] = model;
						exterior_model_transforms[exterior_model_count++] = trans * Mat4::TRANSLATE(Vec3(j*exp*TILE_SIZE,0,k*exp*WINDOW_TILE_SIZE));
					}
				}

				//Getting the end point that we filled to:
				Vec3 ofs = Vec3(num_x * exp, 0, num_y * exp);


				//If we did not fill the wall vertically
				if(wall_height - (num_y * exp) > 0)
				{
#ifdef DEBUG_SUBDIVIDE_WALL
					LOGI("Calling subdivide at top on:  %dx%d area at (0,0,%d)",wall_width, wall_height-(int)ofs.z,(int)ofs.z);
#endif
					//Generate from the left all the way to the right
					subdivide_wall(trans * Mat4::TRANSLATE(Vec3(0,0,ofs.z * WINDOW_TILE_SIZE)),wall_width, wall_height-(int)ofs.z);
				}
				//If we did not fill the wall horizontally
				if(wall_width - (num_x * exp) > 0)
				{
#ifdef DEBUG_SUBDIVIDE_WALL
					LOGI("Calling subdivide on right on:  %dx%d area at (%d,0,0)",wall_width-(int)ofs.x, (int)ofs.z,(int)ofs.x);
#endif
					//Generate from bottom to the top of the tiles that we placed
					subdivide_wall(trans * Mat4::TRANSLATE(Vec3(ofs.x * TILE_SIZE,0,0)),wall_width-(int)ofs.x, (int)ofs.z);
				}
				return;
			}
		}
	}

	//Subdivide an interior window wall horizontally
	void subdivide_interior_wall(Mat4 trans, int wall_width)
	{
		Static_Model* hor_models[6];
		//TODO: change these references depending on the style
		hor_models[0] = Global_Tiles::instance->int_window_models->tile_model;
		hor_models[1] = Global_Tiles::instance->int_window_models->m1x2_model;
		hor_models[2] = Global_Tiles::instance->int_window_models->m1x4_model;
		hor_models[3] = Global_Tiles::instance->int_window_models->m1x8_model;
		hor_models[4] = Global_Tiles::instance->int_window_models->m1x16_model;
		hor_models[5] = Global_Tiles::instance->int_window_models->m1x32_model;


		Mat4 m;

		for(int i = BUILDING_WINDOW_MAX_TILE_MATRIX; i >= 0; i--)
		{
			int exp = 1 << i;
			if(wall_width >= exp)
			{
				int num_x = wall_width / exp;
				Static_Model* model = hor_models[i];
				//Generate a num_x wide interior wall
				for(int j = 0; j < num_x; j++)
				{
					if(exterior_model_count >= BUILDING_MAX_EXTERIOR_MODELS)
					{
						LOGW("Warning, exceeded max exterior model count of %d",exterior_model_count);
						return;
					}
					interior_models[interior_model_count] = model;
					interior_model_transforms[interior_model_count++] = trans * Mat4::TRANSLATE(Vec3(j*exp*TILE_SIZE,0,0));
				}

				//Getting the end point that we filled to:
				Vec3 ofs = Vec3(num_x * exp, 0, 1);
				//If we did not fill the wall horizontally
				if(wall_width - (num_x * exp) > 0)
				{
					//Generate from bottom to the top of the tiles that we placed
					subdivide_interior_wall(trans * Mat4::TRANSLATE(Vec3(ofs.x * TILE_SIZE,0,0)),wall_width-(int)ofs.x);
				}
				return;
			}
		}
	}

	void generate_exterior_model_list()
	{
		//TODO: set exterior style model
		//Generating the front wall of the building
		Mat4 world_trans = Mat4::TRANSLATE(global_mins);
		subdivide_wall(world_trans,(int)dimensions.x,(int)dimensions.z);

		//Generating the back wall of the building
		Mat4 wall_orientation = world_trans * Mat4::TRANSLATE(Vec3(size.x,size.y,0)) * Mat4::ROTATE(Quat(PI,Vec3::UP()));
		subdivide_wall(wall_orientation,(int)dimensions.x,(int)dimensions.z);

		//Generating the right wall of the building
		wall_orientation = world_trans * Mat4::TRANSLATE(Vec3(size.x,0,0)) * Mat4::ROTATE(Quat(HALF_PI,Vec3::UP()));
		subdivide_wall(wall_orientation,(int)dimensions.y,(int)dimensions.z);

		//Generating the left wall of the building
		wall_orientation = world_trans * Mat4::TRANSLATE(Vec3(0,size.y,0)) * Mat4::ROTATE(Quat(HALF_PI+PI,Vec3::UP()));
		subdivide_wall(wall_orientation,(int)dimensions.y,(int)dimensions.z);

		LOGE("Exterior model list generation finished using %d models",exterior_model_count);
	}

	void generate_interior_model_list()
	{
		//TODO: set exterior style model
		//Generating the front inside wall of the building
		Mat4 world_trans = Mat4::TRANSLATE(global_mins + Vec3(0,0,active_floor_number*WINDOW_TILE_SIZE));
		subdivide_interior_wall(world_trans,(int)dimensions.x);

		//Generating the back inside wall of the building
		Mat4 wall_orientation = world_trans * Mat4::TRANSLATE(Vec3(size.x,size.y,0)) * Mat4::ROTATE(Quat(PI,Vec3::UP()));
		subdivide_interior_wall(wall_orientation,(int)dimensions.x);

		//Generating the right inside wall of the building
		wall_orientation = world_trans * Mat4::TRANSLATE(Vec3(size.x,0,0)) * Mat4::ROTATE(Quat(HALF_PI,Vec3::UP()));
		subdivide_interior_wall(wall_orientation,(int)dimensions.y);

		//Generating the left inside wall of the building
		wall_orientation = world_trans * Mat4::TRANSLATE(Vec3(0,size.y,0)) * Mat4::ROTATE(Quat(HALF_PI+PI,Vec3::UP()));
		subdivide_interior_wall(wall_orientation,(int)dimensions.y);

		LOGE("Interior model list generation finished using %d models",interior_model_count);
	}


	int render_ext_walls(Mat4 vp)
	{
		Mat4 m;
		Mat4 mvp;
		Mat3 m_it;
		//Slight optimization: the way in which I populate this array gives a high probability
		// that two consecutive models are the same model.
		// Thus if the last model we rendered is the same as the current model, we can skip binding this model
		Static_Model* last_model = NULL;
		Static_Model* model;
		Material* mat = Global_Tiles::instance->window_mat;

		for(int i = 0; i < exterior_model_count; i++)
		{
			model = exterior_models[i];
			if(model != last_model)
				model->bind_mesh_data2(mat);
			m = exterior_model_transforms[i];
			mat->bind_value(Shader::PARAM_M_MATRIX, (void*) m.m);

			mvp = vp * m;
			mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

			m_it = m.inverted_then_transposed().get_mat3();
			mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

			model->render_without_bind();
			last_model = model;
		}
		return 1;
	}

	int render_int_walls(Mat4 vp)
	{
		Mat4 m;
		Mat4 mvp;
		Mat3 m_it;
		//Slight optimization: the way in which I populate this array gives a high probability
		// that two consecutive models are the same model.
		// Thus if the last model we rendered is the same as the current model, we can skip binding this model
		Static_Model* last_model = NULL;
		Static_Model* model;
		Material* mat = Global_Tiles::instance->window_int_mat;

		for(int i = 0; i < interior_model_count; i++)
		{
			model = interior_models[i];
			if(model != last_model)
				model->bind_mesh_data2(mat);
			m = interior_model_transforms[i];
			mat->bind_value(Shader::PARAM_M_MATRIX, (void*) m.m);

			mvp = vp * m;
			mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

			m_it = m.inverted_then_transposed().get_mat3();
			mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

			model->render_without_bind();
			last_model = model;
		}
		return 1;
	}

	int render(Vec3 player_pos, Mat4 vp)
	{
		if(!generated)
		{
			return 1;
		}
		//If we are in the building, only render floor and interior glass
		//if we are out of the building, only render exterior FIXME: this needs additional checks for broken windows (culling sides of building as well)
		bool plyr_in_bldg = !is_out_of_bounds(player_pos);

		if(!plyr_in_bldg)
		{
			Global_Tiles::instance->window_mat->bind_material();

			Material* mat = Global_Tiles::instance->window_mat;
			mat->bind_value(Shader::PARAM_TEXTURE_DIFFUSE,(void*) Global_Tiles::instance->window_tex0);
			mat->bind_value(Shader::PARAM_TEXTURE_NORMAL,(void*) Global_Tiles::instance->window_tex0);

			//Using Skybox cubemap
			mat->bind_value(Shader::PARAM_CUBE_MAP,(void*) Global_Tiles::instance->sky_cube_map);

			//Should I render walls independently and cull non-visible ones?
			render_ext_walls(vp);
		}

		if(active_floor && plyr_in_bldg)
		{
			active_floor->render(vp);
		}
		return 1;
	}

	//Rendering method called at the end to render transparent windows and tiles
	int render_transparent_meshes(Vec3 player_pos, Mat4 vp)
	{
		if(!generated)
		{
			return 1;
		}
		bool plyr_in_bldg = !is_out_of_bounds(player_pos);

		//Only render the interior windows if we are in the building
		if(plyr_in_bldg)
		{
			Global_Tiles::instance->window_int_mat->bind_material();

			Material* mat = Global_Tiles::instance->window_int_mat;
			mat->bind_value(Shader::PARAM_TEXTURE_DIFFUSE,(void*) Global_Tiles::instance->window_int_tex0);
			mat->bind_value(Shader::PARAM_TEXTURE_NORMAL,(void*) Global_Tiles::instance->window_int_tex0);
			mat->bind_value(Shader::PARAM_TEXTURE_MISC,(void*) Global_Tiles::instance->window_int_misc_tex0);

			//Using Floor interior cubemap
			//FIXME: make sure we reference the correct style and variant for the floor style and variant
			mat->bind_value(Shader::PARAM_CUBE_MAP,(void*) Global_Tiles::instance->style[0]->variants[0]->ref_cube_map);

			render_int_walls(vp);
		}
		//FIXME: if we end up using transparency in tiles, call transparent render for floor
		//if(active_floor)
		//	active_floor->render(vp);
		return 1;
	}
};
#endif //PARKOUR_BUILDING_HPP
