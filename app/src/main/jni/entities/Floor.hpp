//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_FLOOR_HPP
#define PARKOUR_FLOOR_HPP

#include "../engine/math/math.hpp"
#include "../engine/Game_Object.hpp"
#include "Grid_Tile.hpp"
#include "../game/Global_Tiles.hpp"

class Floor : Entity
{
public:
	//height of the floor's ground level
	float altitude;

	static const int MAX_WIDTH = BUILDING_MAX_WIDTH;
	static const int MAX_LENGTH = BUILDING_MAX_LENGTH;

	//Width/length in tiles
	int width;
	int length;

	//center near bottom of floor
	Vec3 global_pos;
	Vec3 global_mins;
	Vec3 global_maxs;

	//Type index of tile
	int tile_type[MAX_WIDTH][MAX_LENGTH];
	//Subtype index of tile (used for walls)
	int tile_subtype[MAX_WIDTH][MAX_LENGTH];
	//Variant index of tile
	int tile_variant[MAX_WIDTH][MAX_LENGTH];

	//What tile set are we using?
	int interior_style;
	//What material are we using?
	int interior_variant;

	//For convenience/speed, we're going to hold an array of pointers to models and collision maps
	Collision_Map* tile_coll_map[MAX_WIDTH][MAX_LENGTH];
	Static_Model* tile_model[MAX_WIDTH][MAX_LENGTH];
	Grid_Tile* tile_object[MAX_WIDTH][MAX_LENGTH];

	Floor()
	{
		global_pos = Vec3(0,0,0);
		altitude = 0;
	}
	~Floor()
	{
	}

	void clear_floor_tiles()
	{
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < length; j++)
			{
				tile_type[i][j] = TILE_TYPE_EMPT;
				tile_subtype[i][j] = 0;
				tile_variant[i][j] = 0;
			}
		}
	}

	//Populates the floor matrices reading generated type, subtypes, and variants
	void populate_floor()
	{
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < length; j++)
			{
				int ttype = tile_type[i][j];
				int t_subtype = tile_subtype[i][j];

				//Setting references to models and collision maps
				Grid_Tile* obj = NULL;

				//tile_object[i][j] = Global_Tiles::instance->test_tiles[ttype];
				//TODO: do this with arrays
				switch(ttype)
				{
					default:
					case TILE_TYPE_EMPT:
						obj = Global_Tiles::instance->style[0]->empty_tile;
						break;
					case TILE_TYPE_SOLD:
						obj = Global_Tiles::instance->style[0]->solid_tile;
						break;
					case TILE_TYPE_WALL:
						//TODO: do this with arrays, too
						switch(t_subtype)
						{
							default:
							case WALL_TYPE_xXyY:
								obj = Global_Tiles::instance->style[0]->wall_xXyY;
								break;
							case WALL_TYPE_oXoY:
								obj = Global_Tiles::instance->style[0]->wall_oXoY;
								break;
							case WALL_TYPE_xooY:
								obj = Global_Tiles::instance->style[0]->wall_xooY;
								break;
							case WALL_TYPE_xoyo:
								obj = Global_Tiles::instance->style[0]->wall_xoyo;
								break;
							case WALL_TYPE_oXyo:
								obj = Global_Tiles::instance->style[0]->wall_oXyo;
								break;
							case WALL_TYPE_xXoo:
								obj = Global_Tiles::instance->style[0]->wall_xXoo;
								break;
							case WALL_TYPE_ooyY:
								obj = Global_Tiles::instance->style[0]->wall_ooyY;
								break;
							case WALL_TYPE_xoyY:
								obj = Global_Tiles::instance->style[0]->wall_xoyY;
								break;
							case WALL_TYPE_oXyY:
								obj = Global_Tiles::instance->style[0]->wall_oXyY;
								break;
							case WALL_TYPE_xXyo:
								obj = Global_Tiles::instance->style[0]->wall_xXyo;
								break;
							case WALL_TYPE_xXoY:
								obj = Global_Tiles::instance->style[0]->wall_xXoY;
								break;
							case WALL_TYPE_xooo:
								obj = Global_Tiles::instance->style[0]->wall_xooo;
								break;
							case WALL_TYPE_oXoo:
								obj = Global_Tiles::instance->style[0]->wall_oXoo;
								break;
							case WALL_TYPE_ooyo:
								obj = Global_Tiles::instance->style[0]->wall_ooyo;
								break;
							case WALL_TYPE_oooY:
								obj = Global_Tiles::instance->style[0]->wall_oooY;
								break;
						}
						break;
					case TILE_TYPE_OBST:
						switch(t_subtype)
						{
							default:
							case 0:
								obj = Global_Tiles::instance->style[0]->floor_vent;
								break;
							case 1:
								obj = Global_Tiles::instance->style[0]->wall_vent;
								break;
						}
						break;
				}
				tile_object[i][j] = obj;
				tile_coll_map[i][j] = obj->coll_map;
				tile_model[i][j] = obj->model;
			}
		}
	}

	struct Wall
	{
		char x1 = 0;
		char y1 = 0;
		char x2 = 0;
		char y2 = 0;

		Wall()
		{
			x1 = y1 = x2 = y2 = 0;
		}
		Wall(const char a,const char b,const char c,const char d)
		{
			x1 = a;
			y1 = b;
			x2 = c;
			y2 = d;
		}
	};

	struct Room
	{
		char min_x = 0;
		char min_y = 0;
		char max_x = 0;
		char max_y = 0;

		Room()
		{
			min_x = min_y = max_x = max_y = 0;
		}

		Room(const char a,const char b,const char c,const char d)
		{
			min_x = a;
			min_y = b;
			max_x = c;
			max_y = d;
		}

		Wall get_north_wall()
		{
			return Wall(min_x,max_y,max_x,max_y);
		}

		Wall get_east_wall()
		{
			return Wall(max_x,min_y,max_x,max_y);
		}

		Wall get_south_wall()
		{
			return Wall(min_x,min_y,max_x,min_y);
		}

		Wall get_west_wall()
		{
			return Wall(min_x,min_y,min_x,max_y);
		}
	};

//#define DEBUG_RBSP

	//Recursively divides the room **stack_ptr, returns the divided rooms on the array *stack_ptr
	void recursive_bsp(Room** stack_ptr,const bool horizontal_divide)
	{
		//Copy the room (we write to stack_ptr, so we need a backup)
		Room rm = (**stack_ptr);

#ifdef DEBUG_RBSP
		LOGE("recursive_bsp: x(%d,%d), y(%d,%d), horizontal_divide: %d",rm.min_x,rm.max_x,rm.min_y,rm.max_y,horizontal_divide);
#endif
		//Getting the size of the room
		char size_x = rm.max_x - rm.min_x;
		char size_y = rm.max_y - rm.min_y;

		//Stop dividing if the room is small enough
		//TODO: random chance to stop dividing before we reach min size
		//TODO: 2 is too small, I think 3 is the threshold to stop dividing
		if(size_x <= 2 || size_y <= 2)
			return;

		//Get the division point (0,1)
		float div = Random::rand();

		Room divide_point; //maxs are maxs of room 1, mins are mins of room 2

		if(horizontal_divide)
		{
			//Division is horizontal
			char delta = (char)(floorf(div * (size_y - 1)) + 1);
			divide_point = Room(rm.min_x,rm.min_y + delta, rm.max_x, rm.min_y + delta);
		}
		else
		{
			//Division is vertical
			char delta = (char)(floorf(div * (size_x - 1)) + 1);
			divide_point = Room( rm.min_x + delta, rm.min_y, rm.min_x + delta,rm.max_y);
		}
#ifdef DEBUG_RBSP
		LOGE("Dividing room: ( x(%d,%d), y(%d,%d) ) , ( x(%d,%d), y(%d,%d) )",rm.min_x,divide_point.max_x,rm.min_y,divide_point.max_y,  divide_point.min_x,rm.max_x,divide_point.min_y,rm.max_y);
#endif

		//create two additional stacks for the two rooms we divide into, and their subdivided rooms
		Room room_stack1[(length-1) * (width-1)];
		Room* room_stack_ptr1 = room_stack1;

		//Set the first room from this new stack as the first subdivided room
		*room_stack_ptr1 = Room(rm.min_x, rm.min_y, divide_point.max_x, divide_point.max_y);

#ifdef DEBUG_RBSP
		LOGE("\t---1assigned ptr1:(%p) as x(%d,%d) y(%d,%d)",room_stack_ptr1,room_stack_ptr1->min_x,room_stack_ptr1->max_x, room_stack_ptr1->min_y,room_stack_ptr1->max_y);
#endif

		//room_stack_ptr1 is now a pointer to the first room
		recursive_bsp(&room_stack_ptr1, !horizontal_divide);
		//room_stack_ptr1 is now a pointer to one past the last room

		//Moving back stack_ptr one element, so that the code below can move it up once every iteration
		//(this only needs to be done once)
		(*stack_ptr)--;

		//Copying all of the recursively subdivided rooms to our main stack
		for(Room* ptr = room_stack1; ptr <= room_stack_ptr1; ptr++)
		{
			(*stack_ptr)++;
			//Copying the room ptr to the stack
			(**stack_ptr) = *ptr;
#ifdef DEBUG_RBSP
			LOGE("\t1assigned ptr:(%p) as x(%d,%d) y(%d,%d) (from %p)", (*stack_ptr),(*stack_ptr)->min_x,(*stack_ptr)->max_x, (*stack_ptr)->min_y,(*stack_ptr)->max_y,ptr);
			LOGE("\tincremented ptr to: (%p)",(*stack_ptr));
#endif
		}

		Room room_stack2[(length-1) * (width-1)];
		Room* room_stack_ptr2 = room_stack2;

		//Set the first room from this second new stack as the second subdivided room
		*room_stack_ptr2 = Room(divide_point.min_x, divide_point.min_y, rm.max_x, rm.max_y);

#ifdef DEBUG_RBSP
		LOGE("\t---2assigned ptr2:(%p) as x(%d,%d) y(%d,%d)", room_stack_ptr2,room_stack_ptr2->min_x,room_stack_ptr2->max_x, room_stack_ptr2->min_y,room_stack_ptr2->max_y);
#endif
		recursive_bsp(&room_stack_ptr2, !horizontal_divide);

		//Copying all of the recursively subdivided rooms to our main stack
		for(Room* ptr = room_stack2; ptr <= room_stack_ptr2; ptr++)
		{
			(*stack_ptr)++;
			//Copying the room ptr to the stack
			(**stack_ptr) = *ptr;
#ifdef DEBUG_RBSP
			LOGE("\t2assigned ptr:(%p) as x(%d,%d) y(%d,%d) (from %p)", (*stack_ptr),(*stack_ptr)->min_x,(*stack_ptr)->max_x, (*stack_ptr)->min_y,(*stack_ptr)->max_y,ptr);
			LOGE("\tincremented ptr to: (%p)",(*stack_ptr));
#endif
		}
	}

	//Returns true if min <= x <= max
	inline bool in_bounds(const char x,const char min,const char max)
	{
		return (x >= min) && (x <= max);
	}

	//Returns true if a == b == c == d
	inline bool all_equal(const char a,const char b,const char c,const char d)
	{
		return (a == b) && (b == c) && (a == d);
	}
	//Checks if w1 is completely inside of w2
	//0 means walls are not inside each other
	//1 means w1 is inside of w2
	//2 means w2 is inisde of w1
	char is_wall_in_wall(const Wall* w1,const Wall* w2)
	{
		//Check if walls are both horizontal and on the same y-coordinate
		if(all_equal(w1->y1,w1->y2,w2->y1,w2->y2))
		{
			//Check if w1 is inside of w2
			//If w1's left vertex is inside of w2's bounds
			if(in_bounds(w1->x1,w2->x1,w2->x2))
			{
				//If w1's right vertex is inside of w2's bounds
				if(in_bounds(w1->x2,w2->x1,w2->x2))
				{
					//w1 is inside of w2
					return 1;
				}
			}
			//Check if w2 is inside of w1
			//If w2's left vertex is inside of w1's bounds
			if(in_bounds(w2->x1,w1->x1,w1->x2))
			{
				//If w2's right vertex is inside of w1's bounds
				if(in_bounds(w2->x2,w1->x1,w1->x2))
				{
					//w2 is inside of w1
					return 2;
				}
			}
		}
		//Check if walls are both vertical and on the same x-coordinate
		else if(all_equal(w1->x1,w1->x2,w2->x1,w2->x2))
		{
			//Check if w1 is inside of w2
			//If w1's left vertex is inside of w2's bounds
			if(in_bounds(w1->y1,w2->y1,w2->y2))
			{
				//If w1's right vertex is inside of w2's bounds
				if(in_bounds(w1->y2,w2->y1,w2->y2))
				{
					//w1 is inside of w2
					return 1;
				}
			}
			//Check if w2 is inside of w1
			//If w2's left vertex is inside of w1's bounds
			if(in_bounds(w2->y1,w1->y1,w1->y2))
			{
				//If w2's right vertex is inside of w1's bounds
				if(in_bounds(w2->y2,w1->y1,w1->y2))
				{
					//w2 is inside of w1
					return 2;
				}
			}
		}
		//Walls are not inside of each other
		return 0;
	}

	//Adds wall to list if w is not in any wall on the list
	//Replaces a wall in the list if w is completely inside of the wall and smaller
	//Does not add w to the list if there is a wall in the list completely inside w and smaller than w
	//Does not add w to the list if the wall makes up the building exterior
	//Returns 0 if wall was not added, returns 1 otherwise
	int add_wall_to_list(const Wall* w, Wall* list_start, Wall** list_end)
	{
		//Checking if wall lies on the building exterior boundary
		if(w->x1 == w->x2 && (w->x1 == 0 || w->x1 == width-1))
		{
			return 0;
		}
		if(w->y1 == w->y2 && (w->y1 == 0 || w->y1 == length-1))
		{
			return 0;
		}


		char res;
		for(Wall* ptr = list_start; ptr < *list_end; ptr++)
		{
			res = is_wall_in_wall(w,ptr);
			if(!res)
				continue;
			if(res == 2)//ptr is in w
			{
				return 1;
			}
			if(res == 1)//w is in ptr
			{
				//Assign ptr as wall w
				*ptr = *w;
				return 1;
			}
		}
		//w is not in the list.
		**list_end = *w;
		(*list_end)++;
		return 1;
	}

	//Returns unique walls given a list of rooms
	//Where rooms is a pointer to Rooms, last_room is a pointer to the last room
	//Walls is a pointer to an array of enough walls
	void get_unique_walls(Wall** wall_ptr, Room* rooms,const Room* last_room)
	{
		Wall* first_wall = *wall_ptr;
		Wall* last_wall = *wall_ptr;

		Wall w;
		for(Room* ptr = rooms; ptr <= last_room; ptr++)
		{
			w = ptr->get_north_wall();
			add_wall_to_list(&w, first_wall, &last_wall);
			w = ptr->get_east_wall();
			add_wall_to_list(&w, first_wall, &last_wall);
			w = ptr->get_south_wall();
			add_wall_to_list(&w, first_wall, &last_wall);
			w = ptr->get_west_wall();
			add_wall_to_list(&w, first_wall, &last_wall);
		}
		*wall_ptr = last_wall;
	}

	void set_vert_wall_tiles(Wall* w)
	{
		//Bottom-most tile
		tile_type[w->x1][w->y1] = TILE_TYPE_WALL;
		tile_subtype[w->x1][w->y1] |= WALL_TYPE_oooY;
		if(w->y1 == 0)
			tile_subtype[w->x1][w->y1] |= WALL_TYPE_ooyo;

		//Top-most tile
		tile_type[w->x1][w->y2] = TILE_TYPE_WALL;
		tile_subtype[w->x1][w->y2] |= WALL_TYPE_ooyo;
		if(w->y2 == length - 1)
			tile_subtype[w->x1][w->y2] |= WALL_TYPE_oooY;

		//Every tile in between first and last
		for(int i = w->y1+1; i < w->y2; i++)
		{
			tile_type[w->x1][i] = TILE_TYPE_WALL;
			tile_subtype[w->x1][i] |= WALL_TYPE_ooyY;
		}
	}

	void set_hor_wall_tiles(Wall* w)
	{
		//Left-most tile
		tile_type[w->x1][w->y1] = TILE_TYPE_WALL;
		tile_subtype[w->x1][w->y1] |= WALL_TYPE_oXoo;
		if(w->x1 == 0)
			tile_subtype[w->x1][w->y1] |= WALL_TYPE_xooo;

		//Right-most tile
		tile_type[w->x2][w->y1] = TILE_TYPE_WALL;
		tile_subtype[w->x2][w->y1] |= WALL_TYPE_xooo;
		if(w->x2 == width - 1)
			tile_subtype[w->x2][w->y1] |= WALL_TYPE_oXoo;

		//Every tile in between first and last
		for(int i = w->x1+1; i < w->x2; i++)
		{
			tile_type[i][w->y1] = TILE_TYPE_WALL;
			tile_subtype[i][w->y1] |= WALL_TYPE_xXoo;
		}
	}

	void generate(Vec3 p, int floor_num, Vec3 mins, Vec3 maxs)
	{
		altitude = p.z + floor_num*(WINDOW_TILE_SIZE);
		global_pos = p + Vec3(0,0,floor_num*WINDOW_TILE_SIZE);
		global_mins = mins;
		global_maxs = maxs;
		global_mins.z = global_maxs.z = altitude;
		width = (int)((global_maxs.x - global_mins.x)/TILE_SIZE);
		length = (int)((global_maxs.y - global_mins.y)/TILE_SIZE);

		//FIXME: this probably shouldn't be here (sets all tile types to 0)
		clear_floor_tiles();

		//temp: explicitly setting some tiles as stuff
		//tile_type[2][3] = TILE_TYPE_SOLD;
		//tile_type[4][3] = TILE_TYPE_OBST;
		//tile_subtype[4][3] = 0;
		//tile_type[6][3] = TILE_TYPE_OBST;
		//tile_subtype[6][3] = 1;
		//tile_type[7][3] = TILE_TYPE_WALL;
		//tile_subtype[7][3] = WALL_TYPE_xXyY;

		//=========== BSP Floor Generation ============

		//Allocating the max possible number of rooms that can be created
		Room room_stack[(length-1) * (width-1)];
		Room* last_room_ptr = room_stack;

		*last_room_ptr = Room(0,0,(char)(width-1),(char)(length-1));//width/length will never exceed 255... we're okay here
		//TODO: make first room stretch from y=1 to y=(length-2), (we leave the first row and last low empty)

		recursive_bsp(&last_room_ptr,true);
		//last_room_ptr now points to the last room on the stack

		//Printing rooms
		for(Room* ptr = room_stack; ptr <= last_room_ptr; ptr++)
		{
			LOGE("Room: x:(%d,%d), y:(%d,%d)",ptr->min_x,ptr->max_x,ptr->min_y,ptr->max_y);
		}

		Wall unique_walls[length * width * 4];
		Wall* next_free_wall = unique_walls;

		get_unique_walls(&next_free_wall, room_stack, last_room_ptr);
		//next_free_wall now points to one pointer past the last wall assigned

		/*int wall_num = 0;
		LOGE("====== Printing Walls: =======");
		for(Wall* ptr = unique_walls; ptr < wall_stack_ptr; ptr++)
		{
			LOGE("Wall[%d]: x(%d,%d) y(%d,%d)",wall_num++,ptr->x1,ptr->x2,ptr->y1,ptr->y2);
		}*/

		//Iterating through walls, adding the appropriate collision tile
		for(Wall* ptr = unique_walls; ptr < next_free_wall; ptr++)
		{
			//Skip walls randomly
			if(Random::rand() < 0.3f)
			{
				LOGE("skipped a wall!");
				continue;
			}

			//If this wall is vertical
			if(ptr->x1 == ptr->x2)
			{
				set_vert_wall_tiles(ptr);
			}
			else //this wall is horizontal
			{
				set_hor_wall_tiles(ptr);
			}
		}

		// ============ end BSP Floor Generation ============
		populate_floor();
	}


	int render(Mat4 vp)
	{
		//how do we get the material?
		//Need to iterate through all tiles in this floor and draw them
		//Starting from frontmost tile, render it and all other tiles that use the same model
		//Then move onto the next unrendered tile
		//TODO: how will we store tile type in the floors?
		Global_Tiles::instance->style[0]->variants[0]->bind_variant();

		Material* mat = Global_Tiles::instance->style[0]->variants[0]->mat;

		Mat4 m;
		Mat4 world_trans = Mat4::TRANSLATE(global_mins);

		//Quick unoptimized test for rendering
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < length; j++)
			{
				tile_model[i][j]->bind_mesh_data(mat);

				m = world_trans * Mat4::TRANSLATE(Vec3(i*TILE_SIZE,j*TILE_SIZE,0));

				Mat4 mvp = vp * m;
				mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

				Mat3 m_it = m.inverted_then_transposed().get_mat3();
				mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

				tile_model[i][j]->render_without_bind();
			}
		}
	}

	void clear()
	{
		altitude = 0;
		width = length = 0;
		global_mins = Vec3::ZERO();
		global_maxs = Vec3::ZERO();
	}

	char is_solid_at(Vec3 p)
	{
		//position given is in floor space, 0,0 being near left corner
		//get tile indices for the position
		if(is_x_out_of_bounds(p) || is_y_out_of_bounds(p))
		{
			LOGW("Warning: X or Y coord to check is out of bounds: coords:(%f,%f), mins:(%f,%f), maxs:(%f,%f)",p.x,p.y,global_mins.x,global_mins.y,global_maxs.x,global_maxs.y);
			return CLIP_SOLID;
		}

		//finding player pos relative to left near corner of floor
		p = p - global_mins;

		int tile_x = (int) floorf(p.x/TILE_SIZE);
		int tile_y = (int) floorf(p.y/TILE_SIZE);

		if(tile_x < 0 || tile_y < 0 || tile_x >= width || tile_y >= length)
		{
			LOGW("Warning: tried reaching out of bounds tile: (floor dims: (%d x %d), index: (%d x %d))",width,length,tile_x,tile_y);
			return CLIP_SOLID;
		}

		Vec3 vox_p = Vec3(efmodf(p.x,TILE_SIZE),efmodf(p.y,TILE_SIZE),0);
		int vox_x = (int) (floorf(vox_p.x/GRID_SIZE));
		int vox_y = (int) (floorf(vox_p.y/GRID_SIZE));

		if(vox_x < 0 || vox_y < 0 || vox_x >= TILE_VOXEL_DIMS || vox_y >= TILE_VOXEL_DIMS)
		{
			LOGW("Warning: tried reaching out of bounds voxel: (index: (%d x %d))",vox_x,vox_y);
			return CLIP_SOLID;
		}

		char rank = tile_coll_map[tile_x][tile_y]->get_vox_at(vox_x,vox_y);
		if(rank != 0)
			LOGE("Tile[%d][%d], Voxel[%d][%d] = %d",tile_x,tile_y,vox_x,vox_y,rank);

		return tile_coll_map[tile_x][tile_y]->get_vox_at(vox_x,vox_y);
	}

	bool is_y_out_of_bounds(Vec3 p)
	{
		if(p.y < global_mins.y || p.y > global_maxs.y)
			return true;
		return false;
	}

	bool is_x_out_of_bounds(Vec3 p)
	{
		if(p.x < global_mins.x || p.x > global_maxs.x)
			return true;
		return false;
	}

	//	Returns a maneuver if there exists a maneuver in the this floor's tileset such that:
	//	(the input required to start the maneuver is input_type) AND (the player is within the bounding box required to start the maneuver)
	//	returns NULL if no such tile exists

	//==== Quick note on what tiles we have to check ====
	//Previously, the 1st keyframe of a maneuver had to lie within that tile
	//But that is no longer the case

	//As a rule of thumb, the start of the maneuver must lie within the tile itself, or the tile before it
	//so for a given player position, we must check the tile the player is on and the tile after it (+1 in y direction)
	//=====================================

	Maneuver* input_to_maneuver(Vec3 pos, int input_type)
	{
		//position given is in floor space, 0,0 being near left corner
		//get tile indices for the position
		if(is_x_out_of_bounds(pos) || is_y_out_of_bounds(pos))
		{
			LOGW("Warning: X or Y coord to check is out of bounds: coords:(%f,%f), mins:(%f,%f), maxs:(%f,%f)",pos.x,pos.y,global_mins.x,global_mins.y,global_maxs.x,global_maxs.y);
			return NULL;
		}

		//finding player pos relative to left near corner of floor
		Vec3 floor_pos = pos - global_mins;

		int tile_x = (int) floorf(floor_pos.x/TILE_SIZE);
		int tile_y = (int) floorf(floor_pos.y/TILE_SIZE);

		if(tile_x < 0 || tile_y < 0 || tile_x >= width || tile_y >= length)
		{
			LOGW("Warning: tried reaching out of bounds tile: (floor dims: (%d x %d), index: (%d x %d))",width,length,tile_x,tile_y);
			return NULL;
		}
		//Checking the tile the player is on
		Vec3 mins;
		Vec3 maxs;
		Maneuver* man = NULL;

		//Getting player pos relative to the tile
		Vec3 p = floor_pos - Vec3(tile_x * TILE_SIZE, tile_y * TILE_SIZE, 0);
		Grid_Tile* tile = tile_object[tile_x][tile_y];

		for(int i = 0; i < tile->maneuver_count; i++)
		{
			man = tile->maneuvers[i];
			//If we have the correct input
			if(input_type & man->input_required)
			{
				//If we are in the correct area
				mins = man->keyframes[0]->mins;
				maxs = man->keyframes[0]->maxs;
				if(p.x >= mins.x && p.x <= maxs.x && p.y >= mins.y && p.y <= maxs.y)
				{
					return man;
				}
			}
		}

		//Checking the next tile
		tile_y++;

		if(tile_y >= length)
		{
			//There is no tile after
			return NULL;
		}

		//Getting player pos relative to the tile
		p = floor_pos - Vec3(tile_x * TILE_SIZE, tile_y * TILE_SIZE, 0);
		tile = tile_object[tile_x][tile_y];


		for(int i = 0; i < tile->maneuver_count; i++)
		{
			man = tile->maneuvers[i];
			//If we have the correct input
			if(input_type | man->input_required)
			{
				//If we are in the correct area
				mins = man->keyframes[0]->mins;
				maxs = man->keyframes[0]->maxs;
				if(p.x >= mins.x && p.x <= maxs.x && p.y >= mins.y && p.y <= maxs.y)
				{
					return man;
				}
			}
		}
		return NULL;
	}
	//Returns the global tile position that p lies on
	Vec3 get_tile_ofs_at_pos(Vec3 p)
	{
		p = p - global_mins;
		p = Vec3(floorf(p.x/TILE_SIZE) * TILE_SIZE,floorf(p.y/TILE_SIZE) * TILE_SIZE,0);
		p = p + global_mins;
		return p;
	}
};

#endif //PARKOUR_FLOOR_HPP
